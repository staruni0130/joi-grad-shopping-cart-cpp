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

TEST_F(ShoppingCartTest, should_calculate_price_for_20_percent_discount) {
    std::vector<Product> products{
            {static_cast<double>(kPrice), "DIS_20_ABCD", kProduct}
    };
    ShoppingCart cart(customer, products);
    Order order = cart.Checkout();

    EXPECT_DOUBLE_EQ(80.0, order.GetTotalPrice());
}

TEST_F(ShoppingCartTest, should_calculate_loyalty_points_for_20_percent_discount) {
    std::vector<Product> products{
            {static_cast<double>(kPrice), "DIS_20_ABCD", kProduct}
    };
    ShoppingCart cart(customer, products);
    Order order = cart.Checkout();

    EXPECT_EQ(5, order.GetLoyaltyPoints());
}

TEST_F(ShoppingCartTest, should_calculate_price_for_bulk_buy_discount) {
    std::vector<Product> products;
    
    Product my_product =  Product(static_cast<double>(kPrice), "BULK_BUY_2_GET_1_ABCD", kProduct);
    
    for (int i = 0; i < 6; i++)
    {
        products.push_back(my_product);
    }
    
    ShoppingCart cart(customer, products);
    
    Order order = cart.Checkout();

    EXPECT_DOUBLE_EQ(400.0, order.GetTotalPrice());
}

TEST_F(ShoppingCartTest, should_calculate_total_price_discount) {
    std::vector<Product> products;
    
    Product product1 =  Product(static_cast<double>(kPrice), "BULK_BUY_2_GET_1_ABCD", kProduct);
    Product product2 =  Product(static_cast<double>(kPrice), "ABCD", kProduct);
    for (int i = 0; i < 6; i++)
    {
        products.push_back(product1);
    }
    products.push_back(product2);

    ShoppingCart cart(customer, products);
    
    Order order = cart.Checkout();

    EXPECT_DOUBLE_EQ(475.0, order.GetTotalPrice());
}