package main

import (
	"medical-device/backend/api"
)

const IS_HTTP = true
const PORT = 8080

func main() {
	api.InitAPI()
	api.InitAlertLogging()
	api.StartServer(IS_HTTP, PORT)
}