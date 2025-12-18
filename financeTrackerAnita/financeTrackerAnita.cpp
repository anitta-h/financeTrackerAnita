#include <iostream>
using namespace std;
//CHART, MAIN, DOUBLE .00
const int MAX_MONTHS = 12;
int monthsCount = 0;
double income[MAX_MONTHS];
double expense[MAX_MONTHS];
bool hasInfo[MAX_MONTHS];
const char* monthNames[12] = {
    "January", "February", "March", "April", "May", "Junå",
    "July", "August", "September", "October", "November", "December"
};

double ceil(double x, int digits) {
    double factor = 1.0;
    for (int i = 0; i < digits; i++) factor *= 10.0;

    double temp = x * factor;
    temp = (int)temp;          
    if (x * factor > temp)   
        temp += 1;

    return temp / factor;
}

bool equals(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

bool compareFirst3(const char* a, const char* b) {
    for (int i = 0; i < 3; i++) {
        if (a[i] != b[i]) return false;
    }
    return true; 
}
void printMonth3(int i) {
    for (int j = 0; j < 3; j++)
        cout << monthNames[i][j];
}

double round2(double x) {
    return (int)(x * 100 + (x >= 0 ? 0.5 : -0.5)) / 100.0;
}
void print2(double x) {
    x = round2(x);

    int whole = (int)x;
    int frac = (int)((x - whole) * 100);
    if (frac < 0) frac = -frac;

    cout << whole << ".";
    if (frac < 10) cout << "0";
    cout << frac;
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

    double balanceForMonth = round2(income[index] - expense[index]);
    cout << "Balance for " << month << " = "
        << (balanceForMonth >= 0 ? "+" : ""); 
        print2(balanceForMonth);
        cout << endl;
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
            totalIncome = round2(totalIncome + income[i]);
            totalExpenses = round2(totalExpenses + expense[i]);
            totalBalance = round2(totalBalance + balance);

            printMonth3(i);
            cout << " | ";
            print2(income[i]);
            cout << " | ";
            print2(income[i]);
            cout << " | " << (balance >= 0 ? "+" : "");
            print2(balance);
            cout << endl;


            count++;
        }
    }
        cout << "----------------------------------\n";

        if (count > 0) {
            cout << "Total income: ";
            print2(totalIncome);
            cout << endl;

            cout << "Total expense: ";
            print2(totalExpenses);
            cout << endl;

            double avg = totalBalance / count;
            cout << "Average balance: " << (avg >= 0 ? "+" : "");
            print2(ceil(avg, 2));
            cout << endl;
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
     ratio = ceil((expense[index] / income[index]) * 100, 1);
    }
    
    cout << "Income: ";
    print2(income[index]);
    cout << endl;

    cout << "Expense: ";
    print2(expense[index]);
    cout << endl;

    cout << "Balance: " << (balance >= 0 ? "+" : "");
    print2(balance);
    cout << endl;

    cout << "Expense ratio: ";
    cout << ratio;
    cout << "%\n";
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

        printMonth3(idxMonth);
        cout << ": " << (value >= 0 && compareFirst3(type, "bal") ? "+" : "");
        print2(value);
        cout << endl;

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

    cout << "Current savings: ";
    print2(savings);
    cout << endl;

    cout << "Average monthly change: " << (avg >= 0 ? "+" : "");
    print2(ceil(avg, 2));
    cout << endl;

    if (avg >= 0) {
        double predicted = savings + monthsAhead * avg;

        cout << "Predicted savings after " << monthsAhead
        << " months: " << (predicted >= 0 ? "+" : "");
        print2(ceil(predicted, 2));
        cout << endl;
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
//TODO
/*void chart() {
    const int STEP = 500;

    double maxIncome = 0;
    for (int i = 0; i < monthsCount; i++) {
        if (hasInfo[i] && income[i] > maxIncome)
            maxIncome = income[i];
    }

    if (maxIncome == 0) {
        cout << "No data available.\n";
        return;
    }

    cout << "=== YEARLY FINANCIAL CHART ===\n";

    for (int level = (int)maxIncome; level > 0; level -= STEP) {
        if (level < 1000) cout << "   "; 
        cout << level << " | ";

        for (int m = 0; m < monthsCount; m++) {
            if (hasInfo[m] && income[m] >= level)
                cout << "#   ";
            else
                cout << "    ";
        }
        cout << endl;
    }

    cout << "       ";
    for (int i = 0; i < monthsCount; i++)
        cout << "----";
    cout << endl;

    cout << "        ";
    for (int i = 0; i < monthsCount; i++)
        cout << monthNames[i][0] << monthNames[i][1] << monthNames[i][2] << " ";
    cout << endl;
}*/



int main()
{
    char command[15];

    while (true) {
        cout << "> ";
        cin >> command;

        switch (command[0]) {

        case 's':
            if (equals(command, "setup")) {
                setup();
            }
            else if (equals(command, "search")) {
                search();
            }
            else if (equals(command, "sort")) {
                sort();
            }
            else {
                cout << "Unknown command!\n";
            }
            break;

        case 'a':
            if (equals(command, "add")) {
                add();
            }
            else {
                cout << "Unknown command!\n";
            }
            break;

        case 'r':
            if (equals(command, "report")) {
                report();
            }
            else {
                cout << "Unknown command!\n";
            }
            break;

        case 'f':
            if (equals(command, "forecast")) {
                forecast();
            }
            else {
                cout << "Unknown command!\n";
            }
            break;

        case 'c':
            if (equals(command, "chart")) {
                //chart();
            }
            else {
                cout << "Unknown command!\n";
            }
            break;

        case 'e':
            if (equals(command, "exit")) {
                cout << "Final report:\n";
                report();
                cout << "Exiting program.\n";
                return 0;
            }
            else {
                cout << "Unknown command!\n";
            }
            break;

        default:
            cout << "Unknown command!\n";
        }
    }
}
