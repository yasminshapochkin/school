
from code import Solution
import unittest

class TestCode(unittest.TestCase):

    def test_Equal(self):
        solution = Solution()
        self.assertEqual(solution.scheduleCourse([[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]), 3)
        self.assertEqual(solution.scheduleCourse([[1, 2]]), 1)
        self.assertEqual(solution.scheduleCourse([[2,2] , [1,2] , [2,3]]), 2)
        self.assertEqual(solution.scheduleCourse([[7,16],[2,3],[3,12],[3,14],[10,19],[10,16],[6,8],[6,11],[6,16]]), 4) 

    def test_IncorrectInput(self):   
        solution = Solution() 
        self.assertEqual(solution.scheduleCourse([[0,0]]), 0)
        self.assertEqual(solution.scheduleCourse([]), 0)
        self.assertEqual(solution.scheduleCourse([[3, 2], [4, 3]]), 0)



if __name__ == '__main__':
    unittest.main()