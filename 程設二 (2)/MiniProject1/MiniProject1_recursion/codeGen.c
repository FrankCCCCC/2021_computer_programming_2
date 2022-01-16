#include <stdio.h>
#include <string.h>
#include "codeGen.h"

int high = 0;

int evaluateTree(BTNode *root)
{
    int retval = 0, lv, rv;
    if (root != NULL)
    {
        switch (root->data)
        {
        case ID:
            //if(strcmp(root->lexeme, "x")) printf("MOV r%d r0\n",high-2);
            //else if(strcmp(root->lexeme, "y")) printf("MOV r%d r1\n",high-2);
            //else if(strcmp(root->lexeme, "z")) printf("MOV r%d r2\n",high-2);
            //break;
        case INT:
            retval = root->val;
            printf("MOV r%d, %d\n", high, retval);
            high++;
            break;
        case ASSIGN:
        case ADDSUB:
        case MULDIV:
            lv = evaluateTree(root->left);
            rv = evaluateTree(root->right);
            if (strcmp(root->lexeme, "+") == 0)
            {
                retval = lv + rv;
                printf("ADD r%d, r%d\n", high-2, high-1);
                high--;
            }
            else if (strcmp(root->lexeme, "-") == 0)
            {
                retval = lv - rv;
                printf("SUB r%d, r%d\n", high-2, high-1);
                high--;
            }
            else if (strcmp(root->lexeme, "*") == 0)
            {
                retval = lv * rv;
                printf("MUL r%d, r%d\n", high-2, high-1);
                high--;
            }
            else if (strcmp(root->lexeme, "/") == 0)
            {
                retval = lv / rv;
                printf("DIV r%d, r%d\n", high-2, high-1);
                high--;
            }
            else if (strcmp(root->lexeme, "=") == 0)
            {
                retval = setval(root->left->lexeme, rv);
                if(strcmp(root->left->lexeme, "x") == 0)
                {
                    printf("MOV [0], r%d\n",high-1);
                    high--;
                }
                else if(strcmp(root->left->lexeme, "y") == 0)
                {
                    printf("MOV [4], r%d\n",high-1);
                    high--;
                }
                else if(strcmp(root->left->lexeme, "z") == 0)
                {
                    printf("MOV [8], r%d\n",high-1);
                    high--;
                }
                high--;
            }
            break;
        default:
            retval = 0;
        }
    }
    return retval;
}


/* print a tree by pre-order. */
void printPrefix(BTNode *root)
{
    if (root != NULL)
    {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
