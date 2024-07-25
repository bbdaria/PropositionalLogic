#include "Formula.h"
#include "Eval.h"
#include "Tree.h"

/*
    FUTURE PLANS:
    1. add more operands (including actual LTL)
    2. attempt to construct automata from the formulas

*/
int main()
{
    shared_ptr<Atom> a = make_shared<Atom>("a");
    shared_ptr<Atom> b = make_shared<Atom>("b");
    shared_ptr<Formula> notA = make_shared<Not>(a);
    shared_ptr<Formula> notB = make_shared<Not>(b);
    shared_ptr<Formula> andExp = make_shared<And>(notA, b);
    shared_ptr<Formula> notBandnotAandB = make_shared<And>(notB, andExp);
    shared_ptr<Formula> notAndExp = make_shared<Not>(andExp);
    shared_ptr<Formula> AorB = make_shared<Or>(a, b);

    cout << andExp->toString() << endl;
    shared_ptr<Tree> treeAndEp = make_shared<Tree>();
    treeAndEp->load(andExp);
    treeAndEp->print();
    cout << endl;

    cout << notBandnotAandB->toString() << endl;
    shared_ptr<Tree> treenotBandnotAandB = make_shared<Tree>();
    treenotBandnotAandB->load(notBandnotAandB);
    treenotBandnotAandB->print();
    cout << endl;

    cout << AorB->toString() << endl;
    shared_ptr<Tree> treeAorB = make_shared<Tree>();
    treeAorB->load(AorB);
    treeAorB->print();

    vector<Atom> stringVector = {*a, *b};
    vector<int> intVector = {0, 1};
    Ass *z = new Ass(stringVector, intVector);
    z->printAss();

    cout << "z(" << andExp->toString() << ") = " << z->evalTree(treeAndEp) << endl;
    cout << "z(" << notBandnotAandB->toString() << ") = " << z->evalTree(treenotBandnotAandB) << endl;
    cout << "z(" << AorB->toString() << ") = " << z->evalTree(treeAorB) << endl;

    vector<shared_ptr<Formula>> sigma1 = {AorB, notA, notB};
    cout << "set: {";
    for (auto it : sigma1)
    {
        cout << it->toString() << " ";
    }
    cout << "}" << endl;
    string answer1 = z->models(sigma1) ? "models" : "doesn't model";
    cout << "z " << answer1 << " the set" << endl;

    vector<shared_ptr<Formula>> sigma2 = {AorB, notA};
    cout << "set: {";
    for (auto it : sigma2)
    {
        cout << it->toString() << " ";
    }
    cout << "}" << endl;
    string answer2 = z->models(sigma2) ? "models" : "doesn't model";
    cout << "z " << answer2 << " the set" << endl;

    return 0;
}