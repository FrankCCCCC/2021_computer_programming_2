#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "codeGen.h"
int sbcount = 0;
int initial = 0;
int getval(void)
{
    int i, retval, found;

    if (match(INT)) {
        retval = atoi(getLexeme());
    } else if (match(ID)) {
        i = 0; found = 0; retval = 0;
        while (i<sbcount && !found) {
            if (strcmp(getLexeme(), table[i].name)==0) {
                retval = table[i].val;
                found = 1;
                break;
            } else {
                i++;
            }
        }
        if (!found) {
            if (sbcount < TBLSIZE) {
                strcpy(table[sbcount].name, getLexeme());
                table[sbcount].val = 0;
                sbcount++;
            } else {
                error(RUNOUT);
            }
        }
    }
    return retval;
}
int setval(char *str, int val)
{
    int i, retval;
    i = 0;
    while (i<sbcount) {
        if (strcmp(str, table[i].name)==0) {
            table[i].val = val;
            retval = val;
            break;
        } else {
            i++;
        }
    }
    return retval;
}
/* create a node without any child.*/
BTNode* makeNode(TokenSet tok, const char *lexe){
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
/*factor := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN*/
BTNode* factor(void)
{
    BTNode* retp = NULL;
    char tmpstr[MAXLEN];

    if (match(INT)) {
        retp =  makeNode(INT, getLexeme());
        retp->val = getval();
        advance();
    } else if (match(ID)) {
        BTNode* left = makeNode(ID, getLexeme());
        left->val = getval();
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->right = expr();
            retp->left = left;
        } else {
            retp = left;
        }
    } else if (match(ADDSUB)) {
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ID) || match(INT)) {
            retp = makeNode(ADDSUB, tmpstr);
            if (match(ID))
                retp->right = makeNode(ID, getLexeme());
            else
                retp->right = makeNode(INT, getLexeme());
            retp->right->val = getval();
            retp->left = makeNode(INT, "0");
            retp->left->val = 0;
            advance();
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    } else {
        error(NOTNUMID);
    }
    if(match(UNKNOWN)) error(NOTFOUND);
    return retp;
}
/*  term        := factor term_tail*/
BTNode* term(void)
{
    BTNode *node;

    node = factor();

    return term_tail(node);
}
/*term_tail := MULDIV factor term_tail | NIL*/
BTNode* term_tail(BTNode *left)
{
    BTNode *node;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();

        node->left = left;
        node->right = factor();

        return term_tail(node);
    }
    else
        return left;
}
/*  expr        := term expr_tail*/
BTNode* expr(void)
{
    BTNode *node;

    node = term();

    return expr_tail(node);
}
/*  expr_tail   := ADDSUB term expr_tail | NIL*/
BTNode* expr_tail(BTNode *left)
{
    BTNode *node;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();

        node->left = left;
        node->right = term();

        return expr_tail(node);
    }
    else
        return left;
}
/*statement   := END | expr END*/
void statement(void)//總管目前該做甚麼的function，由main不斷呼叫
{
    BTNode* retp;//此Node用來儲存回傳Tree的Head

    if (match(ENDFILE)) {
        printf("MOV r0, [0]\nMOV r1, [4]\nMOV r2, [8]\nEXIT 0\n");
        exit(0);//如果從lex.c那邊抓來的Token是ENDFILE 就結束程式
    } else if (match(END)) {
        printf(">> ");
        advance();//如果從lex.c那邊抓來的Token是END 代表換行了 就再抓下一個Token
    } else {
        retp = expr(); //不是上面的情況的話 則把接下來的東西當作expreesion 呼叫148行的expr()
        if (match(END)) {
            evaluateTree(retp);
            //printf("%d\n", evaluateTree(retp));
            //printPrefix(retp); printf("\n");
            freeTree(retp);
            //讀到換行之後，利用上面呼叫建好的Tree，呼叫CodeGen.c裡面的evaluateTree()跟printPrefix()
            printf(">> ");
            advance();//做完之後Free掉Tree，換行繼續抓下一個Token
        }
    }
}
void error(ErrorType errorNum)
{
    switch (errorNum) {
    case MISPAREN:
        fprintf(stderr, "Mismatched parenthesis\n");
        break;
    case NOTNUMID:
        fprintf(stderr, "Number or identifier expected\n");
        break;
    case NOTFOUND:
        fprintf(stderr, "%s not defined\n", getLexeme());
        break;
    case RUNOUT:
        fprintf(stderr, "Out of memory\n");
    }
    printf("EXIT 1\n");
    exit(0);
}

