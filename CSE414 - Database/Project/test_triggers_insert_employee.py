import sqlite3
import os

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()

cursor.execute("INSERT INTO Employees (name, airline_id, position, hire_date) VALUES ('Qwerty Asd', 1,  'Pilot', '2020-01-01')")

conn.commit()
conn.close()

