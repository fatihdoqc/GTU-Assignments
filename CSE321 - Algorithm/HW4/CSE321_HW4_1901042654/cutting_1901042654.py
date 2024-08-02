
def cut(n ):
    count = 0
    while n > 1:
        count = count + 1
        n = round(n / 2)

    return count

print(cut(16))

