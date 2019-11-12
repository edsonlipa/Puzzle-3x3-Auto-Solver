#ifndef NODE_COMPARATOR_H
#define NODE_COMPARATOR_H

#include<bits/stdc++.h>
#include "node_puzzle.h"
using namespace std;

class node_comparator
    {
    bool reverse;
    public:
    node_comparator(const bool& revparam=false)
        {reverse=revparam;}
    bool operator() (node_puzzle* &lhs, node_puzzle* &rhs) const
    {
        if (reverse) return (lhs->get_score()>rhs->get_score());
        else return (lhs->get_score()<rhs->get_score());
    }
    };

#endif