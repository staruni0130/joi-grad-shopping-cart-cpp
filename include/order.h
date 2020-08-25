#ifndef JOI_GRAD_SHOPPING_CART_CPP_ORDER_H
#define JOI_GRAD_SHOPPING_CART_CPP_ORDER_H

#include <ostream>

class Order {
public:
    Order(double total_price, int loyalty_pints_earned) : total_price_(total_price),
                                                          loyalty_points_(loyalty_pints_earned) {}

    double GetTotalPrice() { return total_price_; }

    int GetLoyaltyPoints() { return loyalty_points_; }

    friend std::ostream &operator<<(std::ostream &os, const Order &order) {
        os << "Total price: " << order.total_price_ << std::endl
           << "Will receive " << order.loyalty_points_ << " loyalty points";
        return os;
    }

private:
    double total_price_;
    int loyalty_points_;
};

#endif //JOI_GRAD_SHOPPING_CART_CPP_ORDER_H
