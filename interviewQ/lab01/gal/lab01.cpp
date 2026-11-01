/*Rectangle Area*/
#include <iostream>
#include <algorithm>
int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    //finding the shared area
    int bigXLeft=std::max(ax1,bx1);
    int smallXRight=std::min(ax2,bx2);
    int bigYLeft = std::max(ay1,by1);
    int smallYRight= std::min(ay2,by2);

    //(bigXLeft , bigYLeft )    (smallXRight , smallYRight)
    int sharedArea;
    if( bigXLeft >= smallXRight || bigYLeft >= smallYRight)
        sharedArea= 0;
    else{
        sharedArea =( smallXRight - bigXLeft)  * ( smallYRight- bigYLeft );
    }

    //total area
    int aArea=( ax2-ax1 ) * ( ay2-ay1 );
    int bArea=( bx2-bx1 ) * ( by2-by1 );
    
    return (aArea + bArea -sharedArea);
}

