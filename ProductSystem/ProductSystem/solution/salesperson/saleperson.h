#pragma once
#include <cassert>
#include <string>

// class of salesperson, which has own commision in(percentage / 100) and
// default properties
class SalesPerson {
private:
  static int m_id_counter;
  int m_id;
  std::string m_name;
  float m_commision;

public:
  SalesPerson(const std::string &name, float commision)
      : m_id(++m_id_counter), m_name(name) {

    // calling an abort(), when commision is too high
    assert(commision < 1 && "Commision can't be higher than 1(100%).");
    m_commision = commision;
  }

  // get
  int getID() const;
  std::string getName() const;
  float getCommision() const;
};