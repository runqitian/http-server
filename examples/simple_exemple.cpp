#include "../bin/include/httplib.h"

#include <iostream>

int main(){
	httplib::Server srv;
	srv.Get("/", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
		std::string s = "hello, ";
		s += req.getParam("name");
		resp.createHtmlResponse(s);
	});
	
	srv.Post("/", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
		std::string s = "hello, ";
		s += req.getForm("name");
		resp.createHtmlResponse(s);
	});

	srv.Get("/json", [](httplib::HTTPRequest &req, httplib::HTTPResponse &resp){
		httplib::JSON json = {{"message", "hello"}, {"foods",{"fruit", "meat", "vegie"}}};
		resp.createJSONResponse(json);
	});


	srv.listen("0.0.0.0", 8000);
	return 0;
}
