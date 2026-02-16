
#include "BitcoinExchange.hpp"
#include <exception>
#include <iostream>
#include <utility>

/*
static void testDateValidity(const std::string &date, bool expect) {
    bool res = BitcoinExchange::isValidDate(date);
    std::cout << "Testing " << date << ": " << (res ? "true" : "false")
              << (res == expect ? "  \033[32m[Pass]\033[0m"
                                : "  \033[31m[FAIL!]\033[0m")
              << std::endl;
}

static void dateTests(void) {
    std::cout << " ==== Testing monthly limits ==== " << std::endl;
    testDateValidity("2016-1-31", true);
    testDateValidity("2016-1-32", false);
    testDateValidity("2016-2-29", true);  // leap year
    testDateValidity("2016-2-30", false); // leap year
    testDateValidity("2015-2-28", true);
    testDateValidity("2015-2-29", false);
    testDateValidity("2016-3-31", true);
    testDateValidity("2016-3-32", false);
    testDateValidity("2015-4-30", true);
    testDateValidity("2015-4-31", false);
    testDateValidity("2016-5-31", true);
    testDateValidity("2016-5-32", false);
    testDateValidity("2015-6-30", true);
    testDateValidity("2015-6-31", false);
    testDateValidity("2016-7-31", true);
    testDateValidity("2016-7-32", false);
    testDateValidity("2016-8-31", true);
    testDateValidity("2016-8-32", false);
    testDateValidity("2015-9-30", true);
    testDateValidity("2015-9-31", false);
    testDateValidity("2016-10-31", true);
    testDateValidity("2016-10-32", false);
    testDateValidity("2015-11-30", true);
    testDateValidity("2015-11-31", false);
    testDateValidity("2016-12-31", true);
    testDateValidity("2016-12-32", false);

    std::cout << " ==== Testing parsing non numbers ==== " << std::endl;
    // missing/exceeding numbers
    testDateValidity("2010-2-12-32", false);
    testDateValidity("2010-2", false);
    testDateValidity("2010", false);
    // characters
    testDateValidity("123f-2-3", false);
    testDateValidity("1230-2f-3", false);
    testDateValidity("1230-2-3f", false);
    testDateValidity("1230_2-3", false);
    // empty year/month/day
    testDateValidity("-12-2", false);
    testDateValidity("2004--2", false);
    testDateValidity("2004-12-", false);
    testDateValidity("2004-12--", false);
    testDateValidity("2004-12---", false);
    testDateValidity("", false);
}

static void testPair(const std::string &str, const char seperator) {
    std::pair<std::string, std::string> pair;
    try {
        pair = BitcoinExchange::getLinePair(str, seperator);
    } catch (std::exception &ex) {
        std::cout << "Failed getting a line pair because: " << ex.what()
                  << std::endl;
        return;
    }
    std::cout << "[" << pair.first << ", " << pair.second << "]" << std::endl;
}

static void linePairTests(void) {
    std::cout << " ==== Testing parsing lines to get pairs ==== " << std::endl;

    testPair("  2024689 , 123", ',');
    testPair("  1230-21-23 , 1.2399017", ',');
    testPair("  1230-21-23 , 1.2399017", '|');
    testPair("  1230-21-23 | 1.2399017", '|');
    testPair("  1230-21-23 | |1.2399017", '|');
    testPair("1230-21-23|1.2399017|", '|');
    testPair("1230-21-23|1.2399017", '|');
    testPair("1.2399017", '|');
}
*/

int main(void) {

    /*
    dateTests();
    std::cout << std::endl;
    linePairTests();
    */

    BitcoinExchange btc = BitcoinExchange("data.csv");
    if (!btc.hasValidData()) {
        return 1;
    }

    btc.printData();
    return 0;
}
