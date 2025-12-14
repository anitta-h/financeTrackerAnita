#include <iostream>
using namespace std;

double absDifference(double num1, double num2) {
    double diff = num1 - num2;
    if (diff < 0) {
        return -diff;
    }
    return diff;
}


void setup() {
int months;
    cout<<"Enter number of months: ";
    cin>> months;
}

void add() {
    int month;
    double income;
    double expense;
    cout << "Month: ";
    cin >> month;

    cout << "Enter income: ";
    cin >> income;

    cout << "Enter expense: ";
    cin >> expense;

    double balanceForMonth = absDifference(income,expense);
    char sign = (balanceForMonth >= 0) ? '+' : '-';
    cout << "Result: Balance for "<<month<<" = "<<sign <<balanceForMonth;
}


void report() {
    //TODO
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
