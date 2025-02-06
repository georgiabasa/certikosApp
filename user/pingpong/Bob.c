// USER - READ, EXECUTE

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syscall.h>
#include "permissions.h"

int
main (int argc, char **argv)
{
	char *username = "user";
	char *filename = "secure_data.txt";
	char *exec_file = "./test_exec";

	//READ TEST
	printf("User trying to READ secure_data.txt...\n");
	if (check_permission(username, USER_R)) {
		int fd = open(filename, O_RDONLY);
		if (fd>=0) {
			char buffer[100];
			read(fd, buffer, sizeof(buffer));
			close(fd);
			printf("User successfully READ secure_data.txt: %s\n", buffer);
		} else {
			printf("Error opening secure_data.txt\n");
		}
	} else {
		printf("Access denied for User to READ secure_data.txt\n");
	}

	//WRITE TEST
	printf("User trying to WRITE secure_data.txt...\n");
	if (check_permission(username, USER_W)) {
		int fd = open(filename, O_WRONLY);
		if (fd>=0) {
			write(fd, "User was here!\n", 14);
			close(fd);
			printf("User successfully WROTE secure_data.txt\n");
		} else {
			printf("Error opening secure_data.txt\n");
		}
	} else {
		printf("Access denied for User to WRITE secure_data.txt\n");
	}

	//EXEC TEST
	printf("User trying to EXECUTE secure_data.txt...\n");
	if (check_permission(username, USER_X)) {
		execl(exec_file, exec_file, NULL);
		printf("User successfully EXECUTE test_exec\n");
	} else {
		printf("Access denied for User to EXECUTE test_exec\n");
	}

	return 0;
}
