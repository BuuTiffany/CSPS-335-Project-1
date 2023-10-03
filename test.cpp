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
 *      test.cpp
 *     
 *      Run program with Terminal UI
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

    /* ✧ ✦ ✧────────────────────────────✧ ✦ ✧ *
    *          Function Definitions          *
    * ✧ ✦ ✧────────────────────────────✧ ✦ ✧ */

        void menuLoop();

        void runProgram(string inputTxt, string outputTxt, string testOrRun);
        void credits();
        void waitForInput();

        string getLine();

        string centerText(string text);

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

// ──────────────────────────────────── ･ ｡ﾟ☆: *.☽ .* :☆ﾟ. ────────────────────────────────────

    /* ✧ ✦ ✧────────────✧ ✦ ✧ *
     *          Main          *
     * ✧ ✦ ✧────────────✧ ✦ ✧ */

int main() {
    
    credits();
            
    menuLoop();

    return 0;
}

/* ✧ ✦ ✧─────────────────✧ ✦ ✧ *
 *          Functions          *
 * ✧ ✦ ✧─────────────────✧ ✦ ✧ */
 
void menuLoop() 
{
    while (true)
    {
        /* ✧ ✦ ✧────────────✧ ✦ ✧ *
         *          Menu          *
         * ✧ ✦ ✧────────────✧ ✦ ✧ */

        cout
			<< endl << endl << endl
            << centerText("-----------------------------------------") << endl << endl
			<< centerText("*** Main Menu ***") << endl << endl
			<< centerText("-----------------------------------------") << endl << endl
			<< "1. Run Program" << endl
            << "    - Will read \"input.txt\" and print outputs to \"output.txt\"" << endl
            << "    - Will output information to the terminal" << endl 
            << endl
            << "2. Test Program" << endl
            << "    - Will read \"test.txt\" and print process in terminal" << endl 
            << endl
			<< "3. Credits" << endl 
			<< endl
			<< "Q. Quit" << endl
			<< endl
            << centerText("-----------------------------------------") << endl << endl
			<< "Enter your selection ==> "
			;
		
		//
		string choice = getLine();

        if (choice == "1")
        {
            // 1. Run Program
            runProgram("input.txt","output.txt","Run");
        }
        else if (choice == "2")
        {
            // 2. Test Program
            runProgram("test.txt","testoutput.txt","Test");
        }
        else if (choice == "3")
        {
            // "3. Create Your Own Schedule
            credits();
        }
        else if (choice == "q" || choice == "Q")
        {
            // Q. Quit
            break;
        }
        else
        {
            cout << "Invalid choice: " << choice << endl;
        }
    }

    cout    << endl << divider << endl << endl
            << centerText("Exiting Program . . .") << endl << endl
            << centerText("Good Bye!") << endl << endl
            << divider << endl << endl;
}

/* ✧ ✦ ✧───────────────────✧ ✦ ✧ *
 *          Run Program          *
 * ✧ ✦ ✧───────────────────✧ ✦ ✧ */
/**
 * 
 * */
void runProgram(string inputTxt, string outputTxt, string testOrRun)
{
    cout    << "----------------------------------------------------------------------------------------------------" << endl << endl
            << centerText(testOrRun +" Program") << endl << endl
            << "----------------------------------------------------------------------------------------------------" << endl << endl;
    
    /* ✧ ✦ ✧─────────────────✧ ✦ ✧ *
     *          Variables          *
     * ✧ ✦ ✧─────────────────✧ ✦ ✧ */

        vector<vector<string*>*> groups;
        vector<string*> groupSchedules;

    /* Open file "test.txt"
     * File will have 3 sets of 5 strings to make our groups
     * */
    ifstream readInput(inputTxt);
    string getString;
    cout    << "Opening \"" << inputTxt << "\"" << endl << endl;
    cout    << "Press \"Enter\" to create the groups and continue the program" << endl << endl;
    waitForInput();
    cout    << "Creating Groups . . ." << endl << endl;
    /* Go through test, read file line by line
     * While loop together with the getline() function to read the file line by line
     * */
    waitForInput();
    cout    << "Group " << groups.size()+1 << endl;
    // Check if the string is not empty
    while (getline (readInput, getString))                                          // n * (
    {
        if (!(getString.empty() || getString == "\r" || getString == "\n") )          //      +1
        {
            // Add string to vectors
            groupSchedules.push_back(new string(getString));                        //          (1) (Not included: smaller of if)
        }
        else if (groupSchedules.size() != 0)
        {
            for (string* s : groupSchedules)
            {
                cout    << " * " << *s << endl;
            }
            cout    << endl;
            groups.push_back(new vector<string*>(groupSchedules));                  //          +1
            groupSchedules.clear();                                                 //          +1
            waitForInput();
            cout    << "Group " << groups.size()+1 << endl << endl;
        }                                                                          // )
    } 
    for (string* s : groupSchedules)
    {
        cout    << " * " << *s << endl;
    }
    groups.push_back(new vector<string*>(groupSchedules));

    cout    << endl << endl;

    // Close file to save memory
    readInput.close();

    cout    << "Groups Created" << endl << endl;
    cout    << "Press \"Enter\" when you are ready to move on to schedule creation" << endl << endl;
    waitForInput();
    cout    << "Closing \"" << inputTxt << "\"" << endl << endl;

    cout    << endl << "----------------------------------------------------------------------------------------------------" << endl << endl;

    // cout    << "Printing groups" << endl << endl;
    // cout    << "Press \"Enter\" when you are ready for the part" << endl << endl;
    // waitForInput();
   
    // for (int i = 0; i < groups.size(); i++)
    // {
    //     cout << " - Group " << i+1 << " -" << endl << endl;
    //     cout << "    Inputs:" << endl;
    //     for (string* string : *groups[i]) 
    //     {
    //         cout << tab << tab << "* " << *string << endl;
    //     }
    //     waitForInput();
    // }

    // cout    << endl << "GroupsPrinted" << endl << endl;
    // cout    << "Press \"Enter\" when you are ready for the part" << endl << endl;
    // waitForInput();

    // cout    << endl << "----------------------------------------------------------------------------------------------------" << endl << endl;

    cout    << "Creating Schedules" << endl << endl;
    cout    << "Press \"Enter\" when you are ready to create the schedules and continue the program" << endl << endl;
    waitForInput();
    cout    << "Creating \"" << outputTxt << "\"" << endl << endl;

    vector<MatchingSchedule*> matchingSchedules;
    MatchingSchedule* tempSchedule;
    ofstream writeOutput (outputTxt);

    waitForInput();

    for (int i = 0; i < groups.size(); i++)
    {
        tempSchedule = new MatchingSchedule(*groups[i]);

        cout << endl;

        cout << " - Group " << i+1 << " -" << endl << endl;
        cout << "    Inputs:" << endl;
        for (string* string : *groups[i]) 
        {
            cout << tab << tab << "* " << *string << endl;
        }
        cout << endl;

        tempSchedule->printTestTab();

        cout    << "Number of schedules made: " << matchingSchedules.size() << endl
                << tab << "Adding schedules to vector" << endl;   

        matchingSchedules.push_back(tempSchedule);   

        cout    << "Number of schedules made: " << matchingSchedules.size() << endl;   

        writeOutput << tempSchedule->expectedOutput();

        waitForInput();

        if (i != groups.size()-1)
        {
            writeOutput  << endl;
            cout    << endl << "-----------------------------------------" << endl << endl; 
        }

    }

    writeOutput.close();

    cout    << "Schedules Created" << endl << endl;

    cout    << endl << "----------------------------------------------------------------------------------------------------" << endl << endl;

    cout    << "Reading \"" << outputTxt << "\"" << endl << endl;
    cout    << "Press \"Enter\" when you are ready to print \'output.txt\'";
    waitForInput();

    cout    << "Reading \"" << outputTxt << "\"" << endl << endl;
    
    ifstream readOutput (outputTxt);

    waitForInput();
    while (getline (readOutput, getString)) 
    {
        cout    << getString;
        waitForInput();
    }

    readOutput.close();

    cout    << endl << "Closing \"" << outputTxt << "\"" << endl << endl;

    cout    << "End Program" << endl << endl;

    cout    << "Press \"Enter\" to return to the menu" << endl << endl;

    waitForInput();

    cout    << "----------------------------------------------------------------------------------------------------" << endl << endl
            << "                                            "
            << "Good Bye!" << endl << endl
            << "----------------------------------------------------------------------------------------------------" << endl << endl;
}

void credits()
{
    cout    << divider << endl << endl
            << centerText("Testing Matching Schedules Algorithm") << endl  << endl
            << centerText("-----------------------------------------") << endl << endl
            << centerText("Project 1: Implementing Algorithms - Matching Group Schedules") << endl
            << centerText("CPSC 335-02: Algorithm Engineering") << endl
            << centerText("Professor Ornella Irene Dsouza") << endl
            << centerText("Fall 2023") << endl << endl
            << centerText("-----------------------------------------") << endl << endl
            << centerText("Coded by: Tiffany Buu") << endl << endl
            << divider << endl << endl;
}

void waitForInput()
{
    while(true)
    {
        //cout    << "Press enter key to continue..." << endl;
        cin.get();
        cin.clear();
        break;
    }
}

string getLine()
{
	const size_t BUFFER_SIZE = 8192;
	char buffer[BUFFER_SIZE];
	
	cin.clear();
	cin.getline(buffer, BUFFER_SIZE);
	
	string s = buffer;
	
	return s;
}