#ifndef USERS
#define USERS

typedef struct _USER
{
	struct _USER *LINK;
	char *name;
	char *ID;
	char *password;
	char *address;
	int money;
	int enrollStatus;
	int status;
	int user_num;
}USER;

void printUserData(USER *head);//Print the User Data from customer.csv.
void user_register(USER *user, USER *head, USER *tail);//Register function. New Data will save in customer.csv.
void getUserData(USER *head, USER *tail);//Make LinkedList about User data by reading data from customer.csv.
void AddUserFirst(USER *head, USER *tail, USER *tmp);//Add new user data in front of the user linkedlist.
void maskPass2(char *pwd);//Same function with maskPass in "login.h"
int getch2(void);//Same function with getch in "login.h"
void EditUserInfo(USER *user, USER *head);//Editing User data And update User Linkedlist.
void WriteNewUserData(USER *head);//Save user LinkedList in customer.csv.
void UpdateUserList(USER *user, USER *head);//Update User LinkedList.
void AccountManager(USER *user, USER *head);//Manage every users money.
void freeUserLists(USER *head);//free allocated user linkedlist 

#endif
