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

nodo* stacca(nodo*L, int k, nodo*& resto){

}

nodo* conc(nodo*L, nodo*n){

}

/*PRE=(lista(L),lista(L1),e lista(L2) sono ben formate, A contiene dimA elementi non negativi, 
con dimA pari>=0, vL=lista(L),vL1=lista(L1),vL2=lista(L2))    */
void Fric(nodo*L, int * A, int dimA, nodo *&L1, nodo *& L2){



}
/*POST=(i  nodi  di  vL  sono  distribuiti  correttamente  su  2  
liste  X1  e  X2  secondo  i  valori  di  A  e  L1=vL1@X1  e L2=vL2@X2) */

main()
{
  cout<<"start"<<endl;
  int n, dimA, A[20];
  cin >> n >> dimA;
  nodo*L=buildL(n);
  stampa(L);
  leggiA(A,dimA);
  nodo*X=clone(L);
  nodo*L1=0,*L2=0;
  Fric(L,A,dimA,L1,L2);
  stampa(L1);
  stampa(L2);
  //L1=0;
  //L2=0;
  //Fiter(X,A,dimA,L1,L2);
  //stampa(L1);
  //stampa(L2);
  cout<<"end"<<endl;
}
