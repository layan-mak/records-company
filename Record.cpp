//
// Created by layan on 6/9/2023.
//
#include "Record.h"

/************************************* Record Implementation ***************************************/

int Record::getRID() const
{
    return r_id;
}

int Record::getNumCopies() const
{
    return num_copies;
}

Record* Record::getParent() const
{
    return parent;
}

Pile* Record::getPile() const
{
    return pile;
}

int Record::getRank()
{
    return rank;
}

void Record::setParent(Record* new_parent)
{
    parent = new_parent;
}

void Record::setPile(Pile* new_pile)
{
    pile = new_pile;
}

void Record::setRank(int new_rank)
{
    rank = new_rank;
}

/************************************* Pile Implementation ***************************************/

Record* Pile::getRoot() const
{
    return root;
}

int Pile::getSize() const
{
    return size;
}

int Pile::getNumRecords() const
{
    return num_records;
}

int Pile::getIndexInArray() const
{
    return index;
}

int Pile::getColumn() const
{
    return column;
}

void Pile::incSize(int size_to_add)
{
    size += size_to_add;
}

void Pile::incNumRecords(int num_records_to_add)
{
    num_records += num_records_to_add;
}

void Pile::setColumn(int new_column)
{
    column = new_column;
}
