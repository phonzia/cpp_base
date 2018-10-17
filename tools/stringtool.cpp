#include "stringtool.h"

namespace cppbase {
namespace stringtool {
std::string trimLeft(const std::string &source,
                     const std::string &trimchars) {
    std::string::size_type p = source.find_first_not_of(trimchars);

    if (p == std::string::npos) {
        return std::string();
    } else {
        return std::string(source, p, source.size() - p);
    }
}

std::string trimRight(const std::string &source,
                      const std::string &trimchars) {
    std::string::size_type p = source.find_last_not_of(trimchars);

    if (p == std::string::npos) {
        return std::string();
    } else {
        return std::string(source, 0, p + 1);
    }
}

std::string trimAll(const std::string &source,
                    const std::string &trimchars) {
    return trimLeft(trimRight(source, trimchars), trimchars);
}

std::string lowerCase(const std::string &source) {
    std::string destination = source;

    for (std::string::iterator it = destination.begin();
         it != destination.end();
         ++it) {
        if (*it >= 'A' && *it <= 'Z') {
            *it += 'a' - 'A';
        }
    }

    return destination;
}

std::string upperCase(const std::string &source) {
    std::string destination = source;

    for (std::string::iterator it = destination.begin();
         it != destination.end();
         ++it) {
        if (*it >= 'a' && *it <= 'z') {
            *it += 'A' - 'a';
        }
    }

    return destination;
}

std::string replaceFirstSubStr(const std::string &source,
                               const std::string &substring,
                               const std::string &repstring) {
    std::string::size_type p = source.find(substring);

    if (std::string::npos == p) {
        return source;
    } else {
        return std::string(source).replace(p, substring.size(), repstring);
    }
}

std::string replaceLastSubStr(const std::string &source,
                              const std::string &substring,
                              const std::string &repstring) {
    std::string::size_type p = source.rfind(substring);

    if (std::string::npos == p) {
        return source;
    } else {
        return std::string(source).replace(p, substring.size(), repstring);
    }
}

std::string replaceAllSubStr(const std::string &source,
                             const std::string &substring,
                             const std::string &repstring) {
    std::string destination = source;
    std::string::size_type pStart = 0;
    std::string::size_type p = 0;

    while ((p = destination.find(substring, pStart)) != std::string::npos) {
        destination.replace(p, substring.size(), repstring);
        pStart = p + substring.size();
    }

    return destination;
}

void replaceFirstSubStrM(std::string &source,
                         const std::string &substring,
                         const std::string &repstring) {
    std::string::size_type p = source.find(substring);

    if (std::string::npos == p) {
        return;
    } else {
        source.replace(p, substring.size(), repstring);
        return;
    }
}

void replaceLastSubStrM(std::string &source,
                        const std::string &substring,
                        const std::string &repstring) {
    std::string::size_type p = source.rfind(substring);

    if (std::string::npos == p) {
        return;
    } else {
        source.replace(p, substring.size(), repstring);
        return;
    }
}

void replaceAllSubStrM(std::string &source,
                       const std::string &substring,
                       const std::string &repstring) {
    std::string::size_type pStart = 0;
    std::string::size_type p = 0;

    while ((p = source.find(substring, pStart)) != std::string::npos) {
        source.replace(p, substring.size(), repstring);
        pStart = p + substring.size();
    }

    return;
}


long long strToInt(const std::string &source) {
    return std::stoll(source);
}

double strToFloat(const std::string &source) {
    return std::stod(source);
}

std::string intToStr(const long long &value) {
    return std::to_string(value);
}

std::string floatToStr(const double &value,
                       const int &precision) {
    std::ostringstream os;
    os.setf(std::ios::fixed, std::ios::floatfield);
    os.precision(precision);
    os << value;
    return os.str();
}

bool isNumber(const std::string &source) {
    if (source.size() < 1) {
        return false;
    }

    if (countChar(source, '.') > 1) {
        return false;
    }

    std::string::size_type pos = source.find_first_of('.');

    if ((pos == 0) || (pos == source.length() - 1)) {
        return false;
    }

    std::string src = trimAll(source);

    if ('-' == src[0]) {
        if (src.size() < 2 || ('.' == src[1])) {
            return false;
        }

        src.assign(src, 1, src.size() - 1);
    }

    for (std::string::iterator it = src.begin();
         it != src.end(); ++it) {
        if (!isdigit(*it) && *it != '.') {
            return false;
        }
    }

    return true;
}

bool isIntegerNumber(const std::string &source) {
    if (source.size() < 1) {
        return false;
    }

    if (countChar(source, '.') > 1) {
        return false;
    }

    std::string src = trimAll(source);

    if ('-' == src[0]) {
        if (src.size() < 2) {
            return false;
        }

        src.assign(src, 1, src.size() - 1);
    }

    for (std::string::iterator it = src.begin();
         it != src.end(); ++it) {
        if (!isdigit(*it)) {
            return false;
        }
    }

    return true;
}

size_t countChar(const std::string &source, const char &c) {
    return std::count(source.begin(), source.end(), c);
}

//WARNING!!!! This function will modify the source string
std::string stringTok(std::string &source, const std::string &delim) {
    std::string::size_type delim_position = source.find_first_of(delim);

    if (delim_position != std::string::npos) {
        std::string ret_str = std::string(source, 0, delim_position);
        source.erase(0, delim_position + delim.length());
        return ret_str;
    } else {
        std::string ret_str = source;
        source.clear();
        return ret_str;
    }
}

std::vector<std::string> stringSplit(const std::string &source,
                                     const std::string &delim) {
    std::vector<std::string> result;
    std::string source_copy = source;

    for (std::string part = stringTok(source_copy, delim);;
         part = stringTok(source_copy, delim)) {
        result.push_back(part);

        if (source_copy.empty()) {
            break;
        }
    }

    return result;
}

std::string trimOverSpace(const std::string &source) {
    std::string destination = trimAll(source);
    std::string::size_type i = 0;
    std::string::size_type n = 0;

    while ((n = destination.find_first_of(" \t\r\n", i)) !=
           std::string::npos) {
        std::string::size_type j = destination.find_first_not_of(" \t\r\n", n);
        destination.replace(n, j - n, " ");
        i = n + 1;
    }

    return destination;
}
}; // end namespace stringtool
}; // end namespace cppbase
