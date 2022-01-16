#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"
#include "parser.h"
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void)
{
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // 忽略空白字元

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) { //如果偵測到的字是數字，則不斷期待下一個字是數字
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT; //lexeme儲存的是數值 回傳這是一個INT
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;//lexeme儲存的是+號或-號 回傳這是加或減
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;//lexeme儲存的是*號或/號 回傳這是乘或除
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;//讀到換行 回傳結束算式
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;//讀到等於 用等於蓋掉整個lexeme 回傳指派數值
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;//讀到左括號 用左括號蓋掉整個lexeme 回傳左括號
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;//讀到右括號 用右括號蓋掉整個lexeme 回傳右括號
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;//讀到字母的話，期待下一個字母
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;//lexeme存的是整個字母組成的代號 回傳代號
    } else if (c == EOF) {
        return ENDFILE;//讀到文件結尾 回傳結尾
    } else {
        lexeme[0] = c;
        lexeme[1] = '\0';
        error(NOTFOUND);
        return UNKNOWN;//讀到例外狀況 回傳未知
    }
}

void advance(void)//用來呼叫getToken()，即抓下一個exprrsion的意思
{
    lookahead = getToken();
}

int match(TokenSet token)//用來比對傳來的跟之前拿到的Token一不一樣，如果沒抓過Token或上個抓的Token是例外，再抓一次Token，根據情況回傳1或0
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

char* getLexeme(void)//回傳當前存著的lexeme，可能是符號 數值 或代號
{
    return lexeme;
}

