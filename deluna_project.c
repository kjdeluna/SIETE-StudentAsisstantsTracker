#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"
#include "functions.h"
#include "logoperations.h"
#include "nodeoperations.h"

int main(){	
	int option;
	char choice, choice2;
	NODE *head, *tail, *toViewNode;
	head = (NODE *) malloc (sizeof(NODE));
	tail = (NODE *) malloc (sizeof(NODE));
	head -> prev = NULL;
	head -> next = tail;
	tail -> prev = head;
	tail -> next = NULL;
	loadContents(&head, &tail);
	do{
		dashboard(&option);
		switch(option){
			case 1: insertSorted(&head, &tail, createNewElement(&head)); break;
			case 2: if(isListEmpty(&head, &tail) == 0) addLog(&head, &tail);
					break;
			case 3: if(isListEmpty(&head, &tail) == 0){
						do{
							viewStudentsSubMenu(&choice);
							switch(tolower(choice)){
								case 'a': viewList(&head); break;
								case 'b': viewSpecificPerson(&head); break;
								case 'c': viewStudentsDone(&head, &tail); break;
								case 'd': break; 
								default: 	printf("--------------------------[ ERROR ]---------------------------\n\n");
											printf("Invalid input. Please Try Again.\n\n");
											printf("--------------------------------------------------------------\n\n");
							}
						}while(choice != 'd');
					}
					break;
			case 4: if(isListEmpty(&head, &tail) == 0){
						toViewNode = searchPerson(&head);				
						do{							
							if(toViewNode != NULL){
								viewLogsSubMenu(&choice2);
								switch(tolower(choice2)){
									case 'a': viewLog(&head, toViewNode); break;
									case 'b': viewLogDate(&head, toViewNode); break;
									case 'c': break;
									default: 	printf("--------------------------[ ERROR ]---------------------------\n\n");
												printf("Invalid input. Please Try Again.\n\n");
												printf("--------------------------------------------------------------\n\n");
												continue;
								}
							}
							else break;
						}while(choice2 != 'c'); 
					}
					break;
			case 5: if(isListEmpty(&head, &tail) == 0)
				deletePerson(&head, &tail, searchPerson(&head)); break;
			case 6: viewProgramDetails(); break;
			case 7: exitApplication(&head, &tail);break;
			default: printf("\nInvalid input. Try again.\n\n"); continue;
		}
	}while(option != 7);
	return 0;
}