#ifndef TREE_H
#define TREE_H

#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include "Node.hpp"

using namespace std;

template<typename T, size_t k = 2>
class Tree
{
    public:

    Tree();

    ~Tree();

    void clear(Node<T>* node);

    void add_root(const Node<T>& rootNode);

    bool add_sub_node(const Node<T>& parentNode, const Node<T>& childNode);

    // General Tree iterators
   
    class Iterator
        {
            public:

            enum TraversalType{DFS, BFS};

            Iterator(Node<T>* root, TraversalType type);

            Iterator(const Iterator& other);

            bool operator!=(const Iterator& other) const;

            bool operator==(const Iterator& other) const;

            Node<T>& operator*();

            Node<T>* operator->();

            Iterator& operator++();

            Iterator operator++(int);

            private:

                stack<Node<T>*> dfs_stack;

                queue<Node<T>*> bfs_queue;

                TraversalType traversal_type;
        };

    Iterator begin();
    Iterator end();
    Iterator begin_dfs_scan();
    Iterator end_dfs_scan();
    Iterator begin_bfs_scan();
    Iterator end_bfs_scan();

    // Binary Tree Iterators
    
    template<typename TraversalIterator>
        class BinaryTreeIterator 
        {
            public:

                BinaryTreeIterator(typename vector<Node<T>*>::iterator current);

                BinaryTreeIterator(const BinaryTreeIterator& other);

                bool operator!=(const BinaryTreeIterator& other) const;

                bool operator==(const BinaryTreeIterator& other) const;

                Node<T>& operator*();

                Node<T>* operator->();

                BinaryTreeIterator& operator++();

                BinaryTreeIterator& operator++(int);

        private:

            typename std::vector<Node<T>*>::iterator current;
        };

    using InOrderIterator = BinaryTreeIterator<typename vector<Node<T>*>::iterator>;
    using PreOrderIterator = BinaryTreeIterator<typename vector<Node<T>*>::iterator>;
    using PostOrderIterator = BinaryTreeIterator<typename vector<Node<T>*>::iterator>;
    using MinHeapIterator = BinaryTreeIterator<typename vector<Node<T>*>::iterator>;

    InOrderIterator begin_in_order();
    InOrderIterator end_in_order();
    PreOrderIterator begin_pre_order();
    PreOrderIterator end_pre_order();
    PostOrderIterator begin_post_order();
    PostOrderIterator end_post_order();
    MinHeapIterator begin_min_heap();
    MinHeapIterator end_min_heap();

    
    private:

        Node<T>* root;

        bool has_root;

        // Vectors to store traversal nodes
        vector<Node<T>*> traversal_nodes;

        Node<T>* find_node(Node<T>* node, T value);

        static void inorder_traversal(Node<T>* node, vector<Node<T>*>& nodes);
        static void preorder_traversal(Node<T>* node, vector<Node<T>*>& nodes);
        static void postorder_traversal(Node<T>* node, vector<Node<T>*>& nodes);
        static void minheap_traversal(Node<T>* node, vector<Node<T>*>& nodes);
        static void dfs_traversal(Node<T>* node, vector<Node<T>*>& nodes);


};

#include "../src/Tree.tpp"

#endif