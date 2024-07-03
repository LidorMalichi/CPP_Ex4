/*
 * Name: Lidor Malichi
 * ID: 318515947
 * Email: lidor673@gmail.com
 */

#ifndef NODE_TPP
#define NODE_TPP

#include "../include/Node.hpp"

// Constructor
template<typename T>
Node<T>::Node(const T value, size_t max_children) : value(value), max_children(max_children), current_children(0), children(max_children, nullptr){}

// Copy constructor
template<typename T>
Node<T>::Node(const Node<T>& other) : value(other.value), children(other.children){}

// Getters
template<typename T>
T Node<T>::get_value() const{return this->value;}

template<typename T>
int Node<T>::get_current_children(){return this->current_children;}

template<typename T>
vector<Node<T>*> Node<T>::get_children() const {return this->children;}

// Add child node
template<typename T>
bool Node<T>::add_child(Node<T>* node)
{
    for(size_t i = 0; i < this->max_children; i++)
    {
        if(nullptr == this->children[i])
        {
            this->children[i] = node;
            this->current_children++;
            return true;
        }
    }
    return false;
}
#endif