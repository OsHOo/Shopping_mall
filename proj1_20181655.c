#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"
#include "login.h"
#include "product.h"
int main()
{
	FILE *fp;
	int select = 0, select2 = 0;
	char tmp;
	USER *user = (USER *)malloc(sizeof(USER));
	USER *head = (USER *)malloc(sizeof(USER));
	USER *tail = (USER *)malloc(sizeof(USER));
	PROD *head_pro = (PROD *)malloc(sizeof(PROD));
	PROD *tail_pro = (PROD *)malloc(sizeof(PROD));
	PROD *pro = (PROD *)malloc(sizeof(PROD));
	HIST *head_his = (HIST *)malloc(sizeof(HIST));
	HIST *tail_his = (HIST *)malloc(sizeof(HIST));
	HIST *his = (HIST *)malloc(sizeof(HIST));
	ADMIN admin;
	head->LINK = NULL;
	head_pro -> LINK = NULL;
	head_his -> LINK = NULL;
	tail->LINK = NULL;
	tail_pro -> LINK = NULL;
	tail_his -> LINK = NULL;
	user->status = 0;
	admin.status = 0;
	pro->prod_name = (char *)malloc(sizeof(char)*100);
	pro->prod_category = (char *)malloc(sizeof(char)*100);
	user->name = (char *)malloc(100 * sizeof(char));
	user->password = (char *)malloc(100 * sizeof(char));
	user->ID = (char *)malloc(100 * sizeof(char));
	user->address = (char *)malloc(100 * sizeof(char));
	admin.ID = (char *)malloc(100 * sizeof(char));
	admin.password = (char *)malloc(100 * sizeof(char));
	system("clear");
	if (fopen("customer.csv", "r") == NULL)
	{
		printf("4\n");
		fp = fopen("customer.csv", "w");
		fprintf(fp, "¿¿¿¿,¿¿¿,¿¿¿¿,¿¿,¿¿,¿¿\n");
		fclose(fp);
	}
	else
	{
		getUserData(head, tail);
		getProdData(head_pro,tail_pro);
		getHistData(head_his,tail_his);
	}
	while (select != 5 && user->status == 0 && admin.status == 0)
	{
		system("clear");
		printf("Welcome to SG-Mall.\n");
		printf("1.User Login\n");
		printf("2.Register\n");
		printf("3.Product Searching\n");
		printf("4.Admin Login\n");
		printf("5.Exit\n");
		printf("Choose : ");
		scanf("%d",&select);
		getchar();
//		tmp = getch();
//		select = tmp - '0';
		rewind(stdin);
		if (select == 1)
		{
			login(user, head);
//			system("clear");
		}
		else if (select == 2)
		{
			user_register(user, head, tail);
//			system("clear");
		}
		else if (select == 3)
		{
			prodSearch(pro,head_pro,tail_pro, head_his, user, tail_his, head);
		}
		else if (select == 4)
		{
			admin_login(&admin);
//			system("clear");
		}
	}
	if (user->status == 1)
	{
		while(user->status == 1)
		{
			system("clear");
			printf("%s, Welcome.\n", user->name);
			printf("1. Editing User Information.\n");
			printf("2. Online ATM.\n");
			printf("3. Product Searching.\n");
			printf("4. View Purchase History & Delievery\n");
			printf("5. Logout & Exit.\n");
			printf("Choose : ");
			scanf("%d",&select2);
			getchar();
			if(select2 == 1)
				EditUserInfo(user,head);
			else if(select2 == 2)
				AccountManager(user,head);
			else if(select2 == 3)
				prodSearch(pro,head_pro,tail_pro, head_his, user, tail_his, head);
			else if(select2 == 4)
				ViewBuyHistory(user, head_his, head_pro);
			else if(select2 == 5)
				user->status = 0;
			UpdateUserList(user,head);
		}
	}
	else if (admin.status == 1)
	{
		while(admin.status == 1)
		{
			system("clear");
			printf("Admin Page.\n");
			printf("1. See User Information.\n");
			printf("2. Product Manager.\n");
			printf("3. See Product Information.\n");
			printf("4. See History Information.\n");
			printf("5. Delievery Manager.\n");
			printf("6. View Statistics\n");
			printf("7. Logout & Exit.\n");
			printf("Choose : ");
			scanf("%d",&select2);
			getchar();
			if(select2 == 1)
				printUserData(head);
			else if(select2 == 2)
				ProdManager(head_pro, tail_pro);
			else if(select2 == 3)
				printProdData(head_pro);
			else if(select2 == 4)
				printHistData(head_his);
			else if(select2 == 5)
				DeliverManager(head_his);
			else if(select2 == 6)
				ViewStatistics(head_pro, head_his);
			else if(select2 == 7)
				admin.status = 0;
		}
	}
	WriteNewUserData(head);
	WriteNewProdData(head_pro);
	WriteNewHistData(head_his);
	freeUserLists(head);
	freeProdLists(head_pro);
	freeHistLists(head_his);
	free(admin.password);
	free(admin.ID);
	free(user->address);
	free(user->ID);
	free(user->password);
	free(user->name);
	free(pro->prod_category);
	free(pro->prod_name);
	free(his);
	free(tail_his);
	free(head_his);
	free(pro);
	free(tail_pro);
	free(head_pro);
	free(tail);
	free(head);
	free(user);
	return 0;
}
