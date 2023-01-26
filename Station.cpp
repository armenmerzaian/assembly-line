// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Nov 27, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"
#include "Utilities.h"
#include <iomanip>

using namespace std;

namespace sdds{

    static int id_generator = 0;
    static size_t m_widthField = 0;

    Station::Station(const string &singleRecord) : m_station{0}, m_itemName{""}, m_itemDesc{""}, m_itemSerial{0}, m_stockCount{0}{
        m_station = ++id_generator;
        Utilities obj;
        size_t start = 0;
        bool more = true;
        m_itemName = obj.extractToken(singleRecord, start, more);
        m_itemSerial = stoi(obj.extractToken(singleRecord, start, more));
        m_stockCount = stoi(obj.extractToken(singleRecord, start, more));
        if(m_itemName.size() > m_widthField) m_widthField = m_itemName.size();
        if (obj.getFieldWidth() > m_widthField) m_widthField = obj.getFieldWidth();
        m_itemDesc = obj.extractToken(singleRecord, start, more);
    }

    const std::string &Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_itemSerial++;
    }

    size_t Station::getQuantity() const {
        return m_stockCount;
    }

    void Station::updateQuantity() {
        m_stockCount--;
    }

    void Station::display(ostream &os, bool full) const {
        const int three = 3;
        const int six = 6;
        //[ID] Item: NAME [SERIAL]
        os << "[";
        os << setfill('0');
        os << setw(three) << m_station << "]";
        os << setfill(' ');
        os << " Item: " << left << setw(m_widthField) << getItemName();
        os << right << " [" << setfill('0');
        os << setw(six) << m_itemSerial << "]";
        os << setfill(' ');
        if (full){
            //Item NAME [SERIAL] Quantity: QTY Description: DESCRIPTION
            os << " Quantity: " << left << setw(m_widthField) << getQuantity() << right;
            os << right << " Description: " << m_itemDesc;
        }
        os << endl;
        /*if (!full){
            //[ID] Item: NAME [SERIAL]
            os << "[";
            os << setfill('0');
            os << setw(3) << m_station << "]";
            os << setfill(' ');
            os << " Item: " << left << setw(m_widthField) << getItemName();
            os << right << " [" << setfill('0');
            os << setw(6) << m_itemSerial << "]";
            os << setfill(' ');
            os << endl;
        } else{
            //Item NAME [SERIAL] Quantity: QTY Description: DESCRIPTION
            os << "[" << setfill('0');
            os << setw(3) << m_station << "]";
            os << setfill(' ');
            os << " Item: " << left << setw(m_widthField) << getItemName();
            os << right << " [" << setfill('0');
            os << setw(6) << m_itemSerial << "]";
            os << setfill(' ');
            os << " Quantity: " << left << setw(m_widthField) << getQuantity() << right;
            os << right << " Description: " << m_itemDesc;
            os << endl;
        }*/

    }
}
