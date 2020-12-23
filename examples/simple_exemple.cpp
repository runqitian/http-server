#include "../bin/include/httplib.h"

#include <iostream>

int main(){
	httplib::Server srv;
	srv.Get("/", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
		std::string s = "hello, ";
		s += req.getParam("name");
		resp.createHtmlResponse(s.c_str());
	});

	srv.Get("/yes", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
		resp.createHtmlResponse("Yes!");
	});

	srv.listen("0.0.0.0", 8000);
	return 0;
}
