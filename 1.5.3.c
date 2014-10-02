#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 255

char ** string_split(char*, char*);
int parse_cmd(char*);


char **
string_split(char  * str, char * split)
{
    char ** ret_split = (char **)malloc(sizeof(char * ) * MAXLINE);
    char * temp;
    temp = strtok(str, split);
    int i = 0;
    while(temp)
    {
        *(ret_split + i) = temp;
        i++;
        temp = strtok(NULL, split);
    }
    *(ret_split +i) = NULL; 
    
    return ret_split;
}

int 
parse_cmd(char * cmd)
{
    char ** cmds = string_split(cmd, " ");    
    int signal = execvp(*(cmds + 0), cmds); 
    return signal;
}

int 
main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%%");
    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        buf[strlen(buf) - 1] = 0;
        if((pid = fork()) < 0)
        {
            printf("fork error");
        }
        else if(pid == 0)
        {  
            parse_cmd(buf);
            printf("could not execute : %s\n", buf);
            exit(127);
        }
        if((pid = waitpid(pid, &status, 0)) < 0)
        {
            printf("waitpid error");
        }
        printf("%d\n", status);
        printf("%%");

    }

    exit(0);
}
