#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

const char *html_content = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=utf-8\r\n\r\n"
"<!DOCTYPE html>"
"<html>"
"<head><title>Servidor Carlao</title></head>"
"<body>"
"<h1>Controlador de Acesso</h1>"
"<p>Olá, seja bem-vindo ao controlador de acesso do Carlão!</p>"
"<p>Este é um servidor web simples que foi criado para demonstrar o funcionamento de um servidor web.</p>"
"<p>Este servidor foi criado com a linguagem de programação C e a biblioteca de sockets do Linux.</p>"
"<p>Este servidor foi criado por Carlos Henrique.</p>"
"<p>Este servidor foi criado para fins educacionais.</p>"
"<p>Este servidor foi criado para o curso de Redes de Computadores.</p>"
"<p>Este servidor foi criado para a disciplina de Redes de Computadores.</p>"
"</body>"
"</html>";

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, BUFFER_SIZE);
    write(client_socket, html_content, strlen(html_content));
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Falha ao criar o socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Falha ao fazer o bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Falha ao escutar");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor web rodando na porta %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Falha ao aceitar conexão");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_client(client_socket);
    }

    return 0;
}