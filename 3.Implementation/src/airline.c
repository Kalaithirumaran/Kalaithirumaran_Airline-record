#include <stdio.h>
#include <stdlib.h>
#define size 10

//structure of the ticket
typedef struct Ticket
{
	int reg_no;
	int passport_no;
	int age;
	char name[20];
	char destination[20];
	struct Ticket *next;
} ticket;

//global variables
int num = 0;
ticket *start = NULL;

void initiate()
{
	ticket *new;
	new = (ticket *)malloc(sizeof(ticket));
	new->reg_no = 1;
	printf("Passport Number : ");
	scanf("%d", &new->passport_no);
	printf("Name: ");
	scanf("%s", new->name);
	printf("Age : ");
	scanf("%d", &new->age);
	printf("Destination : ");
	scanf("%s", new->destination);
	start = new;
	new->next=NULL;
	num++;
}

int reserveTicket(ticket *start)
{

	if(start==NULL)
	{
   		 initiate(start);
   		 return 1;
	}
	else
	{
    	ticket *temp, *new;
    	temp = start;
    	while(temp->next!=NULL)
    	{
    	  temp=temp->next;
    	}
    
    	new = (ticket *)malloc(sizeof(ticket));
    	printf("Passport Number : ");
    	scanf("%d", &new->passport_no);
    	printf("Name: ");
    	scanf("%s", new->name);
    	printf("Age : ");
    	scanf("%d", &new->age);
    	printf("Destination : ");
    	scanf("%s",new->destination);
    	
    	new->next = NULL;
    	
    	if(num <= size)
    	{
    		num++;
    		new->reg_no = num;
    		temp->next = new;
    		return 1;
    	}
    	else
    	{
    		return 0;
    	}
    }
}

int cancelTicket(int reg)
{
	ticket *curr, *prev, *new;
	curr = start;
	prev = NULL;
	
	if(start==NULL)
	    return -1;
	if(curr->next==NULL && curr->reg_no==reg)
	{
	    start = NULL;
	    num--;
	    free(curr);
	    return 1;
	}
	else{
	    while(curr->reg_no!=reg && curr->next!=NULL)
		{
			prev = curr;
			curr = curr->next;
		}
		if(curr==NULL && curr->reg_no!=reg)
			return -1;
		else
			prev->next = curr->next;
			
		free(curr);
		num--;
		return 1;
	}
}

void displayDetails()
{
    int flag = 0;
	ticket *temp;
	temp = start;
	while(temp!=NULL)
	{
	    flag = 1;
		printf("Registration Number: %d\n", temp->reg_no);
		printf("Passport Number: %d\n", temp->passport_no);
		printf("Name : %s\n", temp->name);
		printf("Age: %d\n", temp->age);
		printf("Destination: %s\n", temp->destination);
		temp = temp->next;
    }
    
    if(flag == 0){
        printf("No Reserved Tickets Yet!\n\n");
    }

}

int main()
{
    ticket *front = NULL;
    ticket *rear = NULL;
    
    int action = 0;
    
    
    while(action < 4) {
        printf("Do you want to - \n 1. Reserve a ticket? \n 2. Cancel a ticket \n 3. Display Reserved Ticket details \n 4. Exit\n\n");
        scanf("%d", &action);
        
        switch(action){
            case 1: {
                int status = reserveTicket(start);
                if(status == 0)
                    printf("\nBooking Full!! \nYou are added to waiting list.");
                else
                    printf("\nBooking Successful!!! Enjoy your journey! Your Reg No is IRREG%d\n\n", num);
                    
                break;
	        }
	        case 2: {
	            int regNum;
	            printf(" \nGive the Registration number of the ticket to be cancelled (Enter the digits in the register number)\n");
                scanf(" %d", &regNum);
                
                if(regNum > num)
                  printf("Registration number invalid!!\n\n");
                else
                {
                  int status = cancelTicket(regNum);
                  if(status == -1)
                  	printf("\nRegistration number invalid!!\n\n");
                  else
                  	printf("\nRegistration cancelled successfully\n\n");
                }
                break;
	        }
	        case 3: {
	            printf("\nThe details of the Reserved Tickets\n");
	            displayDetails();
	            break;
	        }
	        case 4: {
	            printf("\nQuitting the system! Thank You!\n");
	            break;
	        }
	        default: {
	            printf("\nWrong Action number choosen! Quitting the system!\n");
	        }
	    }
    }

    return 0;
}