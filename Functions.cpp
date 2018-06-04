#include "Functions.h"

std::vector<std::string> sSplit(const std::string &s, const std::string &div)
{
	std::vector<std::string> new_string;

	std::string aux = "";
	std::string aux2 = "";
	unsigned int i, j;
	for (i = 0, j = 0; i < s.length(); ++i) {
		if (s[i] != div[j])
			aux += s[i];
		else {
			aux2 = "";
			for (; j < div.length() && i < s.length() && s[i] == div[j]; ++i, ++j)
				aux2 += s[i];

			if (j == div.length()) {
				new_string.push_back(aux);
				aux = "";
			}
			else {
				aux += aux2;
			}

			--i;
			j = 0;
		}
	}

	new_string.push_back(aux);

	return new_string;
}
