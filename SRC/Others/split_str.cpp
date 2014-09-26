#include "TypeDefs.h"
#include "split_str.h"

void split_str(const std::string& s, const std::string& delim, std::vector<std::string>& result)
{
	size_t last  = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != std::string::npos) {
		result.push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}

	if (index - last > 0)
		result.push_back(s.substr(last, index - last));
}