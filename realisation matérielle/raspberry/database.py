import sqlite3


def open_data():
    database_connection = sqlite3.connect("comm_database.db")
    cursor = database_connection.cursor()
    cursor.execute(
        """CREATE TABLE IF NOT EXISTS mqtt_data
                  (topic TEXT, value TEXT)"""
    )

    database_connection.commit()

    cursor.close()
    database_connection.close()


def insert_data(topic, value):
    conn = sqlite3.connect("comm_database.db")
    cursor = conn.cursor()
    cursor.execute("INSERT INTO mqtt_data (topic, value) VALUES (?, ?)", (topic, value))
    conn.commit()
    cursor.close()
    conn.close()


def fetch_data(topic):
    conn = sqlite3.connect("comm_database.db")
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM mqtt_data WHERE topic=?", (topic,))
    rows = cursor.fetchall()

    data_list = []
    for row in rows:
        data_list.append({"topic": row[0], "value": row[1]})

    cursor.close()
    conn.close()
    return data_list[len(data_list) - 1]
