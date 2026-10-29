package main

import (
	"log"
	"medical-device/backend/api"

	"github.com/joho/godotenv"
)

const IS_HTTP = true
const PORT = 8080
	
func main() {
	if err := godotenv.Load(); err != nil {
		log.Fatal("Error loading .env file: ", err)
	}

	api.InitAPI()
	api.InitAlertLogging()
	api.StartServer(IS_HTTP, PORT)
}