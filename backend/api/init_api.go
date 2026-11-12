package api

import (
	"fmt"
	"log"
	"medical-device/backend/api/endpoints"
	"medical-device/backend/api/middleware"
	"net/http"
)

func InitAPI(a *endpoints.API) {
	const (
		postLimit = 1000
		provisionLimit = 100
	)

	limitedPost := middleware.NewRateLimiter(postLimit).RateLimit(http.HandlerFunc(a.PostAlert))
	limitedProvision := middleware.NewRateLimiter(provisionLimit).RateLimit(http.HandlerFunc(a.ProvisionDevice))

	authenticatedPost := middleware.Authenticate(a, limitedPost)

	http.Handle("/post_alert", authenticatedPost)
	http.Handle("/provision_device", limitedProvision)
}

func StartServer(isHTTP bool, port int) {
	if isHTTP {
		address := fmt.Sprintf("127.0.0.1:%d", port)
		log.Printf("Starting HTTP server at http://%s\n", address)
		if err := http.ListenAndServe(address, nil); err != nil {
			log.Fatalf("Error starting HTTP server: %v", err)
		}
	}
}