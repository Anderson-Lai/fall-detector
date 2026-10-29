package api

import (
	"fmt"
	"log"
	"medical-device/backend/api/endpoints"
	"net/http"
)

func InitAPI(d *endpoints.Database) {
	http.HandleFunc("/post_alert", d.PostAlert)
	http.HandleFunc("/provision_device", d.ProvisionDevice)
}

func StartServer(isHTTP bool, port int) {
	if isHTTP {
		portStr := fmt.Sprintf(":%d", port)
		log.Printf("Starting HTTP server at http://localhost%s\n", portStr)
		http.ListenAndServe(portStr, nil)
	}
}