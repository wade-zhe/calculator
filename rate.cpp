#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

vector<string> split_csv_line(const string& line) {
    vector<string> result;
    stringstream ss(line);
    string item;
    while (getline(ss, item, ',')) {
        result.push_back(item);
    }
    return result;
}

struct ExchangeRate {
    double buy;
    double sell;
};

ExchangeRate get_exchange_rate(const string& currency_code) {
    ifstream file("rate.csv");
    string line;
    while (getline(file, line)) {
        if (line.find(currency_code) != string::npos) {
            vector<string> cols = split_csv_line(line);
            if (cols.size() >= 5) {
                double buy = stod(cols[3]);
                double sell = stod(cols[13]);
                return { buy, sell };
            }
        }
    }
    return { 0.0, 0.0 };
}

int main() {
    system("curl -s -o rate.csv https://rate.bot.com.tw/xrt/flcsv/0/day");

    string from, to;
    double amount;

    cout << "Enter source currency (e.g., USD): ";
    cin >> from;
    cout << "Enter target currency (e.g., JPY): ";
    cin >> to;
    cout << "Enter amount: ";
    cin >> amount;

    double result = 0.0;

    if (from == "TWD") {
        ExchangeRate to_rate = get_exchange_rate(to);
        if (to_rate.buy == 0) {
            cout << "Target currency not found." << endl;
            return 1;
        }
        result = amount / to_rate.buy;
    }
    else if (to == "TWD") {
        ExchangeRate from_rate = get_exchange_rate(from);
        if (from_rate.sell == 0) {
            cout << "Source currency not found." << endl;
            return 1;
        }
        result = amount * from_rate.sell;
    }
    else {
        ExchangeRate from_rate = get_exchange_rate(from);
        ExchangeRate to_rate = get_exchange_rate(to);
        if (from_rate.sell == 0 || to_rate.buy == 0) {
            cout << "Exchange rate not found. Please check your currency codes." << endl;
            return 1;
        }
        result = amount * from_rate.sell / to_rate.buy;
    }

    cout << fixed << setprecision(4);
    cout << amount << " " << from << " is approximately equal to " << result << " " << to << "." << endl;

    return 0;
}
