package api

import (
	"encoding/json"
	"log"
	"net/http"
)

func receivePost(w http.ResponseWriter, r *http.Request) {
	var alert Alert

	err := json.NewDecoder(r.Body).Decode(&alert)
	if err != nil {
		http.Error(w, "Invalid request body", http.StatusBadRequest)
		return
	}

	switch alert.AlertType {
		case alertSOS:
			err := sendEmailNotification(alert)
			if err != nil {
				log.Println("Error sending email notification: ", err)
				http.Error(w, "Failed to send email notification", http.StatusInternalServerError)
				return
			}
			LogAlert(alert)
		default:
			http.Error(w, "Invalid alert type", http.StatusBadRequest)
			return
	}

	w.WriteHeader(http.StatusOK)
}