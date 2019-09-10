#include<iostream>
using namespace std;

struct nodo {
    char chiave;
    nodo *next;
    nodo(char c='\0', nodo* n=NULL){
        chiave=c;
        next=n;
    };
};

struct coda {
    nodo *inizio;
    nodo *fine;
    coda(nodo* i=NULL, nodo* f=NULL){
        inizio=i;
        fine=f;
    };
};

void push(char c, coda &Q);
int pop(coda &Q);
bool e_vuota(coda Q);

// COPIARE QUI I METODI DELLA LIBRERIA `coda` IMPLEMENTATI PER L'ESERCIZIO 1
bool e_vuota(coda Q){
    if(!Q.fine&&!Q.inizio){
        return true;
    }else{
        return false;
    }
}

void push(char c, coda &Q){
    nodo* n=new nodo(c);
    if(e_vuota(Q)){
        Q.fine=n;
        Q.inizio=n;
    }else{
        Q.fine->next=n;
        Q.fine=n;
    }
    return;
}

int pop(coda &Q){
    if(e_vuota(Q)){
        char b='\0';
        return b;
    }else{
        nodo* n=Q.inizio;
        int c=Q.inizio->chiave;
        if(Q.inizio==Q.fine){
            Q.inizio=Q.fine=0;
        }else{
            Q.inizio=n->next;
        }
        delete(n);
        return c;
    }
}

int main() 
{
    coda Q;
    int n,k;
    cout << "start" << endl;
    // IMPLEMENTARE LA SOLUZIONE DELL'ESERCIZIO UTILIZZANDO LE FUNZIONI ESPOSTE DALLA LIBRERIA `coda`
    cin>>n>>k;
    int a=0;
    while(a<n){
        push(a,Q);
        a++;
    }
    int pers;
    while(Q.inizio!=Q.fine){
        int j=0;
        while(j<k-1){
            push(pop(Q),Q);
            j++;
        }
        pers=pop(Q);
        cout<<pers<<" eliminata"<<endl;
    }
    pers=Q.inizio->chiave;
    cout<<pers<<" sopravvive"<<endl;
    cout << "end" << endl;
}