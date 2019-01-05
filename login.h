#ifndef LOGIN
#define LOGIN

typedef struct _ADMIN
{
	char *ID;
	char *password;
	int status;
}ADMIN;

void admin_login(ADMIN *admin);//ADMIN LOGIN function
int getch(void);//Same as func 'getch()' in <conio.h>
void login(USER *user, USER *head);//USER LOGIN function
void maskPass(char *pwd);//Additional function which change 1234 to **** when input password

#endif
