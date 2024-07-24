#pragma once
#include <iostream>
#include <memory>
using namespace std;

class LTLFormula
{
public:
    virtual ~LTLFormula() = default;
    virtual string toString() const = 0;
};

class Atom : public LTLFormula
{
    string m_atom;

public:
    Atom(const string &name) : m_atom(name) {}
    string toString() const override { return m_atom; }
    bool operator==(const Atom &b)
    {
        return this->m_atom == b.m_atom;
    }
    string getAtom() const
    {
        return m_atom;
    }
};

class UnaryOperand : public LTLFormula
{
protected:
    shared_ptr<LTLFormula> m_formula;

public:
    UnaryOperand(shared_ptr<LTLFormula> f) : m_formula(f) {}
};

class Not : public UnaryOperand
{
    string m_operand = "~";

public:
    Not(shared_ptr<LTLFormula> f) : UnaryOperand(f) {}
    string toString() const override { return m_operand + "(" + m_formula->toString() + ")"; }
};

class BinaryOperand : public LTLFormula
{
protected:
    shared_ptr<LTLFormula> m_rightFormula;
    shared_ptr<LTLFormula> m_leftFormula;

public:
    BinaryOperand(shared_ptr<LTLFormula> l, shared_ptr<LTLFormula> r) : m_rightFormula(r), m_leftFormula(l) {}
};

class And : public BinaryOperand
{
    string m_operand = "∧";

public:
    And(shared_ptr<LTLFormula> l, shared_ptr<LTLFormula> r) : BinaryOperand(l, r) {}
    string toString() const override
    {
        return "(" + m_leftFormula->toString() + ")" + m_operand +
               "(" + m_rightFormula->toString() + ")";
    }
};
