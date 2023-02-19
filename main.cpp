#include <iostream>
#include <fstream>
#include <vector>
#include <set>

class Preferences {
public:
    std::vector<int> order;
    void print_prefs();
    int get_big(int a, int b);
    bool assigned = 0;
};

void Preferences::print_prefs() {
    // std::cout << "printing prefs: ";
    for (int pref : order) {
        std::cout << pref << " ";
    }
    std::cout << std::endl;
}

int Preferences::get_big(int a, int b) {
    for (int it = 0; it < 5; it++) {
        if (this->order.at(it) == a) return a;
        if (this->order.at(it) == b) return b;
    }
    return -1;
}

/**
 * Generic Algorithm for delineating strings: https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
 * Takes in a pointer to dest vector, a string to delimit, and a delimiting string
 * 
*/
template <typename T>
void tokenize(std::vector<T>* dest, std::string to_delimit, std::string del = " ")
{
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = to_delimit.find(del, start);
        dest->push_back(to_delimit.substr(start, end - start));
    } while (end != -1);
}

void tokenize(std::vector<int>* dest, std::string to_delimit, std::string del = " ")
{
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = to_delimit.find(del, start);
        dest->push_back(stoi(to_delimit.substr(start, end - start)));
    } while (end != -1);
}

int main() {
    std::vector< std::vector<int> >* file_raw_input = new std::vector< std::vector<int> >(); 

    std::ifstream fileobj ("default_data.txt");

    std::string buffer;

    for (int i = 0; i<10; i++) {
        
        std::getline(fileobj, buffer);

        if (buffer.empty()) return 1;

        std::vector<int>* programmer_response = new std::vector<int>();

        tokenize(programmer_response,buffer);
        
        // std::cout<<"read: ";
        // for (int pref : *programmer_response) {
        //     std::cout<<pref<<" ";
        // }
        file_raw_input->push_back(*programmer_response);
        // std::cout<<std::endl;
        delete programmer_response;
    }

  

    std::vector<Preferences> departments_rankings;
    for (int j = 0; j<5;j++){
        Preferences department;
        for (int i = 0; i < 5; i++) {
            department.order.push_back(file_raw_input->at(i).at(j));
        }
        departments_rankings.push_back(department);
    }

    std::vector<Preferences> programmers_rankings;
    for (int j = 0; j<5;j++){
        Preferences programmer;
        for (int i = 5; i < 10; i++) {
            programmer.order.push_back(file_raw_input->at(i).at(j));
        }
        programmers_rankings.push_back(programmer);
    }

    std::cout << "Department Rankings: \n";
    for (int i = 0; i < departments_rankings.size(); i++) {
        std::cout<<"Dept. "<<i+1<<": ";
        departments_rankings.at(i).print_prefs();
    }

    std::cout << "Programmer Rankings: \n";
    for (int i = 0; i < departments_rankings.size(); i++) {
        std::cout<<"Dev. "<<i+1<<": ";
        departments_rankings.at(i).print_prefs();
    }

    int prog_2_dept[5];

    for (int programmer = 0; programmer < 5; programmer++) { // for every programmer
        int assigned_department = -1;
        int priority = 4;
        
        for (int department = 0; department < 5; department++) {
            for (int pref_order = 0; pref_order < 5; pref_order++) {
                if (departments_rankings.at(department).order.at(pref_order) == (programmer+1)
                && pref_order <= priority
                && !departments_rankings.at(department).assigned
                ) {
                    if (assigned_department == -1) {
                        assigned_department = (department+1);
                    } else  {
                        assigned_department = programmers_rankings.at(programmer).get_big(assigned_department, (department+1));
                    }
                    priority = pref_order;
                }                   
            }
        }
        departments_rankings.at(assigned_department - 1).assigned = 1;
        prog_2_dept[programmer] = assigned_department;
    }
    

    for (int i = 0; i < 5; i++) {
        // std::cout << "programmer " << (i+1) << " to dept " << prog_2_dept[i] << '\n';
        std::cout << "dept " << prog_2_dept[i] << " gets programmer " << (i+1) << '\n';
    }


  
    







    std::cout<<std::endl;
    return 0;
}