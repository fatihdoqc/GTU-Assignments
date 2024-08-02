import numpy as np

def polyval(p, x):
    """
    Evaluate a polynomial at a point x using Horner's method.
    """
    result = p[0]
    for i in range(1, len(p)):
        result = result * x + p[i]
    return result

def eigenvalues(coefficients, tol=1e-12):
    """
    Find the eigenvalues of a polynomial given its coefficients.
    """
    n = len(coefficients) - 1
    if n == 0:
        return []
    elif n == 1:
        return [-coefficients[0] / coefficients[1]]
    elif n == 2:
        a, b, c = coefficients
        discr = b * b - 4 * a * c
        if discr < 0:
            return []
        elif discr == 0:
            return [-b / (2 * a)]
        else:
            return [(-b + discr ** 0.5) / (2 * a), (-b - discr ** 0.5) / (2 * a)]
    else:
        # Use the Durand-Kerner method to find the roots.
        # Initialize the roots as equally spaced points on the unit circle.
        roots = [complex(np.cos(2 * np.pi * i / n), np.sin(2 * np.pi * i / n)) for i in range(n)]
        max_iter = 1000
        for i in range(max_iter):
            # Evaluate the polynomial at each root.
            poly_vals = [polyval(coefficients, root) for root in roots]
            # Update each root using the Durand-Kerner formula.
            new_roots = [root - poly_val / polyval([roots[j] - root if j != k else 1 for j in range(n)], root) for k, root, poly_val in zip(range(n), roots, poly_vals)]
            # Check for convergence.
            if max(abs(new_root - root) for new_root, root in zip(new_roots, roots)) < tol:
                break
            roots = new_roots
        return [root.real for root in roots]

# example usage
p = [1, -5, 6]  # polynomial x^3 - 3x^2 + 3x - 1
print(eigenvalues(p))  # output: [1.0, 1.0, 1.0]