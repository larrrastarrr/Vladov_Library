#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <string>
#include <vector>
#include <iostream>

// =======================
// Class: Author
// =======================
class Author {
private:
    std::string name;
    int birthYear;

public:
    Author();
    Author(std::string name, int birthYear);

    std::string getName() const;
    int getBirthYear() const;
    void setBirthYear(int year);

    std::string to_string() const;
};

// =======================
// Class: Book
// =======================
class Book {
private:
    std::string title;
    Author author;
    int year;
    double price;
    std::string isbn;

    // Статичен брояч
    static int totalBooks;

public:
    Book();
    Book(std::string title, Author author, int year, double price, std::string isbn);
    Book(const Book& other);
    Book(Book&& other) noexcept;
    ~Book();

    Book& operator=(const Book& other);
    Book& operator=(Book&& other) noexcept;
    std::string getIsbn() const;
    Author getAuthor() const;
    void setPrice(double newPrice);
    void setYear(int newYear);

    std::string to_string() const;
    static int getTotalBooks();
};

// =======================
// Class: Member
// =======================
class Member {
private:
    std::string name;
    std::string memberId;
    int yearJoined;

public:
    Member();
    Member(std::string name, std::string memberId, int yearJoined);

    std::string getMemberId() const;
    std::string to_string() const;
};

// =======================
// Class: Loan
// =======================
class Loan {
private:
    std::string isbn;
    std::string memberId;
    std::string startDate;
    std::string dueDate;
    bool returned;

public:
    Loan(std::string isbn, std::string memberId, std::string startDate, std::string dueDate);

    void markReturned();
    bool isOverdue(const std::string& today) const;
    bool isReturned() const;
    std::string getIsbn() const;
    std::string getMemberId() const;

    std::string to_string() const;
};

// =======================
// Class: Library
// =======================
class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;

public:
    void addBook(const Book& b);
    void addMember(const Member& m);

    bool hasBook(const std::string& isbn) const;
    bool isBookAvailable(const std::string& isbn) const;

    bool loanBook(const std::string& isbn, const std::string& memberId, const std::string& start, const std::string& due);
    bool returnBook(const std::string& isbn, const std::string& memberId);

    std::vector<Book> findByAuthor(const std::string& authorName) const;

    std::string to_string() const;
};

#endif