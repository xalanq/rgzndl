#include "atom.h"

Atom::Atom()
{
    val = 0;
    done = 0;
}

Atom::Atom(int value)
{
    val = value;
    done = 0;
}

Atom::~Atom()
{

}

void Atom::cal(bool force)
{
    if (done && !force)
        return;
    a->cal(0);
    b->cal(0);
    if (type == PLUS)
        val = a->val + b->val;
    else if (type == MINUS)
        val = a->val - b->val;
    else if (type == TIMES)
        val = a->val - b->val;
    else if (type == DIVIDE)
        val = a->val / b->val;
    else if (type == MODULO)
        val = a->val % b->val;
}

void Atom::set(int value)
{
    val = value;
}

void Atom::setDone(bool value)
{
    done = value;
}

int Atom::getValue()
{
    return val;
}

Atom::ptr Atom::Plus(const Atom::ptr &x, const Atom::ptr &y)
{
    ptr r(new Atom());
    r->setPair(x, y, PLUS);
    return r;
}

Atom::ptr Atom::Minus(const Atom::ptr &x, const Atom::ptr &y)
{
    ptr r(new Atom());
    r->setPair(x, y, MINUS);
    return r;
}

Atom::ptr Atom::Times(const Atom::ptr &x, const Atom::ptr &y)
{
    ptr r(new Atom());
    r->setPair(x, y, TIMES);
    return r;
}

Atom::ptr Atom::Divide(const Atom::ptr &x, const Atom::ptr &y)
{
    ptr r(new Atom());
    r->setPair(x, y, DIVIDE);
    return r;
}

Atom::ptr Atom::Modulo(const Atom::ptr &x, const Atom::ptr &y)
{
    ptr r(new Atom());
    r->setPair(x, y, MODULO);
    return r;
}

Atom::ptr Atom::Int(const int &val)
{
    ptr x(new Atom());
    x->set(val);
    return x;
}

void Atom::setPair(const Atom::ptr &x, const Atom::ptr &y, const Type &_type)
{
    a = x;
    b = y;
    type = _type;
}
