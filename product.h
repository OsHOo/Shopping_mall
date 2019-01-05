#ifndef PRODUCT
#define PRODUCT
typedef struct _PRODUCT_
{
	int prod_num;
	char *prod_name;
	char *prod_category;
	int prod_price;
	int prod_status;
	struct _PRODUCT_ *LINK;
}PROD;
typedef struct _HISTORY_
{
	struct _HISTORY_ *LINK;
	int order_num;
	int prod_num;
	int user_num;
	int deliver_status;

}HIST;
typedef struct _STAT_
{
	char *prod_name;
	int sales_vol;
	int prod_price;
	struct _STAT_ *LINK;
}STAT;
void getProdData(PROD *head_pro,PROD *tail_pro);//Make product Linkedlist by reading data from product.csv.
void getHistData(HIST *head_his,HIST *tail_his);//Make history Linkedlist by reading data from history.csv. 
void AddProdFirst(PROD *head_pro,PROD *tail_pro, PROD *tmp);//Add new product data infront of product linkedlist.
void AddHistFirst(HIST *head_his,HIST *tail_his, HIST *tmp);//Add new history data infornt of history linkedlist.
void ViewBuyHistory(USER *user,HIST *head_his, PROD *head_pro);//View products that user bought.
int prodSearch(PROD *pro, PROD *head_pro, PROD *tail_pro, HIST *head_his, USER *user, HIST *tail_his, USER *head);//Do the product search. You can choose name or category for searching option.
void printHistData(HIST *head_his);//Print History data.
void printProdData(PROD *head_pro);//Print every product linked list.
void BuyProducts(USER *user, PROD *pro, HIST *head_his, PROD *head_pro, HIST *tail_his);//Do every buying process.
void ProdManager(PROD *head_pro, PROD *tail_pro);//It registers,edits,deletes products.
void ProdRegister(PROD *head_pro, PROD *tail_pro, PROD *pro);//Do product registering.
void ProdDeleter(PROD *head_pro, PROD *pro);//Do product deleting.
void ProdEditer(PROD *head_pro, PROD *pro);//Do product editing.
void WriteNewProdData(PROD *head_pro);//Write every new product data on csv file.
void freeProdLists(PROD *head_pro);//free every allocated product linked lists.
void freeHistLists(HIST *head_his);//free every allocated history linked lists.
void DeliverManager(HIST *head_his);//Edit the history data.
void WriteNewHistData(HIST *head_his);//Write every New history data on csv file.
void ViewStatistics(PROD *head_pro, HIST *head_his);//Print statistical values of products. The higher sales, the upper printing.
void AddSTATFirst(STAT *head, STAT tmp);//Add new data in front of the STAT linked list.
void SortingSTAT(STAT *head);//Sorting by sales volume of products.
#endif
