#include <iostream>
#include <string>
#include <fstream>
#include "mysql/mysql.h"

using namespace std;

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *server = "127.0.0.1";
char *user = "root";
char *password = "";
char *database = "librarymanagement";
char query[1000];
int t,r;

class book
{
    public:
    string title;
    string author;
    string publisher;
    int year;
    string isbn;
    book* next;
    book(string, string, string, int, string, book*);
};

book::book(string tempTitle, string tempAuthor, string tempPublisher, int tempYear, string tempIsbn, book* tempNext)
{
    title=tempTitle;
    author=tempAuthor;
    publisher=tempPublisher;
    year=tempYear;
    isbn=tempIsbn;
    next=tempNext;
}

typedef book* bookPtr;

void getline(istream &stream, string &str, char delimiter)
{    char temp[500];

    stream.get(temp, 500, delimiter);
    stream.ignore(500, delimiter);
    str = temp;
}

void getline(istream &stream, int &num, char delimiter)
{    int temp;

    stream >> temp;
    stream.ignore(500, delimiter);
    num= temp;
}

void readFile(bookPtr &root);
void insert (bookPtr &root);
void delTitle(bookPtr &root);
bookPtr locateNode(bookPtr temp, string titl);
void delIsbn(bookPtr &root);
bookPtr locateNodeIsbn(bookPtr temp, string isb);
void searchIsbn(bookPtr temp);
void printList(bookPtr temp);
void printAuthor(bookPtr temp);
void saveFile(bookPtr temp);
int countNodes(bookPtr temp);


void readFile(bookPtr &root)
{
    // retrieve data from books table in mysql database
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
    if (conn)
    {
        cout << "Connected to database" << endl;
    }
    else
    {
        cout << "Connection failed" << endl;
    }
    sprintf(query, "SELECT * FROM books");
    t = mysql_query(conn, query);
    res = mysql_use_result(conn);
    if (res)
    {
        cout << "Result set created" << endl;
    }
    else
    {
        cout << "Result set failed" << endl;
    }
    // display data in a table like format
    cout << "Title" << "\t" << "Author" << "\t" << "Publisher" << "\t" << "Year" << "\t" << "ISBN" << endl;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl;
        root = new book(row[0], row[1], row[2], atoi(row[3]), row[4], root);
    }

}

void insert (bookPtr &root)
{
    string titl, aut, pub, isb;
    int yea;

    cout << "Title:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, titl, '\n');
    cout << "Author:\t\t\t";
    getline(cin, aut, '\n');
    cout << "Publisher:\t\t";
    getline(cin,pub, '\n');
    cout << "Year:\t\t\t";
    getline(cin,yea, '\n');
    cout << "ISBN:\t\t\t";
    getline(cin, isb, '\n');

    root = new book (titl, aut, pub, yea, isb, root);
}

void delTitle()
{
    // delete row from books table in mysql database using name of book
    string titl;
    cout << "Enter title of book to delete: ";
    cin.ignore(500,'\n');
    getline(cin, titl, '\n');
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
    if (conn)
    {
        cout << "Connected to database" << endl;
    }
    else
    {
        cout << "Connection failed" << endl;
    }
    sprintf(query, "DELETE FROM books WHERE title='%s'", titl.c_str());
int t = mysql_query(conn, query);


    if (t == 0)
    {
        cout << "Book deleted" << endl;
    }
    else
    {
        cout << "Book not deleted" << endl;
    }

}

bookPtr locateNode(bookPtr temp, string titl)
{
    while (temp != NULL)
    {
        if (temp->title == titl)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void delIsbn()
{
    // delete row from books table in mysql database using isbn
    string isb;
    cout << "Enter isbn of book to delete: ";
    cin.ignore(500,'\n');
    getline(cin, isb, '\n');
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
    if (conn)
    {
        cout << "Connected to database" << endl;
    }
    else
    {
        cout << "Connection failed" << endl;
    }
    sprintf(query, "DELETE FROM books WHERE isbn='%s'", isb.c_str());
    t = mysql_query(conn, query);

    if (t == 0)
    {
        cout << "Book deleted" << endl;
    }
    else
    {
        cout << "Book not deleted" << endl;
    }
}

bookPtr locateNodeIsbn(bookPtr temp, string isb)
{
    while (temp != NULL)
    {
        if (temp->isbn == isb)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void searchIsbn()
{
    // search for book using isbn
    string isb;
    cout << "Enter isbn of book to search: ";
    cin.ignore(500,'\n');
    getline(cin, isb, '\n');
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
    if (conn)
    {
        cout << "Connected to database" << endl;
    }
    else
    {
        cout << "Connection failed" << endl;
    }
    sprintf(query, "SELECT * FROM books WHERE isbn='%s'", isb.c_str());
    t = mysql_query(conn, query);
    res = mysql_use_result(conn);
    if (res)
    {
        cout << "Result set created" << endl;
    }
    else
    {
        cout << "Result set failed" << endl;
    }
    // display data in a table like format
    cout << "Title" << "\t" << "Author" << "\t" << "Publisher" << "\t" << "Year" << "\t" << "ISBN" << endl;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl;
    }
}



void printAuthor()
{
    //
    string authorname;
    cout << "Author Name:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, authorname, '\n');
    // retrieve name of all the books having author authorname from books table in mysql database
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
    if (conn)
    {
        cout << "Connected to database" << endl;
    }
    else
    {
        cout << "Connection failed" << endl;
    }
    sprintf(query, "SELECT * FROM books WHERE author = '%s'", authorname.c_str());
    int t = mysql_query(conn, query);
    res = mysql_use_result(conn);
    

cout << "Title" << "\t" << "Author" << "\t" << "Publisher" << "\t" << "Year" << "\t" << "ISBN" << endl;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl;
    }



}

void saveFile(bookPtr temp)
{
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
        cout<<"Error connecting to database: "<<mysql_error(conn)<<endl;
    }
    cout<<"Connected to database"<<endl;
    
    while(temp != NULL)
    {
        // Inserting data into the table as strings
        string title = temp->title;
        string author = temp->author;
        string publisher = temp->publisher;
        string year = to_string(temp->year);
        string isbn = temp->isbn;

        string query="INSERT INTO books (title, author, publisher, year, isbn) VALUES ('"+title+"', '"+author+"', '"+publisher+"', '"+year+"', '"+isbn+"');";
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);
        if(!qstate){
            cout<<"Query executed successfully"<<endl;
        }
        else{
            cout<<"Query execution failed: "<<mysql_error(conn)<<endl;
        }
        temp = temp->next;
    }
}

int countNodes(bookPtr temp)
{
    int countB = 0;
    while (temp != NULL)
    {
        countB++;
        temp = temp->next;
    }
    return countB;
}
int main()
{
    
    int choice;
    bookPtr root = NULL;
    readFile(root);

    do
    {
        cout << "\t\t<<=========================>>";
        cout << "\n\t\t>>LIBRARY MANAGEMENT SYSTEM<<";
        cout << "\n\t\t<<=========================>>";
        cout << "\n\nMenu: Select your option\n\n";
        cout << "(1) Add a book to the list\n";
        cout << "(2) Delete a book based on Title\n";
        cout << "(3) Delete a book based on ISBN\n";
        cout << "(4) Search for a book by ISBN.\n";
        cout << "(5) List all books.\n";
        cout << "(6) List all books by an author.\n";
        cout << "(7) Quit.\n\n";
        cout << "Enter your choice ---> ";

        cin >> choice;

        if (1 <= choice && choice <= 6)
        {
            switch (choice)
            {
            case 1:
                insert(root);
                break;
            case 2:
                delTitle();
                break;
            case 3:
                delIsbn();
                break;
            case 4:
                searchIsbn(root);
                break;
            case 5:
                readFile(root);
                break;
            case 6:
                printAuthor();
                break;
            default:
                cout << "Invalid choice.  Enter again.\n\n";
                break;
            }
        }
    }
    while (choice != 7);
    saveFile(root);
    return 0;
}