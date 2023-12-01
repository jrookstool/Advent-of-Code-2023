wordsToNumbers = {'one': 1, 'two': 2, 'three': 3, 'four': 4, 'five': 5, 'six': 6, 'seven': 7, 'eight': 8, 'nine': 9}

def sumCalibrations(filename):
    file = open(filename, 'r')
    sum = 0
    currentLine = file.readline()
    while(currentLine != ''):
        sum += int(getCalibrationNumber(currentLine))
        currentLine = file.readline()
    return sum

def getCalibrationNumber(string):
    firstIndex = 0
    firstNum = string[firstIndex]
    secondIndex = len(string) - 2
    secondNum = string[secondIndex]

    # Find the first digit number and the first word number

    firstDigit = findDigit(string)
    firstWord = findFirstWordNumber(string)

    # Decide which came first

    if (firstDigit[1] < firstWord[1]):
        firstNum = firstDigit[0]
    
    # Find the second digit number and the second word number

    lastDigit = findDigit(string[::-1])
    lastWord = findLastWordNumber(string)

    # Decide which came last

    if (len(string) - lastDigit[1] > lastWord[1]):
        secondNum = lastDigit[0]
    
    
    # firstNum = setNumber(string, firstNum, firstIndex)

    # while (not isInt(secondNum) and parseWord(string, secondIndex)[0] not in wordsToNumbers):
    #     secondIndex -= 1
    #     secondNum = string[secondIndex]
    
    # secondNum = setNumber(string, secondNum, secondIndex)

    return firstNum + secondNum

def isInt(string):
    try:
        int(string)
        return True
    except ValueError:
        return False

def findDigit(string):
    startIndex = 0
    endIndex = 1
    for i in range(len(string)):
        if (isInt(string[i])):
            startIndex = i
            break
    while (isInt(string[startIndex:endIndex])):
        endIndex += 1
    return string[startIndex:endIndex-1], startIndex

def findFirstWordNumber(string):
    startIndex = 0
    if (isInt(string[0])):
        startIndex += 1
    endIndex = 0
    while (string[startIndex:endIndex] not in wordsToNumbers):
        if (isInt(string[endIndex])):
            startIndex = endIndex + 1
        print(string[startIndex:endIndex])
        endIndex += 1
    return string[startIndex:endIndex], startIndex

def findLastWordNumber(string):
    startIndex = -1
    for i in range(len(string) - 1, -1, -1):
        for j in range(i, len(string)):
            if (string[i:j] in wordsToNumbers):
                startIndex = i
                endIndex = j
                break
        if (startIndex != -1):
            break
    return string[startIndex:endIndex], startIndex

def parseWord(string, startIndex):
    endIndex = startIndex + 1
    while (string[startIndex:endIndex] not in wordsToNumbers and endIndex < len(string)):
        endIndex += 1
    if (string[startIndex:endIndex] not in wordsToNumbers):
        return '', endIndex
    return string[startIndex:endIndex], endIndex

def setNumber(string, number, index):
    if (isInt(number)):
        number = int(number)
    
    if (parseWord(string, index)[0] in wordsToNumbers):
        number = wordsToNumbers[parseWord(string, index)[0]]
    
    return number

def main():
    print(sumCalibrations('day1_input.txt'))

    # print(findDigit('9sixsevenz3'))
    # print(findFirstWordNumber('9sixsevenz3'))
    # print(findDigit('9sixsevenz3'[::-1]))
    # print(findLastWordNumber('9sixsevenz3'))

if __name__ == '__main__':
    main()