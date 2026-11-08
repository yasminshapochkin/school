
#include <iostream>

// function calculates by choosing the maximum of the lower left corner and the minimum of the upper
// right corner to find the intersection area of two rectangles. 
// and then calculated the total area and it subtracts the intersection area from the total area to return the answer.
int square_func(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2 ){
    int rx1 = (ax1 > bx1) ? ax1 : bx1;
    int ry1 = (ay1 > by1) ? ay1 : by1;
    int rx2 = (ax2 < bx2) ? ax2 : bx2;
    int ry2 = (ay2 < by2) ? ay2 : by2;

    int united_area = 0;
    if (rx1 >= rx2 || ry1 >= ry2){united_area = 0;}

    else{ 
        united_area = std::abs(rx2 - rx1) * std::abs(ry2 - ry1);
    }

    return std::abs(ax2 - ax1) * std::abs(ay2 - ay1) + std::abs(bx2 - bx1) * std::abs(by2 - by1) - united_area;


}

