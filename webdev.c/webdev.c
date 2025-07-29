#include "webdev.h"
#include "lib/birchutils.h"


void syslogger(int16 priority, int8 *str){
    openlog("webdev.c", 0, LOG_SYSLOG);
    syslog($i priority, "%s", str);
    closelog();
    return;
}

int32 setupserver(int8 *host, int16 port){
    struct sockaddr_in sock;
    int32 s;

    s=$2 socket(AF_INET, SOCK_STREAM, 0);
    assert(s>0);

    sock.sin_family = AF_INET;
    sock.sin_port = htons($i port);
    sock.sin_addr.s_addr = inet_addr($c host);

    n= $6 bind(s, (struct sockaddr *)&sock, sizeof(sock));
    assert(!n);
    n =$6 listen(s, 50);
    assert(!n);

    return s;
}


int main(int argc, char *argv[]){
    int8 *str;
    str= $8 "Server starting up";
    log(str);
    return 0;
}

