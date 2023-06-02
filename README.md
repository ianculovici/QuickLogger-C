# QuickLogger C Implementation
QuickLogger is a simple logger class with text formatting for C.

## Usage
### Syntax
    void logPrint(
        char *loggingLevel = <"OFF" | "FATAL" | "ERROR" | "WARN" | "INFO" | "DEBUG" | "TRACE" | "ALL">, 
        char *format [, ... parameters])
    void  fatal(char *format [, ... parameters])
    void  error(char *format [, ... parameters])
    void   warn(char *format [, ... parameters])
    void   info(char *format [, ... parameters])
    void  debug(char *format [, ... parameters])
    void  trace(char *format [, ... parameters])
        
    void quickLoggerInit(char *logFilename, char *loggingLevel, bool hasDateTime)

### Paramenters
**format**
- standard text formatting - example:https://pubs.opengroup.org/onlinepubs/9699919799/functions/printf.html

**logFilename**
- Specifies the path and filename for where the logging will be done. If blank (""), it will log to standard & error output.

**hasDateTime**
- If the output should show timestamp or not. Default: true


## Examples
  - Declaration: 
    - This will write to a file
  
      `quickLoggerInit("/opt/log/application.log", "INFO", true);`

    - This will write to the standard output and use the default level of WARN

       `quickLoggerInit(NULL, NULL, true);`

  - Usage:
 
        logInfo("Connection details: Host: %s, User: %s. Port: %d", host, user, port);
        logError("Fatal error! Exiting...");