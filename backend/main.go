package main

import (
	"medical-device/backend/api"
)

const PORT = 8080
const IS_HTTP = true

func main() {
	api.InitAPI()
	api.StartServer(IS_HTTP, PORT)
}