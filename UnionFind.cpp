//
// Created by layan on 6/9/2023.
//

#include "UnionFind.h"

UnionFind::UnionFind(int* record_stocks, int arr_size)
{
    array_size = arr_size;
    records_array = new Record * [arr_size];
    piles_array = new Pile * [arr_size];

    for(int i = 0; i < arr_size; i++)
    {
        //fill records array:
        Record* new_record = new Record(i, record_stocks[i]);
        records_array[i] = new_record;

        //fill piles array:
        Pile* new_pile = new Pile(new_record);
        piles_array[i] = new_pile;

        records_array[i]->setPile(new_pile);
    }
}

UnionFind::~UnionFind()
{
    for(int i = 0; i < array_size; i++)
    {
        delete records_array[i];
        if(piles_array[i]) delete piles_array[i]; //should assign to null after every pile deletion
    }

    delete[] records_array;
    delete[] piles_array;
}

void UnionFind::Union(int r_id1, int r_id2)
{
    Pile* pile1 = find(r_id1);
    Pile* pile2 = find(r_id2);
    Record* root1 = pile1->getRoot();
    Record* root2 = pile2->getRoot();

    if(pile2->getSize() >= pile1->getSize()) // pile1 should point to pile2
    {
        root1->setRank(root1->getRank() + pile2->getNumRecords() - root2->getRank());

        root1->setParent(root2);
        pile2->incSize(pile1->getSize());
        pile2->incNumRecords(pile1->getNumRecords());
        int pile1_index = pile1->getIndexInArray();
        delete pile1;
        piles_array[pile1_index] = nullptr;
    }
    else //pile2 should point to pile1
    {
        root1->setRank(root1->getRank() + pile2->getNumRecords());
        root2->setRank(root2->getRank() - root1->getRank());

        root2->setParent(root1);
        pile1->incSize(pile2->getSize());
        pile1->incNumRecords(pile2->getNumRecords());
        pile1->setColumn(pile2->getColumn());
        int pile2_index = pile2->getIndexInArray();
        delete pile2;
        piles_array[pile2_index] = nullptr;
    }
}

Pile* UnionFind::find(int r_id)
{
    if(r_id >= array_size || r_id < 0) return nullptr;
    int sum_ranks = 0;
    Record* wanted_record = records_array[r_id]; //shouldn't be null
    Record* curr = wanted_record;
    while(curr->getParent() != nullptr) //sum all ranks
    {
        sum_ranks += curr->getRank();
        curr = curr->getParent();
    }
    Record* root = curr;
    int partial_sum = 0, to_subtract = 0;
    curr = wanted_record;
    while(curr->getParent() != nullptr) //update ranks & kivuts mslulim
    {
        //update rank before kivuts mslulim
        to_subtract = partial_sum;
        partial_sum += curr->getRank();
        curr->setRank(sum_ranks - to_subtract);
        Record* tmp = curr;
        curr = curr->getParent();

        //kivuts mslulim:
        tmp->setParent(root);
    }
    return root->getPile(); //shouldn't be null!
}

void UnionFind::getPlace(int r_id, int* column, int* height)
{
    if(!height || !column) return;
    //*height = 0, *column = 0;
    Pile* pile = find(r_id);
    if(!pile)
    {
        column = nullptr, height = nullptr;
        return;
    }
    Record* record = records_array[r_id];
    Record* curr = record;
    int sum_ranks = 0; //root included
    while (curr != nullptr)
    {
        sum_ranks += curr->getRank();
        curr = curr->getParent();
    }
    //*height = root->getNumCopies() + sum_ranks;
    *height = sum_ranks;
    *column = pile->getColumn();
}