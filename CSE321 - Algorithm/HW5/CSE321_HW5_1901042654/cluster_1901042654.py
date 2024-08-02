regions = ["A", "B", "C", "D", "E", "F", "G"]
profits = [3, -5, 2, 11, -8, 9, -5]

def max_cluster(arr):

    total_max = []
    total_max.append( arr[0] )
    curr_max= arr[0]

    for x in range(1, len(arr)):
        # Select the maximum among current index or last max + current index
        curr_max = max(arr[x], curr_max + arr[x])
        print("curr max: ",curr_max)
        total_max.append( max(total_max[x-1], curr_max ))

    print(total_max)
    return total_max[len(total_max) - 1]

print( max_cluster(profits))