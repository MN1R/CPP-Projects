#include "../sale_record.h"

// get
Product &SaleRecord::getProduct() { return m_product; }
SalesPerson &SaleRecord::getSalesPerson() { return m_sales_person; }
int SaleRecord::getQuanity() const { return m_quantity; }