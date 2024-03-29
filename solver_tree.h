#ifndef SOLVER_TREE_H
#define SOLVER_TREE_H

#include<bits/stdc++.h>
#include "node_puzzle.h"
#include "node_comparator.h"
using namespace std;

typedef priority_queue<node_puzzle*, vector<node_puzzle*>, node_comparator> pq_ptr_nodes;

template<class T>
class solver_tree
{
private:
    T *root; 
    set<vector<vector<int>>> current_state;
    priority_queue<node_puzzle*, vector<node_puzzle*>, node_comparator> solver_queue;
public:
    solver_tree();
    solver_tree(T &n);
    bool solve(vector<T *>&np);
    T * get_root();
    ~solver_tree();
};

template<class T>
solver_tree<T>::solver_tree(T &n)
{
    this->root = &n;
    this->root->print_matrix();
    this->solver_queue.push(root);
    this->current_state.insert(root->getpuzz());
}
template<class T>
solver_tree<T>::solver_tree()
{
    
    this->root = new T(3);
}
template<class T>
bool solver_tree<T>::solve(vector<T *>&np)
{
    while (!this->solver_queue.empty())
    {
        T * top=solver_queue.top();
        solver_queue.pop();
        this->current_state.insert(top->getpuzz());
        if(top->is_solved()){
            cout<<"\033[1;32mexito el puzzle ha sido resuelto\033[0m\n"<<endl;
            int counter= -1;
            set<vector<vector<int>>> comprobador;
            while (top!=NULL)
            {
                top->print_matrix();
                np.push_back(top);
                comprobador.insert(top->getpuzz());
                top=top->get_father();
                counter++;

            }
            cout<<"\033[1;32mresuelto en "<<counter <<" movimientos\033[0m\n"<<comprobador.size()<<endl;
            
            return true;
        }else{
            //T * ptr = this->root;
            v_np_ptr vec= top->get_next_nodes();
            pq_ptr_nodes pq;
            for(auto &a:vec)pq.push(a);//posible error con referencia &a
            int s=pq.size();
                cout<<"pq size "<<pq.size()<<endl;        
            
            for (size_t i = 0; i < s; i++)
            {
                node_puzzle * son = pq.top();
                //son->print_matrix();
                if(!current_state.count(son->getpuzz())){
                    this->solver_queue.push(son);
                    //this->solver_queue.top()->print_matrix();
                }else{
                    cout<<"existe en los estados"<<endl;
                }
                pq.pop();
            }
            //solver_queue.top()->print_matrix();
            cout<<"tamanho de la pila "<<solver_queue.size()<<endl;
            cout<<"tamanho del set "<<current_state.size()<<endl;
        }

    }
    cout<<"\033[1;31mNo ha podido ser resuelto\033[0m\n"<<endl;

    return false;
}

template<class T>
T* solver_tree<T>::get_root()
{
    return this->root;
}

template<class T>
solver_tree<T>::~solver_tree()
{

}

#endif