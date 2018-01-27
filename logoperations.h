LOG *createNewLog(LOG *newerLogNode, NODE *newLogNode){
	datePresentInput(&(newerLogNode -> datePresent)); // will ask for date of the log
	newerLogNode = askTimeLog(newLogNode, newerLogNode); // will ask for the time of the log (whether the log will exceed to his allowed hours or the end log is later than the start log are already checked)
	return newerLogNode;
}

void insertAtHeadLog(LOG **down, LOG *newerLogNode){ // will only be used by the insertAtTailLog function
	if(*down != NULL) newerLogNode -> nextLog = *down;
	*down = newerLogNode;
}

void insertAtTailLog(NODE *newLogNode, LOG **down, LOG *newerLogNode){
	LOG *tail = *down;
	if(*down == NULL) insertAtHeadLog(down, newerLogNode); // if the log list is still empty
	else{
		while(tail -> nextLog != NULL){ // else will insert at tail
			tail = tail -> nextLog;
		}
		tail -> nextLog = newerLogNode;
	}
}

void addLog(NODE **head, NODE **tail){
	LOG *ptr;
	NODE *newLogNode = searchPerson(head); // first, will search for the element where the log will be placed to
	if(newLogNode != NULL){
		if(newLogNode -> data.hoursUsed.hours == newLogNode -> data.hoursAllowed.hours
			&& newLogNode -> data.hoursUsed.minutes == newLogNode -> data.hoursAllowed.minutes){
			printf("-------------------------[ PROMPT ]---------------------------\n\n"); // catches the condition where the hours rendered have already maxed out the hours allowed
			printf("Student Code [%s] has already met the allowed number of hours to be rendered.\n", newLogNode -> data.studentCode);
			printf("--------------------------------------------------------------\n\n");
		}
		else{
			LOG *newerLogNode = (LOG *) malloc (sizeof(LOG)); // if there is still time to be rendered, will malloc log 
			newerLogNode -> nextLog = NULL;
			ptr = createNewLog(newerLogNode, newLogNode); 
			if(ptr != NULL){ 
				insertAtTailLog(newLogNode, &(newLogNode -> down), ptr);
				printf("--------------------------[ SUCCESS ]--------------------------\n\n");
				printf("Successfully added new log!\n");
				printf("---------------------------------------------------------------\n\n");
			}
		}
	}
}


void viewLog(NODE **head, NODE *toViewNode){
	if(toViewNode != NULL){
		LOG *toViewLog = toViewNode -> down;
		if(toViewLog == NULL){ // if there is no log present
			printf("-------------------------[ PROMPT ]---------------------------\n\n");
			printf("%s %s [%s] has not made a log yet.\n", toViewNode -> data.name.firstName, toViewNode -> data.name.lastName, toViewNode -> data.studentCode);
			printf("--------------------------------------------------------------\n\n");
		}
		else{
			printf("Student Code: %s Logs:\n", toViewNode -> data.studentCode);
			printf("Date Present\t\tTime\n");
		}
		while(toViewLog != NULL){ // will just iterate until it became null
			printf("%02d/%02d/%d\t", toViewLog -> datePresent.month, toViewLog -> datePresent.day, toViewLog -> datePresent.year);
			printf("%02d:%02d %s", toViewLog -> startLog.time.hours, toViewLog -> startLog.time.minutes, toViewLog -> startLog.timeConvention);
			printf(" - %02d:%02d %s\n", toViewLog -> endLog.time.hours, toViewLog -> endLog.time.minutes, toViewLog -> endLog.timeConvention);
			toViewLog = toViewLog -> nextLog;
		}
		printf("\n");
	}
}

void viewLogDate(NODE **head, NODE *toViewNode){
	int month, day, year, count = 0;
	LOG *toViewLog = toViewNode -> down;
	if(toViewLog == NULL){
		printf("-------------------------[ PROMPT ]---------------------------\n\n");
		printf("%s's log is still empty! Nothing to view.\n", toViewNode -> data.studentCode);
		printf("--------------------------------------------------------------\n\n");
	}
	else{
		printf("Enter month of the log: ");
		scanf("%d", &month);
		getchar();
		printf("Enter day of the log: ");
		scanf("%d", &day);
		getchar();
		printf("Enter year of the log: ");
		scanf("%d", &year);
		getchar();
		while(toViewLog != NULL){
			if(toViewLog -> datePresent.month == month && toViewLog -> datePresent.day == day && toViewLog -> datePresent.year == year){
				if(count == 0) printf("Date Present\t\tTime\n");
				printf("%02d/%02d/%d\t", month, day, year);
				printf("%02d:%02d %s", toViewLog -> startLog.time.hours, toViewLog -> startLog.time.minutes, toViewLog -> startLog.timeConvention);
				printf(" - %02d:%02d %s\n", toViewLog -> endLog.time.hours, toViewLog -> endLog.time.minutes, toViewLog -> endLog.timeConvention);
				++count; // will just add 1 to count 
			}
			toViewLog = toViewLog -> nextLog;
		}
		if(count == 0){ // if no logs were found with the date input of the user
			printf("-------------------------[ PROMPT ]---------------------------\n\n");
			printf("No log was done on that date! [%02d/%02d/%d]\n", month, day, year);
			printf("--------------------------------------------------------------\n\n");
		}
	}
}

 void destroyLogs(NODE *toDelete){ 
	LOG *toDeleteLog = toDelete -> down;
	while(toDeleteLog != NULL){
		free(toDeleteLog); // will free the logs
		toDeleteLog = toDeleteLog -> nextLog;
	}
}

