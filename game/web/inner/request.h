// reference: https://blog.csdn.net/lanzhihui_10086/article/details/40685403
// DO NOT USE THIS HEADER. THIS IS OBSOLETE.

#ifndef NERDLE_WEB_REQUEST_H
#define NERDLE_WEB_REQUEST_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
//#include <inaddr.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "link.h"

typedef struct in_addr in_addr;

#define NERDLEGAME_SITE "nerdlegame.com"

const char default_head_format[] = "GET %s HTTP/1.1\r\nHost:%s\r\nsec-ch-ua: \"Microsoft Edge\";v=\"113\", \"Chromium\";v=\"113\", \"Not-A.Brand\";v=\"24\"\r\nsec-ch-ua-mobile: ?0\r\nsec-fetch-dest: document\r\nsec-fetch-mode: navigate\r\nsec-fetch-site: same-origin\r\nsec-fetch-user: ?1\r\nupgrade-insecure-requests: 1\r\nuser-agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, link Gecko) Chrome/113.0.0.0 Safari/537.36 Edg/113.0.1774.57\r\n:authority: nerdlegame.com\r\n:method: GET\r\n:path: /\r\n:scheme: https\r\naccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*,q=0.8,application/signed-exchange;v=b3;q=0.7\r\naccept-encoding: gzip, deflate, br\r\naccept-language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6\r\ncache-control: no-cache\r\n";

//#pragma comment(lib, "Ws2_32.lib")

void HttpGetHead(char* buf, const char* host, const char* url) {
    sprintf(buf, default_head_format, url, host);
}

bool getIP(char *ip, char *hostname) {
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0) {
        return false;
    }
    HOSTENT *host = gethostbyname(hostname);
    if (host == NULL) {
        return false;
    }
    strcpy(ip, inet_ntoa(*(in_addr*)*host->h_addr_list));
    return true;
}

bool httpGetNerdleEncryptedData(char out_encrypted_data[1024]) {
    int num;
    SOCKET s;
    WSADATA wsa;
    struct sockaddr_in serv;

    char sndBuf[1024], rcvBuf[2048];

    WSAStartup(MAKEWORD(2, 1), &wsa);
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        return false;
    }

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(80);
    char ip[128] = { 0 };
    getIP(ip, NERDLEGAME_SITE);
    serv.sin_addr.S_un.S_addr = inet_addr(ip);

    //BING 70.37.92.127
    //BAIDU 115.239.210.26
    //baidu api 180.149.132.118
    //google 74.125.31.99
    //sina  59.175.132.113
    //163   222.243.110.164
    //taobao   218.75.155.151
    //jd    116.211.94.1

    if ((connect(s, (struct sockaddr*)&serv, sizeof(serv))) < 0) {
        return false;
    }
    memset(sndBuf, 0, 1024);
    memset(rcvBuf, 0, 2048);

    char link[128] = { 0 };
    char url[128] = { 0 };
    getLink(link, url);

    HttpGetHead(sndBuf, link, url);
    if ((num = send(s, sndBuf, 1024, 0)) < 0) {
        return false;
    }

    do {
        if ((num = recv(s, rcvBuf, 2048, 0)) < 0) {
            return false;
        }
        else if (num > 0) {
            break;
        }
    } while (num > 0);
    strncpy(out_encrypted_data, rcvBuf, 1023);

    closesocket(s);

    WSACleanup();
    return true;
}

#endif