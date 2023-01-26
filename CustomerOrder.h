// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Nov 27, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
    class CustomerOrder {

        struct Item
        {
            std::string m_itemName;
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            Item(const std::string& src) : m_itemName(src) {};
        };

        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem;

    public:
        CustomerOrder();
        CustomerOrder(const std::string& singleRecord);
        CustomerOrder(const CustomerOrder& cusOrder_throwERR);//copy constructor
        CustomerOrder& operator=(const CustomerOrder&) = delete;//copy assignment
        CustomerOrder(CustomerOrder&& rh) noexcept;//move constructor
        CustomerOrder& operator=(CustomerOrder&& rh) noexcept; //move assignment

        ~CustomerOrder();

        bool isFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;

    };

}


#endif //SDDS_CUSTOMERORDER_H
