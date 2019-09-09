 
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

nodo* buildList(int n){
    if(n == 0) return NULL;
    int x; cin >> x;
    return new nodo(x,buildList(n-1));
}

nodo* aux(nodo* &L, int x){
    
}

//PRE = L lista ben formata
nodoL* Gric(nodo* L){
    
}
//POST = restituisce lista concatenata LL di nodi di tipo nodoL con tanti nodi quanti sono
//       i pezzi CeNA di L e tale che il primo nodo di LL ha campo p che punta al primo pezzo
//       CeNA di L, il secondo nodo punta al secondo pezzo CeNA e così via. I pezzi CeNA puntati
//       da LL sono trasformati in liste ben formate mettendo a 0 il campo next del loro ultimo nodo)

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
    int n;
    cin >> n;
    nodo* L = buildList(n);
    stampaL(L);
    nodoL* y = Gric(L);
    stampaLL(y);
    //nodoL* ordinata = ordina(y);
    //cout << endl;
    //stampaLL(ordinata);
    return 0;
}
