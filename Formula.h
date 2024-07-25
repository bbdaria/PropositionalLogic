#pragma once
#include <iostream>
#include <memory>
#include <utility>
using namespace std;

class Formula
{
public:
    virtual ~Formula() = default;
    virtual string toString() const = 0;
    virtual string getOperand() const = 0;
    virtual pair<shared_ptr<Formula>, shared_ptr<Formula>> getFormula() const = 0;
};

class Atom : public Formula
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
    pair<shared_ptr<Formula>, shared_ptr<Formula>> getFormula() const override
    {
        return {make_shared<Atom>(*this), make_shared<Atom>(*this)};
    }
};

class UnaryOperand : public Formula
{
protected:
    shared_ptr<Formula> m_formula;

public:
    UnaryOperand(shared_ptr<Formula> f) : m_formula(f) {}
    pair<shared_ptr<Formula>, shared_ptr<Formula>> getFormula() const override
    {
        return {m_formula, m_formula};
    }
    string getOperand() const override = 0;
};

class Not : public UnaryOperand
{
    string m_operand = "~";

public:
    Not(shared_ptr<Formula> f) : UnaryOperand(f) {}
    string toString() const override { return m_operand + "(" + m_formula->toString() + ")"; }
    string getOperand() const override
    {
        return m_operand;
    }
};

class BinaryOperand : public Formula
{
protected:
    shared_ptr<Formula> m_rightFormula;
    shared_ptr<Formula> m_leftFormula;

public:
    BinaryOperand(shared_ptr<Formula> l, shared_ptr<Formula> r) : m_rightFormula(r), m_leftFormula(l) {}
    pair<shared_ptr<Formula>, shared_ptr<Formula>> getFormula() const override
    {
        return {m_leftFormula, m_rightFormula};
    }
    string getOperand() const override = 0;
};

class And : public BinaryOperand
{
    string m_operand = "∧";

public:
    And(shared_ptr<Formula> l, shared_ptr<Formula> r) : BinaryOperand(l, r) {}
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

class Or : public BinaryOperand
{
    string m_operand = "∨";

public:
    Or(shared_ptr<Formula> l, shared_ptr<Formula> r) : BinaryOperand(l, r) {}
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

class Imply : public BinaryOperand
{
    string m_operand = "->";

public:
    Imply(shared_ptr<Formula> l, shared_ptr<Formula> r) : BinaryOperand(l, r) {}
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
