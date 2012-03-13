/**********************************************************************
 *二叉树
 *先定义类型写出大体框架
 *在定义其中的函数
 *能完成创建二叉树，插入，删除，打印
 *以根为中心 是前序：根 左 右
 *             中序：左 根 右
 *             后续: 左 右 根
 * ********************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct tree *tree_p;
typedef struct tree{
	int item;
	tree_p right, left;

}V_NODE;

int menu(void)
{
	int choice;

	puts("Please make a choice:");
	puts("1.print\t2.add\t3.delete\t4.depth\t9.quit:");
	scanf("%d", &choice);

	return choice;
}

tree_p create_tree(int *pre, int *mid, int n)
{
	if(n <= 0)	//判断并且条件返回
	{
		return NULL;
	}
	V_NODE *r = malloc(sizeof(V_NODE));
	if(r == NULL)
	{
		perror("malloc fail");
		exit(1);
	}
	r->item = pre[0];

	
	int k = 0;
	for(k = 0; pre[0] != mid[k]; k++);//移动的是中序，找到根节点在中序的下标


	r->left = create_tree(pre+1, mid, k);//递归的方式 3次
	r->right = create_tree(pre+k+1, mid+k+1, n-k-1);

	return r;//返回完成链接
	

}

void pre_post(V_NODE *r)//前序打印
{
	if(r == NULL)
	{
		return;
	}
	printf("%-5d", r->item);//先根 再左 在右
	pre_post(r->left);//调用它自己 打印中序后序时调换这三句话的顺序,名字也对应改变
	pre_post(r->right);
}
void mid_post(V_NODE *r)
{
	if(r == NULL)
	{
		return;
	}
	mid_post(r->left);
	printf("%-5d", r->item);
	mid_post(r->right);
}

void layer_post(V_NODE *r)
{
	if(r->left != NULL)
	{
		printf("%-5d", r->left->item);
	}
	if(r->right != NULL)
	{
		printf("%-5d", r->right->item);
	}
	if(r->left != NULL)
	{
		layer_post(r->left);
	}
	if(r->right != NULL)
	{
		layer_post(r->right);
	}
}

void layer_p(V_NODE *r)
{
	if(r == NULL)
	{
		return;
	}
	printf("%-5d", r->item);
	layer_post(r);
}
void print_tree(V_NODE *r)
{

	pre_post(r);//前序打印
	printf("\n");
	mid_post(r);
	printf("\n");
	//rear_post(r);
	//printf("\n");
	layer_p(r);//分层打印
	printf("\n");
}

int get_depth(V_NODE *r)
{
	if(r == NULL)
	{
		return 0; 
	} 
	int dep = 1;
	int dl = 0;
	int dr = 0;

	dl = get_depth(r->left);
	dr = get_depth(r->right);
	dep +=(dl > dr ? dl : dr);

	return dep;
}

V_NODE *insert(V_NODE *r, int number)
{
	if(r == NULL)
	{
		r = malloc(sizeof(V_NODE));
		if(r == NULL)
		{
			perror("malloc fail");
			exit(1);
		}
		r->item = number;
		r->left = NULL;
		r->right = NULL;
		return r;
	}
	if(number > r->item)
		r->right = insert(r->right, number);
	else if(number < r->item)
		r->left = insert(r->left, number);
	return r;

}
V_NODE *insert_one_node(V_NODE *r)
{
	int number = 0;
	puts("Input a number to add:");
	scanf("%d", &number);

	r = insert(r, number);

	return r;
}

	
V_NODE *delete(V_NODE *r, int number)
{
	
	V_NODE *p;

	
	if(r == NULL)
	{
		return NULL;
	}

	if(number < r->item)
	{
		r->left = delete(r->left, number);
	}
	else if(number > r->item)
	{
		r->right = delete(r->right, number);
	}
	else//删除操作
	{
		if((r->left == NULL) && (r->right == NULL))//如果是叶子结点
		{
			free(r);
			r = NULL;
		}
		else if(r->left != NULL)//不是叶子结点，有左结点，先找到左边最大的，覆盖再递归调用
		{
			for(p = r->left; p->right != NULL; p = p->right);
			r->item = p->item;	
			r->left = delete(r->left, p->item);
		}
		else if(r->right != NULL)//不是叶子结点，先覆盖再递归调用
		{
			for(p = r->right; p->left != NULL; p = p->left);
			r->item = p->item;	
			r->right = delete(r->right, p->item);
		}
	}
	return r;

}

V_NODE *del_one_node(V_NODE *r)
{
	int number = 0;
	puts("Input anumber to delete:");
	scanf("%d", &number);

	r = delete(r, number);
	
	return r;
}
int main(int argc, char *argv[])
{
	V_NODE *root = NULL;

	int pre[] = {400,200,100,300,500,600};
	int mid[] = {100,200,300,400,500,600};
	root = create_tree(pre, mid, 6);


	while(1)
	{
		switch(menu())
		{
			case 1 : print_tree(root); break;
			case 2 : root = insert_one_node(root); break;
			case 3 : root = del_one_node(root); break;
			case 4 : printf("depth:%d\n", get_depth(root)); break;
			case 9 : return 0;
			default : break;
		}

	}

	return 0;
}
