#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 1. Crea la socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Errore nella creazione della socket");
        return 1;
    }

    // 2. Imposta i parametri del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // 3. Invia messaggio
    string messaggio = "";
    
    while (messaggio != "Fine") {
        cout << "Inserisci messaggio da inviare o scrivi 'Fine' per uscire: ";
        getline(cin, messaggio);

        if (messaggio != "Fine") {
            sendto(sockfd, messaggio.c_str(), messaggio.size(), 0,(struct sockaddr*)&server_addr, sizeof(server_addr));
            // 4. Ricevi risposta
            socklen_t len = sizeof(server_addr);
            int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,(struct sockaddr*)&server_addr, &len);
            buffer[n] = '\0';
            std::cout << "Risposta dal server: " << buffer << std::endl;
        }
    }
    close(sockfd);
    return 0;
}