#include <stdio.h>

#include "QuickLogger.c"

void main(){
	quickLoggerInit("file.log", "INFO", true);
	quickLoggerInit(NULL, NULL, true);

    char *host="localhost", *user="dbuser";
    int port = 54321;
    logInfo("Connection details: Host: %s, User: %s, Port: %d", host, user, port);
    logTrace("If you see this, level of logging 'TRACE' is enabled");
    logError("Fatal error! Exiting...");
	logClose();
}
