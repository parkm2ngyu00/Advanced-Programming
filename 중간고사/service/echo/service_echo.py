#!/usr/bin/python3

from flask import Flask
import hashlib

app = Flask(__name__)

@app.route('/<resource>')
def processResouce(resource):
    return "\"resource\":\"%s\";\"content\":\"%s\";" % (resource, resource)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, debug=True)
