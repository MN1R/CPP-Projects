#pragma once
#include "../product/product.h"
#include "../salesperson/saleperson.h"

// sale record has a data of sale with the special salesperson and product
class SaleRecord {
private:
  Product &m_product;
  SalesPerson &m_sales_person;
  int m_quantity;

public:
  SaleRecord(Product &product, SalesPerson &sales_person, int quantity)
      : m_product(product), m_sales_person(sales_person) {

    // calling abort(), when we haven't enough product tot sale
    assert(product.getQuantity() >= quantity &&
           "Haven't enough product to sale.");
    m_quantity = quantity;
    product.setQuantity(product.getQuantity() - quantity);
  }

  // get
  Product &getProduct();
  SalesPerson &getSalesPerson();
  int getQuanity() const;
};