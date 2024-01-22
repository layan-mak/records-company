#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include "UnionFind.h"
#include "Hash.h"

class RecordsCompany {
  private:

    int records_num;
    HashTable* customers_hash_table;
    UnionFind* records_union_find;
    RankTree<int, Customer*>* members_tree;
    int* record_stocks_array;             //given as an input
    int* record_purchases_array;

    /**
     * Only used in newMonth function
     * deletes record_stocks_array, record_purchases_array
     * and union_find
     * and creates new ones according to the function parameters
     * sets all values in purchuses array to 0
     * updates records_num
     * @return - false if allocation error, true otherwise
     * */
    bool destroyAndCreateRecords(int* new_records_stocks_arr, int new_records_num);

  public:

    /**
     * allocates empty hashTable and rankTree.
     * sets the UnionFind and two int arrays to null, will allocate them given record_stocks
     * array as an input
     * */
    RecordsCompany() : records_num(0), customers_hash_table(new HashTable), records_union_find(nullptr),
                        members_tree(new RankTree<int, Customer*>), record_stocks_array(nullptr),
                        record_purchases_array(nullptr) {};

    /**
     * this destructor deletes the HT, RankTree, UF
     * customer* objects are deleted in HT destructor
     * record* objects are deleted in UF destructor
     * */
    ~RecordsCompany();

    StatusType newMonth(int *records_stocks, int number_of_records);

    StatusType addCostumer(int c_id, int phone);

    Output_t<int> getPhone(int c_id);

    StatusType makeMember(int c_id);

    Output_t<bool> isMember(int c_id);

    StatusType buyRecord(int c_id, int r_id);

    StatusType addPrize(int c_id1, int c_id2, double  amount);

    Output_t<double> getExpenses(int c_id);

    StatusType putOnTop(int r_id1, int r_id2);

    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif