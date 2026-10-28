package api

import (
	"fmt"
	"log"
	"net/http"
)

func InitAPI(isHTTP bool, port int) {
	http.HandleFunc("/receive_post", receivePost)

	if isHTTP {
		portStr := fmt.Sprintf(":%d", port)
		log.Printf("Starting HTTP server at http://localhost%s\n", portStr)
		http.ListenAndServe(portStr, nil)
	}
}