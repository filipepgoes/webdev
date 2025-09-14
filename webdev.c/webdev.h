
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <syslog.h>
#include "./lib/birchutils.h"

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

#define $c (char *)
#define $8 (int8 *)
#define $6 (int16)
#define $2 (int32)
#define $4 (int64)
#define $i (int)

#define log(x)        syslogger(LOG_INFO, x)
#define logwarning(x) syslogger(LOG_WARN, x)
#define logerr(x)     syslogger(LOG_ERR, x)

void syslogger(int16, int8*);
int32 setupserver(int8*, int16);
int8 mainloop(int32);
void usage(int8*);
int main (int, char**);
