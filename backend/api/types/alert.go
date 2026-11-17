package types

type Alert struct {
	DeviceID string `json:"device_id"`
	AlertType alertType `json:"alert_type"`
}

type alertType string
// kinds of alerts
const (
	AlertSOS alertType = "SOS"
)