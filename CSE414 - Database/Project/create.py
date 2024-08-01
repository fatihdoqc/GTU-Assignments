import sqlite3

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()

cursor.execute('''
    CREATE TABLE IF NOT EXISTS Airlines (
        airline_id INTEGER PRIMARY KEY,
        name TEXT,
        country TEXT
    )
''')

cursor.execute('''
    CREATE TABLE IF NOT EXISTS Flights (
        flight_id INTEGER PRIMARY KEY,
        airline_id INTEGER,
        origin TEXT,
        destination TEXT,
        departure_time TEXT,
        arrival_time TEXT,
        FOREIGN KEY (airline_id) REFERENCES Airlines (airline_id)
    )
''')

cursor.execute('''
    CREATE TABLE IF NOT EXISTS Passengers (
        passenger_id INTEGER PRIMARY KEY,
        name TEXT,
        passport_number TEXT
    )
''')

cursor.execute('''
    CREATE TABLE IF NOT EXISTS Bookings (
        booking_id INTEGER PRIMARY KEY,
        flight_id INTEGER,
        passenger_id INTEGER,
        seat_number TEXT,
        booking_time TEXT,
        FOREIGN KEY (flight_id) REFERENCES Flights (flight_id),
        FOREIGN KEY (passenger_id) REFERENCES Passengers (passenger_id)
    )
''')

cursor.execute('''
    CREATE TABLE IF NOT EXISTS Employees (
        employee_id INTEGER PRIMARY KEY,
        airline_id INTEGER,
        name TEXT,
        position TEXT,
        hire_date TEXT,
        FOREIGN KEY (airline_id) REFERENCES Airlines (airline_id)
    )
''')

cursor.execute("INSERT INTO Airlines (name, country) VALUES ('Airline A', 'Country A')")
cursor.execute("INSERT INTO Airlines (name, country) VALUES ('Airline B', 'Country B')")
cursor.execute("INSERT INTO Airlines (name, country) VALUES ('Airline C', 'Country C')")

cursor.execute("INSERT INTO Flights (airline_id, origin, destination, departure_time, arrival_time) VALUES (1, 'City A', 'City B', '2024-06-12 08:00', '2024-06-15 10:00')")
cursor.execute("INSERT INTO Flights (airline_id, origin, destination, departure_time, arrival_time) VALUES (2, 'City C', 'City D', '2024-06-15 09:00', '2024-06-15 11:00')")
cursor.execute("INSERT INTO Flights (airline_id, origin, destination, departure_time, arrival_time) VALUES (1, 'City X', 'City T', '2024-06-17 11:00', '2024-06-18 11:00')")

cursor.execute("INSERT INTO Passengers (name, passport_number) VALUES ('John Doe', 'P1234567')")
cursor.execute("INSERT INTO Passengers (name, passport_number) VALUES ('Jane Smith', 'P7654321')")
cursor.execute("INSERT INTO Passengers (name, passport_number) VALUES ('Fatih Dogac', 'P1234569')")
cursor.execute("INSERT INTO Passengers (name, passport_number) VALUES ('Yunus Emre', 'P1236669')")

cursor.execute("INSERT INTO Bookings (flight_id, passenger_id, seat_number, booking_time) VALUES (1, 1, '12A', '2024-06-14 12:00')")
cursor.execute("INSERT INTO Bookings (flight_id, passenger_id, seat_number, booking_time) VALUES (2, 2, '14B', '2024-06-14 13:00')")
cursor.execute("INSERT INTO Bookings (flight_id, passenger_id, seat_number, booking_time) VALUES (2, 3, '14Z', '2024-06-14 14:00')")
cursor.execute("INSERT INTO Bookings (flight_id, passenger_id, seat_number, booking_time) VALUES (3, 4, '17C', '2024-06-14 15:00')")
cursor.execute("INSERT INTO Bookings (flight_id, passenger_id, seat_number, booking_time) VALUES (3, 2, '21X', '2024-06-14 16:00')")
cursor.execute("INSERT INTO Bookings (flight_id, passenger_id, seat_number, booking_time) VALUES (4, 2, '40S', '2024-06-14 17:00')")

cursor.execute("INSERT INTO Employees (name, airline_id, position, hire_date) VALUES ('Alice Johnson', 1,  'Pilot', '2020-01-01')")
cursor.execute("INSERT INTO Employees (name, airline_id, position, hire_date) VALUES ('Bob Brown', 2, 'Ground Staff', '2021-02-15')")
cursor.execute("INSERT INTO Employees (name, airline_id, position, hire_date) VALUES ('Lebron James', 1, 'Janitor', '2021-02-20')")
cursor.execute("INSERT INTO Employees (name, airline_id, position, hire_date) VALUES ('Mike Tyson', 3, 'Security', '2021-02-10')")

conn.commit()
conn.close()
