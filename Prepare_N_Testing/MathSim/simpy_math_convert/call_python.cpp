#include <iostream>
#include <string>
#include <cstdlib>   // system
#include <sstream>
#include <array>

using namespace std;

// Function to run the Python script and get the result from stdout
string simplify_with_python(const string& expr) {
    string command = "python3 simplify_expr.py \"" + expr + "\"";
    array<char, 128> buffer;
    string result;
    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe) return "Error when calling Python";

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);
    return result;
}

int main() {
    // Complex expressions with sin, cos, and algebraic operations
    string expr1 = "sin(a)*cos(b) + sin(b)*cos(a) + cos(a)*cos(b)";
    string expr2 = "(sin(a + b) + cos(c + d)) * (sin(e + f) + cos(g + h))";
    string expr3 = "(sin(a) + cos(b)) * (sin(c) - cos(d)) + (sin(e) + cos(f))";
    string expr4 = "sin(a*b + c*d) * cos(a*b - c*d)";
    string expr5 = "sin(a + b + c) * cos(a - b - c)";
    string expr6 = "(sin(a) * cos(b) + cos(a) * sin(b)) * (sin(c) * cos(d) + cos(c) * sin(d))";

    // Print the original expressions
    cout << "Original expression 1: " << expr1 << endl;
    cout << "Original expression 2: " << expr2 << endl;
    cout << "Original expression 3: " << expr3 << endl;
    cout << "Original expression 4: " << expr4 << endl;
    cout << "Original expression 5: " << expr5 << endl;
    cout << "Original expression 6: " << expr6 << endl;

    // Call Python to simplify the expressions
    string simplified1 = simplify_with_python(expr1);
    string simplified2 = simplify_with_python(expr2);
    string simplified3 = simplify_with_python(expr3);
    string simplified4 = simplify_with_python(expr4);
    string simplified5 = simplify_with_python(expr5);
    string simplified6 = simplify_with_python(expr6);

    // Print the simplified results
    cout << "Simplified expression 1: " << simplified1 << endl;
    cout << "Simplified expression 2: " << simplified2 << endl;
    cout << "Simplified expression 3: " << simplified3 << endl;
    cout << "Simplified expression 4: " << simplified4 << endl;
    cout << "Simplified expression 5: " << simplified5 << endl;
    cout << "Simplified expression 6: " << simplified6 << endl;

    return 0;
}
