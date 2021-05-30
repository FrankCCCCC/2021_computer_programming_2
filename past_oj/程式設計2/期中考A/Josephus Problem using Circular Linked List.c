#include<stdio.h>
#include<stdlib.h>

typedef struct node{
        int data;
        struct node *next;
} Node;

Node* create(int n)
{
    int i, num;

    Node *head, *tmp;
    head = (Node*)malloc(sizeof(Node));

    head->data = 1;
    head->next = NULL;

    for(i=2; i<n; i++){
        if(head->next == NULL){
            tmp = (Node*)malloc(sizeof(Node));
            tmp->data = i;
            tmp->next = NULL;
            head->next = tmp;
        }else
        {
            tmp->next = (Node*)malloc(sizeof(Node));
            tmp->next->data = i;
            tmp = tmp->next;
        }

    }
    tmp->next = (Node*)malloc(sizeof(Node));
    tmp->next->data = n;
    tmp->next->next = head;
    return head;
}
void josephus(int m,Node *head)
{
    Node *cur, *tmp;
    cur = head;
    int n;
    while(cur->next != cur){
        if(m==1){
            printf("%d ", cur->data);
            cur = cur->next;

            if(cur->next = head) break;

        }else
        {
            n=m-2;
            while(n--) cur = cur->next;
            printf("%d ", cur->next->data);
            tmp = cur->next;
            cur->next = tmp->next;
            free(tmp);
            cur = cur->next;
        }
    }

    printf("%d\n", cur->data);
}


int main(void){
	int n,m;
	scanf("%u %u",&n, &m);
	Node *head = create(n);
	/*while(n--){
        printf("%d ", head->data);
        head=head->next;
	}*/
	josephus(m,create(n));
}
