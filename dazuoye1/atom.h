#ifndef ATOMH
#define ATOMH

#include <memory>

class Atom
{
public:

    enum Type {PLUS, MINUS, TIMES, DIVIDE, MODULO};
    typedef std::shared_ptr<Atom> ptr;

    Atom(int value = 0);
    void cal(bool force = 1);
    void set(int value);
    void setDone(bool value);
    int get();
    friend ptr operator + (const ptr &x, const ptr &y);
    friend ptr operator - (const ptr &x, const ptr &y);
    friend ptr operator * (const ptr &x, const ptr &y);
    friend ptr operator / (const ptr &x, const ptr &y);
    friend ptr operator % (const ptr &x, const ptr &y);
    static ptr fromInt(const int &val = 0);

private:
    ptr a, b;
    int val;
    Type type;
    bool done;

    void setPair(const ptr &x, const ptr &y, const Type &_type);
};

#endif // ATOMH
