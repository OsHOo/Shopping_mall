#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termio.h>
#include "users.h"
#include "login.h"

int getch(void)
{
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag &= ~(ICANON | ECHO);
	*(buf.c_cc + VMIN) = 1;
	*(buf.c_cc + VTIME) = 0;

	tcsetattr(0, TCSAFLUSH, &buf);

	ch = getchar();

	tcsetattr(0, TCSAFLUSH, &save);

	return ch;
}
void admin_login(ADMIN *admin)
{
	int i = 0;
//	FILE *fp;
//	char *tmp_ID = (char *)malloc(sizeof(char) * 100);
//	char *tmp_pwd = (char *)malloc(sizeof(char) * 100);
	system("clear");
//	fp = fopen("admin.csv", "r");
	while (i<3)
	{
		printf("Admin Login Page\n");
		printf("ID : ");
		scanf("%s", admin->ID);
		getchar();
		printf("Password : ");
		maskPass(admin->password);
		if (strcmp("admin", admin->ID) == 0 && strcmp("password", admin->password) == 0)
		{
			admin->status = 1;
			return;
		}
		i++;
		printf("\nID or password are not matched\n");
	}
//	fclose(fp);
	printf("Try Again. Press Enter.\n");
	while(getchar() != '\n');

	return;
}
void maskPass(char *pwd)
{
	int i = 0;
	char tmp;
	while (1)
	{
		tmp = getch();
		if (tmp == '\n')
		{
			*(pwd + i) = '\0';
			break;
		}
		else
		{
			*(pwd + i) = tmp;
			printf("*");
			i++;
		}
	}
	return;
}
void login(USER *user, USER *head)
{
	FILE *fp;
	char *tmp_ID;
	char *tmp_pwd;
	char *dir;
	USER *curr;
	int tmp, i = 0, j = 0;
	dir = (char *)malloc(sizeof(char) * 100);
	tmp_ID = (char *)malloc(sizeof(char) * 50);
	tmp_pwd = (char *)malloc(sizeof(char) * 50);
	curr = (USER *)malloc(sizeof(USER));
	system("clear");
	while (j < 3)
	{
		curr = head -> LINK;
		printf("Enter your ID : ");
		scanf("%s", tmp_ID);
		getchar();
		printf("Enter your password : ");
		maskPass(tmp_pwd);
		fp = fopen("customer.csv", "r");
		fgets(dir, 100, fp);
		while(curr != NULL)
		{
			if(strcmp(curr->ID,tmp_ID) == 0 && strcmp(curr->password,tmp_pwd) == 0)
			{
				if(curr->enrollStatus == -1)
				{
					printf("\nThis ID is unregistered.\n");
					printf("PRESS ENTER");
					while(getchar() != '\n');
				}
					
				else
				{
					strcpy(user->ID ,curr->ID);
					strcpy(user->password , curr->password);
					strcpy(user->name , curr->name);
					strcpy(user->address, curr ->address);
					user->money = curr->money;
					user->enrollStatus = curr->enrollStatus;
					user->user_num = curr->user_num;
					user->status = 1;
					if(strcmp(user->ID, "admin") == 0)
						user->status = 2;
					free(tmp_ID);
					free(tmp_pwd);
				}
				return;
			}
			curr = curr->LINK;
		}

		printf("\nID and password are not matched.\n");
		j++;
		
		fclose(fp);
	}
	printf("login failed. Please check your ID and password.\n");
	printf("PRESS ENTER");
	while(getchar() != '\n');
	free(tmp_ID);
	free(tmp_pwd);
	return;
}
