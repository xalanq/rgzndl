#include "atom.h"

Atom::Atom(int value)
{
    a = b = nullptr;
    val = value;
    done = 0;
}

void Atom::cal(bool force)
{
    if (done && !force)
        return;
    if (a && b) {
        a->cal(0);
        b->cal(0);
        if (type == PLUS)
            val = a->val + b->val;
        else if (type == MINUS)
            val = a->val - b->val;
        else if (type == TIMES)
            val = a->val * b->val;
        else if (type == DIVIDE)
            val = a->val / b->val;
        else if (type == MODULO)
            val = a->val % b->val;
    }
}

void Atom::set(int value)
{
    val = value;
}

void Atom::setDone(bool value)
{
    done = value;
}

int Atom::get()
{
    return val;
}

Atom::ptr operator + (const Atom::ptr &x, const Atom::ptr &y)
{
    Atom::ptr r(new Atom());
    r->setPair(x, y, Atom::PLUS);
    return r;
}

Atom::ptr operator - (const Atom::ptr &x, const Atom::ptr &y)
{
    Atom::ptr r(new Atom());
    r->setPair(x, y, Atom::MINUS);
    return r;
}

Atom::ptr operator * (const Atom::ptr &x, const Atom::ptr &y)
{
    Atom::ptr r(new Atom());
    r->setPair(x, y, Atom::TIMES);
    return r;
}

Atom::ptr operator / (const Atom::ptr &x, const Atom::ptr &y)
{
    Atom::ptr r(new Atom());
    r->setPair(x, y, Atom::DIVIDE);
    return r;
}

Atom::ptr operator % (const Atom::ptr &x, const Atom::ptr &y)
{
    Atom::ptr r(new Atom());
    r->setPair(x, y, Atom::MODULO);
    return r;
}

Atom::ptr Atom::fromInt(const int &val)
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
