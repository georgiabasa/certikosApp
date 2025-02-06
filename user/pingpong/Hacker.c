// GUEST - READ only

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syscall.h>
#include "permissions.h"

int
main (int argc, char **argv)
{
	char *username = "guest";
	char *filename = "secure_data.txt";
	char *exec_file = "./test_exec";

	//READ TEST
	printf("Guest trying to READ secure_data.txt...\n");
	if (check_permission(username, GUEST_R)) {
		int fd = open(filename, O_RDONLY);
		if (fd>=0) {
			char buffer[100];
			read(fd, buffer, sizeof(buffer));
			close(fd);
			printf("Guest successfully READ secure_data.txt: %s\n", buffer);
		} else {
			printf("Error opening secure_data.txt\n");
		}
	} else {
		printf("Access denied for Guest to READ secure_data.txt\n");
	}

	//WRITE TEST
	printf("Guest trying to WRITE secure_data.txt...\n");
	if (check_permission(username, GUEST_W)) {
		int fd = open(filename, O_WRONLY);
		if (fd>=0) {
			write(fd, "Guest was here!\n", 16);
			close(fd);
			printf("Guest successfully WROTE secure_data.txt\n");
		} else {
			printf("Error opening secure_data.txt\n");
		}
	} else {
		printf("Access denied for Guest to WRITE secure_data.txt\n");
	}

	//EXEC TEST
	printf("Guest trying to EXECUTE secure_data.txt...\n");
	if (check_permission(username, GUEST_X)) {
		execl(exec_file, exec_file, NULL);
		printf("Guest successfully EXECUTE test_exec\n");
	} else {
		printf("Access denied for Guest to EXECUTE test_exec\n");
	}

	//yield to user
	while (1) {
		yield();
	}

	return 0;
}
