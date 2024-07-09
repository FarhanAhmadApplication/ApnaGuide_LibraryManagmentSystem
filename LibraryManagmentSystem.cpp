// Library Management System

//  Build a program that simulates a library management system.

//  Include features to add books, display book details, check-out and return books, and maintain a record of library patrons.

// Use object-oriented programming principles with classes and data structures like linked lists or vectors.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>

using namespace std;

class Book
{
public:
    string book_title;
    int no_of_pages;
    string book_author_name;
    bool book_status;
    string ISBN_no;
    Book() {}

    Book(string book_title, int no_of_pages, string book_author_name, bool book_status, string ISBN_no)
    {
        this->book_title = book_title;
        this->no_of_pages = no_of_pages;
        this->book_author_name = book_author_name;
        this->book_status = book_status;
        this->ISBN_no = ISBN_no;
    }
    void DisplayBookDetails(vector<Book> &book)
    {
        for (int i = 0; i < book.size(); i++)
        {
            cout << "Book Name: " << book[i].book_title;
            cout << " ,Number of pages in the book: " << book[i].no_of_pages;
            cout << " ,Author name: " << book[i].book_author_name;
            if (book[i].book_status)
                cout << " ,Status: " << "Available";
            else
                cout << " ,Status: " << "Checked Out";
            cout << " ,ISBN no of book: " << book[i].ISBN_no << endl;
        }
    }
    void SearchBook(string name, vector<Book> book)
    {
        for (int i = 0; i < book.size(); i++)
        {
            if (book[i].book_title == name)
            {
                cout << "Book Name: " << book[i].book_title;
                cout << " ,Number of pages in the book: " << book[i].no_of_pages;
                cout << " ,Author name: " << book[i].book_author_name;
                if (book[i].book_status)
                    cout << " ,Status: " << "Available";
                else
                    cout << " ,Status: " << "Checked Out";
                cout << " ,ISBN no of book: " << book[i].ISBN_no << endl;
            }
        }
    }
    void DeleteBook(string name, vector<Book> &book)
    {
        int c = 0;
        for (int i = 0; i < book.size(); i++)
        {
            if (name == book[i].book_title)
            {
                if (book[i].book_status == 1)
                    book.erase(book.begin() + i);
                else
                    cout << "Book has been borrowed " << endl;
            }

            else
                c++;
        }
        if (c == book.size())
            cout << "No such book exits" << endl;
    }
};

class Patron
{
public:
    string name;
    int patron_id;
    vector<string> name_of_books_borrowed;
    Patron() {}
    Patron(string name, int patron_id, vector<string> name_of_books_borrowed)
    {
        this->name = name;
        this->patron_id = patron_id;
        this->name_of_books_borrowed = name_of_books_borrowed;
    }

    void displayPatrondetails(vector<Patron> &patron)
    {
        for (int i = 0; i < patron.size(); i++)
        {
            cout << "Patron Name:" << patron[i].name;
            cout << " ,Patron Id: " << patron[i].patron_id;
            cout << " ,Books borrowed: ";
            if (patron[i].name_of_books_borrowed.size() == 0)
                cout << "0" << endl;
            else
            {
                for (int j = 0; j < patron[i].name_of_books_borrowed.size(); j++)
                {
                    cout << patron[i].name_of_books_borrowed[j];
                    if (j < patron[i].name_of_books_borrowed.size() - 1)
                        cout << ", ";
                }
                cout << endl;
            }
        }
    }
    void borrow_book(string book_name, vector<Book> &book, vector<Patron> &patron, string name)
    {
        int count = 0;
        int count1 = 0;
        for (int i = 0; i < patron.size(); i++)
        {
            if (name == patron[i].name)
            {
                for (int j = 0; j < book.size(); j++)
                {
                    if (book[j].book_title == book_name)
                    {
                        if (book[j].book_status)
                        {
                            book[j].book_status = false;
                            patron[i].name_of_books_borrowed.push_back(book[j].book_title);
                            cout << "Book withdrawn" << endl;
                        }
                        else
                            cout << "Book Checked Out" << endl;
                    }
                    else
                        count++;
                }
            }
            else
                count1++;
        }
        if (count1 == patron.size())
            cout << "There is no patron with name " << name << endl;
        else if (count == book.size())
            cout << "No such book exists" << endl;
    }

    void return_borrowed_books(string book_name, vector<Book> &book, vector<Patron> &patron, string name)
    {
        int count = 0;
        int count1 = 0;
        int count2 = 0;
        for (int i = 0; i < patron.size(); i++)
        {
            if (patron[i].name == name)
            {
                if (patron[i].name_of_books_borrowed.size() > 0)
                {
                    for (int j = 0; j < book.size(); j++)
                    {
                        if (book[j].book_title == book_name)
                        {
                            if (book[j].book_status == false)
                            {
                                book[j].book_status = true;
                                for (int k = 0; k < patron[i].name_of_books_borrowed.size(); k++)
                                {
                                    if (book_name == patron[i].name_of_books_borrowed[k])
                                    {
                                        patron[i].name_of_books_borrowed.erase(patron[i].name_of_books_borrowed.begin() + k);
                                        cout << "Book Returned" << endl;
                                    }
                                }
                            }
                            else
                                cout << "Book Not Borrowed" << endl;
                        }
                        else
                            count++;
                    }
                }
                else
                    count2++;
            }
            else
                count1++;
        }
        if (count1 == patron.size())
            cout << "There is no patron with name " << name << endl;
        else if (count == book.size())
            cout << "No such book exists" << endl;
        else if (count2 > 0)
            cout << name << " Has not borrowed any book" << endl;
    }
    void deletePatron(vector<Patron> &patron, string name, vector<Book> &book)
    {
        for (int i = 0; i < patron.size(); i++)
        {
            if (name == patron[i].name)
            {
                if (patron[i].name_of_books_borrowed.size() == 0)
                    patron.erase(patron.begin() + i);
                else
                    cout << "First Return the Books" << endl;
            }
        }
    }

    void display_borrowed_books(string name, vector<Patron> &patron)
    {
        int c = 0;
        for (int i = 0; i < patron.size(); i++)
        {
            if (patron[i].name == name)
            {
                if (patron[i].name_of_books_borrowed.size() == 0)
                    cout << "No books have been borrowed by " << name << endl;
                else
                {
                    cout << "Books borrowed by " << name << " are:" << endl;
                    for (int j = 0; j < patron[i].name_of_books_borrowed.size(); j++)
                    {
                        cout << patron[i].name_of_books_borrowed[j] << endl;
                    }
                }
            }
        }
        if (c == patron.size())
            cout << "No such patron" << endl;
    }
    void showSearchPatron(string name, vector<Patron> patron)
    {
        int c = 0;
        for (int i = 0; i < patron.size(); i++)
        {
            if (patron[i].name == name)
            {
                cout << "Patron Name:" << patron[i].name;
                cout << " ,Patron Id: " << patron[i].patron_id;
                cout << " ,Books borrowed: ";
                if (patron[i].name_of_books_borrowed.size() == 0)
                    cout << "0" << endl;
                else
                {
                    for (int j = 0; j < patron[i].name_of_books_borrowed.size(); j++)
                    {
                        cout << patron[i].name_of_books_borrowed[j];
                        if (j < patron[i].name_of_books_borrowed.size() - 1)
                            cout << ", ";
                    }
                    cout << endl;
                }
            }
            else
            {
                c++;
            }
        }
        if (c == patron.size())
        {
            cout << "There is no patron with name" << name << endl;
        }
    }
};

void inputBookDetails(vector<Book> &book)
{
    string book_name;
    int no_of_pages;
    string book_author_name;
    string ISBN_no;
    char choice;
    do
    {
        cout << "Enter name of book" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, book_name);
        cout << "Enter no of pages in book" << endl;
        cin >> no_of_pages;
        cout << "Enter author of book" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, book_author_name);
        cout << "Enter ISBN no of book" << endl;
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, ISBN_no);
        if (book.size() == 0)
        {
            Book book1(book_name, no_of_pages, book_author_name, true, ISBN_no);
            book.push_back(book1);
        }
        else
        {
            for (int i = 0; i < book.size(); i++)
            {
                if (book_name != book[i].book_title)
                {
                    Book book1(book_name, no_of_pages, book_author_name, true, ISBN_no);
                    book.push_back(book1);
                }
                else
                {
                    cout << "Book with same name exists" << endl;
                }
            }
        }

        cout << "Do you want to add more books" << endl
             << "Press y for yes and n for no: ";
        cin >> choice;
    } while (choice == 'y');
}

void readBooktxt(vector<Book> &book)
{
    ifstream in;
    int i = 0;
    string s;
    string book_name;
    int no_of_pages;
    string book_author_name;
    bool book_status;
    string ISBN_no;
    in.open("Books.txt");
    while (in.eof() == 0)
    {
        if (i == 5)
        {
            i = 0;
            Book book1(book_name, no_of_pages, book_author_name, book_status, ISBN_no);
            book.push_back(book1);
        }
        switch (i)
        {
        case 0:
            getline(in, book_name);
            i++;
            break;
        case 1:
            getline(in, s);
            no_of_pages = stoi(s);
            i++;
            break;
        case 2:
            getline(in, book_author_name);
            i++;
            break;
        case 3:
            getline(in, s);
            if (s == "1")
                book_status = true;
            else
                book_status = false;
            i++;
            break;
        case 4:
            getline(in, ISBN_no);
            i++;
            break;
        }
    }
}

void insertBooktxt(vector<Book> &book)
{
    ofstream out;
    out.open("Books.txt");
    for (int i = 0; i < book.size(); i++)
    {
        out << book[i].book_title << "\n";
        out << book[i].no_of_pages << "\n";
        out << book[i].book_author_name << "\n";
        out << book[i].book_status << "\n";
        out << book[i].ISBN_no << "\n";
    }
    out.close();
}

void inputPatronDetails(vector<Patron> &patron)
{
    string patron_name;
    int id;
    vector<string> name_of_books_borrowed;
    cout << "Enter name of patron" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, patron_name);
    id = rand();
    if (patron.size() == 0)
    {
        Patron patron1(patron_name, id, name_of_books_borrowed);
        patron.push_back(patron1);
    }
    else
    {
        int j = 0;
        for (int i = 0; i < patron.size(); i++)
        {
            if (id == patron[j].patron_id)
            {
                id = rand();
                j = 0;
                i = -1;
            }
            else
            {
                j++;
            }
        }
        if (j == patron.size())
        {
            Patron patron1(patron_name, id, name_of_books_borrowed);
            patron.push_back(patron1);
        }
    }
}

void insertPatrontxt(vector<Patron> &patron)
{
    ofstream out;
    out.open("Patron.txt");
    for (int i = 0; i < patron.size(); i++)
    {
        out << patron[i].name << "\n";
        out << patron[i].patron_id << "\n";
        for (int j = 0; j < patron[i].name_of_books_borrowed.size(); j++)
        {
            out << patron[i].name_of_books_borrowed[j] << ",";
        }
        out << "\n";
    }
    out.close();
}

void readPatrontxt(vector<Patron> &patron)
{
    ifstream in;
    in.open("Patron.txt");
    int i = 0;
    int j = 0;
    int id = 0;
    string s;
    string name;
    vector<string> books;
    while (in.eof() == 0)
    {
        if (i == 3)
        {
            i = 0;
            Patron patron1(name, id, books);
            patron.push_back(patron1);
        }
        switch (i)
        {
        case 0:
            getline(in, name);
            i++;
            break;
        case 1:
            getline(in, s);
            id = stoi(s);
            i++;
            break;
        case 2:
            books.clear();
            getline(in, s);
            if (s != " ")
            {
                for (int k = 0; k <= s.length(); k++)
                {
                    if (s[k] == ',')
                    {
                        books.push_back(s.substr(j, k - j));
                        j = k + 1;
                    }
                }
            }

            i++;
            break;
        }
    }
}

void show_books_borrowed_by(vector<Patron> &patron)
{
    Patron patron1;
    string name;
    cout << "Enter name of patron" << endl;
    cin >> name;
    patron1.display_borrowed_books(name, patron);
}

int main()
{
    vector<Book> book;
    Book book1;
    vector<Patron> patron;
    Patron patron1;
    string book_name;
    string patron_name;
    int i;
    bool x = true;
    int choice;
    book.clear();
    readBooktxt(book);
    patron.clear();
    readPatrontxt(patron);
    do
    {
        cout << "Enter 1 to add books" << endl;
        cout << "Enter 2 to add patrons" << endl;
        cout << "Enter 3 to borrow book" << endl;
        cout << "Enter 4 to return book" << endl;
        cout << "Enter 5 to display books" << endl;
        cout << "Enter 6 to display books borrowed by a particlar patron" << endl;
        cout << "Enter 7 to show patron details" << endl;
        cout << "Enter 8 to search a book" << endl;
        cout << "Enter 9 to show a particular patron details" << endl;
        cout << "Enter 10 to delete Book" << endl;
        cout << "Enter 11 to delete Patron" << endl;
        cout << "Enter 12 to exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            inputBookDetails(book);
            insertBooktxt(book);
            cout << "Book added " << endl;
            cout << endl;
            break;
        case 2:
            inputPatronDetails(patron);
            cout << "Size of patron:" << patron.size() << endl;
            insertPatrontxt(patron);
            cout << "Patron added" << endl;
            cout << endl;
            break;
        case 3:
            cout << "Enter patron name who wants to borrow the book" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, patron_name);
            cout << "Enter book name to be borrowed" << endl;
            getline(cin, book_name);
            patron1.borrow_book(book_name, book, patron, patron_name);
            insertBooktxt(book);
            insertPatrontxt(patron);
            cout << endl;
            break;
        case 4:
            cout << "Enter patron name who wants to return the book" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, patron_name);
            cout << "Enter book name to be returned" << endl;
            getline(cin, book_name);
            patron1.return_borrowed_books(book_name, book, patron, patron_name);
            insertBooktxt(book);
            insertPatrontxt(patron);
            cout << endl;
            break;
        case 5:
            book.clear();
            readBooktxt(book);
            book1.DisplayBookDetails(book);
            cout << endl;
            break;
        case 6:
            show_books_borrowed_by(patron);
            cout << endl;
            break;
        case 7:
            patron1.displayPatrondetails(patron);
            cout << endl;
            break;
        case 8:
            cout << "Enter name of book to search" << endl;
            cin >> book_name;
            book1.SearchBook(book_name, book);
            cout << endl;
            break;
        case 9:
            cout << "Enter patron name" << endl;
            cin >> patron_name;
            patron1.showSearchPatron(patron_name, patron);
            cout << endl;
            break;
        case 10:
            cout << "Enter name of book to delete" << endl;
            cin >> book_name;
            book1.DeleteBook(book_name, book);
            insertBooktxt(book);
            break;
        case 11:
            cout << "Enter name" << endl;
            cin >> patron_name;
            patron1.deletePatron(patron, patron_name, book);
            insertPatrontxt(patron);
            cout << endl;
            break;
        case 12:
            x = false;
            break;
        }
    } while (x);
    return 0;
}