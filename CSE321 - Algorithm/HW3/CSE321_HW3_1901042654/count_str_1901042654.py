
def count_words(word , first , last ):
    count = 0
    for x in range(len(word)):
        if(word[x] == first):
            for y in range(x + 1, len(word)):
                if word[y] == last:

                    count = count + 1

    return count

word = "arabamavar"
print("for word: " + word + " first: a , last: r  => " + str(count_words(word , "a" , "r")))

word = "TXZXXJZWX"
print("for word: " + word + " first: X , last: Z  => "  + str(count_words(word , "X" , "Z")))


