#!/usr/bin/python3

from flask import Flask
import hashlib

app = Flask(__name__)

@app.route('/<resource>')
def processResouce(resource):
    md5 = hashlib.md5()
    md5.update(resource.encode('utf-8'))
    content = md5.hexdigest()
    return "\"resource\":\"%s\";\"content\":\"%s\";" % (resource, content)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8001, debug=True)
