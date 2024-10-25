#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct pnode{
	int GSTNo;
	char party_name[100];
	int mobile;
	char address[100];
	char email[100];
	struct pnode *loc;
};
struct pnode *pstart=NULL;
void writepartyLinkedList(char filename[], pnode* head){
	
    FILE* file;
    file = fopen (filename, "ab");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
        fwrite(head, sizeof(struct pnode), 1, file);
    
    if(fwrite == 0)
    {
           printf("Error While Writing\n");
    }
    
    fclose(file);
    
}
struct pnode* readpartyLinkedList( char filename[]){
    
    struct pnode* temp = (struct pnode *)malloc(sizeof(struct pnode));;
    struct pnode* head; // points to the first node of the linked list in the file
    struct pnode* last; // points to the last node of the linked list in the file
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
    while(fread(temp, sizeof(struct pnode), 1, file))
    {
        
        if(head==NULL)
        {
            head = last = (struct pnode *)malloc(sizeof(struct pnode));
        }
        else
        {
            last->loc = (struct pnode *)malloc(sizeof(struct pnode));
            last = last->loc;
        }
        last->GSTNo = temp->GSTNo;
        strcpy(last->party_name, temp->party_name);
        last->mobile=temp->mobile;
        strcpy(last->address, temp->address);
        strcpy(last->email, temp->email);
        last->loc = NULL;
        
    }
    fclose(file);
    return head;
}
void removePartyFileContents(const char *filename,struct pnode* newnode) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "Couldn't open file: %s\n", filename);
        exit(1);
    }
	 while(newnode!=NULL)
    {
        fwrite(newnode, sizeof(struct pnode), 1, file);
        newnode = newnode->loc;
    }
    
    if(fwrite == 0)
    {
           printf("Error While Writing\n");
    }
    fclose(file);
}
 int psearch(const char *key1){
		struct pnode *ptr;
		int flag=0;
		ptr=readpartyLinkedList("party.txt");
		while(ptr!=NULL){
			if(strcmp(key1,ptr->party_name)==0){
				flag=1;
			    break;
			}
			ptr=ptr->loc;
		}
		return flag;
}
int uniquegst(int gst){
	int flag=0;
	struct pnode *t=readpartyLinkedList("party.txt");
	while(t!=NULL){
		if(t->GSTNo==gst){
			flag=1;
			break;
		}
		t=t->loc;
	}
	return flag;
}
void p_add(){
	int a;
	struct pnode *ptr,*temp;
	ptr=(struct pnode *)malloc(sizeof(struct pnode));
	printf("\t\t\tGstNo.:");
	scanf("%d",&ptr->GSTNo);
	a=uniquegst(ptr->GSTNo);
	printf("%d",a);
	if(a==0){
		printf("\t\t\tparty name:");
		scanf("%s",&ptr->party_name);
		printf("\t\t\tmobile:");
		scanf("%d",&ptr->mobile);
		printf("\t\t\taddress:");
		scanf("%s",&ptr->address);
		printf("\t\t\t E-mail:");
		scanf("%s",&ptr->email);
		ptr->loc=NULL;
	    if(pstart==NULL){
	    	pstart=ptr;
	    	writepartyLinkedList("party.txt",pstart);
		}
		else{
			temp=pstart;
			while(temp->loc!=NULL){
				temp=temp->loc;
			}
			temp->loc=ptr;
				writepartyLinkedList("party.txt",ptr);
		}
	}
	else{
		printf("\t\t\tThere exist a party with this Gst no.\n");
		printf("\t\t\tYou can modify it if you want\n");
	}
}
void p_modify(){
int n1;
printf("\t\t\tenter Gst No:");
scanf("%d",&n1);
struct pnode *ptr;
struct pnode *newnode=readpartyLinkedList("party.txt");
ptr=newnode;
if(newnode==NULL){
	printf("\t\t\tNo item to be modified...\n");
}
else{
	while(ptr->GSTNo!=n1&&ptr!=NULL)
	{
		ptr=ptr->loc;
	}
    if(ptr->GSTNo==n1)
	{
		printf("\t\t\tEnter new values:\n");
		printf("\t\t\tparty name:");
		scanf("%s",&ptr->party_name);
		printf("\t\t\tmobile:");
		scanf("%d",&ptr->mobile);
		printf("\t\t\taddress:");
		scanf("%s",&ptr->address);
		printf("\t\t\tE-mail");
		scanf("%s",ptr->email);
		removePartyFileContents("party.txt",newnode);
	}
	else{
		printf("\t\t\tnot found the item code.\n");
	}
}
}

void p_del(){
	int n1,flag=0;
	printf("\t\t\tenter Gst NO. to be deleted:");
	scanf("%d",&n1);
	struct pnode *ptr,*t1=NULL,*newnode;
	newnode=readpartyLinkedList("party.txt");
	ptr=newnode;
	if(newnode==NULL)
	{
		printf("\t\t\tNothing to be deleted...\n");
	}
	else if(ptr->GSTNo==n1){
		newnode=ptr->loc;
		ptr->loc=NULL;
		free(ptr);
		flag=1;
		removePartyFileContents("party.txt",newnode);
		printf("\t\t\tdeleted successfully...\n");
	}
	else{   
	     t1=ptr;
	     ptr=ptr->loc;
		while(ptr!=NULL)
		{  
			if(ptr->GSTNo==n1)
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
removePartyFileContents("party.txt",newnode);
	}
	if(flag==0){
		printf("\t\t\tParty doesn't exist.\n");
	}
}
 void m_print(){
    	struct pnode *ptr;
    	struct pnode *newnode=readpartyLinkedList("party.txt");
    	ptr=newnode;
    	while(ptr!=NULL){
    		printf("\t\t\t--------------------\n");
    		printf("\t\t\tGSTNo:%d\n",ptr->GSTNo);
    		printf("\t\t\tParty:%s\n",ptr->party_name);
    		printf("\t\t\tAddress:%s\n",ptr->address);
    		printf("\t\t\tE-mail%:%s\n",ptr->email);
    		printf("\t\t\tMobile:%d\n",ptr->mobile);
    		printf("\t\t\t--------------------\n");
    		ptr=ptr->loc;
		}
}

