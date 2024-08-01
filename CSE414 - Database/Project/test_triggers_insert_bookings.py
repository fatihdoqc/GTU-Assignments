import sqlite3
import os

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()

cursor.execute("INSERT INTO Bookings (flight_id, passenger_id, seat_number, booking_time) VALUES (7, 1, '12A', '2024-06-14 12:00')")

conn.commit()
conn.close()

