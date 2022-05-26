from http.server import BaseHTTPRequestHandler, HTTPServer
import time
import ssl

hostName = "10.217.194.174"
serverPort = 80 

class MyServer(BaseHTTPRequestHandler):
    def do_HEAD(self):
        print ("send header")
        self.send_response(200)
        #self.send_response(302)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(bytes("<html><head><title>https://pythonbasics.org</title></head>", "utf-8"))
        self.wfile.write(bytes("<p>Request: %s</p>" % self.path, "utf-8"))
        self.wfile.write(bytes("<body>", "utf-8"))
        self.wfile.write(bytes("<p>This is an example web server.</p>", "utf-8"))
        self.wfile.write(bytes("</body></html>", "utf-8"))
    def do_redirect(self):
        print ("send header")
        self.send_response(302)
        self.send_header('Location', 'http://10.217.194.174/claimfs/ls/?wa=wsignin1.0&wtrealm=https%3a%2f%2finsight.tsextranet.int%2f&wctx=rm%3d0%26id%3dpassive%26ru%3d%252fportal-prd%252f&wct=2021-11-16T11%3a07%3a11Z')
        #self.send_header('Content-type', 'text/html')
        #self.wfile.write(bytes("<html><head><title>object moved</title></head>", "utf-8"))
        #self.wfile.write(bytes("<body>", "utf-8"))
        #self.wfile.write(bytes("<h2>Object moved to <a href=\"http://10.217.194.174/claimfs/ls/?wa=wsignin1.0&amp;wtrealm=https%3a%2f%2finsight.tsextranet.int%2f&amp;wctx=rm%3d0%26id%3dpassive%26ru%3d%252fportal-prd%252f&amp;wct=2021-11-16T11%3a07%3a11Z\">here</a>.", "utf-8"))
        #self.wfile.write(bytes("</body></html>", "utf-8"))
        self.end_headers()
    def do_AUTHHEAD(self):
        print ("send header")
        self.send_response(401)
        self.send_header('WWW-Authenticate', 'Basic realm=\"Test\"')
        self.send_header('Content-type', 'text/html')
        self.end_headers()
    def do_POST(self):
        print("in post handling")
        #self.send_response(200)
        #self.end_headers()
        print(self.headers)
    def do_GET(self):
        ''' Present frontpage with user authentication. '''
        print(self.headers)
        return self.do_HEAD()
        #authz = any(k for k in self.headers if k == "Authorization" and self.headers[k] == "Basic dGVzdDp0ZXN0" ) 
        #authz = any(k for k in self.headers if k == "Authorization" and self.headers[k] == "Basic dDp0")  #for user/password t/t
        authz = any(k for k in self.headers if k == "Authorization" and self.headers[k] == "Basic dHNleHRyYW5ldFxzcmloYXJpMTpzcmloYXJpMQ==") 
        #authz = any(k for k in self.headers if k == "Authorization" and self.headers[k] == "Basic c3JpaGFyaTFAYWFhLmxvY2FsOnNyaWhhcmkx") 
        print(authz)
        if authz:
            return self.do_redirect()
            self.do_HEAD()
            self.wfile.write(bytes("<html><head><title>https://pythonbasics.org</title></head>", "utf-8"))
            self.wfile.write(bytes("<p>Request: %s</p>" % self.path, "utf-8"))
            self.wfile.write(bytes("<body>", "utf-8"))
            self.wfile.write(bytes("<p>This is an example web server.</p>", "utf-8"))
            self.wfile.write(bytes("</body></html>", "utf-8"))
            pass
        else:
            self.do_AUTHHEAD()
            pass
#    def do_GET(self):
#        self.do_AUTHHEAD();
#        return;
#        self.send_response(200)
#        self.send_header("Content-type", "text/html")
#        self.end_headers()
#        self.wfile.write(bytes("<html><head><title>https://pythonbasics.org</title></head>", "utf-8"))
#        self.wfile.write(bytes("<p>Request: %s</p>" % self.path, "utf-8"))
#        self.wfile.write(bytes("<body>", "utf-8"))
#        self.wfile.write(bytes("<p>This is an example web server.</p>", "utf-8"))
#        self.wfile.write(bytes("</body></html>", "utf-8"))

if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    #webServer.socket = ssl.wrap_socket (webServer.socket, certfile='./server.pem', server_side=True)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")
