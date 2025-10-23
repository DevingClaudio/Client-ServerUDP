#include <iostream>
#include <cstring>
#include <arpa/inet.h>   // per inet_ntoa, htons, ecc.
#include <sys/socket.h>
#include <unistd.h>      // per close()

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 1. Creazione socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Errore nella creazione della socket");
        return 1;
    }

    // 2. Imposta i parametri del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;        // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);      // Porta in ascolto

    // 3. Bind socket alla porta
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Errore nel bind");
        close(sockfd);
        return 1;
    }

    std::cout << "Server UDP in ascolto sulla porta " << PORT << "...\n";

    // 4. Loop per ricevere messaggi
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,(struct sockaddr*)&client_addr, &client_len);
        if (len < 0) {
            perror("Errore nella ricezione");
            break;
        }

        std::cout << "Messaggio ricevuto da " 
                  << inet_ntoa(client_addr.sin_addr) 
                  << ": " << buffer << std::endl;

        //Risposta al client
        std::string risposta = "Ricevuto: " + std::string(buffer);
        sendto(sockfd, risposta.c_str(), risposta.size(), 0,
               (struct sockaddr*)&client_addr, client_len);
    }

    close(sockfd);
    return 0;
}
