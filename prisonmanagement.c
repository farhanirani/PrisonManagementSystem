#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int officerid=0;
int prisonerid=0;

struct officer
{
    int id;
    char name[50];
    char dob[10];
    struct officer *link;
}*opLoc,*opPrev;

struct officerlist
{
    int count;
    struct officer *pos;
    struct officer *head;
}*opList;

struct prisoner
{
    int id;
    int sentence;
    char name[50];
    char dob[10];
    char crime[200];
    char arrestingofficer[50];
    struct prisoner *link;
}*ppLoc,*ppPrev;

struct prisonerlist
{
    int count;
    struct prisoner *pos;
    struct prisoner *head;
}*ppList;



void displayprisonerlist( )
{
    int i;
    if (ppList->count==0) printf("\nThe List is Empty \n");
    else
    {
	    ppList->pos=ppList->head;
	    printf("*************** The List is as follows *********************\n");
	    for(i=0;i< ppList->count;i++)
	    {
	    	printf("\nID: %d  Name: %s",ppList->pos->id,ppList->pos->name);
	    	ppList->pos=ppList->pos->link;
	    }
	    printf("\n\n************* END OF LIST ************\n");
    }
}


void displayofficerlist( )
{
    int i;
    if (opList->count==0) printf("\nThe List is Empty \n");
    else
    {
	    opList->pos=opList->head;
	    printf("******************* The List is as follows *******************\n");
	    for(i=0;i< opList->count;i++)
	    {
	    	printf("\nID: %d  Name: %s",opList->pos->id,opList->pos->name);
	    	opList->pos=opList->pos->link;
	    }
	    printf("\n\n************** END OF LIST ************\n");
    }
}


void displayprisoner()
{
	printf("\n\nPrisoner name: %s\nPrisoner ID: %d\nDate of birth: %s\nCrime commited: %s\nSentence: %d\nArresting officer: %s\n",ppLoc->name,ppLoc->id,ppLoc->dob,ppLoc->crime,ppLoc->sentence,ppLoc->arrestingofficer);
}


void displayofficer()
{
	printf("\n\nOfficer name: %s\nOfficer ID: %d\nDate of birth: %s\n",opLoc->name,opLoc->id,opLoc->dob);
}


int searchprisoner(int target)
{
	ppPrev=NULL;
    ppLoc=ppList->head;
    while(ppLoc!=NULL)
    {
    	if(ppLoc->id==target)
	        return 1;
    	ppPrev=ppLoc;
	    ppLoc=ppLoc->link;
	    
    }
    return 0;
}


int searchofficer(int target)
{
	opPrev=NULL;
    opLoc=opList->head;
    while(opLoc!=NULL)
    {
        if(opLoc->id==target)
	        return 1;
    	opPrev=opLoc;
	    opLoc=opLoc->link;
    }
    return 0;
}


void createprisonerlist()
{
    ppList = (struct prisonerlist *)malloc(sizeof(struct prisonerlist));
    ppList -> head=NULL;
    ppList -> count=0;
}


void createofficerlist()
{
    opList = (struct officerlist *)malloc(sizeof(struct officerlist));
    opList -> head=NULL;
    opList -> count=0;
}


void addprisoner()
{
    int temp,succ,sent,oid;
    struct prisoner *ppNew;
    ppNew = (struct prisoner *) malloc(sizeof(struct prisoner));
    ppNew->link=NULL;
    printf("enter prisoner's name: ");
    gets(ppNew->name);gets(ppNew->name);
    printf("enter date of birth dd/mm/yyyy: ");
    gets(ppNew->dob);
    printf("enter crime commited: ");
    gets(ppNew->crime);
    printf("enter sentence in years: ");
    scanf("%d",&sent);
    ppNew->sentence=sent;
    
    displayofficerlist();
    printf("**************************\n\nfrom list above, select officer id that arrested the prisoner: ");
    scanf("%d",&oid);
    succ=searchofficer(oid);
    if(succ==1)
    {
   	    strcpy(ppNew->arrestingofficer,opLoc->name);
	}
    else
        strcpy(ppNew->arrestingofficer,"unknown officer");
        
    if(ppList->count==0)
    {
        ppList->head=ppNew;
    }
    else
    {
        ppLoc=ppList->head;
        while(ppLoc->link!=NULL)
            ppLoc=ppLoc->link;
        ppLoc->link=ppNew;
    }
    ppList->count+=1;
    ppNew->id = prisonerid+1;
    prisonerid++;
}


void addofficer()
{
    struct officer *opNew;
    opNew = (struct officer *) malloc(sizeof(struct officer));
    opNew->link=NULL;
    
    printf("enter officer's name: ");
    gets(opNew->name);
    gets(opNew->name);
    printf("enter date of birth dd/mm/yyyy: ");
    gets(opNew->dob);
    
    if(opList->count==0)
    {
        opList->head=opNew;
    }
    else
    {
        opLoc=opList->head;
        while(opLoc->link!=NULL)
            opLoc=opLoc->link;
        opLoc->link=opNew;
    }
    opList->count+=1;
    opNew->id = officerid+1;
    officerid++;
}


void deleteprisoner()
{
    if (ppPrev==NULL)
    	ppList->head=ppLoc->link;
    else
		ppPrev->link=ppLoc->link;
    ppList->count =ppList->count - 1;
    free(ppLoc);
    printf("\nPrisoner deleted\n");
}


void deleteofficer()
{
    if (opPrev==NULL)
    	opList->head=opLoc->link;
    else
		opPrev->link=opLoc->link;
    opList->count =opList->count - 1;
    free(opLoc);
    printf("\nOfficer deleted\n");
}


void removeprisoner(int key)
{
    int found;
    found=searchprisoner(key);
    if (found==1)
    	deleteprisoner();
    else
    	printf("\nPrisoner ID incorrect/does not exist\n");
}


void removeofficer(int key)
{
    int found;
    found=searchofficer(key);
    if (found==1)
    	deleteofficer();
    else
    	printf("\nOfficer ID incorrect/does not exist\n");
}


void main()
{
    int c1,c2,c3,oid,pid,succ;
    createprisonerlist();
    createofficerlist();
    
    printf("\n********************************** PRISON MANAGEMENT SYSTEM *********************************\n\n\n");
    
    do{
        printf("\n******************************MAIN MENU****************************\n\nenter:::  1 : OFFICER MENU , 2 : PRISONER MENU , 3 : EXIT PROGRAM\n");
        scanf("%d",&c1);
        if(c1==1)
        {
            do{
                printf("\n\n********************************OFFICER MENU**********************************");
                printf("\nenter:::  1 :  ADD OFFICER , 2 : DISPLAY OFFICER PROFILE , 3 : DELETE OFFICER , 4 : DISPLAY OFFICER LIST , 5 : EXIT OFFICER MENU\n");
                scanf("%d",&c2);
                
                if(c2==1)
                {
                    addofficer();
                }
                
                if(c2==2)
                {
                    printf("\nenter officer id:");
                    scanf("%d",&oid);
                    succ=searchofficer(oid);
                    if(succ==1)
                    {
               			displayofficer();
					}
                    else
                        printf("\nofficer ID incorrect/does not exist");
                }
                
                if(c2==3)
                {
                	printf("enter officer id:");
                    scanf("%d",&oid);
                    succ=searchofficer(oid);
                    if(succ==1)
                    {
               			removeofficer(oid);
					}
                    else
                        printf("\nofficer ID incorrect/does not exist");
				}
				
				if(c2==4)
				{
					displayofficerlist();
				}
            } while(c2!=5);
        }
        else if(c1==2)
        {
            do{
                printf("\n\n****************************PRISONER MENU*********************************");
                printf("\nenter:::  1 :  ADD PRISONER , 2 : DISPLAY PRISONER PROFILE , 3 : DELETE PRISONER , 4 : DISPLAY PRISONER LIST , 5 : EXIT PRISONER MENU\n");
                scanf("%d",&c3);
                
                if(c3==1)
                {
                    addprisoner();
                }
                
                if(c3==2)
                {
                    printf("\nenter prisoner id:");
                    scanf("%d",&pid);
                    succ=searchprisoner(pid);
                    if(succ==1)
                    {
               			displayprisoner();
					}
                    else
                        printf("\nPRISONER ID incorrect/does not exist");
                }
                
                if(c3==3)
                {
                	printf("\nenter prisoner id:");
                    scanf("%d",&pid);
                    succ=searchprisoner(pid);
                    if(succ==1)
                    {
               			removeprisoner(pid);
					}
                    else
                        printf("\nPRISONER ID incorrect/does not exist");
				}
				
				if(c3==4)
				{
					displayprisonerlist();
				}
            } while(c3!=5);
        }
    }while(c1!=3);
}

