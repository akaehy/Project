#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Macro definition
//--------------------------------------------------------------------
#define BUFFER_SIZE	1024

//--------------------------------------------------------------------
// Type definition
//--------------------------------------------------------------------
typedef struct
{
  char *data;
  unsigned long size;
  unsigned long payload_length;
} buf_t;

typedef struct
{
  buf_t *rbuf;
  buf_t *sbuf;

  //struct sockaddr_in ipv4_address;
  //char ip[] = "ddd.ddd.ddd.ddd";
  char *ip;
  unsigned short port;

  // define other member here.
} conn_t;

//--------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------
conn_t **global_conn_list = NULL;
int global_conn_list_count = 0;
fd_set global_read_set, global_write_set, global_except_set;
int global_maxfd = 0;
volatile sig_atomic_t global_exit_flag = 0;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
void do_extra_job(void);

void *utils_safe_malloc(size_t size);
void utils_safe_free(void *ptr);

int init_conn_list(int n);
void destroy_conn_list(void);

conn_t *init_conn_object(void);
void destroy_conn_object(conn_t * p);

buf_t *init_buf_object(void);
void destroy_buf_object(buf_t * ptr);

int net_accept(int listening_socket);
int net_read(int fd);
int net_write(int fd);

void net_register_read(int fd);
void net_unregister_read(int fd);
void net_register_write(int fd);
void net_unregister_write(int fd);
void net_register_except(int fd);
void net_unregister_except(int fd);

void sigpipe_handler(int sig);
void sigterm_handler(int sig);

int buffered_send(int fd, const void *buf, size_t count);
int parse_data(int fd);
int exchange_data(int fd);

//--------------------------------------------------------------------
// Main function
// Usage: ./app <ip> <port> <backlog>
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  int listening_socket;
  unsigned short port;
  int backlog;

  //------------------------------------------------------------------
  // Initialize global_conn_list
  //------------------------------------------------------------------
  if (init_conn_list(1024) < 0)
  {
    fprintf(stderr, "Create global_conn_list failed, terminat.\n");
    exit(1);
  }

  FD_ZERO(&global_read_set);
  FD_ZERO(&global_write_set);
  FD_ZERO(&global_except_set);

  global_maxfd = 0;

  //------------------------------------------------------------------
  // Parse command line arguments
  //------------------------------------------------------------------
  port = (unsigned short) strtol(argv[2], NULL, 10);
  backlog = (int) strtol(argv[3], NULL, 10);

  //------------------------------------------------------------------
  // Create listening_socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((listening_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "Create new TCP socket failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new TCP socket, listening_socket = %d\n", listening_socket);

  //------------------------------------------------------------------
  // Set SO_REUSEADDR & SO_REUSEPORT options
  //------------------------------------------------------------------
  int optval;

  optval = 1;
  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

#ifdef SO_REUSEPORT
  optval = 1;
  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif

  //------------------------------------------------------------------
  // bind
  //------------------------------------------------------------------
  struct sockaddr_in local_ipv4_address;

  memset(&local_ipv4_address, 0, sizeof(local_ipv4_address));

  local_ipv4_address.sin_family = AF_INET;	// IPv4
  local_ipv4_address.sin_port = htons(port);	// Network byte order

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[1], &local_ipv4_address.sin_addr);

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  if (bind(listening_socket, (struct sockaddr *) &local_ipv4_address, sizeof(local_ipv4_address)) < 0)
  {
    fprintf(stderr, "Bind to %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Bound to %s:%d successfully.\n", argv[1], port);

  //------------------------------------------------------------------
  // listen
  //------------------------------------------------------------------
  //int listen(int sockfd, int backlog);
  if (listen(listening_socket, backlog) < 0)
  {
    fprintf(stderr, "Listen on %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Listen on %s:%d successfully.\n", argv[1], port);

  //------------------------------------------------------------------
  // Add listening_socket to global_read_set
  //------------------------------------------------------------------
  net_register_read(listening_socket);

  //------------------------------------------------------------------
  // Set signal handlers
  //------------------------------------------------------------------
  struct sigaction act, oact;

#if 0
  struct sigaction
  {
    void (*sa_handler) (int);
    void (*sa_sigaction) (int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  };
#endif

  memset(&act, 0, sizeof(act));

  act.sa_handler = sigpipe_handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  sigaction(SIGPIPE, &act, &oact);

  memset(&act, 0, sizeof(act));

  act.sa_handler = sigterm_handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  sigaction(SIGINT, &act, &oact);
  sigaction(SIGTERM, &act, &oact);
  sigaction(SIGQUIT, &act, &oact);

  //------------------------------------------------------------------
  // Main loop
  //------------------------------------------------------------------
  fd_set rset, wset, eset;
  struct timeval to;
  int n;

  for (;;)
  {
    if (global_exit_flag > 0)
    {
      fprintf(stdout, "It's time to exit.\n");
      break;
    }

    rset = global_read_set;
    wset = global_write_set;
    eset = global_except_set;

    to.tv_sec = 1;
    to.tv_usec = 0;

    //int select(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval *timeout);
    if ((n = select(global_maxfd + 1, &rset, &wset, &eset, &to)) < 0)
    {
      // failed
      if (errno == EINTR)
      {
	continue;
      }

      // FIXME: How to do?
      fprintf(stderr, "select() failed: %s\n", strerror(errno));
      break;
    }
    else if (n == 0)
    {
      // timeout
      fprintf(stdout, "timeout ...\n");
      do_extra_job();
    }
    else
    {
      // some file descriptors are ready
      int i;

      for (i = 0; i <= global_maxfd; i++)
      {
	//int FD_ISSET(int fd, fd_set * set);
	if (FD_ISSET(i, &rset))
	{
	  // ready to read

	  if (i == listening_socket)
	  {
	    // accept new connection
	    net_accept(i);
	  }
	  else
	  {
	    // read data 
	    //fprintf(stdout, "[TODO]read data on socket %d\n", i);
	    net_read(i);
	  }
	}

	if (FD_ISSET(i, &wset))
	{
	  // ready to write
	  //fprintf(stdout, "[TODO]write data on socket %d\n", i);
	  net_write(i);
	}

#if 0
	if (FD_ISSET(i, &eset))
	{
	  // exception
	}
#endif
      }
    }
  }

  //------------------------------------------------------------------
  // TODO: close read end for every sockets, keep write end still open
  // TODO: int shutdown(int s, int how);
  // TODO: set SO_LINGER option for all sockets
  // TODO: send all unsent data to clients
  // TODO: close every sockets
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  // Close listening_socket
  //------------------------------------------------------------------
  close(listening_socket);

  destroy_conn_list();

  return 0;
}

void do_extra_job(void)
{
  fprintf(stdout, "do_extra_job ...\n");
}

//--------------------------------------------------------------------
// Connection list management
//--------------------------------------------------------------------
int init_conn_list(int n)
{
  //------------------------------------------------------------------
  // Allocate memory for global_conn_list
  //------------------------------------------------------------------
  global_conn_list = utils_safe_malloc(n * sizeof(conn_t *));

  if (!global_conn_list)
  {
    fprintf(stderr, "Allocate memory for glocal_conn_list failed.\n");
    return -1;
  }

  //------------------------------------------------------------------
  // Initialize every node
  //------------------------------------------------------------------
  int i;

  for (i = 0; i < n; i++)
  {
    global_conn_list[i] = NULL;
  }

  //------------------------------------------------------------------
  // Remember the nodes' count
  //------------------------------------------------------------------
  global_conn_list_count = n;

  return 0;
}

void destroy_conn_list(void)
{
  int i;

  //------------------------------------------------------------------
  // Destroy non-NULL nodes
  //------------------------------------------------------------------
  for (i = 0; i < global_conn_list_count; i++)
  {
    if (global_conn_list[i])
    {
      //free(global_conn_list[i]);
      destroy_conn_object(global_conn_list[i]);
    }
  }

  //------------------------------------------------------------------
  // Destroy global_conn_list
  //------------------------------------------------------------------
  utils_safe_free(global_conn_list);

  global_conn_list = NULL;
  global_conn_list_count = 0;
}

//--------------------------------------------------------------------
// Utilities
//--------------------------------------------------------------------
void *utils_safe_malloc(size_t size)
{
  void *p;

  //void *malloc(size_t size);
  p = malloc(size);

  if (!p)
  {
    fprintf(stdout, "%s:%d:%s(): allocate memory failed.\n", __FILE__, __LINE__, __func__);
    return NULL;
  }

  return p;
}

void utils_safe_free(void *ptr)
{
  if (ptr)
  {
    //void free(void *ptr);
    free(ptr);
    //ptr = NULL;
  }
#ifdef _DEBUG_
  else
  {
    fprintf(stderr, "Attempt to free NULL pointer.\n");
  }
#endif
}

//--------------------------------------------------------------------
// conn_t object related functions
//--------------------------------------------------------------------
conn_t *init_conn_object(void)
{
  conn_t *p;

  //------------------------------------------------------------------
  // Allocate memory for conn_t object
  //------------------------------------------------------------------
  p = utils_safe_malloc(sizeof(conn_t));

  if (!p)
  {
    fprintf(stderr, "Allocate memory for conn_t object failed.\n");
    return NULL;
  }

  //------------------------------------------------------------------
  // Initialize rbuf & sbuf
  //------------------------------------------------------------------
  p->rbuf = init_buf_object();
  p->sbuf = init_buf_object();

  //------------------------------------------------------------------
  // Roll back if initialize rbuf or sbuf failed
  //------------------------------------------------------------------
  if (!p->rbuf || !p->sbuf)
  {
    destroy_buf_object(p->rbuf);
    destroy_buf_object(p->sbuf);

    utils_safe_free(p);

    return NULL;
  }

  return p;
}

void destroy_conn_object(conn_t * p)
{
  if (p)
  {
    //----------------------------------------------------------------
    // Destroy rbuf & sbuf
    //----------------------------------------------------------------
    destroy_buf_object(p->rbuf);
    destroy_buf_object(p->sbuf);

    //----------------------------------------------------------------
    // Destroy itself
    //----------------------------------------------------------------
    utils_safe_free(p);

    p = NULL;
  }
}

//--------------------------------------------------------------------
// buf_t object related functions
//--------------------------------------------------------------------
buf_t *init_buf_object(void)
{
  buf_t *p;

  //------------------------------------------------------------------
  // Allocate memory for buf_t object
  //------------------------------------------------------------------
  p = utils_safe_malloc(sizeof(buf_t));

  if (!p)
  {
    fprintf(stderr, "Allocate memory for buf_t object failed.\n");
    return NULL;
  }

  //------------------------------------------------------------------
  // Allocate memory for p->data object
  //------------------------------------------------------------------
  p->data = utils_safe_malloc(BUFFER_SIZE);

  //------------------------------------------------------------------
  // Roll back if initialize p->data failed
  //------------------------------------------------------------------
  if (!p->data)
  {
    utils_safe_free(p);
    return NULL;
  }

  //------------------------------------------------------------------
  // Initialize p->size & p->payload_length
  //------------------------------------------------------------------
  p->size = BUFFER_SIZE;
  p->payload_length = 0;

  return p;
}

void destroy_buf_object(buf_t * ptr)
{
  if (ptr)
  {
    //----------------------------------------------------------------
    // Destroy p->data
    //----------------------------------------------------------------
    utils_safe_free(ptr->data);

    //----------------------------------------------------------------
    // Destroy itself
    //----------------------------------------------------------------
    utils_safe_free(ptr);
  }
}

int net_accept(int listening_socket)
{
  int new_connected_socket;
  struct sockaddr_in peer_ipv4_address;
  socklen_t peer_ipv4_address_length;
  char peer_ipv4_address_string[] = "ddd.ddd.ddd.ddd";

  peer_ipv4_address_length = sizeof(peer_ipv4_address);

  // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  if ((new_connected_socket = accept(listening_socket, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
  {
    // failed
    fprintf(stderr, "Accept new connection on socket %d failed: %s\n", listening_socket, strerror(errno));
    // FIXME: How to do?
  }
  else
  {
    // success
    inet_ntop(AF_INET, &peer_ipv4_address.sin_addr, peer_ipv4_address_string, sizeof(peer_ipv4_address_string));

    fprintf(stdout, "Accepted a new connection %d from %s:%d.\n", new_connected_socket, peer_ipv4_address_string, ntohs(peer_ipv4_address.sin_port));

    // create new_conn object
    conn_t *new_conn = init_conn_object();

    if (!new_conn)
    {
      fprintf(stderr, "Cannot allocate resource for new connection, i'm sorry.\n");

      char internal_server_error_message[] = "Internal server error, try again please.\n";

      //ssize_t send(int s, const void *buf, size_t len, int flags);
      send(new_connected_socket, internal_server_error_message, strlen(internal_server_error_message), 0);

      close(new_connected_socket);
    }
    else
    {
      //char *strdup(const char *s);
      new_conn->ip = strdup(peer_ipv4_address_string);
      new_conn->port = ntohs(peer_ipv4_address.sin_port);

      // Attach new_conn object to global_conn_list
      global_conn_list[new_connected_socket] = new_conn;

      net_register_read(new_connected_socket);
      //net_register_write(new_connected_socket);
      //net_register_except(new_connected_socket);
    }
  }

  return 0;
}

int net_read(int fd)
{
  conn_t *current_conn = global_conn_list[fd];

  if (!current_conn)
  {
    fprintf(stderr, "conn_t object not exists.\n");
    return -1;
  }

  buf_t *rbuf = current_conn->rbuf;

  if (!rbuf)
  {
    fprintf(stderr, "rbuf object not exists.\n");
    return -2;
  }

  ssize_t n;

read_again:
  //ssize_t read(int fd, void *buf, size_t count);
  if ((n = read(fd, rbuf->data + rbuf->payload_length, rbuf->size - rbuf->payload_length)) < 0)
  {
    // failed
    if (errno == EINTR)
    {
      goto read_again;
    }

    // FIXME: How to do?
    fprintf(stderr, "Receive data on connection %d failed: %s\n", fd, strerror(errno));
    return -3;
  }
  else if (n == 0)
  {
    // Connection closed by peer.
    fprintf(stdout, "Connection closed by peer.\n");
    close(fd);

    destroy_conn_object(global_conn_list[fd]);
    global_conn_list[fd] = NULL;

    net_unregister_read(fd);
    net_unregister_write(fd);
    net_unregister_except(fd);

    return 0;
  }
  else
  {
    fprintf(stdout, "Received %d bytes on connection %d.\n", n, fd);

    rbuf->payload_length += n;

#ifdef _DEBUG_
    fprintf(stdout, "[DEBUG]Connection %d: rbuf->size = %lu, rbuf->payload_length = %lu\n", fd, rbuf->size, rbuf->payload_length);
#endif

    if (rbuf->payload_length >= rbuf->size)
    {
      // Allocate more memory
      int newsize = rbuf->size * 2;
      char *newdata = utils_safe_malloc(newsize);

      if (!newdata)
      {
	// FIXME: allocate memory failed.
	fprintf(stderr, "Allocate more memory for connection %d failed\n", fd);
      }
      else
      {
	//void *memcpy(void *dest, const void *src, size_t n);
	memcpy(newdata, rbuf->data, rbuf->payload_length);

	utils_safe_free(rbuf->data);

	rbuf->data = newdata;
	rbuf->size = newsize;
      }
    }
  }

  //parse_data(fd);
  exchange_data(fd);

  return 0;
}

int net_write(int fd)
{
  conn_t *current_conn = global_conn_list[fd];

  if (!current_conn)
  {
    fprintf(stderr, "conn_t object not exists.\n");
    return -1;
  }

  buf_t *sbuf = current_conn->sbuf;

  if (!sbuf)
  {
    fprintf(stderr, "sbuf object not exists.\n");
    return -2;
  }

  ssize_t n;

write_again:
  //ssize_t write(int fd, const void *buf, size_t count);
  if ((n = write(fd, sbuf->data, sbuf->payload_length)) < 0)
  {
    if (errno == EINTR)
    {
      goto write_again;
    }
    else if (errno == EPIPE)
    {
      // Connection closed by peer.
      fprintf(stdout, "Connection closed by peer.\n");
      close(fd);

      destroy_conn_object(global_conn_list[fd]);
      global_conn_list[fd] = NULL;

      net_unregister_read(fd);
      net_unregister_write(fd);
      net_unregister_except(fd);
    }

    fprintf(stderr, "Send data on connection %d failed: %s\n", fd, strerror(errno));
    return -3;
  }
  else
  {
    fprintf(stdout, "Sent %d bytes on connection %d.\n", n, fd);

    //void *memmove(void *dest, const void *src, size_t n);
    memmove(sbuf->data, sbuf->data + n, sbuf->payload_length - n);
    sbuf->payload_length -= n;

    if (sbuf->payload_length == 0)
    {
      net_unregister_write(fd);
    }
  }

  return 0;
}

void net_register_read(int fd)
{
  FD_SET(fd, &global_read_set);

  if (global_maxfd < fd)
  {
    global_maxfd = fd;
  }
}

void net_unregister_read(int fd)
{
  FD_CLR(fd, &global_read_set);
}

void net_register_write(int fd)
{
  FD_SET(fd, &global_write_set);

  if (global_maxfd < fd)
  {
    global_maxfd = fd;
  }
}

void net_unregister_write(int fd)
{
  FD_CLR(fd, &global_write_set);
}

void net_register_except(int fd)
{
  FD_SET(fd, &global_except_set);

  if (global_maxfd < fd)
  {
    global_maxfd = fd;
  }
}

void net_unregister_except(int fd)
{
  FD_CLR(fd, &global_except_set);
}

//--------------------------------------------------------------------
// Upper level function
//--------------------------------------------------------------------
int buffered_send(int fd, const void *buf, size_t count)
{
  conn_t *current_conn = global_conn_list[fd];

  if (!current_conn)
  {
    fprintf(stderr, "conn_t object not exists.\n");
    return -1;
  }

  buf_t *sbuf = current_conn->sbuf;

  if (!sbuf)
  {
    fprintf(stderr, "sbuf object not exists.\n");
    return -2;
  }

  if (sbuf->payload_length + count > sbuf->size)
  {
    // Allocate more memory
    int newsize = sbuf->payload_length + count;
    char *newdata = utils_safe_malloc(newsize);

    if (!newdata)
    {
      // FIXME: allocate memory failed.
      fprintf(stderr, "Allocate more memory for connection %d failed\n", fd);
    }
    else
    {
      //void *memcpy(void *dest, const void *src, size_t n);
      memcpy(newdata, sbuf->data, sbuf->payload_length);

      utils_safe_free(sbuf->data);

      sbuf->data = newdata;
      sbuf->size = newsize;
    }
  }

  //void *memcpy(void *dest, const void *src, size_t n);
  memcpy(sbuf->data + sbuf->payload_length, buf, count);

  fprintf(stdout, "%s:%d:%s(): buffered send %d bytes.\n", __FILE__, __LINE__, __func__, count);

  sbuf->payload_length += count;

  if (sbuf->payload_length > 0)
  {
    net_register_write(fd);
  }

  return 0;
}

int parse_data(int fd)
{
  // TODO: Implement data parser according to protocol
  return 0;
}

int exchange_data(int fd)
{
  int i;
  char buffer[128];

  if (!global_conn_list[fd])
  {
    return -1;
  }

  memset(buffer, 0, sizeof(buffer));

  snprintf(buffer, sizeof(buffer) - 1, "[%s:%d, %lu bytes]: ", global_conn_list[fd]->ip, global_conn_list[fd]->port, global_conn_list[fd]->rbuf->payload_length);

  fprintf(stdout, "%s\n", buffer);

  for (i = 0; i < global_conn_list_count; i++)
  {
    if (i != fd)
    {
      if (global_conn_list[i])
      {
	buffered_send(i, buffer, strlen(buffer));
	buffered_send(i, global_conn_list[fd]->rbuf->data, global_conn_list[fd]->rbuf->payload_length);
      }
    }
  }

  global_conn_list[fd]->rbuf->payload_length = 0;

  return 0;
}

//--------------------------------------------------------------------
// Signal handlers
//--------------------------------------------------------------------
void sigpipe_handler(int sig)
{
  fprintf(stdout, "Caught signal %d.\n", sig);
}

void sigterm_handler(int sig)
{
  fprintf(stdout, "Caught signal %d.\n", sig);
  global_exit_flag++;
}
