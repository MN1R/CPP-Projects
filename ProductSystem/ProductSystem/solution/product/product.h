#pragma once
#include <string>

// class of Product, which has default properties
class Product {
private:
  static int m_id_counter;
  int m_id;
  std::string m_name;
  float m_price;
  int m_quantity;

public:
  Product(const std::string &name, float price, int quantity)
      : m_id(++m_id_counter), m_name(name), m_price(price),
        m_quantity(quantity) {}

  // get
  int getID() const;
  std::string getName() const;
  float getPrice() const;
  int getQuantity() const;

  // set
  void setQuantity(int new_quantity);
};