#ifndef NODE_PUZZLE_H
#define NODE_PUZZLE_H

#include<bits/stdc++.h>
using namespace std;
class node_puzzle;
typedef vector<vector<int>> puzzle_cont;
typedef vector<int> vi;
typedef vector<node_puzzle*> v_np_ptr;
typedef pair<int,int> ii;


class node_puzzle
{
private:

    
    int puzzle_size=3;
    int score=-1;
    ii  blank_piece;    
    puzzle_cont puzz;
    node_puzzle * father;

public:
    node_puzzle(string,int);
    node_puzzle(int n = 3);
    node_puzzle(node_puzzle * &np);
    puzzle_cont getpuzz();
    
    void init_random();
    void print_matrix();
    void update_black_piece(int,int);
    bool move_up();
    bool move_down();
    bool move_left();
    bool move_right();
    void update_score();
    int get_score();
    bool is_solved();
    bool operator ==(const node_puzzle& node)const{
        return puzz==node.puzz;
    }
    node_puzzle* get_reference(){return this;} 
    v_np_ptr get_next_nodes();
    node_puzzle * get_father(){return this->father;};
    ~node_puzzle();
};

node_puzzle::node_puzzle(string file_name,int n)
{   
    cout<<"creado por archivo"<<endl;
    blank_piece=make_pair(0,0);
    puzz= puzzle_cont(puzzle_size,vi(puzzle_size,0));
    
    puzzle_size=n;
    fstream input(file_name);
    int q;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            input>>puzz[i][j];
            if(puzz[i][j]==0){this->update_black_piece(i,j);}
        }
    }
    this->update_score();
    this->father=NULL;    
}
node_puzzle::node_puzzle(int n)
{   
    puzzle_size=n;
    blank_piece=make_pair(0,0);
    puzz= puzzle_cont(puzzle_size,vi(puzzle_size,0));
    this->init_random();    
    this->father=NULL;    
}
node_puzzle::node_puzzle(node_puzzle* &np)
{   
    this->puzzle_size= np->puzzle_size;
    this->puzz= np->puzz;
    this->score= np->score;
    this->blank_piece=np->blank_piece;
    this->father=np;
}
puzzle_cont node_puzzle::getpuzz(){
    return this->puzz;
}

void node_puzzle::init_random(){
    cout<<"iniciador random"<<endl;
    int n_sqrt=pow(puzzle_size,2);
    vi vrand(n_sqrt);
    for(int i = 0; i<n_sqrt;i++)vrand[i]=i;
    random_shuffle(vrand.begin(),vrand.end());
    for (size_t i = 0; i < puzzle_size; i++)
    {
        for (size_t j = 0; j < puzzle_size; j++)
        {
            puzz[i][j]=vrand[(i*puzzle_size)+j];
        if(vrand[(i*puzzle_size)+j]==0){this->update_black_piece(i,j);}
        }
    }
    
    this->update_score();

}

void node_puzzle::print_matrix()
{
    for (size_t i = 0; i < puzzle_size; i++)
    {
        for (size_t j = 0; j < puzzle_size; j++)
        {
            cout<<puzz[i][j]<<" ";
        }cout<<endl;
    
    }
    cout<<"score: "<<this->score<<endl;
    cout<<endl;
}
void node_puzzle::update_black_piece(int i,int j){
    this->blank_piece.first=i;
    this->blank_piece.second=j;
}
bool node_puzzle::move_up(){
    if(this->blank_piece.first>0){
            swap(this->puzz[this->blank_piece.first][this->blank_piece.second],this->puzz[this->blank_piece.first-1][this->blank_piece.second]);
            this->update_black_piece(this->blank_piece.first-1,this->blank_piece.second);
            this->update_score();
            return true;
    }else{
            //cout<<"no se puede realizar el movimiento hacia arriba "<<this->blank_piece.first<<endl;
            return false;
            
    }   
}
bool node_puzzle::move_down(){
    if(this->blank_piece.first<puzzle_size-1){
        swap(this->puzz[this->blank_piece.first][this->blank_piece.second],this->puzz[this->blank_piece.first+1][this->blank_piece.second]);
        this->update_black_piece(this->blank_piece.first+1,this->blank_piece.second);
            this->update_score();
        return true;            
    }else{

    //cout<<"no se puede realixar el movimiento hacia abajo"<<endl;
        return false;
    }   
    
}
bool node_puzzle::move_left(){
    if(this->blank_piece.second>0){
        swap(this->puzz[this->blank_piece.first][this->blank_piece.second],this->puzz[this->blank_piece.first][this->blank_piece.second-1]);
        this->update_black_piece(this->blank_piece.first,this->blank_piece.second-1);
            this->update_score();
        return true;
    }else{
            //cout<<"no se puede realixar el movimiento hacia la izquierda"<<endl;
            return false;
    }   
    
}
bool node_puzzle::move_right(){
    if(this->blank_piece.second<puzzle_size-1){
        swap(this->puzz[this->blank_piece.first][this->blank_piece.second],this->puzz[this->blank_piece.first][this->blank_piece.second+1]);
        this->update_black_piece(this->blank_piece.first,this->blank_piece.second+1);
            this->update_score();
        return true;
    }else{
        //cout<<"no se puede realixar el movimiento hacia la derecha"<<endl;
        return false;

    }   
}

int node_puzzle::get_score(){
    return this->score;
}
bool node_puzzle::is_solved(){
    return (score==0);
}
void node_puzzle::update_score(){
    
    int score = 0,i2,j2;
    for (int i = 0; i < puzzle_size; i++)
    {
        for (int j = 0; j < puzzle_size; j++)
        {
            j2=puzz[i][j]%puzzle_size;
            i2=(puzz[i][j]-j2)/puzzle_size;
            score+=abs(i-i2)+abs(j-j2);  
        }
    }
    this->score=score;
}
v_np_ptr node_puzzle::get_next_nodes(){
        v_np_ptr pq;
        node_puzzle * p = this->get_reference();
        node_puzzle * abuelo = (p->get_father()!=NULL)?p->get_father():p;        
        node_puzzle * a = new node_puzzle(p);
        if(a->move_down()&&!(*abuelo==*a))pq.push_back(a);
        a= new node_puzzle(p);
        
        if(a->move_right()&&!(*abuelo==*a))pq.push_back(a);
        a= new node_puzzle(p);

        if(a->move_up()&&!(*abuelo==*a))pq.push_back(a);
        a= new node_puzzle(p);

        if(a->move_left()&&!(*abuelo==*a))pq.push_back(a);
        //cout<<"get next nodes size "<<pq.size()<<endl;
        return pq;
}

node_puzzle::~node_puzzle()
{
}
#endif //NODE_PUZZLE_H