#include <vector>
#include <stack>
#include <algorithm>

int largestRectangleArea(std::vector<int>& heights) {
    int size = heights.size();
    std::vector<int> sizes;

    std::stack<int> stack;

    //check the left limits
    std::vector<int> res_left(size);
    for(int i = 0; i < size; i++){
        while ((!stack.empty()) && heights[stack.top()]>= heights[i]){
           stack.pop();
        }
        res_left[i] = stack.empty() ? 0 : (stack.top()+1);
        stack.push(i);
    }

    //check the right limits
    stack= std::stack<int>();
    std::vector<int> res_right(size);
    for(int i = size-1; i > -1; i--){
        while ((!stack.empty()) && heights[stack.top()]>= heights[i]){
           stack.pop();
        }
        res_right[i] = stack.empty() ? (size-1) : (stack.top()-1);
        stack.push(i);
    }

    int result = 0;
    for(int i = 0; i < size; i++){
        result = std::max(result,heights[i]*(res_right[i]-res_left[i] + 1));
    }

    return result;
}


