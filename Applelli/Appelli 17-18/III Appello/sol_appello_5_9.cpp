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

nodo* conc(nodo*L, nodo*n){ //concatenazione di due liste
    if(!L) return n;
    if(!n) return L;
    L->next= conc(L->next,n);
    return L;
}

nodo*stacca(nodo*L, int k, nodo*& resto){ //stacca una porzione di lista (return) e il resto della lista in "resto"
    if(!k){ //caso base in cui ho 0 nodi da staccare
        resto =L;
        return NULL;
    }
    if(!L){ //caso in cui ho finito la lista
        resto=0;
        return 0;
    }
    if(k==1){ //sono sull'ultimo nodo della porzione da staccare
        resto = L->next;
        L->next = 0;
        return L;
    }
    //faccio la chiamata al nodo successivo, il puntatore L si sposta in avanti 
    L->next = stacca(L->next, k-1, resto); //la lista ha almeno un elemento e k>1 
    //ritorno dalle chiamate, il mio puntatore L sarà tornato indietro al primo elemento della lista
    return L;
}

/*PRE=(lista(L),lista(L1),e lista(L2) sono ben formate, A contiene dimA elementi non negativi, 
con dimA pari>=0, vL=lista(L),vL1=lista(L1),vL2=lista(L2))    */

void Fric(nodo*L, int * A, int dimA, nodo *&L1, nodo *& L2){ //funzione principale che richiama le due ausiliarie
    if(!L){ //Caso base 1
        return ; //se la lista è vuota non ho nulla da staccare
    }
    if(!dimA){ //Caso base 2
        L1= conc(L1, L); //se l'array è finito non ho più nodi da distribuire quindi i restanti (il precedente caso base mi dice che ne ho almeno uno) devono essere messi in L1 come da consegna
        return ;
    } 
    nodo* resto = 0; //puntatore che mi serve per il resto della lista
    nodo* x1 =  stacca(L, A[0], resto); //x1 prende la porzione staccata
    L= resto; //L diventa il resto della lista
    resto = 0; //ri inizializzo resto
    L1 = conc(L1, x1); //concateno la porzione staccata ad L1
    
    nodo* x2 = stacca(L,A[1], resto);//x2 prende la porzione staccata
    L= resto; //L diventa il resto della lista
    resto = 0; //ri inizializzo resto
    L2 = conc(L2, x2); //concateno la porzione staccata ad L2
    
    /*PRE_ric=(lista(L),lista(L1),e lista(L2) sono ben formate, A[2..dimA-2] elementi non negativi, 
con dimA-2 pari>=0, vL=lista(L)-lista(x1)-lista(x2), vL1=lista(L1)@lista(x1), vL2=lista(L2)@lista(x2))    */
	
	//ho controllato due valori quindi aumento di 2 A e diminuisco di 2 dimA
    Fric(L, A+2, dimA-2, L1,L2); //passo induttivo
    
    /*POST_ric=(i  nodi  di  vL  sono  distribuiti  correttamente  su  2  
liste  X1  e  X2  secondo  i  valori  di  A[2..dimA-2]  e  L1=vL1@X1  e L2=vL2@X2) */
}
/*POST=(i  nodi  di  vL  sono  distribuiti  correttamente  su  2  
liste  X1  e  X2  secondo  i  valori  di  A  e  L1=vL1@X1  e L2=vL2@X2) */

//----------------- funzioni iterative


nodo*concI(nodo*L, nodo*n){ //concatenazione di due liste
    if(!L) return n;
    if(!n) return L;
    nodo* primo=L;
    while(L->next){
        L=L->next;
    }
    L->next = n;
    return primo;
}

nodo* staccaI(nodo*L, int k, nodo*& resto){ //stacca una porzione di lista (return) e il resto della lista in "resto"
    if(!k){ //ho 0 nodi da staccare
        resto =L;
        return NULL;
    }
    nodo* primo =L; //puntatore al primo nodo della lista
    
    while(L && k>1){ //Filè ha detto meglio L->next piuttosto che L, quindi dovrei fermarmi al nodo precedente 
        L=L->next; //vado avanti a scorrere la lista
        k--; //diminuisco k (ho già controllato un nodo quindi devo fare k-1)
    }
    if(!L){ //se la lista finisce prima di k (presumo che in questo caso k sia ancora >1) allora restituisco i nodi di L (per esempio L ha due nodi ma k = 4)
        resto=0;
        return primo;
    }
    else{ //la lista ha più di k nodi quindi ho un resto 
        resto=L->next;
        L->next= 0; //stacco la porzione dal resto della lista
        return primo; // ritorno il puntatore al primo nodo
    }
}    
    
/*PRE=(lista(L),lista(L1),e lista(L2) sono ben formate, A contiene dimA elementi non negativi, 
con dimA pari>=0, vL=lista(L),vL1=lista(L1),vL2=lista(L2))    */

void Fiter(nodo* L, int *A, int dimA, nodo*&L1, nodo *&L2){ //funzione principale che richiama le due ausiliarie precedenti
    //R=(dimA>=0)&&(lista(L), lista(L1),e lista(L2) sono ben formate)&&(A[0..dimA] elementi non negativi)
    //&&(dimA e' pari >=0)&&(vL=lista(L)-lista(x1)-lista(x2), vL1=lista(L1)@lista(x1), vL2=lista(L2)@lista(x2))
  
    while(L && dimA>0){
        nodo* resto = 0; //puntatore che mi serve per il resto della lista
        nodo* x1 =  staccaI(L, A[0], resto); //x1 prende la porzione staccata
        L= resto; //L diventa il resto della lista
        resto = 0; //ri inizializzo resto (non strettamente necessario, infatti si andrebbe a sovrascrivere, vale per tutti i resto = 0)
        L1 = concI(L1, x1); //concateno la porzione staccata ad L1
        
        nodo* x2 = staccaI(L,A[1], resto); //x2 prende la porzione staccata
        L= resto;//L diventa il resto della lista
        resto = 0; //ri inizializzo resto
        L2 = concI(L2, x2);//concateno la porzione staccata ad L2
        
        A += 2; //ho controllato due valori quindi aumento di 2
        dimA -= 2;
    }
    //dimA e' 0 ma non so se ho ancora elementi nella lista(ho due condizioni di uscita dal ciclo)
    if(L) L1 = concI(L1, L);
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
  L1=0;
  L2=0;
  Fiter(X,A,dimA,L1,L2);
  stampa(L1);
  stampa(L2);
  cout<<"end"<<endl;
}
