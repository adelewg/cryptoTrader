#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "Logs.h"


class BotTrader
{
    public:
    /** The constructor, takes no parameters - maybe it should have parameters ??*/
    BotTrader();
    
    std::string currentTime;
    std::string lastTime;
    //OrderBook OrderBook(csv file). Call the constructor for the orderbook which opens the csv file
    std::vector<OrderBookEntry> botSales;

    //can include an initialisation function which is called when the user selects option 7 and the rest of the functions can then be private

    /**This is the main function to start of the bot trading and it takes no inputs, instead it moves through the timesteps until the end submitting orders depending on if the currency pair is cheap of expensive */
    void botTrade();

    

    

    private:

    /** Depending on what the current time is. The function runs through all the products and making decisions on what to trade. It does not return anything but takes as input the reference to the log file*/
    void enterOrderForMatching(std::ofstream &file);
    
    /**This function moves to the next time frame - first matching orders and them setting the new current time */
    void gotoNextTimeframe(std::ofstream &file);

    /** This function is void as it has no output instead it inserts an order into the botorderbook and it takes in two parameters: 1. an OrderBookEntry 2. The reference to the logfile to log the details of the order */
    void enterOrder(OrderBookEntry &obe, std::ofstream &file);

    


   
    OrderBook botOrderBook{"20200317.csv"};
    Wallet wallet; 

    //instantiating an instance of the logs class to open a file and start writing out details of the trades that the bot makes
    Logs botlog;


};