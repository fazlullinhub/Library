#include <iostream>
#include <vector>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;

public:
    Book(std::string t, std::string a, std::string i) : title(t), author(a), isbn(i), isAvailable(true) {}

    std::string getTitle() {
        return title;
    }

    std::string getAuthor() {
        return author;
    }

    std::string getIsbn() {
        return isbn;
    }

    bool getIsAvailable() {
        return isAvailable;
    }

    void setIsAvailable(bool available) {
        isAvailable = available;
    }

    void displayDetails() {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "ISBN: " << isbn << std::endl;
    }
};

class EBook : public Book {
private:
    int fileSize;

public:
    EBook(std::string t, std::string a, std::string i, int size) : Book(t, a, i), fileSize(size) {}

    void displayDetails() {
        Book::displayDetails();
        std::cout << "File Size: " << fileSize << " KB" << std::endl;
    }
};

class Member {
private:
    std::string name;
    std::string memberId;
    std::vector<Book*> borrowedBooks;

public:
    Member(std::string n, std::string id) : name(n), memberId(id) {}

    std::string getName() {
        return name;
    }

    std::string getMemberId() {
        return memberId;
    }

    void borrowBook(Book& book) {
        if (book.getIsAvailable()) {
            borrowedBooks.push_back(&book);
            book.setIsAvailable(false);
        }
        else {
            std::cout << "Book is not available for borrowing" << std::endl;
        }
    }

    void returnBook(Book& book) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), &book);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            book.setIsAvailable(true);
        }
    }
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(), [isbn](const Book& b) { return b.getIsbn() == isbn; });
        if (it != books.end()) {
            books.erase(it);
        }
    }

    Book* findBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(), [isbn](const Book& b) { return b.getIsbn() == isbn; });
        if (it != books.end()) {
            return &(*it);
        }
        return nullptr;
    }

    void registerMember(const Member& member) {
        members.push_back(member);
    }

    void unregisterMember(const std::string& memberId) {
        auto it = std::find_if(members.begin(), members.end(), [memberId](const Member& m) { return m.getMemberId() == memberId; });
        if (it != members.end()) {
            members.erase(it);
        }
    }

    void displayAllBooks() {
        for (const Book& book : books) {
            book.displayDetails();
        }
    }
};

int main() {
    Library library;

    Book book1("The Great Gatsby", "F. Scott Fitzgerald", "1234567890");
    Book book2("To Kill a Mockingbird", "Harper Lee", "0987654321");
    EBook ebook1("1984", "George Orwell", "5432109876", 1024);

    Member member1("Alice", "001");
    Member member2("Bob", "002");

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(ebook1);

    library.registerMember(member1);
    library.registerMember(member2);

    library.displayAllBooks();

    return 0;
}