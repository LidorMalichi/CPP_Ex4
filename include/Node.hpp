#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

template <typename T>
class Node
{
    public:

        // Constructor
        explicit Node(const T value, const size_t max_children = 2);

        // Copy constructor
        Node(const Node<T>& other);

        // Get node value
        T get_value() const;

        vector<Node<T>*> get_children() const;

        bool add_child(Node<T>* child);

    private:

        T value;

        size_t max_children;

        vector<Node<T>*> children;
        
};


#include "../src/Node.tpp"

#endif
