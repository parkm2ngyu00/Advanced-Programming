#!/usr/bin/python3

import requests
import sys

service = ""

if len(sys.argv) != 3:
    print ("Usage: %s {echo|md5|sha1|sha256|sha512} [resource]" % sys.argv[0])
    exit(0)

if sys.argv[1] not in ["echo", "md5", "sha1", "sha256", "sha512"]:
    print ("Usage: %s {echo|md5|sha1|sha256|sha512} [resource]" % sys.argv[0])
    exit(0)

if sys.argv[1] == "echo":
    service = "8000"
elif sys.argv[1] == "md5":
    service = "8001"
elif sys.argv[1] == "sha1":
    service = "8002"
elif sys.argv[1] == "sha256":
    service = "8003"
elif sys.argv[1] == "sha512":
    service = "8004"

response = requests.get("http://127.0.0.1:%s/%s" % (service, sys.argv[2]))
print(response.text)
