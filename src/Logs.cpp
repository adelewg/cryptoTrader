#include "Logs.h"


//this will eventually take some parameters or data members - the obe
Logs::Logs()
{
    std::ofstream file;
}

// void Logs::logOBE(OrderBookEntry& order)
void Logs::logOBE(std::ofstream &file, OrderBookEntry &obe2)
{
    
    if(obe2.orderType == OrderBookType::bid)
    {

        file << "We have submitted the following Bid into the matching engine: " << std::endl;
        file << "Product: " << obe2.product <<  " Amount: " << obe2.amount << "  Price: " << obe2.price << "  Time: " << obe2.timestamp  << "  Username: "<< obe2.username<< std::endl;
        file << " ------------------------------------" << std::endl;
    }

    if(obe2.orderType == OrderBookType::ask)
    {
        file << "We have submitted the following Ask into the matching engine: " << std::endl;
        file  << "Product: " << obe2.product << " Amount: " << obe2.amount << "  Price: " << obe2.price << "  Time: " << obe2.timestamp  << "  Username: "<< obe2.username<< std::endl;
        file << " ------------------------------------" << std::endl;

    }

    if(obe2.orderType == OrderBookType::asksale)
    {
       file << "Ask Sale has gone through: " << std::endl;
       file  << "Product: " << obe2.product << " Amount: " << obe2.amount << "  Price: " << obe2.price << "  Time: " << obe2.timestamp  << "  Username: "<< obe2.username<< std::endl;
       file << " ------------------------------------" << std::endl;
    }

    if(obe2.orderType == OrderBookType::bidsale)
    {
       file << "BidSale has gone through: " << std::endl;
       file  << "Product: " << obe2.product << " Amount: " << obe2.amount << "  Price: " << obe2.price << "  Time: " << obe2.timestamp  << "  Username: "<< obe2.username<< std::endl;
       file << " ------------------------------------" << std::endl;
    }
    
}


void Logs::logSale(std::ofstream &file, OrderBookEntry &obe2)
{
    file << "The following sale has taken place successfully: " << std::endl;
    file  << "Product: " << obe2.product << " Amount: " << obe2.amount << "  Price: " << obe2.price << "  Time: " << obe2.timestamp  << "  Username: "<< obe2.username<<std::endl;
}