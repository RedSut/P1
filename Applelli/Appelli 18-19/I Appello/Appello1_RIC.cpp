#include<iostream>
using namespace std;

struct nodo{int info; nodo* next;nodo(int a=0, nodo* b=0){info=a; next=b;}};

nodo* faiLista()
{
  int x;
  cin>> x;
  if(x==-1) return 0;
  return new nodo(x, faiLista());
}
void stampaL(nodo*L)
 {
   if(L)
     {
       cout<<L->info<<' ';
       stampaL(L->next);
     }
   cout<<endl;
 } 
// PRE=(Lista(L) ben formata, A ha nA elementi, vL=L)
nodo* patt_match(nodo*&L, int* A, int nA) {
    if(!L){
        return NULL;
    }
    if(!nA){
        nodo* P = L;
        L=0;
        return P;
    }
    if(L->info!=*A){
        nodo* M = L;
        L = L->next;
        M->next = patt_match(L,A+1,nA-1);
        return M;
    }else{
        nodo* M1 = patt_match(L->next,A,nA);
        return M1;
    }
}
/* POST=(L e' la lista che consiste dei nodi di vL che matchano con A e col return 
restituisce la lista degli altri nodi di vL) */

main() {
  cout<<"start"<<endl;
  nodo*K=faiLista();
  int nA;
  cin >>nA;
  int * A= new int[nA];
  for(int i=0; i<nA; i++)
    cin >>A[i];
  nodo* X=patt_match(K,A,nA);
  cout<<"lista del match:"<<endl;
  stampaL(K);
  cout<<"lista rimasta:"<<endl;
  stampaL(X);  
  cout<<"end"<<endl;
}

