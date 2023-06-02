#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

char *logLevels[] = {"OFF", "FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE", "ALL"};
typedef enum { false, true } bool;

int MAX_BUFF_SIZE=8192;

typedef struct {
    FILE *output;
    bool hasDate;
    char *LEVEL;
} Logger;

typedef struct {
    char *date;
    char *level;
    char *msg;
} LogRecord;

Logger *logger;
LogRecord *logRecord;

#define logFatal(...) logPrint("FATAL", __VA_ARGS__)
#define logError(...) logPrint("ERROR", __VA_ARGS__)
#define logWarn(...)  logPrint("WARN" , __VA_ARGS__)
#define logInfo(...)  logPrint("INFO" , __VA_ARGS__)
#define logDebug(...) logPrint("DEBUG", __VA_ARGS__)
#define logTrace(...) logPrint("TRACE", __VA_ARGS__)

void quickLoggerInit(char *logFilename, char *loggingLevel, bool hasDateTime){
    logger = malloc(5*sizeof(Logger));
    if (loggingLevel == NULL){
        logger->LEVEL = "WARN";
    } else {
        logger->LEVEL = loggingLevel;
    }
    
	if(logFilename != NULL && strcmp(logFilename,"")){
		logger->output = fopen(logFilename, "a");
	} else {
        logger->output = NULL;
    }

    logger->hasDate = hasDateTime;
}

void logClose(){
	if(logger->output != NULL){
		fclose(logger->output);
	}
}

int rankLevel(char *s){
	int i = 0;
    int n_levels = sizeof(logLevels)/sizeof(const char*);
	while (i < n_levels)
	{
		if(strcmp(s,logLevels[i]) == 0){
			return i;
		} else {
			i++;
		}
	}
	return -1;	
}

void outputText(char *type, char *s){
	if (logger->output == NULL){
		if (strcmp(type,"err") == 0){
            fprintf(stderr,s);
        } else {
            printf(s);
        }
	} else {
        fprintf(logger->output, s);
    }
}

void logPrint(char *messageLevel, char *s, ... ) {
    logRecord = malloc(sizeof(LogRecord));

	va_list valist;
	va_start(valist, s);

	logRecord->msg = malloc(MAX_BUFF_SIZE * sizeof(char));
    vsprintf(logRecord->msg, s, valist);

	va_end(valist);

    logRecord->date = malloc(80);
	if(logger->hasDate){
		struct timeval tv;
		gettimeofday(&tv,NULL);
		strftime(logRecord->date, 80, "%Y-%m-%d %X", localtime(&tv.tv_sec));
		strcat(logRecord->date, ".");
		char usec[6];
		sprintf(usec, "%d", tv.tv_usec);
		strcat(logRecord->date, usec);
	}

    if(rankLevel(logger->LEVEL) >= rankLevel(messageLevel)){
        char *msgStr = malloc(MAX_BUFF_SIZE * sizeof(char));
        logRecord->level = messageLevel;
        sprintf(msgStr, "%s:%-5s:%s\n", logRecord->date, logRecord->level, logRecord->msg);
        if(rankLevel(messageLevel) <= rankLevel("ERROR")) {
            outputText("err", msgStr);
        } else {
            outputText("out", msgStr);
        }
    }
}
