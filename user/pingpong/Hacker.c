#include <proc.h>
#include <stdio.h>
#include <syscall.h>
#include <sysenter.h>
#include <x86.h>

#define SIZE 100000000
#define PGSIZE 4096
#define BIT 'h'

int
main (int argc, char **argv)
{
  printf("\nHacker process reporting in!\n");

  while (1) yield ();
  return 0;
}
