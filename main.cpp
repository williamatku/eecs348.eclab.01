#include <iostream>
#include <fstream>
#include <vector>

#include "helpers.hpp"

#define NUM_OF_DEPTS_AND_DEVS 5

/*
    Dev:            William A. Morris
    Created:        2023-02-09
    Last Modified:  2023-02-09
    KUID:           3057236
    Email:          morris.william@ku.edu
    Class:          EECS 348 
    Lab Section:    Thursdays @9am
    Description:    
        A simple (and probably unsafe) C++17 Program to assign programmers to departments, 
            accounting for both department and developer preference.
*/

class Preferences {
public:
    std::vector<int> order;
    void print_prefs();
    int get_preferred(int a, int b);
    bool assigned = 0;
};

/**
 * Method to print out the preferred order of ints
*/
void Preferences::print_prefs() {
    for (int pref : order) {
        std::cout << pref << " ";
    }
    std::cout << std::endl;
}

/**
 * Returns the preferred int (a vs b) of the object
 * For programmers, this will return their preferred department 
*/
int Preferences::get_preferred(int a, int b) {
    for (int it = 0; it < NUM_OF_DEPTS_AND_DEVS; it++) {
        if (this->order.at(it) == a) return a;
        if (this->order.at(it) == b) return b;
    }
    return -1;
}

/**
 * App-specific function to read a well formatted input-file into a int[][]
*/
void read_file(std::vector< std::vector<int> >& file) {
    std::ifstream fileobj ("default_data.txt");

    std::string buffer;

    for (int i = 0; i < (2*NUM_OF_DEPTS_AND_DEVS); i++) { // read every line into memory
        
        std::getline(fileobj, buffer);
        // if the buffer runs out before getting all data required by the program
        if (buffer.empty()) exit(EXIT_FAILURE); // exit failure

        std::vector<int>* read_line = new std::vector<int>();

        tokenize(read_line,buffer); // split buffer into white-space delimited vector

        file.push_back(*read_line);

        delete read_line; // free mem
    }
}

void get_department_rankings(std::vector<Preferences>* departments_rankings) {
    std::vector< std::vector<int> > file_raw_input;

    read_file(file_raw_input);    

    for (int i = 0; i < NUM_OF_DEPTS_AND_DEVS; i++){
        Preferences department; // create new object for every department
        for (int j = 0; j < NUM_OF_DEPTS_AND_DEVS; j++) {
            department.order.push_back(file_raw_input.at(j).at(i)); // and read in ranking
        }
        departments_rankings->push_back(department); // save
    }

    std::cout << "Department Rankings: \n"; // Print out every departments' developer preference
    for (int i = 0; i < departments_rankings->size(); i++) {
        std::cout<<"Dept. "<<i+1<<": ";
        departments_rankings->at(i).print_prefs();
    }
    std::cout << '\n';
}

void get_programmer_rankings(std::vector<Preferences>* programmers_rankings) {
    std::vector< std::vector<int> > file_raw_input; 

    read_file(file_raw_input);    

    for (int i = 0; i < NUM_OF_DEPTS_AND_DEVS; i++){
        Preferences programmer; // create new object for every programmer
        for (int j = NUM_OF_DEPTS_AND_DEVS; j < (2*NUM_OF_DEPTS_AND_DEVS); j++) {
            programmer.order.push_back(file_raw_input.at(j).at(i)); // and read in ranking
        }
        programmers_rankings->push_back(programmer); // save
    }

    std::cout << "Programmer Rankings: \n"; // Print out every programmers' department pref.
    for (int i = 0; i < programmers_rankings->size(); i++) {
        std::cout<<"Dev. "<<i+1<<": ";
        programmers_rankings->at(i).print_prefs();
    }
    std::cout << '\n';
}

int main() {
    std::vector<Preferences>* departments_rankings = new std::vector<Preferences>();
    std::vector<Preferences>* programmers_rankings = new std::vector<Preferences>();
    get_department_rankings(departments_rankings);
    get_programmer_rankings(programmers_rankings);

    int prog_2_dept[NUM_OF_DEPTS_AND_DEVS]; // Create static array where index = programmer + 1 AND value = department + 1

    // for every programmer, attempt to assign a department
    for (int programmer = 0; programmer < NUM_OF_DEPTS_AND_DEVS; programmer++) { 
        int assigned_department = -1; // start with invalid department
        int priority = NUM_OF_DEPTS_AND_DEVS; 
                    
        // iterate through every departments' preference for programmers
        for (int department = 0; department < NUM_OF_DEPTS_AND_DEVS; department++) {    
        for (int pref_order = 0; pref_order < NUM_OF_DEPTS_AND_DEVS; pref_order++) {
            // if a specific department wants a programmer
            if (departments_rankings->at(department).order.at(pref_order) == (programmer+1)
            && pref_order <= priority // AND has a higher priority than other departments
            && !departments_rankings->at(department).assigned // AND has not already been assigned a programmer
            ) {
                if (assigned_department == -1) { 
                    assigned_department = (department+1); // assign a department
                } else { // if the programmer has already been assigned a department
                    // they will be RE-ASSIGNED to their preferred department
                    assigned_department = programmers_rankings->at(programmer).get_preferred(assigned_department, (department+1));
                }
                priority = pref_order; // retain priority that the programmer was assigned with
            }                   
        }}
        departments_rankings->at(assigned_department - 1).assigned = 1; // mark the final department assigned to a programmer
        prog_2_dept[programmer] = assigned_department; // and save the assignment
    }

    std::cout << "Assignments: \n"; 
    for (int i = 0; i < NUM_OF_DEPTS_AND_DEVS; i++) { // print out formatted list of programmers' department assignments
        // std::cout << "programmer " << (i+1) << " to dept " << prog_2_dept[i] << '\n  ';
        std::cout << "dept " << prog_2_dept[i] << " gets programmer " << (i+1) << '\n';
    }

    std::cout<<std::endl; // flush output
    return 0; // exit SUCCESS
}