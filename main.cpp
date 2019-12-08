#include <stdio.h>
#include "DynamicArray.hpp"

struct slistnode
{
	int value;
	struct slistnode* next;
};

struct slist{
	size_t size_;
	struct slistnode* head;
	struct slistnode* tail;
};

struct slist* createSList() {
	struct slist* list = (struct slist*)malloc(sizeof(struct slist));
	if (list != NULL) {
		list->size_ = 0;
		list->head = NULL;
		list->tail = NULL;
	}
	return list;
};

struct slist* SListInsertTail(struct slist* list, int value)
{
	if( list == NULL )
		return list;
	struct slistnode* node = (struct slistnode*)malloc(sizeof(struct slistnode));
	if(node == NULL)
		return NULL;
	node->value = value;
	node->next = NULL;
	if( list->size_ == 0 ) {
		list->tail = list->head = node;
	} else {
		list->tail->next = node;
		list->tail = node;
	}
	list->size_++;
	return list;
};

//归并排序 array
void merge_sort( int arr1[], size_t len1, int arr2[], size_t len2, int arr3[], size_t len3 ) {
	int i = 0, j = 0, k = 0;
	while ( i < len1 && j < len2 && k < len3 ) {
		if ( arr1[i] <= arr2[j] ) {
			arr3[k++] = arr1[i++];
		} else {
			arr3[k++] = arr2[j++];
		}
	}
	while ( i < len1 && k < len3 ) {
		arr3[k++] = arr1[i++];
	}
	while ( j < len2 && k < len3 ) {
		arr3[k++] = arr2[j++];
	}
}

//归并排序 list
struct slist* merge_sort( struct slist* l1, struct slist* l2 ) {
	if( l1 == NULL && l2 == NULL ) {
		return NULL;
	}
	struct slist* l3 = createSList();
	if (l3 == NULL) {
		return NULL;
	}
	if (l1 == NULL ) {
		slistnode* pNode = l2->head;
		while(pNode) {
			SListInsertTail(l3, pNode->value);
			pNode = pNode->next;
		}
	} else if(l2 == NULL) {
		slistnode* pNode = l1->head;
		while(pNode) {
			SListInsertTail(l3, pNode->value);
			pNode = pNode->next;
		}
	} else {
		slistnode* pNode1 = l1->head;
		slistnode* pNode2 = l2->head;
		while ( pNode1 != NULL && pNode2 != NULL) {
			if( pNode1->value <= pNode2->value ) {
				SListInsertTail(l3, pNode1->value);
				pNode1 = pNode1->next;
			} else {
				SListInsertTail(l3, pNode2->value);
				pNode2 = pNode2->next;
			}
		}

		while( pNode1 != NULL ) {
			SListInsertTail(l3, pNode1->value);
			pNode1 = pNode1->next;
		}
		while( pNode2 != NULL ) {
			SListInsertTail(l3, pNode2->value);
			pNode2 = pNode2->next;
		}
	}
	return l3;
}

//单链表反转
struct slist* SListReverse(struct slist* list) {
	if ( list == NULL )
		return list;
	struct slistnode* pCur = list->head;
	struct slistnode* pPrev = NULL;
	struct slistnode* pNext = NULL;

	while(pCur != NULL) {
		pNext = pCur->next;
		pCur->next = pPrev;
		pPrev = pCur;
		pCur = pNext;
	}

	list->head = pPrev;
	return list;
}

//求链表的中间结点 - 快慢指针方法
struct slistnode* sListGetMid(struct slist* list) {
	if ( list == NULL )
		return NULL;
	struct slistnode* pFast = list->head;
	struct slistnode* pSlow = list->head;
	while( pFast && pFast->next && pFast->next->next ) {
		pFast = pFast->next->next;
		pSlow = pSlow->next;
	}
	return pSlow;
}

int main()
{
	DynamicArray<int> da;
	for ( int i = 0; i < 100; i++ ) {
		int k = i+1;
		da.push_back(k);
	}
	for ( int i = 0; i < 100; ++i ) {
		printf("%d ", da[i]);
	}
	printf("\n");

	int arr1[] = {1,2,4,5,7,8,10};
	int arr2[] = {0,3,6,9,11,12,15};
	int arr3[20] = {0};
	merge_sort(arr1, 7, arr2, 7, arr3, 20);
	for ( int i = 0; i < 14; ++i ) {
		printf("%d ", arr3[i]);
	}
	printf("\n");

	struct slistnode * pNode;
	struct slist* l1 = createSList();
	struct slist* l2 = createSList();
	if( !l1 || !l2 ) {
		printf("createSList failed\n");
		return -1;
	}

	for ( int i = 0; i < 100000; ++i )
	{
		SListInsertTail(l1, i+1);
		SListInsertTail(l2, i+1);
	}

	struct slist* l3 = merge_sort(l1, l2);
	if( !l3 ) {
		printf("merge_sort failed\n");
		return -1;
	}

	pNode = l3->head;
	while( pNode != NULL ) {
		printf("%d ", pNode->value);
		pNode = pNode->next;
	}
	printf("\n");

	SListReverse(l1);
	pNode = l1->head;
	while( pNode != NULL ) {
		printf("%d ", pNode->value);
		pNode = pNode->next;
	}
	printf("\n");
	
	struct slistnode* mid = sListGetMid(l2);
	if( mid ) {
		printf("%d\n", mid->value);
	}
	
	return 0;
}
