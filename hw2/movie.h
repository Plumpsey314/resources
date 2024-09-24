#include "product.h"

class Movie : public Product
{
    public:
        Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating);
        ~Movie();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;
    private:
        std::string rating_;
        std::string genre_;
        std::set<std::string> keywords_;
};
