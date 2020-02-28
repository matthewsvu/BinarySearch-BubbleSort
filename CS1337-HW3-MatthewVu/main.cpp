/*
    Name - Matthew Vu
    CS1337-HW3-MatthewvVu
    Name of program- Sorting and searching hw3

    change log 1:
        1. added binarySearch, bubblesort, and generateRandomNum functions
        2. Added finding duplicate functionality and display functions
        3. Finished game
    How it works:
        The program asks the user for the # of numbers they want to generate and the max size of the nums
        then it outputs a randomized vector 1 and 2. Which vec 2 is sorted using the bubble sort algo
        while vec 1 is sorted using sort algo from std lib. This is then searched for a specific number the user asks for
        using binary search. Within the binary search method, a findDuplicates method will search both left and right for duplicates of that
        number.

        Thus finishing the program.

*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> vec1, vec2;

int countDuplicates = 0;

// will put identical random numbers into the 2 vectors
void generateRandomNum()
{
    int numMax, numSize, randNum;

    cout << "How many numbers do you want to generate?\n";
    cin >> numSize;
    cout << "How large should the numbers be?\n";
    cin >> numMax;

    while(numMax > 20 || numMax <= 0) // used to make sure the max size of the number does not go out of bound
    {
        cout << "The max cannot be greater than 20 or <= 0 please enter a number less than 20\n";
        cin >> numMax;
    }

    cout << "Outputting unsorted vector 1 and 2: \n";
    for(int i = 0; i < numSize; i++)
    {
        randNum = rand() % numMax;
        //cout << "At the current val of " << randNum << endl;
        vec1.push_back(randNum);
        vec2.push_back(randNum);
        // cout << "made it to past assigning num to vector\n";
    }
    cout << endl;
}
void displayVecCapacity(vector<int> &tempVec)
{
    cout << "The capacity of the vector is: " << tempVec.capacity() << endl;
}
void displayVecSize(vector<int> &tempVec)
{
    cout << "The size of the vector is: " << tempVec.size() << endl;
}
// display function, can use any vector to be displayed
void outputSortedVect(vector<int> sortedVec)
{
    cout << "Contents: ";
    for(unsigned int i = 0; i < sortedVec.size(); i++)
    {
        cout << sortedVec[i] << ", ";
    }
    cout << endl;
}
// sorts the vector with the std algorithm sort function
void sortVector(vector<int> &unsortedVec)
{
    sort(unsortedVec.begin(), unsortedVec.end());
}
// checks the left side of the vector for duplicates
void checkLeft(vector<int> &leftVec, int mid, int num)
{
    while(mid != 0)
    {
        if(leftVec[mid] == num)
        {
            countDuplicates++;
            mid--;
        }
        else
        {
            return;
        }
    }
}
// checks the right side of the vector for duplicates
void checkRight(vector<int> &rightVec, int mid, int num)
{

    while(mid != rightVec.size()-1)
    {
        if(rightVec[mid] == num)
        {
            countDuplicates++;
            mid++;
        }
        else
        {

            return;
        }
    }
}
// finds duplicates within the vector, used inside binary search function
void findDuplicates(vector<int> &tempVec, int mid, int num)
{
    checkLeft(tempVec, mid-1, num); //
    checkRight(tempVec, mid+1, num);
    cout << "Number of duplicates of the number is: " << countDuplicates << endl;
}
// bubble sort works by comparing the current index with next and swapping if the current index is greater then next index
void bubbleSort(vector<int> &tempVec)
{
    cout << "Start of bubble sort function \n";
    for(int i = 0; i < tempVec.size()-1; i++)
    {
        for(int currPos = 0; currPos < tempVec.size()-1; currPos++)
        {
            if(tempVec[currPos] > tempVec[currPos+1]) // checks if the current element is greater than the next element, swaps if it is
            {
                cout << "Swapping numbers: " << tempVec[currPos] << " and " << tempVec[currPos+1] << endl;
                swap(tempVec[currPos], tempVec[currPos+1]);
            }
        }
    }
    cout << "End of bubble sort function\n";
}
// sorts nums in O(log(n)) time, splits array/vector into multiple parts, sliding window algorithm
int binarySearch(int num, vector<int> &tempVec)
{
    cout << "Start of binarySearch function\n";
    int high = vec1.size() - 1;
    int low = 0;
    bool found = false;
    while(!found && low <= high)
    {
        int mid = (high + low) / 2; // calculates or recalculates the mid index after every iteratio
        if(vec1[mid] == num) // when the number we want is found
        {
            cout << "Number found at index: " << mid << endl;
            cout << "BinarySearch ended\n";
            countDuplicates++;
            findDuplicates(tempVec, mid, num);
            return mid;
        }
        if(vec1[mid] < num) // the current number we're on is less than the number we want
        {
            cout << "We're less than the number we want current val is: " << vec1[mid] << endl;
            low = mid + 1; // set low equal to mid + 1 so we can check the upper half of the vector
        }
        else // curr num is greater than one we need, so we set high equal to mid -1, so that
        {
            cout << "We're greater than the number we want current val is: " << vec1[mid] << endl;
            high = mid - 1;
        }
    }
    cout << "Number not found in vector\n";
    cout << "BinarySearch did not find the number\n";
    return -1;
}
// asks the user for the number they'd like to find duplicates for
void findUserNum()
{
    int input;
    cout << "Please enter a number and its duplicates that you wish to find \n";
    cin >> input;
    binarySearch(input, vec1);
}
// should remove all duplicates of a number
void removeDuplicates(vector <int> &tempVec)
{
    cout << "Remove duplicates";
    for(int i = 0; i < tempVec.size(); i++)
    {
        binarySearch(i, tempVec);
    }
}
int main()
{
    generateRandomNum();
    cout << "Start of vector 2: \n\n";
    outputSortedVect(vec2);
    displayVecCapacity(vec2);
    displayVecSize(vec2);
    bubbleSort(vec2);
    cout << "Sorted vec2 with bubblesort: \n";
    outputSortedVect(vec2);
    cout << endl;
    cout << "Start of vector 1: \n\n";
    outputSortedVect(vec1);
    displayVecCapacity(vec1);
    displayVecSize(vec1);
    sortVector(vec1);
    cout << "Sorted vec1 with sort algorithm built into std library: \n";
    outputSortedVect(vec1);
    findUserNum();
    // removeDuplicates(vec1);
    //outputSortedVect(vec1);
    return 0;
}
