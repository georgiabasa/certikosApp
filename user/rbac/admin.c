// ADMIN

#include <stdio.h>
#include <syscall.h>
#include "rbac.h"
#include "../../sys/preinit/dev/disk.h"


void process1() {
	printf("Process1 (Admin) started.\n");

	if (authenticate_user("admin", "adminpass")) {
        	int action = ACTION_1;
        	execute_process(1, action);
    	} else {
        	printf("Authentication failed for Process1.\n");
    	}
}

void admin_disk_operations(void) {
	//pare ti xwritikotita tou diskou
	unsigned long long capacity = sys_disk_capacity();
	if (capacity == 0) {
		printf("Error: Could not retrieve disk capacity.\n");
		return;
	}

	printf("Disk Capacity: %llu sectors\n", capacity);

	//diavazoume enan tomea tou diskou
	unsigned char buffer[512]; //upothetw oti enas tomeas einai 512 bytes
	unsigned long long lba = 0; //LBA tou tomea pou thelw na diabasw
	unsigned int nsectors = 1; //diabazw 1 tomea

	int result = sys_disk_read(lba, nsectors, buffer);
	if (result != 0) {
		printf("Error: Disk read failed with code %d\n", result);
		return;
	}

	printf("Disk Read Successful: First few bytes: ");
	int i = 0;
	for (i=0; i<16; i++) { //ektupwse ta prwta 16 bytes
		printf("%02x ", buffer[i]);
	}
	printf("\n");
}

void check_disk_status(void) {
    unsigned long long capacity = sys_disk_capacity();
    if (capacity == 0) {
        printf("No disk found or disk initialization failed.\n");
    } else {
        printf("Disk detected with capacity: %llu sectors.\n", capacity);
    }
}

int qemu_read(void *buf, size_t size) {
	printf("qemu read\n");

	return 0;
}

int qemu_write(void *buf, size_t size) {
	printf("qemu write\n");

	return 0;
}

int qemu_poll_complete(void) {
	printf("qemu poll complete\n");

	return 1;
}

int main
(int argc, char **argv) {
	
	init_rbac() ;

	print_users();

	add_user(1, "admin", "adminpass", ROLE_ADMIN);
	add_user(2, "user1", "user1pass", ROLE_USER);
	add_user(3, "user2", "user2pass", ROLE_USER);
	add_user(4, "guest1", "guest1pass", ROLE_GUEST);
	add_user(5, "guest2", "guest2pass", ROLE_GUEST);
	
	process1();

	print_users();

	yield();
	
	printf("Admin again!!\n");
	print_users(); // uparxoun otan epistrepsei meta to yield akoma 
		       // enw stis upoloipes diergasies poy pane apo to yield den uparxoun users eggegramenoi

	printf("dokimi gia disk operations\n\n");
	//admin_disk_operations();
	//check_disk_status();

	disk_init(); //arxikopoiisi tou disk module

	/*struct disk_dev my_disk = {
		.dev = (void*)0xC0000000,
		.capacity = 1024,
		.dma_read = qemu_read,
		.dma_write =  qemu_write,
		.poll_complete = qemu_poll_complete
	};*/

	//disk_add_device(&my_disk); //prosthiki diskou sto sustima

	struct disk_dev *dev = disk_get_dev(0); //pare ton prwto disko
	if (dev) {
		size_t cap = disk_capacity(dev);
		printf("Disk capacity: %zu bytes\n", cap);
	} else {
		printf("No disk device found!\n");
	}

	return 0;
}
