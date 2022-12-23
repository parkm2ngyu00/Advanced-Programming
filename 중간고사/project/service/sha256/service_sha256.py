#!/usr/bin/python3

import hashlib
from flask import Flask

app = Flask(__name__)

@app.route('/<resource>')
def processResouce(resource):
    md5 = hashlib.sha256()
    md5.update(resource.encode('utf-8'))
    content = md5.hexdigest()
    return "\"resource\":\"%s\";\"content\":\"%s\";" % (resource, content)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8003, debug=True)
