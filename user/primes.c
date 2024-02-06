#include "kernel/types.h"
// #include "kernel/stat.h"
#include "user/user.h"
// #include "user/ulib.c"
// #include "linux/delay.h"

void sieve(int read_pipe) {
  int pid, i, curr;
  int new_pipe[2];
  int numbers[35] = {};

  curr = 0;
  i = 0;
  while(curr != -1) {    
    if (read(read_pipe, &curr, sizeof(int)) && curr != -1)
      numbers[i++] = curr;
    // fprintf(1, "cand %d\n", curr);
  }
  close(read_pipe);
  
  if (i) {
    fprintf(1, "prime %d\n", numbers[0]);
    pipe(new_pipe);
    pid = fork();

    if (!pid) { // child
      close(new_pipe[1]);
      sieve(new_pipe[0]);
    } else { // parent
      close(new_pipe[0]);
      for(curr = 1; i > curr; ++curr) {
        if (numbers[curr] % numbers[0])
            write(new_pipe[1], numbers + curr, sizeof(int));
      }
      pid = -1;
      write(new_pipe[1], &pid, sizeof(int));
      close(new_pipe[1]);
      wait(0);
    }
  }
}

int main(int argc, char *argv[])
{
  int pid, i;
  int first_pipe[2];

  pipe(first_pipe);
  pid = fork();
  if (!pid) {
    close(first_pipe[1]);
    sieve(first_pipe[0]);
  } else {
    close(first_pipe[0]);
    for (i=2; i<=35; ++i) {
      write(first_pipe[1], &i, sizeof(int));  
    }
    i = -1;
    write(first_pipe[1], &i, sizeof(int));
    close(first_pipe[1]);
    wait(0);    
  }

  exit(0);
}
