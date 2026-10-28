package api

import (
	"fmt"
	"log"
	"net/http"
)

func InitAPI() {
	http.HandleFunc("/receive_post", receivePost)
}

func StartServer(isHTTP bool, port int) {
	if isHTTP {
		portStr := fmt.Sprintf(":%d", port)
		log.Printf("Starting HTTP server at http://localhost%s\n", portStr)
		http.ListenAndServe(portStr, nil)
	}
}