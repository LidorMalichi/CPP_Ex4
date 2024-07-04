/*
 * Name: Lidor Malichi
 * ID: 318515947
 * Email: lidor673@gmail.com
 */

#include "include/doctest.h"
#include "include/Tree.hpp"
#include "include/Node.hpp"
#include "include/Complex.hpp"
#include <sstream>

TEST_CASE("Nodes Compare")
{
    Complex c1(3.5, 2.0);
    Complex c2(1.5, 1.0);
    Complex c3(5.3, 11.0);
    Complex c4(7.2, 2.1);
    Complex c5(8.8, 6.6);
    Complex c9(3.5, 2.0);

   CHECK(c1>c2);
   CHECK(c1<c5);
   CHECK(c1!=c2);
   CHECK(c1!=c2);
   CHECK(c1==c9);
}

TEST_CASE("Tree Initialization") {
    SUBCASE("Create a Tree with valid arity") {
        Tree<int, 2> tree;
        CHECK_NOTHROW(Tree<int, 2>());
    }

    SUBCASE("Create a Tree with invalid arity") {
        CHECK_THROWS(Tree<int, 0>());
    }
}

TEST_CASE("Tree Root Node") {
    Tree<int, 2> tree;

    SUBCASE("Add root node") {
        Node<int> rootNode(10, 2);
        tree.add_root(rootNode);
        CHECK(tree.begin() != tree.end());
        CHECK((*tree.begin()).get_value() == 10);
    }

    SUBCASE("Add second root node throws exception") {
        Node<int> rootNode(10, 2);
        tree.add_root(rootNode);
        Node<int> newRootNode(20, 2);
        CHECK_THROWS_AS(tree.add_root(newRootNode), std::invalid_argument);
    }
}

TEST_CASE("Tree Sub-Nodes") {
    Tree<int, 2> tree;
    Node<int> rootNode(10, 2);
    tree.add_root(rootNode);

    SUBCASE("Add sub-node to existing parent") {
        Node<int> childNode(20, 2);
        CHECK(tree.add_sub_node(rootNode, childNode));
        auto it = tree.begin();
        ++it;
        CHECK(it != tree.end());
        CHECK((*it).get_value() == 20);
    }

    SUBCASE("Add sub-node to non-existing parent throws exception") {
        Node<int> nonExistentParentNode(30, 2);
        Node<int> childNode(20, 2);
        CHECK_THROWS_AS(tree.add_sub_node(nonExistentParentNode, childNode), std::invalid_argument);
    }

    SUBCASE("Add more children than allowed throws exception") {
        Node<int> childNode1(20, 2);
        Node<int> childNode2(30, 2);
        Node<int> childNode3(40, 2);
        tree.add_sub_node(rootNode, childNode1);
        tree.add_sub_node(rootNode, childNode2);
        CHECK_THROWS_AS(tree.add_sub_node(rootNode, childNode3), std::invalid_argument);
    }
}

TEST_CASE("Tree Traversals") {
    Tree<int, 2> tree;
    Node<int> rootNode(10);
    tree.add_root(rootNode);
    Node<int> leftChild(5);
    Node<int> rightChild(15);
    tree.add_sub_node(rootNode, leftChild);
    tree.add_sub_node(rootNode, rightChild);

    SUBCASE("InOrder Traversal") {
        std::vector<int> values;
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            values.push_back(it->get_value());
        }
        CHECK(values == std::vector<int>{5, 10, 15});
    }

    SUBCASE("PreOrder Traversal") {
        std::vector<int> values;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            values.push_back(it->get_value());
        }
        CHECK(values == std::vector<int>{10, 5, 15});
    }

    SUBCASE("PostOrder Traversal") {
        std::vector<int> values;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            values.push_back(it->get_value());
        }
        CHECK(values == std::vector<int>{5, 15, 10});
    }

    SUBCASE("BFS Traversal") {
        std::vector<int> values;
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            values.push_back(it->get_value());
        }
        CHECK(values == std::vector<int>{10, 5, 15});
    }

    SUBCASE("DFS Traversal") {
        std::vector<int> values;
        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
            values.push_back(it->get_value());
        }
        CHECK(values == std::vector<int>{10,15,5});
    }
}

TEST_CASE("Testing non-binary tree with k=3")
{
    Tree<int, 3> tree;

    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Node<int> child5(6);
    Node<int> child6(7);

    tree.add_root(root);

    CHECK(tree.add_sub_node(root, child1));
    CHECK(tree.add_sub_node(root, child2));
    CHECK(tree.add_sub_node(root, child3));
    CHECK(tree.add_sub_node(child1, child4));
    CHECK(tree.add_sub_node(child1, child5));
    CHECK(tree.add_sub_node(child2, child6));

    SUBCASE("DFS Traversal")
    {
        auto it = tree.begin_dfs_scan();
        auto end = tree.end_dfs_scan();
        
        std::vector<int> dfs_result;
        while (it != end)
        {
            dfs_result.push_back(it->get_value());
            ++it;
        }

        std::vector<int> expected_dfs = {1, 4, 3, 7, 2, 6, 5}; // Expected DFS order
        CHECK(dfs_result == expected_dfs);
    }

    SUBCASE("BFS Traversal")
    {
        auto it = tree.begin_bfs_scan();
        auto end = tree.end_bfs_scan();
        
        std::vector<int> bfs_result;
        while (it != end)
        {
            bfs_result.push_back(it->get_value());
            ++it;
        }

        std::vector<int> expected_bfs = {1, 2, 3, 4, 5, 6, 7}; // Expected BFS order
        CHECK(bfs_result == expected_bfs);
    }
}
