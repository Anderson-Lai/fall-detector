import secrets

provisioning_secret = secrets.token_urlsafe(32)

print(provisioning_secret)