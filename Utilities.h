// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Nov 27, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

using namespace std;

namespace sdds {

    class Utilities {
        size_t m_widthField = 1;
    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };

}


#endif //SDDS_UTILITIES_H
