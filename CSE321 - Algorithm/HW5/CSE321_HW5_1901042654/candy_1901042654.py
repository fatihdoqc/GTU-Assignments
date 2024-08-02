
length = [1, 2, 3, 4, 5, 6, 7, 8]
price = [ 1, 5, 8, 9, 10, 17, 17]

def max_price( n):
    total_max = []
    total_max.append(price[0])
    curr_max = price[0]

    for x in range(1,len(price)):
        curr_max = price[x - 1] + price[n-x -1]
        total_max.append( max(total_max[x-1], curr_max ))

    print(total_max)
    return total_max[ len(total_max) - 1 ]

print(max_price(8))