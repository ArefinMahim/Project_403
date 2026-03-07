#pragma once
#include<iostream>

class Payment{
    public:
        virtual void process(double amount)=0;
        virtual ~Payment(){}
};

class cashPayment: public Payment{
    public:
        void process(double amount) override;
};

class ebankingPayment: public Payment{
    public:
        void process(double amount) override;
};