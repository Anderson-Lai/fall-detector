# Backend Documentation

The backend exposes two endpoints, `./provision_device` and `./post_alert`.

**`./provision_device`** is a POST endpoint. It expects one field in the JSON body: `provisioning_secret`. This field should contain the 256-bit authentication key. The endpoint returns two fields in JSON format: `device_id`, a v4 UUID string, and `api_key`, a 256-bit API key string.

**`./post_alert`** is a POST endpoint. It expects two headers: `api_key` and `device_id`. These are the credentials used to authenticate the device and request. The endpoint will automatically send email notifications to recipients listed in `NOTIFICATION_RECIPIENT_EMAILS` in the `.env` file and SMS notifications to recipients listed in `NOTIFICATION_RECIPIENT_NUMBERS` in the `.env` file (to be implemented).