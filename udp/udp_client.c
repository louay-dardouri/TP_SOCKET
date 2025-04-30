#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sock;
  struct sockaddr_in server;
  char buffer[BUFFER_SIZE];
  socklen_t len = sizeof(server);

  sock = socket(AF_INET, SOCK_DGRAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  sendto(sock, "start", 5, 0, (struct sockaddr *)&server, len);

  for (int i = 0; i < 60; i++) {
    int n = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0, NULL, NULL);
    buffer[n] = '\0';
    printf("%s", buffer);
  }

  close(sock);
  return 0;
}
