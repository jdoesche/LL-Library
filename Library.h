#ifndef LIBRARY_H
#define LIBRARY_H


#include <iostream>
using namespace std;
#include <string>

struct Book
{
    Book* next;
    string Title;
    string Author;
    int pages;
    string isbn;
    float price;
    int year;
};

class Library
{
 private:
    void printentry(Book* Item);
    int Libsize;
    Book* head;

 public:
    //Constructor/Destructor
    Library();
    ~Library();

    //fstream
    void readfromfile(string flnm);
    void writetofile(string flnm);

    //Add/Remove
    void addentry(string Title, string Author, int pages,
                  string isbn, float price, int year);
    void deleteentry(string Author, string Book);
    
    //Search
    void find_author(string Author);
    void find_album(string Title);

    //Print
    void print();
};
#endif //LIBRARY_H