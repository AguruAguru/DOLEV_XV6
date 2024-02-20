#include "kernel/types.h"
// #include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

char* strncat(char* destination, const char* source, unsigned num)
{
    // make `ptr` point to the end of the destination string
    char* ptr = destination + strlen(destination);
 
    // Appends characters of the source to the destination string
    while (*source != '\0' && num--) {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // destination string is returned by standard `strncat()`
    return destination;
}

int get_line_from_user(char *buffer, unsigned size)
{
    unsigned cnt = 0;
    char c;
    int tmp;

    if(buffer == 0 || size == 0)
        return 0;

    if ((tmp = read(0, &c, 1)) == 1 && cnt < size - 1)
    {
        do
        {
            if(c == '\n')
            {
                buffer[cnt] = 0;
                return 1;
            }

            buffer[cnt++] = c;
        } while((tmp = read(0, &c, 1)) == 1 && cnt < size - 1);
    } else {
        return 0;
    }
    

    buffer[cnt] = 0; // making sure it's 0-terminated
    return 1;
}

void run(char *s1, char *s2[], int argc) {
  int pid, i, index;
  char buff[MAXARG][30] = {};
  char *my_buff[30] = {};
  for (i = 0; i < argc; ++i)
    strcpy(buff[i], s2[i]);
  
  index = -1;
  while(s1[++index]) {
    if (s1[index] == ' ')
      ++i;
    else
      strncat(buff[i], s1 + index, 1);
  }
  for (pid=0; pid <= i; ++pid)
    my_buff[pid] = buff[pid];
  my_buff[i+1] = 0;
  pid = fork();
  if (!pid) {
    // for (pid = 0; i >= pid; ++pid)
        // fprintf(1,"%s\n", my_buff[pid]);
    exec(my_buff[0], (char **)my_buff);
  } else {
    wait(0);
  }

}

int main(int argc, char *argv[])
{
  char line[MAXARG*30] = {};
  while (get_line_from_user(line, MAXARG*30)) {
    run(line, argv + 1, argc - 1);
  }
  return 1;
}
