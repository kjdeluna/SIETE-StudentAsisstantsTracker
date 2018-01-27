typedef struct nametag{
	char firstName[50], lastName[50];
}NAME;

typedef struct datetag{
	int month, day, year;
}DATE;

typedef struct timetag{
	int hours, minutes;
}TIME;

typedef struct timelogtag{
	TIME time;
	char timeConvention[3];
}TIMELOG;

typedef struct logtag{
	DATE datePresent;
	TIMELOG startLog, endLog;
	struct logtag *nextLog;
}LOG;

typedef struct datatag{
	NAME name;
	char studentCode[7], office[50];
	TIME hoursAllowed, hoursUsed;
}DATA;

typedef struct nodetag{
	struct nodetag *prev;
	DATA data;
	struct logtag *down;
	struct nodetag *next;
}NODE;