package types

type Alert struct {
	DeviceID string `json:"device_id"`
	AlertType alertType `json:"alert_type"`
	Coordinates Coordinates `json:"coordinates"`
}

type alertType string
// kinds of alerts
const (
	AlertSOS alertType = "SOS"
)
type Coordinates struct {
	Latitude, Longitude float64
}