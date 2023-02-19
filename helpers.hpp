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

/**
 * Generic Algorithm for delineating strings of integer values: https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
 * Takes in a pointer to dest vector, a string to delimit, and a delimiting string
 * 
*/
void tokenize(std::vector<int>* dest, std::string to_delimit, std::string del = " ")
{
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = to_delimit.find(del, start);
        dest->push_back(stoi(to_delimit.substr(start, end - start)));    
    } while (end != -1);
};