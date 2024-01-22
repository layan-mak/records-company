//
// Created by layan on 6/9/2023.
//

#ifndef HW2WETDS_UNIONFIND_H
#define HW2WETDS_UNIONFIND_H

#include "Record.h"

class UnionFind
{
    Record** records_array;

    int array_size;             // size of two arrays

    Pile** piles_array;

public:

    /**
     * Allocates two arrays sized arr_size: records_array, piles_array
     * Allocates every record and every pile in each array
     * Sets each pile to be a single record in the beginning
     * */
    explicit UnionFind(int* record_stocks, int arr_size);

    /**
     * Destroys everything: Piles, records and arrays
     * */
    ~UnionFind();

    /** this function unions the piles of r_id1, r_id2 using union by group size
     * also "puts" r_id1's pile on top of r_id2's pile : updates ranks and heights for each record
     * important: there's a difference between the union itself (which pile is bigger which root to point to the other root,
     * this depends on pile sizes), and which pile is put on top of the other (depends solely on the order of parameters)
     * ASSUMES that r_id1, r_id2 are valid. validation check are done in RecordCompany.
     * */
    void Union(int r_id1, int r_id2);

    /** returns the pile of r_id
     * */
    Pile* find(int r_id);

    /**
     * returns r_id's height from ground (not including the number of its copies)
     * and its column (the record id of the lowest record in the pile)
     * */
    void getPlace(int r_id, int* column, int* height);

};

#endif //HW2WETDS_UNIONFIND_H
