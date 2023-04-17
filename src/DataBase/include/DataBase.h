#pragma once

#include <iostream>
#include <map>
#include <sqlite3.h>
#include <string>

struct Book
{
    std::string bookPath;
    std::string bookName;
    std::string bookAuthorName;
    int bookYear{};
    int lastPage{};
    Book() = default;
    Book(std::string path, std::string bName, std::string aName, int year, int lPage)
        : bookPath(path), bookName(bName), bookAuthorName(aName), bookYear(year), lastPage(lPage)
    {
    }
    void print()
    {
        std::cout << bookPath << " " << bookName << " " << bookAuthorName << " " << bookYear << " " << lastPage
                  << " \n";
    }
};

class BookDB
{

  public:
    BookDB(const std::string &dbFilePath);
    Book getBookById(int bookId);
    std::map<int, Book> *getBooksList();
    int addBookToDatabase(Book curBook);
    void changeLastePage(int, int);
    ~BookDB();

  private:
    void createTable(const std::string &dbFilePath);
    void executeInsertQuery(int randomId, Book curBook);
    int generateUniqueId();
    int generateRandomId();
    bool idExists(int id);
  
  private:
    std::string bookDBTable;
    sqlite3 *DB;
    char *messaggeError;
    int exit = 0;
    sqlite3_stmt *stmt;
};