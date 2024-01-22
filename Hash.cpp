#include "Hash.h"

HashTable::HashTable(): hashTableSize(FIRST_HASH_SIZE), numOfCustomers(0)
{
    hashTable = new RankTree<int, Customer*>*[FIRST_HASH_SIZE];
    for(int i=0 ; i < FIRST_HASH_SIZE; i++)
    {
        hashTable[i] = new RankTree<int,Customer*>;
    }
}

HashTable::HashTable(int n) : hashTableSize(n), numOfCustomers(0)
{
    hashTable= new RankTree<int, Customer *> * [n];
    for(int i=0 ; i < n; i++)
    {
        hashTable[i] = new RankTree<int,Customer*>;
    }
}


int HashTable::getNumOfCustomers()
{
    return this->numOfCustomers;
}

void HashTable::updateNumOfCustomers(int diff)
{
    int oldNum = this->getNumOfCustomers();
    this->numOfCustomers = oldNum + diff;
}

int HashTable::getHashSize()
{
    return this->hashTableSize;
}

bool HashTable::insert(int c_id,int phone_number)
{
    int index = this->hashFunction(c_id);
    Customer* customer = new Customer(c_id,phone_number);
    if(!customer) return false;
    if(hashTable[index]->insertNode(c_id,customer))
    {
        this->updateNumOfCustomers(1);
        this->resizeTable();
        return true;
    }
//    std::cout << "insertion failed" << std::endl;
    return false;

}

bool HashTable::remove(int c_id)
{
    //old code:
    /*int index = this->hashFunction(c_id);
    if(hashTable[index]->removeNode(c_id))
    {
        this->updateNumOfCustomers(-1);
        this->resizeTable();
        return true;
    }
    return false;*/

    //new code that deletes the Customer* :
    int index = this->hashFunction(c_id);
    RankTree<int, Customer*>* tree = hashTable[index];
    Node<int, Customer*>* node = tree->findNode(c_id);
    if(!node)
    {
        return false;
    }
    Customer* customer = node->getValue();
    if(hashTable[index]->removeNode(c_id))
    {
        this->updateNumOfCustomers(-1);
        this->resizeTable();
        delete customer;
        return true;
    }
    return false;

}

Customer* HashTable::find(int c_id)
{
    int index = this->hashFunction(c_id);
    Node<int,Customer*>* c_node =  hashTable[index]->findNode(c_id);
    if(c_node)
    {
        return c_node->getValue();
    }
    return nullptr;
}

double HashTable::calculateAlphaFactor()
{
    return double(this->getNumOfCustomers())/double(this->getHashSize());
}




void insertToNewTable(Node<int,Customer*>* node ,RankTree<int,Customer*>** newTable,int newSize)
{
    int newIdx = (node->getKey() % newSize);
    newTable[newIdx]->insertNode(node->getKey(),node->getValue());
}



void HashTable::copyHash(RankTree<int,Customer*>** newTable,int newSize)
{
    for(int i=0;i<this->hashTableSize;i++)
    {
        hashTable[i]->inOrder(insertToNewTable,newTable,newSize);
    }
}

void HashTable::destroyHashTrees()
{
    for(int i = 0; i < hashTableSize; i++)
    {
        delete hashTable[i]; //calls tree destructor!
        //hashTable[i] = nullptr;
    }
}



void HashTable::updateHashTable(int newSize)
{
    HashTable* newHash = new HashTable(newSize);

    this->copyHash(newHash->getTable(),newSize);

    this->destroyHashTrees();

    delete[] hashTable;

    hashTable = newHash->getTable();

    //set table to null
    newHash->setTable(nullptr);

    /**
     * we copied the table we want to our hashTable,
     * and we set newHash's table to null,
     * now we can call its destructor and it won't double delete because we set the table to null.
     * this way we delete the HashTable object - newHash- we created, and get no memory leaks.
     * */
    delete newHash;

    hashTableSize = newSize;
}

void HashTable::increaseHashTable()
{
    int oldSize = this->getHashSize();
    this->updateHashTable(2*oldSize);
}


void HashTable::decreaseHashTable()
{
    int oldSize = this->getHashSize();
    this->updateHashTable(oldSize/2);
}

void HashTable::resizeTable()
{
    double alpha = this->calculateAlphaFactor();
    if(alpha >= 1)
    {
        this->increaseHashTable();
    }
    else if(alpha <= 0.25)
    {
        this->decreaseHashTable();
    }
    else
        return;
}

void deleteCustomer(Node<int, Customer*>* node, int trash1, int trash2)
{
    delete node->getValue();
}

HashTable::~HashTable()
{
    if(hashTable == nullptr) return;
    //delete customers in each tree and the tree itself:
    for(int i = 0; i < hashTableSize; i++)
    {
        RankTree<int, Customer*>* tree = hashTable[i];
        tree->inOrder(deleteCustomer, 0, 0);
        delete tree;
    }
    delete[] hashTable;
}

int HashTable::hashFunction(int val)
{
    int size = this->getHashSize();
    return (val % size);
}

RankTree<int, Customer*>** HashTable::getTable()
{
    return hashTable;
}

void HashTable::setTable(RankTree<int, Customer*>** new_table)
{
    hashTable = new_table;
}