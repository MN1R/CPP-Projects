#include "../saleperson.h"

int SalesPerson::m_id_counter = 0;

// get
int SalesPerson::getID() const { return m_id; }
std::string SalesPerson::getName() const { return m_name; }
float SalesPerson::getCommision() const { return m_commision; }