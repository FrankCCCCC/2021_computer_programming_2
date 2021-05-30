#include<stdio.h>

int a, b, c, d, j;
char e[40], n;

int prefix(void)
{
    int ans, op1, op2;
    j++;
        if(isspace(e[j])){
            ans = prefix();
        }
        else if(e[j] == '&'){
            op1 = prefix();
            op2 = prefix();
            ans = op1 & op2;
        }
        else if(e[j] == '|'){
            op1 = prefix();
            op2 = prefix();
            ans = op1 | op2;
        }
        else if(e[j] == 'A'){
            ans = a;
        }
        else if(e[j] == 'B'){
            ans = b;
        }
        else if(e[j] == 'C'){
            ans = c;
        }
        else if(e[j] == 'D'){
            ans = d;
        }
        return ans;


}

int main()
{
    int i, tmp;
    scanf("%s", e);
    //n = strlen(e);
    //printf("%c\n", e[0]);
    for(i=0; i<16; i++){
        tmp = i;

        d = tmp%2;
        tmp = tmp/2;
        c = tmp%2;
        tmp = tmp/2;
        b = tmp%2;
        tmp = tmp/2;
        a = tmp%2;
        j=-1;

        printf("%d %d %d %d %d\n", a, b, c, d, prefix());

    }
}