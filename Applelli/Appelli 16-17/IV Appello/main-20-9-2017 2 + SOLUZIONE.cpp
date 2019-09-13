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
                            /* R I C O R S I V A */ 
// PRE=(lista(L) corretta, vL=L) 
FIFO eliminaR(nodo*&L, int x){
    if(!L) return FIFO();
    FIFO b=eliminaR(L->next,x);
    if(L->info==x){
        nodo*temp=L;
        L=L->next;
        b=push_begin(b,temp);
    }
    return b;
} 
//POST=(L è vL da cui sono stati eliminati tutti i nodi con info=x)&&(viene restituito un valore FIFO che gestisce la lista dei nodi
//tolti nello stesso ordine che hanno in vL) 

//PRE=(lista(Q) è corretta e ordinata rispetto ai campi info delle liste gestite dai suoi nodi, x gestisce lista non vuota)
nodoF* insR(nodoF*Q, FIFO x){
    
    if(!Q || x.primo->info<Q->info.primo->info) 
        return new nodoF(x,Q);
    else Q->next=insR(Q->next, x);
    return Q;
}  
//POST=(restituisce Q a cui è stato aggiunto un nodoF che contiene x in modo da mantenere l’ordine dei campi info delle liste
//gestite dai suoi nodi)
 
//PRE=(lista(L) è corretta, vL=L) 
nodoF* tieni_primo_ric(nodo*& L){
    if(!L) return 0;
    FIFO x=eliminaR(L->next, L->info);
    nodoF* y=tieni_primo_ric(L->next);
    if(x.primo)
    y=insR(y,x);
    return y;
}
//POST=(L contiene tanti nodi quanti sono i diversi campi info di vL e per ciascun campo info di vL
//contiene esattamente il primo nodo con quel valore di info)&&(la funzione restituisce col return una
//lista di nodi nodoF i cui nodi gestiscono i nodi ripetuti di vL nel modo spiegato nell’esempio)



                            /* I T E R A T I V A */

//PRE=(lista(Q) è corretta e ordinata rispetto ai campi info delle liste gestite dai suoi nodi, x gestisce lista non vuota)
nodoF* insI(nodoF*Q,FIFO x){
    if(!Q || x.primo->info<Q->info.primo->info) return new nodoF(x,Q);
    nodoF* z=Q;
    while(z->next && z->next->info.primo->info<x.primo->info)
        z=z->next;
        
        z->next=new nodoF(x,z->next);
        
    
    return Q;
}
//POST=(restituisce Q a cui è stato aggiunto un nodoF che contiene x in modo da mantenere l’ordine dei campi info delle liste
//gestite dai suoi nodi)

//PRE=(lista(L) è corretta, vL=L)
nodoF* tieni_primo_iter(nodo*& L){
    nodoF* x=0;
    nodo* z=L;
    while(z){
        FIFO a=eliminaR(z->next, z->info);
        if(a.primo)
        x=insI(x,a);
        z=z->next;
    }
    return x;
} 
//POST=(L contiene tanti nodi quanti sono i diversi campi info di vL e per ciascun campo info di vL
//contiene esattamente il primo nodo con quel valore di info)&&(la funzione restituisce col return una
//lista di nodi nodoF i cui nodi gestiscono i nodi ripetuti di vL nel modo spiegato nell’esempio)

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
  nodoF* b=tieni_primo_iter(D); //da fare
  cout<<"soluzione iterativa"<<endl<<"nodi tolti:"<<endl;
  stampa_F(b);
  cout<<"lista rimanente:"<<endl;
  stampa_L(D);
  cout<<"end";
}
