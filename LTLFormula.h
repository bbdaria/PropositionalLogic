#pragma once
#include <iostream>
#include <memory>
#include <utility>
using namespace std;

class LTLFormula
{
public:
    virtual ~LTLFormula() = default;
    virtual string toString() const = 0;
    virtual string getOperand() const = 0;
    virtual pair<shared_ptr<LTLFormula>, shared_ptr<LTLFormula>> getFormula() const = 0;
};

class Atom : public LTLFormula
{
    string m_atom;

public:
    Atom(const Atom &a)
    {
        m_atom = a.getAtom();
    }
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
    string getOperand() const override
    {
        return m_atom;
    }
    pair<shared_ptr<LTLFormula>, shared_ptr<LTLFormula>> getFormula() const override
    {
        return {make_shared<Atom>(*this), make_shared<Atom>(*this)};
    }
};

class UnaryOperand : public LTLFormula
{
protected:
    shared_ptr<LTLFormula> m_formula;

public:
    UnaryOperand(shared_ptr<LTLFormula> f) : m_formula(f) {}
    pair<shared_ptr<LTLFormula>, shared_ptr<LTLFormula>> getFormula() const override
    {
        return {m_formula, m_formula};
    }
    string getOperand() const override = 0;
};

class Not : public UnaryOperand
{
    string m_operand = "~";

public:
    Not(shared_ptr<LTLFormula> f) : UnaryOperand(f) {}
    string toString() const override { return m_operand + "(" + m_formula->toString() + ")"; }
    string getOperand() const override
    {
        return m_operand;
    }
};

class BinaryOperand : public LTLFormula
{
protected:
    shared_ptr<LTLFormula> m_rightFormula;
    shared_ptr<LTLFormula> m_leftFormula;

public:
    BinaryOperand(shared_ptr<LTLFormula> l, shared_ptr<LTLFormula> r) : m_rightFormula(r), m_leftFormula(l) {}
    pair<shared_ptr<LTLFormula>, shared_ptr<LTLFormula>> getFormula() const override
    {
        return {m_leftFormula, m_rightFormula};
    }
    string getOperand() const override = 0;
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
    string getOperand() const override
    {
        return m_operand;
    }
};
