package notifications

import (
	"medical-device/backend/api/types"
	"testing"
)

func TestSendEmailNotification(t *testing.T) {
	alert := types.Alert{
		DeviceID:  "test-device",
		AlertType: types.AlertSOS,
	}

	err := SendEmailNotification(alert)
	if err != nil {
		t.Errorf("SendEmailNotification failed: %v", err)
	}
}