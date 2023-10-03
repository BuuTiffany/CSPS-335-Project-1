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
 *      Schedule.cpp
 *     
 *      Defines the Schedule class's:
 *          * Constructors
 *          * Destructors
 *          * Operators
 *          * Methods
 *   ∘₊✧────────────────────────────────────────────────✧₊∘ */

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
        using std::cout, std::endl;
        using std::vector;
        using std::string;

    /* ✧ ✦ ✧────────────────────✧ ✦ ✧ *
     *          Constructors          *
     * ✧ ✦ ✧────────────────────✧ ✦ ✧ */

        Schedule::Schedule ()
            {
                this->time_unavailable_ = new vector<TimeFrame*> (); 
                this->working_hours_ = new TimeFrame();
            }
        Schedule::Schedule (const Schedule& other)
            {
                this->time_unavailable_ = new vector<TimeFrame*> (other.getTimeUnavailable()); 
                this->working_hours_ = new TimeFrame(other.getWorkingHours());
            }
        Schedule::Schedule (vector<TimeFrame*> &time_unavailable, TimeFrame &working_hours)
            {
                this->time_unavailable_ = new vector<TimeFrame*> (time_unavailable); 
                this->working_hours_ = new TimeFrame(working_hours);
            }
        Schedule::Schedule (string &time_unavailable, string &working_hours)                    // Total: 42n + 40
            {
                if (debugging)
                {
                    cout << tab << "Creating Schedule Object . . ." << endl;
                    cout << tab << tab << "Input Time Unavailable: " << time_unavailable << endl;
                    cout << tab << tab << "Input Working Hours: " << working_hours << endl << endl;

                    cout << tab << tab << "Inputing Unavailable Times . . ." << endl << endl;
                }
                stringToTimeUnavailable(time_unavailable);                                      // (1) -> +37n +6

                if (debugging)
                {
                    cout << tab << tab << "Inputing Working Hours . . ." << endl << endl;
                }
                stringToWorkingHours(working_hours);                                            // (1) -> +5n +34
            }

    /* ✧ ✦ ✧──────────────────✧ ✦ ✧ *
     *          Destructor          *
     * ✧ ✦ ✧──────────────────✧ ✦ ✧ */

        Schedule::~Schedule()
        {
            for (auto pointer : *this->time_unavailable_)
            {
                delete pointer;
            }

            delete this->time_unavailable_;
            delete this->working_hours_;
        }

    /* ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ *
     *          Assignments & Operators          *
     * ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ */

        Schedule& Schedule::operator= (const Schedule& other) 
        {
            Schedule* ptr = new Schedule(other);
            // Sanity check
            if (*this != *ptr) 
            {
                *this->time_unavailable_ = ptr->getTimeUnavailable();
                *this->working_hours_ = ptr->getWorkingHours();
            }
            delete ptr;
            return *this;
        } 
        bool Schedule::operator== (const Schedule& other) const
        {
            Schedule* ptr = new Schedule(other);
            if (*this->time_unavailable_ != ptr->getTimeUnavailable() ||
                *this->working_hours_ != ptr->getWorkingHours())
            {
                delete ptr;
                return false;
            }
            delete ptr;
            return true;
        }
        bool Schedule::operator!= (const Schedule& other) const
        {
            Schedule* ptr = new Schedule(other);
            if (*this->time_unavailable_ == ptr->getTimeUnavailable() ||
                *this->working_hours_ == ptr->getWorkingHours())
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
        vector<TimeFrame*> Schedule::getTimeUnavailable() const
        {
            return *this->time_unavailable_;
        }
        TimeFrame Schedule::getWorkingHours() const
        {
            return *this->working_hours_;
        }

    /* Setters */   
        void Schedule::setTimeUnavailable(const vector<TimeFrame*>& time_unavailable)
        {
            this->time_unavailable_ = new vector<TimeFrame*> (time_unavailable);
        }
        void Schedule::setWorkingHours(const TimeFrame& working_hours)
        {
            this->working_hours_ = new TimeFrame (working_hours);
        }

    /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
     *          Methods          *
     * ✧ ✦ ✧───────────────✧ ✦ ✧ */

        string Schedule::getTimeUnavailableString() 
        {
            string result = "[";

            for (TimeFrame* times : *this->time_unavailable_)
            {
                result = result + times->outputTimeFrameString();

                if (*times != *(this->time_unavailable_->at(this->time_unavailable_->size()-1)))
                {
                    result = result + ",";
                }
            }

            result = result + "]";

            return result;
        }
        string Schedule::getWorkingHoursString() 
        {
            return this->working_hours_->outputTimeFrameString();
        }

    /* ✧ ✦ ✧────────────────────────✧ ✦ ✧ *
     *          Prints for Debug          *
     * ✧ ✦ ✧────────────────────────✧ ✦ ✧ */

        void Schedule::printTimeUnavailable() 
        {
            cout    << "Time Unavailable: " << endl;

            for (auto times : *this->time_unavailable_)
            {
                cout << tab << "* " << times->timeFrameString() << endl;
            }

            cout    << endl;
        }
        void Schedule::printTimeUnavailableTab() 
        {
            cout    << tab << "Time Unavailable: " << endl;

            for (auto times : *this->time_unavailable_)
            {
                cout << tab << tab << tab << "* " << times->timeFrameString() << endl;
            }

            cout    << endl;
        }
        void Schedule::printWorkingHours() 
        {
            cout    << "Working Hours: " << endl;
            cout    << tab << "* " << this->working_hours_->timeFrameString() << endl << endl;
        }
        void Schedule::printExpectedOutput() 
        {
            cout    << "Time Unavailable: " << endl;
            if (this->time_unavailable_->empty())
            {
                cout << tab << "* No Times Unavailable" << endl;
            }
            else
            {
                for (auto times : *this->time_unavailable_)
                {
                    cout << tab << "* " << times->outputTimeFrameString() << endl;
                }
            }
            cout    << "Working Hours: " << endl;
            cout    << tab << "* " << this->working_hours_->outputTimeFrameString() << endl << endl;
        }
        void Schedule::printExpectedOutputTab() 
        {
            cout    << tab << tab << "Time Unavailable: " << endl;
            if (this->time_unavailable_->empty())
            {
                cout << tab << tab << tab << "* No Times Unavailable" << endl;
            }
            else
            {
                for (auto times : *this->time_unavailable_)
                {
                    cout << tab << tab << tab << "* " << times->outputTimeFrameString() << endl;
                }
            }
            cout    << tab << tab << "Working Hours: " << endl;
            cout    << tab << tab << tab << "* " << this->working_hours_->outputTimeFrameString() << endl << endl;
        }

    /* ✧ ✦ ✧───────────────────────✧ ✦ ✧ *
     *          Private Methods          *
     * ✧ ✦ ✧───────────────────────✧ ✦ ✧ */

        void Schedule::stringToTimeUnavailable (string times)                           // Total: 37n+ 6
        {
            /* ✧ ✦ ✧─────────────────✧ ✦ ✧ *
            *          Variables          *
            * ✧ ✦ ✧─────────────────✧ ✦ ✧ */

            vector<TimeFrame*> timeVector;                                              // +1
            TimeFrame* tempTimeFrame;                                                   // +1
            string tempString;                                                          // +1
            vector<int> timeNums;                                                       // +1
            int timeNum;                                                                // +1

            /* Isolating the Numbers
            * Go through string to find each time and convert to time frames
            * */

            if (debugging)
            {
                cout    << tab << tab << tab << "Times: " << times << endl
                        << tab << tab << tab << "Reading input . . ." << endl << endl;
            }

            // Iterate through string to find numbers
            for (int i = 0; i < times.length(); i++)                                    // n * (
            {
                // Check if character is a number
                if (isdigit(times.at(i)))                                               //      +1
                {
                    // If number is found add to string for nums
                    tempString += times.at(i);                                          //          (1) (Not included: smaller of if)
                }
                // If character is not a number
                else 
                {
                    // Check if the string of nums has a number
                    if (!tempString.empty())                                            //          +1
                    {
                        // Turn the string into an int
                        timeNum = stoi(tempString);                                     //              +1
                        // Add int to the vector of ints
                        timeNums.push_back(timeNum);                                    //              +1
                        
                        if (debugging)
                        {
                            cout << tab << tab << tab << tab << "* " << timeNum << endl;
                        }

                        // Clear String
                        tempString = "";                                                //              +1
                    }
                }                                                                       // )
            }                                                                           // +5n
            if (debugging)
            {
                cout << endl;
            }
            /* Creating the Time Frames
                * Iterate through the numbers to create the timeframes
                *     Timeframes require 4 ints, so take the size divided by 4
                * */
            if (debugging)
            {
                cout << tab << tab << tab << "Creating Timeframes . . ." << endl;
            }  
            for (int i = 0; i < (timeNums.size()/4); i++) {                             // n * (
                // Create the Timeframe
                tempTimeFrame = new TimeFrame(timeNums[i*4], timeNums[i*4 + 1], timeNums[i*4 + 2], timeNums[i*4 + 3]);
                                                                                        //      (1) -> +28
                
                // Check if valid Time Frame
                if (tempTimeFrame->isValid())                                           //      (1) -> +3
                {
                    // Add TimeFrame to Vector
                    timeVector.push_back(tempTimeFrame);                                //          +1
                }                                                                       // )
            }                                                                           // +32n
            /* Assign TimeUnavailable to new Vector */
            this->time_unavailable_ = new vector<TimeFrame*> (timeVector);              //      +1
            if (debugging)
            {
                cout << tab << tab << tab << "Updating Current Unavailable Times . . ." << endl << endl;
                cout << tab << tab << tab << "Inputted Times Unavailable" << endl << endl;
            }
        }
        void Schedule::stringToWorkingHours (string times)                              // Total: 5n + 34
        {
            /* ✧ ✦ ✧─────────────────✧ ✦ ✧ *
             *          Variables          *
             * ✧ ✦ ✧─────────────────✧ ✦ ✧ */

            string tempString;                                                          // +1
            vector<int> timeNums;                                                       // +1
            int timeNum;                                                                // +1

            //  ✧ ✦ ✧───────────────✧ ✦ ✧ 

            /* Isolating the Numbers */

            if (times.find('[') != std::string::npos)
            {
                // Iterate through string to find numbers
                for (int i = 0; i < times.length(); i++)                                    // n * (
                {
                    // Check if character is a number
                    if (isdigit(times.at(i)))                                               //      +1
                    {
                        // If number is found add to string for nums
                        tempString += times.at(i);                                          //          (1) (Not included: smaller of if)
                    }
                    // If character is not a number
                    else 
                    {
                        // Check if the string of nums has a number
                        if (!tempString.empty())                                            //          +1
                        {
                            // Turn the string into an int
                            timeNum = stoi(tempString);                                     //              +1
                            // Add int to the vector of ints
                            timeNums.push_back(timeNum);                                    //              +1
                            // Clear String
                            tempString = "";                                                //              +1
                        }
                    }                                                                       // )
                }                                                                           // +5n

                /* Creating the TimeFrames */

                if (timeNums.size() > 3)                                                    // +1
                {
                                                                                            //      (1) -> +28
                    this->working_hours_ = new TimeFrame (timeNums[0], timeNums[1], timeNums[2], timeNums[3]);
                    
                    if (!this->working_hours_->isValid())                                   //      +1
                    {
                        if (debugging)
                        {
                            cout    << tab << tab << tab << "Current working hours not valid, creating default working hours (00:00 - 23:59)" << endl;
                        }
                        this->working_hours_ = new TimeFrame ();                            //      +1
                    }
                }
                else
                {
                    this->working_hours_ = new TimeFrame ();                                //      (1) (Not included: smaller of if)
                }
            }
            else
            {
                this->working_hours_ = new TimeFrame ();                                //      (1) (Not included: smaller of if)
            }
            if (debugging)
            {
                cout << tab << tab << tab << "Updating Current Working Hours . . ." << endl << endl;
                cout << tab << tab << tab << "Inputted Working Hours" << endl << endl;
            }
        }


