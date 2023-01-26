// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Dec 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"
#include <iostream>

using namespace std;

namespace sdds {

    deque<CustomerOrder> pending {};
    deque<CustomerOrder> completed {};
    deque<CustomerOrder> incomplete {};

    //this modifier fills the order at the front of the queue, if there are CustomerOrders in the queue;
    // otherwise, does nothing.
    void Workstation::fill(ostream &os) {
        if (!m_orders.empty() && !m_orders.front().isFilled()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    //attempts to move the order at the front of the queue to the next station in the assembly line:
    //
    //    if the order requires no more service at this station, move it to the next station
    //        if there is no next station in the assembly line, then the order is moved into completed queue
    //    if the order cannot be filled (not enough inventory), move the order to the next station.
    //        if there is no next station in the assembly line, then the order is moved into incomplete queue.
    //    if an order has been moved, return true; false otherwise.
    bool Workstation::attemptToMoveOrder() {
        bool _return = false;
        if (m_orders.front().isItemFilled(getItemName())) {
            if (!m_pNextStation) {
                completed.push_back(move(m_orders.front()));
                if (!completed.back().isFilled()){
                    incomplete.push_back(move(completed.back()));
                    completed.pop_back();
                }
            } else {
                *m_pNextStation += move(m_orders.front());
                _return = true;
            }
        } else {
            if (getQuantity() == 0 && m_pNextStation) {
                *m_pNextStation += move(m_orders.front());
                _return = true;
            } else if (getQuantity() == 0 && !m_pNextStation){
                incomplete.push_back(move(m_orders.front()));
            }
        }
        m_orders.pop_front();

        return _return;
    }

    //moves the CustomerOrder referenced in parameter newOrder to the back of the queue.
    Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
        m_orders.push_back(move(newOrder));
        return *this;
    }

    //this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation.
    // Parameter defaults to nullptr
    void Workstation::setNextStation(Workstation *station) {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const {
        return m_pNextStation;
    }

    //this query inserts the name of the Item for which the current object is responsible into stream os following the format:
    // ITEM_NAME --> NEXT_ITEM_NAME
    //
    //    if the current object is the last Workstation (m_pNextWorkstation is nullptr) this query inserts:
    //    ITEM_NAME --> END OF LINE.
    //    in either case, the message is terminated with an endline
    void Workstation::display(ostream &os) const {
        os << getItemName() << " --> ";
        if(m_pNextStation != nullptr) {
            os << m_pNextStation->getItemName();
        } else {
            os << "End of Line";
        }
        os << endl;
    }


}
