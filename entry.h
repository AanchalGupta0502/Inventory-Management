#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "item_masters.h"
#include "party_masters.h"
void fiprint();
void fiadd();
void fimod();
int fitemsearch(int);
void writeFinalInspLinkedList(char filename[], struct finode*);
struct finode* readFinalInspLinkedList(char filename[]);
void damageprint();
void damageadd();
void damagemod();
int ditemsearch(int);
void writeDamageLinkedList(char filename[], struct dnode*);
struct dnode* readDamageLinkedList(char filename[]);
void saleadd();
void saleprint();
int saleitemsearch(int);
void tableadd(struct bill *);
struct finode{
	int inspNo;
	int SNo;
	int itemcode;
	char itemname[100];
	int qty;
	char date[20];
	struct finode * loc;
}; 
struct dnode{
	int DamageNo;
	int SNo;
	int itemcode;
	char itemname[100];
	int qty;
	char date[20];
	struct dnode * loc;
};
struct snode{
	int inv_no;
	char invdate[20];
	char party[100];
	int total;
	int gst_per;
	int gst_val;
	int net;
	struct snode * loc;
};
struct bill{
	int inv_no;
		int sno;
		int itemcode;
		char itemname[100];
		int qty;
		int rate;
		int amt;
		struct bill * link;
	};
struct dnode *dstart=NULL;
struct finode *fistart=NULL;
struct snode *sstart=NULL;
struct bill *sbill=NULL;
final_inspection()
{ int ch;
	while(1){
		printf("\t\t\t-------------------\n");
		printf("\t\t\tFinal Inspection\n");
		printf("\t\t\t-------------------\n");
		printf("\t\t\t1.Add\n");
		printf("\t\t\t2. Modify\n");
		printf("\t\t\t3. Back\n");
		printf("\t\t\t4. exit\n");
		printf("\t\t\t5. print\n");
		printf("\t\t\tEnter choice");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				fiadd();
				break;
			case 2:
				fimod();
				break;
			case 3:
				return 0;
				break;
			case 4:
				exit(1);
				break;
			case 5:
				fiprint();
				break;
			default:
				printf("\t\t\tenter valid operation\n");
		}
	}
}
void removeFinalInspFileContents(const char *filename,struct finode* newnode) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "Couldn't open file: %s\n", filename);
        exit(1);
    }
	 while(newnode!=NULL)
    {
        fwrite(newnode, sizeof(struct finode), 1, file);
        newnode = newnode->loc;
    }
    
    if(fwrite == 0)
    {
           printf("Error While Writing\n");
    }
    fclose(file);
}
void fiadd(){
struct finode *ptr,*temp;
const char *a;
ptr=(struct finode *)malloc(sizeof(struct finode));
	printf("\t\t\t\tInspection No.:");
	scanf("%d",&ptr->inspNo);
	printf("\t\t\t\tItem code:");
	scanf("%d",&ptr->itemcode);
	printf("\t\t\t\tS.No");
	scanf("%d",&ptr->SNo);
	a=isearch(ptr->itemcode); //search the item code from item master
	if(a!="0"){
	printf("\t\t\t\titem name:%s\n",a); //fetch item name from item master if exist	
	strcpy(ptr->itemname,a);
	printf("\t\t\t\tquantity:");
	scanf("%d",&ptr->qty);
	printf("\t\t\t\tInspdate:");
	scanf("%s",&ptr->date);
	ptr->loc=NULL;
    if(fistart==NULL){
    	fistart=ptr;
    	writeFinalInspLinkedList("finalinspection.txt",fistart);
	}
	else{
		temp=fistart;
		while(temp->loc!=NULL){
			temp=temp->loc;
		}
		temp->loc=ptr;
	writeFinalInspLinkedList("finalinspection.txt",ptr);
	}
}
else{
	printf("\t\t\t\titem code doesn't exist in item master\n"); //else return back to main menu
	}
}
void fimod(){
int n1;
printf("\t\t\t\tenter Inspection No.:");
scanf("%d",&n1);
struct finode *newnode=readFinalInspLinkedList("finalinspection.txt");
struct finode *ptr=newnode;
if(newnode==NULL){
	printf("\t\t\t\tNo item to be modified...");
}
else{
	while(ptr->inspNo!=n1&&ptr!=NULL){
		ptr=ptr->loc;
}
	if(ptr->inspNo==n1){
	
	printf("\t\t\t\tEnter new values:\n");
	printf("\t\t\t\titem code:");
	scanf("%d",&ptr->itemcode);
	const char *a=isearch(ptr->itemcode); //search the item code from item master
		if(a!="0"){
		printf("\t\t\t\titem name:%s\n",a); //fetch item name from item master if exist	
		strcpy(ptr->itemname,a);
		printf("\t\t\t\tquantity");
		scanf("%d",&ptr->qty);
		printf("\t\t\t\tinspection date");
		scanf("%s",&ptr->date);
		removeFinalInspFileContents("finalinspection.txt",newnode);
		}
		else{
		printf("\t\t\t\titem code doesn't exist\n");
		}
	}
	else
	{
		printf("\t\t\t\tnot found the inspection number..");
	}
}
}
int fitemsearch(int key){
	int qty=0;
	struct finode *temp=readFinalInspLinkedList("finalinspection.txt");
	while(temp!=NULL){
		if(temp->itemcode==key){
			qty+=temp->qty;
		}
		temp=temp->loc;
	}
	return qty;
}
void writeFinalInspLinkedList(char filename[], finode* head){
    FILE* file;
    file = fopen (filename, "ab");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    fwrite(head, sizeof(struct finode), 1, file);
    if(fwrite == 0)
    {
           printf("Error While Writing\n");
    }

    fclose(file);
    
}
struct finode* readFinalInspLinkedList( char filename[]){
    
    struct finode* temp = (struct finode *)malloc(sizeof(struct finode));;
    struct finode* head; // points to the first node of the linked list in the file
    struct finode* last; // points to the last node of the linked list in the file
    last = head = NULL;
    
    FILE* file;
    file = fopen (filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        return 0;
    }
    
    // reading nodes from the file
    // nodes are read in the same order as they were stored
    // we are using the data stored in the file to create a new linked list
    while(fread(temp, sizeof(struct finode), 1, file))
    {
        
        if(head==NULL)
        {
            head = last = (struct finode *)malloc(sizeof(struct finode));
        }
        else
        {
            last->loc = (struct finode *)malloc(sizeof(struct finode));
            last = last->loc;
        }
        last->inspNo = temp->inspNo;
        strcpy(last->itemname, temp->itemname);
        last->itemcode=temp->itemcode;
        strcpy(last->date, temp->date);
        last->qty=temp->qty;
        last->SNo=temp->SNo;
        last->loc = NULL;
        
    }
    
    fclose(file);
    
    return head;
    
}
void fiprint(){
	struct finode *ptr=readFinalInspLinkedList("finalinspection.txt");
    while(ptr!=NULL)
	{  	printf("\t\t\t\t-------------------\n");
    	printf("\t\t\t\tInspNo:%d\n",ptr->inspNo);
    	printf("\t\t\t\tItem Code:%d\n",ptr->itemcode);
    	printf("\t\t\t\tItem Name:%s\n",ptr->itemname);
    	printf("\t\t\t\tDate:%s\n",ptr->date);
    	printf("\t\t\t\tQty:%d\n",ptr->qty);
    	printf("\t\t\t\t-------------------\n");
    	ptr=ptr->loc;
	}
} 
////DAMAGE function
damage(){
	int ch;
	while(1){
		printf("\t\t\t-------------------\n");
		printf("\t\t\tDamage\n");
		printf("\t\t\t-------------------\n");
		printf("\t\t\t1.Add\n");
		printf("\t\t\t2. Modify\n");
		printf("\t\t\t3. Back\n");
		printf("\t\t\t4. exit\n");
		printf("\t\t\t5. print\n");
		printf("\t\t\tEnter choice");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				damageadd();
				break;
			case 2:
				damagemod();
				break;
			case 3:
				return 0;
				break;
			case 4:
				exit(1);
				break;
			case 5:
				damageprint();
				break;
			default:
				printf("\t\t\tenter valid operation\n");
		}
	}
}
void damageprint(){
	struct dnode *newnode=readDamageLinkedList("damage.txt");
    struct dnode *ptr=newnode;
    while(ptr!=NULL)
	{   printf("\t\t\t\t-------------------\n");
    	printf("\t\t\t\tDamageNo:%d\n",ptr->DamageNo);
    	printf("\t\t\t\tSNo:%d\n",ptr->SNo);
    	printf("\t\t\t\tItem Code:%d\n",ptr->itemcode);
		printf("\t\t\t\tItem Name:%s\n",ptr->itemname);
    	printf("\t\t\t\tDate:%s\n",ptr->date);
		printf("\t\t\t\tQuantity:%d\n",ptr->qty);
    	printf("\t\t\t\t-------------------\n");
		ptr=ptr->loc;
	}
}
void damageadd(){
struct dnode *ptr,*temp;
const char *a;
ptr=(struct dnode *)malloc(sizeof(struct dnode));
	printf("\t\t\t\tDamage No.");
	scanf("%d",&ptr->DamageNo);
	printf("\t\t\t\tItem code:");
	scanf("%d",&ptr->itemcode);
	a=isearch(ptr->itemcode); //search the item code from item master
	if(a!="0"){
	strcpy(ptr->itemname,a);
	printf("\t\t\t\tItem name:%s",a);
	printf("\t\t\t\tquantity:");
	scanf("%d",&ptr->qty);
	printf("\t\t\t\tDamage date:");
	scanf("%s",&ptr->date);
	printf("\t\t\t\tS.No");
	scanf("%d",&ptr->SNo);
	ptr->loc=NULL;
	    if(dstart==NULL){
	    	dstart=ptr;
	    	writeDamageLinkedList("damage.txt",dstart);
		}
		else{
			temp=dstart;
			while(temp->loc!=NULL){
				temp=temp->loc;
			}
			temp->loc=ptr;
			writeDamageLinkedList("damage.txt",ptr);
		}
	}
	else{
	printf("\t\t\t\titem code doesn't exist\n"); //else return back to main menu
	}
}
void removeDamageFileContents(const char *filename,struct dnode* newnode) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "Couldn't open file: %s\n", filename);
        exit(1);
    }
	 while(newnode!=NULL)
    {
        fwrite(newnode, sizeof(struct dnode), 1, file);
        newnode = newnode->loc;
    }
    
    if(fwrite==0)
    {
           printf("Error While Writing\n");
    }
    fclose(file);
}
void damagemod(){
int n1;
printf("\t\t\t\tenter Damage No.:");
scanf("%d",&n1);
struct dnode *ptr,*newnode;
newnode=readDamageLinkedList("damage.txt");
ptr=newnode;
if(newnode==NULL){
	printf("\t\t\t\tNo item to be modified...");
}
else{
	while(ptr->DamageNo!=n1&&ptr!=NULL){
		ptr=ptr->loc;
	}
	if(ptr->DamageNo==n1){
	
	printf("\t\t\t\tEnter new values:\n");
	printf("\t\t\t\titem code:");
	scanf("%d",&ptr->itemcode);
	const char *a=isearch(ptr->itemcode);
		if(a!="0"){
		printf("\t\t\t\titem name:%s\n",a); //fetch item name from item master if exist	
		strcpy(ptr->itemname,a);
		printf("\t\t\t\tquantity:");
		scanf("%d",&ptr->qty);
		printf("\t\t\t\tinspection date:");
		scanf("%s",&ptr->date);
		removeDamageFileContents("damage.txt",newnode);
		}
		else{
			printf("item code doesn't exist\n");
		}
	}
	else
	{
		printf("\t\t\t\tnot found the damage number..\n");
	}
  }
}
int ditemsearch(int key){
	int qty=0;
	struct dnode *temp;
	temp=readDamageLinkedList("Damage.txt");
	while(temp!=NULL){
		if(temp->itemcode==key){
			qty+=temp->qty;
		}
		temp=temp->loc;
	}
	return qty;
}
void writeDamageLinkedList(char filename[], struct dnode* head){   
    FILE* file;
    file = fopen (filename, "ab");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
        fwrite(head, sizeof(struct dnode), 1, file);
    if(fwrite == 0)
    {
           printf("Error While Writing\n");
    }
    fclose(file);
}
struct dnode* readDamageLinkedList( char filename[]){
    
    struct dnode* temp = (struct dnode *)malloc(sizeof(struct dnode));;
    struct dnode* head; // points to the first node of the linked list in the file
    struct dnode* last; // points to the last node of the linked list in the file
    last = head = NULL;
    
    FILE* file;
    file = fopen (filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File+++'\n");
        return 0;
    }
    
    // reading nodes from the file
    // nodes are read in the same order as they were stored
    // we are using the data stored in the file to create a new linked list
    while(fread(temp, sizeof(struct dnode), 1, file))
    {
        
        if(head==NULL)
        {
            head = last = (struct dnode *)malloc(sizeof(struct dnode));
        }
        else
        {
            last->loc = (struct dnode *)malloc(sizeof(struct dnode));
            last = last->loc;
        }
        last->DamageNo = temp->DamageNo;
        strcpy(last->itemname, temp->itemname);
        last->itemcode=temp->itemcode;
        last->qty=temp->qty;
        last->SNo=temp->SNo;
        strcpy(last->date,temp->date);
        last->loc = NULL;   
    }
    fclose(file);
    return head;
}
//sale billing function
sale_billing(){
		int ch;
	while(1){
		printf("\t\t\t-------------------\n");
		printf("\t\t\tSale billing\n");
		printf("\t\t\t-------------------\n");
		printf("\t\t\t1.Add\n");
		printf("\t\t\t2. Back\n");
		printf("\t\t\t3. exit\n");
		printf("\t\t\t4. print\n");
		printf("\t\t\tEnter choice");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				saleadd();
				break;
			case 2:
				return 0;
				break;
			case 3:
				exit(1);
				break;
			case 4:
				saleprint();
				break;
			default:
				printf("\t\t\tenter valid operation\n");
		}
	}
}
void writeTableBillLinkedList(char filename[], bill* head){
    
    FILE* file;
    file = fopen (filename, "ab");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    	fwrite(head,sizeof(struct bill),1,file);   
    if(fwrite==0)
    {
           printf("Error While Writing\n");
    }
    fclose(file);
}
void tableadd(struct bill *s1){
   struct bill *t;
	if(sbill==NULL){
		sbill=s1;
		writeTableBillLinkedList("bill.txt",sbill); //storing bills in file
	}
	else{
		t=sbill;
		while(t->link!=NULL){
		t=t->link;
		}
		t->link=s1;
		writeTableBillLinkedList("bill.txt",s1); //storing bills in file
	}
}
void writeSalesLinkedList(char filename[], snode* head){
    FILE* file;
    file = fopen (filename, "ab");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    	fwrite(head,sizeof(struct snode),1,file);
	   
    if(fwrite == 0)
       {
        printf("Error While Writing\n");
    	}
    fclose(file);
}
struct snode* readSalesLinkedList( char filename[]){
    struct snode* temp = (struct snode *)malloc(sizeof(struct snode));;
    struct snode* head; // points to the first node of the linked list in the file
    struct snode* last; // points to the last node of the linked list in the file
    last = head = NULL;
    FILE* file;
    file = fopen (filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        return 0;
    }
    // reading nodes from the file
    // nodes are read in the same order as they were stored
    // we are using the data stored in the file to create a new linked list
    while(fread(temp, sizeof(struct snode), 1, file))
    {    
       if(head==NULL)
        {
            head = last = (struct snode *)malloc(sizeof(struct snode));
        }
        else
        {
            last->loc = (struct snode *)malloc(sizeof(struct snode));
            last = last->loc;
        }
        last->inv_no = temp->inv_no;
        strcpy(last->invdate, temp->invdate);
        last->total=temp->total;
        strcpy(last->party, temp->party);
        last->gst_per=temp->gst_per;
        last->gst_val=temp->gst_val;
        last->net=temp->net;
        last->loc = NULL;   
    }
    fclose(file);
    return head;
}
void saleadd(){
struct bill *s2;
struct snode *ptr,*temp;
int sum,i,a,key,n;
const char * b;
ptr=(struct snode *)malloc(sizeof(struct snode));
	printf("\t\t\t\tInvoice No.:");
	scanf("%d",&ptr->inv_no);
	printf("\t\t\t\tInvoice date:");
	scanf("%s",&ptr->invdate);
	printf("\t\t\t\tParty:");
	scanf("%s",&ptr->party);
	a=psearch(ptr->party); //search the party name from party master
	if(a==1)
	{ sum=0;
		printf("\t\t\t\t\tenter number of items:");
		scanf("%d",&n);
		for(i=0;i<n;i++){
				struct bill *s1;
				s1=(struct bill*)malloc(sizeof(struct bill));
				printf("\t\t\t\t\titem code:");
				scanf("%d",&key);
				b=isearch(key); //search the item code from item master
				if(b!="0")
				{	s1->inv_no=ptr->inv_no;
					s1->sno=i+1;		
					printf("\t\t\t\t\ts.no:%d",s1->sno);
					s1->itemcode=key;
					strcpy(s1->itemname,b);
					printf("\t\t\t\t\t\nquantity:");
					scanf("%d",&s1->qty);
					printf("\t\t\t\t\t\nrate:");
					scanf("%d",&s1->rate);
					s1->amt=s1->qty*s1->rate;
					printf("\t\t\t\t\t\namount:%d",s1->amt);
					s1->link=NULL;
					tableadd(s1);
					sum+=s1->amt;
				}
				else{
					i--;		//since that item code doesn't exist in it
				}
				printf("\n");
			}
			printf("\t\t\t\t-------------------------\n");
			ptr->total=sum;
			printf("\t\t\t\t\nTotal:%d",ptr->total);
			printf("\t\t\t\t\nGst %:");
			scanf("%d",&ptr->gst_per);
			ptr->gst_val=(ptr->gst_per*ptr->total)/100;
			printf("\t\t\t\t\nGst val:%d",ptr->gst_val);
			ptr->net=ptr->total+ptr->gst_val;
			printf("\n\t\t\t\tNet amt.:%d",ptr->net);
			ptr->loc=NULL;
		if(sstart==NULL){
		    sstart=ptr;
		     writeSalesLinkedList("Sales.txt",sstart);
		}
		else{
			temp=sstart;
			while(temp->loc!=NULL){
				temp=temp->loc;
				}
				temp->loc=ptr;
				writeSalesLinkedList("Sales.txt",ptr);
			}
	}
	else{
	printf("\t\t\t\tparty doesn't exist in party master\n"); //else return back to main menu
	}
}
struct bill* readBilllinkedList(char filename[],int invoice){
	struct bill *temp=(struct bill*)malloc(sizeof(struct bill));
	struct bill *head;
	struct bill *last;
	head=last=NULL;
	FILE *file;
	file=fopen(filename,"r");
	if(file==NULL){
		fprintf(stderr, "\nCouldn't Open File'\n");
        return 0;
	}
	while(fread(temp,sizeof(struct bill),1,file)==1){
		if(temp->inv_no==invoice){
			if(head==NULL){
				head=last=(struct bill*)malloc(sizeof(struct bill));
			}
			else{
				last->link=(struct bill *)malloc(sizeof(struct bill*));
				last=last->link;
			}
			last->inv_no=temp->inv_no;
			last->sno=temp->sno;
			last->itemcode=temp->itemcode;
			strcpy(last->itemname,temp->itemname);
			last->qty=temp->qty;
			last->rate=temp->rate;
			last->amt=temp->amt;
			last->link=NULL;
		}
	}		
	fclose(file);
	return head;
}
	

void saleprint(){
	struct snode *ptr;
    ptr=readSalesLinkedList("Sales.txt");
    struct bill *temp;
    while(ptr!=NULL){
	
    	printf("\t\t\tInvoice No.:%d\n",ptr->inv_no);
    	printf("\t\t\tInvoice Date:%s\n",ptr->invdate);
    	printf("\t\t\tParty:%s\n",ptr->party);
    	printf("\t\t\t-------------------------\n");
    	printf("\t\t\t--------------------------\n");
		temp=readBilllinkedList("bill.txt",ptr->inv_no);	
    	while(temp!=NULL)
    	{
    		printf("\t\t\t\tS.NO:%d\n",temp->sno);
    		printf("\t\t\t\tItem code:%d\n",temp->itemcode);
    		printf("\t\t\t\tItem Name:%s\n",temp->itemname);
    		printf("\t\t\t\tQty:%d\n",temp->qty);
    		printf("\t\t\t\tRate:%d\n",temp->rate);
    		printf("\t\t\t\tAmt:%d\n",temp->amt);
    		printf("\t\t\t\t-----------------\n");
    		temp=temp->link;
    	}
		printf("\t\t\t-------------------------\n");
		printf("\t\t\t Total:%d\n",ptr->total);
		printf("\t\t\t Gst percentage%:%d%\n",ptr->gst_per);
		printf("\t\t\t Gst Amount:%d\n",ptr->gst_val);
		printf("\t\t\t--------------------------\n");
		printf("\t\t\tNet amount:%d\n",ptr->net);	
    	ptr=ptr->loc;
    	printf("\t\t\t***********************************\n");
		printf("\t\t\t***********************************\n");
	}
}
int saleitemsearch(int key){
	struct snode *s1;
	s1=readSalesLinkedList("Sales.txt");
	struct bill *t;
	int qty=0;
	while(s1!=NULL){
		t=readBilllinkedList("bill.txt",s1->inv_no);
		while(t!=NULL){
			if(t->itemcode==key){
				qty+=t->qty;
			}
			t=t->link;
		}
		s1=s1->loc;
	}
	return qty;
}

