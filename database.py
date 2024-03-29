import sqlite3

database_connection = sqlite3.connect("comm_database.db")
cursor = database_connection.cursor()
cursor.execute("CREATE TABLE publishers(topic, photosensor, button, speaker, screen)")

def display_write(value, topic):
    cursor.execute("INSERT INTO publishers(screen) VALUES(str) WHERE publisher(topic) MATCH 'topic'")

def display_read():
    cursor.execute("SELECT publishers")

def speaker_write(value, topic):
    cursor.execute("INSERT INTO publishers(speaker) VALUES(str) WHERE publisher(topic) MATCH 'topic'")
    
def speaker_read():
    
def photo_read():

def button_read():
