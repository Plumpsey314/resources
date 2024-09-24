#include "product.h"

class Book : public Product
{
    public:
        Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn);
        ~Book();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;
    private:
        std::string isbn_;
        std::string author_;
        std::set<std::string> keywords_;
};
