#include "kernel/types.h"
// #include "kernel/stat.h"
#include "user/user.h"
// #include "user/ulib.c"
// #include "linux/delay.h"

int main(int argc, char *argv[])
{
  int pid;
  char byte;
  int pipe_ds[2][2] = {};
  pipe(pipe_ds[0]);
  pipe(pipe_ds[1]);
  pid = fork();  

  if (!pid) {
    close(pipe_ds[0][1]);
    close(pipe_ds[1][0]);
    while(!read(pipe_ds[0][0], &byte, 1));
    fprintf(1, "%d: received ping\n", getpid());
    write(pipe_ds[1][1], &byte, 1);
  } else {
    close(pipe_ds[1][1]);
    close(pipe_ds[0][0]);
    write(pipe_ds[0][1], &byte, 1);
    while(!read(pipe_ds[1][0], &byte, 1));
    fprintf(1, "%d: received pong\n", getpid());
  }

  exit(0);
}
// git restore --source=HEAD :/
