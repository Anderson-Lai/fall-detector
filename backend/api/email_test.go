package api

import (
	"testing"
)

func TestSendEmailNotification(t *testing.T) {
	alert := Alert{
		DeviceID:  "test-device",
		AlertType: alertSOS,
		Coordinates: coordinates{
			Latitude:  37.7749,
			Longitude: -122.4194,
		},
	}

	err := sendEmailNotification(alert)
	if err != nil {
		t.Errorf("sendEmailNotification failed: %v", err)
	}
}