#include "../sales_manager.h"

// adding new sale info
void SalesManager::addSale(SaleRecord &sale_record) {
  m_sales_records.push_back(sale_record);
  ++m_number_of_sales_records;
}

// getting total sale for all products
int SalesManager::getTotalSales() {
  int sum = 0;
  for (auto &element : m_sales_records)
    sum += element.get().getProduct().getPrice() * element.get().getQuanity();

  return sum;
}

// calculation, how much money person will take
float SalesManager::getSalesPersonCommission(int sales_person_id) {
  float sum = 0;
  for (auto &element : m_sales_records) {
    if (element.get().getSalesPerson().getID() == sales_person_id)
      sum +=
          (element.get().getProduct().getPrice() * element.get().getQuanity() *
           element.get().getSalesPerson().getCommision());
  }

  return sum;
}