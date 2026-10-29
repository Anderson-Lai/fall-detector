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

	limitedPost := middleware.NewRateLimiter(postLimit).RateLimit(http.HandlerFunc(d.PostAlert))
	limitedProvision := middleware.NewRateLimiter(provisionLimit).RateLimit(http.HandlerFunc(d.ProvisionDevice))

	authenticatedPost := middleware.Authenticate(d, limitedPost)

	http.Handle("/post_alert", authenticatedPost)
	http.Handle("/provision_device", limitedProvision)
}

func StartServer(isHTTP bool, port int) {
	if isHTTP {
		portStr := fmt.Sprintf(":%d", port)
		log.Printf("Starting HTTP server at http://localhost%s\n", portStr)
		http.ListenAndServe(portStr, nil)
	}
}