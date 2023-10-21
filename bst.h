#ifndef BST_H
#define BST_H

typedef struct node *link;
struct node
{
  link l;
  link r;
  int item;
  int N;  // quantidade de nos na subarvore
  int id; // id da nó
  int altura;
};

typedef struct tree
{
  link head; // raiz
  link z;    // nó externo
} *Tree;

Tree createTree();

link rotR(link h);

link rotL(link h);

link rotRL(link h);

link rotLR(link h);

link search(Tree h, int query);

// link insert(Tree h, int item);

int alturaNo(link no);

int maior(int a, int b);

int fatorBal(link no);

void imprimeEmOrdem(Tree t, link h);
void imprimePosOrdem(Tree t, link h);
void imprimePreOrdem(Tree t, link h, int k);

link AVLinsert(link h, int item);

void imprime(Tree a, char *s);

#endif
