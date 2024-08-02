

coefs = [3 , 4 , -2] # coefficients a_n , a_n-1 ...

def calculate(x_0):
    total = 0
    n = len(coefs)
    for a in range(n):
        total = total + ( coefs[a] * pow(x_0 , n - a - 1))
    return total

print(calculate(2))