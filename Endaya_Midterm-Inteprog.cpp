#include <iostream>
#include <cctype>
#include <limits>

using namespace std;

string trimSpaces(string str) {
    while(!str.empty() && isspace(str[0])) str.erase(0, 1);
    while(!str.empty() && isspace(str.back())) str.pop_back();
    return str;
}

class Book {
private:
    string ID;
    string ISBN;
    string Title;
    string Author;
    string Edition;
    string Publication;
    string Category;

    bool isAlphaNum(const string& str) {
        for(char c : str) if(!isalnum(c)) return false;
        return true;
    }

    bool isValidISBN(const string& isbn) {
        if(isbn.empty() || isbn[0] == '-') return false;
        int digits = 0;
        for(char c : isbn) {
            if(isdigit(c)) digits++;
            else if(c != '-') return false;
        }
        return (digits == 10 || digits == 13);
    }

public:
    void setID(const string& id, Book* books, int count) {
        string newID = trimSpaces(id);
        while(true) {
            if(newID.empty()) {
                cout << "ID cannot be empty: ";
                getline(cin, newID);
                newID = trimSpaces(newID);
                continue;
            }
            if(!isAlphaNum(newID)) {
                cout << "Only letters/numbers allowed: ";
                getline(cin, newID);
                newID = trimSpaces(newID);
                continue;
            }
            bool duplicate = false;
            for(int i = 0; i < count; i++) {
                if(books[i].getID() == newID) {
                    duplicate = true;
                    break;
                }
            }
            if(duplicate) {
                cout << "Duplicate ID! Try again: ";
                getline(cin, newID);
                newID = trimSpaces(newID);
            } else {
                ID = newID;
                break;
            }
        }
    }

    void setISBN(const string& isbn) {
        string newISBN = trimSpaces(isbn);
        while(true) {
            if(newISBN.empty()) {
                cout << "ISBN cannot be empty: ";
                getline(cin, newISBN);
                newISBN = trimSpaces(newISBN);
                continue;
            }
            if(isValidISBN(newISBN)) {
                ISBN = newISBN;
                break;
            }
            cout << "Invalid ISBN! Must be 10/13 digits (no leading dash): ";
            getline(cin, newISBN);
            newISBN = trimSpaces(newISBN);
        }
    }

    void setTitle(const string& title) {
        string newTitle = trimSpaces(title);
        while(newTitle.empty()) {
            cout << "Title cannot be empty: ";
            getline(cin, newTitle);
            newTitle = trimSpaces(newTitle);
        }
        Title = newTitle;
    }

    void setAuthor(const string& author) {
        string newAuthor = trimSpaces(author);
        while(newAuthor.empty()) {
            cout << "Author cannot be empty: ";
            getline(cin, newAuthor);
            newAuthor = trimSpaces(newAuthor);
        }
        Author = newAuthor;
    }

    void setEdition(const string& edition) {
        string newEdition = trimSpaces(edition);
        while(newEdition.empty()) {
            cout << "Edition cannot be empty: ";
            getline(cin, newEdition);
            newEdition = trimSpaces(newEdition);
        }
        Edition = newEdition;
    }

    void setPublication(const string& publication) {
        string newPublication = trimSpaces(publication);
        while(newPublication.empty()) {
            cout << "Publication cannot be empty: ";
            getline(cin, newPublication);
            newPublication = trimSpaces(newPublication);
        }
        Publication = newPublication;
    }

    void setCategory(const string& category) {
        string newCat = trimSpaces(category);
        while(true) {
            if(newCat.empty()) {
                cout << "Category cannot be empty: ";
                getline(cin, newCat);
                newCat = trimSpaces(newCat);
                continue;
            }
            string lower;
            for(char c : newCat) lower += tolower(c);
            if(lower == "fiction" || lower == "non-fiction" || lower == "nonfiction") {
                Category = (lower == "fiction") ? "Fiction" : "Non-fiction";
                break;
            }
            cout << "Category not found! Enter Fiction/Non-fiction: ";
            getline(cin, newCat);
            newCat = trimSpaces(newCat);
        }
    }

    string getID() const { return ID; }
    string getISBN() const { return ISBN; }
    string getTitle() const { return Title; }
    string getAuthor() const { return Author; }
    string getEdition() const { return Edition; }
    string getPublication() const { return Publication; }
    string getCategory() const { return Category; }

    void display() const {
        cout << "\n----------------------------------------\n"
             << "ID: " << ID << "\n"
             << "ISBN: " << ISBN << "\n"
             << "Title: " << Title << "\n"
             << "Author: " << Author << "\n"
             << "Edition: " << Edition << "\n"
             << "Publication: " << Publication << "\n"
             << "Category: " << Category << "\n"
             << "----------------------------------------\n";
    }
};

class Library {
private:
    static const int MAX_BOOKS = 100;
    Book books[MAX_BOOKS];
    int count = 0;

    int findBook(const string& id) const {
        string cleanID = trimSpaces(id);
        for(int i = 0; i < count; i++) {
            if(books[i].getID() == cleanID) return i;
        }
        return -1;
    }

    void waitForEnter() {
        cout << "Press any key to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool getBookID(string& id, const string& prompt) {
        cout << prompt;
        getline(cin, id);
        id = trimSpaces(id);
        if(findBook(id) != -1) return true;
        
        cout << "Book not found!\nPress any key to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

public:
    void addBook() {
        if(count >= MAX_BOOKS) {
            cout << "Library is full!\n";
            waitForEnter();
            return;
        }

        Book newBook;
        string input;

        while(true) {
            cout << "Enter category (Fiction/Non-fiction): ";
            getline(cin, input);
            input = trimSpaces(input);
            string lower;
            for(char c : input) lower += tolower(c);
            if(lower == "fiction" || lower == "non-fiction" || lower == "nonfiction") {
                newBook.setCategory(input);
                break;
            }
            cout << "Category not found!\n";
        }

        cout << "Enter book ID: ";
        getline(cin, input);
        newBook.setID(input, books, count);

        cout << "Enter ISBN: ";
        getline(cin, input);
        newBook.setISBN(input);

        cout << "Enter title: ";
        getline(cin, input);
        newBook.setTitle(input);

        cout << "Enter author: ";
        getline(cin, input);
        newBook.setAuthor(input);

        cout << "Enter edition: ";
        getline(cin, input);
        newBook.setEdition(input);

        cout << "Enter publication: ";
        getline(cin, input);
        newBook.setPublication(input);

        books[count++] = newBook;
        cout << "Book added successfully!\n";
        waitForEnter();
    }

    void editBook() {
        if(count == 0) {
            cout << "No books available!\n";
            waitForEnter();
            return;
        }

        string id;
        if(!getBookID(id, "Enter book ID to edit: ")) return;

        int index = findBook(id);
        string input;

        cout << "Editing book (leave blank to keep current value):\n";

        cout << "Current ISBN: " << books[index].getISBN() << "\n";
        cout << "New ISBN: ";
        getline(cin, input);
        if(!trimSpaces(input).empty()) books[index].setISBN(input);

        cout << "Current title: " << books[index].getTitle() << "\n";
        cout << "New title: ";
        getline(cin, input);
        if(!trimSpaces(input).empty()) books[index].setTitle(input);

        cout << "Current author: " << books[index].getAuthor() << "\n";
        cout << "New author: ";
        getline(cin, input);
        if(!trimSpaces(input).empty()) books[index].setAuthor(input);

        cout << "Current edition: " << books[index].getEdition() << "\n";
        cout << "New edition: ";
        getline(cin, input);
        if(!trimSpaces(input).empty()) books[index].setEdition(input);

        cout << "Current publication: " << books[index].getPublication() << "\n";
        cout << "New publication: ";
        getline(cin, input);
        if(!trimSpaces(input).empty()) books[index].setPublication(input);

        cout << "Current category: " << books[index].getCategory() << "\n";
        cout << "New category: ";
        getline(cin, input);
        if(!trimSpaces(input).empty()) books[index].setCategory(input);

        cout << "Book edited successfully!\n";
        waitForEnter();
    }

    void searchBook() {
        if(count == 0) {
            cout << "No books available!\n";
            waitForEnter();
            return;
        }

        string id;
        if(!getBookID(id, "Enter book ID to search: ")) return;

        books[findBook(id)].display();
        waitForEnter();
    }

    void deleteBook() {
        if(count == 0) {
            cout << "No books available!\n";
            waitForEnter();
            return;
        }

        string id;
        if(!getBookID(id, "Enter book ID to delete: ")) return;

        int index = findBook(id);
        books[index].display();
        
        cout << "Do you want to delete this book? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();

        if(tolower(choice) == 'y') {
            for(int i = index; i < count-1; i++) {
                books[i] = books[i+1];
            }
            count--;
            cout << "Book deleted successfully!\n";
        }
        waitForEnter();
    }

    void viewByCategory() {
        if(count == 0) {
            cout << "No books available!\n";
            waitForEnter();
            return;
        }

        string category;
        while(true) {
            cout << "Enter category (Fiction/Non-fiction): ";
            getline(cin, category);
            category = trimSpaces(category);
            string lower;
            for(char c : category) lower += tolower(c);
            if(lower == "fiction" || lower == "non-fiction" || lower == "nonfiction") {
                string searchCat = (lower == "fiction") ? "Fiction" : "Non-fiction";
                bool found = false;
                cout << "\nBooks in " << searchCat << ":\n";
                for(int i = 0; i < count; i++) {
                    if(books[i].getCategory() == searchCat) {
                        books[i].display();
                        found = true;
                    }
                }
                if(!found) cout << "No books in this category.\n";
                break;
            }
            cout << "Category not found!\n";
        }
        waitForEnter();
    }

    void viewAllBooks() {
        if(count == 0) {
            cout << "No books available!\n";
            waitForEnter();
            return;
        }

        cout << "\nAll Books (" << count << "):\n";
        for(int i = 0; i < count; i++) {
            books[i].display();
        }
        waitForEnter();
    }
};

void showMenu() {
    Library lib;
    string choice;

    while(true) {
        system("cls || clear");
        cout << "---------------------------------------------\n"
             << "LIBRARY MANAGEMENT SYSTEM\n"
             << "---------------------------------------------\n"
             << "1. Add Book\n"
             << "2. Edit Book\n"
             << "3. Search Book\n"
             << "4. Delete Book\n"
             << "5. View Books by Category\n"
             << "6. View All Books\n"
             << "7. Exit\n"
             << "---------------------------------------------\n";

        cout << "Enter your choice (1-7): ";
        getline(cin, choice);
        choice = trimSpaces(choice);

        if(choice.length() != 1) continue;

        switch(choice[0]) {
            case '1': lib.addBook(); break;
            case '2': lib.editBook(); break;
            case '3': lib.searchBook(); break;
            case '4': lib.deleteBook(); break;
            case '5': lib.viewByCategory(); break;
            case '6': lib.viewAllBooks(); break;
            case '7': return;
            default: continue;
        }
    }
}

int main() {
    showMenu();
    return 0;
}