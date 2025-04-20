#include <iostream>
#include <ginac/ginac.h>

using namespace std;
using namespace GiNaC;

int main() {
    // Declare symbolic variables
    symbol a("a"), b("b"), c("c"), d("d");

    // Example expressions using trigonometric identities
    ex expr1 = sin(a)*cos(b) + sin(b)*cos(a);     // should simplify to sin(a + b)
    ex expr2 = cos(a)*cos(b) - sin(a)*sin(b);     // should simplify to cos(a + b)
    ex expr3 = cos(a)*cos(b) + sin(a)*sin(b);     // should simplify to cos(a - b)
    ex expr4 = sin(a)*cos(b) - sin(b)*cos(a);     // should simplify to sin(a - b)
    ex expr5 = sin(c)*cos(d) - sin(d)*cos(c);     // should simplify to sin(c - d)

    // Define wildcard symbols for general pattern matching
    ex x = wild(0);  // placeholder for any expression
    ex y = wild(1);  // another placeholder

    // Create a list of trigonometric identity rules using wildcards
    lst rules;
    rules.append(sin(x)*cos(y) + sin(y)*cos(x) == sin(x + y));   // sin(x)cos(y) + sin(y)cos(x) = sin(x + y)
    rules.append(cos(x)*cos(y) - sin(x)*sin(y) == cos(x + y));   // cos(x)cos(y) - sin(x)sin(y) = cos(x + y)
    rules.append(cos(x)*cos(y) + sin(x)*sin(y) == cos(x - y));   // cos(x)cos(y) + sin(x)sin(y) = cos(x - y)
    rules.append(sin(x)*cos(y) - sin(y)*cos(x) == sin(x - y));   // sin(x)cos(y) - sin(y)cos(x) = sin(x - y)

    // Apply substitution rules to each expression using algebraic matching
    cout << "1. Simplified sin(a)*cos(b) + sin(b)*cos(a): " << expr1.subs(rules, subs_options::algebraic) << endl;
    cout << "2. Simplified cos(a)*cos(b) - sin(a)*sin(b): " << expr2.subs(rules, subs_options::algebraic) << endl;
    cout << "3. Simplified cos(a)*cos(b) + sin(a)*sin(b): " << expr3.subs(rules, subs_options::algebraic) << endl;
    cout << "4. Simplified sin(a)*cos(b) - sin(b)*cos(a): " << expr4.subs(rules, subs_options::algebraic) << endl;
    cout << "5. Simplified sin(c)*cos(d) - sin(d)*cos(c): " << expr5.subs(rules, subs_options::algebraic) << endl;

    return 0;
}
