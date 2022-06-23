/*
- The dictionary type that is present in C++ is called map which acts like a container to store values that are indexed by keys.
- Each value in the dictionary also called a map is associated with a key.
- The type of all the values must be of the same type in a C++ map and the type of all the keys in a C++ map must be of the same type but it is not necessary that both the keys and values must be of the same type.
- To be able to make use of a map in C++, the map header file must be included in the C++ standard library.
- The values in a map can be iterated through a loop to obtain the corresponding key where each iterated item represents a key-value pair.
*/

// map<datatype_of_keys, datatype_of_values>name_of_the_map;
// where datatype_of_keys is the data type of the keys stored in the map, datatype_of_values is
// the data type of the values stored in the map and name_of_the_map represents the map name and it is a variable.

// ===============================================
// Example #1
// C++ program to demonstrate the dictionary type map by creating a map to store key-value pairs in the map and then retrieving them:

// the headers map, string and iostream are used to be able to make use of map function, cin, cout and strings
#include <iostream>
#include <map>
#include <string>

using namespace std;

// main method is called
int main()
{
    // a map called capitalcities is created which stores keys of type strings and corresponding values of type strings
    map<string, string> capitalcities;
    // the elements are added to the created map
    capitalcities["NewDelhi"] = "India";
    capitalcities["Bangalore"] = "Karnataka";
    capitalcities["Mumbai"] = "Maharashtra";
    capitalcities["Chennai"] = "TamilNadu";

    // iterating through the created map to print out the key and value pairs from the map
    for (auto element : capitalcities)
    {
        // element.first represents the key in the map
        cout << element.first << " is the capital of ";
        // element.second represents the value in the map
        cout << element.second << endl;
    }
    return 0;
}

// ===============================================
// Example #2
// C++ program to demonstrate the dictionary type map by creating a map to store key-value pairs in the map and then retrieving them:

// the headers map, string and iostream are used to be able to make use of map function, cin, cout and strings
#include <iostream>
#include <map>
#include <string>

using namespace std;

// main method is called
int main()
{
    // a map called age is created which stores keys of type strings and corresponding values of type int
    map<string, int> age;
    // the elements are added to the created map
    age["Sanju"] = 10;
    age["Ranju"] = 20;
    age["Manju"] = 30;
    age["Gunju"] = 40;

    // iterating through the created map to print out the key and value pairs from the map
    for (auto element : age)
    {
        // element.first represents the key in the map
        cout << element.first << " is ";
        // element.second represents the value in the map
        cout << element.second << "years old" << endl;
    }
    return 0;
}

// ===============================================
// C++ program to demonstrate the dictionary type map by creating a map to store key-value
// pairs in the map and then retrieving them

// the headers map, string and iostream are used to be able to make use of map function, cin, cout and strings
#include <iostream>
#include <map>
#include <string>

using namespace std;

// main method is called
int main()
{
    // a map called patriotism is created which stores keys of type strings and corresponding values of type int
    map<string, string> patriotism;
    // the elements are added to the created map
    patriotism["India is my motherland"] = "I love my India";
    // iterating through the created map to print out the key and value pairs from the map
    for (auto element : patriotism)
    {
        // element.first represents the key in the map
        cout << element.first << " and ";
        // element.second represents the value in the map
        cout << element.second << endl;
    }
    return 0;
}