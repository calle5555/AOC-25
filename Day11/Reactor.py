from functools import cache

def ParseInput(filePath="Day11/input/input.txt"):
    lines = {}
    with open(filePath, 'r') as f:
        for row in f:
            key, outputs = row.split(':')
            lines[key] = outputs.split()
    return lines

if __name__ == "__main__":
    data = ParseInput()

    @cache
    def SolvePart1(node):
        if node == "out": return 1

        children = data.get(node)
        if children is None: return 0

        return sum(SolvePart1(node) for node in children)
    
    print(SolvePart1("you"))

    @cache
    def SolvePart2(node, hasFoundFft, hasFoundDac):
        if node == "out": return 1 if hasFoundDac and hasFoundFft else 0

        if node == "fft": hasFoundFft = True
        if node == "dac": hasFoundDac = True

        children = data.get(node)
        if children is None: return 0

        return sum(SolvePart2(node, hasFoundFft, hasFoundDac) for node in children)
    
    print(SolvePart2("svr", False, False))
    