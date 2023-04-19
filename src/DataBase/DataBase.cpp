#include "DataBase.h"
#include <QRandomGenerator>

// Global variables for column indices
const int BOOK_PATH_COL = 1;
const int BOOK_NAME_COL = 2;
const int AUTHOR_NAME_COL = 3;
const int AUTHOR_FILE_AS_COL = 4;
const int CONTRIBUTOR_COL = 5;
const int PUBLISHER_COL = 6;
const int UUID_COL = 7;
const int DATE_COL = 8;
const int RIGHTS_COL = 9;
const int LANGUAGE_COL = 10;
const int ISBN_COL = 11;
const int LAST_PAGE_COL = 12;

int BookDB::generateRandomId()
{
    const int randomId = QRandomGenerator::global()->bounded(1, 1000001);
    return randomId;
}

BookDB::BookDB(const std::string &dbFilePath)
{
    createTable(dbFilePath);
}

void BookDB::createTable(const std::string &dbFilePath)
{
    bookDBTable = "CREATE TABLE IF NOT EXISTS BOOKS("
                  "ID INT PRIMARY KEY NOT NULL, "
                  "BOOKPATH     TEXT    NOT NULL, "
                  "TITLE        TEXT, "
                  "AUTHOR       TEXT, "
                  "AUTHOR_FILE_AS TEXT, "
                  "CONTRIBUTOR  TEXT, "
                  "PUBLISHER    TEXT, "
                  "UUID         TEXT, "
                  "DATE         TEXT, "
                  "RIGHTS       TEXT, "
                  "LANGUAGE     TEXT, "
                  "ISBN         TEXT, "
                  "LASTPAGE     INT             );";
    exit = sqlite3_open(dbFilePath.c_str(), &DB);
    exit = sqlite3_exec(DB, bookDBTable.c_str(), nullptr, nullptr, &messaggeError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Create Table: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_free(messaggeError);
    }
    else
    {
        std::cout << "Table created Successfully" << std::endl;
    }
}

int BookDB::addBookToDatabase(const Book &curBook)
{
    int randomId = generateUniqueId();

    executeInsertQuery(randomId, curBook);
    return randomId;
}

void BookDB::executeInsertQuery(int randomId, Book curBook)
{
    Book::Builder builder;

    // Set the fields of the book using the builder's setter methods
    builder.setBookPath(curBook.bookPath)
        .setId(randomId)
        .setTitle(curBook.title)
        .setAuthor(curBook.author)
        .setAuthorFileAs(curBook.author_file_as)
        .setContributor(curBook.contributor)
        .setPublisher(curBook.publisher)
        .setUuid(curBook.uuid)
        .setDate(curBook.date)
        .setRights(curBook.rights)
        .setLanguage(curBook.language)
        .setIsbn(curBook.isbn)
        .setLastPage(curBook.lastPage);

    // Build the Book object
    const Book book = builder.build();

    // Construct the INSERT query
    bookDBTable = "INSERT INTO BOOKS (ID, BOOKPATH, TITLE, AUTHOR, AUTHOR_FILE_AS, CONTRIBUTOR, PUBLISHER, UUID, DATE, "
                  "RIGHTS, LANGUAGE, ISBN, LASTPAGE) "
                  "VALUES (" +
                  std::to_string(book.id) + ", '" + book.bookPath + "', '" + book.title.value_or("") + "', '" +
                  book.author.value_or("") + "', '" + book.author_file_as.value_or("") + "', '" +
                  book.contributor.value_or("") + "', '" + book.publisher.value_or("") + "', '" +
                  book.uuid.value_or("") + "', '" + book.date.value_or("") + "', '" + book.rights.value_or("") +
                  "', '" + book.language.value_or("") + "', '" + book.isbn.value_or("") + "', " +
                  std::to_string(book.lastPage) + ");";

    // Execute the INSERT query
    exit = sqlite3_exec(DB, bookDBTable.c_str(), nullptr, nullptr, &messaggeError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Insert" << sqlite3_errmsg(DB) << std::endl;
        sqlite3_free(messaggeError);
    }
    else
    {
        std::cout << "Records created Successfully!" << std::endl;
    }
}

int BookDB::generateUniqueId()
{
    int randomId = generateRandomId();

    while (idExists(randomId))
    {
        randomId = generateRandomId();
    }

    return randomId;
}

bool BookDB::idExists(int bookId)
{
    bool exists = false;
    const char *query = "SELECT id FROM BOOKS WHERE id = ?";
    exit = sqlite3_prepare_v2(DB, query, -1, &stmt, NULL);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return exists;
    }

    sqlite3_bind_int(stmt, BOOK_PATH_COL, bookId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        exists = true;
    }

    sqlite3_finalize(stmt);
    return exists;
}

std::map<int, Book> *BookDB::getBooksList()
{
    std::map<int, Book> *bookList = new std::map<int, Book>();
    bookDBTable = "SELECT * FROM BOOKS";
    exit = sqlite3_prepare_v2(DB, bookDBTable.c_str(), -1, &stmt, NULL);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const char *bookPath = (const char *)sqlite3_column_text(stmt, BOOK_PATH_COL);
        const char *bookName = (const char *)sqlite3_column_text(stmt, BOOK_NAME_COL);
        const char *authorName = (const char *)sqlite3_column_text(stmt, AUTHOR_NAME_COL);
        const char *year = (const char *)sqlite3_column_text(stmt, DATE_COL);
        int lastPage = static_cast<int>(sqlite3_column_double(stmt, CONTRIBUTOR_COL));

        Book tmp = Book::create()
                       .setId(id)
                       .setBookPath(bookPath)
                       .setTitle(bookName)
                       .setAuthor(authorName)
                       .setDate(year)
                       .setLastPage(lastPage)
                       // Add more setters for the remaining fields
                       .build();

        bookList->insert(std::make_pair(id, tmp));
    }
    if (exit != SQLITE_DONE)
    {
        std::cerr << "Error retrieving data: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);
    return bookList;
}

bool BookDB::bookExists(const Book &bookToCheck)
{
    // Use the getBooksList() function to fetch the books
    std::map<int, Book> *existingBooks = getBooksList();

    for (const auto &[id, existingBook] : *existingBooks)
    {
        // Modify the condition based on your metadata comparison criteria
        if (bookToCheck.title == existingBook.title && bookToCheck.author == existingBook.author)
        {
            return true;
        }
    }
    return false;
}

void BookDB::changeLastePage(int bookid, int newPage)
{
    bookDBTable = "UPDATE BOOKS SET LASTPAGE = ? WHERE id = ?";

    exit = sqlite3_prepare_v2(DB, bookDBTable.c_str(), -1, &stmt, NULL);

    if (exit != SQLITE_OK)
    {
        std::cout << "Failed to prepare statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    sqlite3_bind_int(stmt, BOOK_PATH_COL, newPage);
    sqlite3_bind_int(stmt, BOOK_NAME_COL, bookid);

    exit = sqlite3_step(stmt);

    if (exit != SQLITE_DONE)
    {
        std::cout << "Failed to execute statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    sqlite3_finalize(stmt);
}

Book BookDB::getBookById(int bookId)
{
    Book::Builder builder;
    const char *query = "SELECT * FROM BOOKS WHERE id = ?";
    exit = sqlite3_prepare_v2(DB, query, -1, &stmt, NULL);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return builder.build();
    }

    sqlite3_bind_int(stmt, BOOK_PATH_COL, bookId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *bookPath = (const char *)sqlite3_column_text(stmt, BOOK_PATH_COL);
        const char *bookName = (const char *)sqlite3_column_text(stmt, BOOK_NAME_COL);
        const char *authorName = (const char *)sqlite3_column_text(stmt, AUTHOR_NAME_COL);
        const char *year = (const char *)sqlite3_column_text(stmt, AUTHOR_FILE_AS_COL);
        int lastPage = sqlite3_column_double(stmt, CONTRIBUTOR_COL);

        builder.setBookPath(bookPath)
            .setBookPath(bookPath)
            .setTitle(bookName)
            .setAuthor(authorName)
            .setDate(year)
            .setLastPage(lastPage);
        // Add more setters for the remaining fields
    }
    else
    {
        std::cerr << "Error retrieving data: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);
    return builder.build();
}

void BookDB::removeBook(int bookId)
{
    const char *query = "DELETE FROM BOOKS WHERE ID = ?";
    exit = sqlite3_prepare_v2(DB, query, -1, &stmt, NULL);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    sqlite3_bind_int(stmt, BOOK_PATH_COL, bookId);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Error deleting data: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);

    std::cout << "BookId" << bookId << "is removed.\n";
}

Book BookDB::getBookByPath(const std::string &bookPath)
{
    Book::Builder builder;
    const char *query = "SELECT * FROM BOOKS WHERE BOOKPATH = ?";
    exit = sqlite3_prepare_v2(DB, query, -1, &stmt, NULL);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return builder.build();
    }

    sqlite3_bind_text(stmt, BOOK_PATH_COL, bookPath.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *bookPath = (const char *)sqlite3_column_text(stmt, BOOK_PATH_COL);
        const char *bookName = (const char *)sqlite3_column_text(stmt, BOOK_NAME_COL);
        const char *authorName = (const char *)sqlite3_column_text(stmt, AUTHOR_NAME_COL);
        const char *authorFileAs = (const char *)sqlite3_column_text(stmt, AUTHOR_FILE_AS_COL);
        const char *contributor = (const char *)sqlite3_column_text(stmt, CONTRIBUTOR_COL);
        const char *publisher = (const char *)sqlite3_column_text(stmt, PUBLISHER_COL);
        const char *uuid = (const char *)sqlite3_column_text(stmt, UUID_COL);
        const char *date = (const char *)sqlite3_column_text(stmt, DATE_COL);
        const char *rights = (const char *)sqlite3_column_text(stmt, RIGHTS_COL);
        const char *language = (const char *)sqlite3_column_text(stmt, LANGUAGE_COL);
        const char *isbn = (const char *)sqlite3_column_text(stmt, ISBN_COL);
        int lastPage = sqlite3_column_int(stmt, LAST_PAGE_COL);

        builder.setBookPath(bookPath)
            .setTitle(bookName)
            .setAuthor(authorName)
            .setAuthorFileAs(authorFileAs)
            .setContributor(contributor)
            .setPublisher(publisher)
            .setUuid(uuid)
            .setDate(date)
            .setRights(rights)
            .setLanguage(language)
            .setIsbn(isbn)
            .setLastPage(lastPage);
        // Add more setters for the remaining fields
    }
    else
    {
        std::cerr << "Error retrieving data: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);
    return builder.build();
}

BookDB::~BookDB()
{
    sqlite3_close(DB);
}
