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
 *      Declares the class Schedule to hold one user's:
 *          * Times Unavailable
 *                  * A vector of pointers to TimeFrame objects
 *          * Working Hours
 *                  * A TimeFrame object
 *   ∘₊✧────────────────────────────────────────────────✧₊∘ */

#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

    /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
    *          Include          *
    * ✧ ✦ ✧───────────────✧ ✦ ✧ */
        #include "timeFrame.hpp"
        
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

        

class Schedule {

    private:
        
        /* ✧ ✦ ✧─────────────────────────✧ ✦ ✧ *
         *          Private Variables          *
         * ✧ ✦ ✧─────────────────────────✧ ✦ ✧ */
			
            vector<TimeFrame*>* time_unavailable_;
            TimeFrame* working_hours_;
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

            Schedule ();
            Schedule (const Schedule& other);
            Schedule (vector<TimeFrame*> &time_unavailable, TimeFrame &working_hours);
            Schedule (string &time_unavailable, string &working_hours);

        /* ✧ ✦ ✧──────────────────✧ ✦ ✧ *
         *          Destructor          *
         * ✧ ✦ ✧──────────────────✧ ✦ ✧ */

            ~Schedule();

        /* ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ *
         *          Assignments & Operators          *
         * ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ */

            Schedule& operator= (const Schedule& other);
            bool operator== (const Schedule& other) const;
            bool operator!= (const Schedule& other) const;

        /* ✧ ✦ ✧─────────────────────────✧ ✦ ✧ *
         *          Getters & Setters          *
         * ✧ ✦ ✧─────────────────────────✧ ✦ ✧ */

        /* Getters */
            vector<TimeFrame*> getTimeUnavailable() const;
            TimeFrame getWorkingHours() const;

        /* Setters */   
            void setTimeUnavailable(const vector<TimeFrame*>& time_unavailable);
            void setWorkingHours(const TimeFrame& working_hours);

        /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
         *          Methods          *
         * ✧ ✦ ✧───────────────✧ ✦ ✧ */

            string getTimeUnavailableString();
            string getWorkingHoursString();

        /* ✧ ✦ ✧────────────────────────✧ ✦ ✧ *
         *          Prints for Debug          *
         * ✧ ✦ ✧────────────────────────✧ ✦ ✧ */

            void printTimeUnavailable();
            void printTimeUnavailableTab();
            void printWorkingHours();
            void printExpectedOutput();
            void printExpectedOutputTab();

	private:

        /* ✧ ✦ ✧───────────────────────✧ ✦ ✧ *
         *          Private Methods          *
         * ✧ ✦ ✧───────────────────────✧ ✦ ✧ */

            void stringToTimeUnavailable (string times);
            void stringToWorkingHours (string times);

};

#endif