#include "book.h"
#include "product.h"
#include "util.h"

using namespace std;

Book::Book(const std::string name,
    double price,
    int qty,
    const std::string author,
    const std::string isbn):
    Product("book", name, price, qty)
{
    author_ = author;
    isbn_ = isbn;
    std::set<std::string> nameWords = parseStringToWords(name_);
    std::set<std::string> authorWords = parseStringToWords(author_);
    std::set<std::string> isbnSingleton = std::set<std::string>();
    isbnSingleton.insert(isbn_);
    keywords_ = setUnion(nameWords, authorWords);
    keywords_ = setUnion(keywords_, isbnSingleton);
}

Book::~Book(){}

std::set<std::string> Book::keywords() const{
    return keywords_;
}

std::string Book::displayString() const {
    //<name>
    //Author: <author> ISBN: <isbn>
    //<price> <quantity> left.
    std::string rv = "";
    rv += name_;
    rv += "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n";
    rv += to_string(price_) + " " + to_string(qty_) + " left.";
    return rv;
}

void Book::dump(std::ostream& os) const{
    //should print isbn \n author
    cout << isbn_ << '\n' << author_ << endl;
}
