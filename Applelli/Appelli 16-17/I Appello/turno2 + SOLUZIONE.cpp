#include<iostream>
using namespace std;

struct nodo{int n; char info; nodo*left,*right; nodo(char b=0, nodo*c=0, nodo*d=0, int e=0){n=e; info=b; left=c; right=d;}};

nodo* cerca1_infix(nodo*r, int& k, int *C){
    if(!r) return 0;
    else{
        if(r->left){
            *C=0;
            nodo*sx=cerca1_infix(r->left,k,C+1);
            if(sx) return sx;
        }
        if(k==1){
            *C=-1;
            return r;
        }
        else
            k=k-1;
            
        if(r->right){
            *C=1;
            nodo*dx=cerca1_infix(r->right, k, C+1);
            if(dx) return dx;
        }
    }
}

//PRE=(albero(r) è corretto, valbero(r)=albero(r))
void completa(nodo*r){
    if(r){
        completa(r->left);
        completa(r->right);
        int sx=0, dx=0;
        if(r->left)
            sx=r->left->n;
        if(r->right)
            dx=r->right->n;
        r->n=sx+dx+1;
    }
}
//POST=(albero(r) ha la stessa struttura di valbero(r), ma ogni nodo contiene nel campo n il numero
//di nodi del sottoalbero radicato in quel nodo, compreso il nodo stesso)


nodo* cerca2_infix(nodo*r, int k, int *C){
    if(!r) return 0;
    if(r->n<k) return 0;
    bool trovato=false;
    while(!trovato){
        if(r->left){ // controllo il ramo sx se esiste
            if(r->left->n>=k){ // se ha abbastanza nodi allora mi sposto
                r=r->left;
                *C=0; C++;
                }
                else{
                    k=k-r->left->n; // altrimenti li sottraggo da k
                    if(k==1){ //controllo il nodo attuale
                        *C=-1;
                        trovato=true;
                        }
                        else{ // se non lo era segno che ho cercato in quel nodo mi sposto a dx.
                            k--;
                            *C=1;
                            C++;
                            r=r->right;
                        }
                    }
            }
        else{ // se non ho trovato il nodo sx allora controllo il centro
            if(k==1){
                *C=-1;
                trovato=true;
                }
                else{ // se il centro non era quello cercato allora vado a dx
                    k--;
                    r=r->right;
                    *C=1;
                    C++;
                    }
            }
    }
    return r;
}

void stampa_l(nodo *r)//stampa albero in forma lineare usando campo info
{
  if(r)
    {
      cout<<r->info<<'(';
      stampa_l(r->left);
      cout<<',';
      stampa_l(r->right);
      cout<<')';
    }
  else
    cout<< '_';
}
void stampa_ln(nodo *r)//stampa albero in forma lineare usando campo n
{
  if(r)
    {
      cout<<r->n<<'(';
      stampa_ln(r->left);
      cout<<',';
      stampa_ln(r->right);
      cout<<')';
    }
  else
    cout<< '_';
}

nodo* parse(char*& A) //costruisce albero dalla rappresentazione lineare
{
  if(*A>='a' && *A<='z')
    {
      char p=*A;
      if(*(A+1) !='(') throw (1);
      A=A+2;
      nodo*l=parse(A);
      if(*A != ',') throw (2);
      A=A+1;
      nodo*r=parse(A);
      if(*A !=')') throw(3);
      
      A=A+1;
      return new nodo(p,l,r);
    }
  else
    if(*A=='_') {A=A+1;return 0;}
    else
      throw (4);


}
void stampaC(int*C) //stampa array che rappresenta cammino che termina con -1
{
  while(*C!=-1)
    {cout<<*C<<' '; C++;}
  cout<<endl;
}

main()
try{
  char A[100],y='a',*q=A;
  int m, M[10],C[50];
  
  while(y!='$')
    {
      cin>>y;
      *q=y;
      q++;
    }
  cin>>m;
  for(int i=0; i<m; i++)
    cin>>M[i];
  cout<<"start"<<endl;
  q=A;
  nodo* R=parse(q);
  stampa_l(R);
  cout<<endl;
 
  for(int i=0; i<m; i++)
    {
      int z=M[i];
      nodo*x=cerca1_infix(R,z,C); //domanda (1) ricorsiva
      if(x)
	{cout<<"info nodo N." << M[i]<<" ="<<x->info<<" il cammino e':" << endl; stampaC(C);}
      else
        cout<<"il nodo N."<<M[i]<<" non c'e'"<<endl;	
    }
  
  completa(R); //domanda (2) ricorsiva
					      
  stampa_ln(R);
					      
  cout<<endl;

  for(int i=0; i<m; i++)
    {
      if(M[i]<= R->n)
	{
	  nodo*x=cerca2_infix(R,M[i],C); // domanda (3) iterativa
	  cout<<"info nodo N."<<M[i]<<" =" <<x->info <<" il cammino e':"<<endl;
	  stampaC(C);
	}
      else
        cout<<"il nodo N."<<M[i]<<" non c'e'"<<endl;	
    }
  cout<<"end"<<endl;
 }
 catch(int x)
   {
     switch(x)
       {
       case 1: cout<<"manca ("<<endl;   break;
       case 2: cout<<"manca ," <<endl; break;
       case 3: cout<<"manca )"<<endl;   break;
       case 4: cout<<"non albero"<<endl;   break;
       }

   }

