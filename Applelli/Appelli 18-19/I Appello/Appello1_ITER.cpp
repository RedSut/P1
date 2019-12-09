#include<iostream>
using namespace std;

struct nodo{int info; nodo* next;nodo(int a=0, nodo* b=0){info=a; next=b;}};
struct coda{nodo* primo,*ultimo;coda(nodo*a=0){primo=a; ultimo=a;}};

coda push_end(coda x, nodo*p)
{
  p->next=0;
  if(!x.primo)
    x.primo=x.ultimo=p;
     else
    {
      x.ultimo->next=p;
      x.ultimo=p;
    }
  return x;
}

nodo* faiLista()
{
  int x;
  cin>> x;
  if(x==-1) return 0;
  return new nodo(x, faiLista());
}
void stampaL(nodo*L)
 {
   if(L)
     {
       cout<<L->info<<' ';
       stampaL(L->next);
     }
   cout<<endl;

 } 
 
// PRE= (Lista(L) è ben formata, A ha nA elementi strettamente crescenti, vL =L)

coda preleva(nodo*&L, int*A, int nA) {
    coda L1;
    L1.primo=0;
    L1.ultimo=0;
    coda Lc;
    Lc.primo=0;
    Lc.ultimo=0;
    int contL=0;
    while(L){
        int N=*A;
        if(contL==N){
            nodo* Lcp=L;
            L=L->next;
            contL++;
            //Lcp->next=0;
            L1=push_end(L1,Lcp);
            if(nA-1){
                A=A+1;
                nA--;
            }
        }else{
            nodo* Lcp1=L;
            L=L->next;
            contL++;
            //Lcp1->next=0;
            Lc=push_end(Lc,Lcp1);
        }
    }
    L=Lc.primo;
    return L1;
}

/* POST=(restituisce col return una coda che gestisce una lista con i nodi di vL che 
		 corrispondono agli indici in A, L è vL a cui sono tolti i nodi restituiti col return)*/

main()
{
    cout<<"start"<<endl;
    nodo*K=faiLista();
    int nA;
    cin >>nA;
    int * A= new int[nA];
    for(int i=0; i<nA;i++)
        cin >>A[i];
    coda X=preleva(K,A,nA);
    cout<<"lista prelevata:"<<endl;
    stampaL(X.primo);
    cout<<"lista rimasta:"<<endl;
    stampaL(K);  
    cout<<"end"<<endl;
}