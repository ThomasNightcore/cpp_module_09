#include "BitcoinExchange.hpp"
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

const std::string BitcoinExchange::HEADER_FIRST_VAL = "date";
const std::string BitcoinExchange::HEADER_SECOND_VAL = "exchange_rate";

BitcoinExchange::BitcoinExchange(void) : m_has_valid_map(false) {
    m_map = std::map<std::string, double>();
}

BitcoinExchange::BitcoinExchange(const std::string &database_path)
    : m_has_valid_map(false) {
    try {
        parseDatabase(database_path);
        m_has_valid_map = true;
    } catch (std::exception &ex) {
        std::cout << "Failed to parse the given database \'" << database_path
                  << "\' because: " << ex.what() << std::endl;
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : m_has_valid_map(other.m_has_valid_map) {
    m_map = std::map<std::string, double>(other.m_map);
}

BitcoinExchange::~BitcoinExchange(void) {
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        m_map = other.m_map;
        m_has_valid_map = other.m_has_valid_map;
    }

    return *this;
}

void BitcoinExchange::parseDatabase(const std::string &path) {
    std::ifstream file(path.c_str());
    if (file.fail()) {
        throw std::runtime_error("Failed to open path");
    }

    std::string line;

    // check header validity
    std::getline(file, line);
    std::pair<std::string, std::string> linePair;
    try {
        linePair = getLinePair(line, ',');
    } catch (std::exception &ex) {
        throw std::runtime_error("Failed to parse header line: " +
                                 std::string(ex.what()));
    }
    if (linePair.first != HEADER_FIRST_VAL) {
        throw std::runtime_error(
            "Header does not contain \'date\' as the first value");
    }
    if (linePair.second != HEADER_SECOND_VAL) {
        throw std::runtime_error(
            "Header does not contain \'exchange_rate\' as the second value");
    }

    // parse all remaining lines
    int lineNbr = 2;
    while (std::getline(file, line)) {
        std::stringstream ss;
        try {
            linePair = getLinePair(line, ',');
        } catch (std::exception &ex) {
            ss << "Failed to parse line " << lineNbr << ": " << ex.what();
            throw std::runtime_error(ss.str());
        }
        if (!isValidDate(linePair.first)) {
            ss << lineNbr;
            throw std::runtime_error("Failed to parse line " + ss.str() +
                                     ": Date provided is not valid");
        }

        double value;
        try {
            ss << linePair.second;
            ss >> value;
        } catch (std::exception &ex) {
            ss.clear();
            ss << lineNbr;
            throw std::runtime_error("Failed to parse line " + ss.str() +
                                     ": Failed to parse exchange rate");
        }

        if (m_map.find(linePair.first) != m_map.end()) {
            ss.clear();
            ss << lineNbr;
            throw std::runtime_error("Duplicate entry for " + linePair.first +
                                     " in line " + ss.str());
        }
        m_map.insert(std::pair<std::string, double>(linePair.first, value));
        lineNbr++;
    }

    file.close();
    if (file.fail()) {
        throw std::runtime_error("Failed closing the file " + path);
    }
}

double BitcoinExchange::getExchangeRateAt(const std::string &date) const {
    if (m_map.begin()->first > date) {
        throw std::runtime_error(
            "Bitcoin didn't exist yet. Choose a date after " +
            m_map.begin()->first);
    }
    // find the right value here
    return 0;
}

const bool &BitcoinExchange::hasValidData(void) const {
    return m_has_valid_map;
}

void BitcoinExchange::printData(void) const {

    std::cout << " ========= Printing Map =========" << std::endl;
    std::map<std::string, double>::const_iterator iter;
    for (iter = m_map.begin(); iter != m_map.end(); iter++) {
        std::cout << "[" << iter->first << ", " << iter->second << "]"
                  << std::endl;
    }
}

// ###################
// #   Static Util   #
// ###################
std::pair<std::string, std::string>
BitcoinExchange::getLinePair(const std::string &line, const char seperator) {
    std::string::size_type pos = line.find(seperator);
    if (pos == std::string::npos) {
        throw std::runtime_error("No seperator found");
    }
    if (line.find(seperator, pos + 1) != std::string::npos) {
        throw std::runtime_error("Too many seperators");
    }

    std::string one = line.substr(0, pos);
    std::string two = line.substr(pos + 1, line.length());
    trimString(one);
    trimString(two);
    return std::pair<std::string, std::string>(one, two);
}

/* a year is a leap year if it is divisible by 4, but not by 100 unless
 * they are divisible by 400 too.
 *  Examples:
 *   - 2000, 2400        are leap years
 *   - 2100, 2200, 2300  are not leap years
 */
static bool is_leap_year(int year) {
    return (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0));
}

/*
 * A date format is parsed like following: "Year-Month-Day"
 */
bool BitcoinExchange::isValidDate(const std::string &date) {
    int year, month, day;
    std::string::size_type pos, prev_pos, length;
    length = date.length();

    /* Year */
    prev_pos = 0;
    pos = date.find('-', prev_pos);
    if (pos == std::string::npos) {
        return false;
    }
    try {
        std::stringstream ss(date.substr(prev_pos, pos - prev_pos));
        ss >> year;
    } catch (...) {
        return false;
    }

    /* Month */
    prev_pos = pos + 1;
    pos = date.find('-', prev_pos);
    if (pos == std::string::npos) {
        return false;
    }
    try {
        std::stringstream ss(date.substr(prev_pos, pos - prev_pos));
        ss >> month;
    } catch (...) {
        return false;
    }

    if (month < 1 || month > 12)
        return false;

    /* Day */
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap_year(year))
        days[1]++;

    pos += 1;
    try {
        std::stringstream ss(date.substr(pos, 2));
        ss >> day;
        if (!ss.eof())
            return false;
    } catch (...) {
        return false;
    }

    return (pos + 2 == length) && !(day > days[month - 1] || day < 1);
}

void BitcoinExchange::trimString(std::string &s) {
    s.erase(0, s.find_first_not_of("\t\n\r\f\v ")); // left trim
    s.erase(s.find_last_not_of("\t\n\r\f\v ") + 1); // right trim
}
