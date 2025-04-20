# simplify_expr.py
import sys
from sympy import simplify, symbols, sin, cos, tan, sympify

def main():
    # Define variables from a to z
    variables = {chr(i): symbols(chr(i)) for i in range(ord('a'), ord('z')+1)}
    
    # Add trigonometric functions to the evaluation environment
    env = {
        **variables,
        "sin": sin,
        "cos": cos,
        "tan": tan
    }

    # Get the expression from the command line
    expr_str = sys.argv[1]

    try:
        expr = sympify(expr_str, locals=env)
        simplified = simplify(expr)
        print(simplified)
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
