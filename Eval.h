#pragma once
#include <memory>
#include <iostream>
#include "LTLFormula.h"
#include <map>
#include <algorithm>
class InvalidAssignment : public exception
{
    const char *what() const noexcept override
    {
        return "Invalid value for assignment. Only 0 and 1";
    }
};
class InvalidAP : public exception
{
    const char *what() const noexcept override
    {
        return "Tried to assign the same Atom";
    }
};
class UndefinedSymbol : public exception
{
    const char *what() const noexcept override
    {
        return "An atom is not defined in the assignment";
    }
};

class Eval
{
    map<string, int> m_eval;

public:
    Eval(const vector<Atom> AP, const vector<int> values)
    {
        int k = 0;
        for (auto it : AP)
        {
            if (m_eval.find(it.getAtom()) != m_eval.end())
            {
                throw InvalidAP();
            }
            if (values.size() > k)
            {
                if (values[k] != 0 && values[k] != 1)
                {
                    throw InvalidAssignment();
                }
                m_eval.insert({it.getAtom(), values[k]});
            }
            else
            {
                m_eval.insert({it.getAtom(), 1});
            }
            k++;
        }
    }

    map<string, int> getEval() const
    {
        return m_eval;
    }

    int evalAtom(string atom) const
    {
        try
        {
            return m_eval.at(atom);
        }
        catch (...)
        {
            throw UndefinedSymbol();
        }
    }

    void printEval()
    {
        for (auto it : m_eval)
        {
            cout << it.first << " " << it.second << endl;
        }
    }
};
