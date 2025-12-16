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
double totalIncome = 0;
double totalExpenses = 0;
double totalBalance = 0;

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
            << income[i] << " | "
            << expense[i] << " | "
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
    char type[12];
    cout << "sort ";
    cin >> type;

    int idx[MAX_MONTHS];
    for (int i = 0; i < monthsCount; i++) {
        idx[i] = i;
    }

    for (int i = 0; i < monthsCount - 1; i++) {
        for (int j = i + 1; j < monthsCount; j++) {
            if (!hasInfo[idx[i]] || !hasInfo[idx[j]]) {
                continue;
            }

            double val1 = 0, val2 = 0;

            if (compareFirst3(type, "inc")) { 
                val1 = income[idx[i]];
                val2 = income[idx[j]];
            }
            else if (compareFirst3(type, "exp")) {
                val1 = expense[idx[i]];
                val2 = expense[idx[j]];
            }
            else if (compareFirst3(type, "bal")) {
                val1 = income[idx[i]] - expense[idx[i]];
                val2 = income[idx[j]] - expense[idx[j]];
            }
            else {
                cout << "Invalid sort type!\n";
                return;
            }

            if (val2 > val1) {
                int temp = idx[i];
                idx[i] = idx[j];
                idx[j] = temp;
            }
        }
    }

    cout << "Sorted by monthly " << type << ":\n";

    int count = 0;
    for (int i = 0; i < monthsCount && count < 3; i++) {
        int idxMonth = idx[i];
        if (!hasInfo[idxMonth]) continue;

        double value = 0;
        if (compareFirst3(type, "inc")) value = income[idxMonth];
        else if (compareFirst3(type, "exp")) value = expense[idxMonth];
        else if (compareFirst3(type, "bal")) value = income[idxMonth] - expense[idxMonth];

        char signChar = (compareFirst3(type, "bal") && value >= 0) ? '+' : '\0';

        cout << count + 1 << ". " << monthNames[idxMonth] << ": ";
        if (signChar != '\0') cout << signChar;
        cout << value << endl;

        count++;
    }

}

void forecast() {
    int monthsAhead;
    cout << "Months ahead: ";
    cin >> monthsAhead;

    double savings = 0;
    int count = 0;

    for (int i = 0; i < monthsAhead; i++) {
        if (hasInfo[i]) {
            savings = savings + income[i] - expense[i];
            count++;
        }
    }

    if (count == 0) {
        cout <<"No data.\n";
        return;
    }

    double avg = savings/count;

    cout << "Current savings: " << savings << endl;
    cout << "Average manthly change: ";
    if (avg >= 0) {
        cout << "+";
    }

    if (avg >= 0) {
        cout << "Predicted savings after " << monthsAhead
        << " months: " << savings + monthsAhead * avg << endl;
    }
    else {
        int runOutOfMoney = 0;
        double temp = savings;
        while (temp > 0) {
            temp += avg;
            runOutOfMoney++;
        }
        cout << "Expected to run out of money after "
            << runOutOfMoney << " months.\n";
    }
}

void chart() {
    //todo
}


int main()
{
    std::cout << "Hello World!\n";
}
