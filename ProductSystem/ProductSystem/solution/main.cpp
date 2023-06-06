#include <cassert>
#include <iostream>
#include <string>
#include <iostream>
#include "sales_manager/sales_manager.h"

int main() {
  Product cd_disk("CD Disk", 100, 10);
  Product dendi("Dendi", 1250, 5);
  Product tv("TV", 4750, 3);

  SalesPerson anton("Anton", 0.15f);
  SalesPerson dima("Dima", 0.175f);

  // assertion failure, too high commision
  // SalesPerson nikita("Nikita", 1.175f);

  SalesManager my_sales_manager;

  SaleRecord cd_sale(cd_disk, anton, 5);
  my_sales_manager.addSale(cd_sale);

  SaleRecord cd_sale_1(cd_disk, dima, 5);
  my_sales_manager.addSale(cd_sale_1);

  // assertion failure, quantity error
  // SaleRecord cd_sale_1(cd_disk, dima, 1);

  SaleRecord tv_sale(tv, dima, 2);
  my_sales_manager.addSale(tv_sale);

  std::cout << "Total sum of sales: " << my_sales_manager.getTotalSales()
            << '\n'
            << anton.getName() << " get's: "
            << my_sales_manager.getSalesPersonCommission(anton.getID()) << '\n'
            << dima.getName() << " get's: "
            << my_sales_manager.getSalesPersonCommission(dima.getID());
}