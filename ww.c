#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <sys/ioctl.h>
#include <unistd.h>

int getbar(){ // get barrier of terminal
  // this will return the number
  // of columns in terminal
   
  struct winsize w;  
  ioctl(0, TIOCGWINSZ, &w);
  return w.ws_col;
}

int main(){
  int used = 0;
  int c;
  int bs = 16;
  int bused = 0;
  char* block = calloc(sizeof(char), bs);
  if (block == NULL){
    // calloc call fail
    perror("calloc");
    return 1;
  }
  
  c = getchar();
  while(1){
    if(c == ' ' || c == '\n' || c == EOF){
      // end of word
      if(used > getbar()){ 
        // if used more than available
        // make a newline and print block
        // there
        printf("\n%s ", block);
        used = 0;
      } else {
        // otherwise just print it normally
        printf("%s ", block);
      }

      // reset buffer ctr and zero buffer
      bused = 0;
      memset(block, '\0', bs);

      if(c == EOF) break; // exit on end of file
      // otherwise keep going

      c = getchar();
      
      continue;
    }


    // increment for each character
    used++;
    bused++;
    
    // turn c into a string
    // for strncat
    char s[2] = { c, '\0' };

    if (bused <= bs){
      // prefent buffer overflow
      // by reallocating in 16 byte
      // increments each time buffer
      // runs out of space
      bs += 16;
      char *tmp = realloc(block, bs);
      if (tmp == NULL){
        // if realloc fails
        free(block);
        perror("realloc");
        return 1;
      }
      if (tmp != block){
        // move block to tmp if pointer
        // is moved to a new position
        // in memory, free old one to
        // prevent data leaks
        free(block);
        block = tmp;
      }

    }
    
    // copy first char of string
    // the string should only have
    // one char anyway, but this is
    // paranoia leads me to specify
    strncat(block, s, 1);
    
  
    if (block == NULL) {
      // strncat fails
      perror("strncat");
      return 1;
    }

    // start loop again
    c = getchar();
  }

  // free our memory and return
  free(block);
  return 0;
}
