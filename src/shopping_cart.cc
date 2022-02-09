#include "../include/shopping_cart.h"
#include <algorithm>
#include <map>

Order ShoppingCart::Checkout() {
    double total_price = 0;
    std::map<std::string, int> bulk_buy_map;
    int loyalty_points_earned = 0;
    for (auto &product: products_) {
        double discount = 0;
        if (product.GetProductCode().find("DIS_10") == 0) {
            discount = (product.GetPrice() * 0.1);
            loyalty_points_earned += (product.GetPrice() / 10);
        } else if (product.GetProductCode().find("DIS_15") == 0) {
            discount = (product.GetPrice() * 0.15);
            loyalty_points_earned += (product.GetPrice() / 15);
        }  else if (product.GetProductCode().find("DIS_20") == 0) {
            discount = (product.GetPrice() * 0.20);
            loyalty_points_earned += (product.GetPrice() / 20);
        }  else if (product.GetProductCode().find("BULK_BUY_2_GET_1") == 0) {
                std::map<std::string, int>::iterator it = bulk_buy_map.find(product.GetProductCode()) ; 
                if(it!= bulk_buy_map.end()){
                it->second = it->second + 1;
                } else {
                    bulk_buy_map.insert(std::pair<std::string,int>(product.GetProductCode(), 1));
                }
                if(it->second == 3){
                    discount = product.GetPrice();
                    it->second = 0;
                }
        } else {
            loyalty_points_earned += (product.GetPrice() / 5);
        }
        total_price += product.GetPrice() - discount;
    }
    if(total_price>=500){
        total_price = total_price * 0.95;
    }

    return Order(total_price, loyalty_points_earned);
}

std::ostream &operator<<(std::ostream &os, const ShoppingCart &cart) {
    os << "Customer: " << cart.customer_.GetName() << std::endl
       << "Bought: " << std::endl;
    std::vector<std::string> result;
    std::transform(cart.products_.begin(), cart.products_.end(), std::back_inserter(result),
                   [](const Product &p) { return "- " + p.GetName() + ", " + std::to_string(p.GetPrice()); });
    auto begin = result.begin();
    auto end = result.end();
    if (begin != end) {
        os << *begin++;
    }
    while (begin != end) {
        os << std::endl << *begin++;
    }
    return os;
}
