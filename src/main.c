#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BACKLOG 10
#define BUF_SIZE 1024

int main(void) {
  int server_fd;
  struct sockaddr_in addr;

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("socket");
    exit(1);
  }

  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("setsockopt");
    exit(1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  if (listen(server_fd, BACKLOG) < 0) {
    perror("listen");
    exit(1);
  }

  printf("kvstore listening on port %d\n", PORT);

  while (1) {
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
      perror("accept");
      continue;
    }

    char buffer[BUF_SIZE];
    ssize_t n = read(client_fd, buffer, BUF_SIZE - 1);
    if (n > 0) {
      buffer[n] = '\0';
      printf("received: %s", buffer);
      write(client_fd, "OK\n", 3);
    }

    close(client_fd);
  }

  close(server_fd);
  return 0;
}

