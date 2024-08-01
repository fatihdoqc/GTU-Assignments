import sqlite3
import os

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()


cursor.execute("DELETE FROM Airlines WHERE airline_id = 1")

conn.commit()
conn.close()

