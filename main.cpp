#include "LTLFormula.h"

int main()
{
    shared_ptr<LTLFormula> a = make_shared<Atom>("a");
    shared_ptr<LTLFormula> b = make_shared<Atom>("b");
    shared_ptr<LTLFormula> notA = make_shared<Not>(a);
    shared_ptr<LTLFormula> notB = make_shared<Not>(b);
    shared_ptr<LTLFormula> andExp = make_shared<And>(notA, b);
    shared_ptr<LTLFormula> notBandnotAandB = make_shared<And>(notB, andExp);
    shared_ptr<LTLFormula> notAndExp = make_shared<Not>(andExp);

    cout << andExp->toString() << endl;
    cout << notBandnotAandB->toString() << endl;
    cout << notAndExp->toString() << endl;
    return 0;
}