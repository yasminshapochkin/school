
from interviewQ.presentation.code import Solution
import pytest 

def test_scheduleCourse():
    solution = Solution()
    assert solution.scheduleCourse([[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]) == 3
    assert solution.scheduleCourse([[1, 2]]) == 1
    assert solution.scheduleCourse([[3, 2], [4, 3]]) == 0

    