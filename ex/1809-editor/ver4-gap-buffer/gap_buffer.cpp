// C++ program of implementation of gap buffer 
  
#include <bits/stdc++.h>  
using namespace std;  
  
char buffer[50];  
int gap_size = 10;  
int gap_left = 0;  
int gap_right = gap_size - gap_left-1;  
int size = 10;  
  
// Function that is used to grow the gap  
// at index position and return the array  
  
  
void grow(int k, int position)  
{  
  
    char a[size];  
  
    // Copy characters of buffer to a[]  
    // after position  
    for (int i = position; i < size; i++) {  
        a[i - position] = buffer[i];  
          
    }  
      
    // Insert a gap of k from index position  
    // gap is being represented by '-'  
    for (int i = 0; i < k; i++) {  
        buffer[i + position] = '_';  
    }  
      
    // Reinsert the remaining array  
    for (int i = 0; i < position + k; i++) {  
        buffer[position + k + i] = a[i];  
    }  
  
    size += k; 
    gap_right+=k; 
}  
  
// Function that is used to move the gap  
// left in the array  
void left(int position)  
{  
    // Move the gap left character by character  
    // and the buffers  
    while (position < gap_left) {  
        gap_left--;  
        gap_right--;  
        buffer[gap_right+1] = buffer[gap_left]; 
        buffer[gap_left]='_'; 
    }  
}  
  
// Function that is used to move the gap  
// right in the array  
void right(int position)  
{  
    // Move the gap right character by character  
    // and the buffers  
    while (position > gap_left) {  
        gap_left++;  
        gap_right++;  
        buffer[gap_left-1] = buffer[gap_right];  
        buffer[gap_right]='_'; 
    }  
}  
  
// Function to control the movement of gap  
// by checking its position to the point of  
// insertion  
void move_cursor(int position)  
{  
    if (position < gap_left) {  
        left(position);  
    }  
    else {  
        right(position);  
    }  
}  
  
// Function to insert the string to the buffer  
// at point position  
void insert(string input, int position)  
{  
    int len = input.length();  
    int i = 0;  
  
    // If the point is not the gap check  
    // and move the cursor to that point  
    if (position != gap_left) {  
        move_cursor(position);  
    }  
  
    // Insert characters one by one  
    while (i < len) {  
        // If the gap is empty grow the size  
        if (gap_right == gap_left) {  
            int k = 10;  
            grow(k, position);  
        }  
  
        // Insert the character in the gap and  
        // move the gap  
        buffer[gap_left] = input[i];  
        gap_left++;  
        i++;  
        position++; 
    }  
}  
  
// Driver code  
int main()  
{  
    // Initializing the gap buffer with size 10  
    for (int i = 0; i < 10; i++) {  
        buffer[i] = '_';  
    }  
  
    cout << "Initializing the gap buffer "
         << "with size 10" << endl; 
   
    for (int i = 0; i < size; i++) {  
        cout << buffer[i]<<" ";  
    }  
  
    cout << endl;  
  
    // Inserting a string to buffer  
    string input = "GEEKSGEEKS";  
    int position = 0;  
  
    insert(input, position);  
  
    cout << endl;  
    cout << "Inserting a string to buffer"
         << ": GEEKSGEEKS" << endl;  
    cout << "Output: ";  
    for (int i = 0; i < size; i++) {  
        cout << buffer[i]<<" ";  
    }  
  
    input = "FOR";  
    position = 5;  
  
    insert(input, position);  
  
    cout << endl;  
    cout << endl;  
      
    cout << "Inserting a string to buffer"
         << ": FOR" << endl;  
    cout << "Output: ";  
    for (int i = 0; i < size; i++) {  
        cout << buffer[i]<<" ";  
    }  
  
  
    return 0; 
} 
