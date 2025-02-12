//=======================================================
// This program generates two data files for testing
//  the course scheduling project.
// Author: Dr. Rick Coleman
// Date: January, 2009
//======================================================

//******************************************************
// ONLY CONFLICT EDITION
//******************************************************


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Defines for course preferences
    // Faculty Preferences (20% of the faculty express a preference)
    //     1 = All classes Monday and Wednesday
    //     2 = All classes Tuesday and Thursday
    //     3 = All classes in the mornings
    //     4 = All classes in the afternoon
    //     5 = All classes in the evening

    // Course Preferences (10% of the classes must be in a set classroom)
    //     1 = Must be taught in a specific classroom
    //     2 = Must be taught at a specific time
#define ALL_MW_CLASSES    0x0001
#define ALL_TT_CLASSES    0x0002
#define MORNING_ONLY    0x0004
#define AFTERNOON_ONLY    0x0008
#define EVENING_ONLY    0x0010
#define CLASSROOM_SPEC  0x0020
#define TIME_SPEC       0x0040

#define PC_FAC_WITH_PREFS 30
#define PC_COURSE_WITH_PREFS 10

#define CLASSES_ARRAY_DIM1 30    // Classes for 30 faculty created
#define CLASSES_ARRAY_DIM2 4    // 2ND dimension of array

// Function prototypes
void insertSort(int list[][4]);

int main(void)
{
    fstream dept1File;
    fstream dept2File;
    bool OK = true;
    int courseNum;
    time_t tSec;
    char line[128];
    int randNum;

    // 2 departments
    char dept1Name[] = "Computer Science";
    char dept2Name[] = "Electrical and Computer Engineering";

    // 2 buildings
    char dept1Bld[] = "Technology Hall";
    char dept2Bld[] = "Engineering Building";

    // 2 Class prefixes
    char deptPrefix1[] = "CS";
    char deptPrefix2[] = "ECE";

    // Create 12 classrooms in each building
    int dept1RmNums[] = {131, 132, 133, 133, 241, 242, 243, 243, 341, 342, 343, 344};
    int dept2RmNums[] = {126, 126, 127, 128, 225, 226, 226, 228, 325, 326, 326, 328};

    // Class starting times
    string classStartTimes[] = {"8:00", "9:35", "11:10", "12:45", "2:20", "3:55", "5:30", "7:05"};
    string classEndTimes[] =   {"9:20", "10:55", "12:30", "2:05", "3:40", "5:15", "6:50", "8:25"};

    //Schedule for 15 faculty in each building
    string classDept1Fac[] = {"Dr. Able",
                              "Dr. Brovo",
                              "Dr. Charlie",
                              "Dr. Dog",
                              "Dr. Echo",
                              "Dr. Foxtrot",
                              "Dr. Golf",
                              "Dr. Hotel",
                              "Dr. India",
                              "Dr. Juliet",
                              "Dr. Kilo",
                              "Dr. Lima",
                              "Dr. Mike",
                              "Dr. November",
                              "Dr. Oscar"};
    string classDept2Fac[] = {"Dr. Alpha",
                              "Dr. Beta",
                              "Dr. Gamma",
                              "Dr. Delta",
                              "Dr. Epsilon",
                              "Dr. Zeta",
                              "Dr. Eta",
                              "Dr. Theta",
                              "Dr. Iota",
                              "Dr. Kappa",
                              "Dr. Lamda",
                              "Dr. Mu",
                              "Dr. Nu",
                              "Dr. Xi",
                              "Dr. Omicron"};

    // Course listings
    //   courseListX[i][0] = Course number
    //   courseListX[i][1] = Index of faculty teaching the course
    //   courseListX[i][2] = Flag a preference
    //   courseListX[i][3] = Index of classroom or time slot
    int courseList1[45][4];
    int courseList2[45][4];
    
    // 3 Classes for each faculty member
    //   classes[i][0] = Course 1 number
    //   classes[i][1] = Course 2 number
    //   classes[i][2] = Course 3 number
    //   classes[i][3] = Faculty preference
    int classes[CLASSES_ARRAY_DIM1][CLASSES_ARRAY_DIM2];

    // Faculty preference string
    char preference[32];

    // Init the random number generator
    time(&tSec);
    srand((unsigned int)tSec);

    // Init all classes to 0
    for(int i=0; i<CLASSES_ARRAY_DIM1; i++)
    {
        for(int j=0; j<CLASSES_ARRAY_DIM2; j++)
        {
            classes[i][j] = 0;
        }
    }

    // Init all courses to 0
    for(int i=0; i<45; i++)
    {
        for(int j=0; j<4; j++)
        {
            courseList1[i][j] = 0;
            courseList2[i][j] = 0;

        }
    }
    // Create unique class numbers for each faculty member
    //   For even numbered professors make classes 100, 200, 300
    //   level.  For odd numbered professors make classes 400,
    //   500, and 600 level.
    for(int fac=0; fac<30; fac++)
    {
        // Create 3 class numbers
        for(int cl=0; cl<3; cl++)
        {
            do
            {
                OK = true;
                // Generate a course number
                courseNum = (rand() % 100);
                if((fac % 2) == 0) // make classes 100, 200, and 300 level
                    courseNum += ((cl + 1) * 100);
                else // make classes 300, 400, 500
                    courseNum += (((cl + 1) * 100) + 200);
                // Make sure no one else has this one
                /*
                if(fac < 15) // Check dept 1
                {
                    for(int f=0; f<=fac; f++)
                    {
                        for(int c=0; c<3; c++)
                            if(classes[f][c] == courseNum)
                                OK = false;
                    }
                }
                else // Check dept 2
                {
                    for(int f=15; f<=fac; f++)
                    {
                        for(int c=0; c<3; c++)
                            if(classes[f][c] == courseNum)
                                OK = false;
                    }
                }
                */
                if(OK)
                {
                    // Add this course to the facult member's list
                    classes[fac][cl] = courseNum;

                    // Save it in the course list with the faculty index
                    if(fac < 15) // Department 1
                    {
                        // Save course number
                        courseList1[(fac*3)+cl][0] = courseNum;
                        // Save index of faculty teaching it
                        courseList1[(fac*3)+cl][1] = fac;
                    }
                    else // Department 2
                    {
                        // Save course number
                        courseList2[((fac%15)*3)+cl][0] = courseNum;
                        // Save index of faculty teaching it
                        courseList2[((fac%15)*3)+cl][1] = (fac%15);
                    }
                    // See if there is a preference for this class
                    randNum = rand() % 50;
                    if(randNum <= PC_COURSE_WITH_PREFS)
                    {
                        // Get a preference for the class
                        randNum = rand() % 2;
                        switch(randNum)
                        {
                            case 0 : // Classroom preference
                                // Select a classroom index
                                randNum = rand() % 12;
                                if(fac < 20) // Department 1
                                {
                                    courseList1[(fac*3)+cl][2] |= CLASSROOM_SPEC;
                                    courseList1[(fac*3)+cl][3] = randNum;
                                }
                                else // Department 2
                                {
                                    courseList2[((fac%15)*3)+cl][2] |= CLASSROOM_SPEC;
                                    courseList2[((fac%15)*3)+cl][3] = randNum;
                                }
                                break;
                            case 1 : // Time slot preference
                                // Select a time index
                                randNum = rand() % 8;
                                if(fac < 20) // Department 1
                                {
                                    courseList1[(fac*3)+cl][2] |= TIME_SPEC;
                                    courseList1[(fac*3)+cl][3] = randNum;
                                }
                                else // Department 2
                                {
                                    courseList2[((fac%15)*3)+cl][2] |= TIME_SPEC;
                                    courseList2[((fac%15)*3)+cl][3] = randNum;
                                }
                                break;
                        }
                    }
                }
            }
            while(!OK);
        } // End for 3 classes each
        // Calculate a faculty preference (20% have preferences)
        randNum = rand() % 100;
        if(randNum <= PC_FAC_WITH_PREFS)
        {
            // Get a preference for the faculty member
            randNum = rand() % 5;
            switch(randNum)
            {
                case 0 : classes[fac][3] |= ALL_MW_CLASSES; break;
                case 1 : classes[fac][3] |= ALL_TT_CLASSES; break;
                case 2 : classes[fac][3] |= MORNING_ONLY; break;
                case 3 : classes[fac][3] |= AFTERNOON_ONLY; break;
                case 4 : classes[fac][3] |= EVENING_ONLY; break;
            }
        }
    } // End for 30 faculty members

    // Sort the class lists using insertion sort
    insertSort(courseList1);
    insertSort(courseList2);

    //---------------------------------------------------------
    // Open the file and write out the data for department 1
    //---------------------------------------------------------
    dept1File.open("Dept1ClassData.csv", ios::out);
    if(!dept1File.is_open())
    {
        cout << "Failed to open department 1 class data output file.\n";
        cout << "Application terminating.\n";
        return 0;
    }
    // Print department name
    sprintf(line, "Department: %s\n", dept1Name);
    dept1File.write(line, (long)strlen(line));
    // Print department building
    sprintf(line, "Location: %s\n\n", dept1Bld);
    dept1File.write(line, (long)strlen(line));
    // List all the courses
    strcpy(line, "Courses Offered\n\n");
    dept1File.write(line, (long)strlen(line));

    // List all courses and preferences
    for(int c=0; c<45; c+=5)
    {
        sprintf(line, "\t%s %d, %s %d, %s %d, %s %d, %s %d\n",
            deptPrefix1, courseList1[c][0],
            deptPrefix1, courseList1[c+1][0],
            deptPrefix1, courseList1[c+2][0],
            deptPrefix1, courseList1[c+3][0],
            deptPrefix1, courseList1[c+4][0]);
        dept1File.write(line, (long)strlen(line));
    }
    
    dept1File.write("\n\n", 2L);

    // List all the classroom preferences
    strcpy(line, "Classroom Preferences:\n");
    dept1File.write(line, (long)strlen(line));
    for(int i=0; i<45; i++)
    {
        if((courseList1[i][2] &= CLASSROOM_SPEC) != 0)
        {
            sprintf(line, "\t%s %d must be taught in %s, room %d\n",
                deptPrefix1, courseList1[i][0],
                dept1Bld, dept1RmNums[courseList1[i][3]]);
            dept1File.write(line, (long)strlen(line));
        }
        else if((courseList1[i][2] &= TIME_SPEC) != 0)
        {
            sprintf(line, "\t%s %d must be in the %s - %s time slot.\n",
                deptPrefix1, courseList1[i][0],
                classStartTimes[courseList1[i][3]].c_str(),
                classEndTimes[courseList1[i][3]].c_str());
            dept1File.write(line, (long)strlen(line));
        }
    }
    dept1File.write("\n\n", 2L);

    // List all the faculty assignments
    strcpy(line, "Faculty Assignments:\n");
    dept1File.write(line, (long)strlen(line));

    for(int d=0; d<15; d++)
    {
        // Set the faculty preference
        if((classes[d][3] & ALL_MW_CLASSES) != 0)
            strcpy(preference, "All Mon-Wed classes");
        else if((classes[d][3] & ALL_TT_CLASSES) != 0)
            strcpy(preference, "All Tues-Thurs classes");
        else if((classes[d][3] & MORNING_ONLY) != 0)
            strcpy(preference, "Morning classes only");
        else if((classes[d][3] & AFTERNOON_ONLY) != 0)
            strcpy(preference, "Afternoon classes only");
        else if((classes[d][3] & EVENING_ONLY) != 0)
            strcpy(preference, "Evening classes only");
        else
            strcpy(preference, "None");

        sprintf(line, "%s, %s %d, %s %d, %s %d - Preference: %s\n",
                                        classDept1Fac[d].c_str(),
                                        deptPrefix1,
                                        classes[d][0],
                                        deptPrefix1,
                                        classes[d][1],
                                        deptPrefix1,
                                        classes[d][2],
                                        preference);
        dept1File.write(line, (long)strlen(line));
    }

    dept1File.close();

    // Open the file and write out the data for department 2
    dept2File.open("Dept2ClassData.csv", ios::out);
    if(!dept2File.is_open())
    {
        cout << "Failed to open department 2 class data output file.\n";
        cout << "Application terminating.\n";
        return 0;
    }
    // Print department name
    sprintf(line, "Department: %s\n", dept2Name);
    dept2File.write(line, (long)strlen(line));
    // Print department building
    sprintf(line, "Location: %s\n\n", dept2Bld);
    dept2File.write(line, (long)strlen(line));
    // List all the courses
    strcpy(line, "Courses Offered\n\n");
    dept2File.write(line, (long)strlen(line));
    // List all courses
    for(int c=0; c<45; c+=5)
    {
        sprintf(line, "\t%s %d, %s %d, %s %d, %s %d, %s %d\n",
            deptPrefix2, courseList2[c][0],
            deptPrefix2, courseList2[c+1][0],
            deptPrefix2, courseList2[c+2][0],
            deptPrefix2, courseList2[c+3][0],
            deptPrefix2, courseList2[c+4][0]);
        dept2File.write(line, (long)strlen(line));
    }
    dept2File.write("\n\n", 2L);
    
    // List all the classroom preferences
    strcpy(line, "Classroom Preferences:\n");
    dept2File.write(line, (long)strlen(line));
    for(int i=0; i<45; i++)
    {
        if((courseList2[i][2] &= CLASSROOM_SPEC) != 0)
        {
            sprintf(line, "\t%s %d must be taught in %s, room %d\n",
                deptPrefix2, courseList2[i][0],
                dept2Bld, dept2RmNums[courseList1[i][3]]);
            dept2File.write(line, (long)strlen(line));
        }
        else if((courseList2[i][2] &= TIME_SPEC) != 0)
        {
            sprintf(line, "\t%s %d must be in the %s - %s time slot.\n",
                deptPrefix2, courseList2[i][0],
                classStartTimes[courseList2[i][3]].c_str(),
                classEndTimes[courseList2[i][3]].c_str());
            dept2File.write(line, (long)strlen(line));
        }
    }
    dept2File.write("\n\n", 2L);

    // List all the faculty assignments
    strcpy(line, "Faculty Assignments:\n");
    dept2File.write(line, (long)strlen(line));

    for(int c=0; c<45; c+=5)
    {
        sprintf(line, "\t%s %d, %s %d, %s %d, %s %d, %s %d\n",
            deptPrefix2, courseList2[c][0],
            deptPrefix2, courseList2[c+1][0],
            deptPrefix2, courseList2[c+2][0],
            deptPrefix2, courseList2[c+3][0],
            deptPrefix2, courseList2[c+4][0]);
        dept1File.write(line, (long)strlen(line));
    }

    for(int d=15; d<30; d++)
    {
        // Set the faculty preference
        if((classes[d][3] & ALL_MW_CLASSES) != 0)
            strcpy(preference, "All Mon-Wed classes");
        else if((classes[d][3] & ALL_TT_CLASSES) != 0)
            strcpy(preference, "All Tues-Thurs classes");
        else if((classes[d][3] & MORNING_ONLY) != 0)
            strcpy(preference, "Morning classes only");
        else if((classes[d][3] & AFTERNOON_ONLY) != 0)
            strcpy(preference, "Afternoon classes only");
        else if((classes[d][3] & EVENING_ONLY) != 0)
            strcpy(preference, "Evening classes only");
        else
            strcpy(preference, "None");

        sprintf(line, "%s, %s %d, %s %d, %s %d - Preference: %s\n",
                                        classDept2Fac[d-15].c_str(),
                                        deptPrefix2,
                                        classes[d][0],
                                        deptPrefix2,
                                        classes[d][1],
                                        deptPrefix2,
                                        classes[d][2],
                                        preference);
        dept2File.write(line, (long)strlen(line));
    }
    dept2File.close();
   
    return 0;
}

//-----------------------------------------------
// Sort a list of 45 course numbers
//-----------------------------------------------
void insertSort(int list[][4])
{
    int     i, j;
    int     temp1, temp2, temp3, temp4;
    int     NotDone;
    int     Key;

    for(i=1; i<45; i++)
    {
        Key = list[i][0];
        j = i;
        NotDone = (list[j-1][0] > Key);

        temp1 = list[j][0]; /* Remove and hold the one to be moved */
        temp2 = list[j][1];
        temp3 = list[j][2];
        temp4 = list[j][3];

        while(NotDone)
        {
            /* Slide all others to the right */
            list[j][0] = list[j-1][0];
            list[j][1] = list[j-1][1];
            list[j][2] = list[j-1][2];
            list[j][3] = list[j-1][3];
            j--;
            if(j > 0)
                NotDone = (list[j - 1][0] > Key);
            else
                NotDone = false;
        }

        /* Put the removed record into it's correct slot */
        list[j][0] = temp1;
        list[j][1] = temp2;
        list[j][2] = temp3;
        list[j][3] = temp4;
    }
}
