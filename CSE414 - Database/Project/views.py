import sqlite3
import os

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()

cursor.execute('''
    CREATE VIEW Passenger_Bookings AS
    SELECT p.passenger_id, p.name AS passenger_name, p.passport_number, 
        b.booking_id, b.flight_id, b.seat_number, b.booking_time,
        f.origin, f.destination, f.departure_time, f.arrival_time
    FROM Passengers p
    INNER JOIN Bookings b ON p.passenger_id = b.passenger_id
    INNER JOIN Flights f ON b.flight_id = f.flight_id;
''')

cursor.execute('''
    CREATE VIEW Employee_Airlines AS
    SELECT e.employee_id, e.name AS employee_name, e.position, e.hire_date,
        a.name AS airline_name, a.country
    FROM Employees e
    INNER JOIN Airlines a ON e.airline_id = a.airline_id;
''')

cursor.execute('''
    CREATE VIEW Flight_Schedule AS
    SELECT f.flight_id, f.airline_id, a.name AS airline_name, a.country AS airline_country,
        f.origin, f.destination, f.departure_time, f.arrival_time
    FROM Flights f
    INNER JOIN Airlines a ON f.airline_id = a.airline_id;
''')

cursor.execute('''
    CREATE VIEW Booking_Statistics AS
    SELECT f.flight_id, f.origin, f.destination,
        COUNT(b.booking_id) AS total_bookings,
        MAX(b.booking_time) AS latest_booking_time
    FROM Flights f
    LEFT JOIN Bookings b ON f.flight_id = b.flight_id
    GROUP BY f.flight_id, f.origin, f.destination;
''')

cursor.execute('''
   CREATE VIEW Upcoming_Flights AS
    SELECT flight_id, airline_id, origin, destination, departure_time, arrival_time
    FROM Flights
    WHERE departure_time > DATETIME('now');
''')


conn.commit()
conn.close()

