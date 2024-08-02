

Profit = [ 5 , 8, 9, 10 ,1, 4 , 7]
Weight = [ 2 , 3, 4, 5, 2, 1 , 1]


def fill_box(values , weights , W ):

    def score(i):
        return values[i] / weights[i]

    items = sorted(range(len(values)), key=score, reverse=True) # Descending order , referenced by score function

    value = 0
    weight = 0

    for i in items:
        if weight + weights[i] <= W:
            weight += weights[i]
            value += values[i]
        else: # break the cheese into pieces
            value += (W - weight) / weights[i]

    return value

print(fill_box(Profit , Weight , 10))