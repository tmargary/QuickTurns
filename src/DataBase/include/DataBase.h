#pragma once

#include <iostream>
#include <map>
#include <sqlite3.h>
#include <string>
#include "BookMetadata.h"


class BookDB
{

  public:
    BookDB(const std::string &dbFilePath);
    Book getBookById(int bookId);
    std::map<int, Book> *getBooksList();
    int addBookToDatabase(const Book& curBook);
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