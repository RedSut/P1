#include<iostream>
using namespace std;

struct nodo{int info; nodo* next; nodo(int a =0, nodo* b=0){info=a; next=b;}};
struct nodoL{nodo* info; nodoL* next; nodoL(nodo* a =0, nodoL* b=0){info=a; next=b;}};



nodo* clone(nodo*L)
{
  if(L)
    return new nodo(L->info,clone(L->next));
  return 0;
}

void stampaL(nodo*L)
{
  if(L)
    {cout<<L->info<<' '; stampaL(L->next);}
  else
    cout<<endl;

}
void stampaLL(nodoL*LL,int n)
{
  if(LL)
    {cout<<"fetta "<<n<<") "; stampaL(LL->info); stampaLL(LL->next,n+1);}
}

nodo* faiL(int n)
{
  if(n>0)
    return new nodo(n, faiL(n-1));
  return 0;

}

int contan_ric(nodo*L) {
	if (!L) return 0;
    
    return 1+contan_ric(L->next);
}

// PRE=(lista(L) corretta, dimA >=0 e A contiene dimA interi non negativi (quindi è possibile anche il valore 0), vL= valore iniziale di L)

//RICORSIVA

// POST=(restituisce una lista di nodi di tipo nodoL che puntano alle fette di vL secondo quanto descritto nell’esempio precedente, 
// L è quello che resta di vL una volta tolte le fette)

// PRE=(lista(L) corretta, dimA >=0 e A contiene dimA interi non negativi (quindi è possibile anche il valore 0), vL= valore iniziale di L)

int contaLiter(nodo *L){
    int i=0;
    while (!L){
        L=L->next;
        i++;
    }
    return i;
}

nodo* tagliaLiter(nodo*L, int N) {
	while(N>1 && L) {
		L=L->next;
		N=N-1;
	}
	return L; // caso base
}

nodoL* affettaiter(nodo*& L, int* A, int dimA){
  nodoL* inizio=new nodoL(0);
	nodoL* LL=inizio;
  bool esci=false;
    for(int i=0 ; i<dimA && (!esci) ; i++){
        int N=A[i];
        int nL = contaLiter(L);
        if(N==0){
            if(i==dimA-1 || (A[i+1]>contaLiter(L))){
                LL->info=0; //Creo il nodo a 0
                LL->next=0;
            }else{
                LL->next=new nodoL(0); // LL punta all'ultimo nodo corrente, creo un nuovo nodo successivo vuoto
				        LL=LL->next;
            }
        }
        if(N!=0 && !L){
            esci=true;
        }
        if(nL>=N && N>0){
            nodo* aux = tagliaLiter(L,N);
            nodo* aux1 = L;
            L = aux->next; //Taglio L
            aux->next = 0; //pulisco aux
            if(i!=dimA-1 && A[i+1]<=contaLiter(L)){
                LL->next = new nodoL(0);
                LL->info = aux1;
                LL=LL->next;
            }else{
                LL->info = aux1;
            }
            if(A[i+1]>contaLiter(L)) {
			          esci=true;
			      }
        }
        if(nL<N && N>0){
            esci=true;
        }
    }
    return inizio;
} 

// POST=(restituisce una lista di nodi di tipo nodoL che puntano alle fette di vL secondo quanto descritto nell’esempio precedente, 
// L è quello che resta di vL una volta tolte le fette)
	
main()
{
  cout<<"start"<<endl;
  nodo* L= faiL(10);
  nodo*L0=clone(L);
  int n, A[10];
  cin >> n;
  for(int i=0; i<n; i++)
    cin >> A[i];
  //nodoL*K=affettaric(L,A,n);
  //cout<<"Lric=";
  //stampaL(L);
  //cout<<"LLric:"<<endl;
  //stampaLL(K,1);
  cout<<endl;
  nodoL* K=affettaiter(L0,A,n);
  cout<<"Liter=";
  stampaL(L0);
  cout<<"LLiter:"<<endl;
  stampaLL(K,1);
  
  cout<<"end"<<endl;
  
}
