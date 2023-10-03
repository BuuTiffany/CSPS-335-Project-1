# Project 1: Implementing Algorithms
Fall 2023   CPSC 335.02 - Algorithm Engineering

---

# Abstract
Develop a pseudocode for an algorithm; analyze your pseudocode mathematically; implement the algorithm in Python or C++; test your implementation; and describe your results.

**The Problem:**  Matching Group Schedules

The group schedule matching takes two or more arrays as input. The arrays represent slots that are already booked and login/logout time of group members. It outputs an array containing intervals of time when all members are available for a meeting for a minimum duration expected.

The group schedule matching takes following inputs:
* **Busy_Schedule**: A list of list that represent the persons existing schedule (they can’t plan any other engagement during these hours)
* **Working_period**: Daily working periods of group members.  (login,logout)
* **Duration of the meeting**  

It outputs a list of list containing intervals of time when all members are available for a meeting for the minimum duration of the meeting required.

Assume there are two persons in your class project group. You want to schedule a meeting with another group member. The members decide to provide you with 
1. A schedule of their daily activities, containing times of planned engagements. They are not available during these periods.
2. The earliest and latest times at which they are available for meetings daily. Your schedule and availability are provided too. 

Write an algorithm that takes in your schedule, your daily availability (earliest time, latest time) and that of your group member (or members), and the duration of the meeting you want to schedule. Time is given and should be returned in military format.  

    *For example:* 9:30, 22:21. The given times (output) should be sorted in ascending order. 
    Inputs are also in sorted order.

An algorithm for solving this problem involves combing the two sub-arrays into an array containing of  a set unavailability, with consideration of the daily active periods. 

Sample input
person1_busy_Schedule =[ [’12:00’, ’13:00’],  [’16:00’, ’18:00’]]
person1_work_hours = [‘9:00’, ’19:00’]
person2_busy_Schedule = [[ ‘9:00’, ’10:30’],  [’12:20’, ’14:30’],  [’14:30’, ’15:00’], [’16:00’, ’17:00’ ]]
person2_work_hours = [‘9:00’, ’18: 30’]
duration_of_meeting =30

Sample output 
[[’10:30’, ’12:00’], [’15:00’, ’16:00’], [’18:00’, ’18:30’]]

---

# Implementation
Have following files
* Project1_starter.py or project1_starter.cpp
  * This should define functions for the  algorithm described above. 
  * You will need to develop and write the functions. Describe how to run your program in the ReadMe file
* Input.txt containing the sample input files. Use these sample files to run your program to see whether your algorithm implementations are working correctly. Have a new line character separating the sample test cases (10)
* Output.txt – load the sample test case result to output.txt

---

# To Do

1. Create a Readme file and include your name(s) and email address(es). The Readme file should also contain instructions on how to run your program.
2. Study the sample input and output above. Write your own complete and clear code for an algorithm to solve this problem.
3. Analyze your code for the algorithm mathematically and prove its efficiency class.
4. Implement your algorithm using either Python or C++.
5. Run your code using different data inputs 
6. Produce a brief written project report in PDF format. Your report should include the following:
   * Your names
   * CSUF email address(es)
   * An indication that the submission is for project 1.
   * A screenshot showing the output of your code for a minimum of 10 test cases defined by yourself.
   * Link to your github repo. Keep it private until due date. Make it public after due date (No code commits allowed post due date, any code change after due date will not be considered for grading)
   * A brief proof argument for the time complexity of your algorithm, including step-counts

---

# Mathematical Analysis
Analyze your algorithm mathematically. You should prove a specific big-O efficiency class for the algorithm. The analysis should be routine, similar to the ones we have done in class and in the textbook. The algorithm’s efficiency class will be one of
* O(n)
* O(n^2)
* O(n^3)
* O(n^4)

## Can we do better?  
What changes do you think can be made to your algorithm to increase its time complexity/efficiency?  
Will an increase in **n** change the complexity class?  
  * **n** is the number of persons in the group.

---

# Grading Rubric
The suggested grading rubric is below.  

* Algorithm design and implementation = 50 points, divided as follows:
  * Clear and complete code = 20 points
  * Complete and clear README.md file = 3 points
  * Successful compilation = 15 points
  * Produces accurate result = 12 points

* Analysis = 50 points, divided as follows
  * Mathematical analysis and proof, including step count =22
  * Report document presentation = 20 points
  * Screenshot = 5 points 
  * Comments on possible improvements = 3

Ensure your submissions are your own works. Your submissions will be checked for similarities using a software.

---

# Submitting your code
Submit your project as a zip folder with following format <Team_member_name1_member_2_member_3>.zip to the Project 1 link on Canvas. It allows for multiple submissions. 
Include following files in the zip folder:
* Readme
* Input.txt
* Project1_starter.py or project1_starter.cpp
* Output.txt

---

# Deadline
The project deadline is October 2,2023 11:59 pm  on Canvas.
Penalty for late submission is as stated in the syllabus. Projects submitted more than 48 hours after the deadline will not be accepted.