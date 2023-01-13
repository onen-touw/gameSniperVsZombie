#pragma once
#include"settings.h"

#include<iostream>
#include<fstream>
#include <string>

class saveClass
{

private:
	std::string path = "save/data.txt";
	int lastResult = 0;
	std::string tempStr;
public:
	saveClass() {
		getResultFromSave();

	}
	~saveClass()
	{
	}
	void getResultFromSave() {
		std::ifstream file(path);
		if (file.is_open()) {
			std::getline(file, this->tempStr);
			this->lastResult = atoi(this->tempStr.c_str());
		}
	}

	void saveResult(int result) {
		if (this->lastResult < result)
		{
			std::ofstream file(path, std::ios::out);
			if (file.is_open())
			{
				file << result << "\n";
			}
		}
	}

	int getResult() {
		return this->lastResult;
	}

};

