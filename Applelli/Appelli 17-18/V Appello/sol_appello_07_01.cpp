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
    
nodo* aux_aff(nodo* L, int m) { // potrei contare i nodi di L all'inizio di aux_aff per capire se mi bastano per affettare 
	// dimA e' ancora maggiore di 0 quindi ho interi dentro l'array non so pero' se L mi basta
	// ho abbastanza nodi per fare le fette
	if (m==1) return L;
	return aux_aff(L->next, m-1);
}

// PRE=(lista(L) corretta, dimA >=0 e A contiene dimA interi non negativi (quindi è possibile anche il valore 0), vL= valore iniziale di L)

nodoL* affettaric(nodo*&L, int*A, int dimA) {
	if (!dimA) return 0;
	int m=A[0];
	int c=contan_ric(L);
	if (m==0) {
		nodoL* p= new nodoL(0);
		p->next=affettaric(L, A+1, dimA-1);
		return p;
	}
	if(!L) return 0;
	if (c>=m) {
		nodo* x=aux_aff(L, m); 
		nodo*y=L;
		L=x->next;
		x->next=0;
		nodoL* z= new nodoL(y);
		z->next=affettaric(L, A+1, dimA-1);
		return z;
	}
	else return 0;
}

// POST=(restituisce una lista di nodi di tipo nodoL che puntano alle fette di vL secondo quanto descritto nell’esempio precedente, 
// L è quello che resta di vL una volta tolte le fette)

// PRE=(lista(L) corretta, dimA >=0 e A contiene dimA interi non negativi (quindi è possibile anche il valore 0), vL= valore iniziale di L)
int contan_iter(nodo* L) {
	int i=0;
	while(L) {
		L=L->next;
		i=i+1;
	}
	return i;
}

nodo* aux_aff_iter(nodo*L, int m) {
	while(m>1 && L) {
		L=L->next;
		m=m-1;
	}
	return L; // caso base
}

nodoL* affettaiter(nodo*&L, int*A, int dimA) {
	nodoL* inizio=new nodoL(0);
	nodoL* LL=inizio; 
	bool esci=true;
	for(int i=0; i<dimA && esci; i=i+1) {
		int m=A[i];
		int c=contan_iter(L);
		if (m==0) {
			if(i==dimA-1 || (A[i+1]>contan_iter(L))) {
				LL->info=0;
				LL->next=0;
			}
			else {
				LL->next=new nodoL(0); // LL punta all'ultimo nodo corrente, creo un nuovo nodo successivo vuoto
				LL=LL->next;
			}
		}
		if(m!=0 && !L) {
		    esci=false;
		}
		if (c>=m && m>0) {
			nodo* x=aux_aff_iter(L, m);
			nodo* y= L;
			L=x->next;
			x->next=0;
			if(i!=dimA-1 && A[i+1]<=contan_iter(L)) {
				LL->next= new nodoL(0);
				LL->info=y;
				LL=LL->next;
			}
			else {
				LL->info=y;
			}
			if(A[i+1]>contan_iter(L)) {
			    esci=false;
			}
			
		}
		if (m>c && m>0) {
			esci=false;
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
  nodoL*K=affettaric(L,A,n);
  cout<<"Lric=";
  stampaL(L);
  cout<<"LLric:"<<endl;
  stampaLL(K,1);
  cout<<endl;
  K=affettaiter(L0,A,n);
  cout<<"Liter=";
  stampaL(L0);
  cout<<"LLiter:"<<endl;
  stampaLL(K,1);
  
  cout<<"end"<<endl;
  
}
