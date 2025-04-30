#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sock;
  struct sockaddr_in server;
  char buffer[BUFFER_SIZE];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("connection error");
    exit(EXIT_FAILURE);
  }

  int n;
  while ((n = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
    buffer[n] = '\0';
    printf("%s", buffer);
  }

  close(sock);
  return 0;
}
