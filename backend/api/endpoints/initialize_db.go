package endpoints

import (
	"database/sql"
	"log"

	_ "modernc.org/sqlite"
)

type Database struct {
	DB *sql.DB
}

// creates a database if necessary and returns a connection to the database
func InitializeDatabase() *sql.DB {
	db, err := sql.Open("sqlite", "medical_device.db")
	if err != nil {
		log.Fatal("Failed to open database: ", err)
	}

	if err := db.Ping(); err != nil {
		log.Fatal("Failed to connect to database: ", err)
	}

	db.Exec(`CREATE TABLE IF NOT EXISTS devices (
		device_id TEXT PRIMARY KEY,
		api_key TEXT NOT NULL
	)`)

	return db
}