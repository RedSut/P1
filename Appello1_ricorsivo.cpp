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
 //PRE: lista(L) è ben formata e non vuota
nodo *getLast(nodo *L){
    if(!L->next){
        return L;
    }
    return getLast(L->next);
}
//POST: ritorna il puntatore all'ultimo nodo della lista(L)

//PRE=(Lista(L) ben formata, non vuota, A ha nA elementi, vL=L)
nodo* patt_match(nodo*&L, int*A, int nA){
    if(!L){
        //L=lista match
        return 0;
    }
    if(!nA){
       nodo* tmp=L;
       L=0;
       return tmp; 
    }
    if(L->info==*A){
        //match
        return patt_match(L->next,A+1,nA-1);
    }else{
        //no match
        nodo* U=L;
        L=L->next;
        //delete L;
        U->next=patt_match(L,A,nA);
        return U;
    }

}
//POST=(L è la lista che consiste dei nodi di vL che matchano con A e col return restituisce la lista degli altri nodi di vL)  

main()
{
  cout<<"start"<<endl;
  nodo*K=faiLista();
  int nA;
  cin >> nA;
  int * A= new int[nA];
  for(int i=0; i<nA; i++)
    cin >>A[i];
  if(!K){
      cout<<"Lista vuota, impossibile fare il match"<<endl;
  }else{
      nodo* X=patt_match(K,A,nA);
      cout<<"lista del match:"<<endl;
      stampaL(K);
      cout<<"lista rimasta:"<<endl;
      stampaL(X);  
  }
   cout<<"end"<<endl;
}
