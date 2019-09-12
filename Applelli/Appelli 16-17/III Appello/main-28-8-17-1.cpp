#include<iostream>
using namespace std;

struct nodo{int info; nodo* next; nodo(int a =0, nodo* b=0){info=a; next=b;}};
struct doppioN{nodo*inizio,* fine; int lung; doppioN(nodo* a =0, nodo* b=0, int c=0){inizio=a; fine=b;lung=c;}};


nodo* build(int n)
{
  if(n>0)
    {
      int x;
      cin>>x;
      return new nodo(x,build(n-1));
      }
  else
    return 0;
}
void stampa_DN(doppioN A)
{
  cout<<"valore DN:"<<A.inizio->info<<' '<<A.fine->info<<" lung="<<A.lung<<endl;

}
void stampaL(nodo*L)
{
  if(L)
    {
      cout<<L->info<<' ';
      stampaL(L->next);
    }
  else
    cout<<endl;

}
nodo*clone(nodo*L)
{
  if(L)
    return new nodo(L->info,clone(L->next));
  else
    return 0;
}

//PRE=(lista(L) corretta e non vuota)
doppioN Aux(nodo* L){
  if(!L->next){
    return doppioN(L,L,1);
  }
  doppioN D=0;
  D.lung=1;
  if(L->info<=L->next->info){
    D=Aux(L->next);
    D.lung++;
    D.inizio=L;
    //return D;
  }else{
    D.fine=L;
  }
  return D;
}
//POST=(restituisce il valore doppioN che rappresenta la sotto lista di L crescente di lunghezza massima che inizia col 
//primo nodo di L)

//PRE=(lista(L) corretta)
doppioN Frec(nodo* L){
  if(!L){
    return 0;
  }
  doppioN C1=0;
  C1=Aux(L);
  doppioN C2=Frec(L->next);
  doppioN Cm=0;
  if(C1.lung>=C2.lung){
    Cm=C1;
  }else{
    Cm=C2;
  }
  return Cm;
}
//POST=(restituisce il valore doppioN che rappresenta la sotto lista crescente di lunghezza massima di L)

//PRE=(lista(L) corretta, A di tipo doppioN individua una sotto lista di L, vL=L)
nodo* Grec(nodo*& L, doppioN  A){
  if(!L){
    return 0;
  }
  if(L==A.inizio){
    L=A.fine->next;
    A.fine->next=0;
    return A.inizio;
  }else{
    nodo* N1=Grec(L->next,A);
    return N1;
  }
  
}
//POST=(Giter restituisce col return la sotto lista di vL individuata da A e il valore di L diventa vL senza la sotto lista 
//restituita col return)

main()
{
  int n;
  cin>>  n;
  cout<<"start"<<endl;
  nodo*L=build(n);
  stampaL(L);
  
  nodo*  L1=clone(L);
  //doppioN A=Fiter(L);//da fare
  doppioN B=Frec(L1);//da fare
  //stampa_DN(A);
  stampa_DN(B);
  //nodo*K=Giter(L,A);//da fare
  nodo*K1=Grec(L1,B); //da fare
  //stampaL(K);
  //stampaL(L);
  stampaL(K1);
  stampaL(L1);
  cout<<"end"<<endl;
}
