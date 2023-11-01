//Names: Jesse Doescher & Jace Riley
#include <iostream>
using namespace std;
#include <string>
#include "Library.h"

void mainloop();
void easyop();

int main() //initializer function
{

  cout << "Welcome to the Library Catalog!" << endl;
  
  mainloop();
  
  cout << "Thank you for using the Library Catalog" << endl;
  return 0;
}

void easyop() //helper function to automatically cout the options menu
{
  cout << "You can:" << endl
       << "  (P)rint the current Catalog" << endl
       << "  (R)ead a Catalog in from file" << endl
       << "  (W)rite the current Catalog to file" << endl
       << "  (A)dd a new entry" << endl
       << "  (D)elete an existing entry" << endl
       << "  (S)earch for an entry" << endl
       << "  (?)  Bring up this menu again" << endl
       << "  (X)  Quit the Program (Also works with Q)" << endl
       << endl;
}

void mainloop()
{
  //definitions
  Library a;
  int i = 0;
  char operation;
  string holdinput;
  string junk;

  easyop();
  while (true)
  {
    //user inserts their operations
    cout << "Please enter your desired action: ";
    cin >> operation;

    switch (operation)
    {
      case '?': //What where the optnios again?
      {
        easyop();
        break;
      }
      case 'Q':
      case 'X': //Exit the program
      {

        cout << "Are you sure you wish to quit? Any unsaved changes will be disgarded."
             << endl << "  (Y to confirm, else to return): " << endl;
        cin >> operation;
        if (operation == 'Y' || operation == 'y')
          return;
        break;
      }
      case 'P': //Print the current list
      {
        a.print();
        break;
      }
      case 'S': //Search
      {
        cout << "Do you wish to search by Author (1) or by Album (2)? ";
        cin >> operation;
        cout << endl;
        getline(cin, junk);
        if (operation == '1') //search by author
        {
          cout << "Please enter the author you wish to search:" << endl;
          getline(cin, holdinput);
          cout << endl;
          a.find_author(holdinput);
          break;
        }
        if (operation == '2') //search by album
        {
          cout << "Please enter the Title you wish to search:" << endl;
          getline(cin, holdinput);
          cout << endl;
          a.find_album(holdinput);
          break;
        }
	//in case they user inputs else
        cout << "\"" << operation << "\" is not defined. Please try again.";
        break;
      }
      case 'R': //Read from File
      {
        cout << "Please enter the name of the file you wish to read: ";
        cin >> holdinput;
        a.readfromfile(holdinput);
        break;
      }
      case 'W': //Write to File
      {
        cout << "Please enter the name of the file you wish to write: ";
        cin >> holdinput;
        a.writetofile(holdinput);
        break;
      }
      case 'A': //Add a new entry
      {
        string Title;
        string Author;
        string isbn;
        int pages;
        float price;
        int year;

	//get info, it's a mess
        getline(cin, junk);
        cout << "Please enter the following information: " << endl
             << "The name of the book (Getline): " << endl;
        getline (cin, Title);
        cout << endl << "The author of the book (Getline): " << endl;
        getline (cin, Author);
        cout << endl << "The number of pages (int): ";
        cin >> pages;
        cout << endl << "The ISBN (string): ";
        cin >> isbn;
        cout << endl << "The cover price (float): ";
        cin >> price;
        cout << endl << "The publication year (int): ";
        cin >> year;
        cout << endl << endl;

	//the actually fun part
        a.addentry(Title, Author, pages, isbn, price, year);
        break;
      }
      case 'D': //Delete an existing entry
      {
        string Title;
        string Author;

        getline (cin, junk);
        cout << "Please enter the following information:" << endl;
        cout << "The Title of the book: " << endl;
        getline(cin, Title);
        cout << endl << "The Author of the book: " << endl;
        getline(cin, Author);
        cout << endl << endl;

        a.deleteentry(Author, Title);
        break;
      }
      default:
      {
        cout << "Operation \"" << operation << "\" not recognized. Please try again." << endl;
      }
    }
    cout << "Done. ------------ [ " << i << " ]" << endl;
    i++;
  }
}
