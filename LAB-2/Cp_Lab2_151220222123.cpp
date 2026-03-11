#include <iostream>
#include <string>
using namespace std;

struct Node {
    string title;
    Node* next;
};

void addSong(Node*& head, string songTitle) {
    Node* newNode = new Node;
    newNode->title = songTitle;
    newNode->next = head;
    head = newNode;

    cout << "Song added successfully.\n";
}

void searchSong(Node* head, string songTitle) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->title == songTitle) {
            cout << "Song found: " << songTitle << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Song not found.\n";
}

void displaySongs(Node* head) {
    if (head == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    Node* temp = head;
    int order = 1;

    cout << "\nPlaylist:\n";
    while (temp != nullptr) {
        cout << order << ". " << temp->title << endl;
        temp = temp->next;
        order++;
    }
}

int main() {
    Node* head = nullptr;
    int choice;
    string songTitle;

    do {
        cout << "\n--- Music Playlist Menu ---\n";
        cout << "1. Add Song\n";
        cout << "2. Search Song\n";
        cout << "3. List Songs\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, songTitle);
                addSong(head, songTitle);
                break;

            case 2:
                cout << "Enter song title to search: ";
                getline(cin, songTitle);
                searchSong(head, songTitle);
                break;

            case 3:
                displaySongs(head);
                break;

            case 4:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

