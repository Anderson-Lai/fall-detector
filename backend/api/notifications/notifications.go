package notifications

import (
	"errors"
	"fmt"
	"log"
	"medical-device/backend/api/types"
	"net/smtp"
	"os"
	"strings"
)

type emailSecrets struct {
	Username, Password string
	Recipients []string
}

func SendEmailNotification(alert types.Alert) error {
	details, err := loadEmailSecrets()
	if err != nil {
		return err
	}

	auth := smtp.PlainAuth("", details.Username, details.Password, "smtp.gmail.com")

	var alertType string
	switch alert.AlertType {
		case types.AlertSOS:
			alertType = "SOS"
		default:
			return errors.New("Invalid alert type")
	}

	subject := "Medical Device Alert: " + alertType
	validCoordinates := alert.Coordinates.Latitude <= 90.0 && alert.Coordinates.Latitude >= -90.0 && 
		alert.Coordinates.Longitude <= 180.0 && alert.Coordinates.Longitude >= -180.0

	for _, recipient := range details.Recipients {
		message := "From: " + details.Username + "\r\n" +
			"To: " + recipient + "\r\n" +
			"Subject: " + subject + "\r\n" +
			"\r\n" +
			"A new alert of type: " + alertType + " has been sent from device ID: " +
			alert.DeviceID

		if validCoordinates {
			message += fmt.Sprintf(" at coordinates: (%.6f, %.6f)", 
				alert.Coordinates.Latitude, alert.Coordinates.Longitude)
		}

		message += ".\r\n"

		err := smtp.SendMail("smtp.gmail.com:587", auth, details.Username, []string{recipient}, []byte(message))
		if err != nil {
			log.Printf("Error sending email to %s: %v", recipient, err)
		}
	}

	return nil
}

func loadEmailSecrets() (emailSecrets, error) {
	sender := os.Getenv("GMAIL_USERNAME")
	password := os.Getenv("GMAIL_APP_PASSWORD")
	if sender == "" || password == "" {
		log.Fatal("GMAIL_USERNAME or GMAIL_APP_PASSWORD not set in .env file")
		return emailSecrets{}, errors.New("GMAIL_USERNAME or GMAIL_APP_PASSWORD not set in .env file")
	}

	recipients := strings.Split(os.Getenv("NOTIFICATION_RECIPIENT_EMAILS"), ",")
	if len(recipients) == 0 {
		log.Fatal("NOTIFICATION_RECIPIENT_EMAILS not set in .env file")
		return emailSecrets{}, errors.New("NOTIFICATION_RECIPIENT_EMAILS not set in .env file")
	}

	return emailSecrets{
		Username:   sender,
		Password:   password,
		Recipients: recipients,
	}, nil
}