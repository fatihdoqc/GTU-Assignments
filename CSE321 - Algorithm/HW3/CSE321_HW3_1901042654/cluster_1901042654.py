regions = ["A", "B", "C", "D", "E", "F", "G"]
profits = [3, -5, 2, 11, -8, 9, -5]


def cluster_a():
    current = 0
    max = -9999999
    curr_path = []
    max_path = []
    for x in range(len(regions)):
        current = profits[x]
        curr_path.clear()
        curr_path.append(regions[x])
        for y in range(x + 1, len(regions)):
            current = current + profits[y]
            curr_path.append(regions[y])
            if current > max:
                max_path = curr_path.copy()
                max = current

    print(max_path)


print("5-a")
cluster_a()


# --------------------------QUESTION 5 PART B------------------------------------------------


def maxClusterConnected(l, m, r):  # left middle right

    temp = 0
    left_total = -9999999
    right_total = -9999999

    for x in range(m, l - 1, -1):
        temp = temp + profits[x]
        if temp > left_total:
            left_total = temp

    temp = 0
    for x in range(m + 1, r + 1):
        temp = temp + profits[x]
        if temp > right_total:
            right_total = temp

    return max(left_total + right_total, left_total, right_total)  # return the biggest one among them


def cluster_b(l, r):
    if l == r:
        return profits[l]

    m = (l + r) // 2

    return max(cluster_b(l, m), cluster_b(m + 1, r), maxClusterConnected(l, m, r))


print("\nPart 5-b: ",  cluster_b(0, len(profits) - 1))
