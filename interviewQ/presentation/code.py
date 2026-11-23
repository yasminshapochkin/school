

import heapq

class Solution:
    def scheduleCourse(self, courses: List[List[int]]) -> int:
        courses.sort(key=lambda c: c[1])         
        heap = []                                
        time = 0

        for duration , lastDay in courses:
            heapq.heappush(heap, -duration)
            time += duration
            if time > lastDay:                       
                time += heapq.heappop(heap)      

        return len(heap)