#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;
};

void deleteForwardHistory(Page*& current, Page*& tail) {
    if (current == NULL) return;

    Page* temp = current->next;

    while (temp != NULL) {
        Page* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    current->next = NULL;
    tail = current;
}

void visitPage(Page*& head, Page*& tail, Page*& current) {
    Page* newPage = new Page;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter URL: ";
    getline(cin, newPage->url);

    cout << "Enter title: ";
    getline(cin, newPage->title);

    cout << "Enter access time (hour minute second): ";
    for (int i = 0; i < 3; i++) {
        cin >> newPage->accessTime[i];
    }

    newPage->next = NULL;
    newPage->prev = NULL;

    if (head == NULL) {
        head = tail = current = newPage;
    } else {
        // Eðer current sondaysa normal ekleme yapýlsýn
        if (current == tail) {
            tail->next = newPage;
            newPage->prev = tail;
            tail = newPage;
            current = newPage;
        } 
        // Eðer back yaptýktan sonra yeni sayfa açýldýysa forward geçmiþ silinsin
        else {
            deleteForwardHistory(current, tail);
            current->next = newPage;
            newPage->prev = current;
            tail = newPage;
            current = newPage;
        }
    }

    cout << "Page added to history.\n";
}

void goBack(Page*& current) {
    if (current == NULL) {
        cout << "History is empty.\n";
    } else if (current->prev == NULL) {
        cout << "No previous page.\n";
    } else {
        current = current->prev;
        cout << "Current page: " << current->title << endl;
    }
}

void goForward(Page*& current) {
    if (current == NULL) {
        cout << "History is empty.\n";
    } else if (current->next == NULL) {
        cout << "No next page.\n";
    } else {
        current = current->next;
        cout << "Current page: " << current->title << endl;
    }
}

void deleteCurrent(Page*& head, Page*& tail, Page*& current) {
    if (current == NULL) {
        cout << "There is no page to delete.\n";
        return;
    }

    Page* temp = current;

    if (head == tail) {
        head = tail = current = NULL;
    }
    else if (current == head) {
        head = head->next;
        head->prev = NULL;
        current = head;
    }
    else if (current == tail) {
        tail = tail->prev;
        tail->next = NULL;
        current = tail;
    }
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
    }

    delete temp;
    cout << "Current page deleted.\n";
}

void displayHistory(Page* head, Page* current) {
    if (head == NULL) {
        cout << "History is empty.\n";
        return;
    }

    Page* temp = head;
    int count = 1;

    cout << "\n--- Browser History ---\n";

    while (temp != NULL) {
        cout << "Page " << count << endl;
        cout << "URL: " << temp->url << endl;
        cout << "Title: " << temp->title << endl;
        cout << "Access Time: ";

        for (int i = 0; i < 3; i++) {
            cout << temp->accessTime[i];
            if (i < 2) {
                cout << ":";
            }
        }
        cout << endl;

        if (temp == current) {
            cout << "This is the current page.\n";
        }

        cout << "-----------------------\n";
        temp = temp->next;
        count++;
    }
}

void clearMemory(Page*& head, Page*& tail, Page*& current) {
    Page* temp = head;

    while (temp != NULL) {
        Page* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    head = tail = current = NULL;
}

int main() {
    Page* head = NULL;
    Page* tail = NULL;
    Page* current = NULL;

    int choice;

    do {
        cout << "\n1. Visit Page" << endl;
        cout << "2. Back" << endl;
        cout << "3. Forward" << endl;
        cout << "4. Delete Current Page" << endl;
        cout << "5. Display History" << endl;
        cout << "6. EXIT" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                visitPage(head, tail, current);
                break;
            case 2:
                goBack(current);
                break;
            case 3:
                goForward(current);
                break;
            case 4:
                deleteCurrent(head, tail, current);
                break;
            case 5:
                displayHistory(head, current);
                break;
            case 6:
                clearMemory(head, tail, current);
                cout << "Program ended. Memory cleaned.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
