# Lab 2 — Simple Shell

Extended System Programming Laboratory. A basic command-line interpreter (`myshell`) plus helper programs for signals and pipes.

## What's included

| File | Role |
|------|------|
| `myshell.c` | Shell: prompt, fork/exec, `cd`, background (`&`), I/O redirection, signal commands |
| `looper.c` | Test process that prints and forwards `SIGINT`, `SIGTSTP`, `SIGCONT` |
| `mypipe.c` | Child → parent message over a pipe |
| `LineParser.c` / `LineParser.h` | Course-provided command-line parser |
| `Makefile` | Builds `myshell`, `looper`, and `mypipe` |

## Build

Requires Linux (`linux/limits.h`). On macOS, build inside a Linux container or lab machine.

```bash
make          # builds myshell, looper, mypipe
make myshell
make mypipe
make clean
```

## Run

```bash
./myshell
./myshell -d          # debug: print PID and command to stderr
./looper &
./mypipe "hello"
```

### Shell features

- Prompt shows the current working directory
- External commands via `fork` + `execvp`
- Built-ins: `quit`, `cd <path>`
- Foreground wait with `waitpid`; append `&` to run in the background
- Redirection: `cmd < in.txt > out.txt`
- Signal commands:
  - `zzzz <pid>` — `SIGSTOP`
  - `kuku <pid>` — `SIGCONT`
  - `blast <pid>` — `SIGINT`

### Example

```text
/path/to/lab> sleep 2 &
/path/to/lab> echo hello > test.txt
/path/to/lab> cat < test.txt
hello
/path/to/lab> ./looper &
/path/to/lab> zzzz 12345
/path/to/lab> kuku 12345
/path/to/lab> blast 12345
/path/to/lab> quit
```

## Tasks covered

- **0a / 0b** — basic shell loop; looper signal handler  
- **1a / 1b / 1c** — fork, `-d` debug, `cd`, foreground/background wait  
- **2** — input/output redirection  
- **3** — `zzzz` / `kuku` / `blast`  
- **4** — `mypipe`
