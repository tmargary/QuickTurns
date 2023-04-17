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
  private:
    std::string bookDBTable;
    sqlite3 *DB;
    char *messaggeError;
    int exit = 0;
    sqlite3_stmt *stmt;

  public:
    BookDB(const std::string &dbFilePath);
    Book getBookById(int bookId);
    std::map<int, Book> *getBooksList();
    int addBookToDatabase(Book curBook);
    ~BookDB();

  private:
    void createTable(const std::string &dbFilePath);
    void executeInsertQuery(int randomId, Book curBook);
    int generateUniqueId();
    void changeLastePage(int, int);
    int generateRandomId();
    bool idExists(int id);
};