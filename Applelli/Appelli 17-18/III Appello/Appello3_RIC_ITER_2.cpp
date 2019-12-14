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

//-------- funzioni ricorsive
nodo* concric(nodo* Ln, nodo* Ls){
    //nodo* Lni=Ln;
    if(!Ln){
        //Ln->next=Ls;
        return Ls;
    }
    Ln->next = concric(Ln->next,Ls);
    return Ln;
}
nodo* staccaric(nodo* L,int N,nodo*& R){
    if(!N){
        R = L;
        return 0;
    }
    if(!L){
        R=0;
        return 0;
    }
    //nodo* Ls=0;
    nodo* Ls = staccaric(L->next,N-1,R);
    return new nodo(L->info,Ls);
}

//PRE=(lista(L),lista(L1),e lista(L2) sono ben formate, A contiene dimA elementi non negativi, con dimA pari>=0, 
//vL=lista(L),vL1=lista(L1),vL2=lista(L2))
void Fric(nodo*L, int*A, int dimA, nodo*&L1, nodo*&L2){
    if(!L){
        return;
    }
    if(!dimA){
        L1 = concric(L1,L);
        return;
    }
    nodo* R=0;
    nodo* Ls = staccaric(L,*A,R);
    L1 = concric(L1,Ls);

    nodo* R1=0;
    nodo* Ls1 = staccaric(R,*(A+1),R1);
    L2 = concric(L2,Ls1);

    Fric(R1,A+2,dimA-2,L1,L2);
}
//POST=(i  nodi  di  vL  sono  distribuiti  correttamente  su  2  liste  X1  e  X2  secondo  i  valori  di  A  e  
//L1=vL1@X1  e L2=vL2@X2)

//----------------- funzioni iterative

nodo* conciter(nodo* Ln, nodo* Ls){
    if(!Ln){
        return Ls;
    }
    if(!Ls){
        return Ln;
    }
    nodo* Lni=Ln;
    while(Ln->next){
        Ln = Ln->next;
    }
    Ln->next=Ls;
    return Lni;
}

nodo* staccaiter(nodo* L, int N, nodo*& R){
    if(!N){
        R = L;
        return 0;
    }
    //nodo* Ls = L;
    nodo* Li = L;
    while(L && N-1){
        L = L->next;
        N--;
    }
    if(!L){
        R = 0;
        return Li;
    }
    R = L->next;
    L->next=0;
    return Li;
}

//PRE=(lista(L),lista(L1),e lista(L2) sono ben formate, A contiene dimA elementi non negativi, con dimA pari>=0, 
//vL=lista(L),vL1=lista(L1),vL2=lista(L2))
void Fiter(nodo*L, int*A, int dimA, nodo*&L1, nodo*&L2){
    //bool esci = false;
    while(L && dimA>0){
        nodo* R=0;
        nodo* Ls = staccaiter(L,*A,R);
        L1 = conciter(L1,Ls);
        L=R;
        R=0;
        //nodo* R1=0;
        nodo* Ls1 = staccaiter(L,*(A+1),R);
        L2 = conciter(L2,Ls1);

        L=R;
        A=A+2;
        dimA=dimA-2;
    }
    if(L){
        L1 = conciter(L1,L);
    }
}
//POST=(i  nodi  di  vL  sono  distribuiti  correttamente  su  2  liste  X1  e  X2  secondo  i  valori  di  A  e  
//L1=vL1@X1  e L2=vL2@X2)

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
  cout<<"L1 Ric: ";
  stampa(L1);
  cout<<"L2 Ric: ";
  stampa(L2);
  L1=0;
  L2=0;
  Fiter(X,A,dimA,L1,L2);
  cout<<"L1 Iter: ";
  stampa(L1);
  cout<<"L2 Iter: ";
  stampa(L2);
  cout<<"end"<<endl;
}
