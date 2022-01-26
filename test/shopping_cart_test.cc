#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../include/customer.h"
#include "../include/product.h"
#include "../include/shopping_cart.h"

class ShoppingCartTest : public testing::Test {
public:
    const int kPrice = 100;
    const std::string kProduct = "Product";
    Customer customer;

protected:
    void SetUp() override {
        customer = Customer("test");
    }
};

TEST_F(ShoppingCartTest, should_calculate_price_with_no_discount) {
    std::vector<Product> products{
            {static_cast<double>(kPrice), "", kProduct}
    };
    ShoppingCart cart(customer, products);
    Order order = cart.Checkout();

    EXPECT_DOUBLE_EQ(100.0, order.GetTotalPrice());
}

TEST_F(ShoppingCartTest, should_calculate_loyalty_points_with_no_discount) {
    std::vector<Product> products{
            {static_cast<double>(kPrice), "", kProduct}
    };
    ShoppingCart cart(customer, products);
    Order order = cart.Checkout();

    EXPECT_EQ(20, order.GetLoyaltyPoints());
}

TEST_F(ShoppingCartTest, should_calculate_price_for_10_percent_discount) {
    std::vector<Product> products{
            {static_cast<double>(kPrice), "DIS_10_ABCD", kProduct}
    };
    ShoppingCart cart(customer, products);
    Order order = cart.Checkout();

    EXPECT_DOUBLE_EQ(90.0, order.GetTotalPrice());
}


TEST_F(ShoppingCartTest, should_calculate_loyalty_points_for_10_percent_discount) {
    std::vector<Product> products{
            {static_cast<double>(kPrice), "DIS_10_ABCD", kProduct}
    };
    ShoppingCart cart(customer, products);
    Order order = cart.Checkout();

    EXPECT_EQ(10, order.GetLoyaltyPoints());
}

TEST_F(ShoppingCartTest, should_calculate_price_for_15_percent_discount) {
    std::vector<Product> products{
            {static_cast<double>(kPrice), "DIS_15_ABCD", kProduct}
    };
    ShoppingCart cart(customer, products);
    Order order = cart.Checkout();

    EXPECT_DOUBLE_EQ(85.0, order.GetTotalPrice());
}

TEST_F(ShoppingCartTest, should_calculate_loyalty_points_for_15_percent_discount) {
    std::vector<Product> products{
            {static_cast<double>(kPrice), "DIS_15_ABCD", kProduct}
    };
    ShoppingCart cart(customer, products);
    Order order = cart.Checkout();

    EXPECT_EQ(6, order.GetLoyaltyPoints());
}