// Name: Armen Merzaian
// Seneca Student ID: 060207024
// Seneca email: amerzanian@myseneca.ca
// Date of completion: Dec 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"
#include "Utilities.h"
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>


using namespace std;
namespace sdds{

    LineManager::LineManager() {
        m_cntCustomerOrder = 0;
        m_firstStation = nullptr;
    }


    //this constructor receives the name of the file that identifies the active stations on the assembly line
    // (example: AssemblyLine.txt) and the collection of workstations available for configuring the assembly line.
    //
    //The file contains the linkage between workstation pairs. The format of each record in the file is
    // WORKSTATION|NEXT_WORKSTATION
    // The records themselves are not in any particular order.
    //
    //This function stores the workstations in the order received from the file in the activeLine instance variable.
    // It loads the contents of the file, stores the address of the next workstation in each element of the collection,
    // identifies the first station in the assembly line and stores its address in the m_firstStation attribute.
    // This function also updates the attribute that holds the total number of orders in the pending queue.
    // If something goes wrong, this constructor reports an error.
    //
    //Note: to receive full marks, use STL algorithms throughout this function, except for iterating through the file records (one while loop);
    // marks will be deducted if you use any of for, while or do-while loops except for iterating through the file records.
    LineManager::LineManager(const string &file, const vector<Workstation *> &stations) {
        //This function stores the workstations in the order received from the file in the activeLine instance variable.
        ifstream assemblyLine(file);
        // It loads the contents of the file
        Utilities obj;
        size_t start = 0;
        bool more = true;

        string singleRecord;
        string token1_workstation;
        string token2_next_workstation;

        Workstation* workstation;
        Workstation* next_workstation;

        //for cout debugging purposes //not in final product
        vector<string> list;

        while(!assemblyLine.eof() && getline(assemblyLine, singleRecord)){
            token1_workstation = obj.extractToken(singleRecord, start, more);
            list.push_back(token1_workstation);
            for_each(stations.begin(), stations.end(), [&, this](Workstation* test) {
                auto found = std::find_if(stations.begin(), stations.end(), [&token1_workstation](Workstation* s) {
                    return s->getItemName() == token1_workstation;
                });
                return workstation = *found;
            });
            //stores the address of the next workstation in each element of the collection
            if (more) {
                token2_next_workstation = obj.extractToken(singleRecord, start, more);
                for_each(stations.begin(), stations.end(), [&, this](Workstation *test) {
                    auto found = std::find_if(stations.begin(), stations.end(),
                                              [&token2_next_workstation](Workstation *s) {
                                                  return s->getItemName() == token2_next_workstation;
                                              });
                    return next_workstation = *found;
                });
                if (next_workstation) workstation->setNextStation(next_workstation);
            }
            activeLine.push_back(workstation);
            more = true;
        }

        //for cout debugging purposes //not in final product
        cout << "activeLine.front(): " << activeLine.front()->getItemName() << ": " << activeLine.front()->getNextStation()->getItemName() << endl;
        cout << "--------------------" << endl;
        for(auto& i: activeLine){
            cout << i->getItemName() << ": ";
            if (i->getNextStation()) {
                cout << i->getNextStation()->getItemName() << endl;
            } else {
                cout << endl;
            }
        }
        cout << "--------------------" << endl << endl;

        //identifies the first station in the assembly line and stores its address in the m_firstStation attribute.
        m_firstStation = activeLine.front(); //why can't the first element in the activeLine be m_firstStation?

        m_cntCustomerOrder = pending.size();
        assemblyLine.close();

        /* old code
         * ifstream assemblyLine(file);

        Utilities obj;
        size_t start = 0;
        bool more = true;

        string singleRecord;
        string token1;
        string token2;

        Workstation* first;
        Workstation* second;

        while(!assemblyLine.eof() && getline(assemblyLine, singleRecord)){
            //extract the string of the first token from file
            token1 = obj.extractToken(singleRecord, start, more);
            //compare the string to all the stations available
            first = *find_if(stations.begin(), stations.end(), [&token1](const Workstation* workstation) {
                //if match occurs, return the address of that station, store the address in 'first'
                return workstation->getItemName() == token1;
            });
            //check if there is any more data after the deliminator
            if (more) {
                //extract the string of the second token from file
                token2 = obj.extractToken(singleRecord, start, more);
                //compare the string to all the stations available
                second = *find_if(stations.begin(), stations.end(), [&token2](const Workstation* workstation) {
                    //if match occurs, return the address of that station, store the address in 'second'
                    return workstation->getItemName() == token2;
                });
                //still in if(more)-check, for every workstation saved in first, set it's NextStation to the address of 'second'
                first->setNextStation(second);
            };
            //still in while() loop, add each 'first' workstation to the vector activeLine
            activeLine.push_back(first);
            //reset extraction utility parameters
            start = 0;
            more = true;
        }

         //assign pointer m_firstStation to the first element of the activeLine vector
        m_firstStation = activeLine.front();
         //This function also updates the attribute that holds the total number of orders in the pending queue.
        m_cntCustomerOrder = pending.size();
        assemblyLine.close();
         */
    }

    //this modifier reorders the workstations present in the instance variable activeLine (loaded by the constructor)
    // and stores the reordered collection in the same instance variable.
    // The elements in the reordered collection start with the first station, proceeds to the next,
    // and so forth until the end of the line.
    void LineManager::linkStations() {
        for (size_t i = 0; i < activeLine.size(); i++){
            for (size_t j = 0; j < activeLine.size(); j++){
                if (activeLine[i] == activeLine[j]->getNextStation()){
                    swap(activeLine[i-1], activeLine[j]);
                }
                if (activeLine[i]->getNextStation() == activeLine[j]){
                    swap(activeLine[i+1], activeLine[j]);
                }
            }
        }
    }

    //this modifier performs one iteration of operations on all of the workstations in the current assembly line by doing the following:
    //
    //    keeps track of the current iteration number (use a local variable)
    //    inserts into stream os the iteration number (how many times this function has been called by the client) in the format Line Manager Iteration: COUNT<endl>
    //    if the pending queue has a CustomerOrder object, moves the order at the front of the queue to the m_firstStation of the activeLine and remove it from the queue.
    //    This function moves only one order to the line on a single iteration.
    //    for each station on the line, executes one fill operation
    //    for each station on the line, attempts to move a CustomerOrder down the line
    //    return true if all customer orders (m_cntCustomerOrder) have been filled, otherwise returns false
    bool LineManager::run(ostream &os) {
        static size_t runCount = 0;
        os << "Line Manager Iteration: " << ++runCount << endl;
        if(!pending.empty()) {
            *m_firstStation += move(pending.front());
            pending.pop_front();
        }
        for (auto& s : activeLine)
        {
            s->fill(os);
        }
        for (auto& s : activeLine)
        {
            s->attemptToMoveOrder();
        }
        /*for(auto &i : activeLine){
            i->fill(os);
            i->attemptToMoveOrder();
        }*/
        return (completed.size() + incomplete.size() == m_cntCustomerOrder);
    }

    void LineManager::display(ostream &os) const {
        for (size_t i = 0; i < activeLine.size(); i++){
          activeLine[i]->display(os);
        }
    }


}
