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

double absDifference(double num1, double num2) {
    double diff = num1 - num2;
    if (diff < 0) {
        return -diff;
    }
    return diff;
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
    //TODO
}

void sort() {
    //TODO
}


int main()
{
    std::cout << "Hello World!\n";
}
