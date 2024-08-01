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
    LEFT OUTER JOIN Flights ON Airlines.airline_id = Flights.airline_id
''')

rows = cursor.fetchall()
print_query_results("Left Outer Join (Airlines - Flight)", rows)

#Right Outer Join
cursor.execute('''
    SELECT *
    FROM Flights
    LEFT OUTER JOIN Airlines ON Flights.airline_id = Airlines.airline_id
''')

rows = cursor.fetchall()
print_query_results("Right Outer Join (Airlines - Flights)", rows)

#Full outer join
cursor.execute('''
    SELECT *
    FROM Airlines
    LEFT OUTER JOIN Flights ON Airlines.airline_id = Flights.airline_id

    UNION

    SELECT *
    FROM Flights 
    LEFT OUTER JOIN Airlines ON Airlines.airline_id = Flights.airline_id
    WHERE Airlines.airline_id IS NULL
''')

rows = cursor.fetchall()
print_query_results("Full Outer Join (Airlines - Flights)", rows)

conn.commit()
conn.close()