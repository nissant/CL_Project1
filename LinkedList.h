#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedListElement {
	int data;
	struct LinkedListElement* NextElement;
} LinkedListElement;

LinkedListElement* AppendAtStartOfListAndGetNewHead (LinkedListElement* linkedList, int newDataToAppend);
LinkedListElement* AppendAtEndOfListAndGetNewHead (LinkedListElement* linkedList, int newDataToAppend);
LinkedListElement* AppendAfterCertainElemenentAndGetNewHead (LinkedListElement* linkedList,
	                                                         int newDataToAppend, int elementBeforeNewData);
int                GetPositionOfElementInList (LinkedListElement* linkedList, int element);
LinkedListElement* DeleteCertainElementAndGetNewHead (LinkedListElement* linkedList, int indexOfElementToDelete);
void               PrintLinkedList (LinkedListElement* linkedList);
void			   FreeAllListElements(LinkedListElement* linkedList);
#endif

