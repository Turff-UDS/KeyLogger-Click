#ifndef HELPER_H
#define HELPER_H

#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

namespace Helper {

	template <class T>
	std::string toString (const T &);

	struct DateTime {

		int d, m, y, H, M, S;
		
		DateTime() {

			time_t ms;
			time (&ms);
			struct tm *info = localtime(&ms);

			d = info->tm_mday;
			m = info->tm_mon + 1;
			y = 1900 + info->tm_year;
			M = info->tm_min;
			H = info->tm_hour;
			S = info->tm_sec;
		}

		DateTime(int d, int m, int y, int H, int M, int S) : d(d), m(m), y(y), H(H), M(M), S(S) {};
		DateTime(int d, int m, int y) : d(d), m(m), y(y), H(0), M(0), S(0) {};

		DateTime Now() const {

			return DateTime();
		}	

		std::string getDateString() const {
			
			return std::string (d < 10 ? "0" : "") + toString(d) +
				   std::string (m < 10 ? ".0" : ".") + toString(m) + "." +
				   toString(y);
		}

		std::string getTimeString(const std::string& separator = ":") {
			
			return std::string (H < 10 ? "0" : "") + toString(H) + separator +
				   std::string (M < 10 ? "0" : "") + toString(M) + separator +
				   std::string (S < 10 ? separator: "") + toString(S);
		}

		std::string getDateTimeString(const std::string &separator = ":") {

			return getDateString() + getTimeString(separator);
		}
	};

	template <class T>
	std::string toString(const T& e) {
		std::ostringstream s;
		s << e;
		return s.str();
	}

	void writeAppLog(const std::string &s) {
		std::ofstream file("AppLog.txt", std::ios::app);
		file << "[" << Helper::DateTime().getDateTimeString() << "]" <<
		"\n" << s << std::endl << "\n";
		file.close();
	}

}



#endif
