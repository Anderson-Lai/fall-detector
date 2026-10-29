package logging

import (
	"encoding/json"
	"fmt"
	"log"
	"medical-device/backend/api/timing"
	"medical-device/backend/api/types"
	"os"
)

const logsDir = "logs"

func InitAlertLogging() {
	if err := os.MkdirAll(logsDir, 0777); err != nil {
		log.Fatal("Could not create logs directory: ", err)
	}
}

func LogAlert(alert types.Alert) error {
	day := timing.GetDay()
	logName := fmt.Sprintf("%s/%s.log", logsDir, day)

	if err := createLogFile(logName); err != nil {
		return err
	}

	logData, err := readJSONData(logName)
	if err != nil {
		return err
	}

	logData[timing.GetNow()] = types.Alert{
		DeviceID:    alert.DeviceID,
		AlertType:   alert.AlertType,
		Coordinates: alert.Coordinates,
	}

	if err := writeAsJSONData(logName, logData); err != nil {
		return err
	}

	return nil
}

// creates a file only if the file does not exist; otherwise, it does nothing
func createLogFile(filePath string) error {
	_, err := os.Stat(filePath)
	if os.IsNotExist(err) {
		file, err := os.Create(filePath)
		if err != nil {
			log.Println("Could not create log file: ", err)
			return err
		}
		
		file.Write([]byte("{}"))
		file.Close()
	}
	return nil
}

func readJSONData(filePath string) (map[string]types.Alert, error) {
	file, err := os.ReadFile(filePath)
	if err != nil {
		log.Println("Could not read log file: ", err)
		return nil, err
	}

	var data map[string]types.Alert
	if err := json.Unmarshal(file, &data); err != nil {
		log.Println("Could not unmarshal log data: ", err)
		return nil, err
	}

	return data, nil
}

func writeAsJSONData(filePath string, data map[string]types.Alert) error {
	jsonData, err := json.MarshalIndent(data, "", "  ")
	if err != nil {
		log.Println("Could not marshal log data: ", err)
		return err
	}

	if err := os.WriteFile(filePath, jsonData, 0644); err != nil {
		log.Println("Could not write to log file: ", err)
		return err
	}

	return nil
}