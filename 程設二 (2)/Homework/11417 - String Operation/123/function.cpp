#include <iostream>
#include "11417.h"

Str::Str(char* S)
{
    head = tail = NULL;
    int i = 0;
    while (S[i] != '\0')
    {
        Char* Tmp = new Char(S[i]);
        i += 1;
        if(head)
        {
            tail->next = Tmp;
            tail = tail->next;
        }
        else head = tail = Tmp;
    }
}

Str::Str(const Str &Sample)
{
    head = tail = NULL;
    Char* Now = Sample.head;
    while(Now)
    {
        Char* Temp = new Char(Now->text);

        if(head)
        {
            tail->next = Temp;
            tail = tail->next;
        }
        else head = tail = Temp;
        Now = Now->next;
    }
}

Str& Str::strInsert(const Str &S)
{
    Str* Temp = new Str(S);
    tail->next = Temp->head;
    return *this;
}
