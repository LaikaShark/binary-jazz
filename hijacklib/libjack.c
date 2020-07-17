//compile with: gcc -o libjack.so -fPIC -shared -D_GNU_SOURCE libjack.c -ldl
//run with: LD_PRELOAD=`pwd`/libjack.so ls /usr/share 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/stat.h>
int (*jacked_xstat)(int, const char*, struct stat*);

int is_home(char* path)
{
  char* hpath = getenv("HOME");
  if(hpath == NULL)
    return 0;
    //where are you?

   if(strncmp(path,hpath, strlen(hpath)) == 0)
    return 1;

   return 0;
}

int __xstat(int ver, const char* path, struct stat* stat_buf)
{
  printf("Starting hijacked __xstat\n");
  printf("Grabbing original...");
  if(jacked_xstat == NULL)
    jacked_xstat = dlsym(RTLD_NEXT,"__xstat");
  printf("Done\n");
  
  printf("Checking if home...");
  char *rpath = realpath(path, NULL);
  if(!is_home(rpath))
  {
    printf("Nope!\n");
    errno = EACCES;
    free(rpath);
    return -1;
  }
  printf("Yep!\n");
  free(rpath);
  printf("Handing off to real __xstat\n");
  return jacked_xstat(ver, path, stat_buf);
}
