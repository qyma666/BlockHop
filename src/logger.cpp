//
// Created by Tim on 8/06/2017.
//

#include "logger.h"
#include "triggers/ClickedTrigger.h"
#include <typeinfo>

Logger::Logger()
{
	endLine = true;
	between = "";
}
Logger::Logger(bool doEndLine)
{
	endLine = doEndLine;
	between = "";
}
Logger::Logger(const std::string& inBetween)
{
	endLine = true;
	between = inBetween;
}
Logger::Logger(bool doEndLine, const std::string& inBetween)
{
	endLine = doEndLine;
	between = inBetween;
}

Logger::~Logger()
{
	if(endLine)
	{
		time_t current_time;
		struct tm * time_info;
		std::time(&current_time);
		char timeString[9];  // space for "HH:MM:SS\0"
		time_info = localtime(&current_time);
		strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
		std::cout << "[" << timeString << "] ";

	}

	std::cout << buffer.str();
	if(endLine)
		std::cout << std::endl;
}

template<typename T>
Logger &Logger::operator<<(std::vector<T> val)
{
	buffer << typeid(val).name();
	int i = 0;
	for(auto item : val)
	{
		if(i != 0)
			buffer << "\n";
		buffer << "\tItem " << i++ << ": ";
		(*this) << item;
	}
	return *this;
}

template<typename S, typename T>
Logger &Logger::operator<<(std::map<S, T> val)
{
	buffer << typeid(val).name();
	int i = 0;
	for(auto item : val)
	{
		if(i++ != 0)
			buffer << "\n";
		buffer << "\tItem ";
		(*this) << item->first();
		buffer << ": ";
		(*this) << item->second();
	}
	return *this;
}

//Function for special stream types, eg endl
Logger& Logger::operator<<(std::ostream& (*val)(std::ostream &))
{
	buffer << val << between;
	return *this;
}

// GLM
Logger& Logger::operator<<(const glm::vec2 val)
{
	//Push input to stringstream
	buffer << val.x << ", " << val.y << between;
	return *this;
}

Logger& Logger::operator<<(const glm::vec3 val)
{
	//Push input to stringstream
	buffer << val.x << ", " << val.y << ", " << val.z << between;
	return *this;
}

Logger& Logger::operator<<(const glm::vec4 val)
{
	//Push input to stringstream
	buffer << val.w << ", " << val.x << ", " << val.y << ", " << val.z << between;
	return *this;
}

Logger& Logger::operator<<(const glm::quat val)
{
	(*this) << glm::vec4(val.w,val.x,val.y,val.z);
	return *this;
}

Logger& Logger::operator<<(const glm::mat4 val)
{
	//Push input to stringstream
	(*this) << val[0][0] << "," << val[1][0] << "," << val[2][0] << "," << val[3][0] << " | ";
	(*this) << val[0][1] << "," << val[1][1] << "," << val[2][1] << "," << val[3][1] << " | ";
	(*this) << val[0][2] << "," << val[1][2] << "," << val[2][2] << "," << val[3][2] << " | ";
	(*this) << val[0][3] << "," << val[1][3] << "," << val[2][3] << "," << val[3][3] << " | ";
	return *this;
}

// Bullet
Logger &Logger::operator<<(btVector3 val)
{
	buffer << val.x() << ", " << val.y() << ", " << val.z() << between;
	return *this;
}

Logger &Logger::operator<<(btQuaternion val)
{
	buffer << val.x() << ", " << val.y() << ", " << val.z() << ", " << val.w() << between;
	return *this;
}

Logger &Logger::operator<<(btTransform val)
{
	const btVector3 translation = val.getOrigin();
	const btQuaternion rotation = val.getRotation();
	buffer << "T:(";
	(*this) << translation;
	buffer << ") ";
	buffer << "R:(";
	(*this) << rotation;
	buffer << ")";
	return *this;
}