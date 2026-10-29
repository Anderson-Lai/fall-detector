import requests

url = "http://localhost:8080/api/admin/devices"
secret = ""

try:
    response = requests.post(
        url,
        json={"secret": secret},
        timeout=10,
    )

    response.raise_for_status()

    credentials = response.json()

    device_id = credentials["device_id"]
    api_key = credentials["api_key"]

    print(f"Device ID: {device_id}")
    print(f"API key: {api_key}")

except requests.RequestException as exc:
    print(f"Provisioning request failed: {exc}")