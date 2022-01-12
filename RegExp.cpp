#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

double extractDouble(const std::string &request, const char *param) {
	
	std::string expr { "(){1}(=){1}([0-9]+[\\.,]{1}[0-9]+)" };
	expr.insert(1, param);
	
	std::regex r_dbl(expr);
	
	std::smatch m;
	
	if (!std::regex_search(request, m, r_dbl))
		return 0.0;
	
	return std::stod(m[3]);
}

std::string getBody(const std::string &fullRequest) {
	std::string pattern { "([\\w-:\\s/\"]+)([\\r\\n]{1})([\\w\\s\\{\\}\":,]*)" };
	std::regex r_body(pattern);
	std::smatch m;
	
	if (!std::regex_search(fullRequest, m, r_body))
		return std::string { "Could not extract body" };
	
	/*
	for(int i = 0; i < m.size(); ++i)
		std::cout << '[' << m[i] << ']' << std::endl;
	*/
	
	return m[3];
}

int main(int argc, char *argv[])
{
	std::string httpRequest {
		"http://83.220.174.93:34576/hunting/movePlayer?lat=33.333333&lng=55.555555&nick=Arturas&team=A&type=Shooter"
	};
	
	std::cout << std::setprecision(11) << extractDouble(httpRequest, "lat") << std::endl;
	std::cout << std::setprecision(11) << extractDouble(httpRequest, "lng") << std::endl;
	
	std::regex r_str("(team){1}(=)([a-zA-Z0-9]+)");	

	std::string fullRequest {};
	fullRequest.append("Content-Type: application/json\r\n");
	fullRequest.append("\r\n");
	fullRequest.append("{ \"key1\": \"value1\", \"key2\": \"value2\" }");
	
	//std::cout << fullRequest << std::endl;
	std::cout << getBody(fullRequest) << std::endl;
	
	return 0;
}

// How to build and then run this app:
// cl.exe /std:c++17 /W4 /EHsc "RegExp.cpp" /link /out:"RegExp.exe" && RegExp.exe