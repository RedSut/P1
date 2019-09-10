#include<iostream>
using namespace std;

struct nodo{int info; nodo* next; nodo(int a =0, nodo* b=0){info=a; next=b;}};
struct nodoL{nodo* info; nodoL* next; nodoL(nodo* a =0, nodoL* b=0){info=a; next=b;}};



nodo* clone(nodo*L)
{
  if(L)
    return new nodo(L->info,clone(L->next));
  return 0;
}

void stampaL(nodo*L)
{
  if(L)
    {cout<<L->info<<' '; stampaL(L->next);}
  else
    cout<<endl;

}
void stampaLL(nodoL*LL,int n)
{
  if(LL)
    {cout<<"fetta "<<n<<") "; stampaL(LL->info); stampaLL(LL->next,n+1);}
}

nodo* faiL(int n)
{
  if(n>0)
    return new nodo(n, faiL(n-1));
  return 0;

}

int contan_ric(nodo*L) {
	if (!L) return 0;
    
    return 1+contan_ric(L->next);
}

nodo* taglia_ric(nodo* L, int n){
    if(!n){
        return NULL;
    }
    if(n==1){
        //L->next=NULL;
        return L;
    }
    return taglia_ric(L->next,n-1);
}


// PRE=(lista(L) corretta, dimA >=0 e A contiene dimA interi non negativi (quindi è possibile anche il valore 0), vL= valore iniziale di L)

nodoL* affettaric(nodo*&L, int*A, int dimA) {
    if(!L || !dimA){
        return 0;
    }
    int nL=contan_ric(L);
    if(!*A){
            nodoL* LL = new nodoL(0);
            LL->next=affettaric(L,A+1,dimA-1);
            return LL;
        }
    if(*A>nL){
        return 0;
    }else{
        nodo* T = taglia_ric(L,*A);
        //stampaL(T);
        nodo* tmp=L;
        L=T->next;
        T->next=0;
        nodoL* LL1 = new nodoL(tmp);
        //LL1=conc_ric(LL1,T);
        //L=L->next;
        LL1->next=affettaric(L,A+1,dimA-1);
        return LL1;
    }
    
}

// POST=(restituisce una lista di nodi di tipo nodoL che puntano alle fette di vL secondo quanto descritto nell’esempio precedente, 
// L è quello che resta di vL una volta tolte le fette)

main()
{
  cout<<"start"<<endl;
  nodo* L= faiL(10);
  nodo*L0=clone(L);
  stampaL(L);
  int n, A[10];
  cin >> n;
  for(int i=0; i<n; i++)
    cin >> A[i];
  nodoL*K=affettaric(L,A,n);
  cout<<"Lric=";
  stampaL(L);
  cout<<"LLric:"<<endl;
  stampaLL(K,1);
  cout<<endl;
  /*K=affettaiter(L0,A,n);
  cout<<"Liter=";
  stampaL(L0);
  cout<<"LLiter:"<<endl;
  stampaLL(K,1);*/
  
  cout<<"end"<<endl;
  
}