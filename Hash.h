#ifndef HW2WETDS_HASH_H
#define HW2WETDS_HASH_H

#include <iostream>
#include "Customer.h"
#include "RankTree.h"
#define FIRST_HASH_SIZE 2

class HashTable
{
private:
    int hashTableSize;
    int numOfCustomers;
    RankTree<int,Customer*>** hashTable;

    void copyHash(RankTree<int,Customer*>** newTable,int newSize);

    void destroyHashTrees();

    void updateHashTable(int newSize);

    void setTable(RankTree<int, Customer*>** new_table);

public:
    /**
     * class constructor
     * @param n - the constructor creates new hash table with given size
     */
     HashTable();

     /**
      * class constructor
      * @param n - the size of the hash table
      */
     HashTable(int n);

    /**
     * class copy constructor
     * @param otherHsh
     */
    HashTable(HashTable& otherHsh); //is it needed? is it default?

    /**
     * class assignment operator
     * @param otherHash
     * @return
     */
    HashTable& operator=(const HashTable& otherHash); //is it needed? is it default?

    /**
     * class destructor
     * destructs the hash table
     */
    ~HashTable();

    /**
     * the function inserts new item with given key to the hash table
     * @param c_id - customer id
     * @param phone_number -customer phone number
     * @return returns true if the insertion to the tree was successful, false otherwise
     */
    bool insert(int c_id,int phone_number);

    /**
     * the function removes the item with given key from hash table
     * @param c_id - customer id
     * @return returns true if the removal from the tree was successful, false otherwise
     */
    bool remove(int c_id);

    /**
     * hash function which maps each value to a specific place in the hash table
     * @param val - the value we want to insert
     * @return - returns an index
     */
    int hashFunction(int val);

    /**
     * function searches for element with given key in the hash table
     * @param key
     * @return - function returns the value of the node with given key in the hash table
     */
    Customer* find(int c_id);

    /**
     * doubles the size of the hash table
     * @return
     */
    void increaseHashTable();

    /**
     * cuts the size of the hash table by half
     * @return
     */
    void decreaseHashTable();

    /**
     * resizes the hash table according to the number of elements in the table
     */
    void resizeTable();

    /**
     *
     * @return the ratio of the number of elements in the hash table and the size of the hash table
     */
    double calculateAlphaFactor();

    /**
     *
     * @return the number of cumstomers in the hash table
     */
    int getNumOfCustomers();

    /*
     * updates current number of customers after insertion or removal
     */
    void updateNumOfCustomers(int diff);

    /**
     *
     * @return the size of the hash table
     */
    int getHashSize();

    RankTree<int, Customer*>** getTable();



};



#endif //HW2WETDS_HASH_H
