#include<iostream>
using namespace std;

struct nodo{int num, info; nodo* next; nodo(int a=0,int b=0, nodo* c=0){num=a; info=b; next=c;}}; // nodo di lista 
struct FIFO{nodo* primo, *ultimo; FIFO(nodo*a=0, nodo*b=0){primo=a; ultimo=b;}};
struct nodoF{FIFO info; nodoF*next; nodoF(FIFO a=FIFO(),nodoF*b=0){info=a; next=b;}}; //nodo di lista con FIFO

FIFO push_end(FIFO a, nodo*b)
{
  b->next=0;
  if(!a.primo)
  {a.primo=a.ultimo=b;}
  else
   {a.ultimo->next=b; a.ultimo=b;}
  return a;
}

FIFO push_begin(FIFO a, nodo* b)
{
 if(!a.primo)
   {a.primo=a.ultimo=b; b->next=0; return a;}
 else
  {
   b->next=a.primo;
   a.primo=b;
   return a;
  }
}

  void stampa_L(nodo*L)
{
 if (L)
   {cout<<'['<<L->num<<','<<L->info<<']'<<' '; stampa_L(L->next);}
 else
   cout<<endl;

}
void stampa_F(nodoF* x)
{
  if(x)
    {
      stampa_L(x->info.primo);
      cout<<endl;
      stampa_F(x->next);
    }
}

nodo* costruisci(int n, int dim)
{
 if(dim)
   {int x; cin>>x; return new nodo(n,x,costruisci(n+1,dim-1));}
 return 0;
}
 nodo* clone(nodo*a)
 {
  if(a)
    {return new nodo(a->num, a->info, clone(a->next));}
  return 0;
 }


//PRE=(lista(L) corretta, vL=L) 
FIFO eliminaR(nodo*& L, int x){
  if(!L){
    return 0;
  }
  FIFO F1=0;
  F1=eliminaR(L->next,x);
  if(L->info==x){
    nodo* aux=L;
    //F1.ultimo=L;
    L=L->next;
    F1=push_begin(F1,aux);
    //F1.primo=L;
    //return F1;
  }
  return F1;
}
//POST=(L è vL da cui sono stati eliminati tutti i nodi con info=x)&&(viene restituito un valore FIFO che gestisce la lista
//dei nodi tolti nello stesso ordine che hanno in vL)

//con PRE=(lista(Q) è corretta e ordinata rispetto ai campi info delle liste gestite dai suoi nodi,x gestisce lista non vuota) 
nodoF* insR(nodoF* Q, FIFO x){
  if(!Q){
    return new nodoF(x,Q);
  }
  if(Q->info.primo->info<x.primo->info){
    Q->next=insR(Q->next,x);
  }else{
    return new nodoF(x,Q);
  }
  return Q;
}
//POST=(restituisce Q a cui è stato aggiunto un nodoF che contiene x in modo da mantenere l’ordine dei campi info delle liste
//gestite dai  suoi nodi)
 
 
//PRE=(lista(L) è corretta, vL=L)
nodoF* tieni_primo_ric(nodo*& L){
  if(!L){
    return NULL;
  }
  nodo* L1=L;
  FIFO F=eliminaR(L->next,L->info);
  /*cout<<"F"<<endl;
  stampa_L(F.primo);
  cout<<"L"<<endl;
  stampa_L(L);*/
  nodoF* N=tieni_primo_ric(L->next);
  if(F.primo){
    N=insR(N,F);
  }
  return N;
}//POST=(L contiene tanti  nodi quanti sono i diversi campi info di vL e per ciascuncampo info di vL contiene esattamente il
//primo nodo con quel valore di info)&&(la funzione restituisce col return una lista di nodi nodoF i cui nodi gestiscono i 
//nodi ripetuti di vL nel modospiegato nell’esempio) 
 

main()
{
  int dim;
  cout<<"start"<<endl;
  cin>>dim;
  nodo*C=costruisci(0,dim);
  nodo* D=clone(C);
  cout<<"Lista costruita"<<endl;
  stampa_L(C);
  nodoF* a =tieni_primo_ric(C); //da fare
  cout<<"soluzione ricorsiva"<<endl<<"nodi tolti:"<<endl;
   
  stampa_F(a);
  cout<<"lista rimanente:"<<endl;
  stampa_L(C);
  /*nodoF* b=tieni_primo_iter(D); //da fare
  cout<<"soluzione iterativa"<<endl<<"nodi tolti:"<<endl;
  stampa_F(b);
  cout<<"lista rimanente:"<<endl;
  stampa_L(D);*/
  cout<<"end";
}
