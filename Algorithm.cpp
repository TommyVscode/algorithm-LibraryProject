#include <iostream>
#include <string>
#include <iomanip> // For setw(), left, right
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    int year;
};

// Display table header
void displayHeader() {
    cout << left << setw(5)  << "ID"
         << " | " << left << setw(25) << "Title"
         << " | " << left << setw(20) << "Author"
         << " | " << right << setw(5) << "Year" << endl;
    cout << "-----+---------------------------+--------------------+-----" << endl;
}

// Display a book in aligned columns
void displayBook(Book b) {
    cout << left << setw(5)  << b.id
         << " | " << left << setw(25) << b.title
         << " | " << left << setw(20) << b.author
         << " | " << right << setw(5) << b.year << endl;
}

// View all books
void viewAll(Book books[], int n) {
    displayHeader();
    for (int i = 0; i < n; i++) {
        displayBook(books[i]);
    }
}

// Linear search by title
void searchByTitle(Book books[], int n, string key) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (books[i].title == key) {
            if (!found) displayHeader();
            displayBook(books[i]);
            found = true;
        }
    }
    if (!found) cout << "No book found with Title = \"" << key << "\"\n";
}

// Linear search by author
void searchByAuthor(Book books[], int n, string key) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (books[i].author == key) {
            if (!found) displayHeader();
            displayBook(books[i]);
            found = true;
        }
    }
    if (!found) cout << "No book found with Author = \"" << key << "\"\n";
}

// Linear search by ID
void searchByID(Book books[], int n, int key) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (books[i].id == key) {
            if (!found) displayHeader();
            displayBook(books[i]);
            found = true;
        }
    }
    if (!found) cout << "No book found with ID = " << key << "\n";
}

// Insertion Sort by Title
void sortByTitle(Book books[], int n) {
    for (int i = 1; i < n; i++) {
        Book key = books[i];
        int j = i - 1;
        while (j >= 0 && books[j].title > key.title) {
            books[j + 1] = books[j];
            j--;
        }
        books[j + 1] = key;
    }
    cout << "Books sorted by title!\n";
}

// Selection Sort by Author
void sortByAuthor(Book books[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (books[j].author < books[minIndex].author) {
                minIndex = j;
            }
        }
        swap(books[i], books[minIndex]);
    }
    cout << "Books sorted by author!\n";
}

// Merge function for Merge Sort (by year)
void merge(Book books[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Book L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = books[left + i];
    for (int j = 0; j < n2; j++) R[j] = books[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].year <= R[j].year) {
            books[k++] = L[i++];
        } else {
            books[k++] = R[j++];
        }
    }

    while (i < n1) books[k++] = L[i++];
    while (j < n2) books[k++] = R[j++];
}

void mergeSort(Book books[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(books, left, mid);
        mergeSort(books, mid + 1, right);
        merge(books, left, mid, right);
    }
}

// ------------------- MAIN ---------------------
int main() {
    Book books[10] = {
        {1, "C++ Basics", "Bjarne", 2015},
        {2, "Data Structures", "Mark", 2018},
        {3, "Algorithms", "Thomas", 2017},
        {4, "Operating System", "Silberschatz", 2012},
        {5, "Computer Networks", "Tanenbaum", 2014},
        {6, "Database System", "Navathe", 2016},
        {7, "AI Basics", "Russell", 2020},
        {8, "Machine Learning", "Goodfellow", 2019},
        {9, "Cryptography", "Stallings", 2013},
        {10, "Software Eng", "Pressman", 2011}
    };

    int n = 10;
    int choice;
    string key;
    int idKey;

    do {
        cout << "\n===== Library Menu =====\n";
        cout << "1. View all books\n";
        cout << "2. Search by ID\n";
        cout << "3. Search by title\n";
        cout << "4. Search by author\n";
        cout << "5. Sort by title (Insertion Sort)\n";
        cout << "6. Sort by author (Selection Sort)\n";
        cout << "7. Sort by year (Merge Sort)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();  // Clean input buffer for getline

        switch (choice) {
            case 1:
                viewAll(books, n);
                break;
            case 2:
                cout << "Enter ID: ";
                cin >> idKey;
                searchByID(books, n, idKey);
                break;
            case 3:
                cout << "Enter title: ";
                getline(cin, key);
                searchByTitle(books, n, key);
                break;
            case 4:
                cout << "Enter author: ";
                getline(cin, key);
                searchByAuthor(books, n, key);
                break;
            case 5:
                sortByTitle(books, n);
                viewAll(books, n);
                break;
            case 6:
                sortByAuthor(books, n);
                viewAll(books, n);
                break;
            case 7:
                mergeSort(books, 0, n - 1);
                cout << "Books sorted by year!\n";
                viewAll(books, n);
                break;
        }
    } while (choice != 0);

    cout << "\nThank you for using the Library Information System. Goodbye!\n";

    return 0;
}
