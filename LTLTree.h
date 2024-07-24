#pragma once
#include <memory>
#include <iostream>
#include "LTLFormula.h"
#include <utility>
using namespace std;

class Tree
{

    string m_root;
    shared_ptr<Tree> m_right;
    shared_ptr<Tree> m_left;

public:
    void load(shared_ptr<LTLFormula> f)
    {
        if (dynamic_cast<Atom *>(&(*f)))
        {
            m_root = f->toString();
        }
        else if (dynamic_cast<UnaryOperand *>(&(*f)))
        {
            m_root = f->getOperand();
            pair<shared_ptr<LTLFormula>, shared_ptr<LTLFormula>> formula = f->getFormula();
            m_left = make_shared<Tree>();
            m_left->load(formula.first);
            m_right = nullptr;
        }
        else
        {
            m_root = f->getOperand();
            pair<shared_ptr<LTLFormula>, shared_ptr<LTLFormula>> formula = f->getFormula();
            m_left = make_shared<Tree>();
            m_left->load(formula.first);
            m_right = make_shared<Tree>();
            m_right->load(formula.second);
        }
    }

    int evalTree(Eval *z)
    {
        if (m_root == "~")
        {
            return 1 - m_left->evalTree(z);
        }
        if (m_root == "∧")
        {
            return m_left->evalTree(z) && m_right->evalTree(z);
        }
        return z->evalAtom(m_root);
    }
    void printTree(shared_ptr<Tree> node, int space) const
    {
        if (!node)
            return;

        const int COUNT = 5;
        space += COUNT;

        printTree(node->m_right, space);

        cout << endl;
        for (int i = COUNT; i < space; ++i)
        {
            cout << " ";
        }
        cout << node->m_root << "\n";

        printTree(node->m_left, space);
    }

    void print() const
    {
        printTree(make_shared<Tree>(*this), 0);
    }
};