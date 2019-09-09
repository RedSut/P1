//FUNZIONA SOLO PARTE RIC
#include<iostream>
using namespace std;
struct nodo{int info ; nodo* next; nodo(int a=0, nodo*b=0){info=a; next=b;}};
struct coda{nodo* primo,* ultimo;coda(nodo*a=0,nodo*b=0){primo=a; ultimo=b;}};
coda push_beg(coda x, nodo*a)
{
  if(!x.primo)
    {
      x.primo=x.ultimo=a;
      a->next=0;
      return x;
    }
  a->next=x.primo;
  x.primo=a;
  return x;
}
coda push_end(coda x, nodo*a)
{
  if(!x.primo)
    {
      x.primo=x.ultimo=a;
      a->next=0;
      return x;
    }
  x.ultimo->next=a;
  x.ultimo=a;
  a->next=0;
  return x;
}

nodo* buildlist(int m)
{
  if(m>0)
    {
      int x;
      cin >> x;
      return new nodo(x,buildlist(m-1));
    }
  return 0;
}
nodo* clone(nodo*L)
{
  if(L)
    return new nodo(L->info,clone(L->next));
  return 0;
}
void stampaL(nodo*L)
{
  if(L)
    {
      cout<< L->info<<' ';
      stampaL(L->next);
    }
  else
    cout<<endl;
}
void search(int A, nodo*& L){
  if(A==L->info){
    if(!L->next){
      L=0;
    }else{
      L=L->next;
    }
  }
  search(A,L->next);
}
void ins(nodo* L,nodo*& Ord){
  if(!Ord){
    L->next=0;
    Ord=L;
  }else{
    if(Ord->info>L->info){
      L->next=Ord;
      Ord=L;
    }else{
      ins(L,Ord->next);
    }
  }
}
//PRE=(lista(L) è ben formata, lista(ord) è ben formata, siano v_L e v_o i valori iniziali di lista(L) e lista(ord))
void ordric(nodo*&L, nodo*& ord){
    if(!L){
      return;
    }
    //ord->info=L->info; 
    //delete L;
    ordric(L->next,ord);
    ins(L,ord);
    L=0;
}
//POST=(L è vuota e lista(ord)è la lista ordinata composta dai nodi div_L e di v_o)
void ins2(coda& C, nodo* I){
  if(!C.primo||I->info <= C.primo->info){
    push_beg(C,I);
  }else if(I->info > C.ultimo->info){
    push_end(C,I);
  }else{
    nodo* tmp;
    while (tmp->next && I->info>=tmp->next->info)
    {
      tmp=tmp->next;
    }
    I->next=tmp->next;
    tmp->next=I;
  }

}
//PRE=(lista(L) ben formata, v_L è il valore iniziale di lista(L))
nodo* orditer(nodo* L){
  nodo* P;
  coda C;
  while(L){
    P=L;
    P->next=0;
    L=L->next;
    ins2(C,P);  
  }
  return C.primo;
}
//POST=(restituisce la lista composta dai nodi di v_L ordinati rispetto al campo info

main()
{
  int  n;
  cout<<"start"<<endl;
  cin>> n;
  nodo*L=buildlist(n);
  stampaL(L);
  nodo*L1=clone(L);
  cout<<endl;
  nodo*L2=0;
  ordric(L,L2);
  stampaL(L2);
  //nodo*y=orditer(L1);
  //stampaL(y);
  cout<<"end"<<endl;
}
