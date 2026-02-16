#ifndef __BITCOIN_EXCHANGE_HPP__
#define __BITCOIN_EXCHANGE_HPP__

#include <map>
#include <string>
#include <utility>

class BitcoinExchange {
private:
    std::map<std::string, double> m_map;
    bool m_has_valid_map;

    BitcoinExchange(void);

    void parseDatabase(const std::string &path);

public:
    BitcoinExchange(const std::string &database_path);
    BitcoinExchange(const BitcoinExchange &other);
    ~BitcoinExchange(void);
    BitcoinExchange &operator=(const BitcoinExchange &other);

    const bool &hasValidData(void) const;
    void printData(void) const;
    double getExchangeRateAt(const std::string &date) const;

    static const std::string HEADER_FIRST_VAL;
    static const std::string HEADER_SECOND_VAL;

    // Util
    static std::pair<std::string, std::string>
    getLinePair(const std::string &line, const char seperator);
    static bool isValidDate(const std::string &date);
    static void trimString(std::string &str);
};

#endif
