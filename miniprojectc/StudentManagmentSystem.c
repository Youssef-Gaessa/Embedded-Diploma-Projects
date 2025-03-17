#include <stdio.h>
#include <stdlib.h>


struct student
{
	int id;
	char name[50];
	int age;
	float gpa;
};


struct node
{
	struct student data;
	struct node *next;
};
struct node *head = NULL;


void add_user(void)
{
	struct node *link = (struct node*) malloc(sizeof(struct node));
	struct node *check =NULL;

	int id;
	char name[50];
	int age;
	float gpa;

	printf("Enter user ID :");
	scanf("%d",&id);

	printf("Enter name :");
	scanf("%s",name);

	printf("Enter age :");
	scanf("%d",&age);

	printf("Enter GPA :");
	scanf("%f",&gpa);

	link->data.id=id;
	for(int i=0;i<50;i++)
	{
		link->data.name[i]=name[i];
		if(name[i]=='\0')
			break;
	}
	link->data.age=age;
	link->data.gpa=gpa;

	link->next=NULL;
	if(head==NULL)
	{
		head=link;
		printf("------------------------------\n"
				"Student added successfully\n");
		return;
	}

	check=head;

	while(check != NULL)
	{
		if(check->data.id==id)
		{
			printf("------------------------------\n"
					"This ID is Already Taken\n");
			return;
		}
		check=check->next;
	}

	check=head;

	while(check->next != NULL)
	{
		check=check->next;
	}
	check->next=link;
	printf("------------------------------\n"
			"Student added successfully\n");
	return;
}
void disp(void)
{
	struct node *dsp = head;

	if(head==NULL)
	{
		printf("Linked List is empty\n");
		return;
	}

	while(dsp!=NULL)
	{
		printf("[ ID: %d, Name: %s, Age: %d, GPA: %0.2f ]\n"
				,dsp->data.id
				,dsp->data.name
				,dsp->data.age
				,dsp->data.gpa);
		dsp=dsp->next;
	}
	return;
}
void srch(void)
{
	struct node *srch = head;
	int x;

	printf("Enter Student ID to search : ");
	scanf("%d",&x);

	srch=head;
	printf("------------------------------\n");
	while(srch!=NULL)
	{

		if(srch->data.id==x)
		{

			printf("Student found:\n"
					"ID: %d, Name: %s, Age: %d, GPA: %0.2f\n"
					,srch->data.id
					,srch->data.name
					,srch->data.age
					,srch->data.gpa);
			return;
		}

		srch=srch->next;
	}
	printf("Student with ID %d not found:\n",x);
	return;
}
void update(void)
{
	struct node *update = head;
	int x;
	int id;
	char name[50];
	int age;
	float gpa;

	printf("Enter Student ID to update : ");
	scanf("%d",&x);
	printf("------------------------------\n");

	update=head;
	while(update!=NULL)
	{
		if(update->data.id==x)
		{
			printf("Enter new ID :");
			scanf("%d",&id);

			printf("Enter new name :");
			scanf("%s",name);

			printf("Enter new age :");
			scanf("%d",&age);

			printf("Enter new GPA :");
			scanf("%f",&gpa);
			printf("------------------------------\n");

			if(x!=id)
			{
				update=head;
				while(update != NULL)
				{
					if(update->data.id==id)
					{
						printf("This ID is Already Taken\n");
						return;
					}
					update=update->next;
				}
			}

			update=head;
			while(update->data.id != x)
			{
				update=update->next;
			}
			update->data.id=id;
			for(int i=0;i<50;i++)
			{
				update->data.name[i]=name[i];
				if(name[i]=='\0')
					break;
			}
			update->data.age=age;
			update->data.gpa=gpa;

			printf("Student updated successfully\n");
			return;
		}
		update=update->next;
	}
	printf("Student with ID %d not found:\n",x);
	return;

}
void del()
{
	struct node *del = NULL;
	struct node *crnt= NULL;
	struct node *ref = NULL;


	int x;

	printf("Enter Student ID to delete : ");
	scanf("%d",&x);
	printf("------------------------------\n");


	if(head==NULL)
	{
		printf("Linked List is empty\n");
		return;
	}
	if(head->data.id==x)
	{
		del=head;
		head=head->next;
		free(del);
		printf("deleted successfully\n");
		return;
	}

	crnt=head->next;
	ref=head;

	while(crnt!=NULL)
	{
		if(crnt->data.id==x)
		{
			del=crnt;
			ref->next=crnt->next;
			free(del);
			printf("deleted successfully\n");
			return;
		}
		ref=crnt;
		crnt=crnt->next;
	}
	printf("This ID not found :(\n");
	return;
}
void Avg()
{
	struct node *avg = head;
	int sum=0,cnt=0;

	if(head==NULL)
	{
		printf("Linked List is empty\n");
		return;
	}

	avg=head;
	while(avg!=NULL)
	{
		cnt++;
		sum+=avg->data.gpa;
		avg=avg->next;
	}
	printf("The Avg GPA = %0.2f\n", sum/(float)cnt);
	return;
}
void max()
{
	struct node *max = head;

	float maaax;
	max=head;

	if(head==NULL)
	{
		printf("Linked List is empty\n");
		return;
	}

	maaax=max->data.gpa;

	if(head==NULL)
	{

	}

	while(max!=NULL)
	{
		if((max->data.gpa)>(maaax))
			maaax=max->data.gpa;
		max=max->next;
	}
	printf("The max GPA = %0.2f", maaax);
	return;
}

int main(void)
{
	setvbuf(stdout,NULL,_IONBF,0);
	int x;

	do
	{
		printf("------------------------------\n"
				"1. Add Students\n"
				"2. Display Student by ID\n"
				"3. Search Student by ID\n"
				"4. Update Student Information\n"
				"5. Delete Student\n"
				"6. Calculate Average GPA\n"
				"7. max GPA\n"
				"8. Exit\n"
				"Enter a Choice: ");
		scanf("%d",&x);
		if(x>8||x<1)
		{
			printf(" enter a valid input--\n");
		}
		printf("------------------------------\n");
		switch(x)
		{
		case 1:
			add_user();
			break;
		case 2:
			disp();
			break;
		case 3:
			srch();
			break;
		case 4:
			update();
			break;
		case 5:
			del();
			break;
		case 6:
			Avg();
			break;
		case 7:
			max();
			break;
		}

	}while(x!=8);
	printf("Exiting...");
}
