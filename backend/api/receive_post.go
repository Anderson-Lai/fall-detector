package api

import (
	"encoding/json"
	"net/http"
)

type alertStatus string
const (
	AlertSOS alertStatus = "SOS"
)

type coordinates struct {
	Latitude, Longitude float64
}

type requestBody struct {
	DeviceID string `json:"device_id"`
	AlertType alertStatus `json:"alert_type"`
	Coordinates coordinates `json:"coordinates"`
}

func receivePost(w http.ResponseWriter, r *http.Request) {
	var alert requestBody

	err := json.NewDecoder(r.Body).Decode(&alert)
	if err != nil {
		http.Error(w, "Invalid request body", http.StatusBadRequest)
		return
	}

	switch alert.AlertType {
		case AlertSOS:
			// TODO: handle SOS alert; email and/or sms
		default:
			http.Error(w, "Invalid alert type", http.StatusBadRequest)
			return
	}

	w.WriteHeader(http.StatusOK)
}
