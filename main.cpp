#include "llist.h"
#include "bstree.h"
#define MAX 1000000
#include <stdio.h>
#include <time.h>

int main () {

  llist<int> l;

  // PRUEBAS LISTA
  // int num;
  // for (int i = 0; i < MAX; ++i) {
  //   num = rand() % (MAX * 2 + 1);
  //   l.listInsert(new llnode<int>(num));
  // }
  //
  //
  // int conta = 0;
  // int num1;
  // long x = time(NULL);
  // long y = x + 10;
  // while (x < y) {
  //   num1 = rand() % (MAX * 2 + 1);
  //   l.listSearch(num1);
  //   ++conta;
  //   x = time(NULL);
  // }
  // std::cout << conta << '\n';

  tree<int> t;
  stack<int> s;

  // PRUEBAS ARBOL

  t.secTree();
  //t.inorderTreeWalk(t.getRoot(), s);
  std::cout << "creado" << '\n';

  int conta = 0;
  int num1;
  long x = time(NULL);
  long y = x + 10;
  while (x < y) {
    num1 = rand() % (MAX * 2 + 1);
    t.iterativeTreeSearch(num1);
    ++conta;
    x = time(NULL);
  }
  std::cout << conta << '\n';




}