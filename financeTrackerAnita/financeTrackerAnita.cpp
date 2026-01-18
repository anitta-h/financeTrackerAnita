/**
*
* Solution to course project #3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author <Anita Hadzhilambreva>
* @idnumber 1MI0600604
* @compiler VC
*
* <file with helper functions>
*
*/

#include <iostream>
using namespace std;

const int MAX_MONTHS = 12;
const int COMMAND_MAX_LEN = 15;
const int MONTH_NAME_LEN = 10;
const int SORT_TYPE_LEN = 12;
const int MONTH_ABBR_LEN = 3;
const int TOP_MONTHS = 3;
bool shouldExit = false;


const char* monthNames[MAX_MONTHS] = {
    "January", "February", "March", "April", "May", "Junå",
    "July", "August", "September", "October", "November", "December"
};

double ceil(double x, int digits) {
    double factor = 1.0;

    for (int i = 0; i < digits; i++) {
        factor *= 10.0;
    }

    double temp = x * factor;

    if (x >= 0) {
        temp = (int)temp;
        if (x * factor > temp) temp += 1;
    }
    else {
        temp = (int)temp;
        if (x * factor < temp) temp -= 1;
    }

    return temp / factor;
}

bool equals(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
        return false;
        }
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

bool compareFirst3(const char* a, const char* b) {
    for (int i = 0; i < TOP_MONTHS; i++) {
        if (a[i] != b[i]) {
        return false;
        }
    }

    return true; 
}

void printMonth3(int index) {
    for (int j = 0; j < MONTH_ABBR_LEN; j++)
        cout << monthNames[index][j];
}

double round2(double x) {
    return (int)(x * 100 + (x >= 0 ? 0.5 : -0.5)) / 100.0;
}
void print2(double x) {
    x = round2(x);

    int whole = (int)x;
    int frac = (int)((x - whole) * 100);
    if (frac < 0) {
        frac = -frac;
    }

    cout << whole << ".";

    if (frac < 10) {
    cout << "0";
    }

    cout << frac;
}


void setup(int& monthsCount, bool hasInfo[], double income[], double expense[]) {

    cout << "Enter number of months: ";
    cin >> monthsCount;

    if (monthsCount < 1 || monthsCount > MAX_MONTHS) {
        cout << "Invalid number of months!\n";
        monthsCount = 0;
        return;
    }


    for (int i = 0; i < monthsCount; i++) {
        income[i] = 0;
        expense[i] = 0;
        hasInfo[i] = false;
    }

    cout << "Profile created successfully.\n";
}

void add(int monthsCount, double income[], double expense[], bool hasInfo[]) {
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

    cout << "Balance for " << monthNames[index] << " = "
        << (balanceForMonth >= 0 ? "+" : ""); 
        print2(balanceForMonth);
        cout << endl;
}


void report(int monthsCount, double income[], double expense[], bool hasInfo[]) {
    double totalIncome = 0;
    double totalExpenses = 0;
    double totalBalance = 0;
    int count = 0;

    cout << "Month | Income | Expense | Balance" <<endl;
    cout << "----------------------------------\n";

    for (int i = 0; i < monthsCount; i++) {
        if (!hasInfo[i]) {
            continue;
        }

        double balance = income[i] - expense[i];

        totalIncome += income[i];
        totalExpenses += expense[i];
        totalBalance += balance;

        printMonth3(i);
        cout << " | ";
        print2(income[i]);
        cout << " | ";
        print2(expense[i]);
        cout << " | " << (balance >= 0 ? "+" : "");
        print2(balance);
        cout << endl;

        count++;
    }

    cout << "----------------------------------\n";

    if (count == 0) {
        cout << "No data available.\n";
        return;
    }

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

void search(int monthsCount, double income[], double expense[], bool hasInfo[]) {
    char monthSearch[MONTH_NAME_LEN];
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

    if (income[index] != 0) {
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


void sort(int monthsCount, double income[], double expense[], bool hasInfo[]) {
    char type[SORT_TYPE_LEN];
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
    int displayNumber = 1;
    for (int i = 0; i < monthsCount && count < TOP_MONTHS; i++) {
        int idxMonth = idx[i];
        if (!hasInfo[idxMonth]) {
             continue;
        }

        double value = 0;
        if (compareFirst3(type, "inc")) {
             value = income[idxMonth];
         } else if (compareFirst3(type, "exp")) {
             value = expense[idxMonth];
         } else if (compareFirst3(type, "bal")) {
         value = income[idxMonth] - expense[idxMonth];
         }

         cout << displayNumber << ". ";
         printMonth3(idxMonth);
         cout << ": " << (value >= 0 && compareFirst3(type, "bal") ? "+" : "");
         print2(value);
         cout << endl;

         count++;
         displayNumber++;
    }

}

void calculateSavings(int monthsAhead, double& savings, double& avg, int& count,
                      int monthsCount, double income[], double expense[], bool hasInfo[]) {
    savings = 0;
    count = 0;

    for (int i = 0; i < monthsAhead; i++) {
        if (hasInfo[i]) {
            savings += income[i] - expense[i];
            count++;
        }
    }

    if (count > 0) {
        avg = savings / count;
    }
    else {
        avg = 0;
    }
}

void predictFuture(int monthsAhead, double savings, double avg) {
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

void forecast(int monthsCount, double income[], double expense[], bool hasInfo[]) {
    int monthsAhead;
    cout << "Months ahead: ";
    cin >> monthsAhead;

    if (monthsAhead > monthsCount) {
        cout << "Warning: You entered more months ahead than available data ("
            << monthsCount << " months). Calculation will use only available months.\n";
        monthsAhead = monthsCount;
    }

    double savings, avg;
    int count;
    calculateSavings(monthsAhead, savings, avg, count, monthsCount, income, expense, hasInfo);

    if (count == 0) {
        cout << "No data.\n";
        return;
    }

    cout << "Current savings: ";
    print2(savings);
    cout << endl;

    cout << "Average monthly change: " << (avg >= 0 ? "+" : "");
    print2(ceil(avg, 2));
    cout << endl;

    predictFuture(monthsAhead, savings, avg);
}

void chart(int monthsCount, double income[], double expense[], bool hasInfo[]) {
    if (monthsCount == 0) {
        cout << "No data.\n";
        return;
    }

    bool hasAnyData = false;
    double minBalance = 0;
    double maxBalance = 0;

    for (int i = 0; i < monthsCount; i++) {
        if (hasInfo[i]) {
            double balance = income[i] - expense[i];

            if (!hasAnyData) {
                minBalance = balance;
                maxBalance = balance;
                hasAnyData = true;
            }
            else {
                if (balance < minBalance) {
                    minBalance = balance;
                }
                if (balance > maxBalance) {
                    maxBalance = balance;
                }
            }
        }
    }

    if (!hasAnyData) {
        cout << "No data.\n";
        return;
    }

    cout << "=== YEARLY FINANCIAL CHART ===\n";

    double range = maxBalance - minBalance;
    int levels = 10;
    double step = range / levels;

    if (step <= 0) {
        step = 1;
    }

    for (double level = maxBalance; level >= minBalance; level -= step) {
        int printedLevel = (int)level;

        if (printedLevel >= 0 && printedLevel < 1000) {
            cout << " ";
        }
        if (printedLevel >= -999 && printedLevel < 0) {
            cout << " ";
        }

        cout << printedLevel << " | ";

        for (int m = 0; m < monthsCount; m++) {
            if (hasInfo[m]) {
                double balance = income[m] - expense[m];
                if (balance >= level) {
                    cout << "# ";
                }
                else {
                    cout << "  ";
                }
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    cout << "      ";
    for (int i = 0; i < monthsCount; i++) {
        cout << "--";
    }
    cout << endl;

    cout << "      ";
    for (int i = 0; i < monthsCount; i++) {
        printMonth3(i);
        cout << " ";
    }
    cout << endl;
}

void printHelp() {
    cout << "============================================\n";
    cout << " PERSONAL FINANCE MANAGER - USER GUIDE\n";
    cout << "============================================\n";
    cout << "This application manages monthly incomes\n";
    cout << "and expenses for up to 12 months.\n\n";

    cout << "Available commands:\n";
    cout << " setup                -> create profile and set number of months\n";
    cout << " add                  -> add income and expense for a month\n";
    cout << " report               -> show summary report for all months\n";
    cout << " sort inc|exp|bal     -> show top 3 months by income, expense or balance\n";
    cout << " search <month>       -> show detailed info for a given month\n";
    cout << " forecast             -> predict future savings\n";
    cout << " chart                -> display yearly balance chart\n";
    cout << " help                 -> display help information\n";
    cout << " exit                 -> show final report and exit program\n\n";

    cout << "Notes:\n";
    cout << " - Months are entered as numbers (1 - January, 12 - December)\n";
    cout << " - Month names are matched by first 3 letters (e.g. Jan, Feb)\n";
    cout << " - Use setup before adding data\n";
    cout << "============================================\n\n";
}



void processCommand(const char* command, int& monthsCount, double income[], double expense[], bool hasInfo[]) {
    if (equals(command, "setup")) {
        setup(monthsCount, hasInfo, income, expense);
    }
    else if (equals(command, "add")) {
        add(monthsCount, income, expense, hasInfo);
    }
    else if (equals(command, "report")) {
        report(monthsCount, income, expense, hasInfo);
    }
    else if (equals(command, "sort")) {
        sort(monthsCount, income, expense, hasInfo);
    }
    else if (equals(command, "chart")) {
        chart(monthsCount, income, expense, hasInfo);
    }
    else if (equals(command, "search")) {
        search(monthsCount, income, expense, hasInfo);
    }
    else if (equals(command, "forecast")) {
        forecast(monthsCount, income, expense, hasInfo);
    }
    else if (equals(command, "help")) {
        printHelp();
    }
    else {
        cout << "Unknown command!\n";
    }
}


int main()
{
    char command[COMMAND_MAX_LEN];
    int monthsCount = 0;
    double income[MAX_MONTHS];
    double expense[MAX_MONTHS];
    bool hasInfo[MAX_MONTHS];

    printHelp();

    while (true) {
        cout << "> ";
        cin >> command;
        if (equals(command, "exit")) {
            cout << "Final report:\n";
            report(monthsCount, income, expense, hasInfo);
            cout << "Exiting program.\n";
            break;
        }
        processCommand(command, monthsCount, income, expense, hasInfo);
    }
    return 0;
}
