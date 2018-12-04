/*	Copyright 2018 heiyedeshengyin All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct LNode	//结点
{
	float coef; //系数
	int expn;   //指数
	struct LNode *next;	//下一个结点的指针
}*LinkList;	//LNode指针的别名

typedef LinkList polynomial;	//多项式
//----------------------------------------------------------------------------
void CreatList(LinkList &p, float _coef, int _expn);
void addAtTail(LinkList &p, float _coef, int _expn);
void show(polynomial &p);
void CreatPolyn(polynomial &p, int m);
bool isZero(polynomial &p);
void addPolyn(polynomial &pa, polynomial &pb);
//----------------------------------------------------------------------------
/*
	创建一个带头结点的链表
	LinkList &p:被创建的链表的地址
	float _coef:头结点的系数
	int _expn:头结点的指数

	@Return void
*/
void CreatList(LinkList &p, float _coef, int _expn)
{
	p = (LinkList)malloc(sizeof(LNode));	//为链表p分配一个结点的内存
	p->next = NULL;	//头结点的下一个节点指针赋值为NULL
	p->coef = _coef;	//头结点的系数赋值为_coef
	p->expn = _expn;	//头结点的指数赋值为_expn
}
//----------------------------------------------------------------------------
/*
	在链表末尾创建一个节点
	LinkList &p:被创建的链表的地址
	float _coef:尾结点的系数
	int _expn:尾结点的指数

	@Return void
*/
void addAtTail(LinkList &p, float _coef, int _expn)
{
	if (p)
	{
		/*
			链表p不为NULL的情况
			创建一个新结点并为此分配内存
			这个新结点中的系数和指数分别赋值为_coef和_expn
			把这个新节点放到链表p的末尾
		*/
		LinkList cur;	//新的结点cur
		cur = (LinkList)malloc(sizeof(LNode));
		cur->next = NULL;
		cur->coef = _coef;
		cur->expn = _expn;
		LinkList temp;	//用来指向链表p最后一项的指针temp
		temp = p;		//首先指针temp指向链表p的头结点
		while (temp->next)	//若下一个结点不为NULL,指针temp就指向下一个结点,直到下一个结点为NULL
			temp = temp->next;
		temp->next = cur;	//此时指针temp指向链表的尾节点,把结点cur放到后面作为新的尾结点
	}
	else
	{
		/*
			链表p为NULL的情况
			给链表p分配一个结点的内存,这个结点就是链表p的头结点
			这个头结点中的系数和指数分别赋值为_coef和_expn
		*/
		p = (LinkList)malloc(sizeof(LNode));
		p->next = NULL;
		p->coef = _coef;
		p->expn = _expn;
	}
}
//----------------------------------------------------------------------------
/*
	显示多项式,把多项式打印出来
	polynomial &p:被显示的多项式的地址

	@Return void
*/
void show(polynomial &p)
{
	if (p)
	{
		polynomial temp;
		temp = p;
		int flag = 0;	//flag标签,如果前几项系数为零,那么flag为1,将不打印系数为零的项,直到遇到系数不为零的项
		if (temp->coef != 0)	//常数项不为零的打印情况
		{
			printf("%.3f", temp->coef);
			flag = 0;
		}
		else	//常数项为零的情况,此时flag置为1
			flag = 1;

		while (temp->next)	//非常数项的打印情况
		{
			temp = temp->next;
			if (temp->coef > 0 && flag == 0)	//如果系数为正且flag为0的情况
				if (temp->expn == 1)
					printf(" + %.3fx", temp->coef);
				else
					printf(" + %.3fx^%d", temp->coef, temp->expn);
			if (temp->coef < 0 && flag == 0)	//如果系数为负且flag为0的情况
				if (temp->expn == 1)
					printf(" - %.3fx", -temp->coef);
				else
					printf(" - %.3fx^%d", -temp->coef, temp->expn);
			if (temp->coef != 0 && flag == 1)	//如果系数不为零且flag为1的情况,此时之前的项都未打印
				if (temp->expn == 1)
				{
					printf("%.3fx^%d", temp->coef, temp->expn);
					flag = 0;
				}
				else
				{
					printf("%.3fx", temp->coef);
					flag = 0;
				}
		}

		if (flag == 1)	//如果所有系数和常数项都为零,则只打印一个0
			printf("0");
		printf("\n");
	}
	else
		printf("0\n");
}
//----------------------------------------------------------------------------
/*
	判断多项式是否为零
	若为零或输入的链表为NULL,则返回true
	若不为零,则返回false
	polynomial &p:被判断的多项式的地址

	@Return bool
*/
bool isZero(polynomial &p)
{
	if (p)
	{
		polynomial temp;
		temp = p;
		int flag = 1;
		if (temp->coef != 0)
			flag = 0;

		while (temp->next)
		{
			temp = temp->next;
			if (temp->coef != 0)
				flag = 0;
		}

		if (flag == 1)
			return true;
		else
			return false;
	}
	else
		return true;
}
//----------------------------------------------------------------------------
/*
	创建一个多项式
	polynomial &p:被创建的多项式的地址
	int m:多项式的项数

	@Return void
*/
void CreatPolyn(polynomial &p, int m)
{
	p = NULL;	//这一行删掉程序立马崩溃,不信你试试
	for (int i = 0; i < m; i++)
	{
		float _coef;
		if (i == 0)
			printf("请输入常数项的值(共%d项):", m);
		else
			printf("请输入指数为%d的项的系数(共%d项):", i, m);
		scanf("%f", &_coef);
		addAtTail(p, _coef, i);
	}
	printf("\n");
}
//----------------------------------------------------------------------------
/*
	把两个多项式相加,pa = pa + pb
	polynomial &pa:被加的多项式,它的值会改变
	polynomial &pb:加上的多项式,它的值不会改变

	@Return void
*/
void addPolyn(polynomial &pa, polynomial &pb)
{
	if (!isZero(pa) && !isZero(pb))
	{
		/*
			多项式pa和多项式pb都不为零且都不为NULL的情况
		*/
		polynomial tempa;	//指向多项式pa各个结点的指针tempa
		polynomial tempb;	//指向多项式pb各个结点的指针tempb
		tempa = pa;	//指针tempa首先指向多项式pa的头结点
		tempb = pb;	//指针tempb首先指向多项式pb的头结点
		tempa->coef += tempb->coef;	//多项式pa常数项 = 多项式pa常数项 + 多项式pb常数项

		while (tempa->next&&tempb->next)	//指针tempa和tempb都指向下一个结点,直到其中一个指针的下一个结点为NULL
		{
			tempa = tempa->next;
			tempb = tempb->next;
			tempa->coef += tempb->coef;	//多项式pa某项系数 = 多项式pa某项系数 + 多项式pb某项系数
		}
		while (!tempa->next&&tempb->next)	//若多项式pa的项数小于pb的项数,就把pb多出来的项赋值给pa
		{
			tempb = tempb->next;
			addAtTail(tempa, tempb->coef, tempb->expn);
			tempa = tempa->next;
		}
	}
	if (isZero(pa) && !isZero(pb))
		/*
			多项式pa为零或为NULL的情况,这时直接将pb的头结点赋值给pa
		*/
		pa = pb;
}
//----------------------------------------------------------------------------
int main()
{
	LinkList p1;
	int n1;
	printf("请输入多项式p1的项数:");
	scanf("%d", &n1);
	printf("\n现在正在输入多项式p1\n");
	CreatPolyn(p1, n1);
	printf("p1 = ");
	show(p1);
	printf("\n");

	LinkList p2;
	int n2;
	printf("请输入多项式p2的项数:");
	scanf("%d", &n2);
	printf("\n现在正在输入多项式p2\n");
	CreatPolyn(p2, n2);
	printf("p2 = ");
	show(p2);
	printf("\n");

	addPolyn(p1, p2);
	printf("p1 + p2 = ");
	show(p1);

	return 0;
}
