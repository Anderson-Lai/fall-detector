package endpoints

import (
	"bytes"
	"encoding/json"
	"medical-device/backend/api/types"
	"net/http"
	"testing"
	"time"
)

func TestPostAlert(t *testing.T) {
	data := types.Alert{
		DeviceID: "test-device",
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

	request, err := http.NewRequest(http.MethodPost, "http://localhost:8080/post_alert", bytes.NewBuffer(body))
	if err != nil {
		t.Fatalf("Error creating request: %v", err)
	}
	request.Header.Set("Content-Type", "application/json")
	// safe to commit since these are test credentials and database is local
	request.Header.Set("device_id", "c348737e-c432-452f-a01e-7c9b0b255e21")
	request.Header.Set("api_key", "7c415cb06ea369fb475a11e88f30f73dbb5060c9a6b94e8c7809858ac1d05a1b")
	client := &http.Client{
		Timeout: 5 * time.Second,
	}

	resp, err := client.Do(request)
	if err != nil {
		t.Fatalf("Error sending request: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		t.Errorf("Expected status code %d, got %d", http.StatusOK, resp.StatusCode)
	} else {
		t.Logf("Received expected status code %d", resp.StatusCode)
	}
}