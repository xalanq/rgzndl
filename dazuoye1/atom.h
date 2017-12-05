#ifndef ATOMH
#define ATOMH

#include <memory>

class Atom
{
public:

    enum Type {PLUS, MINUS, TIMES, DIVIDE, MODULO};
    typedef std::shared_ptr<Atom> ptr;

    Atom();
    Atom(int value);
    ~Atom();
    void cal(bool force = 1);
    void set(int value);
    void setDone(bool value);
    int getValue();
    static ptr Plus(const ptr &x, const ptr &y);
    static ptr Minus(const ptr &x, const ptr &y);
    static ptr Times(const ptr &x, const ptr &y);
    static ptr Divide(const ptr &x, const ptr &y);
    static ptr Modulo(const ptr &x, const ptr &y);
    static ptr Int(const int &val = 0);

private:
    ptr a, b;
    int val;
    Type type;
    bool done;

    void setPair(const ptr &x, const ptr &y, const Type &_type);
};

#endif // ATOMH
