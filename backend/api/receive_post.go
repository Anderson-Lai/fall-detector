package api

import (
	"encoding/json"
	"net/http"
)

type Alert struct {
	DeviceID string `json:"device_id"`
	AlertType alertType `json:"alert_type"`
	Coordinates coordinates `json:"coordinates"`
}

type alertType string
const (
	alertSOS alertType = "SOS"
)
type coordinates struct {
	Latitude, Longitude float64
}

func receivePost(w http.ResponseWriter, r *http.Request) {
	var alert Alert

	err := json.NewDecoder(r.Body).Decode(&alert)
	if err != nil {
		http.Error(w, "Invalid request body", http.StatusBadRequest)
		return
	}

	switch alert.AlertType {
		case alertSOS:
			// TODO: handle SOS alert; email and/or sms
		default:
			http.Error(w, "Invalid alert type", http.StatusBadRequest)
			return
	}

	w.WriteHeader(http.StatusOK)
}
