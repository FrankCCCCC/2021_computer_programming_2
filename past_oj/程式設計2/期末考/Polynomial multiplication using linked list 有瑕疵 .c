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
    Node *tmp1, *tmp2, *p3=NULL, *tmp3, *tmp;

    tmp2 = p2;
    while(tmp2!=NULL){

        tmp1 = p1;
        while(tmp1!=NULL){
            if(p3==NULL){
                if((tmp1->data * tmp2->data) == 0){
                    tmp1 = tmp1->next;
                    continue;
                }
                tmp3 = (Node*)malloc(sizeof(Node));
                tmp3->next = NULL;
                tmp3->prev = NULL;
                tmp3->data = tmp1->data * tmp2->data;
                tmp3->power = tmp1->power + tmp2->power;
                p3 = tmp3;
            }else{
                if((tmp1->data * tmp2->data) == 0){
                    tmp1 = tmp1->next;
                    continue;
                }

                tmp3->next = (Node*)malloc(sizeof(Node));
                tmp3->next->next = NULL;
                tmp3->next->prev = tmp3;

                tmp3->next->data = tmp1->data * tmp2->data;
                tmp3->next->power = tmp1->power + tmp2->power;
                tmp3 = tmp3->next;

                tmp = p3;
                while(tmp!=tmp3){
                    if(tmp->power == tmp3->power){
                        tmp->data += tmp3->data;
                        tmp3->prev->next = NULL;
                        free(tmp3);
                        tmp3 = tmp3->prev;
                        break;
                    }else{
                        tmp = tmp->next;
                    }

                }
            }

            tmp1 = tmp1->next;
        }

        tmp2 = tmp2->next;
    }

    //sort p3

    /*Node *tmp4, *p4=NULL, *cur, *comp, *tmp5;
    cur = p3;
    while(cur!=NULL){
        if(p4 == NULL){
            tmp4 = (Node*)malloc(sizeof(Node));
            tmp4->data = cur->data;
            tmp4->power = cur->power;
            tmp4->next = NULL;
            tmp4->prev = NULL;
            p4 = tmp4;
            cur = cur->next;
        }else{
            int flag = 0;
            comp = p4;
            tmp5 = (Node*)malloc(sizeof(Node));
            tmp5->data = cur->data;
            tmp5->power = cur->power;

            while(comp->next!=NULL){
                if(cur->power > comp->power){
                    comp->prev->next = tmp5;
                    tmp5->prev = comp->prev;
                    comp->prev = tmp5;
                    tmp5->next = comp;
                    tmp4 = tmp5;
                    flag = 1;
                    break;
                }

                comp = comp->next;
            }
            if(flag == 0){
                comp->next = tmp5;
                tmp5->next = NULL;
                tmp5->prev = comp;
                tmp4 = tmp5;
            }

            cur = cur->next;
        }

    }*/

    //±N0§R±¼

    Node *tmp6, *tmp7;
    tmp6 = p3;
    if(p3==NULL) return p3;
    else{
        while(tmp6->next!=NULL){
            if(tmp6->data == 0){
                tmp7 = tmp6;
                tmp6 = tmp6->next;
                tmp6->prev = tmp7->prev;
                tmp7->prev->next = tmp6;
                free(tmp7);
            }else{
                tmp6=tmp6->next;
            }
        }
        if(tmp6->data==0){
            tmp6->prev->next = NULL;
            free(tmp6);
        }


        return p3;
    }

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