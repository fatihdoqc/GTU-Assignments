


experiments = [ 15 , 30 ,8 , 50 , 90 , 70 , 100 , 1 , 3 ]

def worst_best(arr , l , r):

    print( "Best test result is: " + str(best(arr , l , r)))
    print( "Worst test result is: " + str(worst(arr, l, r)))


def best(arr , l , r):
    if (l == r):
        return arr[l]

    m = (l + r) // 2

    return max(best(arr, l, m), best(arr, m + 1, r))

def worst(arr , l , r):
    if (l == r):
        return arr[l]

    m = (l + r) // 2

    return min(worst(arr, l, m), worst(arr, m + 1, r))

worst_best(experiments, 0, len(experiments) - 1)