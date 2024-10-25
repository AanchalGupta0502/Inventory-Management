#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	int item_code;
	char item_name[100];
	int op_qty;
	int min_level;
	struct node *loc;
};
struct node *start=NULL;
void writeLinkedList(char filename[], node* head){
    
    FILE* file;
    file = fopen (filename, "ab");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
        fwrite(head, sizeof(struct node), 1, file);
    
    if(fwrite != 0)
    {
        printf("Linked List stored in the file successfully\n");
    }
       else
    {
           printf("Error While Writing\n");
    }
    
    fclose(file);
    
}
struct node* readLinkedList( char filename[]){
    
    struct node* temp = (struct node *)malloc(sizeof(struct node));;
    struct node* head; // points to the first node of the linked list in the file
    struct node* last; // points to the last node of the linked list in the file
    last = head = NULL;
    
    FILE* file;
    file = fopen (filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File...'\n");
        return 0;
    }
    
    // reading nodes from the file
    // nodes are read in the same order as they were stored
    // we are using the data stored in the file to create a new linked list
    while(fread(temp, sizeof(struct node), 1, file))
    {
        
        if(head==NULL)
        {
            head = last = (struct node *)malloc(sizeof(struct node));
        }
        else
        {
            last->loc = (struct node *)malloc(sizeof(struct node));
            last = last->loc;
        }
        last->item_code = temp->item_code;
        strcpy(last->item_name, temp->item_name);
        last->min_level=temp->min_level;
        last->op_qty=temp->op_qty;
        last->loc = NULL;
        
    }
    
    fclose(file);
    
    return head;
    
}
const char* isearch(int key){
		struct node *ptr;
		int flag=0;
		ptr=readLinkedList("item.txt");
		while(ptr!=NULL){
			if(ptr->item_code==key){
				flag=1;
			    break;
			}
			ptr=ptr->loc;
		}
		if(flag==1){
			return(ptr->item_name);
		}
		else{
			return("0");
		}		
	}
void add(){
	const char *a;
	struct node *ptr,*temp;
	ptr=(struct node *)malloc(sizeof(struct node));
	printf("\t\t\tItem code:");
	scanf("%d",&ptr->item_code);
	a=isearch(ptr->item_code);
	if(a=="0"){		// for unique item entry in item master
	
		printf("\t\t\tItem name:");
		scanf("%s",&ptr->item_name);
		printf("\t\t\top qty:");
		scanf("%d",&ptr->op_qty);
		printf("\t\t\tmin level:");
		scanf("%d",&ptr->min_level);
		ptr->loc=NULL;
	    if(start==NULL){
	    	start=ptr;
	    	writeLinkedList("item.txt",start);
		}
		else{
			temp=start;
			while(temp->loc!=NULL){
				temp=temp->loc;
			}
			temp->loc=ptr;
		writeLinkedList("item.txt",ptr);	
		}
	}
	else{
		printf("\t\t\titem already exists!\n");
		printf("\t\t\tYou can modify it if you want\n");
	}
}
void removeFileContents(const char *filename,struct node* newnode) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "Couldn't open file: %s\n", filename);
        exit(1);
    }
	 while(newnode!=NULL)
    {
        fwrite(newnode, sizeof(struct node), 1, file);
        newnode = newnode->loc;
    }
    
    if(fwrite == 0)
    {
           printf("Error While Writing\n");
    }
    fclose(file);
}
void modify(){
int n1;
printf("\t\t\tenter item code:");
scanf("%d",&n1);
struct node *ptr;
struct node *newnode=readLinkedList("item.txt");
ptr=newnode;
if(newnode==NULL){
	printf("\t\t\tNo item to be modified...");
}
else{
	while(ptr->item_code!=n1&&ptr!=NULL){
		ptr=ptr->loc;
	}
	if(ptr->item_code==n1){
	
	printf("\t\t\tEnter new values:");
	printf("\t\t\titem name:");
	scanf("%s",&ptr->item_name);
	printf("\t\t\topening qty:");
	scanf("%d",&ptr->op_qty);
	printf("\t\t\tminimum level:");
	scanf("%d",&ptr->min_level);
	removeFileContents("item.txt",newnode);
	}
	else
	{
		printf("\t\t\tnot found the item code...\n");
	}
}
}
void del(){
	int n1,flag=0;
	printf("\t\t\tenter item code to be deleted:");
	scanf("%d",&n1);
	struct node *t1=NULL;
	struct node *newnode=readLinkedList("item.txt");
    struct node *ptr;
	ptr=newnode;
	if(newnode==NULL)
	{
		printf("\t\t\tNo item to be deleted...\n");
	}
	else if(ptr->item_code==n1){
		newnode=ptr->loc;
		ptr->loc=NULL;
		free(ptr);
		flag=1;
		printf("\t\t\tdeleted successfully...\n");
		removeFileContents("item.txt",newnode);
	}
	else{   
	     t1=ptr;
	     ptr=ptr->loc;
		while(ptr!=NULL)
		{  
			if(ptr->item_code==n1)
				{
			     t1->loc=ptr->loc;
				 ptr->loc=NULL;
				 free(ptr);	//delete the node
				 printf("\t\t\tdeleted successfully..\n");
				 flag=1;
				 break;
				 }
			t1=ptr;
			ptr=ptr->loc;
		}
		struct node *rem=newnode;
		while(rem!=NULL){
			printf("%s\n",rem->item_name);
			rem=rem->loc;
			}
		removeFileContents("item.txt",newnode);
		
	}
	if(flag==0){
	printf("\t\t\titem code doesnt exist..\n");
	}
}
void print(){
    	struct node *newnode=readLinkedList("item.txt");
    	struct node *ptr;
    	ptr=newnode;
    	while(ptr!=NULL){
    		printf("\t\t\t--------------------\n");
    		printf("\t\t\tItem code:%d\n",ptr->item_code);
    		printf("\t\t\tItem name:%s\n",ptr->item_name);
    		printf("\t\t\tMinimum Level:%d\n",ptr->min_level);
    		printf("\t\t\tOpening Qty:%d\n",ptr->op_qty);
    		printf("\t\t\t----------------\n");
    		ptr=ptr->loc;
		}
	}
