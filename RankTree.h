//
// Created by layan on 5/3/2023.
//

/* COMMENTS:
 * shared ptr: how to access? -> / .get()?
 *
 * */

#ifndef HW2WETDS_RANKTREE_H
#define HW2WETDS_RANKTREE_H

#include <memory>
#include <iostream>
#include <math.h>
#define POS_FACTOR 2
#define NEG_FACTOR -2

/*************************** Class & functions DECLARATIONS *************************/

template <class T, class S> class Node;

template <class T, class S>
class RankTree
{
    Node<T,S>* root;

    int getTreeSizeAux(Node<T,S>* node);

    template <class DoSomething, class Param1, class Param2>
    void inOrderAux(Node<T,S>* subtree_root, DoSomething doSomething, Param1 param1 = 0 ,Param2 param2 = 0);

    template <class DoSomething, class Param1, class Param2>
    void preOrderAux(Node<T,S>* subtree_root, DoSomething doSomething, Param1 param1=0,Param2 param2 = 0);

    template <class DoSomething, class Param1, class Param2>
    void postOrderAux(Node<T,S>* subtree_root, DoSomething doSomething, Param1 param1=0,Param2 param2 = 0);

    void destroyTreeAux(Node<T,S>* subtree_root);

public:
    RankTree() : root(nullptr) {};

    ~RankTree();

    RankTree(const RankTree& tree_to_copy) = default;

    RankTree& operator=(const RankTree& tree) = default;

    Node<T,S>* findNode(T Key) const;  //- DONE

    Node<T,S>* getRoot() const; //DONE

    bool insertNode(const T& key, const S& value);  //lul - DONE

    bool removeNode(const T& key);  //dim

    void rotateLeft(Node<T,S>* subtree_root); //lul - DONE

    void rotateRight(Node<T,S>* subtree_root); //lul  - DONE

    void rotateLL(Node<T,S>* subtree_root); //dim - DONE

    void rotateRR(Node<T,S>* subtree_root); //dim - DONE

    void rotateLR(Node<T,S>* subtree_root); //dim - DONE

    void rotateRL(Node<T,S>* subtree_root); //dim - DONE

    void balance(Node<T,S>* subtree_root); //lul  - DONE

    template <class DoSomething, class Param1, class Param2>
    void inOrder(DoSomething doSomething, Param1 param1 = 0, Param2 param2 = 0);

    template <class DoSomething, class Param1, class Param2>
    void preOrder(DoSomething doSomething, Param1 param1=0, Param2 param2 = 0);

    template <class DoSomething, class Param1, class Param2>
    void postOrder(DoSomething doSomething, Param1 param1=0, Param2 param2 = 0);

    /* for each node that is in the search path of subtree_root: this function updates its height
     * (incerements/ decrements it by 1) and its BF (using the updated heights)
     * */
    void updateAncestorHeightsAndBF(Node<T,S>* subtree_root); // lul - DONE

    /* this function changes ptr to point to the first unblanaced node that is in ptr's search path
     * will use this function for balancing and rotations.
     * might be bugged - will check later
     * */
    Node<T,S>* goToFirstUnbalanced(Node<T,S>* ptr); // lul - DONE

    bool hasOneSon(Node<T,S>* node);

    Node<T,S>* getNextInorder(Node<T,S>* node);

    Node<T,S>* getPreviousInorder(Node<T,S>* node);

    //this function checks if this node is a left son or a right son
    //true means right, false means left
    //assumes that node isn't the root. (that parent!=null)
    bool isRightSon(Node<T,S>* node);

    int getTreeSize();

    void addExtraUntil(T key,double amount);

    void addExtra(T min, T max , double amount);

    double calcExtraVal(int key);
};

template <class T, class S>
class Node
{
    T key;

    S value;

    double extra;

    Node<T,S>* left_son;

    Node<T,S>* right_son;

    Node<T,S>* parent;

    int bf;

    int height;

public:
    /* Node: Constructor
     * creates a new node with a key and a value, assigns left and right son and parent to null
     * @param new_key - the new node's key
     * @param new_value - the new node's value
     * */
    Node(const T& new_key, const S& new_value) : key(new_key), value(new_value), extra(0), left_son(nullptr),
                                                 right_son(nullptr), parent(nullptr), bf(0), height(0) {};

    Node() = default;

    ~Node() = default;

    Node(Node<T,S> &node) = default;

    Node& operator=(const Node& node) = default;

    T& getKey();

    S& getValue();

    double getExtra();

    int getHeight();

    int getBF();

    Node<T,S>* getLeftSon();

    Node<T,S>* getRightSon();

    Node<T,S>* getParent();

    void setKey(T& new_key);

    void setValue(S& new_value);

    void setExtra(double new_extra);

    void setHeight(int new_height);

    void setBF(int new_bf);

    void setRightSon(Node<T,S>* new_right_son);

    void setLeftSon(Node<T,S>* new_left_son);

    void setParent(Node<T,S>* new_parent);

    int calcHeight();

    int calcBalanceFactor();

    bool isLeaf();

    bool hasTwoSons();

    void detach();

};

/**************************** Node Class Implementation *******************************/

template<class T,class S>
T& Node<T,S>::getKey()
{
    return key;
}

template<class T,class S>
S& Node<T,S>::getValue()
{
    return value;
}

template<class T, class S>
double Node<T,S>::getExtra()
{
    return extra;
}

template<class T,class S>
int Node<T,S>::getHeight()
{
    return height;
}

template<class T,class S>
int Node<T,S>::getBF()
{
    return bf;
}

template<class T,class S>
Node<T,S>* Node<T,S>::getLeftSon()
{
    return left_son;
}

template<class T,class S>
Node<T,S>* Node<T,S>::getRightSon()
{
    return right_son;
}

template<class T,class S>
Node<T,S>* Node<T,S>::getParent(){
    return parent;
}

template<class T,class S>
void Node<T,S>::setKey(T& new_key)
{
    key = new_key;
}

template<class T,class S>
void Node<T,S>::setValue(S& new_value)
{
    value = new_value;
}

template<class T, class S>
void Node<T,S>::setExtra(double new_extra)
{
    extra = new_extra;
}

template<class T,class S>
void Node<T,S>::setHeight(int new_height)
{
    height = new_height;
}

template<class T,class S>
void Node<T,S>::setBF(int new_bf)
{
    bf = new_bf;
}

template<class T,class S>
void Node<T,S>::setRightSon(Node<T,S>* new_right_son)
{
    right_son = new_right_son;
}

template<class T,class S>
void Node<T,S>::setLeftSon(Node<T,S>* new_left_son)
{
    left_son = new_left_son;
}

template<class T,class S>
void Node<T,S>::setParent(Node<T,S>* new_parent)
{
    parent = new_parent;
}

template<class T,class S>
int Node<T,S>::calcHeight()
{
    int right_son_height = (right_son == nullptr) ? -1 : right_son->getHeight();
    int left_son_height = (left_son == nullptr) ? -1 : left_son->getHeight();
    return (right_son_height > left_son_height) ? right_son_height + 1 : left_son_height + 1; //changes layan +1
}

template<class T,class S>
int Node<T,S>::calcBalanceFactor()
{
    int left_son_height = (left_son== nullptr)? -1 : left_son->getHeight();
    int right_son_height = (right_son == nullptr) ? -1 : right_son->getHeight();
    int balance_factor = left_son_height - right_son_height;
    return balance_factor;
}

template<class T,class S>
bool Node<T,S>::isLeaf()
{
    return ((left_son == nullptr) && (right_son == nullptr));
}

template<class T,class S>
bool Node<T,S>::hasTwoSons()
{
    if(right_son && left_son) return true;
    return false;
}

template<class T,class S>
void Node<T,S>::detach()
{
    parent = nullptr;
    right_son = nullptr;
    left_son = nullptr;
}

/**************************** RankTree Class Implementation ****************************/

template <class T, class S>
void RankTree<T,S>::destroyTreeAux(Node<T,S>* subtree_root)
{
    if(!subtree_root) return;
    //T key = subtree_root->getKey();
    Node<T,S>* right_son = subtree_root->getRightSon();
    Node<T,S>* left_son = subtree_root->getLeftSon();
    destroyTreeAux(left_son);
    destroyTreeAux(right_son);
    subtree_root->detach();
    delete subtree_root;
    //subtree_root = nullptr;
}

template <class T, class S>
RankTree<T,S>::~RankTree()
{
    destroyTreeAux(root);
}

/*/
 * searches the tree for the given value
 * if found returns pointer to the node with given key
 * else returns nullptr
 */
template<class T,class S>
Node<T,S>* RankTree<T,S>::findNode(T key) const
{
    if(root == nullptr)
    {
        return nullptr;
    }
    Node<T,S>* curr = root;
    while(curr != nullptr)
    {
        if(curr->getKey() == key)
        {
            return curr;
        }
        else if(curr->getKey() > key)
        {
            curr = curr->getLeftSon();
        }
        else
        {
            curr = curr->getRightSon();
        }
    }
    return nullptr; //check
}

/* returns false if key already exists or allocation error
 * returns true with successful insertion
 * */
template<class T,class S>
bool RankTree<T,S>::insertNode(const T& key, const S& value)
{
    if(findNode(key) != nullptr) //key already exists, can't insert
    {
        return false;
    }
    Node<T,S>* new_node = new Node<T,S>(key, value);
    if(!new_node) return false;

    if(root == nullptr)
    {
        root = new_node;
        return true;
    }
    Node<T,S>* new_parent; //new_node will be new_parent's son
    Node<T,S>* curr = root;
    double sum_extras = root->getExtra();
    bool direction = true; //true - new_node will be new_parent's right son. false - will be a left son/
    while(curr)
    {
        new_parent = curr;
        if(curr->getKey() > key)
        {
            curr = curr->getLeftSon();
            if(curr) sum_extras += curr->getExtra();
            direction = false;
        }
        else if(curr->getKey() < key)
        {
            curr = curr->getRightSon();
            if(curr) sum_extras += curr->getExtra();
            direction = true;
        }
    }
    if(direction) //insert right
    {
        new_parent->setRightSon(new_node);
    }
    else //insert left
    {
        new_parent->setLeftSon(new_node);
    }

    new_node->setParent(new_parent);

    new_node->setExtra(-sum_extras);

    updateAncestorHeightsAndBF(new_node);
    curr = new_node;
    curr = goToFirstUnbalanced(curr);
    balance(curr);

    return true;
}

template <class T, class S>
bool RankTree<T,S>::removeNode(const T& key) {
    Node<T,S>* wanted_node = findNode(key);

    if (wanted_node == nullptr)
    {
        return false;
    }

    // Check if wanted node is a left son or a right son:
    bool direction = false; // false is left son, true is right son
    Node<T,S>* wanted_parent = wanted_node->getParent();

    // Check if wanted_node is root
    bool wanted_is_root = false;
    if (wanted_parent == nullptr)
    {
        wanted_is_root = true;
    }

    if (!wanted_is_root && wanted_parent->getRightSon() == wanted_node) {
        direction = true;
    }

    if (wanted_node->isLeaf()) {
        if (wanted_is_root)
        {
            delete root;
            root = nullptr;
            return true;
        }

        if (direction)
        { // right son
            wanted_parent->setRightSon(nullptr);
        }

        else
        {
            wanted_parent->setLeftSon(nullptr);
        }

        updateAncestorHeightsAndBF(wanted_parent);

        Node<T,S>* ptr = wanted_parent;
        while (ptr) {
            if (abs(ptr->getBF()) == 2) {
                break;
            }
            ptr = ptr->getParent();
        }

        while (ptr) {
            balance(ptr);
            ptr = ptr->getParent();
        }
        wanted_node->detach();
        delete wanted_node;

        return true;
    }

    // If wanted node has only one son, let wanted node's parent point to wanted_node's son
    bool left_son_exists = (wanted_node->getLeftSon() != nullptr);
    bool right_son_exists = (wanted_node->getRightSon() != nullptr);

    if (!left_son_exists || !right_son_exists) {
        Node<T,S>* child;
        if (!right_son_exists) { // right son is null - wanted_node has only left son
            child = wanted_node->getLeftSon();
        } else { // left son is null - wanted_node has only right son
            child = wanted_node->getRightSon();
        }

        child->setParent(wanted_parent);

        if (!wanted_is_root)
        {
            if (direction) {
                wanted_parent->setRightSon(child);
            } else {
                wanted_parent->setLeftSon(child);
            }
        }
        else
        {
            root = child;
        }

        updateAncestorHeightsAndBF(wanted_parent);

        Node<T,S>* ptr = wanted_parent;
        while (ptr) {
            if (abs(ptr->getBF()) == 2) {
                break;
            }
            ptr = ptr->getParent();
        }

        while (ptr) {
            balance(ptr);
            ptr = ptr->getParent();
        }

        wanted_node->detach();
        delete wanted_node;

        return true;
    }

    // Wanted node has two children: supremum_child is the following inorder child
    Node<T,S>* wanted_right_son = wanted_node->getRightSon();
    Node<T,S>* wanted_left_son = wanted_node->getLeftSon();
    Node<T,S>* supremum_child = wanted_right_son;

    while (supremum_child->getLeftSon() != nullptr) {
        supremum_child = supremum_child->getLeftSon();
    }

    Node<T,S>* supremum_parent = supremum_child->getParent();
    Node<T,S>* supremum_right_son = supremum_child->getRightSon();

    if (supremum_parent != wanted_node) {
        supremum_parent->setLeftSon(supremum_right_son);
        if (supremum_right_son != nullptr) {
            supremum_right_son->setParent(supremum_parent);
        }
    }

    supremum_child->setParent(wanted_parent);
    supremum_child->setLeftSon(wanted_left_son);
    wanted_left_son->setParent(supremum_child);

    if (supremum_child != wanted_right_son) {
        supremum_child->setRightSon(wanted_right_son);
        wanted_right_son->setParent(supremum_child);
    }

    if (!wanted_is_root) {
        if (direction) {
            wanted_parent->setRightSon(supremum_child);
        } else {
            wanted_parent->setLeftSon(supremum_child);
        }
    } else {
        root = supremum_child;
    }

    wanted_node->detach();
    delete wanted_node;

    Node<T,S>* first_to_update = supremum_child->getRightSon();
    if (!first_to_update) {
        first_to_update = supremum_child;
    }

    while (first_to_update != nullptr && first_to_update->getLeftSon() != nullptr) {
        first_to_update = first_to_update->getLeftSon();
    }

    updateAncestorHeightsAndBF(first_to_update);
    supremum_child->setHeight(supremum_child->calcHeight());
    supremum_child->setBF(supremum_child->calcBalanceFactor());

    Node<T,S>* ptr = first_to_update;
    while (ptr) {
        if (abs(ptr->getBF()) == 2) {
            break;
        }
        ptr = ptr->getParent();
    }

    while (ptr) {
        balance(ptr);
        ptr = ptr->getParent();
    }

    if (wanted_is_root) {
        auto curr = supremum_child;
        while (curr->getParent() != nullptr) {
            curr = curr->getParent();
        }
        root = curr;
    }

    return true;
}

template<class T,class S>
void RankTree<T,S>::rotateLeft(Node<T,S>* subtree_root)
{
    if(subtree_root == nullptr) return;
    auto subtree_parent = subtree_root->getParent();
    auto subtree_right = subtree_root->getRightSon();

    //update extras:
    double old_extra_1 = subtree_root->getExtra();
    double old_extra_2 = subtree_right->getExtra();
    subtree_root->setExtra(-old_extra_2);
    subtree_right->setExtra(old_extra_1 + old_extra_2);
    auto subtree_right_left = subtree_right->getLeftSon();
    if(subtree_right_left)
    {
        double old_extra_3 = subtree_right_left->getExtra();
        subtree_right_left->setExtra(old_extra_3 + old_extra_2);
    }
    //finished updating extras

    if(subtree_right != nullptr)
    {
        subtree_right->setParent(subtree_parent);
        subtree_root->setRightSon(subtree_right->getLeftSon());
        if(subtree_right->getLeftSon() != nullptr)
        {
            subtree_right->getLeftSon()->setParent(subtree_root);
        }
    }
    if(subtree_parent != nullptr)
    {
        //find out if subtree_root is a left son or a right son:
        if(subtree_parent->getRightSon() == subtree_root)
        {
            subtree_parent->setRightSon(subtree_right);
        }
        else if(subtree_parent->getLeftSon() == subtree_root)
        {
            subtree_parent->setLeftSon(subtree_right);
        }
    }
    subtree_root->setParent(subtree_right);
    if(subtree_right != nullptr)
    {
        subtree_right->setLeftSon(subtree_root);
    }
    updateAncestorHeightsAndBF(subtree_root);
}

template<class T,class S>
void RankTree<T,S>::rotateRight(Node<T,S>* subtree_root)
{
    if(subtree_root == nullptr) return;
    auto subtree_parent = subtree_root->getParent();
    auto subtree_left = subtree_root->getLeftSon(); //for sure not null?
    //update extras:
    double old_extra_1 = subtree_root->getExtra();
    double old_extra_2 = subtree_left->getExtra();
    subtree_root->setExtra(-old_extra_2);
    subtree_left->setExtra(old_extra_1+old_extra_2);
    auto subtree_left_right = subtree_left->getRightSon();
    if(subtree_left_right)
    {
        double old_extra_3 = subtree_left_right->getExtra();
        subtree_left_right->setExtra(old_extra_3 + old_extra_2);
    }

    if(subtree_left != nullptr) //always happens?
    {
        subtree_left->setParent(subtree_parent);
        subtree_root->setLeftSon(subtree_left->getRightSon());
        if(subtree_left->getRightSon() != nullptr)
        {
            subtree_left->getRightSon()->setParent(subtree_root);
        }
    }
    if(subtree_parent != nullptr)
    {
        //find out if subtree_root is a left son or a right son:
        if(subtree_parent->getRightSon() == subtree_root)
        {
            subtree_parent->setRightSon(subtree_left);
        }
        else if(subtree_parent->getLeftSon() == subtree_root)
        {
            subtree_parent->setLeftSon(subtree_left);
        }
    }
    subtree_root->setParent(subtree_left);
    if(subtree_left != nullptr)
    {
        subtree_left->setRightSon(subtree_root);
    }
    updateAncestorHeightsAndBF(subtree_root);
}

template<class T,class S>
void RankTree<T,S>::rotateLL(Node<T,S>* subtree_root)
{
    if(!subtree_root) return;
    rotateRight(subtree_root);
}

template<class T,class S>
void RankTree<T,S>::rotateRR(Node<T,S>* subtree_root)
{
    if(!subtree_root) return;
    rotateLeft(subtree_root);
}

template<class T,class S>
void RankTree<T,S>::rotateLR(Node<T,S>* subtree_root)
{
    if(!subtree_root) return;
    rotateLeft(subtree_root->getLeftSon());
    rotateRight(subtree_root);
}

template<class T,class S>
void RankTree<T,S>::rotateRL(Node<T,S>* subtree_root)
{
    if(!subtree_root) return;
    rotateRight(subtree_root->getRightSon());
    rotateLeft(subtree_root);
}

template<class T,class S>
void RankTree<T,S>::balance(Node<T,S>* subtree_root)
{
    if(!subtree_root) return;
    if(subtree_root->getBF() == POS_FACTOR)
    {
        if(subtree_root->getLeftSon()->getBF() >= 0)
        {
            rotateLL(subtree_root);
        }
        else
        {
            rotateLR(subtree_root);
        }
    }
    else if(subtree_root->getBF() == NEG_FACTOR)
    {
        if (subtree_root->getRightSon()->getBF() <=0)
        {
            {
                rotateRR(subtree_root);
            }
        }
        else
        {
            rotateRL(subtree_root);
        }
    }
    else return;
    if(root == subtree_root) //if root is part of rotation:
    {
        root = root->getParent();
    }
}

template<class T,class S>
template <class DoSomething, class Param1, class Param2>
void RankTree<T,S>::inOrderAux(Node<T,S>* subtree_root, DoSomething doSomething, Param1 param1, Param2 param2)
{
    if(subtree_root == nullptr)
    {
        return;
    }
    Node<T,S>* left_son = subtree_root->getLeftSon();
    Node<T,S>* right_son = subtree_root->getRightSon();
    inOrderAux(left_son, doSomething, param1, param2);
    doSomething(subtree_root, param1, param2);
    inOrderAux(right_son, doSomething, param1, param2);
}

template<class T,class S>
template <class DoSomething, class Param1, class Param2>
void RankTree<T,S>::preOrderAux(Node<T,S>* subtree_root, DoSomething doSomething, Param1 param1, Param2 param2)
{
    if(subtree_root == nullptr)
    {
        return;
    }
    Node<T,S>* left_son = subtree_root->getLeftSon();
    Node<T,S>* right_son = subtree_root->getRightSon();
    doSomething(subtree_root, param1, param2);
    preOrderAux(left_son, doSomething, param1, param2);
    preOrderAux(right_son, doSomething, param1, param2);
}

template<class T,class S>
template <class DoSomething, class Param1, class Param2>
void RankTree<T,S>::postOrderAux(Node<T,S>* subtree_root, DoSomething doSomething, Param1 param1, Param2 param2)
{
    if(subtree_root == nullptr)
    {
        return;
    }
    Node<T,S>* left_son = subtree_root->getLeftSon();
    Node<T,S>* right_son = subtree_root->getRightSon();
    postOrderAux(left_son, doSomething, param1, param2);
    postOrderAux(right_son, doSomething, param1, param2);
    doSomething(subtree_root, param1, param2);
}

template<class T,class S>
template <class DoSomething, class Param1, class Param2>
void RankTree<T,S>::inOrder(DoSomething doSomething, Param1 param1, Param2 param2)
{
    inOrderAux(root, doSomething, param1, param2);
}

template<class T,class S>
template <class DoSomething, class Param1, class Param2>
void RankTree<T,S>::preOrder(DoSomething doSomething, Param1 param1, Param2 param2)
{
    preOrderAux(root, doSomething, param1, param2);
}

template<class T,class S>
template <class DoSomething, class Param1, class Param2>
void RankTree<T,S>::postOrder(DoSomething doSomething, Param1 param1, Param2 param2)
{
    postOrderAux(root, doSomething, param1, param2);
}


template<class T,class S>
void RankTree<T,S>::updateAncestorHeightsAndBF(Node<T,S>* subtree_root)
{
    auto curr = subtree_root;
    while(curr != nullptr)
    {
        int left_son_height = (curr->getLeftSon() == nullptr) ? -1 : curr->getLeftSon()->getHeight();
        int right_son_height = (curr->getRightSon() == nullptr) ? -1 : curr->getRightSon()->getHeight();
        int ptr_height = (left_son_height > right_son_height) ? left_son_height + 1 : right_son_height + 1;
        curr->setHeight(ptr_height);
        curr->setBF(curr->calcBalanceFactor());
        curr = curr->getParent();
    }
}

template<class T,class S>
Node<T,S>* RankTree<T,S>::goToFirstUnbalanced(Node<T,S>* ptr)
{
    while(ptr)
    {
        if(abs(ptr->getBF()) == POS_FACTOR)
        {
            return ptr;
        }
        ptr = ptr->getParent();
    }
    return ptr;
}

template<class T,class S>
bool RankTree<T,S>::isRightSon(Node<T,S>* node)
{
    auto parent = node->getParent();
    if(!parent) return false; //just in case
    if(parent->getRightSon() == node)
    {
        return true;
    }
    return false;
}

//assumes key exists!!
template<class T,class S>
void RankTree<T,S>::addExtraUntil(T key,double amount)
{
    auto curr = root;
    if(!root) return;
    bool series_right_turns = false;
    //Node<T,S>* first_node_to_turn_right = curr;
    while(curr != nullptr)
    {
        if(curr->getKey() == key)
        {
            if(!series_right_turns)
            {
                curr->setExtra(curr->getExtra() + amount);
            }
            auto right_son = curr->getRightSon();
            if(right_son)
            {
                right_son->setExtra(right_son->getExtra() - amount);
            }
            break;
        }
        else if(curr->getKey() > key)
        {
            if(series_right_turns)
            {
                //first_node_to_turn_right->setExtra(first_node_to_turn_right->getExtra() + amount);
                series_right_turns = false;
                curr->setExtra(curr->getExtra() - amount);
            }
            curr = curr->getLeftSon();
        }
        else
        {
            if(!series_right_turns)
            {
                curr->setExtra(curr->getExtra() + amount);
                //first_node_to_turn_right = curr;
            }
            curr = curr->getRightSon();
            series_right_turns = true;
        }
    }
}

//helper function
template<class T, class S>
Node<T,S>* findSmallestBiggerThanX(RankTree<T,S>* tree, int x)
{
    Node<T,S>* curr = tree->getRoot();
    Node<T,S>* res = nullptr;
    while(curr != nullptr)
    {
        if(curr->getKey() > x)
        {
            res = curr;
            curr = curr->getLeftSon();
        }
        else
        {
            curr = curr->getRightSon();
        }
    }
    return res;
}

template<class T, class S>
Node<T,S>* findSmallestBiggerThanOrEqualToX(RankTree<T,S>* tree, int x)
{
    Node<T,S>* node = tree->findNode(x);
    if(node) return node;
    return findSmallestBiggerThanX(tree, x);
}

//helper function
template<class T, class S>
Node<T,S>* findBiggestSmallerThanX(RankTree<T,S>* tree, int x)
{
    Node<T,S>* curr = tree->getRoot();
    Node<T,S>* res = nullptr;
    while(curr != nullptr)
    {
        if(curr->getKey() == x)
        {
            break;
        }
        if(curr->getKey() > x)
        {
            curr = curr->getLeftSon();
        }
        else
        {
            res = curr;
            curr = curr->getRightSon();
        }
    }
    return res;
}

//helper function
template<class T, class S>
Node<T,S>* findBiggestSmallerThanOrEqualToX(RankTree<T,S>* tree, int x)
{
    Node<T,S>* node = tree->findNode(x);
    if(node) return node;
    return findBiggestSmallerThanX(tree, x);
}

template<class T,class S>
void RankTree<T,S>::addExtra(T min, T max , double amount)
{
     //key minimal is the smallest key that's bigger than min
    Node<T,S>* small_node = findSmallestBiggerThanOrEqualToX(this, min);
    Node<T,S>* big_node = findBiggestSmallerThanOrEqualToX(this, max);
    if(!small_node || !big_node) return;
    Node<T,S>* previous_small_node = getPreviousInorder(small_node);
    addExtraUntil(big_node->getKey(), amount);
    if(previous_small_node)
    {
        addExtraUntil(previous_small_node->getKey(), -amount);
    }

}

//assumes key exists!!
template<class T,class S>
double RankTree<T,S>::calcExtraVal(int key)
{
    double sum_extras = 0;
    Node<T,S>* curr = root;
    while(curr != nullptr)
    {
        sum_extras += curr->getExtra();
        if(curr->getKey() == key)
        {
            break;
        }
        else if(curr->getKey() > key)
        {
            curr = curr->getLeftSon();
        }
        else
        {
            curr = curr->getRightSon();
        }
    }
    return sum_extras;
}

//*********************************** dim helping func***********************************//

template<class T,class S>
Node<T,S>* RankTree<T,S>::getNextInorder(Node<T,S>* node)
{
    Node<T,S>* curr = node->getRightSon();
    if(!curr)
    {
        return node->getParent();
    }
    while(curr->getLeftSon() != nullptr)
    {
        curr = curr->getLeftSon();
    }
    return curr;
}

template<class T,class S>
Node<T,S>* RankTree<T,S>::getPreviousInorder(Node<T,S>* node)
{
    if(!node) return nullptr;
    Node<T,S>* curr = node->getLeftSon();
    if(!curr) //no left son
    {
        if(isRightSon(node)) //parent is smaller than node
        {
            return node->getParent();
        }
        else if(node == root)
        {
            return nullptr;
        }
        //no left son and parent is bigger, and node is a left son
        else
        {
            return findBiggestSmallerThanX(this, node->getKey());
        }
    }
    while(curr->getRightSon() != nullptr)
    {
        curr = curr->getRightSon();
    }
    return curr;
}


template<class T,class S>
bool RankTree<T,S>::hasOneSon(Node<T,S>* node)
{
    //should check if node is null!
    bool hasLeftSon = ((node->getRightSon() == nullptr) && (node->getLeftSon()!= nullptr));
    bool hasRightSon = ((node->getRightSon() != nullptr) && (node->getLeftSon()== nullptr));
    return (hasLeftSon || hasRightSon);
}


template<class T,class S>
Node<T,S>* RankTree<T,S>::getRoot() const
{
    return root;
}

template<class T,class S>
int RankTree<T,S>::getTreeSizeAux(Node<T,S>* node)
{
    if(!node) return 0;
    int left_num = getTreeSizeAux(node->getLeftSon());
    int right_num = getTreeSizeAux(node->getRightSon());
    return left_num + right_num + 1;
}


template<class T,class S>
int RankTree<T,S>::getTreeSize()
{
    return getTreeSizeAux(root);
}



#endif //HW2WETDS_RANKTREE_H
