package main

import (
	"medical-device/backend/api"
)

const PORT = 8080

func main() {
	api.InitAPI(true, PORT)
}