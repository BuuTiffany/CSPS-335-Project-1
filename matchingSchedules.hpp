/**──────────────────────────────────── ･ ｡ﾟ☆: *.☽ .* :☆ﾟ. ────────────────────────────────────*
 *          
 *                 Project 1: Implementing Algorithms - Matching Group Schedules
 *                              CPSC 335-02: Algorithm Engineering
 *                                Professor Ornella Irene Dsouza
 *                                           Fall 2023
 * 
 **──────────────────────────────────── ･ ｡ﾟ☆: *.☽ .* :☆ﾟ. ────────────────────────────────────*
 *                     
 *         Name:       Tiffany Buu
 *         Email:      tiffanybuu@csu.fullerton.edu
 *         CWID:       885404830
 * 
 **──────────────────────────────────── ･ ｡ﾟ☆: *.☽ .* :☆ﾟ. ────────────────────────────────────*/

/**  ∘₊✧────────────────────────────────────────────────✧₊∘ *
 *      Schedule.hpp
 *     
 *      Declares the class MatchingSchedules to hold one groups,
 *          * Times Unavailable
 *                  * A vector of TimeFrames
 *          * Working Hours
 *                  * A TimeFrame
 *   ∘₊✧────────────────────────────────────────────────✧₊∘ */

#ifndef MATCHINGSCHEDULE_HPP
#define MATCHINGSCHEDULE_HPP

    /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
    *          Include          *
    * ✧ ✦ ✧───────────────✧ ✦ ✧ */
        #include "schedule.hpp"

        #include <iostream>
        #include <fstream>
        #include <string>

    /* ✧ ✦ ✧─────────────✧ ✦ ✧ *
    *          Using          *
    * ✧ ✦ ✧─────────────✧ ✦ ✧ */
        using std::cout;
        using std::endl;
        using std::vector;
        using std::string;
        using std::to_string;

class MatchingSchedule 
{
    private:

        /* --------------------------- *
         *          Variables          *
         * --------------------------- */
			
            vector<Schedule*>* schedules_;
            vector<TimeFrame*>* potential_meeting_times_ ;
            int* meeting_duration_;
            TimeFrame* matching_working_hours_;

            bool debugging = false;
            string tab = "    ";
            string divider = "----------------------------------------------------------------------------------------------------";

            string centerText(string text)
            {
                int spaces = 50 - (text.size() / 2);
                string result;
                result.append(spaces, ' ');
                result = result + text;
                return result;
            }

	public:
		
        /* ✧ ✦ ✧────────────────────✧ ✦ ✧ *
         *          Constructors          *
         * ✧ ✦ ✧────────────────────✧ ✦ ✧ */

            MatchingSchedule ();
            MatchingSchedule (MatchingSchedule& other);
            MatchingSchedule (vector<Schedule*> schedules, int meeting_duration);
            MatchingSchedule (vector<string*> toMatch);

        /* ✧ ✦ ✧──────────────────✧ ✦ ✧ *
         *          Destructor          *
         * ✧ ✦ ✧──────────────────✧ ✦ ✧ */

            ~MatchingSchedule();

        /* ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ *
         *          Assignments & Operators          *
         * ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ */

            MatchingSchedule& operator= (const MatchingSchedule& other);
            bool operator== (const MatchingSchedule& other) const;
            bool operator!= (const MatchingSchedule& other) const;

        /* ✧ ✦ ✧─────────────────────────✧ ✦ ✧ *
         *          Getters & Setters          *
         * ✧ ✦ ✧─────────────────────────✧ ✦ ✧ */

        /* Getters */
            vector<Schedule*> getSchedules () const;
            int getMeetingDuration () const;
            vector<TimeFrame*> getPotentialMeetingTimes() const;

        /* Setters */  
            void setSchedules (vector<Schedule*> schedules);
            void setMeetingDuration (int meeting_duration);

        /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
         *          Methods          *
         * ✧ ✦ ✧───────────────✧ ✦ ✧ */

            void printTest();
            void printTestTab();
            string expectedOutput();
            void printExpectedOutput();
            void printExpectedOutputFull();
			
	private:

        /* ✧ ✦ ✧───────────────────────✧ ✦ ✧ *
         *          Private Methods          *
         * ✧ ✦ ✧───────────────────────✧ ✦ ✧ */

            void createSchedules (vector<string*> toMatch);
            void createPotentialMeetingTimes();
            void calculateMatchingWorkingHours();
            void calculatePotentialWorkingHours();
            void removeTimesUnderDuration();
            
};

#endif