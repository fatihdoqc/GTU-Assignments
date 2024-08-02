Commands: (position_column position_row ) EXIT - SAVE (file_name) - LOAD (file_name)

When program asks user for size of board ,if user enters "EXIT" program enters infinite loop.

EXIT only works when you can enter position.

I used string.find() function to get commands. So when you enter "qwjrqwbwqtubqLOAD file.txt" , program will LOAD file.txt.

Again , because of string.find() function, when you enter LOADSAVE file.txt.

Board size must be larger than 5 and lesser than 30.
