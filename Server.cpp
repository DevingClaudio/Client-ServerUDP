#include <iostream>
#include <cstring>
#include <arpa/inet.h>   
#include <sys/socket.h>
#include <unistd.h>      
using namespace std;

#define porta 8080
#define Buffer_Size 1024

char buffer[Buffer_Size];
struct sockaddr_in serverAddr, clientAddr;
socklen_t clientLen = sizeof(clientAddr);
int Socket = socket(AF_INET, SOCK_DGRAM, 0);
if (Socket < 0) {
    cout<<"Errore nella creazione del socket";
    return -1;
}
else {
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);  

    if (bind(Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout<<"Errore nel binding a indirizzo e porta"
    }
    else {
        cout<<'Server UDP in ascolto sulla porta: '<<PORT<<'\n';
        while (true) {
            memset(buffer, 0, Buffer_Size)
            
        }
    }
}