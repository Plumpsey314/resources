#include <iostream>

#include "util.h"
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore(){
    products_ = std::vector<Product*>();
    users_ = std::map<std::string, User*>();
    keywordMapping_ = std::map<std::string, std::set<Product*>>();
    carts_ = std::map<User*, std::queue<Product* >>();
}

MyDataStore::~MyDataStore(){
 // no destructing   
}

void MyDataStore::addUser(User* u){
    users_.insert(std::make_pair(u->getName(), u));
    carts_[u] = std::queue<Product* >();
}

void MyDataStore::addProduct(Product* p){
    products_.push_back(p);

    // adjusting keyword mapping.
    std::set<Product*> productSingelton = std::set<Product*>();
    productSingelton.insert(p);
    // p->keywords() is O(1) time to run.
    for(std::set<std::string>::iterator it = p->keywords().begin(); it != p->keywords().end(); ++it){
        if(keywordMapping_.find(*it) == keywordMapping_.end()){
            keywordMapping_[*it] = productSingelton;
        }else{
            keywordMapping_[*it] = setUnion(keywordMapping_[*it], productSingelton);
        }
    }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    //0=and 1=or
    if(type != 0 and type != 1){ throw std::invalid_argument("type must be 0 or 1");}

    if(terms.size() == 0){
        // returning the empty set if no terms are provided
        return std::vector<Product*>();
    }
    std::set<Product*> items = keywordMapping_[terms[0]];
    for(size_t i = 1; i < terms.size(); i++){
        if(type==1){
            items=setUnion(items, keywordMapping_[terms[1]]);
        }else{
            items=setIntersection(items, keywordMapping_[terms[1]]);
        }
    }
    return std::vector<Product*>(items.begin(), items.end());
}

void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << "\n";
    for(size_t i = 0; i < products_.size(); i++){
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << "\n";
    ofile << "<users>" << "\n";
    for(std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

User* MyDataStore::findUser(std::string username) {
    std::map<std::string, User*>::iterator userIt = users_.find(username);
    if(userIt == users_.end()){return NULL;}
    return userIt->second;
}

void MyDataStore::addToCart(User* user, Product* product){
    // each user has a cart.
    carts_[user].push(product);
}

void MyDataStore::viewCart(User* user){
    int itemNum = 1;
    for(std::queue<Product*>* cart = &carts_[user]; !cart->empty(); ++cart){
        cout << "Item " << itemNum++ << '\n';
        cout << cart->front()->displayString() << endl;
    }
}

void MyDataStore::buyCart(User* user){
    std::queue<Product*>* cart = &carts_[user];
    while(!cart->empty()){
        Product* cur = cart->front();
        // need the user to be able to afford and the product to be in stock
        if(user->getBalance() >= cur->getPrice() && cur->getQty() > 0){
            cur->subtractQty(1);
            user->deductAmount(cur->getPrice());
        }else{
            cart++;
        }
    }
}

