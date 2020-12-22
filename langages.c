#include <stdio.h>

int main(int argc, char** argv){
  char c;

  // États internes des automates
  int L4=0;
  
  while((c = fgetc(stdin)) != EOF) {

    // Automate reconnaissant L4
    if (c == '\n' && L4!=1 && L4!=2 && L4!=3)	printf("non ");
    if (c == '\n')		{printf("reconnu par L4\n"); L4 = 0;}
    else if(L4==0 && c=='a')	L4 = 1;
    else if(L4==1 && c=='d')	L4 = 2;
    else if(L4==1 && c=='c')	L4 = 3;
    else if(L4==1 && c=='b')	L4 = 4;
    else if(L4==2 && c=='d')	L4 = 2;
    else if(L4==2 && c=='c')	L4 = 3;
    else if(L4==2 && c=='b')	L4 = 4;
    else if(L4==3 && c=='a')	L4 = 5;
    else if(L4==3 && c=='d')	L4 = 2;
    else if(L4==3 && c=='c')	L4 = 3;
    else if(L4==3 && c=='b')	L4 = 4;
    else if(L4==4 && c=='c')	L4 = 2;
    else if(L4==5 && c=='a')	L4 = 5;
    else if(L4==5 && c=='b')	L4 = 4;
    else if(c!=' ' && c!='\t')	L4 = -1;

  }
  return 0;
}
