import sqlite3
import os

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()

cursor.execute("DELETE FROM Passengers WHERE passenger_id = 4")

conn.commit()
conn.close()

