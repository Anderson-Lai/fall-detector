import os
import requests
from dotenv import load_dotenv

load_dotenv()
url = os.environ.get("BACKEND_URL")
url += "/provision_device"
secret = os.environ.get("PROVISIONING_SECRET")

try:
    response = requests.post(
        url,
        json={"provisioning_secret": secret},
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