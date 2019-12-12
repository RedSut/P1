#include<iostream>
using namespace std;

struct nodo{int info; nodo*next; nodo(int a=0, nodo*b=0){info=a; next=b;}};
struct FIFO {nodo* primo, *ultimo; int dim; FIFO(nodo*a=0,nodo*b=0,int c=0){primo=a; ultimo=b; dim=c;}};
struct nodoFIFO{FIFO info; nodoFIFO* next; nodoFIFO(FIFO a=FIFO(), nodoFIFO*b=0){info=a; next=b;}};

  
  void stampa(nodoFIFO*Q,int i)
  {
    if(Q)
      {
	cout<<"nella FIFO n."<< i<<" ci sono "<<Q->info.dim<<" valori, il primo e l'ultimo seguono:"<<endl;
        cout<<"primo="<<Q->info.primo->info<<", ultimo="<<Q->info.ultimo->info<<endl;
        stampa(Q->next,i+1);
      }

    //cout<<endl;
  }
  //PRE=(x gestisce una lista non vuota ordinata in modo crescente) 
  FIFO addord(FIFO x, nodo* N){ //iterativa    
    nodo* xpcp=x.primo;
    if(xpcp->info > N->info){ //inserimento in testa
        N->next = xpcp;
        return FIFO(N,x.ultimo, x.dim++);
    }
    bool exit = false;   
    while(xpcp->next && !exit){
        nodo* xpncp=xpcp->next;
        if(xpncp && xpncp->info > N->info){ //inserimento nel mezzo
            xpcp->next = N;
            N->next = xpncp;
            exit = true;
        }else{
            xpcp=xpcp->next;
        }
    }
    if(xpcp->next){
        return FIFO(x.primo, x.ultimo, x.dim++);
    } 
    xpcp->next = N;                             //inserimento in coda
    return FIFO(x.primo, N, x.dim++);    
  }
  /*POST=(restituisce una FIFO che gestisce una lista che è quella gestita da x a cui è stato
  aggiunto il nodo N mantenendo l’ordinamento, i campi primo, ultimo e  dim del valore FIFO restituito devono essere corretti 
  rispetto alla lista che gestisce, in particolare, il campo  dim deve essere incrementato di 1 rispetto a x.dim
  iniziale) */
  
  //PRE=(x gestisce una lista non vuota)
  nodo* poplast(FIFO& x){ //iterativa
    nodo* xpcp=x.primo;
    nodo* xucp=x.ultimo;
    if(x.dim == 1){
        x.primo = x.ultimo = 0;
        x.dim = 0;
        return xucp;
    }
    while(xpcp->next != xucp){
        xpcp=xpcp->next;
    }
    xpcp->next=0;
    x.ultimo=xpcp;
    x.dim--;
    return xucp;
  }
  /*POST=(toglie dalla lista gestita da x l’ultimo nodo e lo restituisce col return, alla fine x deve essere un valore 
        FIFO corretto (anche dim) rispetto alla lista che resta (possibilmente vuota)) */
  
  //PRE=(Q è una lista di nodoFIFO  corretta (potrebbe essere anche vuota), N è un nodo allocato con next=0, m>0)
  nodoFIFO* addtolist(nodoFIFO*Q, nodo*N, int m){ //ricorsiva
    if(!Q){
        return new nodoFIFO(FIFO(N,N,1),0);
    }
    Q->info=addord(Q->info,N);
    if((Q->info).dim > m){
        N = poplast(Q->info);
        Q->next = addtolist(Q->next, N, m);
    }
    return Q;
  }
  /*POST=(restituisce una lista Q’ di nodoFIFO ottenuta da Q inserendo in Q il nodo N in modo tale da 
    mantenere il fatto che complessivamente le liste gestite dai FIFO dei nodi di Q’ sono ordinate e sono tutte di 
    lunghezza m, a parte l’ultima che ha lunghezza tra 1 e m)*/
  
  main()
    {
      int n, m,a;
      cin>>n>>m;
      nodoFIFO* Q=0;
      for(int i=0; i<n; i++)
	{
	  cin >>a;
	  nodo*N=new nodo(a);
	  Q=addtolist(Q,N,m);//da fare
	}
      cout<<"start"<<endl;
      stampa(Q,0);
      
      cout<< "end"<<endl;
    }
