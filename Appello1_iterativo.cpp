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
/*nodo* ins_end(nodo* p){
    nodo *q;
    for ( q = p; q->next != NULL; q = q->next ){};
    
    q->next = p;
    
    return q;
}*/
//
coda preleva(nodo*&L, int*A, int nA){
    coda C, D;
    //nodo* L1;
    int i=0,k=0;
    while(L){
        if(i==A[k]){
            nodo* tmp1;
            tmp1=L;
            L=L->next;
            tmp1->next=0;
            C=push_end(C,tmp1);
            k++;
        }else{
            nodo* tmp2;
            tmp2=L;
            L=L->next;
            tmp2->next=0;
            D=push_end(D,tmp2);
        }
        i++;
    }
    L=D.primo;    
    return C;
}
//
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
