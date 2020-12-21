#include <stdio.h>

int main(int argc, char** argv){
  char c;

  // États internes des automates
  int L2=0;
  
  while((c = fgetc(stdin)) != EOF) {

    // Automate reconnaissant L2
    if (c == '\n' && L2!=2)	printf("non ");
    if (c == '\n')		{printf("reconnu par L2\n"); L2 = 0;}
    else if(L2==0 && c=='a')	L2 = 1;
    else if(L2==1 && c=='a')	L2 = 1;
    else if(L2==1 && c=='b')	L2 = 2;
    else if(L2==2 && c=='b')	L2 = 2;
    else if(c!=' ' && c!='\t')	L2 = -1;

  }
  return 0;
}
