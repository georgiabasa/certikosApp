// ADMIN - READ, WRITE, EXECUTE

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syscall.h>
#include "permissions.h"

int
main (int argc, char **argv)
{
	char *username = "admin";
	char *filename = "secure_data.txt";
	char *exec_file = "./test_exec";

	//READ TEST
	printf("Admin trying to READ secure_data.txt...\n");
	if (check_permission(username, ADMIN_R)) {
		int fd = open(filename, O_RDONLY);
		if (fd>=0) {
			char buffer[100];
			read(fd, buffer, sizeof(buffer));
			close(fd);
			printf("Admin successfully READ secure_data.txt: %s\n", buffer);
		} else {
			printf("Error opening secure_data.txt\n");
		}
	} else {
		printf("Access denied for Admin to READ secure_data.txt\n");
	}

	//WRITE TEST
	printf("Admin trying to WRITE secure_data.txt...\n");
	if (check_permission(username, ADMIN_W)) {
		int fd = open(filename, O_WRONLY | O_CREAT, 0644);
		if (fd>=0) {
			write(fd, "Admin was here!\n", 16);
			close(fd);
			printf("Admin successfully WROTE secure_data.txt\n");
		} else {
			printf("Error opening secure_data.txt\n");
		}
	} else {
		printf("Access denied for Admin to WRITE secure_data.txt\n");
	}

	//EXEC TEST
	printf("Admin trying to EXECUTE secure_data.txt...\n");
	if (check_permission(username, ADMIN_X)) {
		execl(exec_file, exec_file, NULL);
		printf("Admin successfully EXECUTE test_exec\n");
	} else {
		printf("Access denied for Admin to EXECUTE test_exec\n");
	}

	//yield to guest
	while (1) {
		yield();
	}

	return 0;
}
