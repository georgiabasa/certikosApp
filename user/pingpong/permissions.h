//permissions.h
#ifndef PERMISSIONS_H
#define PERMISSIONS_H

//9-bit permission masks
#define ADMIN_R 0b100000000
#define ADMIN_W 0b010000000
#define ADMIN_X 0b001000000
#define USER_R  0b000100000
#define USER_W  0b000010000
#define USER_X  0b000001000
#define GUEST_R 0b000000100
#define GUEST_W 0b000000010
#define GUEST_X 0b000000001

typedef struct {
	char *username;
	int permissions;
} User;

static User users[] = {
	{"admin", ADMIN_R | ADMIN_W | ADMIN_X},
	{"user", USER_R | USER_X},
	{"guest", GUEST_R}
};

//sunartisi gia elegxo an kapoio role exei ena dikaiwma
static inline int check_permission(char *username, int action) {
	for (int i=0; i < sizeof(users) / sizeof(users[0]); i++) {
		if (strcmp(users[i].username, username) == 0 {
			return (users[i].permissions & action) != 0;
		}
	}
	
	return 0;
}

#endif //PERMISSIONS_H
