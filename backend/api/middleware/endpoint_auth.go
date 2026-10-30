package middleware

import (
	"database/sql"
	"errors"
	"log"
	"medical-device/backend/api/endpoints"
	"net/http"
)

func Authenticate(a *endpoints.API, next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		apiKey := r.Header.Get("api_key")
		deviceID := r.Header.Get("device_id")

		row := a.DB.QueryRow(`SELECT device_id, api_key FROM devices WHERE 
			device_id = (?) AND api_key = (?)`, deviceID, endpoints.HashAPIKey(apiKey))

		err := row.Scan(new(string), new(string))
		if err != nil {
			if errors.Is(err, sql.ErrNoRows) {
                log.Println("Authentication failed for device_id: ", deviceID)
                http.Error(w, "Unauthorized", http.StatusUnauthorized)
                return
            }

            log.Println("Database error during authentication: ", err)
            http.Error(w, "Internal server error", http.StatusInternalServerError)
            return
		}

		next.ServeHTTP(w, r)
	})
}