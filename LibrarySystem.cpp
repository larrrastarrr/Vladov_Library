#include "LibrarySystem.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

// =======================
// Author Implementation
// =======================
Author::Author() : name("Unknown"), birthYear(1900) {}

Author::Author(std::string name, int birthYear) : name(std::move(name)) {
    setBirthYear(birthYear);
}

std::string Author::getName() const { return name; }
int Author::getBirthYear() const { return birthYear; }

void Author::setBirthYear(int year) {
    if (year >= 1850 && year <= 2025) {
        birthYear = year;
    }
    else {
        std::cerr << "Warning: Invalid birth year for author. Setting to default 1900.\n";
        birthYear = 1900;
    }
}

std::string Author::to_string() const {
    return name + " (" + std::to_string(birthYear) + ")";
}

// =======================
// Book Implementation
// =======================

int Book::totalBooks = 0;

Book::Book()
    : title("Untitled"), author(), year(2000), price(0.0), isbn("000-000") {
    totalBooks++;
}

Book::Book(std::string title, Author author, int year, double price, std::string isbn)
    : title(std::move(title)), author(std::move(author)), isbn(std::move(isbn)) {
    setYear(year);
    setPrice(price);
    totalBooks++;
}

Book::Book(const Book& other)
    : title(other.title), author(other.author), year(other.year),
    price(other.price), isbn(other.isbn) {
    totalBooks++;
}

Book::Book(Book&& other) noexcept
    : title(std::move(other.title)), author(std::move(other.author)), year(other.year),
    price(other.price), isbn(std::move(other.isbn)) {
    totalBooks++;
}

Book::~Book() {
    totalBooks--;
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        title = other.title;
        author = other.author;
        year = other.year;
        price = other.price;
        isbn = other.isbn;
    }
    return *this;
}

Book& Book::operator=(Book&& other) noexcept {
    if (this != &other) {
        title = std::move(other.title);
        author = std::move(other.author);
        year = other.year;
        price = other.price;
        isbn = std::move(other.isbn);
    }
    return *this;
}

void Book::setPrice(double newPrice) {
    if (newPrice >= 0) price = newPrice;
    else price = 0.0;
}

void Book::setYear(int newYear) {
    if (newYear > 0 && newYear <= 2025) year = newYear;
    else year = 2000;
}

std::string Book::getIsbn() const { return isbn; }
Author Book::getAuthor() const { return author; }

std::string Book::to_string() const {
    std::ostringstream oss;
    oss << "'" << title << "' by " << author.getName()
        << ", " << year << ", $" << std::fixed << std::setprecision(2) << price
        << " [ISBN: " << isbn << "]";
    return oss.str();
}

int Book::getTotalBooks() {
    return totalBooks;
}

// =======================
// Member Implementation
// =======================
Member::Member() : name("Guest"), memberId("G000"), yearJoined(2024) {}

Member::Member(std::string name, std::string memberId, int yearJoined)
    : name(std::move(name)), yearJoined(yearJoined) {
    if (!memberId.empty()) this->memberId = std::move(memberId);
    else this->memberId = "UNKNOWN";
}

std::string Member::getMemberId() const { return memberId; }

std::string Member::to_string() const {
    return name + " [ID: " + memberId + "]";
}

// =======================
// Loan Implementation
// =======================
Loan::Loan(std::string isbn, std::string memberId, std::string startDate, std::string dueDate)
    : isbn(std::move(isbn)), memberId(std::move(memberId)),
    startDate(std::move(startDate)), dueDate(std::move(dueDate)), returned(false) {

    if (this->dueDate < this->startDate) {
        std::cerr << "Error: Due date is before start date. Swapping.\n";
        std::swap(this->startDate, this->dueDate);
    }
}

void Loan::markReturned() { returned = true; }

bool Loan::isOverdue(const std::string& today) const {
    return !returned && (today > dueDate);
}

bool Loan::isReturned() const { return returned; }
std::string Loan::getIsbn() const { return isbn; }
std::string Loan::getMemberId() const { return memberId; }

std::string Loan::to_string() const {
    return "Loan: Book " + isbn + " to Member " + memberId +
        " (" + startDate + " -> " + dueDate + ")" +
        (returned ? " [RETURNED]" : " [ACTIVE]");
}

// =======================
// Library Implementation
// =======================
void Library::addBook(const Book& b) {
    books.push_back(b);
}

void Library::addMember(const Member& m) {
    members.push_back(m);
}

bool Library::hasBook(const std::string& isbn) const {
    for (const auto& b : books) {
        if (b.getIsbn() == isbn) return true;
    }
    return false;
}

bool Library::isBookAvailable(const std::string& isbn) const {
    if (!hasBook(isbn)) return false;

    for (const auto& loan : loans) {
        if (loan.getIsbn() == isbn && !loan.isReturned()) {
            return false;
        }
    }
    return true;
}

bool Library::loanBook(const std::string& isbn, const std::string& memberId, const std::string& start, const std::string& due) {
    if (!isBookAvailable(isbn)) {
        std::cerr << "Loan Failed: Book " << isbn << " is not available or does not exist.\n";
        return false;
    }

    bool memberExists = false;
    for (const auto& m : members) {
        if (m.getMemberId() == memberId) {
            memberExists = true;
            break;
        }
    }
    if (!memberExists) {
        std::cerr << "Loan Failed: Member " << memberId << " not found.\n";
        return false;
    }

    loans.emplace_back(isbn, memberId, start, due);
    return true;
}

bool Library::returnBook(const std::string& isbn, const std::string& memberId) {
    for (auto& loan : loans) {
        if (loan.getIsbn() == isbn && loan.getMemberId() == memberId && !loan.isReturned()) {
            loan.markReturned();
            return true;
        }
    }
    std::cerr << "Return Failed: No active loan found for this book and member.\n";
    return false;
}

std::vector<Book> Library::findByAuthor(const std::string& authorName) const {
    std::vector<Book> result;
    for (const auto& b : books) {
        if (b.getAuthor().getName().find(authorName) != std::string::npos) {
            result.push_back(b);
        }
    }
    return result;
}

std::string Library::to_string() const {
    int activeLoans = 0;
    for (const auto& l : loans) {
        if (!l.isReturned()) activeLoans++;
    }

    std::ostringstream oss;
    oss << "=== Library Status ===\n"
        << "Total Books in Collection: " << books.size() << "\n"
        << "Total Members: " << members.size() << "\n"
        << "Total Loans (History): " << loans.size() << "\n"
        << "Active Loans: " << activeLoans << "\n"
        << "Global Book Instances (Static): " << Book::getTotalBooks() << "\n"
        << "======================";
    return oss.str();
}