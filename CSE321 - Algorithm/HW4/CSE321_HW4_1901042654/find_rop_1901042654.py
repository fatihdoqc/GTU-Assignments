
arr = [ 1 , 6 , 5 , 4 ]

counter = 0


def merge(arr , left , mid , right):
    global counter
    i = left
    j = mid + 1

    for x in range(left , right):
        if (i > mid):
            j += 1
        elif (j > right):
            i += 1
        elif (arr[i] <= arr[j]):
            i += 1

        else:
            counter += mid + 1 - i
            j += 1

def updatedMergeSort(arr , left , right):

    if (left < right):
        mid = (left + right) // 2
        updatedMergeSort(arr , left, mid)
        updatedMergeSort(arr , mid + 1, right)
        merge(arr , left, mid, right)




updatedMergeSort(arr , 0 , len(arr) - 1 )
print(counter)

    