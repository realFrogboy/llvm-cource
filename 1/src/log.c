#include <stdio.h>

void funcStartLogger(char *funcName) {
  printf("[LOG] Start function '%s'\n", funcName);
}

void callLogger(char *callerName, char *calleeName, long int valID) {
  printf("[LOG] CALL '%s' -> '%s' {%ld}\n", callerName, calleeName, valID);
}

void funcEndLogger(char *funcName, long int valID) {
  printf("[LOG] End function '%s' {%ld}\n", funcName, valID);
}

void binOptLogger(int val, int arg0, int arg1, char *opName, char *funcName,
                  long int valID) {
  printf("[LOG] In function '%s': %d = %d %s %d {%ld}\n", funcName, val, arg0,
         opName, arg1, valID);
}

void cmpLogger(unsigned pred, int arg0, int arg1, char *opName, char *funcName,
               long int valID) {
  printf("[LOG] In function '%s': %s pred=%u %d, %d {%ld}\n", funcName, opName,
         pred, arg0, arg1, valID);
}

void brLogger(char *funcName, char *opName, int cond, long int valID) {
  printf("[LOG] In function '%s': %s ", funcName, opName);
  if (cond != -1)
    printf("cond=%u", cond);
  printf(" {%ld}\n", valID);
}

void unaryLogger(char *funcName, char *opName, long int valID) {
  printf("[LOG] In function '%s': %s {%ld}\n", funcName, opName, valID);
}
