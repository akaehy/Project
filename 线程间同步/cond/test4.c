#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define THREADS_NUM	20

struct msg
{
  struct msg *next;
  int num;
};

struct msg *head;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
  int id = (int) p;

  struct msg *mp;

  for (;;)
  {
    pthread_mutex_lock(&lock);

    while (head == NULL)
    {
      pthread_cond_wait(&has_product, &lock);

      if (head == NULL)
      {
	printf("[C%02d] not ready\n", id);
      }
    }

    mp = head;
    head = mp->next;

    pthread_mutex_unlock(&lock);

    printf("[C%02d] %d\n", id, mp->num);

    free(mp);

    sleep(rand() % 5);
  }
}

void *producer(void *p)
{
  int id = (int) p;

  struct msg *mp;

  for (;;)
  {
    mp = malloc(sizeof(struct msg));
    mp->num = rand() % 1000 + 1;

    printf("[P%02d] %d\n", id, mp->num);

    pthread_mutex_lock(&lock);

    mp->next = head;
    head = mp;

    pthread_mutex_unlock(&lock);

    //pthread_cond_signal(&has_product);
    pthread_cond_broadcast(&has_product);

    sleep(rand() % 5);
  }
}

int main(int argc, char *argv[])
{
  //pthread_t pid, cid;
  pthread_t threads[THREADS_NUM];

  srand(time(NULL));

  int i;

  for (i = 0; i < THREADS_NUM; i++)
  {
    if (i % 5 == 0)
    {
      pthread_create(&threads[i], NULL, producer, (void *) i);
    }
    else
    {
      pthread_create(&threads[i], NULL, consumer, (void *) i);
    }
  }

  for (i = 0; i < THREADS_NUM; i++)
  {
    pthread_join(threads[i], NULL);
  }

  pthread_cond_destroy(&has_product);
  pthread_mutex_destroy(&lock);

  return 0;
}
