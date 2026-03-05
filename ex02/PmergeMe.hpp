#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <deque>
#include <vector>

class PmergeMe {
private:
    std::deque<int> m_queue;
    std::vector<int> m_vector;

public:
    PmergeMe(void);
    PmergeMe(const PmergeMe &other);
    ~PmergeMe(void);
    PmergeMe &operator=(const PmergeMe &other);

    void sort(std::deque<int> input);
    void sort(std::vector<int> input);
};

#endif
