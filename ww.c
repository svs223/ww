#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <sys/ioctl.h>
#include <unistd.h>

int getbar(){
  struct winsize w;  
  ioctl(0, TIOCGWINSZ, &w);
  return w.ws_col;
}

int main(){
  int used = 0;
  int c = '\0';
  int bs = 16;
  int bused = 0;
  char* block = calloc(sizeof(char), bs);
  if (block == NULL){
    perror("calloc");
    return 1;
  }
  
  c = getchar();
  while(1){
    if(c == ' ' || c == '\n' || c == EOF){
       if(used > getbar()){
        printf("\n%s ", block);
        used = 0;
      } else {
        printf("%s ", block);
      }

      bused = 0;
      memset(block, '\0', bs);

      if(c == EOF) break;

      c = getchar();
      
      continue;
    }



    used++;
    bused++;
    char s[2] = { c, '\0' };
    if (bused <= bs){
      bs += 16;
      char *tmp = realloc(block, 16);
      if (tmp == NULL){
        free(block);
        perror("realloc");
        return 1;
      }
      if (tmp != block){
        free(block);
        block = tmp;
      }

      
    }
    strncat(block, s, 1);
    used++;
    bused++;
    
    if (block == NULL) {
      perror("strcat");
      return 1;
    }

    c = getchar();
  }
  
  free(block);
  return 0;
}
