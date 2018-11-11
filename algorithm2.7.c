#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 10 // 线性表储存空间的初始分配量
#define LISTINCREMENT 2 // 线性表储存空间的分配增量
// 函数结果状态代码
#define OVERFLOW -2
#define ERROR 0

typedef int ElemType;

/*线性表的动态分配顺序存储结构*/
typedef struct{
    ElemType *elem; //储存空间基址
    int length; //当前长度
    int listsize; //当前分配的储存容量（以sizeof(ElemType)为单位）
}SqList;

int InitList_Sq(SqList *L){
    // 构造一个空的线性表L
    (*L).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!(*L).elem)exit(OVERFLOW); // 储存分配失败
    (*L).length=0; // 空表长度为0
    (*L).listsize=LIST_INIT_SIZE; // 初始存储容量
    return ERROR;
}

int ListInsert_Sq(SqList *L, int i, ElemType e){
    /* 在顺序线性表L中第i个位置之前插入新元素e,
    i的合法值为1<=i<=ListLength_Sq(L)+1 */
    ElemType *newbase,*q,*p;
    if(i<1||i>(*L).length+1) // i值不合法
        return ERROR;
    if((*L).length>=(*L).listsize) // 当前存储空间已满,增加分配
        {
            newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
            if(!newbase)
            exit(OVERFLOW); // 存储分配失败
            (*L).elem=newbase; // 新基址
            (*L).listsize+=LISTINCREMENT; // 增加存储容量
        }
   q=(*L).elem+i-1; // q为插入位置
   for(p=(*L).elem+(*L).length-1;p>=q;--p) // 插入位置及之后的元素右移
        *(p+1)=*p;
        *q=e; // 插入e
        ++(*L).length; // 表增长1
   return ERROR;
}

void MergeList(SqList La, SqList Lb, SqList *Lc){
    //已知顺序线性表La和Lb的元素按值非递减排列
    //归并La和Lb得到新的顺序线性表Lc,Lc的元素也按值非递减排列
	ElemType *pa, *pa_last, *pb, *pb_last, *pc;
	pa = La.elem;pb = Lb.elem;
	(*Lc).listsize = (*Lc).length = La.length + Lb.length;// 不用InitList()创建空表Lc
	pc = (*Lc).elem = (ElemType *)malloc((*Lc).listsize*sizeof(ElemType));
	if (!(*Lc).elem) // 存储分配失败
		exit(OVERFLOW);
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last&&pb <= pb_last) 
	{ // 归并
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last) *pc++ = *pa++; // 插入La的剩余元素
	while (pb <= pb_last) *pc++ = *pb++; // 插入Lb的剩余元素
}

int main()
{
	SqList La, Lb, Lc;
	int j,i;
	int *ta,*tb,*tc; 
	InitList_Sq(&La);  //建立一个空线性表 
	for (j = 1; j <= 5; j++) 
		ListInsert_Sq(&La, j, j);   //对线性表进行顺序存储赋值 
	ta =La.elem;
	printf("La= "); 
	for (i = 1; i<= La.length; i++) // 循环打印
	{
		printf("%d",*(ta++));
		printf(" ");
	}
	printf("\n");
	InitList_Sq(&Lb); 
	for (j = 1; j <= 9; j++)
		ListInsert_Sq(&Lb, j, (2*j+1));
	tb =Lb.elem;
	printf("Lb= "); 
	for (i = 1; i<= Lb.length; i++)
	{
		printf("%d",*(tb++));
		printf(" ");
	}
	printf("\n");
	MergeList(La, Lb, &Lc);
	tc = Lc.elem;
	printf("Lc= ");
	for (i = 1;i<=Lc.length;i++)
	{
		printf("%d",*(tc++));
		printf(" ");
	}
   	return ERROR;
} 