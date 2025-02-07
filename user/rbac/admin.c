// ADMIN - READ, WRITE, EXECUTE

#include <stdio.h>
//#include <fcntl.h>
//#include <unistd.h>
#include <string.h>
#include <syscall.h>
#include "permissions.h"

int
main (int argc, char **argv)
{
	const char *username = "admin";
	//char *filename = "secure_data.txt";
	//char *exec_file = "./test_exec";

	//READ TEST
	printf("\n\nAdmin trying to READ...\n");
	if (check_permission(username, ADMIN_R)) {
		const char *m1 = "Admin: Access to READ files.\n";
		sys_puts(m1, strlen(m1));
		//int fd = open(filename, O_RDONLY);
		//if (fd>=0) {
		//	char buffer[100];
		//	read(fd, buffer, sizeof(buffer));
		//	close(fd);
		//	printf("Admin successfully READ secure_data.txt: %s\n", buffer);
		//} else {
		//	printf("Error opening secure_data.txt\n");
	} else {
		const char *m2 = "Access denied for Admin to READ\n";
		sys_puts(m2, strlen(m2));
	}

	//WRITE TEST
	printf("Admin trying to WRITE...\n");
	if (check_permission(username, ADMIN_W)) {
		const char *m3 = "Admin: Access to WRITE files.\n";
		sys_puts(m3, strlen(m3));
	} else {
		const char *m4 = "Access denied for Admin to WRITE\n";
		sys_puts(m4, strlen(m4));
	}

	//EXEC TEST
	printf("Admin trying to EXECUTE...\n");
	if (check_permission(username, ADMIN_X)) {
		//execl(exec_file, exec_file, NULL);
		uint32_t elf_id = 4;
    		uint32_t quota = 10;
		sys_spawn(elf_id, quota);
		const char *m5 = "Admin access to EXECUTE spawn\n";
		sys_puts(m5, strlen(m5));
	} else {
		const char *m6 = "Access denied for Admin to EXECUTE spawn\n";
		sys_puts(m6, strlen(m6));
	}

	//yield to guest
	while (1) {
		yield();
	}

	return 0;
}
