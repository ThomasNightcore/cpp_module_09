
#include "BitcoinExchange.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
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
    std::pair<std::string, double> pair;
    try {
        pair = BitcoinExchange::getLinePair(str, seperator);
    } catch (std::exception &ex) {
        std::cout << "Failed getting a line pair for \'" << str
                  << "\' because: " << ex.what() << std::endl;
        return;
    }
    std::cout << "[" << pair.first << ", " << pair.second << "]" << std::endl;
}

static void linePairTests(void) {
    std::cout << " ==== Testing parsing lines to get pairs ==== " << std::endl;

    testPair(" 2050-01-02, 123", ',');
    testPair("  1230-12-23 , 1.2399017", ',');
    testPair("  1230-12-23 , 1.2399017", '|');
    testPair("  1230-12-23 | 1.2399017", '|');
    testPair("  1230-12-23 | |1.2399017", '|');
    testPair("1230-12-23|1.2399017|", '|');
    testPair("1230-12-23|1.2399017", '|');
    testPair("1.2399017", '|');
}
*/

int main(int argc, char **argv) {

    /*
    dateTests();
    std::cout << std::endl;
    linePairTests();
    */

    if (argc != 2) {
        std::cout << "Usage: ./btc \'input.txt\'" << std::endl;
        return 1;
    }

    BitcoinExchange btc = BitcoinExchange("data.csv");
    if (!btc.hasValidData()) {
        return 1;
    }

    std::ifstream file(argv[1]);
    if (file.fail()) {
        std::cout << "failed to open file " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line);
    std::pair<std::string, std::string> headerPair;
    try {
        headerPair = BitcoinExchange::getLinePairStr(line, '|');
    } catch (std::exception &ex) {
        std::cout << "\033[31mFailed to parse header line: " << ex.what()
                  << "\033[0m";
    }
    if (headerPair.first != "date") {
        std::cout << "\033[31mHeader does not contain \'date\' as the first "
                     "value\033[0m"
                  << std::endl;
    }
    if (headerPair.second != "value") {
        std::cout << "\033[31mHeader does not contain \'value\' as the first "
                     "value\033[0m"
                  << std::endl;
    }

    while (std::getline(file, line)) {
        std::pair<std::string, double> pair;
        try {
            pair = BitcoinExchange::getLinePair(line, '|');
        } catch (std::exception &ex) {
            std::cout << "\033[31mError: " << ex.what() << "\033[0m"
                      << std::endl;
            continue;
        }

        if (pair.second < 0) {
            std::cout << "\033[31mError: negative number\033[0m" << std::endl;
            continue;
        }
        if (pair.second > 1000) {
            std::cout << "\033[31mError: number too large\033[0m" << std::endl;
            continue;
        }

        double exchange_rate;
        try {
            exchange_rate = btc.getExchangeRateAt(pair.first);
        } catch (std::exception &ex) {
            std::cout << "\033[31mError: " << ex.what() << "\033[0m"
                      << std::endl;
            continue;
        }

        double res = pair.second * exchange_rate;
        std::cout << pair.first << " => " << pair.second << " = " << res
                  << std::endl;
    }

    file.clear(std::_S_eofbit);
    file.close();
    if (file.fail()) {
        std::cout << "failed to close file " << argv[1] << std::endl;
        return 1;
    }

    return 0;
}
