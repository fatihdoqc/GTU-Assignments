import sqlite3
import os

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()

cursor.execute("UPDATE Bookings SET flight_id = 50 WHERE booking_id = 1")

conn.commit()
conn.close()

