// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Nov 27, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"


namespace sdds{

    static char m_delimiter = {};

    void Utilities::setFieldWidth(size_t newWidth){
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    /*
     * extracts a token from string str referred to by the first parameter

    This function uses the delimiter to extract the next token from str starting at position next_pos.
    If successful, this function returns a copy of the extracted token found, updates next_pos with the position of the next token, and sets more to true (false otherwise0.
    This function reports an exception if a delimiter is found at next_pos.
    This function updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
    Note: in this application, str represents a single line that has been read from an input file

     */
    std::string Utilities::extractToken(const string &str, size_t &next_pos, bool &more) {
        string extract;
        if (str.find(m_delimiter, next_pos) == next_pos) {
            more = false;
            throw string("No token.");
        }
        extract = str.substr(next_pos, (str.find(m_delimiter, next_pos) - next_pos));
        if ((str.find(m_delimiter, next_pos) == (size_t)-1) || extract.empty()) more = false;
        next_pos = (str.find(m_delimiter, next_pos)) + 1;
        if (extract.size() > getFieldWidth()) setFieldWidth(extract.size());
        return extract;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}
