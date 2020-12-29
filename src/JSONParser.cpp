#include "JSONParser.h"

#include <string>
#include <stdexcept>

httplib::JSONParser::JSONParser()
{}

httplib::JSONParser::~JSONParser()
{}

httplib::JSON httplib::JSONParser::parse(const std::string &input)
{
	const char *p = input.c_str();
	skipBlankChar(p);

	JSON json;
	if (*p == '[')
	{
		json = parseArray(p);
	}
	else if (*p == '{')
	{
		json = parseObject(p);
	}
	else
		throw std::runtime_error("parse error!");
	return json;
}

httplib::JSON httplib::JSONParser::parseArray(const char *&p)
{
	if (*p != '[')
		throw std::runtime_error("parseArray error!");
	p++;
	skipBlankChar(p);
	httplib::JSON json;

	if (*p == ']')
		return json;

	while(true)
	{
		skipBlankChar(p);
		// read item
		if (*p == '\"')
		{
			std::string s = readString(p);
			JSONObject item = s.c_str();
			json.append(item);
		}
		else if (*p == '{')
		{
			// std::cout << "parse object " << std::endl;
			JSONObject item = parseObject(p);
			json.append(item);
		}
		else
		{
			JSONObject item = readUnknowText(p);
			json.append(item);
		}

		skipBlankChar(p);
		if (*p == ',')
		{
			p++;
			continue;
		}
		else if (*p == ']')
		{
			p++;
			break;
		}
		else
		{
			throw std::runtime_error("parseArray error!");
		}
	}
	return json;
}

httplib::JSON httplib::JSONParser::parseObject(const char *&p)
{
	if (*p != '{')
		throw std::runtime_error("parseObject error!");
	p++;
	skipBlankChar(p);

	httplib::JSON json;

	// empty object
	if (*p == '}')
		return json;
	
	// read key-value pair
	while(true)
	{
		skipBlankChar(p);
		std::pair<std::string, JSON> kv = readKeyPair(p);
		json.set(kv.first, kv.second);
		skipBlankChar(p);
		if (*p == ',')
		{
			p++;
			continue;
		}
		else if (*p == '}')
		{
			p++;
			break;
		}
		else
		{
			throw std::runtime_error("parseObject error!");
		}
	}
	return json;

}

std::string httplib::JSONParser::readString(const char *&p)
{
	if (*p != '\"')
		throw std::runtime_error("readString error!");
	p++;

	// read string
	std::string tmp;
	while(*p != '\"'){
		if (*p == '\\')
		{
			p++;
		}
		if (*p == 0)
			throw std::runtime_error("readString error!");
		tmp += *p;
		p++;
	}
	p++;
	return tmp;
}

httplib::JSON httplib::JSONParser::readUnknowText(const char *&p)
{
	// could be double, int, bool
	std::string tmp;
	while (*p != '\n' && *p != ' ' && *p !=  ',' && *p != '}'  && *p != 0)
	{
		tmp += *p;
		p++;
	}

	JSON json;
	// bool
	if (tmp == "false")
	{
		json = false;
		return json;
	}
	else if (tmp == "true")
	{
		json = true;
		return json;
	}
	// int
	std::string::size_type sz;
	int r1 = std::stoi(tmp,&sz,10);
	if (sz == tmp.size())
	{
		json = r1;
		return json;
	}
	// double
	double r2 = std::stod(tmp, &sz);
	if (sz == tmp.size())
	{
		json = r2;
		return json;
	}
	throw std::runtime_error("readUnknowText parse error!");
	return json;
}

std::pair<std::string, httplib::JSON> httplib::JSONParser::readKeyPair(const char *&p)
{
	// read key
	if (*p != '\"')
		throw std::runtime_error("key pair error");
	std::string key = readString(p);

	// read colon
	skipBlankChar(p);
	if (*p != ':')
		throw std::runtime_error("key pair error");
	p++;
	skipBlankChar(p);

	JSON json;
	// read value
	if (*p == '{')
	{
		json = parseObject(p);
	}
	else if (*p == '"')
	{
		std::string s = readString(p);
		json = s.c_str();
	}
	else if (*p == '[')
	{
		json = parseArray(p);
	}
	else{
		json = readUnknowText(p);
	}
	std::pair<std::string, JSON> result(key, json);
	return result;

}

void httplib::JSONParser::skipBlankChar(const char *&p)
{
	while (*p == ' ' || *p == '\n')
	{
		p++;
	}
}
