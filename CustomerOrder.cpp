// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Nov 27, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

namespace sdds {

    static size_t m_widthField;


    CustomerOrder::CustomerOrder() {
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;
    }

    CustomerOrder::CustomerOrder(const string &singleRecord) : CustomerOrder() {
        Utilities obj;
        size_t start = 0;
        bool more = true;
        vector<Item*> tempList{};

        m_name = obj.extractToken(singleRecord, start, more);
        m_product = obj.extractToken(singleRecord, start, more);
        size_t vecStart = start;
        if (more) {
            //figure out how many items are going in the list
            while(more){
                //add items to a vector
                tempList.push_back(new Item(obj.extractToken(singleRecord, vecStart, more)));
                m_cntItem = tempList.size();
            }
            m_lstItem = new Item*[m_cntItem];
            for (size_t i = 0; i < m_cntItem; i++){
                m_lstItem[i] = tempList[i];
            }
        }
        if (more) more = false;
        if (obj.getFieldWidth() > m_widthField) m_widthField = obj.getFieldWidth();

    }

    CustomerOrder::CustomerOrder(const CustomerOrder &cusOrder_throwERR) {
        throw "";
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&rh) noexcept {
        *this = (move(rh));
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&rh) noexcept {
        if (this != &rh) {
            this->m_name = rh.m_name;
            this->m_product = rh.m_product;
            this->m_cntItem = rh.m_cntItem;
            this->m_lstItem = rh.m_lstItem;
            rh.m_lstItem = nullptr;
            rh.m_name = "";
            rh.m_product = "";
            rh.m_cntItem = 0;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        if (m_lstItem && m_lstItem != nullptr) {
            for (size_t i = 0; i < m_cntItem; i++) {
                if (m_lstItem[i] != nullptr) {
                    delete this->m_lstItem[i];
                    this->m_lstItem[i] = nullptr;
                }
            }
            delete[] this->m_lstItem;
            this->m_lstItem = nullptr;
        }
    }

    bool CustomerOrder::isFilled() const {
        int check = 0;
        for (size_t i = 0; i < m_cntItem; i++){
            if (m_lstItem[i]->m_isFilled) check++;
        }
        if(check == m_cntItem) return true;
        return false;
    }

    bool CustomerOrder::isItemFilled(const string &itemName) const {
        bool itemfilled = false;
        for(size_t i = 0; i < m_cntItem; i++){
            if(itemName == m_lstItem[i]->m_itemName){
                if (m_lstItem[i]->m_isFilled) itemfilled = true;
            } else {
                itemfilled = true;
            }
        }
        return itemfilled;
    }

    /*
     *
        if the order doesn't contain the item handled, this function does nothing
        if the order contains items handled, and the Station's inventory contains at least one item,
         this function fills the order with one item.
         It subtracts 1 from the inventory and updates Item::m_serialNumber and Item::m_isFilled.
         It also prints the message Filled NAME, PRODUCT [ITEM_NAME].
        if the order contains items handled but unfilled, and the inventory is empty, this function prints the
        message Unable to fill NAME, PRODUCT [ITEM_NAME].
        all messages printed are terminated by an endline
     */
    void CustomerOrder::fillItem(Station &station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (station.getItemName() == m_lstItem[i]->m_itemName) {
                if (station.getQuantity() >= 1) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled ";
                } else {
                    os << "    Unable to fill ";
                }
                os << this->m_name << ", " << this->m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
        }
    }


    /*
     *  CUSTOMER_NAME - PRODUCT
        [SERIAL] ITEM_NAME - STATUS
        [SERIAL] ITEM_NAME - STATUS
     */
    void CustomerOrder::display(ostream &os) const {
        const int six = 6;
        os << m_name << " - " << m_product << endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << setfill('0') << setw(six) << m_lstItem[i]->m_serialNumber << setfill(' ') << "] ";
            os << setw(m_widthField) << left << m_lstItem[i]->m_itemName << right << " - ";
            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
        }
    }
}
