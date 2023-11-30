#include <iostream>
#include <list>
#include <algorithm>
#include <string>
using namespace std;


const int str_size = 100;
struct Book
{
    char author[str_size];
    char name[str_size];
    int year;
    bool avaliable;
    Book(const char* author, const char* name, const int& year) : year{ year }, avaliable{true} {
        strcpy_s(this->author,author);
        strcpy_s(this->name, name);
    }
    void given() {
        if (avaliable) {
            avaliable = false;
        }
        else cout << "This book has already been given" << endl;
    }
    void returnb() {
        if (!avaliable) {
            avaliable = true;
        }
    }
    void print() {
        cout << "Author: " << author << ", Name: " << name << ", Year: " << year << ", Avaliable: " << boolalpha << avaliable << endl;
    }
};

ostream& operator<<(ostream& os, const Book& b) {
    os << "Author: " << b.author << ", Name: " << b.name << ", Year: " << b.year << ", Avaliable: " << boolalpha << b.avaliable;
    return os;
}

class Library
{
public:
    Library() = default;
    ~Library() {
    };

    void add(Book b) {
        lib.push_back(b);
    }
    void print() const {
        ostream_iterator<Book> outIt(cout, "\n");
	    copy(lib.begin(), lib.end(), outIt);
        cout << endl;
    }
    int findByName(const char* name) {
        auto p = find_if(lib.begin(), lib.end(), [name](const Book& b) {return strcmp(b.name, name) == 0; });
        if (p != lib.end()) {
            return distance(lib.begin(), p);
        }
        return -1;
    }
    int findByAuthor(const char* author) {
        auto p = find_if(lib.begin(), lib.end(), [author](const Book& b) {return strcmp(b.author, author) == 0; });
        if (p != lib.end()) {
            return distance(lib.begin(), p);
        }
        return -1;
    }
    void give(const int& index) {
        if (index < 0 || index >= lib.size()) {
            cout << "Index out of bounds" << endl;
            return;
        }
        list<Book>::iterator it = lib.begin();
        advance(it, index);

        if (it != lib.end()) {
            it->given();
            it->print();
        }
        else cout << "Book not found" << endl;
    }
    void return_book(const int& index) {
        if (index < 0 || index >= lib.size()) {
            cout << "Index out of bounds" << endl;
            return;
        }
        list<Book>::iterator it = lib.begin();
        advance(it, index);

        if (it != lib.end()) {
            it->returnb();
            it->print();
        }
        else cout << "Book not found" << endl;
    }
    void sort() {
        lib.sort([](const Book& a, const Book& b) {
            return strcmp(a.author, b.author) < 0;
        });
        lib.sort([](const Book& a, const Book& b) {
            return strcmp(a.name, b.name) < 0;
            });
    }

    void remove(const char* author, const char* name, const int& year) {
        lib.remove_if([=](const Book& b) {return strcmp(b.name, name) == 0 && strcmp(b.author, author) == 0 && b.year == year; });
    }
    void remove(const int& index) {
        if (index < 0 || index >= lib.size()) {
            cout << "Index out of bounds" << endl;
            return;
        }
        list<Book>::iterator it = lib.begin();
        advance(it, index);

        if (it != lib.end()) {
            remove(it->author, it->name, it->year);
        }
        else cout << "Book not found" << endl;
    }
    void edit(const int& index, const char* name, const char* author, const int& year){
        if (index < 0 || index >= lib.size()) {
            cout << "Index out of bounds" << endl;
            return;
        }
        list<Book>::iterator it = lib.begin();
        advance(it, index);

        if (it != lib.end()) {
            strcpy_s(it->name, name);
            strcpy_s(it->author, author);
            it->year = year;
        }
        else cout << "Book not found" << endl;
    }


private:
    list<Book> lib;
};




int main()
{
    Book b("Leo Tolstoy", "War and Peace", 1869);
    //cout << b << endl;

    Library lib;
    lib.add({ "J.K. Rowling", "Harry Potter and the Philosopher's Stone", 1997 });
    lib.add({ "J.R.R. Tolkien", "The Lord of the Rings", 1954 });
    lib.add(b);
    lib.add({ "F. Scott Fitzgerald", "The Great Gatsby", 1925 });
    lib.print();

    int index = lib.findByAuthor("J.R.R. Tolkien");
    lib.give(index);
    lib.return_book(index);
    lib.remove(index);
    cout << endl;
    lib.print();
    lib.edit(1, "The Lord of the Rings", "J.R.R. Tolkien", 1954);
    lib.print();

    //Book b("Leo Tolstoy", "War and Peace", 1869);
    //cout << b << endl;
    

}
