#include<iostream>
using namespace std;
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}};
struct nodoP{nodo* P; nodoP* next; nodoP(nodo* a=0, nodoP* b=0){P=a; next=b;}};

//PRE=(cin contiene x0...xm-1 con m>=0)
nodo* leggi(){
    int i=0;
    cin>>i;
    if(i==-1){return 0;}
    return new nodo(i,leggi());
}
//POST=(restituisce una lista concatenata con m nodi tale cheil campo info del nodo 0 sia x0, quello del nodo 1 sia x1,e così via)

//PRE=(Lista(L) è ben formata, x è definito)
nodoP* aux(nodo*L, int x){
    nodoP* S=new nodoP;
    if(L->info==0){
        return S;
    }
    //x=L->info;
    S=aux(L->next,L->info);
    
    if(x==L->info){
        S->P=L->next;
        return new nodoP(S->P,S);
    }else{
        return S;
    }

}
//POST=(restituisce una lista di nodoP lunga come il n. di nodi di Lista(L) con x=info e i cui nodi puntano a questi nodi di L nell’ordine in cui i nodi sono in L)

nodoP* F(nodo* L){
    nodoP* S=new nodoP;
    if(L->info==0){
        return S;
    }
    S=F(L->next);
    int ele;
    cin>>ele;
    S=aux(L,ele);
    if(ele!=-1){
        return S;
    }
    

}

void stampa(nodoP* S){
    if(S->next==0){
        cout<<endl;
        return;
    }
    nodo* A=new nodo();
    A=S->P;
    cout<<A->info<<" ";
    stampa(S->next);
}

main()
{
  cout<<"start"<<endl;
  nodo*L=leggi();
  nodoP*y=F(L);
  stampa(y);
  cout<<endl;
  cout<<"end"<<endl;

}
