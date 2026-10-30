package main

import (
	"log"
	"medical-device/backend/api"
	"medical-device/backend/api/endpoints"
	"medical-device/backend/api/logging"

	"github.com/joho/godotenv"
)

const IS_HTTP = true
const PORT = 8080
	
func main() {
	if err := godotenv.Load(); err != nil {
		log.Fatal("Error loading .env file: ", err)
	}

	resources := &endpoints.API{
		DB: endpoints.InitializeDatabase(),
	}
	defer resources.DB.Close()

	logging.InitAlertLogging()
	api.InitAPI(resources)

	api.StartServer(IS_HTTP, PORT)
}