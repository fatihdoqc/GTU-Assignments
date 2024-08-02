Commands: (position_column position_row ) - UNDO - EXIT - SAVE (file_name) - LOAD (file_name)

There is a little bug; when program asks user for size of board and when user enters "EXIT" program enters infinite loop. Please don't.

EXIT only works when you can enter position.

I used string.find() function to get commands. So when you enter "qwjrqwbwqtubqLOAD file.txt" , program will LOAD file.txt.

Again , because of string.find() function, when you enter LOADSAVE file.txt. No one can know what will happen.Program doesn't behaves right.

I don't have menu. So if you want to compare games ,you need to include my class and header files and do it by your own in your main.