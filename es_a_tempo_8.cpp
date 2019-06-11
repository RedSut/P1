#include<iostream>
using namespace std;
struct nodo{int info; nodo*next; nodo(int a=0, nodo*b=0){info=a; next=b;}};
// funzioni per input e output
nodo *buildL(int k)
{
  if(!k) return 0;
  else
    {
      int x;
      cin>>x;
      return new nodo(x,buildL(k-1));
    }
}
void leggiA(int*A,int k)
{
  for(int i=0; i<k; i++)
    cin>>A[i];
}
nodo* clone(nodo*L)
{
  if(!L) return 0;
  else
    return new nodo(L->info,clone(L->next));
}
void stampa(nodo*L)
{
  if(!L) cout<<endl;
  else
    {
      cout<<L->info<<' ';
      stampa(L->next);

    }
}

//PRE: lista(L) è ben formata, *A>0
nodo *scl(nodo *&L, int n){
    if(!L) return 0;
    if(n==0){
        nodo *tmp=L;
        L=0;
        return tmp;
    }
    return scl(L->next, n-1);
}
//POST: scollega l'(n-1)-esimo nodo dalla lista, ritornando il puntatore al nodo n-esimo, ovvero il resto della lista, possibilmente vuoto

//PRE: lista(L) è ben formata e non vuota
nodo *getLast(nodo *L){
    if(!L->next){
        return L;
    }
    return getLast(L->next);
}
//POST: ritorna il puntatore all'ultimo nodo della lista(L)

//PRE=(lista(L),lista(L1),e lista(L2) sono ben formate, A contiene dimA elementi non negativi, con dimA pari>=0, vL=lista(L),vL1=lista(L1),vL2=lista(L2))
void Fric(nodo*L, int*A, int dimA, nodo*&L1, nodo*&L2){
    if(!L){
        return;
    }
    if(dimA==0){
        if(!L1)
            L1=L;
        else{
            nodo *last=getLast(L1);
            last->next=L;
        }
        return;
    };
    if(dimA%2==0){
        if(*A!=0){
            if(!L1){
                L1=L;
            }else{
                nodo *last=getLast(L1);
                last->next=L;
            }
            L=scl(L,*A);
        }
        Fric(L,A+1,dimA-1,L1,L2);
    }
    if(dimA%2!=0){
        if(*A!=0){
            if(!L2){
                L2=L;
            }else{
                nodo *last=getLast(L2);
                last->next=L;
            }
            L=scl(L,*A);
        }
        Fric(L,A+1,dimA-1,L1,L2);
    }
    return;
}
//POST=(i  nodi  di  vL  sono  distribuiti  correttamente  su  2  liste  X1  e  X2  secondo  i  valori  di  A  e  L1=vL1@X1  e L2=vL2@X2)

main()
{
  cout<<"start"<<endl;
  int n, dimA;
  cin >> n >> dimA;
  int*A=new int[dimA];
  nodo*L=buildL(n);
  stampa(L);
  leggiA(A,dimA);
  
  nodo*L1=0,*L2=0;
  Fric(L,A,dimA,L1,L2);
  stampa(L1);
  stampa(L2);
  
  cout<<"end"<<endl;
}
