#ifndef RED_BLACK_rbtree
#define RED_BLACK_rbtree
#include <stack>
#include <iostream>
#define MAX 5
using namespace std;


enum colors {RED, BLACK};

// Nodos del arbol:
template <typename T>
class rbnode{
   public:
		// Esta clase es para ser usada por otras clases.
		// Por eficiencia se hacen los atributos publicos.
		T key;
		rbnode<T> *p, *left, *right;
		enum colors color;

		// Constructor por omision.
		rbnode(){
		};

		// Constructor por copia del nodo.
		rbnode(const rbnode<T> * obj, const rbnode<T> * objNil, rbnode<T> * parent, rbnode<T> * nilPtr){
		}

      // Inicializacion de datos miembro.
		rbnode (const T& k, rbnode<T> *w = NULL, rbnode<T> *y = NULL, rbnode<T> *z = NULL, enum colors c = RED):
					key(k), p(w), left(y), right(z), color(c)
		{};

		~rbnode(){

		}
};

// Arbol:
template <typename T>
class rbtree{
	public:
		rbtree(){
      nil = nullptr;
      root = nil;
		};
			// Constructor (crea un arbol vacio)

		rbtree(const rbtree<T>& obj){
      nil = nullptr;
      root = nil;
		};
			// Constructor copia

		~rbtree(){
      // while (root) {
      //   treeDelete(root);
      // }
		};
			// Destructor (borra el arbol)

		void inorderTreeWalk(rbnode<T>* x, stack<T> & pila){
      if (x != nil) {
        inorderTreeWalk(x->left, pila);
        pila.push(x->key);
        if (x->color == RED) {
          pila.push(0);
        } else {
          pila.push(1);
        }
        inorderTreeWalk(x->right, pila);
      }
		};
            // Efectua un recorrido en orden del subarbol cuya raiz es apuntada
            // por x. En cada visita apila la llave de cada nodo y su color.
            // Es decir, cada vez que se llega a un nodo se ejecutan las
            // instrucciones pila.push(x->key); y luego pila.push(colorDeX).
            // Para efectos de la tarea, si el color del nodo es rojo,
            // ponga en la pila un 0, y si es negro, ponga un 1.
            // Si se hace correctamente, al finalizar el metodo la pila deberia
            // contener las llaves de los nodos del subarbol (y su color)
            // ordenadas de mayor a menor.

		rbnode<T>* treeSearch(const T& k){
      rbnode<T> * ptr = root;
      ptr = treeSearchRec(ptr, k);
      return ptr;
		};
			// Busca la llave recursivamente, si la encuentra devuelve un
            // puntero al nodo que la contiene, sino devuelve NULL.

		rbnode<T>* iterativeTreeSearch(const T& k){
      rbnode<T> * ptr = root;
      while (ptr != nil && k != ptr->key) {
        if (k < ptr->key) {
          ptr = ptr->left;
        } else {
          ptr = ptr->right;
        }
      }
      if (ptr == nil) {
        ptr = NULL;
      }
      return ptr;
		};
			// Igual que en el anterior pero usa un procedimiento iterativo.

		rbnode<T>* treeMinimum(){
      rbnode<T> * ptr = min(root);
      return ptr;
		};
			// Devuelve el nodo con la llave menor.
            // Si el arbol esta vacio devuelve NULL.

		rbnode<T>* treeMaximum(){
      rbnode<T> * ptr = max(root);
      return ptr;
		};
			// Devuelve el nodo con la llave mayor.
            // Si el arbol esta vacio devuelve NULL.

		rbnode<T>* treeSuccessor(const rbnode<T>* x){
      if (x->right != nil) {
        return min(x->right);
      }
      rbnode<T> * y = x->p;
      while (y != nil && x == y->right) {
        x = y;
        y = y->p;
      }
      return y;
		};
			// Devuelve el nodo cuya llave es la siguiente mas grande que
            // la del nodo x. Si no existe tal nodo devuelve NULL.

		void treeInsert(rbnode<T>* z){ //aux es y, actual es x.
      rbnode<T> * y = nil;
      rbnode<T> * x = root;
      while (x != nil) {
        y = x;
        if (z->key < x->key) {
          x = x->left;
        } else {
          x = x->right;
        }
      }
      z->p = y;
      if (y == nil) {
        root = z;
      } else {
        if (z->key < y->key) {
          y->left = z;
        } else {
          y->right = z;
        }
      }
      z->left = nil;
      z->rigth = nil;
      z->color = RED;
      fixUp(z);
	   };
			// Inserta el nodo z en la posicion que le corresponde en el arbol.

		rbnode<T>* treeDelete(rbnode<T>* z){
		};
			// Saca del arbol la llave contenida en el nodo apuntado por z.
			// Devuelve la direccion del nodo eliminado para que se pueda
			// disponer de el.

		rbnode<T> * getRoot() const{
			return this->root;
		};
		// Devuelve la raiz del arbol. (Para efectos de revision de la tarea).

		rbnode<T> * getNil() const{
			return this->nil;
		};
		// Devuelve T.nil. (Para efectos de revision de la tarea).

    void print(stack<T> & pila) {
      while (!pila.empty()) {
        cout << pila.top() << "  |  ";
        pila.pop();
      }
    };

    void secTree () {
      rbnode<T> * x = root;
      for (int i = 0; i < MAX; ++i) {
        rbnode<T> * n = new rbnode<T>(i);
        if (x == nil) {
          root = n;
          n->color = BLACK;
        } else {
          n->p = x;
          x->right = n;
          n->color = RED;
        }
        x = n;
      }
    };

		private:

		rbnode<T> *root;	// raiz del arbol
		rbnode<T> *nil;	    // nodo nil (hoja) del arbol

    rbnode<T>* min(rbnode<T>* x){
      while (x->left != nil) {
        x = x->left;
      }
      return x;
    };

    rbnode<T>* max(rbnode<T>* x){
      while (x->right != nil) {
        x = x->right;
      }
      return x;
    };

    rbnode<T>* treeSearchRec(rbnode<T> * x, const T& k){
      if (x == nil) {
        return NULL;
      } else {
        if (k == x->key) {
          return x;
        } else {
          if (k < x->key) {
            return treeSearchRec(x->left, k);
          } else {
            return treeSearchRec(x->right, k);
          }
        }
      }
    };

    void fixUp(rbnode<T> * z){
      rbnode<T> * y = nil;
      while (z->p != nil && z->p->color == RED){
        if (z->p == z->p->p->left){
          y = z->p->p->right;
          if (y->color == RED) {
            z->p->color = BLACK;
            y->color = BLACK;
            z->p->p->color = RED;
            z = z->p->p;
          } else {
            if (z == z->p->right) {
              z = z->p;
              leftRotate(z);
            }
            z->p->color = BLACK;
            z->p->p->color = RED;
            rightRotate(z->p->p);
          }
        } else {
          if (z->p == z->p->p->right){
            y = z->p->p->left;
            if (y->color == RED) {
              z->p->color = BLACK;
              y->color = BLACK;
              z->p->p->color = RED;
              z = z->p->p;
            } else {
              if (z == z->p->left) {
                z = z->p;
                rightRotate(z);
              }
              z->p->color = BLACK;
              z->p->p->color = RED;
              leftRotate(z->p->p);
            }
          }
        }
      }
      root->color = BLACK;
    }

    void leftRotate(rbnode<T>* x){

    }

};

#endif	// RED_BLACK_rbtree
