#include "../bin/include/httplib.h"
#include <iostream>

int main(){
	httplib::Server srv;
	srv.listen("0.0.0.0", 8000);
	return 0;
}
