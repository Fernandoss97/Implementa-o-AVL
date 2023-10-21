#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int id = 0;

link novoNo(int item)
{
  link novo = malloc(sizeof(struct node));

  if (novo)
  {
    novo->item = item;
    novo->l = NULL;
    novo->r = NULL;
    novo->altura = 0;
  }
  else
  {
    printf("\nNão foi possível alocar o nó");
  }

  return novo;
}

Tree createTree()
{
  Tree t = malloc(sizeof(struct tree));
  t->z = malloc(sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0;
  t->z->r = t->z;
  return t;
}

// Rotação à direita
link rotR(link h) // h nó com fb -2 ou 2
{
  link x = h->l; // x aponta para o filho esquerdo de h
  h->l = x->r;   // o que era o filho esquerdo de h aponta para o filho direito de x se houver
  x->r = h;      // descer o nó h balanceando a arvore

  // recalcula a altura da arvore, verificando a altura da maior subarvore (esquerda e direita)
  // função maior retorna o maior valor
  h->altura = maior(alturaNo(h->l), alturaNo(h->r)) + 1;
  x->altura = maior(alturaNo(x->l), h->altura) + 1;

  // retorna a nova raiz da arvore
  return x;
}

// Rotação à esquerda
// basicamente o mesmo processo da rotR
// recebe um no desbalanceado
// reposiciona os nós
// recalcula a altura do no
// devolve a nova raiz
link rotL(link h)
{
  link x = h->r;
  h->r = x->l;
  x->l = h;

  h->altura = maior(alturaNo(h->l), alturaNo(h->r)) + 1;
  x->altura = maior(alturaNo(x->r), h->altura) + 1;

  return x;
}

// rotação dupla direita/esquerda
// junção das duas rotações simples
//  uma única rotação não seria suficiente para balancear a arvore
link rotRL(link h)
{
  h->r = rotR(h->r);
  return rotL(h);
}

link rotLR(link h)
{
  h->l = rotL(h->l);
  return rotR(h);
}

link searchR(Tree t, link h, int query)
{
  if (h == t->z)
  {
    return NULL;
  }
  if (h->item == query)
    return h;
  if (h->item >= query)
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
}

link search(Tree t, int query)
{
  return searchR(t, t->head, query);
}

link insertR(Tree t, link h, link n)
{
  if (h == t->z)
  {
    return n;
  }

  if (h->item >= n->item)
    h->l = insertR(t, h->l, n);
  else
    h->r = insertR(t, h->r, n);
  (h->N)++;
  return h;
}

// Retorna o maior valor entre a e b (descobrir maior subárvore)
int maior(int a, int b)
{
  if (a > b)
  {
    return a;
  }
  else
  {
    return b;
  }
}

// Retorna a altura de um nó
int alturaNo(link no)
{
  if (no == NULL)
  {
    return -1;
  }
  else
  {
    return maior(alturaNo(no->l), alturaNo(no->r)) + 1;
  }
}

// Retorna o fator de balanceamento
int fatorBal(link no)
{
  if (no)
  {
    return (alturaNo(no->l) - (alturaNo(no->r)));
  }
  else
  {
    return 0;
  }
}

void imprimeEmOrdem(Tree t, link h)
{
  if (h == t->z)
    return;
  imprimeEmOrdem(t, h->l);
  printf("<chave: %d N: %d>", h->item, h->N);
  imprimeEmOrdem(t, h->r);
}

void imprimePosOrdem(Tree t, link h)
{
  if (h == t->z)
    return;
  imprimePosOrdem(t, h->l);
  imprimePosOrdem(t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N);
}
void imprimePreOrdem(Tree t, link h, int k)
{
  if (h == t->z)
    return;
  for (int i = 0; i <= k; i++)
    printf(" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N);
  imprimePreOrdem(t, h->l, k + 1);
  imprimePreOrdem(t, h->r, k + 1);
}

void printnode(char *x, int h)
{
  int i;
  for (i = 0; i < h; i++)
    printf("\t");
  printf("%s\n", x);
}

int c = 0;

void imprimeR(Tree a, link t)
{
  // char s[255];
  if (t == a->z)
  {
    return;
  }
  imprimeR(a, t->r);
  printf("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N);
  if (t->l != a->z)
  {
    printf("%d:f0->%d:f1;\n", t->id, t->l->id);
  }
  else
  {
    printf("z%d [ shape=point ];\n", c);
    printf("%d:f0->z%d;\n", t->id, c);
    c++;
  }
  if (t->r != a->z)
  {
    printf("%d:f2->%d:f1;\n", t->id, t->r->id);
  }
  else
  {
    printf("z%d [ shape=point ];\n", c);
    printf("%d:f2->z%d;\n", t->id, c);
    c++;
  }
  imprimeR(a, t->l);
}
void imprime(Tree a, char *s)
{
  c = 0;
  printf("digraph %s {\n", s);
  printf("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, a->head);
  printf("}\n");
}
void imprimeFromNode(Tree a, link h, char *s)
{
  c = 0;
  printf("digraph  {\n");
  printf("name [label = \"%s\",shape=plaintext]\n", s);
  printf("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, h);
  printf("}\n");
}

// remove um elemento da árvore
link remover(link raiz, int chave) // recebe a raiz e a chave (elemento a ser removido)
{
  if (raiz == NULL)
  {
    printf("Valor não encontrado!\n");
    return NULL;
  }
  else
  {
    // Procura o nó a ser removido
    // decide o caminho (esquerda ou direito a depender do valor da chave)
    if (chave < raiz->item)
    {
      raiz->l = remover(raiz->l, chave);
    }
    else if (chave > raiz->item)
    {
      raiz->r = remover(raiz->r, chave);
    }
    else
    {
      // Elemento encontrado, processar a remoção
      // trata o 3 casos individualmente
      // Remove nós folhas (nós sem filhos)
      if (raiz->l == NULL && raiz->r == NULL)
      {
        free(raiz);
        printf("Elemento folha removido: %d!\n", chave);
        return NULL;
      }

      // Remove nós que possuem 2 filhos
      else if (raiz->l != NULL && raiz->r != NULL)
      {
        link aux = raiz->l;
        while (aux->r != NULL)
          aux = aux->r;
        raiz->item = aux->item;
        aux->item = chave;
        printf("Elemento trocado: %d!\n", chave);
        raiz->l = remover(raiz->l, chave);
      }

      // Remove nós que possuem apenas 1 filho
      else
      {
        link aux;
        if (raiz->l != NULL)
        {
          aux = raiz->l;
        }
        else
        {
          aux = raiz->r;
        }
        free(raiz);
        printf("Elemento com 1 filho removido: %d!\n", chave);
        return aux;
      }
    }
    // após a remoção, recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaNo(raiz->l), alturaNo(raiz->r)) + 1;

    // Verifica a necessidade de rebalancear a árvore
    int fb = fatorBal(raiz);

    if (fb > 1)
    {
      if (fatorBal(raiz->l) >= 0)
      {
        return rotR(raiz);
      }
      else
      {
        return rotLR(raiz);
      }
    }

    if (fb < -1)
    {
      if (fatorBal(raiz->r) <= 0)
      {
        return rotL(raiz);
      }
      else
      {
        return rotRL(raiz);
      }
    }

    return raiz;
  }
}

// insere um elemento na árvore
link AVLinsert(link h, int item) // recebe a raiz e o valor
{
  if (h == NULL) // encontra uma raiz nula, aloca o ná e retorna o endereço dele
  {
    return novoNo(item);
  }

  // se a raiz não for nula, verifica se o item é maior ou menor que a raiz e decide o caminho (esquerda ou dir)
  if (item < h->item)
  {
    h->l = AVLinsert(h->l, item);
  }
  else if (item > h->item)
  {
    h->r = AVLinsert(h->r, item);
  }
  else
  {
    // tratamento para não permitir a inserção de itens iguais
    printf("\nO elemento %d já existe\n", item);
    return h; // Retorna o mesmo nó, não houve alteração na árvore.
  }

  // após a inserção, recalcula a altura do nó
  h->altura = maior(alturaNo(h->l), alturaNo(h->r)) + 1;

  // calcula o fator de balanceamento
  int fb = fatorBal(h);

  // Verifica a necessidade de rotações e balanceia o nós se for preciso
  if (fb > 1)
  {
    if (item < h->l->item)
    {
      return rotR(h);
    }
    else
    {
      return rotLR(h);
    }
  }
  if (fb < -1)
  {
    if (item > h->r->item)
    {
      return rotL(h);
    }
    else
    {
      return rotRL(h);
    }
  }

  // retorno da raiz
  return h;
}
