package endpoints

import (
	"bytes"
	"encoding/json"
	"medical-device/backend/api/types"
	"net/http"
	"testing"
)

func TestPostAlert(t *testing.T) {
	data := types.Alert{
		DeviceID:  "test-device",
		AlertType: types.AlertSOS,
		Coordinates: types.Coordinates{
			Latitude:  37.7749,
			Longitude: -122.4194,
		},
	}

	body, err := json.Marshal(data)
	if err != nil {
		t.Fatalf("Error marshaling data: %v", err)
	}

	req, err := http.Post("http://localhost:8080/post_alert", "application/json", bytes.NewReader(body))
	if err != nil {
		t.Fatalf("Error creating request: %v", err)
	}
	defer req.Body.Close()

	if req.StatusCode != http.StatusOK {
		t.Errorf("Expected status code %d, got %d", http.StatusOK, req.StatusCode)
	} else {
		t.Logf("Received expected status code %d", req.StatusCode)
	}
}