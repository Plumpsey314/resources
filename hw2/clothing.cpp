#include "clothing.h"
#include "product.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string name,
    double price,
    int qty,
    const std::string size,
    const std::string brand):
    Product("clothing", name, price, qty)
{
    size_ = size;
    brand_ = brand;
    std::set<std::string> nameWords = parseStringToWords(name_);
    std::set<std::string> brandWords = parseStringToWords(brand_);
    std::set<std::string> sizeSingleton = std::set<std::string>();
    sizeSingleton.insert(size_);
    keywords_ = setUnion(nameWords, brandWords);
    keywords_ = setUnion(keywords_, sizeSingleton);
}

Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords() const{
    return keywords_;
}

std::string Clothing::displayString() const {
    //<name>
    // Size: <size> Brand: <brand>
    //<price> <quantity> left.
    std::string rv = "";
    rv += name_;
    rv += "\nSize: " + size_ + " Brand: " + brand_ + "\n";
    rv += to_string(price_) + " " + to_string(qty_) + "left.";
    return rv;
}

void Clothing::dump(std::ostream& os) const{
    //should print size \n brand
    cout << size_ << '\n' << brand_ << endl;
}
