#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TK_REVERSED,    // symbol
    TK_NUM,         // integer
    TK_EOF,         // end of input
} Tokenkind;

typedef struct Token Token;

struct Token {
    Tokenkind kind; // type of a token
    Token *next;    // next token
    int val;        // value if kind is TK_NUM
    char *str;      // string of a token
};

Token *token;

// a function to report an error
// take the same arguments to printf()
void error(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// returns true if the next token is the expected symbol
// otherwise, returns false
bool consume(char op) {
    if (token->kind != TK_REVERSED || token->str[0] != op)
        return false;
    token = token->next;
    return true;
}

// reads one token forward if the next token is the expected symbol
// otherwise, reports an error
void expect(char op) {
    if (token->kind != TK_REVERSED || token->str[0] != op)
        error("'%c' is not expected", op);
    token = token->next;
}

// reads one token and return the value if the next token is integer
// otherwise, reports an error
int expect_number() {
    if (token->kind != TK_NUM)
        error("It is not a number");
    int val = token->val;
    token = token->next;
    return val;
}

bool at_eof() {
    return token->kind == TK_EOF;
}

// Create a new token and connect to cur
Token *new_token(Tokenkind kind, Token *cur, char *str) {
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    cur->next = tok;
    return tok;
}

// Tokenize input string p and return it
Token *tokenize(char *p) {
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while (*p) {
        // Skip spaces
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (*p == '+' || *p == '-') {
            cur = new_token(TK_REVERSED, cur, p++);
            continue;
        }

        if (isdigit(*p)) {
            cur = new_token(TK_NUM, cur, p);
            cur->val = strtol(p, &p, 10);
            continue;
        }

        error("Cannot tokenize");
    }

    new_token(TK_EOF, cur, p);
    return head.next;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "The number of arguments is not correct.\n");
        return 1;
    }

    // Tokenize
    token = tokenize(argv[1]);

    // Output former assembly
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    // Output the first mov if the first input is a number
    printf("  mov rax, %d\n", expect_number());

    // Consume the sequences either "+<integer>" or "-<integer>"
    // and output assembly
    while  (!at_eof()) {
        if (consume('+')) {
            printf("  add rax, %d\n", expect_number());
            continue;
        }

        expect('-');
        printf("  sub rax, %d\n", expect_number());
    }

    printf("  ret\n");
    return 0;
}