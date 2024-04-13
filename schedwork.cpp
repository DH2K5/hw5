#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduler (
    const AvailabilityMatrix&,
    const size_t,
    const size_t,
    DailySchedule&,
    map<Worker_T, size_t>,
    size_t,
    size_t
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    if(avail[0].size() < dailyNeed){
        return false;
    }
    map<Worker_T, size_t> days;
    for(size_t i = 0; i < avail[0].size(); i++){
        days.insert(pair<Worker_T, size_t> (i, 0));
    }
    for(size_t i = 0; i < avail.size(); i++){
        vector<Worker_T> day;
        sched.push_back(day);
        for (size_t j = 0; j < dailyNeed; j++)
        {
            sched[i].push_back(0);
        }
    }
    return scheduler(avail, dailyNeed, maxShifts, sched, days, 0, 0);
}

bool scheduler (
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    map<Worker_T, size_t> days,
    size_t currentDay,
    size_t currentshift
)
{
    if(currentDay >= avail.size()){
        return true;
    }
    for(int i = 0; i < ((int) avail[currentDay].size()); i++){
        sched[currentDay][currentshift] = i;
        days[i]++;
        currentshift++;
        if((avail[currentDay][i] == 1) && (days[i] <= maxShifts)){
            if(currentshift == dailyNeed){
                if(scheduler(avail, dailyNeed, maxShifts, sched, days, currentDay+1, 0)){
                    return true;
                }
            }
            else{
                if(scheduler(avail, dailyNeed, maxShifts, sched, days, currentDay, currentshift)){
                    return true;
                }
            }
        }
        currentshift--;
        days[i]--;
        sched[currentDay][currentshift] = 0;
    }
    return false;
}