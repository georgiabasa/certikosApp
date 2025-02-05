#include <stdio.h>
#include <proc.h>
#include <syscall.h>
#include <sysenter.h>

int 
main (int argc, char **argv)
{
    printf("\n\n\nHello, world!!!!!!\n\n\n\n\n");
    printf("hello passed\n");

    while(1) {
	yield ();
    }

    return 0;
}
