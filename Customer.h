//
// Created by layan on 6/9/2023.
//

#ifndef HW2WETDS_CUSTOMER_H
#define HW2WETDS_CUSTOMER_H

class Customer
{
    int c_id;
    int phone_number;
    bool member;
    double monthly_debt;

public:
    Customer(int c_id, int phone_number) : c_id(c_id), phone_number(phone_number), member(false), monthly_debt(0) {};

    ~Customer() = default;

    int getCID() const;

    int getPhoneNumber() const;

    bool isMember() const;

    double getDebt() const;

    void makeMember();

    void setDebt(double new_debt);
};

#endif //HW2WETDS_CUSTOMER_H
