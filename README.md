# http-server
A simple http server implemented with c++

## Use Instruction
requirements:
* Unix based system
* c++ 11 and above

Compile:
```
~/Workspace/http-server$ make
~/Workspace/http-server$ cd examples/
~/Workspace/http-server/examples$ make clean
~/Workspace/http-server/examples$ make
~/Workspace/http-server/examples$ ./simple_exemple.o
```

## Examples:
```
// create a server object
httplib::Server srv;

// registry your url
srv.Get("/", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
    std::string s = "hello, ";
    s += req.getParam("name");
    resp.createHtmlResponse(s.c_str());
});

srv.Post("/", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
    std::string s = "hello, ";
    s += req.getForm("name");
    resp.createHtmlResponse(s.c_str());
});

srv.Get("/yes", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
    resp.createHtmlResponse("Yes!");
});

// run the server
srv.listen("0.0.0.0", 8000);
```

### Update: 12/23/2020
Finished job:
* response is HTTP/1.0, which is non-persistent connection.
* supported request type: GET, POST
* for POST request, only support decoding Content-Type: application/x-www-form-urlencoded
* response content type now support: text/html; charset=utf-8

