/*
struct snode *readSNodeFromFile(FILE *file) {
    struct snode *head = NULL;  // Initialize the head of the linked list

    while (1) {
        struct snode *newSNode = (struct snode *)malloc(sizeof(struct snode));

        // Read snode information from file
        if (fscanf(file, "%d %s %s %d %d %d %d\n", &newSNode->inv_no, newSNode->invdate, newSNode->party, &newSNode->total, &newSNode->gst_per, &newSNode->gst_val, &newSNode->net) != 7) {
            free(newSNode);
			break;  // Break the loop if there are no more snodes to read
        }

        // Initialize bill1 to NULL
        newSNode->bill1 = NULL;

        // Read bill information from file
        struct bill *currentBill = NULL;
        struct bill *prevBill = NULL;
        while (1) {
            struct bill *newBill = (struct bill *)malloc(sizeof(struct bill));

            if (fscanf(file, "%d %d %s %d %d %d\n", &newBill->sno, &newBill->itemcode, newBill->itemname, &newBill->qty, &newBill->rate, &newBill->amt) != 6) {
                free(newBill);
                break;  // Break the inner loop if there are no more bills
            }

            newBill->link = NULL;

            if (prevBill == NULL) {
                newSNode->bill1 = newBill;
                prevBill = newBill;
            } else {
                prevBill->link = newBill;
                prevBill = newBill;
            }
        }

        // Link the new snode to the existing linked list
        newSNode->loc = head;
        head = newSNode;
    }

    return head;  // Return the head of the linked list
}
struct snode* SalesreadLinkedList(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    struct snode *head = readSNodeFromFile(file);
    fclose(file);
    return head;

}*/
/*
struct snode *readSNodeFromFile(FILE *file) {
    struct snode *newSNode = (struct snode *)malloc(sizeof(struct snode));
    
    // Read snode information from file
    if (fscanf(file, "%d %s %s %d %d %d %d\n", &newSNode->inv_no, newSNode->invdate, newSNode->party, &newSNode->total, &newSNode->gst_per, &newSNode->gst_val, &newSNode->net) != 7) {
        free(newSNode);
        return NULL;
    }

    // Initialize bill1 to NULL
    newSNode->bill1 = NULL;

    // Read bill information from file
    struct bill *currentBill = NULL;
    struct bill *prevBill = NULL;
    while (1) {
        struct bill *newBill = (struct bill *)malloc(sizeof(struct bill));

        if (fscanf(file, "%d %d %s %d %d %d\n", &newBill->sno, &newBill->itemcode, newBill->itemname, &newBill->qty, &newBill->rate, &newBill->amt) != 6) {
            free(newBill);
            break;
        }
        newBill->link = NULL;

        if (prevBill == NULL) {
            newSNode->bill1 = newBill;
            prevBill = newBill;
        } else {
            prevBill->link = newBill;
            prevBill = newBill;
        }
    }

    return newSNode;
}
struct snode* SalesreadLinkedList() {
    FILE *file = fopen("Sales.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    struct snode *head = NULL;  // Initialize the head of the linked list

    while (1) {
        struct snode *newSNode = readSNodeFromFile(file);	
        if (newSNode == NULL) {
            // If readSNodeFromFile returns NULL, it means there are no more snodes to read
            break;
        }

        // Link the new snode to the existing linked list
        newSNode->loc = head;
        head = newSNode;
    }

    fclose(file);

    // 'head' is the first snode 
    return head;
}

*/
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
		printf("\t\t\t\tenter number of items:");
		scanf("%d",&n);
		for(i=0;i<n;i++){
				struct bill *s1;
				s1=(struct bill*)malloc(sizeof(struct bill));
				printf("\t\t\t\titem code:");
				scanf("%d",&key);
				b=isearch(key); //search the item code from item master
				if(b!="0")
				{	s1->sno=i+1;		
					printf("\t\t\t\ts.no:%d",s1->sno);
					s1->itemcode=key;
					strcpy(s1->itemname,b);
					printf("\t\t\t\t\nquantity:");
					scanf("%d",&s1->qty);
					printf("\t\t\t\t\nrate:");
					scanf("%d",&s1->rate);
					s1->amt=s1->qty*s1->rate;
					printf("\t\t\t\t\namount:%d",s1->amt);
					s1->link=NULL;
					tableadd(s1);
					sum+=s1->amt;
				}
				else{
					i--;		//since that item code doesn't exist in it
				}
				printf("\n");
		   }
		   s2=sbill;
		 //  writeTableBillLinkedList("table.txt",sbill); //storing bills in file
		   sbill=NULL; ////for nesting purpose s2 is first added in sbill and then sbill is again set to null
			printf("\t\t\t\t-------------------------\n");
			ptr->bill1=s2;
			ptr->total=sum;
			printf("\t\t\t\t\nTotal:%d",ptr->total);
			printf("\t\t\t\t\nGst %:");
			scanf("%d",&ptr->gst_per);
			ptr->gst_val=(ptr->gst_per*ptr->total)/100;
			printf("\t\t\t\t\nGst val:%d",ptr->gst_val);
			ptr->net=ptr->total+ptr->gst_val;
			printf("\nNet amt.:%d",ptr->net);
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
struct snode{
	int inv_no;
	char invdate[20];
	char party[100];
    struct bill * bill1;
	int total;
	int gst_per;
	int gst_val;
	int net;
	struct snode * loc;
};
void saleprint(){
	struct snode *ptr;
    ptr=SalesreadLinkedList("Sales.txt");
    struct bill *temp;
    while(ptr!=NULL){
	
    	printf("\t\t\t\tInvoice No.:%d\n",ptr->inv_no);
    	printf("\t\t\t\tInvoice Date:%s\n",ptr->invdate);
    	printf("\t\t\t\tParty:%s\n",ptr->party);
    	printf("\t\t\t\t-----------------\n");
    	printf("\t\t\t\t-----------------\n");
    	printf("\t\t\t\t-----------------\n");
		temp=ptr->bill1;	
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
    	printf("\t\t\t\t-----------------\n");
		printf("\t\t\t\t-----------------\n");
		printf("\t\t\t\t Total:%d\n",ptr->total);
		printf("\t\t\t\t Gst percentage%:%d\n",ptr->gst_per);
		printf("\t\t\t\t Gst Amount:%d\n",ptr->gst_val);
		printf("\t\t\t\t-----------------\n");
		printf("\t\t\t\tNet amount:%d\n",ptr->net);	
    	ptr=ptr->loc;
    	printf("\t\t\t\t***************************\n");
	}
	printf("erroerror!!!!!\n");
}
