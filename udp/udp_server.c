#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sock;
  struct sockaddr_in server, client;
  char buffer[BUFFER_SIZE];
  socklen_t len = sizeof(client);

  sock = socket(AF_INET, SOCK_DGRAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("bind error");
    exit(EXIT_FAILURE);
  }

  recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &len);

  for (int i = 0; i < 60; i++) {
    time_t now = time(NULL);
    strftime(buffer, BUFFER_SIZE, "Il est %H:%M:%S\n", localtime(&now));
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&client, len);
    sleep(1);
  }

  close(sock);
  return 0;
}
