 
#include<iostream>
using namespace std;

struct nodo
{
    int info;
    nodo *next;
    nodo(int a=0, nodo *b=0){
        info = a;
        next = b;
    }
};

struct nodoL
{
    nodo* info;
    nodoL *next;
    nodoL(nodo* a=NULL, nodoL* b=NULL){
        info = a;
        next = b;
    }
};

nodo *buildL(int k)
{
	if(!k) return 0;
	else {
		int x;
		cin>>x;
		return new nodo(x,buildL(k-1));
    }
}

nodo* clone(nodo*L)
{
	if(!L) return 0;
	else
		return new nodo(L->info,clone(L->next));
}

void stampa(nodo*L);
void stampaL(nodoL*LL)
{
	if(LL) {
		stampa(LL->info);
		stampaL(LL->next);
    }
}

void stampa(nodo*L)
{
	if(!L) cout<<endl;
	else {
      cout<<L->info<<' ';
      stampa(L->next);
	}
}

/*nodo* buildList(int n){
    if(n == 0) return NULL;
    int x; cin >> x;
    return new nodo(x,buildList(n-1));
}*/

nodo* aux(nodo* &L, int x){
    if(!L){
        return NULL;
    }
    if(L->info<x){
        nodo* tmp= L;
        L=NULL;
        return tmp;
    }
    return aux(L->next,L->info);
}

//PRE = L lista ben formata
nodoL* Gric(nodo* L){
    if(!L){
        return NULL;
    }
    nodoL* tmp = new nodoL(L);
    nodo* pros = aux(L,L->info);
    tmp->next = Gric(pros);
    return tmp;
}
//POST = restituisce lista concatenata LL di nodi di tipo nodoL con tanti nodi quanti sono
//       i pezzi CeNA di L e tale che il primo nodo di LL ha campo p che punta al primo pezzo
//       CeNA di L, il secondo nodo punta al secondo pezzo CeNA e così via. I pezzi CeNA puntati
//       da LL sono trasformati in liste ben formate mettendo a 0 il campo next del loro ultimo nodo)

int contaiter(nodo* L){
    int i=0;
    while(L){
        L=L->next;
        i++;
    }
    return i;
}

int contaiLLter(nodoL* LL){
    int i=0;
    while(LL){
        LL=LL->next;
        i++;
    }
    return i;
}

nodoL* mettiiter(nodoL* ins, nodoL* F){
    if(!F){
        return ins;
    }
    if(contaiter(ins->info)>contaiter(F->info)){
        ins->next=F;
        return ins;
    }
    nodoL* Fi=F;
    while (F->next && contaiter(ins->info)<=contaiter(F->info)){
        F=F->next;
    }
    if(!F->next){
        F->next=ins;
    }else{
        ins->next=F->next;
        F->next=ins;
    }
    return Fi;
}

//PRE = (lista(LL) ben formata di nodi nodoL)
nodoL* ordina(nodoL* LL){
    nodoL* F = nullptr;
    while (LL){
        nodoL* LLcp = LL;
        LL = LL->next;
        LLcp->next=0;
        F = mettiiter(LLcp,F);
    }
    return F;
}
//POST = (restituisce la lista LL’che contiene i nodi di LL ordinatiper lunghezza decrescente dei pezzi puntati. 
//       I nodi che puntano a pezzi di uguale lunghezza mantengono la loro posizione relativain LL)

//PRE = (lista(LL) ben formata di nodi nodoL)
/*nodoL* ordina(nodoL* LL){  PRIMA VERSIONE NON FUNZIONANTE
    nodoL* LLcp = LL;
    nodoL* LLf = new nodoL(0);
    nodoL* LLi = LLf;
    //cout<<"1 ";
    int N=contaiLLter(LL);
    for(int i=0;i<N;i++){
        cout<<"99 ";
        int Nprev=0;
        nodo* L = new nodo(0);
        while (LL){
            int NL = contaiter(LL->info);
            if(NL>Nprev){
                Nprev=NL;
                L=LL->info;
            }
            LL=LL->next;
        }
        stampa(L);
        LLf->info=L;
        LLf=LLf->next;
        LL=LLcp;
        while (LL){
            if(LL->info==L){
                LL->info=0;
            }
            LL=LL->next;
        }
        LL=LLcp;
    }
    return LLi;
}*/
//POST = (restituisce la lista LL’che contiene i nodi di LL ordinatiper lunghezza decrescente dei pezzi puntati. 
//       I nodi che puntano a pezzi di uguale lunghezza mantengono la loro posizione relativain LL)

void stampaL(nodo* L){
    if(!L) {
        cout << endl;
        return;
    }
    cout << L->info;
    if(L->next) cout << " -> ";
    stampaL(L->next);
}

void stampaLL(nodoL* G){
    if(!G) return;
    stampaL(G->info);
    stampaLL(G->next);
}

int main(){
    cout<<"start"<<endl;
	int n;
	cin >> n;
	nodo*L=buildL(n);
	stampa(L);
   
	nodoL* LL=Gric(L);
	cout<<"Lista dei pezzi:"<<endl;
	stampaL(LL);
 
	nodoL* LL1=ordina(LL);
	cout<<"Lista ordinata:"<<endl;
	stampaL(LL1);
	cout<<"end"<<endl;
}
