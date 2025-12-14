import pulp

def ParseInput(file_path="input/input.txt"):
    machines = []
    with open(file_path, 'r') as f:
        for line in f:
            tokens = line.split()
            buttons = []
            goalStateJoltages = []

            for token in tokens:
                if token.startswith('('):
                    buttons.append([int(x) for x in token[1:-1].split(',')])
                elif token.startswith('{'):
                    goalStateJoltages = [int(x) for x in token[1:-1].split(',')]

            machines.append({
                'buttons': buttons, 
                'goalStateJoltages': goalStateJoltages
            })
    return machines


def SolveMachine(machine):
    buttons = machine['buttons']
    goalStateJoltages = machine['goalStateJoltages']
    n = len(goalStateJoltages)
    m = len(buttons)

    prob = pulp.LpProblem("Min_Button_Presses", pulp.LpMinimize)

    x = [pulp.LpVariable(f"x{i}", lowBound=0, cat="Integer") for i in range(m)]

    for var in x:
        var.upBound = max(goalStateJoltages)

    prob += pulp.lpSum(x)

    for i in range(n):
        prob += pulp.lpSum(x[j] for j in range(m) if i in buttons[j]) == goalStateJoltages[i]

    prob.solve(pulp.PULP_CBC_CMD(msg=False))

    return int(pulp.value(prob.objective))

if __name__ == "__main__":
    result = 0
    for machine in ParseInput():
        result += SolveMachine(machine)

    print(result)