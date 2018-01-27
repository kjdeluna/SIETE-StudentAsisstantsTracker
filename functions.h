void dashboard(int *option){
	printf("                      MAIN MENU                      \n\n");
	printf("\t[1] Add a Student Assistant\n");
	printf("\t[2] Add Log\n");
	printf("\t[3] View Students\n");
	printf("\t[4] View Logs\n");
	printf("\t[5] Delete Student\n");
	printf("\t[6] View Program Details\n");
	printf("\t[7] Exit\n");
	printf("                                                      \n");
	printf(">> ");
	scanf("%d", option);
	getchar();
}

void viewStudentsSubMenu(char *choice){
	printf("                    VIEW STUDENTS                    \n\n");
	printf("\t[a] View All Students\n");
	printf("\t[b] View Specific Student\n");
	printf("\t[c] View Students who have reached\n\t    their allowable number of hours\n");
	printf("\t[d] Exit\n");
	printf("                                                      \n");
	printf(">> ");
	scanf("%c", choice);
	getchar();
}

void viewLogsSubMenu(char *choice){
	printf("                     VIEW LOGS                      \n\n");
	printf("\t[a] View all Logs\n");
	printf("\t[b] View Log on a Date\n");
	printf("\t[c] Exit\n");
	printf("                                                      \n");
	printf(">> ");
	scanf("%c", choice);
	getchar();
}

void viewProgramDetails(){
	printf("ASA: App for Student Assistants\n\n");
	printf("\tThis application will help keep track of\n\tstudent assistants, their assignments,\n\ttheir tasks, and whether they have met \n\tthe required hours for their job or not.\n\n");
	printf("Press Any Key To Continue\n");
	getchar();
}

void chooseTimeConvention(char timeConvention[3]){ //for choosing between am or pm; In this program, 12:00 AM is the same as 12 midnight and 12:00 pm is the same as 12 nn
	char choice1;
	do{
		printf("\tEnter Time Convention:\n");
		printf("\t\t[a] AM\n");
		printf("\t\t[b] PM\n");
		printf(">> ");
		scanf("%c", &choice1);
		getchar();
		switch(tolower(choice1)){
			case 'a': strcpy(timeConvention, "AM"); break;
			case 'b': strcpy(timeConvention, "PM"); break;
			default: 
					printf("--------------------------[ ERROR ]---------------------------\n\n");
					printf("Invalid input. Please try again.\n"); 
					printf("--------------------------------------------------------------\n\n");
					continue;
		}
		break;
	}while(1);		
}

int checkStringAlNum(char string[]){ //this will check whether the student code consists of alphanumeric characters
	int i, counter = 0;
	for(i = 0; i <= strlen(string); ++i){
		if(isalnum(string[i])) counter += 1; // if a character is alphanumeric, the count will concatenate by 1
	}
	if(counter != strlen(string)) return 0; // if there is one or more non-alphanumeric characters present
	return 1; // if all are alphanumeric
}

int doesNameExist(NODE **head, char studFirstName[50], char studLastName[50]){ //checks whether the name already exists in the list
	NODE *toCheck = (*head) -> next;
	while(toCheck -> next != NULL){ // will just reiterate until it before it reaches the tail dummy node
		if(strcasecmp(toCheck -> data.name.firstName, studFirstName) == 0 && strcasecmp(toCheck -> data.name.lastName, studLastName) == 0) return 0;
		toCheck = toCheck -> next;
	}
	return 1;
}

int doesStudCodeExist(NODE **head, char studCode[7]){ //checks whether the student code already exists in the list
	NODE *toCheck = (*head) -> next;
	while(toCheck -> next != NULL){
		if(strcasecmp(toCheck -> data.studentCode, studCode) == 0){
			return 0;
		}
		toCheck = toCheck -> next;
	}
	return 1;
}
int isListEmpty(NODE **head, NODE **tail){ // will check if no element is present in the list; will produce a prompt; if no element is present, some features of the program cannot beu sed
	if((*head) -> next == *tail){
		printf("--------------------------[ ERROR ]---------------------------\n\n");
		printf("The list is currently empty! This feature cannot be used!\n");
		printf("Add a Student Assistant first.\n");
		printf("--------------------------------------------------------------\n\n");
		return 1;
	}
	return 0;
}

int askName(NODE  **head, char studFirstName[50], char studLastName[50]){
	do{
		printf("Enter First Name: ");
		fgets(studFirstName, 50, stdin);
		if(strcmp(studFirstName, "\\\n") == 0) return 0; // if the user wanted to go back to previous menu
		studFirstName[strlen(studFirstName)-1] = '\0';
		printf("Enter Last Name: ");
		fgets(studLastName, 50, stdin);
		if(strcmp(studLastName, "\\\n") == 0) return 0;
		studLastName[strlen(studLastName)-1] = '\0';
		if(doesNameExist(head, studFirstName, studLastName) == 0){
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Name already exists! \n\n");
			printf("Press \\ to go back to Menu.\n");
			printf("--------------------------------------------------------------\n\n");
			continue;
		}
		break; // if the name is unique, it will break the loop
	}while(1);
	return 1;
}

int askStudentCode(char studCode[7]){ // only for other functions except addition of new student assistant
	do{
		printf("Enter Student Code: ");
		scanf("%[^\n]s", studCode);
		getchar();
		if(strcmp(studCode, "\\") == 0) return 0; // if the user wanted to go back to previous menu
		else if(strlen(studCode) != 6 || checkStringAlNum(studCode) == 0){ // if the student code is not exactly 6 or contains non alphanumeric characters -> error
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Student Code can only contain 6 alphanumeric characters.\n\n");
			printf("Press \\ to go back to Menu.\n");
			printf("--------------------------------------------------------------\n\n");
			continue;
		}
		break; 
	}while(1);
	return 1;
}

int askStudCodeForAdd(NODE **head, char studCode[7]){ // only for addition of new student assistant
	do{
		printf("Enter Student Code: ");
		scanf("%[^\n]s", studCode);
		getchar();
		if(strcmp(studCode, "\\") == 0) return 0;
		else if(strlen(studCode) != 6 || checkStringAlNum(studCode) == 0){
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Student Code can only contain 6 alphanumeric characters.\n\n");
			printf("Press \\ to go back to Menu.\n");
			printf("--------------------------------------------------------------\n\n");
			continue;
		}
		else if(doesStudCodeExist(head, studCode) == 0){ //if the student code is not unique, error will be shown
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Student Code already exists!\n");
			printf("Press \\ to go back to Menu.\n");			
			printf("--------------------------------------------------------------\n\n");
			continue;
		}
		break; // if the student code is unique, contains exactly six alphanumeric characters
	}while(1);
	return 1;
}

int askOfficeAssigned(char office[50]){
	printf("Enter Assigned Office: ");
	fgets(office, 50, stdin);
	if(strcmp(office, "\\\n") == 0) return 0;
	office[strlen(office) - 1] = '\0';
	return 1;
}

int askTimeAllowed(int *studHoursAllowed, int *studMinutesAllowed){
	char hours[5], minutes[5];
	do{
		printf("Enter hours allowed: ");
		scanf("%s", hours);
		getchar();
		if(strcmp(hours, "\\") == 0) return 0;
		else *studHoursAllowed = atoi(hours);
		if(*studHoursAllowed < 0){
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Error: Hours cannot be negative!\n\n");
			printf("Press \\ to go back to Menu.\n");
			printf("--------------------------------------------------------------\n\n");
			continue;
		}
		printf("Enter minutes allowed: ");
		scanf("%s", minutes);
		getchar();
		if(strcmp(minutes, "\\") == 0) return 0;
		else *studMinutesAllowed = atoi(minutes);
		if(*studMinutesAllowed < 0){
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Error: Minutes cannot be negative!\n\n");
			printf("Press \\ to go back to Menu.\n");
			printf("--------------------------------------------------------------\n\n");
			continue;
		}
		break;
	}while(1);
	return 1;
}

int checkLogDiff(LOG *newerLogNode){ // this will compute whether the end log is on a later time than the start log 
	int startLogMins, endLogMins; // by converting the hours into minutes (w/ consideration of the time convention)
	if(strcmp(newerLogNode -> startLog.timeConvention, "PM") == 0 && newerLogNode -> startLog.time.hours != 12) startLogMins = 720 + ((newerLogNode -> startLog.time.hours) * 60) 
																+ newerLogNode -> startLog.time.minutes;
	else if(strcmp(newerLogNode -> startLog.timeConvention, "AM") == 0 && newerLogNode -> startLog.time.hours == 12) startLogMins = newerLogNode ->
		startLog.time.minutes; //sLM = 3
	else startLogMins = (newerLogNode -> startLog.time.hours) * 60 + (newerLogNode -> startLog.time.minutes);
	if(strcmp(newerLogNode -> endLog.timeConvention, "PM") == 0 && newerLogNode -> endLog.time.hours != 12) endLogMins = 720 + ((newerLogNode -> endLog.time.hours) * 60)
																+ newerLogNode -> endLog.time.minutes;
	else if(strcmp(newerLogNode -> endLog.timeConvention, "AM") == 0 && newerLogNode -> endLog.time.hours == 12) endLogMins = newerLogNode -> endLog.time.minutes;
	else endLogMins = (newerLogNode -> endLog.time.hours) * 60 + (newerLogNode -> endLog.time.minutes); 
	if(endLogMins <= startLogMins) return 0;
	return 1;
}
void getHoursRendered(NODE *newLogNode, LOG *newerLogNode){ // will compute for the hours already used by the student assistant
	TIME startLogDiff, endLogDiff;
	startLogDiff.minutes = newerLogNode -> startLog.time.minutes;
	endLogDiff.minutes = newerLogNode -> endLog.time.minutes;
	if(strcmp(newerLogNode -> startLog.timeConvention, "PM") == 0 && newerLogNode -> startLog.time.hours != 12) startLogDiff.hours = 12 + newerLogNode -> startLog.time.hours;
	else if(strcmp(newerLogNode -> startLog.timeConvention, "AM") == 0 && newerLogNode -> startLog.time.hours == 12) startLogDiff.hours = 0; 
	else startLogDiff.hours = newerLogNode -> startLog.time.hours;  //8
	if(strcmp(newerLogNode -> endLog.timeConvention, "PM") == 0 && newerLogNode -> endLog.time.hours != 12) endLogDiff.hours = 12 + newerLogNode -> endLog.time.hours;
	else if(strcmp(newerLogNode -> endLog.timeConvention, "AM") == 0 && newerLogNode -> endLog.time.hours == 12) endLogDiff.hours = 0;
	else endLogDiff.hours = newerLogNode -> endLog.time.hours; 
	if(endLogDiff.minutes < startLogDiff.minutes){
		endLogDiff.hours -= 1;
		endLogDiff.minutes += 60; 
	}
	newLogNode -> data.hoursUsed.hours += (endLogDiff.hours - startLogDiff.hours); // will just add the computed time to the previous rendered time
	newLogNode -> data.hoursUsed.minutes += (endLogDiff.minutes - startLogDiff.minutes);
	if(newLogNode -> data.hoursUsed.minutes >= 60){
		newLogNode -> data.hoursUsed.hours +=  (newLogNode -> data.hoursUsed.minutes / 60);
		newLogNode -> data.hoursUsed.minutes = newLogNode -> data.hoursUsed.minutes % 60;
	}
}

LOG *askTimeLog(NODE *newLogNode, LOG *newerLogNode){ // asks time-in and time-out of the student assistants
	int prevHoursUsed = newLogNode -> data.hoursUsed.hours,
	prevMinutesUsed = newLogNode -> data.hoursUsed.minutes;
	printf("Enter Time-in: ");
	scanf("%d:%d", &(newerLogNode -> startLog.time.hours), &(newerLogNode -> startLog.time.minutes));
	getchar();
	chooseTimeConvention(newerLogNode -> startLog.timeConvention);
	printf("Enter Time-out: ");
	scanf("%d:%d", &(newerLogNode -> endLog.time.hours), &(newerLogNode -> endLog.time.minutes));
	getchar();
	chooseTimeConvention(newerLogNode -> endLog.timeConvention);
	if(checkLogDiff(newerLogNode) == 0){
		printf("--------------------------[ ERROR ]---------------------------\n\n");
		printf("Unable to add log. Logout should be on a later time than the Login!\n\n");
		printf("--------------------------------------------------------------\n\n");
		free(newerLogNode); // if error, will free the previous memory allocated
		newerLogNode = NULL;
	}
	else{
		getHoursRendered(newLogNode, newerLogNode);
		if((newLogNode -> data.hoursUsed.hours) * 60 + newLogNode -> data.hoursUsed.minutes > 
			newLogNode -> data.hoursAllowed.hours * 60 + newLogNode -> data.hoursAllowed.minutes){
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Unable to add log. Exceeded allowed number of hours!\n\n");
			printf("--------------------------------------------------------------\n\n");
			free(newerLogNode);
			newerLogNode = NULL;
			newLogNode -> data.hoursUsed.hours = prevHoursUsed;
			newLogNode -> data.hoursUsed.minutes = prevMinutesUsed;
		}
	}
	return newerLogNode;
}	

void datePresentInput(DATE *date){ // asks the date of the log of the student assistants
	do{
		printf("Enter month: ");
		scanf("%d", &(date->month));
		getchar();
		if(date -> month < 0 || date -> month > 12){ // no negative months and months > 12
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Invalid input for month!\n\n");
			printf("--------------------------------------------------------------\n\n");
			continue;
		}
		break;
	}while(1);
	do{
		printf("Enter day: ");
		scanf("%d", &(date->day));
		getchar();
		if(date -> day < 0 || date -> day > 31){ // no negative days and days > 31
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Invalid input for day!\n\n");
			printf("--------------------------------------------------------------\n\n");
			continue;			
		}
		break;
	}while(1);
	do{
		printf("Enter year: ");
		scanf("%d", &(date->year));
		getchar();
		if(date -> year < 0){
			printf("--------------------------[ ERROR ]---------------------------\n\n");
			printf("Invalid input for year!\n\n");
			printf("--------------------------------------------------------------\n\n");
			continue;
		}
		break; 
	}while(1);
}

NODE *searchPerson(NODE **head){ // will search for the SA with the input student code
	NODE *toSearch = *head;
	char toSearchStudCode[7];
	if(askStudentCode(toSearchStudCode) == 1){ //if the user wanted to proceed and does not want to go back to prev menu
		while(toSearch != NULL){
			if(strcasecmp(toSearch -> data.studentCode, toSearchStudCode) == 0) 
				return toSearch;			
				toSearch = toSearch -> next;
		}
		printf("--------------------------[ ERROR ]---------------------------\n\n");
		printf("Student Code does not exist.\n\n");
		printf("--------------------------------------------------------------\n\n");
	}
	else toSearch = NULL; // if the user wants to go back, the toSearch pointer will be null; NULL == two cases: the user wants to go back to prev menu or no person with student code is found
	return toSearch;
}

void printInformation(NODE *found){ // will simply print the information
		printf("Name: %s, %s\n", found->data.name.lastName, found->data.name.firstName);
		printf("Student Code: %s\n", found -> data.studentCode);
		printf("Office of Assignment: %s\n", found -> data.office);
		printf("Allowed number of hours: %d hours and %d minutes\n", found -> data.hoursAllowed.hours, found -> data.hoursAllowed.minutes);
		printf("Time Rendered: %d hours and %d minutes\n", found -> data.hoursUsed.hours, found -> data.hoursUsed.minutes);
}

int getSaveSize(NODE **head){ // finds how many student assistants are present 
	int count = 0;
	NODE *toView = (*head) -> next;
	while(toView -> next != NULL){
		count += 1;
		toView = toView -> next;
	}
	return count;
}

int getSaveSizeLog(LOG **toViewLog){ // finds how many logs are done by a student assistant
	int count = 0;
	LOG *toViewSquared = *toViewLog;
	while(toViewSquared != NULL){
		count += 1;
		toViewSquared = toViewSquared -> nextLog;
	}
	return count;
}
