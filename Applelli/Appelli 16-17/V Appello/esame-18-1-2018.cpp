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
      //N e' necessariamente != 0 altrimenti la post non sarebbe valida (il campo dim deve essere incrementato di 1 rispetto a x.dim iniziale) cio' non e' rispettato se N = 0
      nodo* i = x.primo;
      if(i->info > N->info){ //N va inserito in testa alla FIFO
          N->next = i;
          return FIFO(N,x.ultimo, x.dim+1);
      }                
      bool out = false;      //N va inserito tra x.primo (escluso) e x.ultimo
      //PRE_R=(x.primo->info < N->info)
      while(i->next && !out){           //R=(Lista(x.primo) - Lista(i->next) non contiene alcun valore maggiore di N->info)
          nodo* c = i->next;
          if(c && c->info > N->info){ //inserimento in mezzo
              i->next = N;
              N->next = c;
              out = true;
          }
          else i = i->next;
      }
      //POST_R=(se out==true => i->next!=0 => x.primo < N < x.ultimo, cioe' ho inserito N tra x.primo e x.ultimo)&&(se out==false => i->next==0 => n andra' inserito in coda a Lista(x.primo))
      if(i->next) return FIFO(x.primo, x.ultimo, x.dim+1);
      i->next = N;                                      //inserimento in coda
      return FIFO(x.primo, N, x.dim+1); 
  }
  /*POST=(restituisce una FIFO che gestisce una lista che è quella gestita da x a cui è stato
  aggiunto il nodo N mantenendo l’ordinamento, i campi primo, ultimo e  dim del valore FIFO restituito devono essere corretti 
  rispetto alla lista che gestisce, in particolare, il campo  dim deve essere incrementato di 1 rispetto a x.dim
  iniziale) */
  /*    DOMANDA 2+3) (correttezza) DIMOSTRARE CHE R AND !(i->next && !out) = POST_R, successivamente dimostrare che POST_R + istruzioni successive => POST
        se (i->next && !out) == false ALLORA i->next e' false oppure out e' true:    
            1) non e' possibile che i->next sia = 0 ed out sia true contemporaneamente: se i->next fosse uguale a zero significherebbe 
               che non e' stato trovato alcun valore di Lista(x.primo) che sia maggiore di N->info. Se cio' si verifica, allora
               significa che l'espressione "c && c->info > N->info" [con c=i->next] e' risultata sempre falsa: soddisfare tale condizione e' l'unico
               modo per cambiare il valore di out, che rimane quindi invariato ed uguale a false;
            2) se i->next!=0 => out=true => N viene inserito (in modo logico) tra x.primo ed x.ultimo:
                 =>POST_R
               i campi dati dim, primo ed ultimo della nuova FIFO ritornata per valore col return, come hanno fatto precedentemente i campi next di prec(N) ed N, verranno rappresentati coerentemente: 
                 => return FIFO(x.primo, x.ultimo, x.dim+1);
                 => POST
            3) se !i->next => out=false => N andra' inserito in coda a Lista(x.primo);
                 => POST_R
               i campi dati dim, primo ed ultimo della nuova FIFO ritornata per valore col return, come il campo next di x.ultimo, verranno rappresentati coerentemente: 
                 => return FIFO(x.primo, N, x.dim+1);
                 => POST 
  */
  
  //PRE=(x gestisce una lista non vuota)
  nodo* poplast(FIFO& x){ //iterativa
      nodo* c = x.ultimo;
      if(x.dim == 1){
          x.primo = x.ultimo = 0;
          x.dim = 0;
          return c;
      }
      //dim>1
      nodo* i = x.primo;
      while(i->next != c) //non necessita controllo su i
          i = i->next;
      i->next = 0; 
      x.ultimo = i; x.dim--;
      return c;
  }
  /*POST=(toglie dalla lista gestita da x l’ultimo nodo e lo restituisce col return, alla fine x deve essere un valore 
        FIFO corretto (anche dim) rispetto alla lista che resta (possibilmente vuota)) */
  
  //PRE=(Q è una lista di nodoFIFO  corretta (potrebbe essere anche vuota), N è un nodo allocato con next=0, m>0)
  nodoFIFO* addtolist(nodoFIFO*Q, nodo*N, int m){ //ricorsiva
      if(!Q) return new nodoFIFO(FIFO(N,N,1),0); //caso base, lista Q vuota
      Q->info = addord(Q->info, N);
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
