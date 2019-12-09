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
    nodo* ri=r;
    if(!r){
        r=new nodo(x,1,0,0);
    }else{
        bool vai=true;
        while(vai){
            r->num++;
            if(x>r->info){
                if(!r->right){
                    r->right=new nodo(x,1);
                    vai=false;
                }else{
                    r=r->right;
                }
            }else if(x<r->info){
                if(!r->left){
                    r->left=new nodo(x,1);
                    vai=false;
                }else{
                    r=r->left;
                }
            }
        }
        r=ri;
    }
}
	
/* POST=(albero(r) è ben formato, BST e con i campi num corretti ed è ottenuto da Vr 
		aggiungendo il nodo con info=x come foglia) */

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