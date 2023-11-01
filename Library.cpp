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
    cout << "Title    : " << Item -> Title << endl
         << "  Author : " << Item -> Author << endl
         << "  ISBN   : " << Item -> isbn << endl
         << "  Year   : " << Item -> year << endl
         << "  Pages  : " << Item -> pages << endl
         << "  Price  : $" << Item -> price << endl
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
    /* So Basically, how this next functions work boggles my mind, but it works. Basically:
     *  The Loop Function creates two Book* items. These items are such that Doubletail is set equal to Tail
     *  before Tail is updated (So Doubletail always equals the entry immedietely prior to Tail). The loop stops
     *  if it finds the right place to put the new item, or if tail reaches the end. In which case:
     *
     *  If the new entry is head, that's easy. We just set the new entry to the new head, and have it point to
     *  the old head.
     *
     *  If the new entry is somewhere in the list, that's where we use Doubletail to reroute the previous
     *  item into the New Entry, and set the new entry's next to Tail.
     *
     *  If it reaches the end of the list, first it will check to see if the end of the list is in the right
     *  spot (in which case, the previous function is called). If not, it creates a new entry on the end
     *  of the list.
     *
     *  I (Jesse) had worries of if the function failed, so the final case is if that happens.
     */
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

    while (cursor != NULL) //This loop ensures that, if the same author printed multiple works, all works by that author will be shown.
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

void Library::find_album (string Title) //This whole function is a copy-paste of find_author().
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
    while (file)    //while infile, it will store the items in temporary variables, and then send them to addentry()
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
    Book* cursor = head;

    file.open(flnm);
    while (cursor != NULL)
    {
        file << cursor -> Title << endl;
        file << cursor -> Author << endl;
        file << cursor -> pages << " ";
        file << cursor -> isbn << " ";
        file << cursor -> price << " ";
        file << cursor -> year << endl;
	
        cursor = cursor -> next;
    }

    file.close();

    return;
}
