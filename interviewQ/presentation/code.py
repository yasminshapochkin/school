

import heapq
from typing import List

class Solution:
    def scheduleCourse(self, courses: List[List[int]]) -> int:
        if not courses:
            return 0
        courses.sort(key=lambda c: c[1])         
        heap = []                                
        time = 0

        for duration , lastDay in courses:
            if duration > lastDay or duration == 0 :
                continue
            heapq.heappush(heap, -duration)
            time += duration
            if time > lastDay:                       
                time += heapq.heappop(heap)      

        return len(heap)