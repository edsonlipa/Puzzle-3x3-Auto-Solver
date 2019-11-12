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
    stack<T*> solver_queue;
public:
    solver_tree();
    solver_tree(T &n);
    bool solve();
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
bool solver_tree<T>::solve()
{
    while (!this->solver_queue.empty())
    {
        T * top=solver_queue.top();
        solver_queue.pop();
        if(top->is_solved()){
            cout<<"\033[1;32mexito el puzzle ha sido resuelto\033[0m\n"<<endl;
            int counter= -1;
            set<vector<vector<int>>> comprobador;
            while (top!=NULL)
            {
                top->print_matrix();
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
                    this->current_state.insert(son->getpuzz());
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

int main(){
    srand(time(NULL));
    //node_puzzle node("input_matrix.input",3);
    node_puzzle node(3);
    solver_tree<node_puzzle> st(node);
    st.solve();
    
    /*
    node_puzzle cp(3);
    cp.print_matrix();
    cout<<"score: "<<cp.get_score()<<endl;
    cp.move_up();
    cp.print_matrix();
    cout<<"score: "<<cp.get_score()<<endl;
    cp.move_left();
    cp.print_matrix();
    cout<<"score: "<<cp.get_score()<<endl;
    cp.move_right();
    cp.move_right();
    cp.move_right();
    cout<<cp.is_solved()<<endl;*/ 
    return 0;
}