

name =      ["English" , "Mathematic" , "Physics" , "Chemistry" , "Biology" , "Geography" ]
start =     [   1 ,           3 ,          0 ,          5 ,         8 ,            5      ]
finish =    [   2 ,           4 ,          6 ,          7 ,         9 ,            9      ]

def MaxActivities(start , finish ):

    i = 0           # First course
    print(name[i])

    for x in range( len(finish) ):

        # If this activity has start time >= finish time
        # of previously selected activity, then print it
        if start[x] >= finish[i]:
            print(name[x] + " ")
            i = x

MaxActivities(start , finish)