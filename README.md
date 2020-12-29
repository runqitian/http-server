# http-server
A simple http server implemented with c++

## Use Instruction
requirements:
* Unix based system
* g++ with c++11 or above

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
// create srv
httplib::Server srv;

// register url
// get request
srv.Get("/", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
    std::string s = "hello, ";
    s += req.getParam("name");
    resp.createHtmlResponse(s);
});

// post request
srv.Post("/", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
    std::string s = "hello, ";
    s += req.getForm("name");
    resp.createHtmlResponse(s);
});

// get request with json
srv.Get("/json", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
    httplib::JSON json = {{"message", "hello"}, {"foods",{"fruit", "meat", "vegie"}}};
    resp.createJSONResponse(json);
});

// listen
srv.listen("0.0.0.0", 8000);
```

### Update: 12/23/2020
Finished job:
* response is HTTP/1.0, which is non-persistent connection.
* supported request type: GET, POST
* for POST request, only support decoding Content-Type: application/x-www-form-urlencoded
* response content type now support: text/html; charset=utf-8

### Update 12/29/2020
Finished job:
* add JSON support, support conversion between json and string.
* response support application/json
