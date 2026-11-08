class Solution {
public:

#include <vector>
#include <stack>
#include <algorithm>

int largestRectangleArea(std::vector<int>& heights) {

    int size = heights.size();
    std::vector<int> Result_Left(size); 
    std::vector<int> sizes;
    std::stack<int> Stack;
    // left
    for(int i = 0; i < size ; i++){
        while(!(Stack.empty()) &&  heights[Stack.top()]> heights[i]){
            Stack.pop();
        }
        Result_Left[i] = Stack.empty() ? 0 : Stack.top();
        Stack.push(i);
    }
    
    Stack = std::stack<int>();
    std::vector<int> Result_Right(size);
    // right
    for(int i = size-1; i >= 0 ; i--){
        while(!(Stack.empty()) && heights[Stack.top()] > heights[i]){
            Stack.pop();
        }
        Result_Right[i] = Stack.empty() ? (size-1) : (Stack.top()-1);
        Stack.push(i);
    }
    int result = 0;
    for(int i = 0; i < size ; i++){
        result = std::max(result, heights[i]*(Result_Right[i]-Result_Left[i]) );
    }
    return result;
}



};