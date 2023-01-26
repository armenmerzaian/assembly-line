// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Dec 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

using namespace std;

namespace sdds {
    class LineManager {

        std::vector<Workstation*> activeLine;
        size_t m_cntCustomerOrder;
        Workstation* m_firstStation;
    public:
        LineManager();
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void linkStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}


#endif //SDDS_LINEMANAGER_H
