#include<iostream>
using namespace std;
struct nodo {
	int info,num;
	nodo* left, *right;
	nodo(int a=0,int b=1, nodo*c=0, nodo*d=0) {
		info=a;
		num=b;
		left=c;
		right=d;
	}
};

void build_BST(nodo*&r, int x)
{
  if(!r)
    r=new nodo(x);
  else
    {
      nodo*q=r;
      bool continua=true;
      while (r && continua)
	{
	  r->num=r->num+1;
	  if(r->info >=x)
	    if(r->left)
	      r=r->left;
	      else
		{r->left=new nodo(x); continua=false;}
	    else
	      if(r->right)
		r=r->right;
	      else
		{r->right=new nodo(x); continua=false;}
	}
      r=q;
    }
}
void stampa_lin(nodo*r)
{
  if(r)
    {
      cout <<'['<<r->info<<','<<r->num<<']'<<'(';
      stampa_lin(r->left);
      cout<<',';
      stampa_lin(r->right);
      cout<<')';
    }
  else
  cout<<'_';
}

nodo* trova_aux(nodo *r, int& n) {
    if(r->left){
        nodo* L=trova_aux(r->left,n);
        if(n==1){return L;}
    }
    if(r->right){
        //n--;
        nodo* L1=trova_aux(r->right,n);
        if(n==1){return L1;}
    }
    if(n==1){
        return r;
    }else{
        n--;
        return r; 
    }
    
}

//PRE=(albero(r) è benformato, n>0)
nodo* trova (nodo*r, int n) {
    if(!r || n>r->num){
        return NULL;
    }
    nodo* L=trova_aux(r,n);
    if(L){
        return L;
    }
    else{
        return 0;
    }
}
//POST=(se albero(r) contiene almeno n nodi, restituisce il puntatore al nodo numero n nell’ordinamento determinato
//dalla visita postfissa di albero(r), altrimenti restituisce 0)

int main() {
  cout<<"start"<<endl;
  int n;
  nodo*R=0;
  cin >>n;
    while (n !=-1)
      {
      build_BST(R,n);
      cin>>n;
      }
  stampa_lin(R);
  cout<<endl;
  cin >>n;
  while(n!=-1)
    {
      nodo*x=trova(R,n);
      if(x)
	cout<<"nodo n."<<n<<" info = "<<x->info<<endl;
      else
	cout<<"nodo n."<<n<<" non c'è"<<endl;
      cin>>n;
    }
  cout<<"end"<<endl;
}

