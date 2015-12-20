
#ifndef SRC_SOUNDEX_H_
#define SRC_SOUNDEX_H_

#include <iostream>
#include <string>
#include <unordered_map>

class Soundex {
public :
	std::string encodedDigit(char letter) const {
		const std::unordered_map<char, std::string> encodings {
			{'b', "1"},{'f', "1"},{'p', "1"}, {'v', "1"},
			{'c', "2"},{'g', "2"},{'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"},{'x', "2"}, {'z', "2"},
			{'d', "3"},{'t', "3"},
			{'l', "4"},
			{'m', "5"},{'n', "5"},
			{'r', "6"}
		};
		auto it = encodings.find(letter);

		return it == encodings.end() ? "": it->second;
	}

	std::string encode(const std::string& word) const {

		return zeroPad(head(word) + encodedDigits(tail(word)));
	}

private :
	std::string head(const std::string& word) const {
		return word.substr(0,1);
	}

	std::string tail(const std::string& word) const {
		return word.substr(1);
	}

	std::string lastDigit(const std::string& encoding) const {
		if (encoding.empty()) return "";
		return std::string(1, encoding.back());
	}

	std::string encodedDigits(const std::string& word) const {
//		if(word.empty()) return "";

		std::string encoding;
		for(auto letter:word) {
			if(isComplete(encoding)) break;
			if(encodedDigit(letter) != lastDigit(encoding))
				encoding += encodedDigit(letter);
		}

		return encoding;
//		return encodedDigit(word.front());
	}

	bool isComplete(const std::string& encoding) const {
		return encoding.length() == MaxCodeLength -1;
	}


	static const size_t MaxCodeLength{4};

	std::string zeroPad(const std::string& word) const {
		auto zeroNeeded = MaxCodeLength - word.length();

//		std::cout << "word is "<< word << ". Zero needed is " << zeroNeeded << std::endl;
		return word + std::string(zeroNeeded, '0');
	}

/*	void test(const char* str) {
//		str = "Test";
		str[0] = "a";
	}*/
};

#endif /* SRC_SOUNDEX_H_ */
