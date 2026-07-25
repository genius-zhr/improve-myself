#include <stdio.h>
#include <stdlib.h>
#define Table_size 100
/*比较malloc/realloc/calloc
struct listnode *newnode = (struct listnode *)malloc(5*sizeof(listnode));
//给newnode动态分配5个listnode类型且未初始化的内存
struct listnode *newnode = (struct listnode *)calloc(5，sizeof(listnode));
//给newnode动态分配5个listnode类型且初始化为0的内存，注意calloc参数形式
struct listnode *newnode = (struct listnode *)malloc(5*sizeof(listnode));
struct listnode *t = (struct listnode *)realloc(newnode,10*sizeof(listnode));
if(t!=NULL)
{
newnode=t;
}//realloc:由5个扩容至10个listnode类型且未初始化的内存，注意参数形式，
第一个参数必须是原内存指针，重新分配的用一个新指针承接，以免内存丢失
*/

//二维字符指针数组做函数参数要定义好第二维的大小
void putnum(char *num[][2]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%s  ", num[i][j]);
		}
	}
	return;
}

typedef struct listnode {
	int data;
	struct listnode *next;
} listnode;
void deleteList(listnode **node) {
	struct listnode *p = *node;

	for (int i = 0; p != NULL; i++) {
		struct listnode *q = p;
		p = p->next;
		free(q);
	}
	*node = NULL;
	return;
}
/*数组指针，函数部分
int main() {
char a[] = "person" ;//char规则与cpp相同char a='b';
*(a + 1) = 'm';
printf("%s\n", a);
char *num[3][2] = {"apple", "banana", "pink", a, "water", "pig"};
char **p[3] = {num[0], num[1], num[2]};
char ***q = p;

//*(num[1][1] + 2) = 'e'; //一级指针修改
//*(*(*(q + 1) + 1) + 2) = 'e'; //三级指针修改
*(*(*(p + 1) + 1) + 2) = 'e'; //二级指针操作
putnum(num);
return 0;
}
*/
int main() {
	//头插法建立链表
	int nums[] = {1, 2, 3, 4, 5};
	struct listnode *node = (struct listnode *)malloc(sizeof(listnode));
	node->next = NULL;
	int i = 0;
	/*while (i < 5) {
		struct listnode *newnode = (struct listnode *)malloc(sizeof(listnode));
		newnode->data = nums[i];
		newnode->next = node->next;
		node->next = newnode;
		i++;
	}
	struct listnode *p = node->next;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}*/

	//尾插法建立链表
	struct listnode *head = node;
	while (i < 5) {
		struct listnode *newnode = (struct listnode *)malloc(sizeof(listnode));
		newnode->data = nums[i];
		newnode->next = NULL;
		head->next = newnode;
		head = newnode;
		i++;
	}
	struct listnode *p = node->next;

	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	//删除链表以及free用法
	deleteList(&node);/*你的家门 = 链表头结点地址
    main 的 node：写着家门的纸条 A
    调用函数：复印一张纸条 B 给函数（形参 node），两张纸条写了完全一样的门牌号。
    你拿纸条 B 开门进屋装修（node->data），房子变了，拿纸条 A 开门也能看到装修。
    你直接把纸条 B 涂掉改成空白（node=NULL），纸条 A 纹丝不动。
    纸条 A 依旧是旧门牌号，但房子已经被拆掉 free 了，拿着旧纸条就是野指针。*/
	return 0;
}