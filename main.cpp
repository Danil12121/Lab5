#include <iostream>
#include <fstream>
#include <deque>
#include <list>
#include <algorithm>
#include <string>
#include <set>
#include <unordered_set>

class BankDeposit {
private:
    std::string name;
    double amount;
    std::string currency;
    double percent;

public:
    BankDeposit() : name(""), amount(0), currency(""), percent(0) {}

    BankDeposit(const std::string &n, double a, const std::string &c, double ir)
            : name(n), amount(a), currency(c), percent(ir) {}

    BankDeposit(const BankDeposit &other)
            : name(other.name), amount(other.amount), currency(other.currency), percent(other.percent) {}

    BankDeposit(BankDeposit &&other)
            : name(std::move(other.name)), amount(other.amount), currency(std::move(other.currency)), percent(other.percent) {
        other.amount = 0;
        other.percent = 0;
        other.name = "";
        other.currency = "";
    }

    BankDeposit &operator=(const BankDeposit &other) {
        if (this != &other) {
            name = other.name;
            amount = other.amount;
            currency = other.currency;
            percent = other.percent;
        }
        return *this;
    }

    BankDeposit &operator=(BankDeposit &&other) {
        if (this != &other) {
            name = std::move(other.name);
            amount = other.amount;
            currency = std::move(other.currency);
            percent = other.percent;
            other.name = "";
            other.currency = "";
            other.amount = 0;
            other.percent = 0;
        }
        return *this;
    }
    const std::string& getName() const { return name; }
    double getAmount() const { return amount; }
    const std::string& getCurrency() const { return currency; }
    double getpercent() const { return percent; }

    bool operator==(const BankDeposit& other) const {
        return name == other.name &&
               amount == other.amount &&
               currency == other.currency &&
               percent == other.percent;
    }
    friend std::ostream &operator<<(std::ostream &os, const BankDeposit &deposit) {
        os << "Name: " << deposit.name << ", Amount: " << deposit.amount
           << " " << deposit.currency << ", Percent: " << deposit.percent << "%";
        return os;
    }
    bool operator<(const BankDeposit &other) const {
        return name < other.name;
    }
};

namespace std {
    template<>
    struct hash<BankDeposit> {
        size_t operator()(const BankDeposit& deposit) const {
            return hash<string>()(deposit.getName()) ^
                   hash<double>()(deposit.getAmount()) ^
                   hash<string>()(deposit.getCurrency()) ^
                   hash<double>()(deposit.getpercent());
        }
    };
}
int main() {
    std::ifstream input("input.txt");
    if (!input) {
        std::cerr << "Cannot open input file" << std::endl;
        return 1;
    }

    std::deque<BankDeposit> deposits;
    std::string name, currency;
    double amount, rate;

    while (input >> name >> amount >> currency >> rate) {
        deposits.emplace_back(name, amount, currency, rate);
    }
    input.close();

    std::ofstream output("output.txt");
    output << "Start deque:" << std::endl;
    for (const auto &dep: deposits) {
        output << dep << std::endl;
    }

    std::sort(deposits.begin(), deposits.end());
    output << "\nSorted deque:" << std::endl;
    for (const auto &dep: deposits) {
        output << dep << std::endl;
    }

    std::list<BankDeposit> depositList;
    std::copy(deposits.begin(), deposits.end(), std::back_inserter(depositList));

    depositList.sort();

    output << "\nCopied and sorted list:" << std::endl;
    for (const auto &dep: depositList) {
        output << dep << std::endl;
    }
    std::set<BankDeposit> depositSet(deposits.begin(), deposits.end());
    std::unordered_set<BankDeposit> depositUnorderedSet(deposits.begin(), deposits.end());
    output << "\nSet:" << std::endl;
    for (const auto& dep : depositSet) {
        output << dep << std::endl;
    }

    output << "\nUnordered set:" << std::endl;
    for (const auto& dep : depositUnorderedSet) {
        output << dep << std::endl;
    }
    output.close();

    BankDeposit bD1("bD1111", 1000, "Rub", 5.0);
    BankDeposit moved(std::move(bD1));

    return 0;
}
