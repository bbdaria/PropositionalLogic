#include "LTLFormula.h"
#include "Eval.h"
#include "LTLTree.h"

int main()
{
    shared_ptr<Atom> a = make_shared<Atom>("a");
    shared_ptr<Atom> b = make_shared<Atom>("b");
    shared_ptr<LTLFormula> notA = make_shared<Not>(a);
    shared_ptr<LTLFormula> notB = make_shared<Not>(b);
    shared_ptr<LTLFormula> andExp = make_shared<And>(notA, b);
    shared_ptr<LTLFormula> notBandnotAandB = make_shared<And>(notB, andExp);
    shared_ptr<LTLFormula> notAndExp = make_shared<Not>(andExp);

    cout << andExp->toString() << endl;
    // cout << notAndExp->toString() << endl;

    shared_ptr<Tree> treeAndEp = make_shared<Tree>();
    treeAndEp->load(andExp);
    treeAndEp->print();
    cout << endl;

    cout << notBandnotAandB->toString() << endl;
    shared_ptr<Tree> treenotBandnotAandB = make_shared<Tree>();
    treenotBandnotAandB->load(notBandnotAandB);
    treenotBandnotAandB->print();

    vector<Atom> stringVector = {*a, *b};
    vector<int> intVector = {0, 1};
    Eval *z = new Eval(stringVector, intVector);
    z->printEval();

    cout << "z" << andExp->toString() << " = " << treeAndEp->evalTree(z) << endl;
    cout << "z" << notBandnotAandB->toString() << " = " << treenotBandnotAandB->evalTree(z) << endl;
    return 0;
}