#include "bookDB.h"

int bookDB::ID = 0; 

bookDB::bookDB() {
    bookDBTable = "CREATE TABLE IF NOT EXISTS BOOKS("
                  "ID INT PRIMARY KEY     NOT NULL, "
                  "BOOKPATH           TEXT    NOT NULL, "
                  "BOOKNAME          TEXT     NOT NULL, "
                  "AUTHORNAME          TEXT     NOT NULL, "
                  "YEAR            INT     NOT NULL, "
                  "LASTPAGE            INT);";
    exit = sqlite3_open("bookdb.db", &DB);
    exit = sqlite3_exec(DB, bookDBTable.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Create Table: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;

    sqlite3_stmt* stmt;
    bookDBTable = "SELECT COUNT(*) FROM BOOKS;";

    int result = sqlite3_prepare_v2(DB, bookDBTable.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            bookDB::ID = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
}

void bookDB::addBook(book curBook)
{
    bookDBTable = "INSERT INTO BOOKS VALUES (" +
                              std::to_string(ID) + ", '" + curBook.bookPath + "', '" + curBook.bookName + "', '" +
                              curBook.bookAuthorName + "', " + std::to_string(curBook.bookYear) + ", " +
                              std::to_string(curBook.lastPage) + ");";
    std::cout << bookDBTable << std::endl;
    exit = sqlite3_exec(DB, bookDBTable.c_str(), NULL, 0, &messaggeError);
    bookDB::ID++;
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << sqlite3_errmsg(DB) << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;
}

std::map<int, book>* bookDB::getData() { 
    std::map<int, book>* bookList = new std::map<int, book>();
    bookDBTable = "SELECT * FROM BOOKS";
    exit = sqlite3_prepare_v2(DB, bookDBTable.c_str(), -1, &stmt, NULL);
    if (exit != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* bookPath = (const char*)sqlite3_column_text(stmt, 1);
        const char* bookName = (const char*)sqlite3_column_text(stmt, 2);
        const char* authorName = (const char*)sqlite3_column_text(stmt, 3);
        int year = sqlite3_column_double(stmt, 4);
        int lastPage = sqlite3_column_double(stmt, 5);
        book tmp(bookPath, bookName, authorName, year, lastPage);
        bookList->insert(std::make_pair(id,tmp));
    }
    if (exit != SQLITE_DONE) {
        std::cerr << "Error retrieving data: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);
    return bookList;
}

void bookDB::changeLastePage(int id, int newPage) {
    bookDBTable = "UPDATE BOOKS SET LASTPAGE = ? WHERE id = ?";

    exit = sqlite3_prepare_v2(DB, bookDBTable.c_str(), -1, &stmt, NULL);

    if (exit != SQLITE_OK) {
        std::cout << "Failed to prepare statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    sqlite3_bind_int(stmt, 1, newPage);
    sqlite3_bind_int(stmt, 2, id);

    exit = sqlite3_step(stmt);

    if (exit != SQLITE_DONE) {
        std::cout << "Failed to execute statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    sqlite3_finalize(stmt);
}

bookDB::~bookDB() {
    sqlite3_close(DB);
}