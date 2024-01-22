//
// Created by layan on 6/9/2023.
//

#ifndef HW2WETDS_RECORD_H
#define HW2WETDS_RECORD_H

class Pile;

class Record
{
    int r_id;
    int num_copies;
    Record* parent;
    Pile* pile;      // pile is always nullptr unless this record is the root of a pile
    int rank;        // value to calculate record's height

public:
    explicit Record(int r_id, int num_copies) : r_id(r_id), num_copies(num_copies), parent(nullptr), pile(nullptr), rank(0){};

    ~Record() = default;

    int getRID() const;

    int getNumCopies() const;

    Record* getParent() const;

    Pile* getPile() const;

    int getRank();

    void setParent(Record* new_parent);

    void setPile(Pile* new_pile);

    void setRank(int new_rank);

};

class Pile
{
    Record* root;
    int size;        //number of different records in pile
    int num_records; //number of all records in pile including copies (this is the pile height)
    int index;       //in piles array
    int column;

public:
    Pile(Record* root) : root(root), size(1), num_records(root->getNumCopies()),
                            index(root->getRID()), column(root->getRID()) {};

    Record* getRoot() const;

    int getSize() const;

    int getNumRecords() const;

    int getIndexInArray() const;

    int getColumn() const;

    void incSize(int size_to_add);

    void incNumRecords(int num_records_to_add);

    void setColumn(int new_column);
};

#endif //HW2WETDS_RECORD_H
