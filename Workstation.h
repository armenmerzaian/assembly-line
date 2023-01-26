// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Dec 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
#include <iostream>
#include <string>

using namespace std;
namespace sdds {

    extern deque<CustomerOrder> pending;
    extern deque<CustomerOrder> completed;
    extern deque<CustomerOrder> incomplete;

    class Workstation: public Station {
        deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation = nullptr;
    public:
        Workstation(const string& singleRecord): Station(singleRecord){};

        Workstation& operator+=(CustomerOrder&& newOrder);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;

        Workstation(const Workstation&) = delete;//copy constructor
        Workstation& operator=(const Workstation&) = delete;//copy assignment
        Workstation(Workstation&& rh) = delete;//move constructor
        Workstation& operator=(Workstation&& ) = delete; //move assignment

    };

}


#endif //SDDS_WORKSTATION_H
