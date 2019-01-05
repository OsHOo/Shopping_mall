#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termio.h>
#include "users.h"
int getch2(void)
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
void maskPass2(char *pwd)
{
	int i = 0;
	char tmp;
	while (1)
	{
		tmp = getch2();
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
void printUserData(USER *head)
{
	USER *curr;

	curr = head->LINK;
	system("clear");
	printf("======================================\n");
	while (curr != NULL)
	{
		printf("회원이름 : %s\n", curr->name);
		printf("회원 ID : %s\n",curr->ID);
		printf("주소 : %s\n",curr->address);
		printf("잔액 : %d\n",curr->money);
		printf("상태 : %d\n",curr->enrollStatus);
		printf("=======================================\n");
		curr = curr->LINK;
	}
	printf("PRESS ENTER");
	while(getchar() != '\n');
	return;
}
void getUserData(USER *head, USER *tail)
{
	FILE *fp;
	char *dir;
	USER tmp;
	tmp.LINK = NULL;
	tmp.ID = (char *)malloc(sizeof(char) * 100);
	tmp.password = (char *)malloc(sizeof(char) * 100);
	tmp.name = (char *)malloc(sizeof(char) * 100);
	tmp.address = (char *)malloc(sizeof(char) * 100);
	dir = (char *)malloc(sizeof(char) * 100);
	fp = fopen("customer.csv", "r");
	fgets(dir, 100, fp);
	while (1)
	{
		if (fscanf(fp, "%d%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d%*c%d\n",&(tmp.user_num), tmp.ID, tmp.password, tmp.name, tmp.address, &(tmp.money), &(tmp.enrollStatus)) == EOF)
			break;
		AddUserFirst(head, tail, &tmp);
	}
	fclose(fp);
	free(dir);
	free(tmp.ID);
	free(tmp.password);
	free(tmp.name);
	free(tmp.address);
	return;
}
void AddUserFirst(USER *head, USER *tail, USER *tmp)
{
	USER *NewUser = (USER *)malloc(sizeof(USER));
	NewUser->user_num = tmp->user_num;
	NewUser->name = (char *)malloc(100 * sizeof(char));
	NewUser->password = (char *)malloc(100 * sizeof(char));
	NewUser->ID = (char *)malloc(100 * sizeof(char));
	NewUser->address = (char *)malloc(100 * sizeof(char));
	NewUser->LINK = NULL;
	NewUser->money = tmp->money;
	NewUser->enrollStatus = tmp->enrollStatus;
	strcpy(NewUser->name, tmp->name);
	strcpy(NewUser->password, tmp->password);
	strcpy(NewUser->ID, tmp->ID);
	strcpy(NewUser->address, tmp->address);
	if (head->LINK == NULL)
	{
		head->LINK = NewUser;
		NewUser->LINK = NULL;
		tail->LINK = NewUser;
	}
	else
	{
		NewUser->LINK = head->LINK;
		head->LINK = NewUser;
	}
	return;
}
void user_register(USER *user, USER *head, USER *tail)
{
	FILE *fp, *fp1, *fp_a;
	char *tmp;
	char *dir;
	USER *curr;
	int i = 1, line,ttmp=0;
	dir = (char *)malloc(100 * sizeof(char));
	tmp = (char *)malloc(100 * sizeof(char));
	system("clear");
	printf("Your ID : ");
	scanf("%s", user->ID);
	getchar();
	fp = fopen("customer.csv", "a+");
	fseek(fp, 0L, SEEK_SET);
	while (1)
	{
		if (fscanf(fp, "%*[^,]%*c%[^,]%*[^\n]\n", dir) == EOF)
			break;
		if (strcmp(dir, user->ID) == 0)
		{
			printf("That ID had already been used.\nPress Enter\n");
			while(getchar() != '\n');
			return;
		}
	}
	i = 1;
	fclose(fp);
	printf("Your name : ");
	scanf("%s", user->name);
	getchar();
	printf("Your password : ");
	maskPass2(user->password);
	printf("\n");
	printf("password one more : ");
	maskPass2(tmp);
	printf("\n");
	while (strcmp(tmp, user->password) != 0)
	{
		if (i == 3)
		{
			printf("Check your password.\nPress Enter.\n");
			while(getchar() != '\n');
			return;
		}
		printf("Your password wrong. Try again.\n");
		printf("Your password : ");
		maskPass2(user->password);
		printf("\n");
		printf("password one more : ");
		maskPass2(tmp);
		printf("\n");
		i++;
	}
	printf("Your address : ");
	scanf("%[^\n]s", user->address);
	getchar();
	line = 1;
	fp1 = fopen("customer.csv", "r");
	fseek(fp1, 0L, SEEK_SET);
	while (1)
	{
		fgets(tmp, 100, fp1);
		if (fscanf(fp1, "%d,%*s,%*s,%*s,%*s,%*d,%*d\n", &ttmp) == EOF)
			break;
		line++;
	}
	user->user_num = line;
	user->money = 0;
	user->enrollStatus = 1;
	fclose(fp1);
	AddUserFirst(head,tail,user);
	fp_a = fopen("customer.csv", "a");
	fprintf(fp_a, "%d,%s,%s,%s,%s,0,1\n", user->user_num, user->ID, user->password, user->name, user->address);
	fclose(fp_a);
	free(tmp);
	free(dir);
}
void EditUserInfo(USER *user, USER *head)
{
	int select;
	char ttmp;
	char *tmp = (char *)malloc(sizeof(char));
	system("clear");
	printf("1. Change Password.\n");
	printf("2. Change Address.\n");
	printf("3. Change Name.\n");
	printf("4. Unregister.\n");
	printf("Choose : ");
	scanf("%d",&select);
	getchar();
	if(select != 4)
	{
		if(select == 1)
		{
			printf("Enter your New Password. : ");
			maskPass2(tmp);
			strcpy(user->password,tmp);
			printf("\n");
		}
		else if(select == 2)
		{
			printf("Enter your New Address. : ");
			scanf("%[^\n]",tmp);
			getchar();
			strcpy(user->address,tmp);
		}
		else if(select == 3)
		{
			printf("Enter your New Name. : ");
			scanf("%[^\n]",tmp);
			getchar();
			strcpy(user->name,tmp);
		}
		UpdateUserList(user,head);
		printf("Change Successfully!\n");
		printf("PRESS ENTER");
		while(getchar() != '\n');
	}
	else if(select == 4)
	{
		printf("Are you really want to unregister? You cannot register with Same ID if you unregister.(y/n)");
		scanf("%c",&ttmp);
		getchar();
		if(ttmp == 'y' || ttmp == 'Y')
		{
			user->enrollStatus = -1;
			user->status = 0;
			UpdateUserList(user,head);
			free(tmp);
			return;
		}
		else
		{
			free(tmp);
			return;
		}
	}
	free(tmp);
	return;

}
void WriteNewUserData(USER *head)
{
	FILE *fp;
	USER *curr;
	curr = head->LINK;
	fp = fopen("customer.csv","w");
	fprintf(fp,"회원번호,아이디,비밀번호,이름,주소,잔액,상태\n");
	while(curr != NULL)
	{
		fprintf(fp,"%d,%s,%s,%s,%s,%d,%d\n",curr->user_num,curr->ID,curr->password,curr->name,curr->address,curr->money,curr->enrollStatus);
		
		curr = curr->LINK;
	}
	fclose(fp);
	return;
			
}
void UpdateUserList(USER *user, USER *head)
{
	USER *curr= head->LINK;
	while(curr != NULL)
	{
		if(strcmp(user->ID, curr->ID) == 0)
		{
			strcpy(curr->name, user->name);
			strcpy(curr->password, user->password);
			strcpy(curr->address, user->address);
			curr->enrollStatus = user->enrollStatus;
			curr->money = user->money;
			curr->status = user->status;
			break;
		}
		curr = curr->LINK;
	}
}
void AccountManager(USER *user, USER *head)
{
	int select,tmp, MAX;
	USER *curr = head->LINK;
	system("clear");
	printf("<Online ATM>\n");
	printf("1. Deposit\n");
	printf("2. Withdraw\n");
	printf("3. Send to Other.\n");
	printf("0. Go back to previous page.\n");
	printf("Choose : ");
	scanf("%d",&select);
	getchar();
	MAX = user->money;
	printf("================================\n");
	if(select == 1)
	{
		printf("Your money : %d\n",MAX);
		printf("Input deposit money. : ");
		scanf("%d",&tmp);
		getchar();
		user->money += tmp;
		printf("Deposit Finish. Press Enter");
		while(getchar() != '\n');
		UpdateUserList(user,head);
		return;
	}
	else if(select == 2)
	{
		printf("Your money : %d\n",MAX);
		printf("Input withdraw money. : ");
		scanf("%d",&tmp);
		getchar();
		if(tmp>MAX)
		{
			printf("There isn't enough money.\n");
			printf("Press Enter");
			while(getchar() != '\n');

			return;
		}
		else
		{
			user->money -= tmp;
			printf("Withdraw Finish. Press Enter.");
			while(getchar() != '\n');
			UpdateUserList(user, head);
			return;
		}
	}
	else if(select == 3)
	{
		printf("Not Yet.\n");
		printf("Press Enter.");
		while(getchar() != '\n');
		return;
	}
}
void freeUserLists(USER *head)
{
	USER *tmp;
	USER *curr;
	curr = head->LINK;
	while(curr != NULL)
	{
		tmp = curr->LINK;
		free(curr->name);
		free(curr->ID);
		free(curr->password);
		free(curr->address);
		free(curr);
		curr = tmp;
	}
	return;
}
