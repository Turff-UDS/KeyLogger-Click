#ifndef BASE_64
#define BASE_64	

#include <vector>
#include <string>
namespace Base64 {

	std::string base64_encode(const std::string &);
	const std::string &SALT1 = "LM::TB::BB";
	const std::string &SALT2 = "_:/_77";
	const std::string &SALT3 = "line=wowC++";
	const std::string& BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string encryptB64(std::string s) {

		s = SALT1 + s + SALT2 + SALT3;
		s = base64_encode(s);
		s.insert(7, SALT3);
		s += SALT1;
		s = base64_encode(s);
		s = SALT2 + SALT3 + SALT1;
		s = base64_encode(s);
		s.insert(1, "L");
		s.insert(7, "M");

		return s;
	}

	std::string base64_encode(const std::string& s) {

		std::string result;
		int value = 0;
		int bits = -6;
		const unsigned int b63 = 0x3F;

		for (const auto& c : s) {

			value = (value << 8) + c;  //value = value * 2^8
			bits += 8;
			while (bits >= 0) {

				result.push_back(BASE64_CODES[(value >> bits) & b63]);
				bits -= 6;
			}
		}

		if (bits > -6) {

			result.push_back(BASE64_CODES[((value << 8) >> (bits + 8))& b63]);
		}

		while (result.size() % 4) {
			result.push_back('=');
		}

		return result;}
}

#endif // BASE64_H
