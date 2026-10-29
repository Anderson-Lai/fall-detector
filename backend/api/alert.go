package api

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