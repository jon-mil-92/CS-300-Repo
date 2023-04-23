//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Jonathan Miller
// Version     : 1.0
// Description : Project Two BinarySearchTree Implementation
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Forward declarations.
bool checkFileFormat(string csvPath, vector<string>& csvLines);
string toUpperCase(string& str);

// Define a structure to hold course information.
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;

    // Default constructor.
    Course() {
        courseNumber = "";
        courseName = "";
        prerequisites.resize(0);
    }
};

// Internal structure for a binary search tree node.
struct Node {
    Course course;
    Node *left;
    Node *right;

    // Default constructor.
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a course.
    Node(Course aCourse) :
            Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree.
 */
class BinarySearchTree {

private:
    Node* node;

    void deleteNode(Node* node);
    void addNode(Node* node, Course course);
    void printSampleSchedule(Node* node);
    void printCourseInformation(string courseNumber);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Clear();
    void Insert(Course course);
    void PrintSampleSchedule();
    void PrintCourseInformation(string courseNumber);
};

//============================================================================
// BinarySearchTree private method definitions.
//============================================================================

/**
 * Recursively delete all nodes in the BST.
 * 
 * @param curNode - This is the current node in the deletion process.
 */
void BinarySearchTree::deleteNode(Node* currentNode) {
    // If the current node is not null...
    if (currentNode != nullptr) {
        // If the current node has no children...
        if ((currentNode->left == nullptr) && (currentNode->right == nullptr)) {
            // Delete the current node from the BST.
            delete currentNode;
            currentNode = nullptr;
        }
        // If the current node has any children...
        else {
            // Recursively delete the left node.
            deleteNode(currentNode->left);

            // Recursively delete the right node.
            deleteNode(currentNode->right);
        }
    }
}

/**
 * Add a course to some node (recursive).
 *
 * @param node - Current node in tree.
 * @param course - Course to be added.
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // If the current node's course number is greater than the specified course's course number...
    if (node->course.courseNumber > course.courseNumber) {
        // If the current node does not have a left child...
        if (node->left == nullptr) {
            // Set the left child to a new course node containing the specified course.
            node->left = new Node(course);
        }
        // If the current node has a left child...
        else {
            // Recursively traverse down the left sub-tree.
            addNode(node->left, course);
        }
    }
    // If the current node's course number is less than or equal to the specified course's course number...
    else {
        // If the current node does not have a right child...
        if (node->right == nullptr) {
            // Set the right child to a new course node containing the specified course.
            node->right = new Node(course);
        }
        // If the current node has a right child...
        else {
            // Recursively traverse down the right sub-tree.
            addNode(node->right, course);
        }
    }
}

/**
* Recursively traverse the BST in order and print each node.
* 
* @param node - The current node in the BST.
*/
void BinarySearchTree::printSampleSchedule(Node* node) {
    // If the current node is not null...
    if (node != nullptr) {
        // Recursively print out the left sub-tree.
        printSampleSchedule(node->left);

        // Print the node's course number and course name.
        std::cout << node->course.courseNumber << ", "
            << node->course.courseName << endl;

        // Recursively print out the right sub-tree.
        printSampleSchedule(node->right);
    }
}

void BinarySearchTree::printCourseInformation(string courseNumber) {
    // Set the current node to the root.
    Node* currentNode = node;

    // Boolean to determine if the course was found.
    bool courseFound = false;

    // Keep looping downwards until the bottom of the tree is reached or a matching course number is found.
    while (currentNode != nullptr) {
        // If the current node's course contains the specified courseNumber...
        if (currentNode->course.courseNumber == courseNumber) {
            // Update the courseFound boolean since it was found.
            courseFound = true;

            // Print the node's course number and course name.
            cout << currentNode->course.courseNumber << ", "
                 << currentNode->course.courseName << endl;

            // Get the amount of prerequisites the current course has.
            int prerequisitesSize = currentNode->course.prerequisites.size();

            // Prerequisite identifier string.
            cout << "Prerequisites: ";

            // If the course has any prerequisites...
            if (prerequisitesSize > 0) {
                // Print each prerequisite course number.
                for (int i = 0; i < prerequisitesSize; i++) {
                    // If the current prerequisite is not the last one in the prerequisites vector...
                    if (i < prerequisitesSize - 1) {
                        // Print the course number followed by a comma.
                        cout << currentNode->course.prerequisites.at(i) << ", ";
                    }
                    // If it is the last or only element in the prerequisites vector...
                    else {
                        // Print the course number followed by a new line.
                        cout << currentNode->course.prerequisites.at(i) << endl;
                    }
                }
            }
            else {
                // Print a message to show that the course has no prerequities.
                cout << "None" << endl;
            }

            // Stop searching after the course is found.
            break;
        }
        // If the specified course number is smaller than the course number at the current node...
        else if (courseNumber < currentNode->course.courseNumber) {
            // Traverse the left sub-tree.
            currentNode = currentNode->left;
        }
        // If the specified course number is larger than the course number at the current node...
        else {
            // Traverse the right sub-tree.
            currentNode = currentNode->right;
        }
    }

    // If the specified course was not found...
    if (!courseFound) {
        // Print a message to show that the course was not found.
        cout << "Course not found." << endl;
    }
}

//============================================================================
// BinarySearchTree public method definitions.
//============================================================================

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // The root node is initially null.
    node = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // Recursively delete each node in the BST, starting at the root.
    deleteNode(node);
}

/**
 * Remove all elements from the BST.
 */
void BinarySearchTree::Clear() {
    // Recursively delete each node in the BST, starting at the root.
    deleteNode(node);

    // Reinitialize the root node after deleting all nodes from the BST.
    node = nullptr;
}

/**
 * Insert a course into the BST.
 */
void BinarySearchTree::Insert(Course course) {
    // If the BST is empty...
    if (node == nullptr) {
        // Initialize the root node with the given course.
        node = new Node(course);
    }
    else {
        // Add a node with the given course into the correct place in the BST.
        addNode(node, course);
    }
}

/**
 * Print each course in ascending alphanumeric order.
 */
void BinarySearchTree::PrintSampleSchedule() {
    // Call the private method to display all courses from the BST in order.
    printSampleSchedule(node);
}

/**
 * Search for and print a specified course.
 * 
 * @param courseNumber - The number of the course to print.
 */
void BinarySearchTree::PrintCourseInformation(string courseNumber) {
    // Call the private method to find and print the given course number.
    printCourseInformation(courseNumber);
}

//============================================================================
// Static Methods
//============================================================================

/**
*  This method checks the supplied csv file for the correct format
*  and populates a vector of lines from the csv file.
*
*  @param csvPath - This is the string path for the specified csv file.
*  @param csvLines - This is the vector to store all course lines from the csv file.
*
*  @return Whether or not the specified csv file is in the correct format or not.
*/
bool checkFileFormat(string csvPath, vector<string>& csvLines) {
    string currentLine;
    string courseElement;
    vector<string> courseNumbers;
    int elementCount;
    ifstream csvFile;

    // Try to open the specified csv file.
    csvFile.open(csvPath);

    // If the file could not be opened...
    if (!csvFile.is_open()) {
        // Display an error message.
        cout << endl << "Could not open file!" << endl;

        // Do not attempt to parse the file if it cannot be opened.
        return false;
    }

    // Clear the csv lines vector before adding to it.
    csvLines.clear();

    // Populate the csvLines and courseNumbers vectors.
    while (getline(csvFile, currentLine)) {
        // Do not process blank lines. Skip lines with only whitespace.
        if (!all_of(currentLine.begin(), currentLine.end(), isspace)) {
            // Store the current line of the csv file for loading courses into the BST.
            csvLines.push_back(currentLine);

            // Open the current line string as a stream.
            istringstream currentLineStream(currentLine);

            // Get the first element from the current line.
            while (getline(currentLineStream, courseElement, ',')) {
                // Store all encountered course numbers.
                courseNumbers.push_back(toUpperCase(courseElement));

                // Only get the first courseElement to store in courseNumbers.
                break;
            }
        }
    }

    // Close the file after getting all course numbers.
    csvFile.close();

    // Reopen the specified csv file.
    csvFile.open(csvPath);

    // Get each line in the csv file.
    while (getline(csvFile, currentLine)) {
        // Do not process blank lines. Skip lines with only whitespace.
        if (!all_of(currentLine.begin(), currentLine.end(), isspace)) {
            // Open the current line string as a stream.
            istringstream currentLineStream(currentLine);

            // The number of course elements from each line in the csv file.
            elementCount = 0;

            // Define a variable to hold the course number for the current line.
            string currentCourseNumber = "";

            // Define a variable to hold the course name for the current line.
            string currentCourseName = "";

            // Define a variable to hold a prerequisite for the current line.
            string currentPrerequisite = "";

            // Get each element in the current line.
            while (getline(currentLineStream, courseElement, ',')) {
                // Increment the element count once a courseElement is retrieved.
                elementCount++;
            
                // Store the current course number for the missing course name error.
                if (elementCount == 1) {
                    currentCourseNumber = toUpperCase(courseElement);
                }

                // Store the current course number for the missing course name error.
                if (elementCount == 2) {
                    currentCourseName = courseElement;
                }

                // Check if the current prerequisite exist in the file. Skip checking empty and whitespace course numbers.
                if (elementCount > 2 && !all_of(courseElement.begin(), courseElement.end(), isspace)) {
                    // Store the current course element as the current prerequisite.
                    currentPrerequisite = toUpperCase(courseElement);

                    // If the prerequisite was not previously added to the vector of course numbers.
                    if (find(courseNumbers.begin(), courseNumbers.end(), currentPrerequisite) == courseNumbers.end()) {
                        // Print an error message for the missing prerequisite.
                        cout << endl << "Prerequisite " << currentPrerequisite << " not found in the file." << endl;

                        return false;
                    }
                }
            }

            // After parsing the currentLineStream, if there is not a course name or it's only whitespace...
            if (elementCount == 1 || all_of(currentCourseName.begin(), currentCourseName.end(), isspace)) {
                // Print an error message for the missing course name.
                cout << endl << "No course name found for " << currentCourseNumber << "." << endl;

                return false;
            }

            // After parsing the currentLineStream, if there is not a course number (if it's only whitespace)...
            if (elementCount >= 2 && all_of(currentCourseNumber.begin(), currentCourseNumber.end(), isspace)) {
                // Print an error message for the missing course number.
                cout << endl << "No course number found for " << currentCourseName << "." << endl;

                return false;
            }
        }
    }

    // If no formatting errors are found...
    return true;
}

/**
*  This method loads the BST with courses from a vector of raw string lines from the specified csv file.
*
*  @param bst - This is the BinarySearchTree that will store all of the courses.
*  @param csvPath - This is the string path for the specified csv file.
*  @return - Whether the courses were successfully loaded.
*/
bool loadCourses(BinarySearchTree* bst, string csvPath) {
    // This is the vector that stores all raw string lines from the csv file.
    vector<string> csvLines;

    // Check the format of the csv file before continuing.
    if (!checkFileFormat(csvPath, csvLines)) {
        cout << endl << "Incorrect file format." << endl;

        return false;
    }

    string courseElement;
    int elementIndex;
    int numberOfLoadedCourses = 0;

    // Parse through each line from the csv file.
    for (string courseString : csvLines) {
        // Create a new Course struct to add to the BST.
        Course newCourse;

        // Open the current course string as a stream.
        istringstream courseStringStream(courseString);

        elementIndex = 0;

        // Get each element from the current course string stream.
        while (getline(courseStringStream, courseElement, ',')) {
            // Update the new course struct with the course number from the current course element.
            if (elementIndex == 0) {
                // The letters in the course number should be uppercase for searching purposes.
                newCourse.courseNumber = toUpperCase(courseElement);
            }

            // Update the new course struct with the course name from the current course element.
            if (elementIndex == 1) {
                newCourse.courseName = courseElement;
            }

            // Append the current course element (prerequisite) to the new course struct's prerequisites vector.
            if (elementIndex >= 2) {
                // Skip empty strings or strings of whitespace.
                if (!all_of(courseElement.begin(), courseElement.end(), isspace)) {
                    newCourse.prerequisites.push_back(toUpperCase(courseElement));
                }
            }

            elementIndex++;
        }

        // Insert the new course into the BST after processing the current line.
        bst->Insert(newCourse);

        // Update the number of courses that were loaded into the BST.
        numberOfLoadedCourses++;
    }

    // Print the number of courses that were loaded into the BST.
    if (numberOfLoadedCourses == 1) {
        cout << endl << numberOfLoadedCourses << " course was loaded." << endl;
    }
    else {
        cout << endl << numberOfLoadedCourses << " courses were loaded." << endl;
    }

    return true;
}

/**
* Convert all the letters in a given string to uppercase.
* 
* @param str - The string to make uppercase.
*/
string toUpperCase(string& str) {
    // Loop through each character in the string and make it uppercase.
    transform(str.begin(), str.end(), str.begin(), ::toupper);

    return str;
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {
    // The path of the csv file of courses.
    string csvPath;

    // The course number to find and print.
    string courseNumber;

    // Define a binary search tree to hold all courses.
    BinarySearchTree* bst;

    // Initialize the data structure used to store the courses.
    bst = new BinarySearchTree();

    // Define a boolean to determine if courses have been loaded yet.
    bool coursesLoaded = false;

    // Define a boolean to determine if user input failed or not.
    bool inputFailed = false;
    
    // Define a variable for the menu option. Set to 0 to enter program loop.
    int choice = 0;

    // Print a greeting message.
    cout << "Welcome to the ABCU course planner!" << endl;

    // Main program loop. Kepp running the program until the user enters 9.
    while (choice != 9) {
        // The menu title and options.
        cout << endl << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl << endl;

        // Reset the input failed boolean.
        inputFailed = false;

        // Ask the user for an option number and store it.
        cout << "Enter an option number: ";
        cin >> choice;
        cout << endl;

        // Only use the first integer that was entered. Disregard everything after the integer.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Print an error message if the user does not first enter an integer. This avoids program loops.
        if (cin.fail()) {
            // Update the input failed boolean so that the default switch case does not also display an error message.
            inputFailed = true;

            // Clear the input buffer and ignore all previous input.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Print an error message because the user did not enter a correct option number.
            cout << "Please enter an integer value of 1, 2, 3, or 9. " << endl;
        }

        switch (choice) {

        case 1:
           // Ask the user for the csv file name and store it.
            cout << "Enter the system path and file name (Example: C:\\courses.csv): ";
            cin >> csvPath;

            // Clear the BST before loading it with courses.
            // This allows the user to load different files while the program is running.
            bst->Clear();

            // Load all the courses from the specified csv file and get whether it was successful or not.
            coursesLoaded = loadCourses(bst, csvPath);

            break;

        case 2:
            // If the user has successfully loaded courses via option 1...
            if (coursesLoaded) {
                // Print all courses.
                bst->PrintSampleSchedule();
            }
            else
            {
                // Print an error message if the user has not loaded courses yet.
                cout << "Please load courses with Option 1 first." << endl;
            }

            break;

        case 3:
            // If the user has successfully loaded courses via option 1...
            if (coursesLoaded) {
                // Ask the user for the course number and store it.
                cout << "Enter the course number to find: ";
                cin >> courseNumber;
                cout << endl;

                // Convert the letters in the course number to uppercase before searching.
                // All course number letters are converted to uppercase before storing them in the BST.
                toUpperCase(courseNumber);

                // Print the specified course number and its prerequisites if it is found.
                bst->PrintCourseInformation(courseNumber);
            }
            else
            {
                // Print an error message if the user has not loaded courses yet.
                cout << "Please load courses with Option 1 first." << endl;
            }

            break;

        case 9:
            // Do nothing. Don't enter the default case. Allow the program to terminate.

            break;

        default:
            // If the input did not fail and the user entered an invalid integer...
            if (!inputFailed) {
                // Print an error message if the user does not enter a correct option number.
                cout << "Please enter an integer value of 1, 2, 3, or 9. " << endl;
            }
            
            break;
        }
    }

    // Print a program end message after the user enters 9.
    cout << "Thank you for using the course planner! Goodbye." << endl;

	return 0;
}
