#include<stdio.h>
#include<stdlib.h>
#include "entry.h"
#include<time.h> 
struct report{
	int itemcode;
	int stock;
	char itemname[100];
	struct report *loc;
};
struct report *srep=NULL;
void masters();
void entry();
void report();
void masters();
void party_master();
void item_master();
void reportadd(struct report*);
void reportprint();
int main()
{
	while(1){
		int ch;
		printf("INVENTORY MANAGEMENT SYSTEM\n");
		printf("----------------------\n");
		printf("Main Menu:\n");
		printf("--------------------\n");
		printf("1.Entry\n");
		printf("2.Report\n");
		printf("3.Masters\n");
		printf("4.Exit\n");
		printf("Enter your choice:");
		scanf("%d",&ch);
        switch(ch){
        	case 1:
        		entry();
        		break;
        	case 2:
        		report();
        		break;
        	case 3:
        		masters();
        		break;
        	case 4:
        		exit(1);
        		break;
        	default:
        		printf("Enter valid choice....\n");
		}
	}
}
void entry(){
	while(1){
		int ch;
		printf("\t-------------------\n");
		printf("\tEntry\n");
		printf("\t--------------------\n");
		printf("\t1.Final inspection\n");
		printf("\t2.Sale- Billing\n");
		printf("\t3. Damage scrap\n");
		printf("\t4. back\n");
		printf("\t5. exit\n");
		printf("\tenter choice");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				final_inspection();
				break;
			case 2:
				sale_billing();
				break;
			case 3:
				damage();
				break;
			case 4:
				main();
				break;
			case 5:
				exit(1);
				break;
			default:
				printf("\tenter valid choice\n");
		}
	}
}
void masters(){
	while(1){
		int ch;
		printf("\t----------------------\n");
		printf("\tMasters\n");
		printf("\t----------------------\n");
		printf("\t 1.Item Master\n");
		printf("\t 2.Party master\n");
		printf("\t 3.Back to main menu\n");
		printf("\t 4.Exit\n");
		printf("\t Enter choice:");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				item_master();
				break;
			case 2:
				party_master();
				break;
			case 3:
				main();
				break;
			case 4:
				exit(1);
				break;
			default:
				printf("\tenter valid choice!\n");						
		}
	}
}
void item_master(){
	int ch;
	while(1){
printf("\t\t-----------------\n");
printf("\t\tItem Master\n");
printf("\t\t-----------------\n");
printf("\t\t1.add item\n");
printf("\t\t2.modify item\n");
printf("\t\t3. delete item\n");
printf("\t\t4.back\n");
printf("\t\t5. exit\n");
printf("\t\t6. print\n");
printf("\t\tenter choice:");
scanf("%d",&ch);
switch(ch){
	case 1:
		add();
		break;
	case 2:
		modify();
		break;
	case 3:
		del();
		break;
	case 4:
		return;
	case 5:
		exit(1);
	case 6:
		print();
		break;
	default:
		printf("\t\tenter valid choice\n");	
}
}
}
void party_master(){
	int ch;
	while(1){
printf("\t\t---------------\n");
printf("\t\tParty Master\n");
printf("\t\t----------------\n");
printf("\t\t1.add item\n");
printf("\t\t2.modify item\n");
printf("\t\tt3. delete item\n");
printf("\t\t4.back\n");
printf("\t\t5. exit\n");
printf("\t\t6. print\n");
printf("\t\tenter choice:");
scanf("%d",&ch);
switch(ch){
	case 1:
		p_add();
		break;
	case 2:
		p_modify();
		break;
	case 3:
		p_del();
		break;
	case 4:
		return;
	case 5:
		exit(1);
	case 6:
		m_print();
		break;
	default:
		printf("\t\tenter valid choice\n");	
}
}
}
void writeReportLinkedList(char filename[], struct report* head){
    FILE* file;
    file = fopen (filename, "ab");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File...'\n");
        exit (1);
    }
        fwrite(head, sizeof(struct report), 1, file);
    
    if(fwrite == 0)
    {
           printf("Error While Writing\n");
    }
    fclose(file);
}
struct report* readReportLinkedList( char filename[]){
    struct report* temp = (struct report *)malloc(sizeof(struct report));;
    struct report* head; // points to the first node of the linked list in the file
    struct report* last; // points to the last node of the linked list in the file
    last = head = NULL;
    
    FILE* file;
    file = fopen (filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File11111'\n");
        return 0;
    }
    // reading nodes from the file
    // nodes are read in the same order as they were stored
    // we are using the data stored in the file to create a new linked list
    while(fread(temp, sizeof(struct report), 1, file))
    {
         if(head==NULL)
        {
            head = last = (struct report *)malloc(sizeof(struct report));
        }
        else
        {
            last->loc = (struct report *)malloc(sizeof(struct report));
            last = last->loc;
        }
        last->itemcode = temp->itemcode;
        strcpy(last->itemname, temp->itemname);
        last->stock=temp->stock;
        last->loc = NULL;      
    }
    fclose(file);
    return head;
}
void reportadd(struct report* temp){
    struct report *s1;
	if(srep==NULL){
		srep=temp;
		writeReportLinkedList("Report.txt",srep);
	}
	else{
		s1=srep;
		while(s1->loc!=NULL){
			s1=s1->loc;
		}
		s1->loc=temp;
		writeReportLinkedList("Report.txt",temp);
	}
}
void reportprint(){
	struct report *temp;
	temp=readReportLinkedList("Report.txt");
	while(temp!=NULL){
		printf("\t\t\t\tItem Code:%d\t",temp->itemcode);
		printf("\tItem Name:%s\t",temp->itemname);
		printf("\n\t\t\t\tStock:%d\t\n",temp->stock);
		printf("\t\t\t\t----------------\n");
		temp=temp->loc;
	}
	remove("Report.txt");
}
void report(){
	time_t t;
	time(&t);
	int stock,fi,sale,damage;
	printf("\t\t\t\t--------Report--------------\n");
	printf("\t\t\t\t--------Stock Status--------\n");
	printf("\t\t\t\tAs On Date:%s\n",ctime(&t));
	struct node *ptr;
    ptr=readLinkedList("item.txt");

	while(ptr!=NULL){
		struct report *temp;
		temp=(struct report*)malloc(sizeof(struct report));
		stock=0;
		temp->itemcode=ptr->item_code;
		strcpy(temp->itemname,ptr->item_name);
		fi=fitemsearch(ptr->item_code);
		damage=ditemsearch(ptr->item_code);
		sale=saleitemsearch(ptr->item_code);
		stock=ptr->op_qty+fi-sale-damage;	//stock formula
		temp->stock=stock;
		temp->loc=NULL;
		reportadd(temp);
		ptr=ptr->loc;		
	}	   
	reportprint();
}

