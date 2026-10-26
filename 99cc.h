extern Token *token;
extern char *user_input;

void error_at(char *loc, char *fmt, ...);
Token *tokenize(char *p)
Node *expr(void);
void gen(Node *node)