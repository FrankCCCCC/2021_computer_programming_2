#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[11];
    struct Node* next;
}Node;

void Push(Node* Queue, char* Name);
void Pop(Node* Queue);
void Front(Node Queue);

int main()
{
    Node Queue;
    Queue.next = NULL;
    char Command[10];
    while(scanf("%s", Command))
    {
        printf("Queue: %d\n", Queue);
        if(strcmp(Command, "Push") == 0)
        {
            char Name[11];
            scanf("%s", Name);
            Push(&Queue, Name);
        }
        else if(strcmp(Command, "Pop") == 0)
            Pop(&Queue);
        else if(strcmp(Command, "Front") == 0)
            Front(Queue);
    }
}

void Push(Node* Queue, char* Name)
{
    if(Queue->next == NULL)
    {
        Node* Temp = Queue;
        while(Temp->next != NULL)
        {
            Temp = Temp->next;
        }
        Node* New = (Node*) malloc(sizeof(Node));
        strcpy(New->name, Name);
        New->next = NULL;
        Temp->next = New;
    }
    else
    {
        Queue = malloc(sizeof(Node));
        strcpy(Queue->name, Name);
        Queue->next = NULL;
    }
}

void Pop(Node* Queue)
{
    if(Queue != NULL)
    {
        Node* Temp = Queue;
        Queue = Queue->next;
        free(Temp);
    }
    else return;
}

void Front(Node Queue)
{
    if(Queue.name)
        printf("%s", Queue.name);
    else
        printf("empty\n");
}

