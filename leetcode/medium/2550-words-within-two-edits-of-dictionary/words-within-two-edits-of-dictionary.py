class Solution:
    def twoEditWords(self, queries, dictionary) :
        result = []
        for q in queries:
            for d in dictionary:
                diff = sum(a != b for a, b in zip(q, d))
                if diff <= 2:
                    result.append(q)
                    break
        return result