#include "product.h"

class Clothing : public Product
{
    public:
        Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand);
        ~Clothing();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;
    private:
        std::string brand_;
        std::string size_;
        std::set<std::string> keywords_;
};
