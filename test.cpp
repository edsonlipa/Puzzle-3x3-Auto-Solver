#include<bits/stdc++.h>
using namespace std;

int main(){
    set<int*> myset;
    int *a;
    int *b;
    int cont=10;
    int diff=10;
    a=&cont;
    b=&cont;
    myset.insert(a);
    if(myset.count(b)!=0){
        cout<<"encontrado"<<endl;
    }else{
        cout<<"no encontrado"<<endl;

    }
    cout<<(a==b?"exito":"fail")<<endl;
    return 0;
}