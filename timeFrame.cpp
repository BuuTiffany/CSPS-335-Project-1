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
 *      timeFrame.cpp
 *     
 *      Defines the TimeFrame class's:
 *          * Constructors
 *          * Destructors
 *          * Operators
 *          * Methods
 *   ∘₊✧────────────────────────────────────────────────✧₊∘ */  

    /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
    *          Include          *
    * ✧ ✦ ✧───────────────✧ ✦ ✧ */
        #include "timeFrame.hpp"

        #include <cstdio>
        #include <stdio.h>
        #include <iostream>
        #include <fstream>
        #include <string>

    /* ✧ ✦ ✧─────────────✧ ✦ ✧ *
     *          Using          *
     * ✧ ✦ ✧─────────────✧ ✦ ✧ */
        using std::cout, std::endl;
        using std::string;

    /* ✧ ✦ ✧────────────────────✧ ✦ ✧ *
        *          Constructors          *
        * ✧ ✦ ✧────────────────────✧ ✦ ✧ */

        TimeFrame::TimeFrame () 
        {
            this->start_time_hour_ = new int (0);
            this->start_time_minute_ = new int (0);
            this->end_time_hour_ = new int(23);
            this->end_time_minute_ = new int(59);
        }
        TimeFrame::TimeFrame (const TimeFrame& other) 
        {
            this->start_time_hour_ = new int (other.getStartTimeHour());
            this->start_time_minute_ = new int (other.getStartTimeMinute());
            this->end_time_hour_ = new int(other.getEndTimeHour());
            this->end_time_minute_ = new int(other.getEndTimeMinute());
        }
        TimeFrame::TimeFrame (int start_time_hour, int start_time_minute, int end_time_hour, int end_time_minute) 
                                                                                            // Total: 28
        {
            setTimes(start_time_hour, start_time_minute, end_time_hour, end_time_minute);   // (1) -> + 28
        }

    /* ✧ ✦ ✧──────────────────✧ ✦ ✧ *
     *          Destructor          *
     * ✧ ✦ ✧──────────────────✧ ✦ ✧ */

        TimeFrame::~TimeFrame () 
        {
            delete this->start_time_hour_;
            delete this->start_time_minute_;
            delete this->end_time_hour_;
            delete this->end_time_minute_;
        }

    /* ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ *
     *          Assignments & Operators          *
     * ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ */

        TimeFrame& TimeFrame::operator=(const TimeFrame& other)
        {
            TimeFrame* ptr = new TimeFrame(other);
            // Sanity check to insure we aren't copying the same thing
            if (*this != *ptr)
            {
                *this->start_time_hour_ = ptr->getStartTimeHour();
                *this->start_time_minute_ = ptr->getStartTimeMinute();
                *this->end_time_hour_ = ptr->getEndTimeHour();
                *this->end_time_minute_ = ptr->getEndTimeMinute();
            }
            delete ptr;
            // Return the item the object
            return *this;
        } 
        bool TimeFrame::operator==(const TimeFrame& other) const
        {
            TimeFrame* ptr = new TimeFrame(other);
            if (*this->start_time_hour_ != ptr->getStartTimeHour() ||
                *this->start_time_minute_ != ptr->getStartTimeMinute() ||
                *this->end_time_hour_ != ptr->getEndTimeHour() ||
                *this->end_time_minute_ != ptr->getEndTimeMinute())
            {
                delete ptr;
                return false;
            }
            delete ptr;
            return true;
        }
        bool TimeFrame::operator!=(const TimeFrame& other) const
    {
        TimeFrame* ptr = new TimeFrame(other);
        if (*this->start_time_hour_ == ptr->getStartTimeHour() ||
            *this->start_time_minute_ == ptr->getStartTimeMinute() ||
            *this->end_time_hour_ == ptr->getEndTimeHour() ||
            *this->end_time_minute_ == ptr->getEndTimeMinute())
        {
            delete ptr;
            return false;
        }
        delete ptr;
        return true;
    }

    /* ✧ ✦ ✧─────────────────────────✧ ✦ ✧ *
     *          Getters & Setters          *
     * ✧ ✦ ✧─────────────────────────✧ ✦ ✧ */

    /* Getters */
        int TimeFrame::getStartTimeHour () const
        {
            return *this->start_time_hour_;
        }
        int TimeFrame::getStartTimeMinute () const
        {
            return *this->start_time_minute_;
        }
        int TimeFrame::getEndTimeHour () const
        {
            return *this->end_time_hour_;
        }
        int TimeFrame::getEndTimeMinute () const
        {
            return *this->end_time_minute_;
        }

    /* Setters */  
        void TimeFrame::setStartTimeHour (const int& new_start_time_hour)           // Total: 3
        { 
            // If time is after 23:00, set to 23:00
            if (new_start_time_hour > 23)                                           // +1
            {
                // throw std::range_error ("Hours must be between 00 - 23");
                
                if (debugging)
                {
                    cout    << "Starting hour input (" << new_start_time_hour << ") is greater than 23:00" << endl
                            << "Setting hour to 23:00";
                }

                this->start_time_hour_ = new int(23);                               //      (1)
            }
            // If hour is before 00:00 set to 00:00
            else if (new_start_time_hour < 0)                                       // +1
            {
                // throw std::range_error ("Hours must be between 00 - 23");
                if (debugging)
                {
                    cout    << "Starting hour input (" << new_start_time_hour << ") is earlier than 00:00" << endl
                            << "Setting time to 00:00";
                }

                this->start_time_hour_ = new int(0);                                //      (1)
            }
            else
            {
                this->start_time_hour_ = new int(new_start_time_hour);              //      +1
            }
            
        }
        void TimeFrame::setStartTimeMinute (const int& new_start_time_minute) 
        {
            // If time is after XX:59, set to XX:59
            if (new_start_time_minute > 59) 
            {
                // throw std::range_error ("Minutes must be between 00 - 59");
                
                if (debugging)
                {
                    cout    << "Starting Minute input (" << new_start_time_minute << ") is greater than XX:59" << endl
                            << "Setting hour to XX:59";
                }

                this->start_time_minute_ = new int(59);
            }
            // If hour is before 00:00 set to 00:00
            else if (new_start_time_minute < 0) 
            {
                // throw std::range_error ("Hours must be between 00 - 23");
                
                if (debugging)
                {
                    cout    << "Starting minute input (" << new_start_time_minute << ") is earlier than XX:00" << endl
                            << "Setting time to XX:00";
                }

                this->start_time_minute_ = new int(0);
            }
            else
            {
                this->start_time_minute_ = new int(new_start_time_minute);
            }
        }   
        void TimeFrame::setEndTimeHour (const int& new_end_time_hour) 
        {
            // If time is after 23:00, set to 23:00
            if (new_end_time_hour > 23) 
            {
                // throw std::range_error ("Hours must be between 00 - 23");
                
                if (debugging)
                {
                    cout    << "Ending hour input (" << new_end_time_hour << ") is greater than 23:00" << endl
                            << "Setting hour to 23:00";
                }

                this->end_time_hour_ = new int(23);
            }
            // If hour is before 00:00 set to 00:00
            else if (new_end_time_hour < 0) 
            {
                // throw std::range_error ("Hours must be between 00 - 23");
                
                if (debugging)
                {
                    cout    << "Ending hour input (" << new_end_time_hour << ") is earlier than 00:00" << endl
                            << "Setting time to 00:00";
                }

                this->end_time_hour_ = new int(0);
            }
            else
            {
                this->end_time_hour_ = new int(new_end_time_hour);
            }
        }
        void TimeFrame::setEndTimeMinute (const int& new_end_time_minute) 
        {
            // If time is after XX:59, set to XX:59
            if (new_end_time_minute > 59) 
            {
                // throw std::range_error ("Minutes must be between 00 - 59");
                
                if (debugging)
                {
                    cout    << "Ending Minute input (" << new_end_time_minute << ") is greater than XX:59" << endl
                            << "Setting hour to XX:59";
                }

                this->end_time_minute_ = new int(59);
            }
            // If hour is before 00:00 set to 00:00
            else if (new_end_time_minute < 0) 
            {
                // throw std::range_error ("Hours must be between 00 - 23");
                
                if (debugging)
                {
                    cout    << "Ending minute input (" << new_end_time_minute << ") is earlier than XX:00" << endl
                            << "Setting time to XX:00";
                }

                this->end_time_minute_ = new int(0);
            }
            else
            {
                this->end_time_minute_ = new int(new_end_time_minute);
            }
        }
        void TimeFrame::setTimes (int start_time_hour, int start_time_minute, int end_time_hour, int end_time_minute)
                                                                                // Total: 28
        {
            if (debugging)
            {
                cout    << tab << tab << tab << tab << tab << "Times Inputed:" << endl
                        << tab << tab << tab << tab << tab << tab << "* Starting Hour: " << start_time_hour << endl
                        << tab << tab << tab << tab << tab << tab << "* Starting Minute: " << start_time_minute << endl
                        << tab << tab << tab << tab << tab << tab << "* Ending Hour: " << end_time_hour << endl
                        << tab << tab << tab << tab << tab << tab << "* Ending Minute: " << end_time_minute << endl << endl;
                cout    << tab << tab << tab << tab << tab << "Adjusting Starting Time" << endl << endl;
            }
            // Set Starting Time
            adjustTimes(start_time_hour, start_time_minute);                    // (1) -> +12
            if (debugging)
            {
                cout    << tab << tab << tab << tab << tab << "Starting Times after Adjustment:" << endl
                        << tab << tab << tab << tab << tab << tab << "* Starting Hour: " << start_time_hour << endl
                        << tab << tab << tab << tab << tab << tab << "* Starting Minute: " << start_time_minute << endl << endl;
            }

            // Set Ending Time
            adjustTimes(end_time_hour, end_time_minute);                        // (1) -> +12
            if (debugging)
            {
                cout    << tab << tab << tab << tab << tab << "Ending Times after Adjustment:" << endl
                        << tab << tab << tab << tab << tab << tab << "* Ending Hour: " << end_time_hour << endl
                        << tab << tab << tab << tab << tab << tab << "* Ending Minute: " << end_time_minute << endl << endl;
            }

            this->start_time_hour_ = new int (start_time_hour);                 // +1
            this->start_time_minute_ = new int (start_time_minute);             // +1
            this->end_time_hour_ = new int(end_time_hour);                      // +1
            this->end_time_minute_ = new int(end_time_minute);                  // +1

            if (debugging)
            {
                cout    << tab << tab << tab << tab << tab << "Final Times Inputed:" << endl
                        << tab << tab << tab << tab << tab << tab << "* Starting Hour: " << *this->start_time_hour_ << endl
                        << tab << tab << tab << tab << tab << tab << "* Starting Minute: " << *this->start_time_minute_ << endl
                        << tab << tab << tab << tab << tab << tab << "* Ending Hour: " << *this->end_time_hour_ << endl
                        << tab << tab << tab << tab << tab << tab << "* Ending Minute: " << *this->end_time_minute_ << endl << endl;
            }
        }

    /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
     *          Methods          *
     * ✧ ✦ ✧───────────────✧ ✦ ✧ */

        void TimeFrame::adjustTimes (int& hour, int& minute)
                                                        // Total: 12
        {
            int minutesToHours = 0;                     // +1

            if (debugging)
            {
                cout    << tab << tab << tab << tab << tab << "Times:" << endl
                        << tab << tab << tab << tab << tab << tab << "* Hour: " << hour << endl
                        << tab << tab << tab << tab << tab << tab << "* Minute: " << minute << endl << endl;
            }

            // Set any negative numbers
            if (hour < 0)                               // +1
            {
                hour = 0;                               //      +1
                if (debugging)
                {
                    cout    << tab << tab << tab << tab << tab << tab << "Hour is less than 0, setting hour to 0" << endl;
                }
            }
            if (minute < 0)                             // +1
            {
                minute = 0;                             //      +1
                if (debugging)
                {
                    cout    << tab << tab << tab << tab << tab << tab << "Minute is less than 0, setting minute to 0" << endl;
                }
            }

            // If minutes is 60 minutes or more
            if (minute > 59)                            // +1
            {
                // Calculate how many hours in minutes
                minutesToHours = minute/60;             //      +1
                // Set the minutes to remainders
                minute = minute % 60;                   //      +1
                // Add the extra hours to hours int
                hour += minutesToHours;                 //      +1
                if (debugging)
                {
                    cout    << tab << tab << tab << tab << tab << tab << "Minute is over 60 minutes, converting to hours" << endl;
                    cout    << tab << tab << tab << tab << tab << tab << "Conversion:" << endl
                            << tab << tab << tab << tab << tab << tab << tab << "* Minutes to Hours Conversion: " << minutesToHours << endl
                            << tab << tab << tab << tab << tab << tab << tab << "* New Minute: " << minute << endl 
                            << tab << tab << tab << tab << tab << tab << tab << "* New Hour: " << hour << endl << endl;
                }
            }
            
            // If hour is over 23:00
            if (hour > 23)                              // +1
            {
                // Set time to 23:59
                hour = 23;                              //      +1
                minute = 59;                            //      +1
                if (debugging)
                {
                    cout    << tab << tab << tab << tab << tab << tab << "Hour is over 23:59, setting time to 23:59" << endl;
                }
            }
        }
        bool TimeFrame::isValid ()
        // Total: 3
        {
            // +1
            if ((*this->start_time_hour_ > *this->end_time_hour_) || (*this->start_time_hour_ == *this->end_time_hour_ && this->start_time_minute_ >= this->end_time_minute_))
            {
                if (debugging)
                {
                    cout    << tab << tab << tab << tab << tab << "Timeframe is invalid" << endl 
                            << tab << tab << tab << tab << tab << tab << "* Starting Hour: " << *this->start_time_hour_ << endl
                            << tab << tab << tab << tab << tab << tab << "* Starting Minute: " << *this->start_time_minute_ << endl
                            << tab << tab << tab << tab << tab << tab << "* Ending Hour: " << *this->end_time_hour_ << endl
                            << tab << tab << tab << tab << tab << tab << "* Ending Minute: " << *this->end_time_minute_ << endl
                            << endl;
                }   
                // +1
                return false;
            }
            if (debugging)
                {
                    cout    << tab << tab << tab << tab << tab << "Timeframe is valid" << endl 
                            << endl;
                }   
            // +1
            return true;
        }
        int TimeFrame::calculateDurationInMinutes() // Total: +4
        {
            // Get Starting Time in Minutes
            int startingTime = (60 * *this->start_time_hour_) + *this->start_time_minute_;

            // Get Ending Time in Minutes
            int endingTime = (60 * *this->end_time_hour_) + *this->end_time_minute_;

            int result = endingTime - startingTime;
            return result;
        }
        // Creates a string with format
        // ##:##
        // i.e 23:59
        string TimeFrame::startTimeString () 
        {
            char buffer [6];
            snprintf(buffer, 6, "%.2i:%.2i", *this->start_time_hour_, *this->start_time_minute_);
            string result = buffer;
            return result;
        }
        // Creates a string with format
        // ##:##
        // i.e 23:59
        string TimeFrame::endTimeString() 
        {
            char buffer [6];
            snprintf(buffer, 6, "%.2i:%.2i", *this->end_time_hour_, *this->end_time_minute_);
            string result = buffer;
            return result;
        }
        string TimeFrame::timeFrameString() 
        {
            string result = startTimeString() + " - " + endTimeString();
            return result;
        }
        // [’15:00’, ’16:00’]
        string TimeFrame::outputTimeFrameString() // Total: 2
        {
            string result = "[\'" + startTimeString() + "\',\'" + endTimeString() + "\']"; // +1
            return result;                                                                  // +1
        }

    /* ✧ ✦ ✧────────────────────────✧ ✦ ✧ *
     *          Prints for Debug          *
     * ✧ ✦ ✧────────────────────────✧ ✦ ✧ */

        void TimeFrame::printStartTime () 
        {
            string result = startTimeString();
            cout << result << endl;
        }
        void TimeFrame::printEndTime() 
        {
            string result = endTimeString();
            cout << result << endl;
        }
        void TimeFrame::printTimeFrame() 
        {
            string result = timeFrameString();
            cout << result << endl;
        }
        void TimeFrame::printOutput()
        {
            string result = outputTimeFrameString();
            cout << result << endl;
        }
