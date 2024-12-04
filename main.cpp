#include <WS2tcpip.h>
#include <WinSock2.h>
#include <iostream>

constexpr char DEFAULT_PORT[] = "27015";

bool server_init(struct addrinfo *result);

int main() {
    auto wVersionRequested = MAKEWORD(2, 0);
    WSADATA wsaData;
    auto err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        std::cerr << "WSAStartup failed with code: " << err << std::endl;
        return 0;
    }

    addrinfo *result = nullptr;
    //    server_init(result);
    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    auto iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed with code: " << iResult << std::endl;
        WSACleanup();
        return 0;
    }
    if (result == nullptr) {
        std::cerr << "addrinfo is null" << std::endl;
        return 0;
    }
    SOCKET ListenSocket = INVALID_SOCKET;
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 0;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int) result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "Error at socket bind(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
    }
    freeaddrinfo(result);
    return 0;
}
