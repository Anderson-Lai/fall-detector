package api

import (
	"encoding/json"
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
			// TODO: handle SOS alert; email and/or sms
		default:
			http.Error(w, "Invalid alert type", http.StatusBadRequest)
			return
	}

	w.WriteHeader(http.StatusOK)
}
