// USER - READ, EXECUTE

#include <stdio.h>
//#include <string.h>
#include <syscall.h>
#include "roles.h"

#define BUF_SIZE 51
#define VM_ID 1
#define TARGET_PROCESS 2

void execute_syscalls(const char* username);

int
main (int argc, char **argv)
{
	printf("[Process] Running Process-Level System Calls...\n");

	//ektelesi gia "user1"
	execute_syscalls("user1");

	printf("[Process] Yielding CPU to next process...\n");
	while (1) {
		yield(); //allagi diergasias
	}
	
	return 0;
}

void execute_syscalls(const char* username) {
	User* user = find_user(username);
	if (!user) {
		printf("[-] User %s not found!\n", username);
		return;
	}

	printf("[*] User: %s (Role: %d)\n", user->username, user->role);
	unsigned int buf[BUF_SIZE];

	//sys_disk_op
	if (can_execute(user->role, "sys_disk_op")) {
		printf("[+] Permission for sys_disk_op\n");
		int err = sys_disk_read(0, 1, buf);
		if (err) printf("[-] Disk read failed!\n");
		else printf("[+] Disk read successful.\n");
		log_action(user->username, "sys_disk_op", err == 0);
	} else {
		printf("[-] No permission for sys_disk_op!\n");
		log_action(user->username, "sys_disk_op", 0);
	}

	//sys_send
	if (can_execute(user->role, "sys_send")) {
		printf("[+] Permission for sys_send\n");
		int err = sys_send(TARGET_PROCESS, (unsigned int)buf, BUF_SIZE);
		if (err) printf("[-] Message sending failed!\n");
		else printf("[+] Message sent successfully.\n");
		log_action(user->username, "sys_send", err == 0);
	} else {
		printf("[-] No permission for sys_send!\n");
		log_action(user->username, "sys_send", 0);
	}

	//sys_hvm_run_vm
	if (can_execute(user->role, "sys_hvm_run_vm")) {
		printf("[+] Permission for sys_hvn_run_vm\n");
		int err = sys_hvm_run_vm(VM_ID);
		if (err) printf("[-] VM Start failed!\n");
		else printf("[+] VM Started successfully.\n");
		log_action(user->username, "sys_hvm_run_vm", err == 0);
	} else {
		printf("[-] No permission for sys_hvm_run_vm!\n");
		log_action(user->username, "sys_hvm_run_vm", 0);
	}
}
