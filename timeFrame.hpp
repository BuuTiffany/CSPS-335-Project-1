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
 *      timeFrame.hpp
 *     
 *      Declares the class TimeFrame to hold the start and end times
 *   ∘₊✧────────────────────────────────────────────────✧₊∘ */

#ifndef TIMEFRAME_HPP
#define TIMEFRAME_HPP

    /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
     *          Include          *
     * ✧ ✦ ✧───────────────✧ ✦ ✧ */

        #include <cstdio>
        #include <stdio.h>
        #include <iostream>
        #include <fstream>
        #include <string>

    /* ✧ ✦ ✧─────────────✧ ✦ ✧ *
     *          Using          *
     * ✧ ✦ ✧─────────────✧ ✦ ✧ */
        using std::cout;
        using std::endl;
        using std::string;

class TimeFrame {

    private:

        /* ✧ ✦ ✧─────────────────────────✧ ✦ ✧ *
         *          Private Variables          *
         * ✧ ✦ ✧─────────────────────────✧ ✦ ✧ */
			
            int* start_time_hour_;
            int* start_time_minute_;
            int* end_time_hour_;
            int* end_time_minute_;

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

            TimeFrame ();
            TimeFrame (const TimeFrame& other);
            TimeFrame (int start_time_hour, int start_time_minute, int end_time_hour, int end_time_minute);

        /* ✧ ✦ ✧──────────────────✧ ✦ ✧ *
         *          Destructor          *
         * ✧ ✦ ✧──────────────────✧ ✦ ✧ */

            ~TimeFrame ();

        /* ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ *
         *          Assignments & Operators          *
         * ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ */

            TimeFrame& operator=(const TimeFrame& other);
            bool operator==(const TimeFrame& other) const;
            bool operator!=(const TimeFrame& other) const;

        /* ✧ ✦ ✧─────────────────────────✧ ✦ ✧ *
         *          Getters & Setters          *
         * ✧ ✦ ✧─────────────────────────✧ ✦ ✧ */

        /* Getters */
            int getStartTimeHour () const;
            int getStartTimeMinute () const;
            int getEndTimeHour () const;
            int getEndTimeMinute () const;

        /* Setters s*/ 
            void setStartTimeHour (const int& new_start_time_hour);
            void setStartTimeMinute (const int& new_start_time_minute);
            void setEndTimeHour (const int& new_end_time_hour);
            void setEndTimeMinute (const int& new_end_time_minute);
            void setTimes (int start_time_hour, int start_time_minute, int end_time_hour, int end_time_minute);
        
        /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
         *          Methods          *
         * ✧ ✦ ✧───────────────✧ ✦ ✧ */

            void adjustTimes (int& hour, int& minute);
            bool isValid ();
            int calculateDurationInMinutes();
            string startTimeString ();
            string endTimeString();
            string timeFrameString();
            string outputTimeFrameString();

        /* ✧ ✦ ✧────────────────────────✧ ✦ ✧ *
         *          Prints for Debug          *
         * ✧ ✦ ✧────────────────────────✧ ✦ ✧ */

            void printStartTime ();
            void printEndTime();
            void printTimeFrame();
            void printOutput();
};

#endif