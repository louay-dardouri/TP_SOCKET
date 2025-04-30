#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int server_fd, client_fd;
  struct sockaddr_in server, client;
  socklen_t client_len = sizeof(client);
  char buffer[BUFFER_SIZE];

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("bind error");
    exit(EXIT_FAILURE);
  }
  listen(server_fd, 5);

  printf("Waiting for client...\n");
  client_fd = accept(server_fd, (struct sockaddr *)&client, &client_len);

  for (int i = 0; i < 60; i++) {
    time_t now = time(NULL);
    strftime(buffer, BUFFER_SIZE, "Il est %H:%M:%S\n", localtime(&now));
    send(client_fd, buffer, strlen(buffer), 0);
    sleep(1);
  }

  close(client_fd);
  close(server_fd);
  return 0;
}
