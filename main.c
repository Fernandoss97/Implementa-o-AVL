#include <stdio.h>
#include "bst.h"
#include "bst.c"

int main()
{
  Tree t = createTree();

  t->head = AVLinsert(t->head, 10);
  t->head = AVLinsert(t->head, 50);
  t->head = AVLinsert(t->head, 35);
  t->head = AVLinsert(t->head, 15);
  t->head = AVLinsert(t->head, 25);
  // imprime(t, "oi");
  // insert(t, 88);
  // imprime(t, "oi");
  // insert(t, 77);
  // imprime(t, "oi");

  return 0;
}
