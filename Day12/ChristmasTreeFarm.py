import re

def ParseInput(filePath="Day12/input/input.txt"):
    layouts = []
    with open(filePath, 'r') as f:
        for line in f:
            testCaseMatch = re.match(r"^(\d+)x(\d+):\s*(.*)$", line)
            if testCaseMatch:
                width = int(testCaseMatch.group(1))
                height = int(testCaseMatch.group(2))
                values = list(map(int, testCaseMatch.group(3).split()))

                layouts.append({
                    "width": width,
                    "height": height,
                    "values": values,
                })
    return layouts

def SolveTask1(layouts):
    count = 0
    for layout in layouts:
        roomFor3by3Shapes = (layout["width"] - layout["width"]%3) * (layout["height"] - layout["height"]%3)
        if roomFor3by3Shapes >= 9 * sum(layout["values"]):
            count += 1

    print(count)

if __name__ == "__main__":
    layouts = ParseInput()
    SolveTask1(layouts)
    