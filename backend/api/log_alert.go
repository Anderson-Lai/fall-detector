package api

import (
	"encoding/json"
	"fmt"
	"log"
	"os"
	"time"
)

const logsDir = "logs"

func InitAlertLogging() {
	if err := os.MkdirAll(logsDir, 0777); err != nil {
		log.Fatal("Could not create logs directory: ", err)
	}
}

func LogAlert(alert Alert) {
	day := getDay()
	logName := fmt.Sprintf("%s/%s.log", logsDir, day)

	if err := createLogFile(logName); err != nil {
		return
	}

	logData, err := readJSONData(logName)
	if err != nil {
		logData = make(map[string]Alert)
	}

	logData[getNow()] = Alert{
		DeviceID:    alert.DeviceID,
		AlertType:   alert.AlertType,
		Coordinates: alert.Coordinates,
	}

	if err := writeAsJSONData(logName, logData); err != nil {
		return
	}
}

func getDay() string {
	return time.Now().Format("2006-01-02")
}

func getNow() string {
	return time.Now().Format("2006-01-02 15:04:05")
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
		file.Close()
	}
	return nil
}

func readJSONData(filePath string) (map[string]Alert, error) {
	file, err := os.ReadFile(filePath)
	if err != nil {
		return nil, err
	}

	var data map[string]Alert
	if err := json.Unmarshal(file, &data); err != nil {
		return nil, err
	}

	return data, nil
}

func writeAsJSONData(filePath string, data map[string]Alert) error {
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