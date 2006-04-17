#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static int N=200,n,i,j;double *s;
static void process_string(const char*u)
{double x;int j;const char*_=u;while(*_==' ')++_;
 for(j=0;j<n;j++){sscanf(_,"%lf",&x);s[j]+=x;_=strchr(_+1,' ');}
 if(++i==N)
 {i=0;for(j=0;j<n;s[j++]=0)printf("%.2f ",s[j]/N);putchar('\n');}
}
static void init_n(const char*u)
{const char*_=u;while(*_==' ')++_;do{n++;_=strchr(_+1,' ');}while(_);
 s=calloc(n,sizeof(*s));for(j=0;j<n;s[j++]=0);
}void free_all(void){if(s)free(s);}
int main(int argc,char**argv)
{static char str[4913];if(argc>1)sscanf(argv[1],"%i",&N);if(N<1)return 1;
 fgets(str,sizeof(str),stdin);init_n(str);process_string(str);
 while(!feof(stdin)){fgets(str,sizeof(str),stdin);process_string(str);}
 free_all();return 0;
}
