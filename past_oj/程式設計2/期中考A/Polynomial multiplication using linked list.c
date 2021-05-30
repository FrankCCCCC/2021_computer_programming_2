#include<stdio.h>
#include<stdlib.h>

typedef struct _Node{
 long data;  //the value of coefficient
 int power; //the value of power
 struct _Node *next;
 struct _Node *prev;
}Node;
void printNode(Node* head);         //the function which will print the output
Node* create();                     //create polynomial linked list
void destroy(Node *node);           //destroy polynomial linked list
Node* multiple(Node* p1, Node* p2); //input two polynomial linked list and return the result

void printNode(Node* head)
{
    Node *tmp = head;
    if(tmp==NULL || tmp->data==0) return;
    while(tmp != NULL){
        printf(" %ld %d", tmp->data, tmp->power);
        tmp = tmp->next;
    }
}

Node* create(void)
{
    Node *head, *tmp, *tmp1;
    head = NULL;

    while(1){
        if(head==NULL){
            tmp = (Node*) malloc(sizeof(Node));
            tmp->next = NULL;
            tmp->prev = NULL;
            scanf(" %ld %d", &tmp->data, &tmp->power);
            head = tmp;
        }else
        {
            tmp1 = (Node*) malloc(sizeof(Node));
            tmp1->next = NULL;
            tmp1->prev = tmp;
            scanf(" %ld %d", &tmp1->data, &tmp1->power);
            tmp->next = tmp1;
            tmp = tmp->next;
        }

        if(tmp->power == 0) break;
    }
    return head;

}

void destroy(Node *node)
{
    Node* tmp;
    if(node == NULL) return;
    else{
        while(node->next != NULL){
            tmp = node;
            node = node->next;
            free(tmp);
        }
        free(node);
    }

}

Node* multiple(Node* p1, Node* p2)
{
    Node *p3=NULL, *tmp1, *tmp2, *tmp3, *tmp4, *tmp;

    tmp2 = p2;
    while(tmp2!=NULL){
        tmp1 = p1;
        while(tmp1!=NULL){
            if(p3 == NULL){
                if(tmp1->data * tmp2->data == 0){
                    tmp1 = tmp1->next;
                    continue;
                }
                p3 = (Node*)malloc(sizeof(Node));
                p3->data = tmp1->data * tmp2->data;
                p3->power = tmp1->power + tmp2->power;
                p3->prev = NULL;
                p3->next = NULL;
                tmp3 = p3;
            }else{
                if(tmp1->data * tmp2->data == 0){
                    tmp1 = tmp1->next;
                    continue;
                }
                tmp3->next = (Node*)malloc(sizeof(Node));
                tmp3->next->data = tmp1->data * tmp2->data;
                tmp3->next->power = tmp1->power + tmp2->power;
                tmp3->next->prev = tmp3;
                tmp3->next->next = NULL;
                tmp3 = tmp3->next;

                tmp = p3;
                while(tmp!=tmp3){
                    if(tmp->power == tmp3->power){
                        tmp->data += tmp3->data;
                        if(tmp->data == 0){
                            tmp->prev->next = tmp->next;
                            tmp->next->prev = tmp->prev;
                        }

                        tmp3->prev->next = NULL;
                        tmp4 = tmp3;
                        tmp3 = tmp3->prev;
                        free(tmp4);
                        break;
                    }else if(tmp->power < tmp3->power){
                        tmp4 = tmp3;
                        tmp3 = tmp3->prev;
                        tmp4->prev->next = NULL;
                        tmp4->prev = tmp->prev;
                        tmp4->next = tmp;
                        tmp->prev->next = tmp4;
                        tmp->prev = tmp4;
                        break;
                    }

                    tmp = tmp->next;
                }
            }
            tmp1 = tmp1->next;
        }
        tmp2 = tmp2->next;
    }
    return p3;
}

int main(void){
 Node *p1=create(); //polynomial linked list1
 Node *p2=create(); //polynomial linked list2
 Node *mul=multiple(p1,p2);
 printNode(mul);
 destroy(mul);
 destroy(p2);
 destroy(p1);

    //printNode(p1);
 //printNode(p2);
 return 0;
}
