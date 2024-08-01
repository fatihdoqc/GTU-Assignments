import sqlite3

def print_query_results(query_title, rows):
    print(f"\n{query_title}:")
    if len(rows) == 0:
        print("No results found.")
        return
    
    # Get column names
    columns = [description[0] for description in cursor.description]
    
    # Calculate maximum width for each column
    max_lengths = [len(column) for column in columns]
    for row in rows:
        for i, value in enumerate(row):
            max_lengths[i] = max(max_lengths[i], len(str(value)))
    
    # Print column headers
    header_format = ' | '.join(f"{columns[i]:<{max_lengths[i]}}" for i in range(len(columns)))
    print(header_format)
    print('-' * len(header_format))
    
    # Print rows
    for row in rows:
        row_format = ' | '.join(f"{str(row[i]):<{max_lengths[i]}}" for i in range(len(columns)))
        print(row_format)

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()

cursor.execute('''
    SELECT *
    FROM Airlines
''')

rows = cursor.fetchall()
print_query_results("Airlines", rows)

cursor.execute('''
    SELECT *
    FROM Flights
''')

rows = cursor.fetchall()
print_query_results("Flights", rows)

cursor.execute('''
    SELECT *
    FROM Passengers
''')

rows = cursor.fetchall()
print_query_results("Passengers", rows)

cursor.execute('''
    SELECT *
    FROM Employees
''')

rows = cursor.fetchall()
print_query_results("Employees", rows)

cursor.execute('''
    SELECT *
    FROM Bookings
''')

rows = cursor.fetchall()
print_query_results("Bookings", rows)

