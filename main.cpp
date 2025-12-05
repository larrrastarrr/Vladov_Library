#include <iostream>
#include "LibrarySystem.h"

using namespace std;

int main() {
    cout << "--- Initializing Library ---\n";
    Library lib;

    Author ivanVazov{ "Ivan Vazov", 1850 };
    Author aleko{ "Aleko Konstantinov", 1863 };
    cout << "Current live books: " << Book::getTotalBooks() << endl;

    Book b1{ "Pod igoto", ivanVazov, 1894, 25.50, "ISBN-001" };
    Book b2{ "Nema zemya", ivanVazov, 1900, 18.90, "ISBN-002" };
    Book b3{ "Bai Ganyo", aleko, 1895, 15.00, "ISBN-003" };

    lib.addBook(b1);
    lib.addBook(b2);
    lib.addBook(b3);

    cout << "Current live books (after adding to vector): " << Book::getTotalBooks() << endl;

    lib.addMember(Member{ "Petar Petrov", "M001", 2023 });
    lib.addMember(Member{ "Maria Ivanova", "M002", 2024 });

    cout << "\n" << lib.to_string() << "\n\n";
    cout << "--- Testing Loans ---\n";
    if (lib.loanBook("ISBN-001", "M001", "2025-11-03", "2025-11-17"))
        cout << "Success: 'Pod igoto' loaned to Petar.\n";

    if (!lib.loanBook("ISBN-001", "M002", "2025-11-04", "2025-11-18"))
        cout << "Expected Fail: 'Pod igoto' is already loaned.\n";

    cout << "Is ISBN-001 available? " << boolalpha << lib.isBookAvailable("ISBN-001") << "\n";

    cout << "\n--- Testing Returns ---\n";
    lib.returnBook("ISBN-001", "M001");
    cout << "Returned ISBN-001.\n";
    cout << "Is ISBN-001 available? " << boolalpha << lib.isBookAvailable("ISBN-001") << "\n";

    cout << "\n--- Search for 'Vazov' ---\n";
    vector<Book> vazovBooks = lib.findByAuthor("Vazov");
    for (const auto& bk : vazovBooks) {
        cout << bk.to_string() << "\n";
    }

    cout << "\n--- Rule of 5 Scope Test ---\n";
    {
        Book tempBook = b1;
        cout << "Inside scope live books: " << Book::getTotalBooks() << "\n";
    }
    cout << "Outside scope live books: " << Book::getTotalBooks() << "\n";

    return 0;
}