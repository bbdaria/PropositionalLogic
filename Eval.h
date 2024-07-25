#pragma once
#include <memory>
#include <iostream>
#include "Formula.h"
#include <map>
#include "Tree.h"
#include <algorithm>
class InvalidAssignment : public exception
{
    const char *what() const noexcept override
    {
        return "Invalid value forAssignment. Only 0 and 1";
    }
};
class InvalidAP : public exception
{
    const char *what() const noexcept override
    {
        return "Tried toAssign the same Atom";
    }
};
class UndefinedSymbol : public exception
{
    const char *what() const noexcept override
    {
        return "An atom is not defined in theAssignment";
    }
};

class Ass
{
    map<string, int> m_ass;

public:
    Ass(const vector<Atom> AP, const vector<int> values)
    {
        int k = 0;
        for (auto it : AP)
        {
            if (m_ass.find(it.getAtom()) != m_ass.end())
            {
                throw InvalidAP();
            }
            if (values.size() > k)
            {
                if (values[k] != 0 && values[k] != 1)
                {
                    throw InvalidAssignment();
                }
                m_ass.insert({it.getAtom(), values[k]});
            }
            else
            {
                m_ass.insert({it.getAtom(), 1});
            }
            k++;
        }
    }

    map<string, int> getAss() const
    {
        return m_ass;
    }

    int evalAtom(string atom) const
    {
        try
        {
            return m_ass.at(atom);
        }
        catch (...)
        {
            throw UndefinedSymbol();
        }
    }

    void printAss()
    {
        for (auto it : m_ass)
        {
            cout << it.first << " " << it.second << endl;
        }
    }

    bool models(vector<shared_ptr<Formula>> sigma)
    {
        bool answer = true;
        for (auto it : sigma)
        {
            shared_ptr<Tree> tree = make_shared<Tree>();
            tree->load(it);
            answer = answer && evalTree(tree);
        }
        return answer;
    }
    int evalTree(shared_ptr<Tree> tree)
    {
        if (tree->getRoot() == "~")
        {
            return 1 - evalTree(tree->getLeft());
        }
        if (tree->getRoot() == "∧")
        {
            return evalTree(tree->getLeft()) && evalTree(tree->getRight());
        }
        if (tree->getRoot() == "∨")
        {
            return evalTree(tree->getLeft()) || evalTree(tree->getRight());
        }
        if (tree->getRoot() == "->")
        {
            return (1 - evalTree(tree->getLeft())) || evalTree(tree->getRight());
        }
        return evalAtom(tree->getRoot());
    }
};
