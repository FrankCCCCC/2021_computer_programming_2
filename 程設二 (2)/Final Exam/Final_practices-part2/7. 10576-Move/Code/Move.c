#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
    struct Node *prev;
    struct Node *next;
    int data;
}Node;

int main(void){
    // Declare value
    int n,i,a,b;
    char inst[10];
    Node *temp = NULL, *temp2 = NULL;
    Node *head = NULL;
    // Declare done
    scanf("%d", &n);
    // create a linked list
    Node *node = malloc(sizeof(Node)*(n+1));
    head = &node[1];
    node[1].data = 1;
    node[1].prev = NULL;
    node[1].next = NULL;
    for(i=2;i<=n;i++){
       node[i].data = i;
       node[i].prev = &node[i-1];
       node[i].next = NULL;
       node[i-1].next = &node[i];
    }
    // create done

    while(scanf("%s", inst)!=EOF){

        if(strcmp("Exit",inst) == 0) break; // Exit program
        else scanf("%d %d", &a, &b); // input a and b

        if(node[a].next == &node[b]) continue; // if a's next position is b, then do nothing
        // part 1
        temp = node[b].prev;
        temp2 = node[a].next;
        node[a].next = &node[b];
        node[b].prev = &node[a];
        // part 2
        head->prev = temp;
        temp->next = head;
        // part 3
        temp2->prev = NULL;
        head = temp2;

    }
    while(head!=NULL){
        if(head->prev == NULL) printf("%d", head->data);
        else printf(" %d", head->data);
        head = head->next;
    }
    printf("\n");
    return 0;
}

