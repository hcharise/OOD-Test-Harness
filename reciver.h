#undef UNICODE

#ifndef WIN32_LEAN_AND_MEAN_REC
#define WIN32_LEAN_AND_MEAN_REC

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl getMessage(std::string& message);

#endif