import sqlite3

conn = sqlite3.connect('airport.db')
cursor = conn.cursor()

cursor.execute('''
    DROP TRIGGER IF EXISTS cascade_delete_bookings;
''')

cursor.execute('''
               
    CREATE TRIGGER cascade_delete_bookings
    AFTER DELETE ON Passengers
    FOR EACH ROW
    BEGIN
        DELETE FROM Bookings
        WHERE passenger_id = OLD.passenger_id;
    END;
''')

cursor.execute('''
    DROP TRIGGER IF EXISTS enforce_referential_integrity;
''')

cursor.execute('''
               
    CREATE TRIGGER enforce_referential_integrity
    BEFORE INSERT ON Bookings
    FOR EACH ROW
    BEGIN
        SELECT RAISE(ABORT, 'Invalid flight_id or passenger_id')
        WHERE (SELECT COUNT(*) FROM Flights WHERE flight_id = NEW.flight_id) = 0
        OR (SELECT COUNT(*) FROM Passengers WHERE passenger_id = NEW.passenger_id) = 0;
    END;
''')

cursor.execute('''
    DROP TRIGGER IF EXISTS update_enforce_referential_integrity;
''')

cursor.execute('''
               
    CREATE TRIGGER update_enforce_referential_integrity
    BEFORE UPDATE ON Bookings
    FOR EACH ROW
    BEGIN
        SELECT RAISE(ABORT, 'Invalid flight_id or passenger_id')
        WHERE (SELECT COUNT(*) FROM Flights WHERE flight_id = NEW.flight_id) = 0
        OR (SELECT COUNT(*) FROM Passengers WHERE passenger_id = NEW.passenger_id) = 0;
    END;
''')

cursor.execute('''
    DROP TRIGGER IF EXISTS assign_employee_id;
''')

cursor.execute('''
    CREATE TRIGGER assign_employee_id
    AFTER INSERT ON Employees
    BEGIN
        UPDATE Employees
        SET employee_id = COALESCE((SELECT MAX(employee_id) FROM Employees), 0)
        WHERE rowid = NEW.rowid;
    END;
''')

cursor.execute('''
    DROP TRIGGER IF EXISTS prevent_delete_airline_with_employees;
''')

cursor.execute('''
    CREATE TRIGGER prevent_delete_airline_with_employees
    BEFORE DELETE ON Airlines
    FOR EACH ROW
    WHEN EXISTS (SELECT 1 FROM Employees WHERE airline_id = OLD.airline_id)
    BEGIN
        SELECT RAISE(ABORT, 'Cannot delete airline with employees');
    END;
''')

conn.commit()
conn.close()

