#include <assert.h>
#include "compiler.h"

void PROG();
void STMTS();
int isEnd();
int isNext(char *set);
void STMT();
void WHILE();
void IF();
void BLOCK();
void ASSIGN();
char *next();
char *skip(char *set);
int E(char* te);
int F(char* te);
void Eif(int elseBegin, char* te);
void genOp1(int i, char* c, char* te);
void genOp2(int i, int i1, char* op, int i2, char* te);

int tempIdx = 0, labelIdx = 0;
char *te;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
#define emit printf

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}

void PROG() {
  STMTS();
}

void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

int isEnd() {
  return tokenIdx >= tokenTop;
}

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

void STMT() {
  if (isNext("while"))
    return WHILE();
  else if (isNext("if"))
    IF();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  emit("(L%d)\n", whileBegin);
  skip("while");
  skip("(");
  int e = E(te);
  emit("if not T%d goto L%d\n", e, whileEnd);
  skip(")");
  STMT();
  emit("goto L%d\n", whileBegin);
  emit("(L%d)\n", whileEnd);
}

void IF() {
  te = tokens[tokenIdx];
  int elseBegin = nextLabel();
  int ifEnd = nextLabel();
  skip("if");
  skip("(");
  Eif(elseBegin, te);
  skip(")");
  STMT();
  emit("@L%d\n", ifEnd);
  emit("0;JMP\n\n");
  
  if(isNext("else")) {
    emit("(L%d)\n", elseBegin);
    skip("else");
    STMT();
  }
  emit("(L%d)\n", ifEnd);
}

void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

void ASSIGN() {
  te = tokens[tokenIdx];

  char *id = next();
  skip("=");
  int e = E(te);
  skip(";");
}

char *next() {
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    printf("skip(%s) got %s fail!\n", set, next());
    assert(0);
  }
}

int E(char* te) {
  int i1 = F(te);
  while (isNext("+ - * / & | ! < > = == >= <=")) {
    char *op = next();
    int i2 = E(te);
    int i = nextTemp();
    genOp2(i, i1, op, i2, te);
    i1 = i;
  }
  return i1;
}

int F(char* te) {
  int f;
  
  if (isNext("(")) {
    next();
    f = E(te);
    next();
  } else {
    f = nextTemp();
    
    char *item = next();
    genOp1(f, item, te);
  }
  return f;
}

void Eif(int elseBegin, char* te) {
  next();

  while (isNext("+ - * / & | ! < > = == >= <=")) {
    char *op = next();
    char *ti = tokens[tokenIdx];
    int i = nextTemp();
    next();

    printf("@%c\n", *te);
    printf("D=M\n");
    printf("@%c\n", *ti);

    if(isdigit(*ti))
      printf("D=D-A\n");
    else
      printf("D=D-M\n");
    printf("@L%d\n", elseBegin);
    printf("D;JGT\n\n");
  }
}

void genOp1(int i, char* c, char* te) {
  printf("@%c\n", *c);
  
  if(isdigit(*c))
    printf("D=A\n");
  else
    printf("D=M\n");
  printf("@%c\n", *te);
  printf("M=D\n\n");
}

void genOp2(int i, int i1, char* op, int i2, char* te) {
  printf("@%c\n", *te);
  printf("D=M\n");
  printf("@%c\n", *te);
  printf("D=D%cM\n", *op);
  printf("@t%d\n", i);
  printf("M=D\n\n");
}