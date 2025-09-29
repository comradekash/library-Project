#include <iostream>
#include <string>
#include <stack>
using namespace std;
void addBook(string*& titles, string*& authors, int& size, string title, string author) {
    string* newTitles = new string[size + 1];
    string* newAuthors = new string[size + 1];
    for (int i = 0; i < size; i++) {
        newTitles[i] = titles[i];
        newAuthors[i] = authors[i];
    }
    newTitles[size] = title;
    newAuthors[size] = author;
    delete[] titles;
    delete[] authors;
    titles = newTitles;
    authors = newAuthors;
    size++;
}
void deleteBook(string*& titles, string*& authors, int& size,
    stack<string>& deletedTitles, stack<string>& deletedAuthors) {
    if (size == 0) {
        cout << "No books to delete!\n";
        return;
    }
    int index;
    cout << "Enter book number to delete (1-" << size << "): ";
    cin >> index;
    if (index < 1 || index > size) {
        cout << "Invalid index!\n";
        return;
    }
    deletedTitles.push(titles[index - 1]);
    deletedAuthors.push(authors[index - 1]);
    string* newTitles = new string[size - 1];
    string* newAuthors = new string[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index - 1) {
            newTitles[j] = titles[i];
            newAuthors[j] = authors[i];
            j++;
        }
    }
    delete[] titles;
    delete[] authors;

    titles = newTitles;
    authors = newAuthors;
    size--;

    cout << "Book deleted successfully!\n";
}
void undoDelete(string*& titles, string*& authors, int& size,
    stack<string>& deletedTitles, stack<string>& deletedAuthors) {
    if (deletedTitles.empty()) {
        cout << "No book to undo!\n";
        return;
    }

    string lastTitle = deletedTitles.top(); deletedTitles.pop();
    string lastAuthor = deletedAuthors.top(); deletedAuthors.pop();

    addBook(titles, authors, size, lastTitle, lastAuthor);

    cout << "Undo successful! Book restored.\n";
}
void searchBook(string* titles, string* authors, int size, string keyword) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (titles[i].find(keyword) != string::npos || authors[i].find(keyword) != string::npos) {
            cout << i + 1 << ". " << titles[i] << " by " << authors[i] << endl;
            found = true;
        }
    }
    if (!found) cout << "No matching book found.\n";
}


void displayBooks(string* titles, string* authors, int size) {
    if (size == 0) {
        cout << "No books in library!\n";
        return;
    }
    cout << "\nBook List:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << titles[i] << " by " << authors[i] << endl;
    }
}

int main() {
    int size = 0;
    string* titles = nullptr;
    string* authors = nullptr;

    stack<string> deletedTitles; 
    stack<string> deletedAuthors;

    int choice;
    do {
        cout << "\n=== Book Management Menu ===\n";
        cout << "1. Add Book\n";
        cout << "2. Delete Book\n";
        cout << "3. Undo Delete (Stack Pop)\n";
        cout << "4. Search Book\n";
        cout << "5. Display All Books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter author name: ";
            getline(cin, author);
            addBook(titles, authors, size, title, author);
        }
        else if (choice == 2) {
            deleteBook(titles, authors, size, deletedTitles, deletedAuthors);
        }
        else if (choice == 3) {
            undoDelete(titles, authors, size, deletedTitles, deletedAuthors);
        }
        else if (choice == 4) {
            string keyword;
            cout << "Enter title/author to search: ";
            getline(cin, keyword);
            searchBook(titles, authors, size, keyword);
        }
        else if (choice == 5) {
            displayBooks(titles, authors, size);
        }
    } while (choice != 6);
    delete[] titles;
    delete[] authors;

    return 0;
}