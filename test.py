import base64
import requests

API_ENDPOINT = 'https://discord.com/api/v10'
CLIENT_ID = '332269999912132097'
CLIENT_SECRET = '937it3ow87i4ery69876wqire'


def get_token():
    data = {
        'grant_type': 'client_credentials',
        'scope': 'identify connections'
    }
    headers = {
        'Content-Type': 'application/x-www-form-urlencoded'
    }
    r = requests.Request('POST', '%s/oauth2/token' % API_ENDPOINT, data=data,
                      headers=headers, auth=(CLIENT_ID, CLIENT_SECRET))
    print(r.prepare().body)
get_token()