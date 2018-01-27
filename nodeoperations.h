NODE *createNewElement(NODE **head){
	printf("\n");
	NODE *newNode = (NODE *) malloc (sizeof(NODE));
	newNode -> prev = NULL;
	if(askName(head, newNode -> data.name.firstName, newNode -> data.name.lastName) == 0){
		free(newNode);
		newNode = NULL;
	}
	else{
		if(askStudCodeForAdd(head, newNode -> data.studentCode) == 0){
			free(newNode);
			newNode = NULL;
		}
		else{
			if(askOfficeAssigned(newNode -> data.office) == 0){
				free(newNode);
				newNode = NULL;
			}
			else{
				if(askTimeAllowed(&(newNode -> data.hoursAllowed.hours), &(newNode -> data.hoursAllowed.minutes)) == 0){
					free(newNode);
					newNode = NULL;
				}	
				else{
					newNode -> data.hoursUsed.hours = 0;
					newNode -> data.hoursUsed.minutes = 0;
					newNode -> next = NULL;
					newNode -> down = NULL;
				}
			}
		}
	}
	printf("\n");
	return newNode;
}

void insertAtMiddle(NODE *newNode, NODE *before, NODE *after){ // general form of insert at middle
	newNode -> prev = before;
	newNode -> next = after;
	before -> next = newNode;
	after -> prev = newNode;
}

void insertSorted(NODE **head, NODE **tail, NODE *newNode){ // this function finds out where to insert the element; the list is sorted by their last name
	if(newNode != NULL){
		NODE *before = *head, *after = before -> next;
		while(strcmp(newNode -> data.name.lastName, after -> data.name.lastName) > 0 && after != *tail){ 
			before = before -> next;
			after = after -> next;
		}
		if(strcmp(newNode -> data.name.lastName, after -> data.name.lastName) == 0){ // catches the condition where the last names of different person are the same
			while(strcmp(newNode -> data.name.firstName, after -> data.name.firstName) > 0 && after != *tail){
				before = before -> next;
				after = after -> next;
			}
		}
		insertAtMiddle(newNode, before, after);
		printf("--------------------------[ SUCCESS ]--------------------------\n\n");
		printf("Student Assistant with Student Code %s has been added!\n", newNode -> data.studentCode);
		printf("---------------------------------------------------------------\n\n");
	}
}

void viewSpecificPerson(NODE **head){
	NODE *viewPerson = searchPerson(head);
	if(viewPerson != NULL){ // if the person exists, will print the information
		printInformation(viewPerson);
	}
}

void viewList(NODE **head){ // view all student assistants
	NODE *toView = (*head) -> next;
	while(toView -> next != NULL){ //while toView does not point to tail
		printInformation(toView);
		printf("\n");
		toView = toView -> next;
	}
}

void viewStudentsDone(NODE **head, NODE **tail){ //view students who have already reached his allowed number of hours
	int mark = 0;
	NODE *viewPerson = (*head) -> next;
	while(viewPerson -> next != NULL){
		if(viewPerson -> data.hoursAllowed.hours == viewPerson -> data.hoursUsed.hours && viewPerson -> data.hoursAllowed.minutes == viewPerson -> data.hoursUsed.minutes){
			printInformation(viewPerson);
			printf("\n");
			mark = 1; // means that there is already a person who have reached his allowed number of hours 
		}
		viewPerson = viewPerson -> next;
	}
	if(mark == 0){ // else this prompt is shown
		printf("-------------------------[ PROMPT ]---------------------------\n\n");
		printf("There are no students who reached their allowed number of hours.\n");
		printf("--------------------------------------------------------------\n\n");
	}
}

void deleteAtMiddle(NODE **head, NODE *toDelete){
	toDelete -> prev -> next = toDelete -> next;
	toDelete -> next -> prev = toDelete -> prev;
	destroyLogs(toDelete); //freeing the logs of that specific person
	free(toDelete); // freeing the element itself
}

void deleteFile(NODE **head, NODE *toDelete){
	char fileName[50];
	strcpy(fileName, toDelete -> data.studentCode);
	strcat(fileName, ".txt"); 
	remove(fileName); //deletes the log file if the element is already deleted
	deleteAtMiddle(head, toDelete);
}
void deletePerson(NODE **head, NODE **tail, NODE *found){
	char option;
	NODE *toDelete = NULL;
	if(found != NULL){
		toDelete = found;
		printf("Are you sure you want to delete the following? [Y/N]: \n"); // asks whether to delete or not
		printf("Name: %s, %s\t\tStudent Code: %s\n", toDelete -> data.name.lastName, toDelete -> data.name.firstName, toDelete -> data.studentCode);
		do{
			scanf("%c", &option);
			getchar();
			switch(toupper(option)){
				case 'Y': deleteFile(head, toDelete); 				
					printf("--------------------------[ SUCCESS ]--------------------------\n\n");
					printf("Successfully deleted the Student Assistant!\n");
					printf("-------------------------------------------------------------\n\n");
					break;
				case 'N': break;
				default: 					
					printf("---------------------------[ERROR]---------------------------\n\n");
					printf("Please try again. Enter choice:\n"); 
					printf("Press \\ to go back to Menu.\n");
					printf("-------------------------------------------------------------\n\n");
					continue;
			}
		break;
		}while(option != 'Y' || option != 'N');
	}
}

void destroyList(NODE **head, NODE **tail){ //will free all the previously mallocated elements by starting at the element next to dummy head
	NODE *toDelete = (*head) -> next, *stalker;
	while(toDelete != *tail){
		stalker = toDelete;
		toDelete = toDelete -> next;
		deleteAtMiddle(head, stalker);
	}
	free(*head); //frees the dummy head node
	free(*tail); //frees the dummy tail node
}

void exitApplication(NODE **head, NODE **tail){ //once the user exits the program, it will save the previously done changes to a file
	char fileName[50];
	FILE *fp = fopen("students.txt", "w"); // if the file exists, it will just overwrite the file, if it does not exist, it will create a file
	fprintf(fp, "%d\n", getSaveSize(head));
	NODE *toView = (*head) -> next;
	LOG *toViewLog;
	while(toView -> next != NULL){
		fprintf(fp, "%s\n", toView -> data.name.lastName);
		fprintf(fp, "%s\n", toView -> data.name.firstName);
		fprintf(fp, "%s\n", toView -> data.studentCode);
		fprintf(fp, "%s\n", toView -> data.office);
		fprintf(fp, "%d,%d\n", toView -> data.hoursAllowed.hours, toView -> data.hoursAllowed.minutes);
		fprintf(fp, "%d,%d\n", toView -> data.hoursUsed.hours, toView -> data.hoursUsed.minutes);
		strcpy(fileName, toView -> data.studentCode);
		strcat(fileName, ".txt"); // will add file extension, txt to the student code
		FILE *fptr = fopen(fileName , "w"); // will write the logs of each student assistant
		toViewLog = toView -> down;
		fprintf(fptr, "%d\n", getSaveSizeLog(&toViewLog));
		while(toViewLog!= NULL){
			fprintf(fptr, "%02d\n", toViewLog -> datePresent.month);
			fprintf(fptr, "%02d\n", toViewLog -> datePresent.day);
			fprintf(fptr, "%d\n", toViewLog -> datePresent.year);
			fprintf(fptr, "%02d:%02d %s\n", toViewLog -> startLog.time.hours, toViewLog -> startLog.time.minutes, toViewLog -> startLog.timeConvention);
			fprintf(fptr, "%02d:%02d %s\n", toViewLog -> endLog.time.hours, toViewLog -> endLog.time.minutes, toViewLog -> endLog.timeConvention);
			toViewLog = toViewLog -> nextLog;
		}
		fclose(fptr); //closes the fptr for logs
		toView = toView -> next;
	}
	fclose(fp); //closes the fp for elements
	destroyList(head, tail); // will free previously mallocated elements
}

void loadContents(NODE **head, NODE **tail){
	int size, count = 0, logSize;
	char string[100];
	char fileName[100];
	NODE *newNode, *before = *head, *after = *tail;
	LOG *newLogNode;
	FILE *fp = fopen("students.txt", "r"); // this fp will be for the reading of the elements
	if(fp != NULL){
		fscanf(fp, "%d\n", &size);
		if(size != 0){
			while(!feof(fp)){
				count = 0; // reinitializes the count of the logs loaded
				newNode = (NODE *) malloc (sizeof(NODE));
				fgets(string,100,fp);
				string[strlen(string)-1] = '\0';
				strcpy(newNode -> data.name.lastName, string);
				fgets(string,100,fp);
				string[strlen(string)-1] = '\0';
				strcpy(newNode -> data.name.firstName, string);
				fgets(string,100,fp);
				string[strlen(string)-1] = '\0';
				newNode -> down = NULL;
				strcpy(newNode -> data.studentCode, string);
				strcpy(fileName, newNode -> data.studentCode);
				strcat(fileName, ".txt");
				FILE *fptr = fopen(fileName, "r"); // this fptr will be for the reading of the logs
				fscanf(fptr, "%d\n", &logSize);
				while(count < logSize && logSize != 0){ 
					newLogNode = (LOG *) malloc (sizeof(LOG));
					fscanf(fptr, "%d\n%d\n%d\n", &(newLogNode -> datePresent.month), &(newLogNode -> datePresent.day), &(newLogNode -> datePresent.year));
					fscanf(fptr, "%d:%d ", &(newLogNode -> startLog.time.hours), &(newLogNode -> startLog.time.minutes));
					fgets(string, 100, fptr);
					string[strlen(string) - 1] = '\0';
					strcpy(newLogNode -> startLog.timeConvention, string);
					fscanf(fptr, "%d:%d ", &(newLogNode -> endLog.time.hours), &(newLogNode -> endLog.time.minutes));
					fgets(string, 100, fptr);
					string[strlen(string) - 1] = '\0';
					strcpy(newLogNode -> endLog.timeConvention, string);
					newLogNode -> nextLog = NULL;
					insertAtTailLog(newNode, &(newNode -> down), newLogNode); 
					++count;
				}
				fclose(fptr);
				fgets(string,100,fp);
				string[strlen(string)-1] = '\0';
				strcpy(newNode -> data.office, string);
				fscanf(fp, "%d,%d\n", &(newNode -> data.hoursAllowed.hours), &(newNode -> data.hoursAllowed.minutes));
				fscanf(fp, "%d,%d\n", &(newNode -> data.hoursUsed.hours), &(newNode -> data.hoursUsed.minutes));
				insertAtMiddle(newNode, before, after); // since the elements are already sorted, we can do something similar like insertAtTail. So to do this with dummy nodes, we will only move the before ptr. The after ptr is always at tail
				before = before -> next;
			}
		}
		fclose(fp);
	}
}