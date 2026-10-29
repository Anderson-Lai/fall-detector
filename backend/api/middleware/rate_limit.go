package middleware

import (
	"medical-device/backend/api/timing"
	"net/http"
	"sync"
)

type RateLimiter struct {
	Count int
	Limit int
	Mtx sync.Mutex
	Day string
}

func NewRateLimiter(limit int) *RateLimiter {
	return &RateLimiter{
		Limit: limit,
		Count: 0,
		Day:   "",
		Mtx:   sync.Mutex{},
	}
}

func (rl *RateLimiter) RateLimit(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		rl.Mtx.Lock()

		today := timing.GetDay()
		if rl.Day != today {
			rl.Day = today
			rl.Count = 0
		}

		rl.Count++
		if rl.Count > rl.Limit {
			http.Error(w, "Rate limit exceeded", http.StatusTooManyRequests)
			return
		}

		rl.Mtx.Unlock()
		next.ServeHTTP(w, r)
	})
}