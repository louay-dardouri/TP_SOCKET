#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
  int sock;
  struct sockaddr_in server;
  char request[BUFFER_SIZE], response[BUFFER_SIZE];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("Socket creation failed");
    exit(1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;

  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("Connection failed");
    exit(1);
  }

  printf("Enter HTTP request (e.g., GET / HTTP/1.1");
  fgets(request, sizeof(request), stdin);

  if (strstr(request, "\n\n") == NULL) {
    strcat(request, "\n\n");
  }

  send(sock, request, strlen(request), 0);

  int n;
  while ((n = recv(sock, response, sizeof(response) - 1, 0)) > 0) {
    response[n] = '\0';
    printf("%s", response);
  }

  close(sock);
  return 0;
}
