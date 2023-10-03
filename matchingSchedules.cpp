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
 *      matchingSchedules.cpp
 *     
 *      Defines the MatchingSchedule class's:
 *          * Constructors
 *          * Destructors
 *          * Operators
 *          * Methods
 *   ∘₊✧────────────────────────────────────────────────✧₊∘ */

    /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
    *          Include          *
    * ✧ ✦ ✧───────────────✧ ✦ ✧ */
        #include "matchingSchedules.hpp"

        #include <iostream>
        #include <fstream>
        #include <string>

    /* ✧ ✦ ✧─────────────✧ ✦ ✧ *
    *          Using          *
    * ✧ ✦ ✧─────────────✧ ✦ ✧ */
        using std::cout, std::endl;
        using std::vector;
        using std::string, std::to_string;

    /* ✧ ✦ ✧────────────────────✧ ✦ ✧ *
     *          Constructors          *
     * ✧ ✦ ✧────────────────────✧ ✦ ✧ */

        MatchingSchedule::MatchingSchedule () 
        {
            if (debugging)
            {
                cout    << "Creating MatchingSchedules Object . . ." << endl << endl;
            }
            this->schedules_ = new vector<Schedule*> ();
            this->meeting_duration_ = new int ();
            createPotentialMeetingTimes();
        }
        MatchingSchedule::MatchingSchedule (MatchingSchedule& other) 
        {
            if (debugging)
            {
                cout    << "Creating MatchingSchedules Object . . ." << endl << endl;
            }
            this->schedules_ = new vector<Schedule*> (other.getSchedules());
            this->meeting_duration_ = new int (other.getMeetingDuration());
            createPotentialMeetingTimes();
        } 
        MatchingSchedule::MatchingSchedule (vector<Schedule*> schedules, int meeting_duration)
        {
            if (debugging)
            {
                cout    << "Creating MatchingSchedules Object . . ." << endl << endl;
            }
            this->schedules_ = new vector<Schedule*> (schedules);
            this->meeting_duration_ = new int (meeting_duration);
            createPotentialMeetingTimes();
        }
        MatchingSchedule::MatchingSchedule (vector<string*> toMatch)                    // Total: 121n^3 + 86n^2 + 168n + 73
        {
            if (debugging)
            {
                cout    << "Creating MatchingSchedules Object . . ." << endl << endl;
            }
            if ((toMatch.back()->find('[') != std::string::npos) || ((toMatch.back()->find('[') != std::string::npos) && (toMatch.back()->find_first_of("0123456789") == std::string::npos)))   // +1
            {
                if (debugging)
                {
                    cout    << tab << "Invalid string: (" << toMatch.at(toMatch.size()-1) << ") seting time to 1 minute" << endl << endl;
                }
                this->meeting_duration_ = new int(1);                                                        // +1
            }
            else
            {
                this->meeting_duration_ = new int(stoi(*toMatch.back()));                                   //  (1)                                                       // (1)
            }
            createSchedules(toMatch);                                                   // (1) -> +42n^2 + 40n + 1 (matchingSchedules.cpp 270)
            createPotentialMeetingTimes();                                              // (1) -> +121n^3 + 44n^2 + 128n + 70 (matchingSchedules.cpp 284)
        }

    /* ✧ ✦ ✧──────────────────✧ ✦ ✧ *
     *          Destructor          *
     * ✧ ✦ ✧──────────────────✧ ✦ ✧ */

        MatchingSchedule::~MatchingSchedule()
        {
            for (auto pointer : *this->schedules_)
            {
                delete pointer;
            }
        }

    /* ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ *
     *          Assignments & Operators          *
     * ✧ ✦ ✧───────────────────────────────✧ ✦ ✧ */

        MatchingSchedule& MatchingSchedule::operator= (const MatchingSchedule& other)
        {
            MatchingSchedule* ptr = new MatchingSchedule();
            // Sanity Check
            if (*this != *ptr) {
                *this->schedules_ = ptr->getSchedules();
                *this->meeting_duration_ = ptr->getMeetingDuration();
            }
            delete ptr;
            return *this;
        } 
        bool MatchingSchedule::operator== (const MatchingSchedule& other) const
        {
            MatchingSchedule* ptr = new MatchingSchedule();
            if (*this->schedules_ != ptr->getSchedules() ||
                *this->meeting_duration_ != ptr->getMeetingDuration())
            {
                delete ptr;
                return false;
            }
            delete ptr;
            return true;
        }
        bool MatchingSchedule::operator!= (const MatchingSchedule& other) const
        {
            MatchingSchedule* ptr = new MatchingSchedule();
            if (*this->schedules_ == ptr->getSchedules() ||
                *this->meeting_duration_ == ptr->getMeetingDuration())
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
        vector<Schedule*> MatchingSchedule::getSchedules () const
        {
            return *this->schedules_;
        }
        int MatchingSchedule::getMeetingDuration () const
        {
            return *this->meeting_duration_;
        }
        vector<TimeFrame*> MatchingSchedule::getPotentialMeetingTimes() const
        {

            if (this->potential_meeting_times_->empty())
            {
                cout << "No potential meeting times :c" << endl;
            }

            return *this->potential_meeting_times_;
        }

    // Setters    
        void MatchingSchedule::setSchedules (vector<Schedule*> schedules) 
        {
            this->schedules_ = new vector<Schedule*>(schedules);
            createPotentialMeetingTimes();
            return;
        }
        void MatchingSchedule::setMeetingDuration (int meeting_duration) 
        {
            this->meeting_duration_ = new int(meeting_duration);
            createPotentialMeetingTimes();
            return;
        }

    /* ✧ ✦ ✧───────────────✧ ✦ ✧ *
     *          Methods          *
     * ✧ ✦ ✧───────────────s✧ ✦ ✧ */

        void MatchingSchedule::printTest() {
            int count = 1;
            cout    << "Matching Group Schedules: " << endl;

            for (auto person : *this->schedules_) {
                cout    << tab << "Group Member " << count << ":" << endl;
                person->printExpectedOutputTab();
                count++;
            }

            cout    << tab << "Meeting Duration: " << *this->meeting_duration_ << endl << endl;

            cout    << tab << "Potential Meeting Times: " << endl;

            if (!(this->potential_meeting_times_->empty()))
            {
                for (auto times : *this->potential_meeting_times_) 
                {
                    cout    << tab << tab << "* " << times->outputTimeFrameString() << endl;
                }
            }
            else
            {
                cout    << tab << tab << "* No potential meeting times" << endl;
            }

            cout << endl;
        }
        void MatchingSchedule::printTestTab() {
            int count = 1;
            for (auto person : *this->schedules_) {
                cout    << "    Group Member " << count << ":" << endl ;
                person->printExpectedOutputTab();
                count++;
            }

            cout    << "    Meeting Duration: " << *this->meeting_duration_ << endl << endl;

            cout    << "    Potential Meeting Times: " << endl;

            if (!(this->potential_meeting_times_->empty()))
            {
                for (auto times : *this->potential_meeting_times_) 
                {
                    cout    << "        * " << times->outputTimeFrameString() << endl;
                }
            }
            else
            {
                cout    << "        * No potential meeting times" << endl;
            }

            cout << endl;
        }
        string MatchingSchedule::expectedOutput()                       // Total: 4n + 6
        {
            string result = "[";                                        // +1

                                                                        // +1 +2 (timeFrame.cpp 455)
            if (!this->potential_meeting_times_->empty())                // +1
            {
                result = result + this->potential_meeting_times_->at(0)->outputTimeFrameString();
                                                                        //      n * (
                for (size_t i = 1; i < this->potential_meeting_times_->size(); i++) {
                    result = result + ",";                              //      +1 +1 +2 (timeFrame.cpp 455))
                    result = result + this->potential_meeting_times_->at(i)->outputTimeFrameString();
                }                                                       //  )
            }                                                           // + 4n

            result = result + "]";                                      // +1
            return result;                                              // +1
        }
        void MatchingSchedule::printExpectedOutput() {
            string result = expectedOutput();
            cout    << result << endl;
        }
        void MatchingSchedule::printExpectedOutputFull() {
            string result;
            for (auto schedule : *this->schedules_)
            {
                result = result + schedule->getTimeUnavailableString() + "\n";
                result = result + schedule->getWorkingHoursString() + "\n";
            }
            result = result + to_string(getMeetingDuration()) + "\n\n";
            result = result + expectedOutput();
            cout    << result << endl;
        }

    /* ✧ ✦ ✧───────────────────────✧ ✦ ✧ *
     *          Private Methods          *
     * ✧ ✦ ✧───────────────────────✧ ✦ ✧ */

        void MatchingSchedule::createSchedules (vector<string*> toMatch)                // Total: 42n^2 + 40n + 1
        {
            this->schedules_ = new vector<Schedule*>();                                 // +1

            size_t num = (toMatch.size()/2);

            for (size_t i = 0; i < num; i++)                                 // n * (
            {
                this->schedules_->push_back(new Schedule(*toMatch[i*2], *toMatch[i*2 +1]));  //      (1) -> +42n +40 (schedule.cpp 61)
            }                                                                           // )
        }                                                                               // + 42n^2 + 40n
        void MatchingSchedule::createPotentialMeetingTimes()                            // Total: 121n^3 + 44n^2 + 128n + 70
        {
            if (debugging)
            {
                cout    << tab << "Finding Potential Meeting Times" << endl;
            }

            // Check to make sure there is a meeting time duration
            if (*this->meeting_duration_ <= 0)                                          // +1
            {
                if (debugging)
                {
                    cout    << tab << tab << "No meeting duration set, no potential meeting times available" << endl;
                }
                return;                                                                 //      +1
            }

            calculateMatchingWorkingHours();                                            // (1) -> +42n^2 +92n +31 (matchingSchedules.cpp 322)

            if (debugging)
            {
                cout    << endl << "----------------------------------------------------------------------------------------------------------" << endl << endl;
            }

            calculatePotentialWorkingHours();                                           // (1) -> +121n^3 +2n^2 +n +37 (matchingSchedules.cpp 453)

            if (debugging)
            {
                cout    << endl << "----------------------------------------------------------------------------------------------------------" << endl << endl;
            }

            removeTimesUnderDuration();                                                 // (1) -> +35n +2 (matchingSchedules.cpp 781)

            if (debugging)
            {
                cout    << endl;
            }
        }
        void MatchingSchedule::calculateMatchingWorkingHours()                          // Total: 42n^2 + 92n + 31
        {
            if (debugging)
            {
                cout    << tab << "----------------------------------------------------" << endl 
                        << tab << "         Calculating Matching Working Hours         " << endl 
                        << tab << "----------------------------------------------------" << endl << endl;
            }
            
            /* --------------------------- *
                *          Variables          *
                * --------------------------- */
            matching_working_hours_ = new TimeFrame();                                  // +1
            TimeFrame* temp_working_hours;                                              // +1
            int count = 1;                                                              // +1

            // Create Matching Working Hours TimeFrame
            this->matching_working_hours_ = new TimeFrame();                            // (1) -> +28 (timeFrame.cpp 61)

            // Calculating combined working hours
            for (auto schedule : *this->schedules_)                                     // n * (
            {                                                                           //      (1) -> +42n + 40 (schedule.cpp 61)
                // Get each person n's working hours
                temp_working_hours = new TimeFrame(schedule->getWorkingHours());        //      (1) -> +28 (timeFrame.cpp 61)
                if (debugging)
                {
                    cout    << tab << "Group Member " << count << "'s Schedule:" << endl;
                    schedule->printExpectedOutputTab();
                    cout    << tab << tab << "Current Working Hours: " << this->matching_working_hours_->outputTimeFrameString() << endl;
                    cout    << tab << tab << "Group Member " << count << "'s Working Hours: " << temp_working_hours->outputTimeFrameString() << endl << endl;
                }
                /* -------------------------------- *
                 *          Starting Times          *
                 * -------------------------------- *
                 * Compare the starting times
                 * If the current start time is before the person n's earliest start time:
                 *      - Change current start time to be the person n's earliest start time
                 * */

                // Check if starting hour is before person n's starting hour :)
                                                                                        //      +1
                if (this->matching_working_hours_->getStartTimeHour() < temp_working_hours->getStartTimeHour())
                {
                    if (debugging) 
                    {
                        cout    << "Current start time (" << this->matching_working_hours_->startTimeString() << ") is earlier than Group Member " << count << "'s earliest start time (" << temp_working_hours->startTimeString() << ")" << endl << "    Setting new start time . . ." << endl;
                    }
                    // If yes, set time the start time to the new later time            //          +1 +3 +1
                    this->matching_working_hours_->setStartTimeHour(temp_working_hours->getStartTimeHour());
                                                                                        //          +1 +3 +1
                    this->matching_working_hours_->setStartTimeMinute(temp_working_hours->getStartTimeMinute());
                    if (debugging) 
                    {
                        cout    << "New Current Start Time: " << this->matching_working_hours_->startTimeString() << endl;
                    }
                }
                // Check if starting hours are the same
                                                                                        //      +1
                else if (this->matching_working_hours_->getStartTimeHour() == temp_working_hours->getStartTimeHour())
                {
                    // Check if starting minutes are before person n's starting minutes //          (1)
                    if (this->matching_working_hours_->getStartTimeMinute() < temp_working_hours->getStartTimeMinute())
                    {
                        if (debugging) 
                        {
                            cout    << "Current start time (" << this->matching_working_hours_->startTimeString() << ") is earlier than Group Member " << count << "'s earliest start time (" << temp_working_hours->startTimeString() << ")" << endl << "    Setting new start time . . ." << endl;
                        }
                        // If yes, change the minutes to match                          //              (1 +3 +1)
                        this->matching_working_hours_->setStartTimeMinute(temp_working_hours->getStartTimeMinute());
                        if (debugging) 
                        {
                            cout    << "New Current Start Time: " << this->matching_working_hours_->startTimeString() << endl;
                        }
                    }
                }

                /* ------------------------------ *
                 *          Ending Times          *
                 * ------------------------------ *
                 * Compare the endinging times
                 * If the current end time is after the person n's latest end time:
                 *      - Change current end time to be the person n's latest end time
                 * */

                // Check if ending hour is after person n's ending hour :)              // +1
                if (this->matching_working_hours_->getEndTimeHour() > temp_working_hours->getEndTimeHour())
                {
                    if (debugging) {
                        cout    << "Current end time (" << this->matching_working_hours_->endTimeString() << ") is later than Group Member " << count << "'s latest end time (" << temp_working_hours->endTimeString() << ")" << endl << "    Setting new end time . . ." << endl;
                    }
                    // If yes, set time the end time to the new earlier time            //      +1 +3 +1
                    this->matching_working_hours_->setEndTimeHour(temp_working_hours->getEndTimeHour());
                                                                                        //      +1 +3 +1
                    this->matching_working_hours_->setEndTimeMinute(temp_working_hours->getEndTimeMinute());

                    if (debugging) {
                        cout    << "New Current End Time: " << this->matching_working_hours_->endTimeString() << endl;
                    }
                }
                // Check if ending hours are the same                                   // +1
                else if (this->matching_working_hours_->getEndTimeHour() == temp_working_hours->getEndTimeHour())
                {
                    // Check if endinging minutes are after person n's starting minutes //      (1)
                    if (this->matching_working_hours_->getEndTimeMinute() > temp_working_hours->getEndTimeMinute())
                    {
                        if (debugging) {
                            cout    << "Current end time (" << this->matching_working_hours_->endTimeString() << ") is later than Group Member " << count << "'s latest end time (" << temp_working_hours->endTimeString() << ")"  << endl << "    Setting new end time . . ." << endl;
                        }
                        // If yes, change the minutes to match                          //          (+1 +3 +1)
                        this->matching_working_hours_->setEndTimeMinute(temp_working_hours->getEndTimeMinute());

                        if (debugging) {
                            cout    << "New Current End Time: " << this->matching_working_hours_->endTimeString() << endl;
                        }
                    }
                }

                if (debugging) {
                    cout    << endl;
                }

                count++;                                                                // +1
            }                                                                           // )
                                                                                        // +42n^2 + 92n

            if (debugging)
            {
                cout    << endl << "Matching working hours: " << this->matching_working_hours_->outputTimeFrameString() << endl << endl;
            }

        }
        void MatchingSchedule::calculatePotentialWorkingHours()                         // Total: 121n^3 + 2n^2 + n + 37
        {
            if (debugging)
            {
                cout    << tab << "-----------------------------------------------------" << endl 
                        << tab << "         Calculating Potential Meeting Times         " << endl 
                        << tab << "-----------------------------------------------------" << endl << endl;
            }

            /* --------------------------- *
             *          Variables          *
             * --------------------------- */
            int count = 1;                                                              // +1

            bool startAfterPStart, startAfterPEnd;                                      // +1
            bool endAfterPStart, endAfterPEnd;                                          // +1

            TimeFrame tempTimeFrame1;                                                   // +1
            TimeFrame tempTimeFrame2;                                                   // +1
            TimeFrame* potentialTimes;                                                  // +1

            vector<TimeFrame*>* groupMemberTimeFrame;                                   // +1

            vector<TimeFrame*>::iterator meetingsIt;                                    // +1

            // Create Potential Times Vector:
            this->potential_meeting_times_ = new vector<TimeFrame*> ();                 // (1) -> +28 (timeFrame.cpp 61)
            this->potential_meeting_times_->push_back(this->matching_working_hours_);   // +1

            if (debugging)
            {
                cout    << tab << "Current Potential Meeting Times" << endl;
                for (TimeFrame* times : *this->potential_meeting_times_)
                {
                    cout    << tab << tab << "* " << times->outputTimeFrameString() << endl;
                }
            }

            /**------------------------------------------ *
             *          Group Members' Schedules          *
             * ------------------------------------------ */
            /* Iterate through each group member's schedule
                * Grab each members unavailible times and compare to potential meeting times
                * Correct as needed
                * */
            for (Schedule* groupMemberSchedule : *this->schedules_)                     // n * (
            {
                // Grab Group Member's Unavailable Times                                //      +n (n for every element in vector)
                groupMemberTimeFrame = new vector<TimeFrame*>( groupMemberSchedule->getTimeUnavailable() );
                if (debugging)
                {
                    cout    << "Group Member " << count << endl;
                    groupMemberSchedule->printTimeUnavailableTab();
                }

                // Iterate through Unavailable Time Frames                              //      n * (
                for (TimeFrame* groupMemberUnavailableTimeFrame : *groupMemberTimeFrame)
                {
                    // Iterate through the potential meeting times
                    meetingsIt = this->potential_meeting_times_->begin();               //          +1
                    for (int i = 0; i < this->potential_meeting_times_->size(); i++)    //          n * (
                    {
                        // Get meeting time
                        potentialTimes = new TimeFrame(*(*meetingsIt));                 //              (1) -> +28 (timeFrame.cpp 61)
                        // If the unavailable time frame starts between the current potential meeting time

                        if (debugging) {
                            cout    << tab << "Comparing Group Member Unavailable Time Frame to Potential Time Frame" << endl
                                    << tab << tab << "* Group Member Unavailable Time Frame: " << groupMemberUnavailableTimeFrame->outputTimeFrameString() << endl
                                    << tab << tab << "* Potential Meeting Time Frame: " << potentialTimes->outputTimeFrameString() << endl << endl;
                        }
                        /* ---------------------------------------- *
                         *          Checking for Conflicts          *
                         * ---------------------------------------- */
                        /* Check if the current unavailible time frame conflicts with the current time frame
                            * This would happen under 4 conditions:
                            *      1. Start time of unavailable time frame falls within the potential meeting time frame
                            *      2. End Time of unavailable time frame falls within the potential meeting time frame
                            *      3. Both start and end time of unavailable time frame falls within  the meeting time frame
                            *      4. Potential time frame is inside end time
                            * If no conflicts continue
                            * */

                        // Reset Checks
                        startAfterPStart = false;
                        startAfterPEnd = false;
                        endAfterPStart = false;
                        endAfterPEnd = false;
                        
                        // Check group member's time frame, check if start time is before or after potential time frame start time
                                                                                        //              +1
                        if ((potentialTimes->getStartTimeHour() < groupMemberUnavailableTimeFrame->getStartTimeHour()) || 
                            (potentialTimes->getStartTimeHour() == groupMemberUnavailableTimeFrame->getStartTimeHour() && potentialTimes->getStartTimeMinute() <= groupMemberUnavailableTimeFrame->getStartTimeMinute()))
                        {
                            // True     = After Potential Start
                            // False    = Before Potential Start
                            startAfterPStart = true;                                    //                  +1
                        }

                        // Check group member's time frame, check if start time is before or after potential time frame end time
                                                                                        //              +1
                        if ((potentialTimes->getEndTimeHour() < groupMemberUnavailableTimeFrame->getStartTimeHour()) || 
                            (potentialTimes->getEndTimeHour() == groupMemberUnavailableTimeFrame->getStartTimeHour() && potentialTimes->getStartTimeMinute() <= groupMemberUnavailableTimeFrame->getStartTimeMinute()))
                        {
                            // True     = After Potential End
                            // False    = Before Potential End
                            startAfterPEnd = true;                                      //                  +1
                        }

                        // Check group member's time frame, check if end time is before or after potential time frame start time
                                                                                        //              +1
                        if ((potentialTimes->getStartTimeHour() < groupMemberUnavailableTimeFrame->getEndTimeHour()) || 
                            (potentialTimes->getStartTimeHour() == groupMemberUnavailableTimeFrame->getEndTimeHour() && potentialTimes->getStartTimeMinute() <= groupMemberUnavailableTimeFrame->getEndTimeMinute()))
                        {
                            // True     = After Potential Start
                            // False    = Before Potential Start
                            endAfterPStart = true;                                      //                  +1
                        }

                        // Check group member's time frame, check if end time is before or after potential time frame end time
                                                                                        //              +1
                        if ((potentialTimes->getEndTimeHour() < groupMemberUnavailableTimeFrame->getEndTimeHour()) || 
                            (potentialTimes->getEndTimeHour() == groupMemberUnavailableTimeFrame->getEndTimeHour() && potentialTimes->getEndTimeMinute() <= groupMemberUnavailableTimeFrame->getEndTimeMinute()))
                        {
                            // True     = After Potential End
                            // False    = Before Potential End
                            endAfterPEnd = true;                                        //                  +1
                        }

                        // Creating New Potential Time Frames          
                                                                                        //              +1
                        if (startAfterPStart && !startAfterPEnd && endAfterPStart && endAfterPEnd)
                        {
                            /* 1. If the start time is within the time frame but the end time doesn't
                                *      (startAfterPStart && !startAfterPEnd && endAfterPStart && endAfterPEnd)
                                *      * Adjust the END time of the potential time frame
                                *          Start Time: Original Start Time
                                *          End Time: Unavailable Start Time
                                *      ! continue
                                *          End time can still conflict with other time frames
                                * */
                            if (debugging)
                            {
                                cout    << tab << tab << "Scheduling Conflict: Adjusting potential time frame end time" << endl 
                                        << tab << tab << ". . ." << endl;
                            }

                            // Create Time Frame                                        //                  ((4) -> +3)
                            tempTimeFrame1.setStartTimeHour(potentialTimes->getStartTimeHour());
                            tempTimeFrame1.setStartTimeMinute(potentialTimes->getStartTimeMinute());
                            tempTimeFrame1.setEndTimeHour(groupMemberUnavailableTimeFrame->getStartTimeHour());
                            tempTimeFrame1.setEndTimeMinute(groupMemberUnavailableTimeFrame->getStartTimeMinute());

                            *meetingsIt = new TimeFrame(tempTimeFrame1);                //                  ((1) -> +28)

                            meetingsIt++;                                               //                  (1)
                            if (debugging)
                            {
                                cout    << tab << tab << "Scheduling Conflict Resolved" << endl << endl;
                                cout    << "--------------------------------------" << endl << endl;

                                cout    << "Current Potential Meeting Times" << endl;
                                for (TimeFrame* times : *this->potential_meeting_times_)
                                {
                                    cout    << tab << tab << "* " << times->outputTimeFrameString() << endl;
                                }

                                cout    << "--------------------------------------" << endl << endl;
                            }
                        }                                                               //              +1
                        else if (!startAfterPStart && !startAfterPEnd && endAfterPStart && !endAfterPEnd)
                        {
                            /* 2. If the end time is within the time frame but the start time doesn't
                                *      (!startAfterPStart && !startAfterPEnd && endAfterPStart && !endAfterPEnd)
                                *      * Adjust the STARTING time of the potential time frame
                                *          Start Time: Unavailable End Time
                                *          End Time: Original End Time
                                *      ! break
                                *          No times after will include the time frame
                                * */
                            if (debugging)
                            {
                                cout    << tab << tab << "Scheduling Conflict: Adjusting potential time frame start time" << endl
                                        << tab << tab << ". . ." << endl;
                            }
                            // Create Time Frame                                        //                  ((4) -> +3)
                            tempTimeFrame2.setStartTimeHour(groupMemberUnavailableTimeFrame->getEndTimeHour());
                            tempTimeFrame2.setStartTimeMinute(groupMemberUnavailableTimeFrame->getEndTimeMinute());
                            tempTimeFrame2.setEndTimeHour(potentialTimes->getEndTimeHour());
                            tempTimeFrame2.setEndTimeMinute(potentialTimes->getEndTimeMinute());

                            *meetingsIt = new TimeFrame(tempTimeFrame2);                //                  ((1) -> +28)
                            if (debugging)
                            {
                                cout    << tab << tab << "Scheduling Conflict Resolved" << endl << endl;
                                cout    << "--------------------------------------" << endl << endl;

                                cout    << "Current Potential Meeting Times" << endl;
                                for (TimeFrame* times : *this->potential_meeting_times_)
                                {
                                    cout    << tab << tab << "* " << times->outputTimeFrameString() << endl;
                                }

                                cout    << "--------------------------------------" << endl << endl;
                            }
                            break;                                                      //                  (1)
                        }                                                               //              +1
                        else if (startAfterPStart && !startAfterPEnd && endAfterPStart && !endAfterPEnd)
                        {
                            /*  3. If the start time and end time is within the time frame
                                *      (startAfterPStart && !startAfterPEnd && endAfterPStart && !endAfterPEnd)
                                *      * We are creating 2 new time frames to replace the current one
                                *          1. Start Time: Original Start Time
                                *             End Time: Unavailable Start Time
                                *          2. Start Time: Unavailable End Time
                                *             End Time: Original End Time
                                *      ! break
                                *          No time after will include the time frame
                                * */
                            if (debugging)
                            {
                                cout    << tab << tab << "Scheduling Conflict: Creating two new time frames" << endl
                                        << tab << tab << ". . ." << endl;
                            }
                            
                            // Create 1st Time Frame                                    //                  (4) -> +3
                            tempTimeFrame1.setStartTimeHour(potentialTimes->getStartTimeHour());
                            tempTimeFrame1.setStartTimeMinute(potentialTimes->getStartTimeMinute());
                            tempTimeFrame1.setEndTimeHour(groupMemberUnavailableTimeFrame->getStartTimeHour());
                            tempTimeFrame1.setEndTimeMinute(groupMemberUnavailableTimeFrame->getStartTimeMinute());

                            // Create 2nd Time Frame                                    //                  (4) -> +3
                            tempTimeFrame2.setStartTimeHour(groupMemberUnavailableTimeFrame->getEndTimeHour());
                            tempTimeFrame2.setStartTimeMinute(groupMemberUnavailableTimeFrame->getEndTimeMinute());
                            tempTimeFrame2.setEndTimeHour(potentialTimes->getEndTimeHour());
                            tempTimeFrame2.setEndTimeMinute(potentialTimes->getEndTimeMinute());

                            /* ------------------------------------------- *
                             *          Replacing The Time Frames          *
                             * ------------------------------------------- */
                            /*  x = other time frames
                                *  0 = old potential meeting time      (potentialTimes)
                                *  1 = new time frame 1                (tempTimeFrame1)
                                *  2 = new time frame 2                (tempTimeFrame2)
                                *  i = index of (0)
                                * 
                                *  We want to replace the old timeframe (0) with the 2 new time frames (1,2)
                                * 
                                *  1. Replace (0) with (2)
                                *          [x, ..., x, 0, x, ..., x]
                                *           |
                                *           v
                                *          [x, ..., x, 2, x, ..., x]
                                *  
                                *  2. Insert (1) at i
                                *          [x, ..., x, 2, x, ..., x]
                                *           |          ^
                                *           v          1
                                *          [x, ..., x, 1, 2, x, ..., x]
                                * */

                            *meetingsIt = new TimeFrame(tempTimeFrame2);                //                  (1) -> +28 (timeFrame.cpp 61)
                                                                                        //                  (1) -> +28 (timeFrame.cpp 61)
                            this->potential_meeting_times_->insert(meetingsIt, new TimeFrame(tempTimeFrame1));
                            if (debugging)
                            {
                                cout    << tab << tab << "Scheduling Conflict Resolved" << endl << endl;
                                cout    << "--------------------------------------" << endl << endl;

                                cout    << tab << "Current Potential Meeting Times" << endl;
                                for (TimeFrame* times : *this->potential_meeting_times_)
                                {
                                    cout    << tab << tab << "* " << times->outputTimeFrameString() << endl;
                                }

                                cout    << "--------------------------------------" << endl << endl;
                            }
                            break;                                                      //                  +1
                        }                                                               //              +1
                        else if (startAfterPStart && startAfterPEnd && !endAfterPStart && !endAfterPEnd)
                        {
                            /* 4. If the time frame is between the start and end time
                                *      (startAfterPStart && startAfterPEnd && !endAfterPStart && !endAfterPEnd)
                                *      * We are removing the current potential time frame
                                *      ! continue
                                *          End time can still conflict with other time frames
                                * */
                            if (debugging)
                            {
                                cout    << tab << tab << "Scheduling Conflict: Erasing Time Frame" << endl
                                        << tab << tab << ". . ." << endl;
                            }

                            this->potential_meeting_times_->erase(meetingsIt);          //                  (1)
                            
                            if (debugging)
                            {
                                cout    << tab << tab << "Scheduling Conflict Resolved" << endl << endl;
                                cout    << "--------------------------------------" << endl << endl;

                                cout    << tab << "Current Potential Meeting Times" << endl;
                                for (TimeFrame* times : *this->potential_meeting_times_)
                                {
                                    cout    << tab << tab << "* " << times->outputTimeFrameString() << endl;
                                }

                                cout    << "--------------------------------------" << endl << endl;
                            }
                        }
                        else 
                        {
                            /* 5. No conflicts
                                *      ! continue
                                *          End time can still conflict with other time frames
                                * */
                            if (debugging)
                            {
                                cout    << tab << tab << "No Scheduling Conflicts" << endl << endl;
                            }

                            meetingsIt++;                                               //                  (1)
                        }                                                               //              )
                    }                                                                   //          +121n
                                                                                        //          )
                }                                                                       //      +121n^2 + n
                count ++;                                                               //      +1
            }                                                                           // +121n^3 +2n^2 +1n
        }
        void MatchingSchedule::removeTimesUnderDuration()                               // Total: 35n +2
        {
            if (debugging)
            {
                cout    << tab << "-------------------------------------------------------" << endl 
                        << tab << "         Removing Times Under Meeting Duration         " << endl 
                        << tab << "-------------------------------------------------------" << endl << endl;
            }

            int timeDuration;                                                           // +1
            TimeFrame* times;                                                           // +1
            
            // Iterate through potential times, remove any with duration under meeting duration
            if (debugging)
            {
                cout    << tab << "Meeting Duration: " << *this->meeting_duration_ << endl;
                cout    << tab << "Potential Meeting Times:" << endl;
            }
                                                                                        // n * (
            for (vector<TimeFrame*>::iterator timeIterator = this->potential_meeting_times_->begin(); timeIterator != this->potential_meeting_times_->end(); timeIterator++)
            {
                times = new TimeFrame(*(*timeIterator));                                //      (1) -> +28 (timeFrame.cpp 61)
                timeDuration = times->calculateDurationInMinutes();                     //      (1) -> +4 (timeFrame.cpp 418)

                if (debugging)
                {
                    cout    << tab << tab << "* " << times->outputTimeFrameString() << endl;
                    cout    << tab << tab << tab << "* Potential time frame duration (" << timeDuration << ")" << endl;
                }


                if (timeDuration < *this->meeting_duration_) {                          //      +1
                    if (debugging)
                    {
                        cout    << tab << tab << tab << "* Potential time frame duration is less than the meeting duration (" << *this->meeting_duration_ << ")" << endl;
                        cout    << tab << tab << tab << "* Removing time frame" << endl;
                    }

                    this->potential_meeting_times_->erase(timeIterator);                //          +1
                    timeIterator--;                                                     //          +1

                }                                                                       //      )
            }                                                                           // +35n
            if (debugging) 
            {
                cout    << endl << tab << "Finished Removing Times Under Meeting Duration" << endl;
            }
        }
