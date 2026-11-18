#include <stdio.h>
#include <unistd.h>
#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif
#include "LineParser.h"
#include <string.h>
#include <stdlib.h>

void execute(cmdLine *pCmdLine)
{
  execvp(pCmdLine->arguments[0], (char **)pCmdLine->arguments);
  perror("execvp failed");
  _exit(1);
}

int main(int argc, char **argv)
{
  char path[PATH_MAX];
  char input[2048];
  cmdLine *parsedLine;
  pid_t pid;
  int debug = 0;
  int i;

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      debug = 1;
    }
  }
  while (1) {
    if (getcwd(path, PATH_MAX) == NULL) {
      perror("getcwd");
      return 1;
    }

    printf("%s> ", path);
    fflush(stdout);

    if (fgets(input, 2048, stdin) == NULL) {
      break;
    }

    parsedLine = parseCmdLines(input);
    if (parsedLine == NULL) {
      continue;
    }
    if (parsedLine->argCount == 0) {
      freeCmdLines(parsedLine);
      continue;
    }
    if (strcmp(parsedLine->arguments[0], "quit") == 0) {
      freeCmdLines(parsedLine);
      return 0;
    }
    if (strcmp(parsedLine->arguments[0], "cd") == 0) {
      if (parsedLine->argCount < 2) {
        fprintf(stderr, "cd: missing argument\n");
      } else if (chdir(parsedLine->arguments[1]) == -1) {
        perror("cd");
      }
      freeCmdLines(parsedLine);
      continue;
    }
    pid = fork();
    if (pid == 0) {
      execute(parsedLine);
    }
    if (debug) {
      fprintf(stderr, "PID: %d\n", pid);
      fprintf(stderr, "Executing command: %s\n", parsedLine->arguments[0]);
    }
    freeCmdLines(parsedLine);
  }

  return 0;
}
