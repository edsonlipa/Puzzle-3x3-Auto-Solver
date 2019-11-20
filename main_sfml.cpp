#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include"solver_tree.h"
using namespace std;

sf::Texture img0,img1,img2,img3,img4,img5,img6,img7,img8;
vector<sf::Texture> text_vec;
vector<node_puzzle* > solution;
vector<vector<int>> full_matrix(){
    vector<vector<int>> puzz= vector<vector<int>>(3,vector<int>(3,0));
    
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            puzz[i][j]=(i*3)+j;
        }
    }
    return puzz;
}
void draw_puzzle(vector<vector<int>> &puzz,sf::RenderWindow &windows){
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(300, 0)),
        sf::Vertex(sf::Vector2f(300, 900))
    };
    sf::Vertex line1[] =
        {
            sf::Vertex(sf::Vector2f(600, 0)),
            sf::Vertex(sf::Vector2f(600, 900))
        };
    sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(0, 300)),
            sf::Vertex(sf::Vector2f(900, 300))
        };
    sf::Vertex line3[] =
        {
            sf::Vertex(sf::Vector2f(0,600 )),
            sf::Vertex(sf::Vector2f(900, 600))
        };


    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            sf::Sprite sp;
            sp.setTexture(text_vec[puzz[i][j]]);
            sp.setPosition(j*300,i*300);
            windows.draw(sp);
            //cout<<puzz[i][j]<<" ";
        }//std::cout<<std::endl;
    
    }//std::cout<<std::endl;
    windows.draw(line, 2, sf::Lines);
    windows.draw(line1, 2, sf::Lines);
    windows.draw(line2, 2, sf::Lines);
    windows.draw(line3, 2, sf::Lines);
    
}
void load_images(){
    img0.loadFromFile("split/white.jpg");text_vec.push_back(img0);
    img1.loadFromFile("split/8.jpg");text_vec.push_back(img1);
    img2.loadFromFile("split/7.jpg");text_vec.push_back(img2);
    img3.loadFromFile("split/6.jpg");text_vec.push_back(img3);
    img4.loadFromFile("split/5.jpg");text_vec.push_back(img4);
    img5.loadFromFile("split/4.jpg");text_vec.push_back(img5);
    img6.loadFromFile("split/3.jpg");text_vec.push_back(img6);
    img7.loadFromFile("split/2.jpg");text_vec.push_back(img7);
    img8.loadFromFile("split/1.jpg");text_vec.push_back(img8);

}
int main()
{   
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
    load_images();    
    node_puzzle node("input_matrix.input",3);
//    node_puzzle node(3);
    solver_tree<node_puzzle> st(node);
    if(st.solve(solution))cout<<"solucion encontrada"<<endl;
    int count=solution.size()-1;
    vector<vector<int>> test = node.getpuzz();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    cout<<"anterior :"<<count<<endl;
                    test=solution[(count<solution.size()-1)?++count:count]->getpuzz();
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    cout<<"siguiente :"<<count<<endl;
                    test=solution[(count>0)?--count:count]->getpuzz();
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                cout<<"presion "<<count++<<endl;
                }   
                else if (event.key.code == sf::Keyboard::Down)
                {
                cout<<"presion "<<count++<<endl;
                }

            }
        }
        
        window.clear(sf::Color(0, 255, 255, 128));
        draw_puzzle(test,window);
        
        window.display();
    }

    return 0;
}

//crear eventos 
//posicionar solve 
//crear contenerdor vector
//crear contador
