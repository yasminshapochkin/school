class Solution:
    def scheduleCourse(self, courses: list[list[int]]) -> int:
        courses.sort(key=lambda x: x[1])
        n = len(courses)

        def dfs(i, time):
            if i == n:
                return 0

            duration, deadline = courses[i]

            # Skip course[i]
            best = dfs(i + 1, time)

            # Take course[i]
            if time + duration <= deadline:
                best = max(best, 1 + dfs(i + 1, time + duration))

            return best

        return dfs(0, 0)