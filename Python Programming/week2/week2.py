studentScore = {'Alice': 99, "Bob": 97, "Carol": 96, "Dave": 100}


def sortNameSequence(studentScore):
    for name, score in sorted(studentScore.items()):
        print("%s,%s" % (name, score))


def sortNameInverse(studentScore):
    for name, score in sorted(studentScore.items(), reverse=True):
        print("%s,%s" % (name, score))


def sortScoreSequence(studentScore):
    studentScore2 = {(score, name): score for name, score in studentScore.items()}
    for (score, name), score in sorted(studentScore2.items()):
        print("%s,%s" % (name, score))


def sortScoreInverse(studentScore):
    studentScore2 = {(score, name): score for name, score in studentScore.items()}
    for (score, name), score in sorted(studentScore2.items(), reverse=True):
        print("%s,%s" % (name, score))


operationInformation = """
1. Sort by name in lexicographical order.
2. Sort by name in reverse lexicographical order.
3. Sort by score from small to large.
4. Sort by score from large to small.
q. Quit the program.
"""

while True:
    opt = input(operationInformation)
    if opt == "1":
        sortNameSequence(studentScore)
    elif opt == "2":
        sortNameInverse(studentScore)
    elif opt == "3":
        sortScoreSequence(studentScore)
    elif opt == "4":
        sortScoreInverse(studentScore)
    elif opt.lower() == "q":
        print("Sayonara")
        break
    else:
        print("Invalid command")
