
from code import Solution
import unittest

class TestStringMethods(unittest.TestCase):

    def test_Equal(self):
        solution = Solution()
        self.assertEqual(solution.scheduleCourse([[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]), 3)
        self.assertEqual(solution.scheduleCourse([[1, 2]]), 1)
        self.assertEqual(solution.scheduleCourse([[3, 2], [4, 3]]), 0)

if __name__ == '__main__':
    unittest.main()