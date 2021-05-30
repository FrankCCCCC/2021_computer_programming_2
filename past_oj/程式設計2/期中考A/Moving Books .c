#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int book;
    struct node *next;
    struct node *prev;
}Node;

int main()
{
    int n;
    scanf("%d", &n);
    Node *head, *tmp;
    head = (Node*)malloc(sizeof(Node));
    head->book = 0;
    head->next = NULL;
    head->prev = NULL;
    n--;
    int i=1;
    while(n--){
        if(head->next == NULL){
            tmp = (Node*)malloc(sizeof(Node));
            tmp->book = i;
            head->next = tmp;
            tmp->prev = head;
            tmp->next = NULL;
            i++;
        }else{
            tmp->next = (Node*)malloc(sizeof(Node));
            tmp->next->book = i;
            tmp->next->prev = tmp;
            tmp = tmp->next;
            tmp->next = NULL;
            i++;
        }
    }
    /*tmp = head;
    while(tmp!=NULL){
        printf("%d ", tmp->book);
        tmp=tmp->next;
    }*/

    char command[10], choose[10];
    Node *tmp1, *tmp2;
    int a, b;
    while(1){
        scanf("%s", command);
        if(command[0] == 'm'){
            scanf("%d", &a);
            scanf("%s", choose);
            scanf("%d", &b);
            if(choose[0] == 'o'){
                tmp1 = head;
                tmp2 = head;

                while(tmp1->book != a)
                {
                    if(tmp1->next==NULL) break;
                    tmp1 = tmp1->next;
                }
                while(tmp2->book != b)
                {
                    if(tmp2->next==NULL) break;
                    tmp2 = tmp2->next;
                }

                if(tmp1->book != a || tmp2->book != b) continue;

                if(tmp1 == tmp2) continue;
                if(tmp2->next == tmp1) continue;

                if(tmp1 == head){
                    //if(head->next == NULL) break;

                    if(tmp2->next == NULL){
                        head = tmp1->next;
                        tmp1->next->prev = NULL;
                        tmp1->next = NULL;
                        tmp1->prev = tmp2;
                        tmp2->next = tmp1;
                        continue;
                    }else{
                        head = tmp1->next;
                        tmp1->next->prev = NULL;
                        tmp1->next = tmp2->next;
                        tmp1->next->prev = tmp1;
                        tmp1->prev = tmp2;
                        tmp2->next = tmp1;
                    }

                }else if(tmp1->next == NULL){
                    tmp1->prev->next = NULL;
                    tmp1->next = tmp2->next;
                    tmp1->prev = tmp2;
                    tmp1->next->prev = tmp1;
                    tmp2->next = tmp1;
                }
                else{
                    if(tmp2->next == NULL){
                        tmp1->next->prev = tmp1->prev;
                        tmp1->prev->next = tmp1->next;
                        tmp1->next = NULL;
                        tmp1->prev = tmp2;
                        tmp2->next = tmp1;
                    }else{
                        tmp1->prev->next = tmp1->next;
                        tmp1->next->prev = tmp1->prev;
                        tmp1->next = tmp2->next;
                        tmp1->prev = tmp2;
                        tmp1->next->prev = tmp1;
                        tmp2->next = tmp1;
                        continue;
                    }

                }
            }
            else if(choose[0] == 'u'){
                tmp1 = head;
                tmp2 = head;

                while(tmp1->book != a)
                {
                    if(tmp1->next == NULL) break;
                    tmp1 = tmp1->next;
                }
                while(tmp2->book != b)
                {
                    if(tmp2->next == NULL) break;
                    tmp2 = tmp2->next;
                }


                if(tmp1->book != a || tmp2->book != b) continue;
                if(tmp1 == tmp2) continue;
                if(tmp1->next==tmp2) continue;

                if(tmp2 == head){
                    if(tmp1->next == NULL){
                        tmp1->prev->next = NULL;
                        tmp1->prev = NULL;
                        tmp1->next = tmp2;
                        tmp2->prev = tmp1;
                        head = tmp1;
                    }else{
                        tmp1->prev->next = tmp1->next;
                        tmp1->next->prev = tmp1->prev;
                        tmp1->next = tmp2;
                        tmp1->prev = NULL;
                        tmp2->prev = tmp1;
                        head = tmp1;
                    }
                }else{
                    if(tmp1 == head){
                        head = tmp1->next;
                        tmp1->next->prev = NULL;
                        tmp1->next = tmp2;
                        tmp1->prev = tmp2->prev;
                        tmp2->prev = tmp1;
                        tmp1->prev->next = tmp1;
                    }else if(tmp1->next == NULL){
                        tmp1->prev->next = NULL;
                        tmp1->prev = tmp2->prev;
                        tmp1->next = tmp2;
                        tmp1->prev->next = tmp1;
                        tmp2->prev = tmp1;
                    }else{
                        tmp1->prev->next = tmp1->next;
                        tmp1->next->prev = tmp1->prev;
                        tmp1->next = tmp2;
                        tmp1->prev = tmp2->prev;
                        tmp1->prev->next = tmp1;
                        tmp2->prev = tmp1;
                    }

                }

            }
        }
        else if(command[0] == 'r'){
            scanf("%d", &a);
            tmp1 = head;

            while(tmp1->book != a)
            {
                if(tmp1->next == NULL) break; //這裡要改成這樣，原本寫成while(tmp1->book != a && tmp1->next != NULL)會錯
                tmp1 = tmp1->next;
            }

            if(tmp1->book != a) continue;

            if(tmp1 == head){
                head = tmp1->next;
                tmp1->next->prev = NULL;
                free(tmp1);
            }else if(tmp1->next == NULL){
                tmp1->prev->next = NULL;
                free(tmp1);
            }else{
                tmp1->prev->next = tmp1->next;
                tmp1->next->prev = tmp1->prev;
                free(tmp1);
            }
        }
        else if(command[0] == 'e'){
            if(head == NULL) continue;
            tmp = head;
            while(tmp!=NULL){
                printf("%d ", tmp->book);
                tmp = tmp->next;
            }
            printf("\n");
            break;
        }
    }


}
