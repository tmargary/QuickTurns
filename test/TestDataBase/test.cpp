#include "gtest/gtest.h"
#include "DataBase.h"

TEST(BookDBTest, AddBookToDatabaseTest)
{
    // Initialize a BookDB instance
    BookDB bookDB(":memory:");

    // Create a book to add to the database
    Book book("path/to/book", "My Book", "Jane Doe", 2021, 50);

    // Add the book to the database and get the new ID
    int id = bookDB.addBookToDatabase(book);

    // Check that the book was added with a unique ID
    EXPECT_NE(id, -1);

    // Check that the book can be retrieved by its ID
    Book retrievedBook = bookDB.getBookById(id);
    EXPECT_EQ(retrievedBook.bookPath, book.bookPath);
    EXPECT_EQ(retrievedBook.bookName, book.bookName);
    EXPECT_EQ(retrievedBook.bookAuthorName, book.bookAuthorName);
    EXPECT_EQ(retrievedBook.bookYear, book.bookYear);
    EXPECT_EQ(retrievedBook.lastPage, book.lastPage);
}
