package endpoints

import (
	"encoding/json"
	"log"
	"net/http"
	"os"
)

func (a *API) ProvisionDevice(w http.ResponseWriter, r *http.Request) {
	secret := loadProvisioningSecret()
	if secret == "" {
		log.Fatal("Provisioning secret not set in environment variables")
		w.WriteHeader(http.StatusInternalServerError)
		return
	}

	requestSecret, err := getRequestSecret(r)
	if err != nil {
		log.Println("Error getting request secret: ", err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}
	
	if requestSecret != secret {
		log.Println("Invalid provisioning secret")
		w.WriteHeader(http.StatusUnauthorized)
		return
	}

	apiKey, err := generateAPIKey()
	if err != nil {
		log.Println("Error generating API key: ", err)
		w.WriteHeader(http.StatusInternalServerError)
		return
	}

	hashedAPIKey := HashAPIKey(apiKey)
	deviceID := generateUUID()

	_, err = a.DB.Exec("INSERT INTO devices (device_id, api_key) VALUES (?, ?)", deviceID, hashedAPIKey)
	if err != nil {
		log.Println("Error inserting device into database: ", err)
		w.WriteHeader(http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	response := map[string]string{
		"device_id": deviceID,
		"api_key":   apiKey,
	}

	err = json.NewEncoder(w).Encode(response)
	if err != nil {
		log.Println("Error encoding response: ", err)
		w.WriteHeader(http.StatusInternalServerError)
		return
	}
}

func loadProvisioningSecret() string {
	return os.Getenv("PROVISIONING_SECRET")
}

func getRequestSecret(r *http.Request) (string, error) {
	var data map[string]string
	err := json.NewDecoder(r.Body).Decode(&data)

	if err != nil {
		return "", err
	}

	return data["provisioning_secret"], nil
}