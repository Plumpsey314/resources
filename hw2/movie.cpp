#include "movie.h"
#include "product.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string name,
    double price,
    int qty,
    const std::string genre,
    const std::string rating):
    Product("movie", name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
    std::set<std::string> nameWords = parseStringToWords(name_);
    std::set<std::string> genreSingleton = std::set<std::string>();
    genreSingleton.insert(genre_);
    keywords_ = setUnion(nameWords, genreSingleton);
}

Movie::~Movie(){}

std::set<std::string> Movie::keywords() const{
    return keywords_;
}

std::string Movie::displayString() const {
    //<name>
    //Genre: <genre> Rating: <rating>
    //<price> <quantity> left.
    std::string rv = "";
    rv += name_;
    rv += "\nGenre: " + genre_ + " Rating: " + rating_ + "\n";
    rv += to_string(price_) + " " + to_string(qty_) + " left.";
    return rv;
}

void Movie::dump(std::ostream& os) const{
    //should print genre \n rating
    cout << genre_ << '\n' << rating_ << endl;
}
