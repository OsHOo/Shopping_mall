#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "product.h"
void getProdData(PROD *head_pro, PROD *tail_pro)
{
	FILE *fp;
	char *dir;
	PROD tmp;
	tmp.LINK = NULL;
	tmp.prod_name = (char *)malloc(sizeof(char)*100);
	tmp.prod_category = (char *)malloc(sizeof(char)*100);
	dir = (char *)malloc(sizeof(char) *100);
	fp = fopen("product.csv","r");
	fgets(dir,100,fp);
	while(1)
	{
		if(fscanf(fp,"%d%*c%[^,]%*c%[^,]%*c%d%*c%d\n",&tmp.prod_num,tmp.prod_name,tmp.prod_category,&tmp.prod_price,&tmp.prod_status) == EOF)
			break;
		AddProdFirst(head_pro,tail_pro, &tmp);
	}
	fclose(fp);
	free(dir);
}
void AddProdFirst(PROD *head_pro, PROD *tail_pro, PROD *tmp)
{
	PROD *NewProd = (PROD *)malloc(sizeof(PROD));
	NewProd->prod_name = (char *)malloc(sizeof(char)*100);
	NewProd->prod_category = (char *)malloc(sizeof(char)*100);
	NewProd->LINK = NULL;
	strcpy(NewProd->prod_name, tmp->prod_name);
	strcpy(NewProd->prod_category,tmp->prod_category);
	NewProd->prod_num = tmp->prod_num;
	NewProd->prod_price = tmp->prod_price;
	NewProd->prod_status = tmp->prod_status;
	if(head_pro -> LINK == NULL)
	{
		head_pro->LINK = NewProd;
		NewProd->LINK = NULL;
		tail_pro -> LINK = NewProd;
	}
	else
	{
		NewProd -> LINK = head_pro->LINK;
		head_pro->LINK = NewProd;
	}
}
int prodSearch(PROD *pro, PROD *head_pro, PROD *tail_pro, HIST *head_his, USER *user, HIST *tail_his, USER *head)
{
	int select, flag=0;
	char *code;
	char tmp;
	PROD *curr;
	code = (char *)malloc(sizeof(char)*100);
	system("clear");
	while(1)
	{
		curr = head_pro -> LINK;
		printf("<Searching Product>\n");
		printf("1. Searching for name.\n");
		printf("2. Searching for category.\n");
		printf("3. Searching for all products.\n");
		printf("0. Go back to previous page.\n");
		printf("Choose : ");
		scanf("%d",&select);
		getchar();
		if(select != 0)
		{
			if(select == 3)
			{
				printProdData(head_pro);
				continue;
			}
			printf("Searching : ");
			scanf("%[^\n]",code);
			getchar();
			printf("====================================\n");
			if(select == 1)
			{
			 	while(curr != NULL)
				{
					if(strcmp(code,curr->prod_name) == 0)
						break;
					curr = curr->LINK;
				}
				if(curr != NULL)
				{
					printf("Product Number : %d\n",curr->prod_num);
					printf("Product Name : %s\n",curr->prod_name);
					printf("Product Category : %s\n",curr->prod_category);
					printf("Product Price : %d\n",curr->prod_price);
					printf("Product Status : %d\n",curr->prod_status);
					printf("===========================================\n");
					pro->prod_num = curr->prod_num;
					strcpy(pro->prod_name,curr->prod_name);
					strcpy(pro->prod_category,curr->prod_category);
					pro->prod_price = curr->prod_price;
					pro->prod_status = curr->prod_status;
					if(user->status == 1 && pro->prod_status == 1)
					{
						printf("Do you Want to Buy this?(y/n) : ");
						scanf("%c",&tmp);
						getchar();
						if(tmp == 'y' || tmp == 'Y')
						{
							BuyProducts(user, pro, head_his, head_pro, tail_his);
							UpdateUserList(user,head);
						}
					}
				}
				else
				{
					printf("Product name : <%s> is not exists.\n", code);
					printf("========================================\n");
				}
			}
			else if(select == 2)
			{
				while(curr != NULL)
				{
					if(strcmp(code,curr->prod_category) == 0)
					{
						printf("Product Number : %d\n",curr->prod_num);
						printf("Product Name : %s\n",curr->prod_name);
						printf("Product Category : %s\n",curr->prod_category);
						printf("Product Price : %d\n",curr->prod_price);
						printf("Product Status : %d\n",curr->prod_status);
						printf("===========================================\n");
						flag = 1;
					}
					curr = curr->LINK;
				}
				if(flag == 0)
				{
					printf("Product name : <%s> is not exists.\n",code);
					printf("========================================\n");
				}
			}
		}
		else
		{
			system("clear");
			free(code);
			return -1;
		}
	}
	free(code);

}
void getHistData(HIST *head_his, HIST *tail_his)
{
	FILE *fp;
	HIST tmp;
	char *dir = (char *)malloc(sizeof(char)*100);
	tmp.LINK = NULL;
	fp = fopen("history.csv","r");
	fgets(dir,100,fp);
	while(1)
	{
		if(fscanf(fp,"%d%*c%d%*c%d%*c%d\n",&tmp.order_num, &tmp.prod_num, &tmp.user_num,&tmp.deliver_status) == EOF)
			break;
		AddHistFirst(head_his,tail_his, &tmp);
	}
	fclose(fp);
	free(dir);
}
void AddHistFirst(HIST *head_his, HIST *tail_his, HIST *tmp)
{
	HIST *NewHist = (HIST *)malloc(sizeof(HIST));
	NewHist->LINK = NULL;
	NewHist->order_num = tmp->order_num;
	NewHist->prod_num = tmp->prod_num;
	NewHist->user_num = tmp->user_num;
	NewHist->deliver_status = tmp->deliver_status;

	if(head_his -> LINK == NULL)
	{
		head_his->LINK = NewHist;
		NewHist->LINK = NULL;
		tail_his -> LINK = NewHist;
	}
	else
	{
		NewHist -> LINK = head_his->LINK;
		head_his->LINK = NewHist;
	}
}
void ViewBuyHistory(USER *user, HIST *head_his, PROD *head_pro)
{
	system("clear");
	HIST *curr = (HIST *)malloc(sizeof(HIST));
	PROD *curr2 = (PROD *)malloc(sizeof(PROD));
	curr2->prod_name = (char *)malloc(sizeof(char)*100);
	curr = head_his->LINK;
	curr2 = head_pro->LINK;
	printf("<Buying History>\n");
	while(curr != NULL)
	{
		if(user->user_num == curr->user_num)
		{
			curr2 = head_pro->LINK;
			while(curr2 != NULL)
			{
				if(curr->prod_num == curr2->prod_num)
					break;
				curr2 = curr2->LINK;
			}

			printf("======================================\n");
			printf("Product name : %s\n",curr2->prod_name);
			printf("Delivery Tracking : %d\n",curr->deliver_status);
		}
		curr = curr->LINK;
	}
	printf("======================================\n");
	printf("Press Enter.");
	while(getchar() != '\n');
	return;
}

void printHistData(HIST *head_his)
{
	HIST *curr;
	curr = head_his->LINK;
	system("clear");
	printf("======================================\n");
	while (curr != NULL)
	{
		printf("주문번호 : %d\n", curr->order_num);
		printf("회원번호 : %d\n", curr->user_num);
		printf("상품번호 : %d\n", curr->prod_num);
		printf("배달상태 : %d\n", curr->deliver_status);
		curr = curr->LINK;
 		printf("======================================\n");
	}
	printf("PRESS ENTER");
	while(getchar() != '\n');
	return;
}
void printProdData(PROD *head_pro)
{
	PROD *curr;
	curr = head_pro->LINK;
	system("clear");
	printf("======================================\n");
	while(curr != NULL)
	{
		printf("제품이름 : %s\n",curr->prod_name);
		printf("제품카테고리 : %s\n",curr->prod_category);
		printf("제품 가격 : %d\n",curr->prod_price);
		printf("상품 상태 : %d\n",curr->prod_status);
		printf("======================================\n");

		curr = curr->LINK;
	}
	printf("PRESS ENTER");
	while(getchar() != '\n');
	return;
}
void BuyProducts(USER *user, PROD *pro, HIST *head_his, PROD *head_pro, HIST *tail_his)
{
	FILE *fp;
	HIST *tmp= (HIST *)malloc(sizeof(HIST));
	int line = 0;
	fp = fopen("history.csv","r");
	while(fscanf(fp,"%*[^\n]\n") != EOF)
		line++;
	fclose(fp);
	if(user->money - pro->prod_price < 0)
	{
		printf("You don't have enough money!\n");
		printf("Press Enter.");
		while(getchar() != '\n');
		return;
	}
	user->money -= pro->prod_price;	
	fp = fopen("history.csv","a+");
	fprintf(fp,"%d,%d,%d,0\n",line,pro->prod_num,user->user_num);
	fclose(fp);
	tmp->order_num = line;
	tmp->prod_num = pro->prod_num;
	tmp->user_num = user->user_num;
	tmp->deliver_status = 0;
	AddHistFirst(head_his, tail_his,tmp);
	free(tmp);
	return;
}
void ProdManager(PROD *head_pro, PROD *tail_pro)
{
	PROD *Newprod = (PROD *)malloc(sizeof(PROD));
	Newprod->prod_name = (char *)malloc(sizeof(char)*100);
	Newprod->prod_category = (char *)malloc(sizeof(char)*100);
	int select;
	system("clear");
	printf("<Product Manager>\n");
	printf("1. Register New Products.\n");
	printf("2. Delete Products.\n");
	printf("3. Edit Products Informaton.\n");
	printf("Choose : ");
	scanf("%d",&select);
	getchar();
	if(select == 1)
		ProdRegister(head_pro, tail_pro, Newprod);
	else if(select == 2)
		ProdDeleter(head_pro, Newprod);
	else if(select == 3)
		ProdEditer(head_pro, Newprod);
	return;
}
void ProdEditer(PROD *head_pro, PROD *pro)
{
	int select;
	PROD *curr;
	system("clear");
	printf("<Product Editer>\n");
	printf("Enter the Product Name : ");
	scanf("%[^\n]",pro->prod_name);
	getchar();
	curr = head_pro -> LINK;
	while(curr != NULL)
	{
		if(strcmp(curr->prod_name, pro->prod_name) == 0)
		{
			printf("What Information You Want to Edit?\n");
			printf("1. Product Category\n");
			printf("2. Product Price\n");
			printf("Choose : ");
			scanf("%d",&select);
			getchar();
/*			if(select == 1)
			{
				printf("Input New Name : ");
				scanf("%[^\n]",curr->prod_name);
				getchar();
				return;
			}
*/			if(select == 1)
			{
				printf("Input New Category : ");
				scanf("%[^\n]",curr->prod_category);
				getchar();
				return;
			}
			else if(select == 2)
			{
				printf("Input New Price : ");
				scanf("%d",&curr->prod_price);
				getchar();
				return;
			}
		}
		curr = curr->LINK;
	}
	printf("You Input Wrong Name. PRESS ENTER");
	while(getchar() != '\n');
	return;
}
void ProdDeleter(PROD *head_pro, PROD *pro)
{
	PROD *curr; 
	system("clear");
	printf("<Product Deleter>\n");
	printf("Enter the Product Name : ");
	scanf("%[^\n]",pro->prod_name);
	getchar();
	curr = head_pro -> LINK;
	while(curr != NULL)
	{
		if(strcmp(curr->prod_name, pro->prod_name) == 0)
		{
			curr->prod_status = -1;
			printf("Finished. PRESS ENTER.\n");
			getchar();
			return;
		}
		curr = curr->LINK;
	}
	printf("You Input Wrong Name. PRESS ENTER.");
	while(getchar() != '\n');
	return;

}
void ProdRegister(PROD *head_pro, PROD *tail_pro, PROD *pro)
{
	FILE *fp;
	PROD *curr = head_pro->LINK;
	int line=0;
	fp = fopen("product.csv","r");
	while(fscanf(fp,"%*[^\n]\n") != EOF)
			line++;
	system("clear");
	printf("<Product Register>\n");
	printf("Enter New Product Name : ");
	scanf("%[^\n]",pro->prod_name);
	getchar();
	while(curr != NULL)
	{
		if(strcmp(curr->prod_name, pro->prod_name) == 0)
		{
			printf("That product already exists!\n");
			printf("Press Enter");
			while(getchar() != '\n');
			return;
		}
		curr = curr->LINK;
	}
	printf("Enter New Product Category : ");
	scanf("%[^\n]",pro->prod_category);
	getchar();
	printf("Enter New Product Price : ");
	scanf("%d",&pro->prod_price);
	getchar();
	pro->prod_status = 1;
	pro->prod_num = line;
	AddProdFirst(head_pro, tail_pro, pro);
	printf("Finished. PRESS ENTER.");
	while(getchar() != '\n');
	return;
}
void WriteNewProdData(PROD *head_pro)
{
	FILE *fp;
	PROD *curr;
	curr = head_pro->LINK;
	fp = fopen("product.csv","w");
	fprintf(fp,"상품번호,상품명,카테고리,가격,상태\n");
	while(curr != NULL)
	{
		fprintf(fp,"%d,%s,%s,%d,%d\n",curr->prod_num,curr->prod_name,curr->prod_category,curr->prod_price,curr->prod_status);
		curr = curr->LINK;
	}
	fclose(fp);
	return;
}
void WriteNewHistData(HIST *head_his)
{
	FILE *fp;
	HIST *curr = head_his->LINK;
	fp = fopen("history.csv","w");
	fprintf(fp,"주문번호,상품번호,회원번호,배송현황\n");
	while(curr != NULL)
	{
		fprintf(fp,"%d,%d,%d,%d\n",curr->order_num,curr->prod_num,curr->user_num,curr->deliver_status);
		curr = curr->LINK;
	}
	fclose(fp);
}
void freeProdLists(PROD *head_pro)
{
	PROD *tmp, *curr;
	curr = head_pro->LINK;
	while(curr != NULL)
	{
		tmp = curr->LINK;
		free(curr->prod_name);
		free(curr->prod_category);
		free(curr);
		curr = tmp;
	}
	return;
}
void freeHistLists(HIST *head_his)
{
	HIST *tmp, *curr;
	curr = head_his->LINK;
	while(curr != NULL)
	{
		tmp = curr->LINK;
		free(curr);
		curr = tmp;
	}
	return;
}
void DeliverManager(HIST *head_his)
{
	int select = 3, tmp;
	HIST *curr;
	while(select != 0)
	{
		system("clear");
		printf("<Delivery Manager>\n");
		printf("1. View History.\n");
		printf("2. Edit Delivery Status.\n");
		printf("0. Go back to previous page.\n");
		printf("Choose : ");
		scanf("%d",&select);
		getchar();
		if(select == 1)
			printHistData(head_his);
		else if(select == 2)
		{
			printf("Input the Order num. :");
			scanf("%d",&tmp);
			getchar();
			for(curr=head_his->LINK;(curr->order_num != tmp) && (curr->LINK != NULL);curr=curr->LINK);
			if(curr->LINK == NULL && curr->order_num != tmp)
			{
				printf("There Are No Order_num <%d>\n",tmp);
				printf("PRESS ENTER");
				while(getchar() != '\n');
			}
			else
			{
				printf("============================================\n");
				printf("Current Deliver Status : %d\n",curr->deliver_status);
				printf("============================================\n");
				printf("AND NOW?\n");
				printf("0. 배송 준비\n");
				printf("1. 배송 중\n");
				printf("2. 배송 완료\n");
				printf("Choose(In Number): ");
				scanf("%d",&curr->deliver_status);
				getchar();
				printf("============================================\n");
				printf("Current Deliver Status : %d\n",curr->deliver_status);
				printf("============================================\n");
				printf("PRESS ENTER");
				while(getchar() != '\n');

			}

		}
	}
}
void ViewStatistics(PROD *head_pro, HIST *head_his)
{
	PROD *curr_pro = head_pro->LINK;
	HIST *curr_his = head_his->LINK;
	STAT *head = (STAT *)malloc(sizeof(STAT));
	STAT *curr;
	head->LINK = NULL;
	STAT *tmp = (STAT *)malloc(sizeof(STAT));
	tmp->prod_name = (char *)malloc(sizeof(char)*100);
	int line=1, temp;
	FILE *fp = fopen("history.csv","r");
	FILE *fp_pro = fopen("product.csv","r");
	int *amount;

	fscanf(fp,"%*[^\n]\n");
	fscanf(fp_pro,"%*[^\n]\n");

	while(fscanf(fp_pro,"%*[^\n]\n") != EOF)
		line++;

	amount = (int *)calloc(line+1,sizeof(int));
	while(curr_his != NULL)
	{
		if(fscanf(fp,"%*d%*c%d%*[^\n]\n",&temp) == EOF)
			break;
		*(amount+temp)+=1;
		curr_his = curr_his -> LINK;
	}
	printf("=========================================================\n");
	printf("<Product Statistics>\n");
	printf("상품이름\t판매량\t가격\n");
	while(curr_pro != NULL)
	{
		strcpy(tmp->prod_name,curr_pro->prod_name);
		tmp->sales_vol = *(amount+curr_pro->prod_num);
		tmp->prod_price = curr_pro->prod_price;
		AddSTATFirst(head, *tmp);
		curr_pro = curr_pro->LINK;
	}
	SortingSTAT(head);
	curr = head->LINK;
	while(curr != NULL)
	{
		printf("%-12s\t%-3d\t%-8d\n",curr->prod_name,curr->sales_vol,curr->prod_price);
		curr = curr->LINK;
	}
	printf("==========================================================\n");
	printf("PRESS ENTER");
	while(getchar() != '\n');
	fclose(fp);
	fclose(fp_pro);
	curr = head->LINK;
	while(curr != NULL)
	{
		tmp = curr->LINK;
		free(curr->prod_name);
		free(curr);
		curr = tmp;
	}
	free(tmp);
	free(head);
	free(amount);

	return;
}
void SortingSTAT(STAT *head)
{
	STAT *curr = head->LINK;
	STAT *curr2 = head->LINK;
	STAT *tmp = (STAT *)malloc(sizeof(STAT));
	tmp->prod_name = (char *)malloc(sizeof(char)*100);
	while(curr != NULL)
	{
		curr2 = head->LINK;
		while(curr2->LINK != NULL)
		{
			if(curr2->sales_vol < curr2->LINK->sales_vol)
			{
				tmp->sales_vol = curr2->sales_vol;
				tmp->prod_price = curr2->prod_price;
				strcpy(tmp->prod_name,curr2->prod_name);
				curr2->sales_vol = curr2->LINK->sales_vol;
				curr2->prod_price = curr2->LINK->prod_price;
				strcpy(curr2->prod_name,curr2->LINK->prod_name);
				curr2->LINK->sales_vol = tmp->sales_vol;
				curr2->LINK->prod_price = tmp->prod_price;
				strcpy(curr2->LINK->prod_name,tmp->prod_name);
			}
			curr2 = curr2->LINK;
		}
		curr = curr->LINK;
	}
	free(tmp->prod_name);
	free(tmp);
	return;
}
void AddSTATFirst(STAT *head, STAT tmp)
{
	STAT *NewNode = (STAT *)malloc(sizeof(STAT));
	NewNode -> prod_name = (char *)malloc(sizeof(char)*100);
	strcpy(NewNode->prod_name, tmp.prod_name);
	NewNode->sales_vol = tmp.sales_vol;
	NewNode->prod_price = tmp.prod_price;
	NewNode->LINK = NULL;
	if(head->LINK == NULL)
	{
		head->LINK = NewNode;
		NewNode->LINK = NULL;
	}
	else
	{
		NewNode->LINK = head->LINK;
		head->LINK = NewNode;
	}
	return;
}

