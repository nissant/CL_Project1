#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LinkedList.h"

void SetDataInElement (LinkedListElement* element, int newData) {
	element->data = newData;
}

void SetNextInElement (LinkedListElement* element, LinkedListElement* nextElement) {
	element->NextElement = nextElement;
}

LinkedListElement* GetLastElementInLinkedList (LinkedListElement* linkedList) {
	LinkedListElement* endOfLinkedList = linkedList;
	if    (endOfLinkedList == NULL)              { return endOfLinkedList; }
	while (endOfLinkedList->NextElement != NULL) { endOfLinkedList = endOfLinkedList->NextElement; }
	return endOfLinkedList;
}

LinkedListElement* GetNewElementAndSetData (int newData) {
	LinkedListElement* newElementInList = (LinkedListElement*)malloc(sizeof(LinkedListElement));
	SetDataInElement(newElementInList, newData);
	return newElementInList;
}

void FreeAllListElements(LinkedListElement* linkedList) {
	LinkedListElement* currentElement = linkedList;
	LinkedListElement* previousElement = NULL;
	while (currentElement != NULL) {
		previousElement = currentElement;
		currentElement = currentElement->NextElement;
		free(previousElement);
	}
}

LinkedListElement* AppendAtStartOfListAndGetNewHead (LinkedListElement* linkedList, int newDataToAppend) {
	LinkedListElement* newStartElement = GetNewElementAndSetData(newDataToAppend);
	SetNextInElement(newStartElement, linkedList);
	return newStartElement;
}

LinkedListElement* AppendAtEndOfListAndGetNewHead (LinkedListElement* linkedList, int newDataToAppend) {
	LinkedListElement* newEndElement = GetNewElementAndSetData(newDataToAppend);
	SetNextInElement(newEndElement, NULL);

	if (linkedList == NULL) {
		return newEndElement;
	} else {
		LinkedListElement* previousEndElement = GetLastElementInLinkedList(linkedList);
		SetNextInElement(previousEndElement, newEndElement);
	}

	return linkedList;
}

LinkedListElement* AppendAfterCertainElemenentAndGetNewHead (LinkedListElement* linkedList,
	                                              int newDataToAppend, int elementBeforeNewData) {
	LinkedListElement* newElement = GetNewElementAndSetData(newDataToAppend);
	SetDataInElement(newElement, newDataToAppend);

	LinkedListElement* previousElement = linkedList;
	bool anchorElementExist            = false;
	while ((previousElement != NULL) && !anchorElementExist) {
		if (previousElement->data == elementBeforeNewData) { anchorElementExist = true; break; }
		previousElement = previousElement->NextElement;
	}

	if (anchorElementExist == false) { return NULL; }
	else {
		SetNextInElement(newElement, previousElement->NextElement);
		SetNextInElement(previousElement, newElement);
	}

	return linkedList;
}

#define COULDNT_FIND_ELEMENT -1

int GetPositionOfElementInList (LinkedListElement* linkedList, int element) {
	int elementIndex = 0;
	while (linkedList != NULL) {
		if (linkedList->data == element) { return elementIndex; }
		elementIndex++;
		linkedList = linkedList->NextElement;
	}
	return COULDNT_FIND_ELEMENT;
}

LinkedListElement* DeleteCertainElementAndGetNewHead (LinkedListElement* linkedList, int indexOfElementToDelete) {
	LinkedListElement* previousToElementToDelete = linkedList;
	LinkedListElement* theElementToDelete        = NULL;
	int currentElementIndex                      = 0;

	if ((indexOfElementToDelete == 0) && (linkedList != NULL)) {
		LinkedListElement* newFirstElementForTheList = linkedList->NextElement;
		free(linkedList);
		return newFirstElementForTheList;
	}

	while ((currentElementIndex != (indexOfElementToDelete - 1)) && (previousToElementToDelete != NULL)) {
		previousToElementToDelete = previousToElementToDelete->NextElement;
		currentElementIndex++;
	}

	bool canDelete = (previousToElementToDelete != NULL) && (previousToElementToDelete->NextElement != NULL);
	if (!canDelete) { return NULL; }
	else {
		theElementToDelete = previousToElementToDelete->NextElement;
		SetNextInElement(previousToElementToDelete, theElementToDelete->NextElement);
		free(theElementToDelete);
	}
	return linkedList;
}

void PrintLinkedList (LinkedListElement* linkedList) {
	printf("[");
	while (linkedList != NULL) {
		bool isLastElement = (linkedList->NextElement == NULL);

		if (isLastElement) { printf("%d", linkedList->data); }
		else               { printf("%d, ",   linkedList->data); }

		linkedList = linkedList->NextElement;
	}
	printf("]\n");
}

