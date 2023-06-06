#pragma once
#include "../sale_record/sale_record.h"
#include "vector"

// class which has data of all sales, which is added to our vector
class SalesManager {
private:
  std::vector<std::reference_wrapper<SaleRecord>> m_sales_records;
  int m_number_of_sales_records = 0;

public:
  // adding new sale info
  void addSale(SaleRecord &sale_record);

  // getting total sale for all products
  int getTotalSales();

  // calculation, how much money person will take
  float getSalesPersonCommission(int sales_person_id);
};