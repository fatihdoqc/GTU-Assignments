
def bruteforce(x , n ):
    result = 1;
    for a in range(n):
        result *= x

    return result

print(bruteforce(2,5))


def div_conq(x , n):

    if n == 1:
        return x

    if(n % 2 == 0): # when dividing the problem into subproblems.
                    # If n is a odd number, one x will be out of the range of that if-block
        return div_conq(x, n // 2) * div_conq(x, n // 2)
    else:
        return x * div_conq(x, n // 2) * div_conq(x, n // 2)


print(div_conq(2,4))