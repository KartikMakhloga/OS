#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(){
int p=fork();
if(p==-1)
{
printf("unable to fork");
return 0;
}
else if(p>0)
{
wait(NULL);
printf("in parent with pid=%d\n",getpid());
char* path="/bin/ls";
char* arg="-l";
execl(path,path,arg,NULL);
}
else
{
printf("in child with pid=%d\n",getpid());
char* chpath="/bin/date";
execl(chpath,chpath,NULL);
}
return 0;
}