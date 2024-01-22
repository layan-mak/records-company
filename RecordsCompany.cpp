//
// Created by layan on 6/10/2023.
//

#include "recordsCompany.h"

/***********************************Non-Member Helper Functions: ************************************/

void copyArrays(int* source, int* dest, int size)
{
    if(!source || !dest) return;
    for(int i = 0; i < size; i++)
    {
        dest[i] = source[i];
    }
}

//sets all array values to val
void fillArray(int* array, int size, int val)
{
    for(int i = 0; i < size; i++)
    {
        array[i] = val;
    }
}

/**
 * gets a Customer* node as parameter and sets its debt to 0
 * */
 void resetCustomerDebt(Node<int, Customer*>* customer_node, int trash1, int trash2)
{
     if(!customer_node || !customer_node->getValue()) return;
     customer_node->getValue()->setDebt(0);
     customer_node->setExtra(0);
}

/************************************* Member helper functions: *************************************/

bool RecordsCompany::destroyAndCreateRecords(int* new_records_stocks_arr, int new_records_num)
{
    records_num = new_records_num;

    //destroy and create new record_stocks_array:
    if(record_stocks_array)
    {
        delete[] record_stocks_array;
    }
    record_stocks_array = new int[new_records_num];
    if(!record_stocks_array) return false;
    copyArrays(new_records_stocks_arr, record_stocks_array, new_records_num);

    //create new record_purchases array:
    if(record_purchases_array)
    {
        delete[] record_purchases_array;
    }
    record_purchases_array = new int[new_records_num];
    if(!record_purchases_array)
    {
        return false;
    }
    fillArray(record_purchases_array, new_records_num, 0); //initialize all record purchases to 0

    //destroy and create new union find:
    if(records_union_find)
    {
        delete records_union_find;
    }
    records_union_find = new UnionFind(new_records_stocks_arr, new_records_num);
    if(!records_union_find)
    {
        return false;
    }

    return true;
}

/*****************************************************************************************************/

RecordsCompany::~RecordsCompany()
{
    delete customers_hash_table;
    delete members_tree;
    if(records_union_find) delete records_union_find;
    if(record_purchases_array) delete[] record_purchases_array;
    if(record_stocks_array) delete[] record_stocks_array;
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    bool res = destroyAndCreateRecords(records_stocks, number_of_records);
    if(!res)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    members_tree->inOrder(resetCustomerDebt, 0, 0);

    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id < 0 || phone < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Customer* customer = customers_hash_table->find(c_id);
    if(customer)
    {
        return StatusType::ALREADY_EXISTS;
    }

    bool successful_insertion = customers_hash_table->insert(c_id, phone);
    if(!successful_insertion)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer* customer = customers_hash_table->find(c_id);
    if(!customer)
    {
        return StatusType::DOESNT_EXISTS;
    }
    return Output_t<int>(customer->getPhoneNumber());
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer* customer = customers_hash_table->find(c_id);
    if(!customer)
    {
        return StatusType::DOESNT_EXISTS;
    }
    if(customer->isMember())
    {
        return StatusType::ALREADY_EXISTS;
    }
    //add to rank tree
//    if(c_id == 24)
//    {
//        int x = 0;
//    }
    bool successful_insertion = members_tree->insertNode(c_id, customer);
    if(!successful_insertion)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    //set member field in customer to true
    customer->makeMember();
//    if(c_id == 213)
//    {
//        int x = 0;
//    }

    return StatusType::SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(c_id < 0)
    {
        return Output_t<bool>(StatusType::INVALID_INPUT);
    }
    Customer* customer = customers_hash_table->find(c_id);
    if(customer == nullptr)
    {
        return Output_t<bool>(StatusType::DOESNT_EXISTS);
    }
    if(customer->isMember())
    {
        return Output_t<bool>(true);
    }
    return Output_t<bool>(false);
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id < 0 || r_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer* customer = customers_hash_table->find(c_id);
    if(customer == nullptr ||r_id >= records_num)
    {
        return StatusType::DOESNT_EXISTS;
    }
    if(customer->isMember())
    {
        double oldDebt = customer->getDebt();
        double price = 100 + record_purchases_array[r_id];
        customer->setDebt(price+oldDebt);
    }
    record_purchases_array[r_id]++;
    return StatusType::SUCCESS;
}

/*void test()
{
    int x = 0;
    //nothing at all
}*/

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    /*if(c_id1 == 160 && c_id2 == 161)
    {
        int x = 0;
        //nothing
    }*/
    if(c_id1 < 0  || c_id2 < c_id1 || amount <= 0 )
    {
        return StatusType::INVALID_INPUT;
    }
    //if(c_id1 == c_id2 - 1) return StatusType::SUCCESS; //not sure?
    members_tree->addExtra(c_id1,c_id2 - 1,amount);
    return StatusType ::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id < 0)
    {
        return Output_t<double>(StatusType::INVALID_INPUT);
    }
    /*if(c_id == 160)
    {
        int x = 0;
    }*/
    Node<int,Customer*>* customer_node = members_tree->findNode(c_id);
    if(customer_node == nullptr){
        return Output_t<double>(StatusType::DOESNT_EXISTS);
    }
    //if(c_id == 231) test();
    Customer* customer = customer_node->getValue();
    double prize = members_tree->calcExtraVal(c_id);
    double expenses = customer->getDebt() - prize;          //changes!!
    return Output_t<double>(expenses);
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    /*if(r_id1 == 22 && r_id2 == 0)
    {
        int x = 0;
    }*/
    if(r_id1 < 0 || r_id2 < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(r_id1 >= records_num || r_id2 >= records_num)
    {
        return StatusType::DOESNT_EXISTS;
    }
    if(records_union_find->find(r_id1) == records_union_find->find(r_id2))
    {
        return StatusType::FAILURE;
    }
    records_union_find->Union(r_id1, r_id2);
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(r_id < 0 || column == nullptr || hight == nullptr)
    {
        return StatusType::INVALID_INPUT;
    }
    if(r_id >= records_num)
    {
        return StatusType::DOESNT_EXISTS;
    }
    records_union_find->getPlace(r_id,column,hight);
    return StatusType::SUCCESS;
}