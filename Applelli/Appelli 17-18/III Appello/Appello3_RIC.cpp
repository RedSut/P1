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

nodo* conc(nodo*L, nodo*Ln){
  if(!L){
    return Ln;
  }
  if(!Ln){
    return L;
  }
  Ln->next=conc(L,Ln->next);
  return Ln;
}

nodo* stacca(nodo*L, int k, nodo*& resto){
  if(!k){
    resto=L;
    return NULL;
  }
  if(!L){
    L=0;
    resto=0;
    return L;
  }
  if(k==1){//ultimo elemento da staccare
    resto=L->next;
    L->next=0;
    return L;
  }

  L->next=stacca(L->next,k-1,resto);
  return L;
}

/*PRE=(lista(L),lista(L1),e lista(L2) sono ben formate, A contiene dimA elementi non negativi, 
con dimA pari>=0, vL=lista(L),vL1=lista(L1),vL2=lista(L2))    */
void Fric(nodo*L, int * A, int dimA, nodo *&L1, nodo *& L2){
  if(!L){
    return;
  }
  if(!dimA){
    L1=conc(L1,L);
    return;
  }
  int n=0;
  n=*A;
  nodo* R=0;
  nodo* nL=0;
  nL=stacca(L,n,R);
  L=R;
  //L->next=0;
  if(dimA%2==0){
    L1=conc(nL,L1);
  }
  if(dimA%2!=0){
    L2=conc(nL,L2);
  }
  Fric(L,A+1,dimA-1,L1,L2);
  //stampa(L);
}
/*POST=(i  nodi  di  vL  sono  distribuiti  correttamente  su  2  
liste  X1  e  X2  secondo  i  valori  di  A  e  L1=vL1@X1  e L2=vL2@X2) */

nodo* staccaiter(nodo* L, int N, nodo*& resto){
  //cout<<"stacca";
  if(!N){
    resto=L;
    return NULL;
  }
  nodo* Li = L;
  for(int i=0;L->next && (i<N-1);i++){
    L=L->next;
  }
  if(!L->next){
    resto=0;
  }else{
    resto=L;
    L=0;
  }
  return Li;
}

nodo* conciter(nodo* Ln, nodo* ins){
  //cout<<"conc ";
  if(!Ln){
    return ins;
  }
  if(!ins){
    return Ln;
  }
  nodo* Lni = Ln;
  while (Ln->next){
    Ln = Ln->next;
  }
  Ln->next=ins;
  return Lni;
}

/*nodo* avanzaL(nodo*L, int N){
  cout<<"avanzaL ";
  for(int i=0;L->next && (i<N);i++){
    L=L->next;
  }
  return L;
}*/

/*PRE=(lista(L),lista(L1),e lista(L2) sono ben formate, A contiene dimA elementi non negativi, 
con dimA pari>=0, vL=lista(L),vL1=lista(L1),vL2=lista(L2))    */
void Fiter(nodo* L, int* A, int dimA, nodo*& L1, nodo*& L2){
  //cout<<"fiter ";
  int i=0;
  while(L && i<dimA-1){
    //cout<<"uno ";
    int N = A[i];
    nodo* resto = 0;
    nodo* ins1 = staccaiter(L,N,resto);
    L = resto;
    L1 = conciter(L1,ins1);
    resto=0;
    nodo* ins2 = staccaiter(L,N,resto);
    L=resto;
    L2 = conciter(L2,ins2);
    i+=2;
  }
  if(L){
    L1 = conciter(L1,L);
  }
}

/*POST=(i  nodi  di  vL  sono  distribuiti  correttamente  su  2  
liste  X1  e  X2  secondo  i  valori  di  A  e  L1=vL1@X1  e L2=vL2@X2) */

int main(){
  cout<<"start"<<endl;
  int n, dimA, A[20];
  cin >> n >> dimA;
  nodo*L=buildL(n);
  stampa(L);
  leggiA(A,dimA);
  nodo*X=clone(L);
  nodo*L1=0,*L2=0;
  Fric(L,A,dimA,L1,L2);
  cout<<"Fric:"<<endl;
  cout<<"L1: ";
  stampa(L1);
  cout<<"L2: ";
  stampa(L2);
  L1=0;
  L2=0;
  Fiter(X,A,dimA,L1,L2);
  cout<<"Fiter:";
  cout<<"L1: ";
  stampa(L1);
  cout<<"L2: ";
  stampa(L2);
  cout<<"end"<<endl;
}
