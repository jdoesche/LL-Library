#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "Library.h"

//Constuctor
Library::Library()
{ head = NULL; }

//Destructor
Library::~Library()
{
    while (head != NULL)
    {
        deleteentry(head -> Author, head -> Title);
    }
}

void Library::printentry(Book* Item)
{
    cout << "Title     : " << Item -> Title << endl
         << "  Author  : " << Item -> Author << endl
         << "  ISBN    : " << Item -> isbn << endl
         << "  Year    : " << Item -> year << endl
         << "   Pages  : " << Item -> pages << endl
         << "   Price  : $" << Item -> price << endl
         << endl;
}

//add a new entry
void Library::addentry(string Title, string Author, int pages,
                       string isbn, float price, int year)
{
    Book* NEWENTRY = new Book;
    NEWENTRY -> next = NULL;
    NEWENTRY -> Title = Title;
    NEWENTRY -> Author = Author;
    NEWENTRY -> pages = pages;
    NEWENTRY -> isbn = isbn;
    NEWENTRY -> price = price;
    NEWENTRY -> year = year;

    //Case 1: Empty List
    if (head == NULL)
    {
        head = NEWENTRY;
        return;
    }
    //Case 2: Not Empty List (Add Sorted)
    Book* tail = head;
    Book* doubletail = head;
    bool ishead = true;
    while (tail -> next != NULL && NEWENTRY -> Author <= tail -> Author)
    {
        doubletail = tail;
        tail = tail -> next;
        ishead = false;
    }
    //Case 2a: Head
    if (ishead == true)
    {
        NEWENTRY -> next = head;
        head = NEWENTRY;
        return;
    }
    //Case 2b: Tail is in the list
    if(NEWENTRY -> Author > tail -> Author)
    {
        NEWENTRY -> next = tail -> next;
        doubletail -> next = NEWENTRY;
        return;
    }
    //Case 2c: Tail == NULL
    if (tail -> next == NULL)
    {
        tail -> next = NEWENTRY;
        return;
    }
    //Case 2d: Panic
    cout << "Error - Undefined entry, returning" << endl;
    return;

    //I'm not gonna sit here and pretend like I undersatnd this
    //  I really dont... I'm just gonna hope it works...
    //  OOOH We're half-way there. OH-OH! LIVING ON A PRAYER!
}

//delete an existing entry
void Library::deleteentry(string Author, string Title)
{
    //compared to the Hell that was the last one, this will
    //be a cakewalk

    Book* temp;
    Book* eraser;

    //Case 1: Empty List
    if (head == NULL)
        return;

    //Case 2: Delete the Head
    if (head -> Author == Author && head -> Title == Title)
    {
        eraser = head;
        head = head -> next;
        delete eraser;
        return;
    }

    //Case 3: Search & Destroy
    temp = head;
    while (temp -> next != NULL && (temp -> next -> Author != Author ||
           temp -> next -> Title != Title))
    {
        temp = temp -> next;
    }
    //Case 3a: No matches
    if (temp -> next == NULL)
    {
        cout << "Item requested does not exist. Please try again." << endl;
        return;
    }
    //Case 3b: Match!
    eraser = temp -> next;
    temp -> next = eraser -> next;
    delete eraser;
    return;
}

void Library::print()
{
    //Finally, an actually "Easy" one;
    Book* cursor;
    cursor = head;

    while (cursor != NULL)
    {
        printentry(cursor);
        cursor = cursor -> next;
    }
    return;
}

void Library::find_author (string Author)
{
    Book* cursor = head;
    int counter = 0;

    while (cursor != NULL)
    {
        if (cursor -> Author == Author)
        {
            printentry(cursor);
            counter++;
        }
        cursor = cursor -> next;
    }
    cout << "Found " << counter << " matching entries." << endl;
    if (counter == 0)
        cout << "Are you sure you typed it right?" << endl << endl;
    return;
}

void Library::find_album (string Title)
{
    Book* cursor = head;
    int counter = 0;

    while (cursor != NULL)
    {
        if (cursor -> Title == Title)
        {
            printentry(cursor);
            counter++;
        }
        cursor = cursor -> next;
    }
    cout << "Found " << counter << " matching entries." << endl;
    if (counter == 0)
        cout << "Are you sure you typed it right?" << endl << endl;
    return;
}

void Library::readfromfile(string flnm)
{
    ifstream file;

    string junk;
    string Title;
    string Author;
    int pages;
    string isbn;
    float price;
    int year;

    file.open(flnm);
    while (file)
    {
        getline(file,Title);
        getline(file,Author);
        file >> pages;
        file >> isbn;
        file >> price;
        file >> year;

        addentry(Title, Author, pages, isbn, price, year);
        getline(file, junk);
    }
    file.close();

    return;
}

void Library::writetofile(string flnm)
{
    ofstream file;
    Book* cursor;

    file.open(flnm);
    while (cursor != NULL)
    {
        file << cursor -> Title;
        file << cursor -> Author;
        file << cursor -> pages << " ";
        file << cursor -> isbn << " ";
        file << cursor -> price << " ";
        file << cursor -> year << endl;
        cursor = cursor -> next;
    }
}