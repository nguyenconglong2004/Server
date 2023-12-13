#include "socket.h"

Socket::Socket() {

}
Socket :: ~Socket() {

}
int Socket::init_and_connect() {
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }
    else std ::cout << "WSAStartup Successful.\n";

    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 2;
    }
    else std ::cout << "Socket Successful.\n";

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    iResult = bind(listenSocket, (sockaddr*)&address, sizeof(address));
    if (iResult == SOCKET_ERROR) {
        std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
        data[0] = WSAGetLastError();
        closesocket(listenSocket);
        WSACleanup();
        return 3;
    }
    else std :: cout << "Bind Successfull.\n";

    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 4;
    }
    else std :: cout << "Listen Successful.\n";

    // Chờ kết nối từ máy khách
    clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 5;
    }
    else std :: cout << "Accepted connection.\n";

}
bool Socket::recieve() {
    char buffer[12] = {'\0'};
    int bytesReceived = recv(clientSocket, buffer, 12, 0);
    if (bytesReceived == -1)
        return 0;
    for (int i = 0; i < 3; i++) {
        int networkInt;
        memcpy(&networkInt, buffer + i * sizeof(int), sizeof(int));
        data[i] = ntohl(networkInt);
    }
    return 1;
}
void Socket::break_up() {
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();
}