package notifications

import (
	"medical-device/backend/api/types"
	"testing"
)

func TestSendEmailNotification(t *testing.T) {
	alert := types.Alert{
		DeviceID:  "test-device",
		AlertType: types.AlertSOS,
		Coordinates: types.Coordinates{
			Latitude:  37.7749,
			Longitude: -122.4194,
		},
	}

	err := SendEmailNotification(alert)
	if err != nil {
		t.Errorf("SendEmailNotification failed: %v", err)
	}
}