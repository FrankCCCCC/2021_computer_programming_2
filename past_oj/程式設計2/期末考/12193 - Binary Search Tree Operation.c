#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    int data;
    struct _Node *left;
    struct _Node *right;
} Node;



Node *create_tree(Node *root, int n)
{
    if(n==0) return root;
    int num;
    scanf("%d", &num);
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->data = num;
    if(root == NULL){
        root = node;
        create_tree(root, n-1);
    }else{
        Node *cur, *cur_record;
        for(cur=root;cur!=NULL;){
            cur_record = cur;
            if(cur->data>num)cur = cur->left;
            else if(cur->data<num) cur = cur->right;
            else{
                create_tree(root, n-1);
                return;
            }
        }
        if(cur_record->data>num){
            cur_record->left = node;
            create_tree(root, n-1);
        }else if(cur_record->data<num){
            cur_record->right = node;
            create_tree(root, n-1);
        }
    }
}


void printInorder(Node *root){
    if(root!=NULL){
        printInorder(root->left);
        printf("%d ", root->data);
        printInorder(root->right);
    }
}

int getMax(Node *root){
    int left, right;
    if (root==NULL)
        return 0;

    // your code
    left = getMax(root->left);
    right = getMax(root->right);
    return (left>right)?(left+1):(right+1);
    /*上面那行的意思是
        if(left>right)
            return left+1;
        else
            return right+1;*/


}

void getLevelInfo(Node* root, int level, int *count, int *sum){
    if (root == NULL)
        return;
    // your code

    sum[level] += root->data;
    count[level]++;
    getLevelInfo(root->left, level+1, count, sum);
    getLevelInfo(root->right, level+1, count, sum);
}

int main(void){
    int m, nlvl, i, lvl;
    Node* root=NULL;
    int *count=NULL, *sum=NULL;
    char cmd[10];
    int n;
    scanf("%d", &n);
    root = create_tree(root, n);
    nlvl = getMax(root);

    //把兩個array清乾淨
    if(nlvl>0){
        count = (int*) malloc(sizeof(int)*nlvl);
        sum = (int*) malloc(sizeof(int)*nlvl);
        for (i=0; i<nlvl; i++) {
            count[i] = 0;
            sum[i] = 0;
        }
    }


    getLevelInfo(root, 0, count, sum);

    scanf("%d", &m);
    for(i=0;i<m;i++){
        scanf("%s", cmd);
        if (strcmp(cmd, "P")==0) {
            if (root == NULL)
                printf("NULL\n");
            else{
                printInorder(root);
                printf("\n");
            }
        } else if (strcmp(cmd, "GetMax")==0) {
            printf("%d\n", nlvl);
        } else if (strcmp(cmd, "SumLevel")==0) {
            scanf("%d", &lvl);
            if (lvl<=0 || lvl > nlvl)
                printf("0\n");
            else
                printf("%d\n", sum[lvl-1]);
        } if (strcmp(cmd, "AverLevel")==0) {
            scanf("%d", &lvl);
            if (lvl<=0 || lvl > nlvl)
                printf("0\n");
            else
                printf("%.3f\n", ((float)sum[lvl-1])/count[lvl-1]);
        }
    }

    return 0;
}
