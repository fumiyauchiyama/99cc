typedef enum {
    TK_RESERVED, 
    TK_NUM,
    TK_EOF,
} TokenKind;

typedef struct Token Token;

struct Token {
    TokenKind kind;
    Token *next;
    int val; // value if kind is TK_NUM
    char *str;
    int len;
};

typedef enum {
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_NUM, // Integer
    ND_EQ, // ==
    ND_NE, // !=
    ND_LT, // <
    ND_LE, // <=
} NodeKind;

typedef struct Node Node;

struct Node {
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val;
};

extern Token *token;
extern char *user_input;

void error_at(char *loc, char *fmt, ...);
Token *tokenize(char *p);
Node *expr(void);
void gen(Node *node);