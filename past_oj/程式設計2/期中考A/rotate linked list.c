#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

void rotateList(Node** head,int n)
{
    Node *tmp1;
    Node *tmp2;
    tmp1 = *head;
    tmp2 = *head;
    n--;
    while(n--) tmp1=tmp1->next;
    while(tmp2->next != NULL) tmp2=tmp2->next;
    tmp2->next = *head;
    *head = tmp1->next;
    tmp1->next = NULL;
}


void freeList(Node *head);
Node* createList();
void printList(Node *head);

int main() {
	Node *head = NULL;
	Node *temp;
	int data;
	int k;

    	head = createList();
	scanf("%d",&k);
	rotateList(&head,k);
	printList(head);
	freeList(head);
	return 0;
}



void freeList(Node *head)
{
	Node *temp;
	for(temp=head; temp!=NULL; temp=head)
	{
		head = head->next;
		free(temp);
	}
}

Node* createList(){
    Node* head = NULL;
    Node* temp = NULL;
    int data;

    while(1){
        scanf("%d",&data);
        if(data>-1){
            if (temp==NULL) {
                temp = (Node*) malloc(sizeof(Node));
                head = temp;
            } else {
                temp->next = (Node*) malloc(sizeof(Node));
                temp = temp->next;
            }
            temp->data = data;
            temp->next = NULL;
        } else break;
    }
    return head;
}

void printList(Node *head)
{
	Node *temp=head;
	printf("%d", temp->data);
	temp=temp->next;

	for(; temp!=NULL; temp=temp->next)
	{
		printf(" %d", temp->data);
	}
	printf("\n");
}
