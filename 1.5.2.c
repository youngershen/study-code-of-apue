#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
    pid_t pid = getpid();
    printf("hell world from process ID %d\n", pid);
    exit(0);
}
