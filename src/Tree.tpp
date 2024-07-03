/*
 * Name: Lidor Malichi
 * ID: 318515947
 * Email: lidor673@gmail.com
 */

#ifndef TREE_TPP
#define TREE_TPP

#include "../include/Node.hpp"
#include "../include/Tree.hpp"

// Constructor
template<typename T, size_t k>
Tree<T, k>::Tree() : root(nullptr), has_root(false)
{
    if(k <= 0)
    {
        throw std::runtime_error("Tree arity nuast be greater than 0\n");
    }
}

// Destructor
template<typename T, size_t k>
Tree<T, k>::~Tree()
{
    clear(this->root);
}

template<typename T, size_t k>
void Tree<T, k>::clear(Node<T>* node)
{
    if(node)
    {
        for(auto child : node->get_children())
        {
            clear(child);
        }
        delete node;
    }
}

// Add root node
template<typename T, size_t k>
void Tree<T, k>::add_root(const Node<T>& rootNode)
{
    if (this->has_root) {
        throw std::invalid_argument("Root already exists");
    }
    // Initialize root with k children
    root = new Node<T>(rootNode.get_value(), k);
    has_root = true;
}

// Add child node to parent node
template<typename T, size_t k>
bool Tree<T, k>::add_sub_node(const Node<T>& parentNode, const Node<T>& childNode)
{
    if (!this->has_root) {
        throw std::invalid_argument("Tree has no root.");
    }
    Node<T>* parent = find_node(root, parentNode.get_value());
    if (parent) 
    {
        // Initialize child node with k children
        Node<T>* child = new Node<T>(childNode.get_value(), k);
        if (parent->add_child(child)) 
        {
            return true;
        } 
        else 
        {
            // Clean up if add_child fails
            delete child;  
            throw std::invalid_argument("Cannot add more children to the parent node.");
        }
    } else 
    {
        throw std::invalid_argument("Parent node not found.");
    }
}

// Find given node in the tree
template<typename T, size_t k>
Node<T>* Tree<T, k>::find_node(Node<T>* node, T value)
{
    if(node == nullptr){return nullptr;}

    else if(node->get_value() == value){return node;}

    for(auto child : node->get_children())
    {
        Node<T>* result = find_node(child, value);
        if (result) 
        {
            return result;
        }
    }

    return nullptr;
}

template<typename T, size_t k>
Tree<T, k>::Iterator::Iterator(Node<T>* rootNode, TraversalType type) : traversal_type(type)
{
    if(rootNode)
    {
        if(BFS == type)
        {
            this->bfs_queue.push(rootNode);
        }
        else if(DFS == type)
        {
            this->dfs_stack.push(rootNode);
        }
    }
} 

template<typename T, size_t k>
Tree<T, k>::Iterator::Iterator(const Iterator& other) 
    : bfs_queue(other.bfs_queue), dfs_stack(other.dfs_stack), traversal_type(other.traversal_type){}

template<typename T, size_t k>
bool Tree<T, k>::Iterator::operator!=(const Iterator& other) const
{
    if (this->traversal_type != other.traversal_type) 
    {
        return true;
    }

    if (traversal_type == DFS) 
    {
        if (this->dfs_stack.empty() && other.dfs_stack.empty()) {
            return false;
        }
        if (this->dfs_stack.empty() || other.dfs_stack.empty()) {
            return true;
        }
        return this->dfs_stack.top() != other.dfs_stack.top();
    } 
    else 
    {
        if (this->bfs_queue.empty() && other.bfs_queue.empty()) 
        {
            return false;
        }
        if (this->bfs_queue.empty() || other.bfs_queue.empty()) 
        {
            return true;
        }
        return this->bfs_queue.front() != other.bfs_queue.front();
    }

}

template<typename T, size_t k>
bool Tree<T, k>::Iterator::operator==(const Iterator& other) const
{
    return !(*this != other);
}

template<typename T, size_t k>
Node<T>& Tree<T, k>::Iterator::operator*()
{
   if(this->traversal_type == DFS)
   {
        return *this->dfs_stack.top();
   }
   else
   {
        return *this->bfs_queue.front();
   } 
}

template<typename T, size_t k>
Node<T>* Tree<T, k>::Iterator::operator->()
{
    if (this->traversal_type == DFS)
    {
        return this->dfs_stack.top();
    }
    else
    {
        return this->bfs_queue.front();
    }
}

template<typename T, size_t k>
typename Tree<T, k>::Iterator& Tree<T, k>::Iterator::operator++()
{
    if (this->traversal_type == DFS)
    {
        Node<T>* current = dfs_stack.top();
        dfs_stack.pop();
        for (auto child : current->get_children())
        {
            if(child)
            {
                this->dfs_stack.push(child);
            }
        }
        
    }
    else
    {
        Node<T>* current = bfs_queue.front();
        bfs_queue.pop();
        for (auto child : current->get_children())
        {
            if(child)
            {
                bfs_queue.push(child);
            } 
        }
        
    }
    return *this;  
}

template<typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::Iterator::operator++(int)
{
    Iterator temp = *this;   
    if (this->traversal_type == DFS)
    {
        Node<T>* current = this->dfs_stack.top();
        dfs_stack.pop();
        for (auto child : current->get_children())
        {
            if(child)
            {
                this->dfs_stack.push(child);
            }
        }
        
    }
    else
    {
        Node<T>* current = bfs_queue.front();
        bfs_queue.pop();
        for (auto child : current->get_children())
        {
            if(child)
            {
                bfs_queue.push(child);
            } 
        }
        
    }
    return temp;  
}

template<typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin()
{
    return Iterator(this->root, Iterator::BFS);
}

template<typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end()
{
    return Iterator(nullptr, Iterator::BFS);
}

template<typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_dfs_scan()
{
    return Iterator(this->root, Iterator::DFS);
}

template<typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_dfs_scan()
{
    return Iterator(nullptr, Iterator::DFS);
}

template<typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_bfs_scan()
{
    return Iterator(this->root, Iterator::BFS);
}

template<typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_bfs_scan()
{
    return Iterator(nullptr, Iterator::BFS);
}

template<typename T, size_t k>
void Tree<T, k>::inorder_traversal(Node<T>* node, vector<Node<T>*>& nodes)
{
    if(k == 2)
    {
        if(node == nullptr){return;}

        inorder_traversal(node->get_children()[0], nodes);
        nodes.push_back(node);
        inorder_traversal(node->get_children()[1], nodes);
    }
    else
    {
        dfs_traversal(node, nodes);
    }
}

template<typename T, size_t k>
void Tree<T, k>::preorder_traversal(Node<T>* node, vector<Node<T>*>& nodes)
{
    if(k == 2)
    {
        if(node == nullptr){return;}

        nodes.push_back(node);
        preorder_traversal(node->get_children()[0], nodes);
        preorder_traversal(node->get_children()[1], nodes);
    }
    else
    {
        dfs_traversal(node, nodes);
    }
}

template<typename T, size_t k>
void Tree<T, k>::postorder_traversal(Node<T>* node, vector<Node<T>*>& nodes)
{
    if(k == 2)
    {
        if(node == nullptr){return;}

        postorder_traversal(node->get_children()[0], nodes);
        postorder_traversal(node->get_children()[1], nodes);
        nodes.push_back(node);
    }
    else
    {
        dfs_traversal(node, nodes);
    }
}

template<typename T, size_t k>
void Tree<T, k>::minheap_traversal(Node<T>* node, vector<Node<T>*>& nodes)
{
    if(k == 2)
    {
        inorder_traversal(node, nodes);
        std::sort(nodes.begin(), nodes.end(), [](Node<T>* a, Node<T>* b) { return a->get_value() < b->get_value(); });
    }

}

template<typename T, size_t k>
void Tree<T, k>::dfs_traversal(Node<T>* node, vector<Node<T>*>& nodes)
{
    if (node == nullptr){return;}

    nodes.push_back(node);
    for (auto child : node->get_children()) {
        dfs_traversal(child, nodes);
    }
}

template<typename T, size_t k>
template <typename TraversalIterator>
Tree<T, k>::BinaryTreeIterator<TraversalIterator>::BinaryTreeIterator(typename vector<Node<T>*>::iterator current) : current(current){} 

template<typename T, size_t k>
template <typename TraversalIterator>
Tree<T, k>::BinaryTreeIterator<TraversalIterator>::BinaryTreeIterator(const BinaryTreeIterator& other) : current(other.current){}

template<typename T, size_t k>
template <typename TraversalIterator>
bool Tree<T, k>::BinaryTreeIterator<TraversalIterator>::operator!=(const BinaryTreeIterator& other) const
{
    return current != other.current;
}

template<typename T, size_t k>
template <typename TraversalIterator>
bool Tree<T, k>::BinaryTreeIterator<TraversalIterator>::operator==(const BinaryTreeIterator& other) const
{
    return current == other.current;
}

template<typename T, size_t k>
template <typename TraversalIterator>
Node<T>& Tree<T, k>::BinaryTreeIterator<TraversalIterator>::operator*()
{
    return **current;
}

template<typename T, size_t k>
template <typename TraversalIterator>
Node<T>* Tree<T, k>::BinaryTreeIterator<TraversalIterator>::operator->()
{
    return *current;
}

template<typename T, size_t k>
template <typename TraversalIterator>
typename Tree<T, k>::template BinaryTreeIterator<TraversalIterator>& Tree<T, k>::BinaryTreeIterator<TraversalIterator>::operator++()
{
    ++current;
    return *this;
}

template<typename T, size_t k>
template <typename TraversalIterator>
typename Tree<T, k>::template BinaryTreeIterator<TraversalIterator>& Tree<T, k>::BinaryTreeIterator<TraversalIterator>::operator++(int)
{
    current++;
    return *this;
}

template<typename T, size_t k>
typename Tree<T, k>::InOrderIterator Tree<T, k>::begin_in_order()
{
    this->traversal_nodes.clear();
    inorder_traversal(this->root, this->traversal_nodes);
    return InOrderIterator(this->traversal_nodes.begin());
}

template<typename T, size_t k>
typename Tree<T, k>::InOrderIterator Tree<T, k>::end_in_order()
{
    return InOrderIterator(this->traversal_nodes.end());
}

template<typename T, size_t k>
typename Tree<T, k>::PreOrderIterator Tree<T, k>::begin_pre_order()
{
    this->traversal_nodes.clear();
    preorder_traversal(this->root, this->traversal_nodes);
    return PreOrderIterator(this->traversal_nodes.begin());
}

template<typename T, size_t k>
typename Tree<T, k>::PreOrderIterator Tree<T, k>::end_pre_order()
{
    return PreOrderIterator(this->traversal_nodes.end());
}

template<typename T, size_t k>
typename Tree<T, k>::PostOrderIterator Tree<T, k>::begin_post_order()
{
    this->traversal_nodes.clear();
    postorder_traversal(this->root, this->traversal_nodes);
    return PostOrderIterator(this->traversal_nodes.begin());
}

template<typename T, size_t k>
typename Tree<T, k>::PostOrderIterator Tree<T, k>::end_post_order()
{
    return PostOrderIterator(this->traversal_nodes.end());
}

template<typename T, size_t k>
typename Tree<T, k>::MinHeapIterator Tree<T, k>::begin_min_heap()
{
    this->traversal_nodes.clear();
    minheap_traversal(this->root, this->traversal_nodes);
    return MinHeapIterator(this->traversal_nodes.begin());
}

template<typename T, size_t k>
typename Tree<T, k>::MinHeapIterator Tree<T, k>::end_min_heap()
{
    return MinHeapIterator(this->traversal_nodes.end());
}

template <typename T, std::size_t k>
void Tree<T, k>::print() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Tree Display");
        sf::Font font;
        if (!font.loadFromFile("./Lato-BlackItalic.ttf")) {
            throw std::runtime_error("Failed to load font!");
            return;
        }
        window.clear(sf::Color::White);

        // Pass the root node pointer directly
        this->tree_paint(window, *this, root, 400, 50, 200, font);
        window.display();

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    
}

template<typename T, size_t k>
void Tree<T, k>::tree_paint(sf::RenderWindow& window, Tree<T, k>& tree, Node<T>* node, float x, float y, int horizontal_gap, sf::Font& font){
         if (!node) return;

        // Drawing circle and lines...
        sf::Color circleColor = sf::Color::Green; 
        sf::Color outlineColor = sf::Color::Black; 
        sf::Color textColor = sf::Color::Black; 

        // Draw circle
        sf::CircleShape circle(30); 
        circle.setFillColor(circleColor);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(outlineColor);
        circle.setPosition(x, y);
        window.draw(circle);

        // Convert value to string with fixed precision
        T value = node->get_value();
        std::ostringstream oss;
        oss.precision(1);
        oss << std::fixed << value;
        std::string str = oss.str();

        // Draw text
        sf::Text text(str, font, 20);
        text.setFillColor(textColor);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                            textBounds.top + textBounds.height / 2.0f);
        text.setPosition(x + circle.getRadius(), y + circle.getRadius());
        window.draw(text);

        // Draw lines to children
        auto children = node->get_children();
        int num_children = node->get_current_children();
        if (num_children > 0) {
            for (size_t i = 0; i < num_children; ++i) {
                float child_x = x - horizontal_gap / 2 + i * horizontal_gap;
                float child_y = y + 100;

                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + circle.getRadius(), y + 2 * circle.getRadius())),
                    sf::Vertex(sf::Vector2f(child_x + circle.getRadius(), child_y))
                };
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
                window.draw(line, 2, sf::Lines);

                tree_paint(window, tree, children[i], child_x, child_y, horizontal_gap / 2, font);
            }
        }
    }

#endif