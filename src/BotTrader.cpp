#include "BotTrader.h"
#include <iostream>

BotTrader::BotTrader()
{

}

void BotTrader::botTrade()
{
    // We set current time and last time as well which is needed in the while loop condition so that we know when to stop
    currentTime = botOrderBook.getEarliestTime();
    lastTime = botOrderBook.getLatestTime();

    // Insert some currently into the wallet
    wallet.insertCurrency("BTC", 10);
    wallet.insertCurrency("USDT", 1000);
    wallet.insertCurrency("DODGE", 100);
    wallet.insertCurrency("ETH", 100);

    //set up the text file where we shall be saving the logs
    std::ofstream logFile;
    logFile.open("logs.txt");
    logFile << "Entering orders into the system" << std::endl;
    logFile << lastTime << std::endl;

    // While loop to iterate through all the timesteps until the end
    while(currentTime < botOrderBook.getLatestTime())
    {
        enterOrderForMatching(logFile);
        gotoNextTimeframe(logFile);
        std::cout << wallet.toString() << std::endl;
    }

    logFile.close();
}

void BotTrader::enterOrderForMatching(std::ofstream &file)
{
    for (std::string const& p : botOrderBook.getKnownProducts())
    {
        //declare a local variables to store the bid-ask spreads. bid ask spreads are part of the algorithm to decide prices
        double bidAskSpread;
        double targetSpread = -0.01;
        
        //pull up all the entries with the currentTime that are asks of that product type
        std::vector<OrderBookEntry> entriesAsk = botOrderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::vector<OrderBookEntry> entriesBid = botOrderBook.getOrders(OrderBookType::bid, p, currentTime);

        // declare an orderbookentry which is just the first item in the entries vector
        OrderBookEntry obe = entriesAsk[0];

        bidAskSpread = (OrderBook::getHighPrice(entriesBid) - OrderBook::getLowPrice(entriesAsk) )/ OrderBook::getLowPrice(entriesAsk);
        // if the bid ask spread is narrow - the ask price should be equal to the highest bid

        if(bidAskSpread < targetSpread)
        {
            // set the price of the order book to be the highest bid;
            obe.price = OrderBook::getHighPrice(entriesBid);
            obe.orderType = OrderBookType::ask;
        }
        // if the spread is higher than the targe spread than we switch to a bid. Therefore if we are not selling than we are buying
        else
        {
            obe.price = OrderBook::getLowPrice(entriesAsk);
            obe.orderType = OrderBookType::bid;
        }

        obe.username = "botuser";

        if(wallet.canFulfillOrder(obe))
        {
            enterOrder(obe, file);
        }    
    }
}

void BotTrader::enterOrder(OrderBookEntry &obe, std::ofstream &file)
{
    botOrderBook.insertOrder(obe);
    botlog.logOBE(file, obe);
    file << wallet.toString() << std::endl;
}

void BotTrader::gotoNextTimeframe(std::ofstream &file)
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : botOrderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  botOrderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl; 
            std::cout << sale.username << std::endl;
            if (sale.username == "dataset")
            {
                // update the wallet and log the transaction
                wallet.processSale(sale);
                botlog.logOBE(file, sale);
            }
        }
    }
    currentTime = botOrderBook.getNextTime(currentTime);
}



