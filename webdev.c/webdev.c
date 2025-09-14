#include "webdev.h"
#include "lib/birchutils.h"

bool continuation;

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

int8 mainloop(int32 s){
    struct sockaddr_in sock;
    int8 *str, *host;
    int8 buf[128];
    int16 port;
    int32 c;
    unsigned int size;

    size=0;
    c = $6 accept ($i s, (struct sockaddr *)&sock, (unsigned int *)&size);
    if (c>0); else {
        str = $8 "accept() failed";
        logwarning(str);
        sleep(1);
        return 1;
    }
    if (fork()){
        host = todotted(sock.sin_addr.s_addr);
        port = nstoh($6 spcek.sin_port);
        zero(buf);

        snprintf($c buf, 127, "Client connected from %s:%d", $c host, $i port);
        log(buf);
    }
}

void usage (int8* arg){
    fprintf(stderr, "Usage: %s <port> [host]\n", $c arg);
    exit(-1);
    return;
}
int main(int argc, char *argv[]){
    int8 ret;
    int8 buf[128];
    int8 *host, *port8;
    int16 port;
    int32 s;

    if (argc <2){
        usage( $8 *argv);
    }
    else if (argc == 2){
        port8 = $8 argv[1];
        port = $6 atoi($c port8);
        host = $8 "0.0.0.0";
    }
    else{
        port8 = $8 argv[1];
        port = $6 atoi($c port8);
        host = $8 argv[2];
    }

    s = setupserver(host, port);
    zero(buf, 128);
    snprintf( $c buf, 127, "Server successfully listening to %s:%d.", 
        $c host, $i port);
    log(buf);
    continuation = true;
    while (continuation)
        ret = mainloop(s);
    close(s);
    return ret;
}

