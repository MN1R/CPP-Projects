#ifndef KNIGHT
#define KNIGHT
   
class Knight
{
private:
    int m_health;
    int m_expirience;

public:
    Knight() : m_health(100), m_expirience(0)
    {
    };

    int getHealth() const;
    int getExpirience() const;

    void setHealth(int number);
    void setExpirience(int number);
};

#endif
