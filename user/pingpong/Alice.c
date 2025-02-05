#include <proc.h>
#include <stdio.h>
#include <syscall.h>
#include <sysenter.h>
#include <x86.h>

#define SIZE 100000000
#define PGSIZE 4096
#define BIT 'a'

int
main (int argc, char **argv)
{
  printf("\n\nHELLO GEORGIAAAAAAAA !!! \n\n");
  while (1) {
	//printf ("Alice silently yield\n");
	yield ();
  }	
  return 0;
}
