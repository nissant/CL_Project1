
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "LinkedList.h"

#define ADD_AT_END_COMMAND        1
#define ADD_AT_START_COMMAND      2
#define ADD_AFTER_ELEMENT_COMMAND 3
#define INDEX_COMMAND             4
#define DELETE_COMMAND            5
#define PRINT_COMMAND             6
#define EXIT_COMMAND              7

#define COMMAND_LINE_LENGTH 100

#define NOT_A_VALID_COMMAND 0

int DoesCommandHaveArguments(int cmdFromUserSymbol) {
	bool doesntHaveArguments = (cmdFromUserSymbol == PRINT_COMMAND) || (cmdFromUserSymbol == EXIT_COMMAND);
	return !doesntHaveArguments;
}

int DoesCommandHaveTwoArguments(int cmdFromUserSymbol) {
	return (cmdFromUserSymbol == ADD_AFTER_ELEMENT_COMMAND);
}

void ExitProgram(LinkedListElement* linkedList) {
	FreeAllListElements(linkedList);
	exit(0);
}

void ExitInFailure(LinkedListElement* linkedList) {
	printf("Couldn't find element!");
	FreeAllListElements(linkedList);
	exit(-1);
}

LinkedListElement* ExecuteCommand(LinkedListElement* curLinkedList, int commandSymbolFromUser,
	                              int commandFirstArgument, int commandSecondArgument) {
	LinkedListElement* newLinkedList = NULL;
	bool isOneElementOnly = (curLinkedList != NULL) && (curLinkedList->NextElement == NULL);
	switch (commandSymbolFromUser) {
		case ADD_AT_END_COMMAND:
			return AppendAtEndOfListAndGetNewHead(curLinkedList, commandFirstArgument);      break;
		case ADD_AT_START_COMMAND:
			 return AppendAtStartOfListAndGetNewHead(curLinkedList, commandFirstArgument);   break;
		case ADD_AFTER_ELEMENT_COMMAND:
			newLinkedList = AppendAfterCertainElemenentAndGetNewHead
			               (curLinkedList, commandFirstArgument, commandSecondArgument);
			if (newLinkedList == NULL) { ExitInFailure(curLinkedList); }
			return newLinkedList;
			                                                                                 break;
		case INDEX_COMMAND:
			printf("%d\n", GetPositionOfElementInList(curLinkedList, commandFirstArgument)); break;
		case DELETE_COMMAND:
			newLinkedList = DeleteCertainElementAndGetNewHead(curLinkedList, commandFirstArgument);
			if (!isOneElementOnly && (newLinkedList == NULL)) { ExitInFailure(curLinkedList); }
			return newLinkedList;
			                                                                                 break;
		case PRINT_COMMAND: PrintLinkedList(curLinkedList);                                  break;
		case EXIT_COMMAND : ExitProgram(curLinkedList);                                      break;
	}
	return curLinkedList;
}

int TranslateCommandLine(char* commandLineFromUser) {
	char firstCmdChar, fourthCmdCharAfterAdd;
	firstCmdChar = tolower(*commandLineFromUser);
	switch (firstCmdChar) {
	case 'i': return INDEX_COMMAND;  break;
	case 'd': return DELETE_COMMAND; break;
	case 'p': return PRINT_COMMAND;  break;
	case 'e': return EXIT_COMMAND;   break;
	}
	fourthCmdCharAfterAdd = tolower(*(commandLineFromUser + 4));
	switch (fourthCmdCharAfterAdd) {
	case 'e': return ADD_AT_END_COMMAND;        break;
	case 's': return ADD_AT_START_COMMAND;      break;
	case 'a': return ADD_AFTER_ELEMENT_COMMAND; break;
	}
	return NOT_A_VALID_COMMAND;
}

int main() {
	LinkedListElement* linkedListHead = NULL;

	while (true) {
		char commandLineFromUser[COMMAND_LINE_LENGTH];
		int commandFirstArgument  = 0;
		int commandSecondArgument = 0;
		scanf("%s", commandLineFromUser);
		int commandSymbolFromUser = TranslateCommandLine(commandLineFromUser);
		
		if (DoesCommandHaveTwoArguments(commandSymbolFromUser)) {
			scanf(" %d %d", &commandFirstArgument, &commandSecondArgument);
		} else if (DoesCommandHaveArguments(commandSymbolFromUser)) {
			
			scanf(" %d", &commandFirstArgument);
		}

		linkedListHead = ExecuteCommand(linkedListHead, commandSymbolFromUser, commandFirstArgument,
			                                                                   commandSecondArgument);
	}
	return 0;
}
