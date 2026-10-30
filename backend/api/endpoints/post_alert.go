package endpoints

import (
	"encoding/json"
	"log"
	"medical-device/backend/api/logging"
	"medical-device/backend/api/notifications"
	"medical-device/backend/api/types"
	"net/http"
)

func (a *API) PostAlert(w http.ResponseWriter, r *http.Request) {
	var alert types.Alert

	err := json.NewDecoder(r.Body).Decode(&alert)
	if err != nil {
		http.Error(w, "Invalid request body", http.StatusBadRequest)
		return
	}

	switch alert.AlertType {
		case types.AlertSOS:
			err := notifications.SendEmailNotification(alert)
			if err != nil {
				log.Println("Error sending email notification: ", err)
				http.Error(w, "Failed to send email notification", http.StatusInternalServerError)
				return
			}
			if err := logging.LogAlert(alert); err != nil {
				log.Println("Error logging alert: ", err)
				http.Error(w, "Failed to log alert", http.StatusInternalServerError)
				return
			}
		default:
			http.Error(w, "Invalid alert type", http.StatusBadRequest)
			return
	}

	w.WriteHeader(http.StatusOK)
}