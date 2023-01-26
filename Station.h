// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Nov 27, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

using namespace std;

namespace sdds {

    class Station {
        int m_station;
        string m_itemName;
        string m_itemDesc;
        size_t m_itemSerial;
        size_t m_stockCount;
    public:
        Station(const string& singleRecord);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };

}


#endif //SDDS_STATION_H
