package api

import (
	"fmt"
	"log"
	"medical-device/backend/api/endpoints"
	"net/http"
)

func InitAPI() {
	http.HandleFunc("/post_alert", endpoints.PostAlert)
}

func StartServer(isHTTP bool, port int) {
	if isHTTP {
		portStr := fmt.Sprintf(":%d", port)
		log.Printf("Starting HTTP server at http://localhost%s\n", portStr)
		http.ListenAndServe(portStr, nil)
	}
}