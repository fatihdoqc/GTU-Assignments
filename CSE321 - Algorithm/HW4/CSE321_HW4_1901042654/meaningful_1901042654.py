

experiments = [ 15 , 30 ,8 , 50 , 90 , 70 , 100 , 1 , 3 ]


def meaningful(arr, k, n):
    # Minimum and maximum element from the array
    low = min(arr);
    high = max(arr);

    # Modified binary search
    while (low <= high):

        mid = low + (high - low) // 2;

        # count of
        countless = 0;  # elements less than mid
        countequal = 0; # elements equal to mid

        for i in range(n):
            if (arr[i] < mid):
                countless += 1;

            elif (arr[i] == mid):
                countequal += 1;

        # If mid is the first meaningful kth experiment
        if (countless < k and (countless + countequal) >= k):
            return mid;

        # If the required element is less than mid
        elif (countless >= k):
            high = mid - 1;

        # If the required element is greater than mid
        elif (countless < k and countless + countequal < k):
            low = mid + 1;

print(meaningful(experiments , 9 , len(experiments) ))