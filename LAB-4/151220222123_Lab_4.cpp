#include <iostream>
#include <string>
using namespace std;

struct MoneyBundle {
    string serialNumber, currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

MoneyBundle* topMoney = NULL;

void pushMoney(string serial, string currency, int c100, int c50, int c20) {
    MoneyBundle* n = new MoneyBundle{serial, currency, {c100, c50, c20}, topMoney};
    topMoney = n;
}

bool popMoney() {
    if (topMoney == NULL) return false;
    MoneyBundle* temp = topMoney;
    topMoney = topMoney->next;
    delete temp;
    return true;
}

void displayMoney() {
    if (topMoney == NULL) {
        cout << "Money stack is empty.\n";
        return;
    }
    MoneyBundle* temp = topMoney;
    while (temp != NULL) {
        cout << "Serial: " << temp->serialNumber
             << ", Currency: " << temp->currencyType
             << ", [100s:" << temp->billCounts[0]
             << ", 50s:" << temp->billCounts[1]
             << ", 20s:" << temp->billCounts[2] << "]\n";
        temp = temp->next;
    }
}

struct Customer {
    string customerName, transactionType;
};

const int SIZE = 5;
Customer queueArr[SIZE];
int frontQ = -1, rearQ = -1;

bool isEmpty() {
    return frontQ == -1;
}

bool isFull() {
    return frontQ == (rearQ + 1) % SIZE;
}

void enqueueCustomer(string name, string type) {
    if (isFull()) {
        cout << "Queue is full.\n";
        return;
    }
    if (isEmpty()) frontQ = rearQ = 0;
    else rearQ = (rearQ + 1) % SIZE;

    queueArr[rearQ] = {name, type};
}

bool dequeueCustomer() {
    if (isEmpty()) return false;
    if (frontQ == rearQ) frontQ = rearQ = -1;
    else frontQ = (frontQ + 1) % SIZE;
    return true;
}

void displayQueue() {
    if (isEmpty()) {
        cout << "Customer queue is empty.\n";
        return;
    }
    int i = frontQ;
    while (true) {
        cout << "Name: " << queueArr[i].customerName
             << ", Transaction: " << queueArr[i].transactionType << endl;
        if (i == rearQ) break;
        i = (i + 1) % SIZE;
    }
}

void processTransaction() {
    if (isEmpty()) {
        cout << "No customer in queue.\n";
        return;
    }
    if (topMoney == NULL) {
        cout << "No money bundle in stack.\n";
        return;
    }

    cout << "Processing " << queueArr[frontQ].customerName
         << " with bundle " << topMoney->serialNumber << endl;

    popMoney();
    dequeueCustomer();
}

void clearStack() {
    while (topMoney != NULL) popMoney();
}

int main() {
    int choice, c100, c50, c20;
    string serial, currency, name, type;

    do {
        cout << "\n1.Push Money\n2.Enqueue Customer\n3.Process Transaction\n4.Display All\n0.Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Serial Currency 100s 50s 20s: ";
                cin >> serial >> currency >> c100 >> c50 >> c20;
                pushMoney(serial, currency, c100, c50, c20);
                break;
            case 2:
                cout << "Name TransactionType: ";
                cin >> name >> type;
                enqueueCustomer(name, type);
                break;
            case 3:
                processTransaction();
                break;
            case 4:
                cout << "\n--- Money Stack ---\n";
                displayMoney();
                cout << "\n--- Customer Queue ---\n";
                displayQueue();
                break;
            case 0:
                clearStack();
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
