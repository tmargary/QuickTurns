#include "DataBase.h"
#include "gtest/gtest.h"

class BookDBTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        // Set up the test database
        db = std::make_unique<BookDB>("test_database.db");
    }

    virtual void TearDown() {
        // Clean up the test database
        sqlite3 *db_handle;
        sqlite3_open("test_database.db", &db_handle);
        sqlite3_exec(db_handle, "DELETE FROM BOOKS", nullptr, nullptr, nullptr);
        sqlite3_close(db_handle);
    }

    std::unique_ptr<BookDB> db;
};

TEST_F(BookDBTest, AddAndRetrieveBook) {
    Book book = Book::create()
        .setBookPath("path/to/test/book.epub")
        .setTitle("Test Book")
        .setAuthor("Test Author")
        .build();

    int bookId = db->addBookToDatabase(book);
    Book retrievedBook = db->getBookById(bookId);

    EXPECT_EQ(book.bookPath, retrievedBook.bookPath);
    EXPECT_EQ(book.title, retrievedBook.title);
    EXPECT_EQ(book.author, retrievedBook.author);
}

TEST_F(BookDBTest, BookExists) {
    Book book = Book::create()
        .setBookPath("path/to/test/book.epub")
        .setTitle("Test Book")
        .setAuthor("Test Author")
        .build();

    db->addBookToDatabase(book);
    EXPECT_TRUE(db->bookExists(book));
}

TEST_F(BookDBTest, RemoveBook) {
    Book book = Book::create()
        .setBookPath("path/to/test/book.epub")
        .setTitle("Test Book")
        .setAuthor("Test Author")
        .build();

    int bookId = db->addBookToDatabase(book);
    db->removeBook(bookId);
    Book removedBook = db->getBookById(bookId);

    EXPECT_TRUE(removedBook.bookPath.empty());
}