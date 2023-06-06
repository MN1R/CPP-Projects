#include "../product.h"

int Product::m_id_counter = 0;

// get
int Product::getID() const { return m_id; }
std::string Product::getName() const { return m_name; }
float Product::getPrice() const { return m_price; }
int Product::getQuantity() const { return m_quantity; }

//set
void Product::setQuantity(int new_quantity) { m_quantity = new_quantity; }