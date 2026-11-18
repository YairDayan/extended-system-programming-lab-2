#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "usage: %s <message>\n", argv[0]);
    return 1;
  }
  int fd[2];
  if (pipe(fd) == -1) {
    perror("pipe");
    return 1;
  }
  pid_t pid = fork();
  if (pid == 0) {
    close(fd[0]);
    write(fd[1], argv[1], strlen(argv[1]));
    close(fd[1]);
    _exit(0);
  }

  close(fd[1]);
  char buffer[1024];
  ssize_t n;
  while ((n = read(fd[0], buffer, sizeof(buffer))) > 0) {
    write(1, buffer, n);
  }
  write(1, "\n", 1);
  close(fd[0]);
  waitpid(pid, NULL, 0);
  return 0;
}
