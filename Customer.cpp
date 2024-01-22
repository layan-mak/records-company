//
// Created by layan on 6/9/2023.
//
#include "Customer.h"

int Customer::getCID() const
{
    return c_id;
}

int Customer::getPhoneNumber() const
{
    return phone_number;
}

bool Customer::isMember() const
{
    return member;
}

double Customer::getDebt() const
{
    return monthly_debt;
}

void Customer::makeMember()
{
    member = true;
}

void Customer::setDebt(double new_debt)
{
    monthly_debt = new_debt;
}