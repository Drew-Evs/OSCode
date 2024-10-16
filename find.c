#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: find <filename>");
        exit(1);
    }

    ls(argv[1]);

    exit(0);
}

char* fmtname(char *path) {
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--);
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

//takes in a path and lists all files in that path
void ls(char *path) {
  //creates a pointer to a character buffer
  char buf[512], *p;
  int fd;
  //directory stream
  struct dirent de;
  //gets status of file
  struct stat st;

  //if opening the path is 0 then it doesnt exist
  if((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  //if status of file is 0 doesnt exist
  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  //controls what happens based on the file type
  switch(st.type){
  case T_DEVICE:
  case T_FILE:
    printf("%s %d %d %d\n", fmtname(path));
    break;

  //if file type is directory needs to pass reflexively into ls
  case T_DIR:
    //test length of path
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }

    //copies the path 
    strcpy(buf, path);
    p = buf+strlen(buf);
    //sets the pointer to the next slash
    *p++ = '/';
    //loops until out of range of directory
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
      //skips invalid entries
      if(de.inum == 0)
        continue;
      //copies + null terminates string to buffer
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      //gets status of file if negative returns value
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      //prints the directory name + passes reflexively
      printf("%s %d %d %d\n", fmtname(buf));
      ls(buf);
    }
    break;
  }
  close(fd);
}
