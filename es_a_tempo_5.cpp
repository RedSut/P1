#include<iostream>
using namespace std;


void stampa(int*P,int m,int i)
{
  if(i==m)
    {cout<<endl; return;}
  cout<<'('<<i<<','<<P[i]<<')'<<' ';
  stampa(P,m,i+1);
}
bool trova(bool* N, int m, int i, int j, int*P){
    bool b=true,c=true,e=true;
    if(i==m-1){
        return true;
    }
    if(j!=0){
        if(N[j-1+((i+1)*m)]==true){
            P[i]=j;
            b=false;
            e=false;
            bool b1=trova(N,m,i+1,j-1,P+1);
        }
    }
    if(N[j+((i+1)*m)]==true&&b){
        P[i]=j;
        c=false;
        e=false;
        bool b2=trova(N,m,i+1,j,P+1);
    }
    if(j!=m-1){
        if(N[j+1+((i+1)*m)]==true&&b&&c){
            P[i]=j;
            e=false;
            bool b3=trova(N,m,i+1,j+1,P+1);
        }
    }
    if(e){
        return false;
    }/*else{
        if(i<m){
            if(j<m){
                bool d=trova(N,m,i,j+1,P);
            }
            bool d1=trova(N,m,i+1,0,P);
        }
    }*/
}

bool partenza(bool*N, int m, int i, int*P){
    bool b=false;
    if(i==m){
        return false;
    }
    if(N[i]==true){
        b=trova(N,m,0,i,P);
    }
    else{
        bool d=partenza(N,m,i+1,P);
    }
}


   
main()
{
  //ifstream in("input_es5t.txt");
  int m;
  cin>>m;
  int*P=new int[m];
  bool*N =new bool[m*m];
  for(int i=0; i<m*m; i++)
          cin>>N[i];
  bool x=partenza(N,m,0,P);//da fare 
  cout<<"start"<<endl;
  if(x)
    { cout<<"esiste un cammino e quello più a sinistra è:"<<endl;
      stampa(P,m,0);
     
    }    
  else
    cout<<"il cammino non esiste"<<endl;
  cout<<"end"<<endl;
      
}

