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
 *      project1_starter.cpp
 *     
 *      The main program
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
        
        using std::cout;
        using std::cin;
        using std::endl;
        using std::vector;
        using std::string;
        using std::to_string;
        using std::ifstream;
        using std::ofstream;
        using std::getline;


// ──────────────────────────────────── ･ ｡ﾟ☆: *.☽ .* :☆ﾟ. ────────────────────────────────────

    /* ✧ ✦ ✧────────────✧ ✦ ✧ *
     *          Main          *
     * ✧ ✦ ✧────────────✧ ✦ ✧ */

int main() {                                                                        // Total: 121n^4 + 86n^3 + 172n^2 + 82n + 8
    
    /* ✧ ✦ ✧─────────────────✧ ✦ ✧ *
     *          Variables          *
     * ✧ ✦ ✧─────────────────✧ ✦ ✧ */

        vector<vector<string*>*> groups;                                            // +1
        vector<string*> groupSchedules;                                             // +1

        vector<MatchingSchedule*> matchingSchedules;                                // +1
        MatchingSchedule* tempSchedule;                                             // +1
        
        ofstream writeOutput ("output.txt");                                        // +1
        ifstream readInput ("input.txt");                                           // +1
        
        string getString;                                                           // +1
    

    /* Go through test, read file line by line
     * While loop together with the getline() function to read the file line by line
     * Separate the inputs into the groups
     * */
    while (getline (readInput, getString))                                          // n * (
    {
        // Check if the string is not empty
        if (!(getString.empty() || getString == "\r" || getString == "\n"))         //      +1
        {
            // Add string to vectors
            groupSchedules.push_back(new string(getString));                        //          (1) (Not included: smaller of if)
        }
        else if (groupSchedules.size() != 0)
        {
            groups.push_back(new vector<string*>(groupSchedules));                  //          +1
            groupSchedules.clear();                                                 //          +1
        }                                                                           // )
    }                                                                               // +3n
    // Close file to save memory
    readInput.close();                                                              // +1

    // Go through groups and make schedules
    for (int i = 0; i < groups.size(); i++)                                         // n * ()
    {
        tempSchedule = new MatchingSchedule(*groups[i]);                            //      (1) -> 121n^3 + 86n^2 + 168n + 73 (matchingSchedules.cpp 76)
        matchingSchedules.push_back(tempSchedule);                                  //      +1
        writeOutput << tempSchedule->expectedOutput();                              //      (1) -> 4n + 6 (matchingSchedules.cpp 235)

        if (i != groups.size()-1)                                                   //      +1
        {
            writeOutput  << endl;                                                   //          +1
        }
                                                                                    // )
    }                                                                               // +121n^4 + 86n^3 + 172n^2 + 82n

    writeOutput.close();                                                            // +1

    return 0;
}

