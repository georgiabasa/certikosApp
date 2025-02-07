// USER - READ, EXECUTE

#include <stdio.h>
//#include <fcntl.h>
//#include <unistd.h>
#include <string.h>
#include <syscall.h>
#include "permissions.h"

int
main (int argc, char **argv)
{
	const char *username = "user";
	//char *filename = "secure_data.txt";
	//char *exec_file = "./test_exec";

	//READ TEST
	printf("\nUser trying to READ...\n");
	if (check_permission(username, USER_R)) {
		const char *m1 = "User: Access to READ files\n";
		sys_puts(m1, strlen(m1));
	} else {
		const char *m2 = "Access denied for User to READ\n";
		sys_puts(m2, strlen(m2));
	}

	//WRITE TEST
	printf("User trying to WRITE...\n");
	if (check_permission(username, USER_W)) {
		const char *m3 = "User: Access to WRITE files\n";
		sys_puts(m3, strlen(m3));
	} else {
		const char *m4 = "Access denied for User to WRITE\n";
		sys_puts(m4, strlen(m4));
	}

	//EXEC TEST
	printf("User trying to EXECUTE...\n");
	if (check_permission(username, USER_X)) {
		//execl(exec_file, exec_file, NULL);
		uint32_t elf_id = 4;
    		uint32_t quota = 10;
		sys_spawn(elf_id, quota);
		const char *m5 = "User: Access to EXECUTE spawn\n";
		puts(m5, strlen(m5));
	} else {
		const char *m6 = "Access denied for User to EXECUTE spawn\n";
		puts(m6, strlen(m6));
	}

	return 0;
}
