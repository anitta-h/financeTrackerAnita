#include <iostream>
using namespace std;

const int MAX_MONTHS = 12;
int monthsCount = 0;
double income[MAX_MONTHS];
double expense[MAX_MONTHS];
bool hasInfo[MAX_MONTHS];
const char* monthNames[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

bool compareFirst3(const char* a, const char* b) {
    for (int i = 0; i < 3; i++) {
        if (a[i] != b[i]) return false;
    }
    return true; 
}


void setup() {

    cout << "Enter number of months: ";
    cin >> monthsCount;

    for (int i = 0; i < monthsCount; i++) {
        income[i] = 0;
        expense[i] = 0;
        hasInfo[i] = false;
    }

    cout << "Profile created successfully.\n";
}

void add() {
    int month;
    
    cout << "Month: ";
    cin >> month;

    if (month < 1 || month > monthsCount) {
        cout << "Invalid month!\n";
        return;
    }

    int index = month - 1;

    cout << "Enter income: ";
    cin >> income[index];

    cout << "Enter expense: ";
    cin >> expense[index];

    hasInfo[index] = true;

    double balanceForMonth = income[index] - expense[index];
    cout << "Result: Balance for " << month << " = "
        << (balanceForMonth >= 0 ? "+" : "") << balanceForMonth << endl;
}


void report() {
double totalIncome;
double totalExpenses;
double totalBalance;

int count = 0;

    cout << "Month | Income | Expense | Balance" <<endl;
    cout << "----------------------------------\n";

    for (int i = 0; i < monthsCount; i++) {
        if (hasInfo[i]) {
            double balance = income[i] - expense[i];
            totalIncome = totalIncome + income[i];
            totalExpenses = totalExpenses + expense[i];
            totalBalance = totalBalance + balance;

            cout << monthNames[i] << " | " 
            << income[i] << + " | "
            << expense[i] << + " | "
            << (balance >= 0 ? "+" : "") << balance << endl;

            count++;
        }
    }
        cout << "----------------------------------\n";

        if (count > 0) {
            cout << "Total income: " << totalIncome << endl;
            cout << "Total expense: " << totalExpenses << endl;
            cout << "Average balance: " << totalBalance / count << endl;
        }
        else {
            cout << "No data available.\n";
        }
    }

void search() {
     char monthSearch[10];
    cout << "Search ";
    cin >> monthSearch;

    int index = -1;

    for (int i = 0; i < monthsCount; i++) {
        if (compareFirst3(monthSearch, monthNames[i])) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Invalid month name!\n";
        return;
    }
    if (!hasInfo[index]) {
        cout << "There is no data for this month.\n";
        return;
    }

    double balance = income[index] - expense[index];
    double ratio = 0.0;

    if(income[index] != 0) {
     ratio = (expense[index] / income[index]) * 100;
    }
    
    cout << "Income: " << income[index] << endl;
    cout << "Expense: " << expense[index] << endl;
    cout << "Balance: " << (balance >= 0 ? "+" : "") << balance << endl;
    cout << "Expense ratio: " << ratio << "%\n";
    }


void sort() {
    //TODO
}


int main()
{
    std::cout << "Hello World!\n";
}
