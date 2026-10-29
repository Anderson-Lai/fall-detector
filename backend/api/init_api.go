package api

import (
	"fmt"
	"log"
	"medical-device/backend/api/endpoints"
	"medical-device/backend/api/middleware"
	"net/http"
)



func InitAPI(d *endpoints.Database) {
	const (
		postLimit = 1000
		provisionLimit = 100
	)

	postRL := middleware.NewRateLimiter(postLimit)
	provisionRL := middleware.NewRateLimiter(provisionLimit)

	http.Handle("/post_alert", postRL.RateLimit(http.HandlerFunc(d.PostAlert)))
	http.Handle("/provision_device", provisionRL.RateLimit(http.HandlerFunc(d.ProvisionDevice)))
}

func StartServer(isHTTP bool, port int) {
	if isHTTP {
		portStr := fmt.Sprintf(":%d", port)
		log.Printf("Starting HTTP server at http://localhost%s\n", portStr)
		http.ListenAndServe(portStr, nil)
	}
}