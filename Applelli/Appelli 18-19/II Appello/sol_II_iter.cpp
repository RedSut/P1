#include<iostream>
using namespace std;
struct nodo {int info,num; nodo* left,*right; nodo(int a=0,int b=1, nodo*c=0, nodo*d=0){info=a; num=b; left=c; right=d;} };

void stampa_lin(nodo*r) {
	if(r) {
		cout <<'['<<r->info<<','<<r->num<<']'<<'(';
		stampa_lin(r->left);
		cout<<',';
		stampa_lin(r->right);
		cout<<')';
	}
	else
		cout<<'_';
}

/* PRE=(albero(r) è un albero binario benformato e BST in cui il campo num di ciascun nodo
		è corretto, Vr=albero(r), x è un qualsiasi intero) */
void build_BST(nodo*&r, int x) {
	if (!r) {
		r=new nodo(x);
	}
	// r!=0
	else {
		nodo* p=r;
		bool ok=true;
		/* PRE=(albero(r) e' un albero binario che soddisfa la proprieta' BST, non vuoto e in cui 
				il campo num di ciascun nodo e' corretto, p e' un puntatore a nodo che punta 
				all'albero(r), ok e' una booleana, la quale indica che non e' stato ancora inserito 
				il nodo con campo info=x come foglia mantenendo la proprieta' BST */
		while (ok) {
		/* R=((p!=0 punta a un nodo dell'albero(r) che e' non vuoto e mantiene la proprieta' BST 
			   && (p->num>=1) && (ok==true se non ho inserito il nodo con campo info=x come foglia mantenendo la 
			   proprieta' BST, false altrimenti)) */
			p->num=p->num+1;
			if(x<p->info) {
				if(!p->left) {
					p->left=new nodo(x);
					ok=false;
				}
				else {
					p=p->left;
				}
			}
			// x>p->info
			else {
				if(!p->right) {
					p->right=new nodo(x);
					ok=false;
				}
				else {
					p=p->right;
				}			
			}
		}
	}
}
/* POST=(albero(r) è ben formato, BST e con i campi num corretti ed è ottenuto da Vr 
		 aggiungendo il nodo con info=x come foglia) */

/* DIMOSTRAZIONE DI CORRETTEZZA 
Per dimostrare che il programma e' corretto devo dimostrare che:
1) la PRE del ciclo => l'invariante R del ciclo.
2) l'invariante R del ciclo && la condizione B del while e il corpo => l'invariante R del ciclo.
3) l'invariante R del ciclo && la negazione della condizione del ciclo (!B) => la POST del ciclo e della funzione.

1) l'invariante R rispetta la condizione iniziale? Sì:
- Prima di entrare nel ciclo while albero(r) e' un albero ben formato e non vuoto che soddisfa la 
  proprieta' BST per la PRE della funzione.
- p e' un puntatore p!=0 che punta alla radice di albero(r) in quanto r e' non vuoto quindi e' formato
  da almeno un nodo e p punta a tale nodo.
- Prima di entrare nel ciclo p->num sara' 1 se albero(r) ha solo la radice e quindi e' corretto, 
  altrimenti p->num>1 se ho gia' inserito nodi precedentemente nell'albero(r) e i nodi sottostanti p
  avranno il campo num corretto.2
- ok==true perche' non ho ancora inserito il nodo con campo info=x come foglia mantenendo la proprieta' 
  BST.
  
2) R rispetta l'invarianza? Si':
- all'inizio del ciclo incremento il campo num del nodo a cui punta p, questo perche' sto andando a inserire
  un nuovo nodo all'albero (infatti r e' non vuoto e quindi posso scorrere l'albero tramite il puntatore p
  in modo tale da andare a inserire il nodo con campo info=x come foglia mantenendo la proprieta' BST).
  Ad ogni iterazione p puntera' a un nodo diverso, si sposta in profondita' (a sinistra se x<p->info 
  e a destra viceversa). Il campo num del nodo corrente viene incrementato di 1 fino a quando non viene 
  inserito il nodo (per la condizione del while). Questo fa sì che ciascun nodo abbia il campo num parzialmente
  corretto considerando che verra' inserito un nuovo nodo in quel ramo.
  A questo punto ho due casi:
a: se x<p->info allora vuol dire che per mantenere la proprieta' BST devo andare a inserire il nodo con 
   campo info=x a sinistra del nodo corrente. A questo punto ho due sottocasi:
   - Se il nodo corrente (ovvero il nodo a cui p punta) non ha una foglia a sinistra allora vuol dire che
   possiamo inserire il nuovo nodo a sinistra, quindi viene eseguita l'istruzione p->left=new nodo(x);
   A questo punto, dato che abbiamo inserito il nodo con campo info=x mantenendo la proprieta' BST
   possiamo uscire dal ciclo quindi viene eseguita l'istruzione ok=false per negare la condizione del
   while e uscire dal ciclo.
   - Se il nodo corrente ha gia' una foglia a sinistra allora vuol dire che dobbiamo scendere di un livello
   nel nostro albero tramite il puntatore p perche' il nodo non puo' essere ancora inserito dato che la
   posizione della foglia sinistra e' occupata da un altro nodo ben definito (con un certo campo info),
   quindi viene eseguita l'istruzione p=p->left e a questo punto p punta al nodo piu' a sinistra del 
   vecchio nodo a cui puntava prima.
b: se x>=p->info il ragionamento e' analogo. Data la consegna assumo che alla funzione non verra' mai 
   passato un intero x uguale a uno precedente, quindi l'else va bene poiche' ricopre il caso x<p->info. 
   Per la proprieta' BST dobbiamo andare a inserire il nodo con campo info=x a destra del nodo corrente 
   a cui punta p, quindi ho di nuovo due casi: p->right esiste oppure no. Se esiste faccio scorrere 
   il puntatore p di un livello piu' in basso puntando alla foglia destra quindi p=p->right e proseguo 
   con il ciclo. Altrimenti inserisco il nodo con campo info=x a destra del nodo corrente a cui punta p 
   e definisco ok=false (corretto per l'invariante R) in modo da poter uscire dal ciclo poiche' il nodo 
   con campo info=x e' stato inserito nell'albero(r) mantenendo la proprieta' BST. Quindi per ogni passo 
   di iterazione p continua a puntare a un nodo dell'albero(r) mantenendo la proprieta' BST dell'albero, 
   il campo num del nodo corrente viene incrementato di 1 && ok rimane true finche' non ho inserito il 
   nodo con campo info=x mantenendo la proprieta' BST, dopo diventa false per uscire dal ciclo.

3) R rispetta la condizione di uscita? Sì:
Usciremo dal ciclo while nel momento in cui ok non e' piu' true, ovvero false, cioe' subito dopo 
aver inserito il nodo con campo info=x nell'albero(r) mantenendo la proprieta' BST. Questo implica 
la POST della funzione e del ciclo in quanto albero(r) continua a essere un albero ben formato e BST, 
ed e' appunto ottenuto da Vr aggiungendo il nodo con campo info=x come foglia: a destra se x>p->info, 
a sinistra altrimenti. Alla fine del ciclo p non esistera' piu' ma il nodo sara' stato inserito 
mantenendo la proprieta' BST e r verra' modificato in quanto viene passato per riferimento. 
Alla fine del ciclo, dopo aver inserito il nuovo nodo i campi num dell'albero(r) risulteranno corretti 
nel totale poiche' sono stati incrementati ogni volta che il puntatore p scendeva in profondita' 
percorrendo il cammino corretto per mantenere la proprieta' BST dell'albero(r).
*/

main() {
	cout<<"start"<<endl;
	int n;
	nodo*R=0;
	cin >>n;
	while (n !=-1) {
		build_BST(R,n);
		cin>>n;
	}
	stampa_lin(R);
	cout<<endl;
	cout<<"end"<<endl;
}