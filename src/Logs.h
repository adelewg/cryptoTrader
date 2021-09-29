#pragma once
#include <fstream>
#include "OrderBookEntry.h"
#include "Wallet.h"



class Logs 
{
    public:
    std::ofstream logFile;
    // This is the constructor function that takes no parameters
    Logs();

    //R4A maintain a record of assets - maybe use the wallet class - in which case maybe this function should be in the "bottrader"

    void logWallet(std::ofstream &file);

    //R4B maintain a record of bids and offers in a suitable file format - in a text file. It will be called everytime the bot submits a bid of offer, so that it can be logged at the same time. The function does not return anything but it will take as input parameters a reference to the file to write to as well as the orderbookentry object.
    void logOBE(std::ofstream &file, OrderBookEntry &obe2);




    // R4C Maintain a record of successful bids and offers along with the context (eg exchange average offer and bid). The function does not return anything but it will take as input parameters a reference to the file to write to as well as the orderbookentry object.
    void logSale(std::ofstream &file, OrderBookEntry &obe2);

    private:

    
};