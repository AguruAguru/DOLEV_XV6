#include "kernel/types.h"
//#include "kernel/stat.h"
#include "user/user.h"
// #include "user/ulib.c"

int main(int argc, char *argv[])
{
  unsigned time;

  if (argc <= 1) {
    fprintf(1, "not enough args");
    exit(1);
  }
  time = atoi(argv[1]);
  sleep(time * 10);
  exit(0);
}
