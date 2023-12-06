wordsToNumbers = {'one': '1', 'two': '2', 'three': '3', 'four': '4', 'five': '5', 'six': '6', 'seven': '7', 'eight': '8', 'nine': '9'}

def sumCalibrations(filename):
    file = open(filename, 'r')
    sum = 0
    currentLine = file.readline()
    while(currentLine != ''):
        sum += int(getCalibrationNumber(currentLine))
        print(currentLine[:len(currentLine) - 1] + ' = ' + getCalibrationNumber(currentLine) + ' (sum = ' + str(sum) + ')')
        currentLine = file.readline()
    return sum

def getCalibrationNumber(string):
    firstIndex = 0
    firstNum = string[firstIndex]
    secondIndex = len(string) - 2
    secondNum = string[secondIndex]

    # Find the numbers using helper function that uses regex

    digitInstances = findDigits(string)
    wordInstances = findWords(string)

    if (digitInstances == None and wordInstances == None):
        return 0
    elif (digitInstances == None):
        firstWord = wordInstances[0][1]
        lastWord = wordInstances[1][1]
        firstNum = wordsToNumbers[firstWord]
        secondNum = wordsToNumbers[lastWord]
    elif (wordInstances == None):
        firstNum = digitInstances[0][1]
        secondNum = digitInstances[1][1]
    else:
        firstDigitInfo = digitInstances[0]
        lastDigitInfo = digitInstances[-1]
        firstWordInfo = wordInstances[0]
        lastWordInfo = wordInstances[-1]

        if (firstDigitInfo[0] < firstWordInfo[0]):
            firstNum = firstDigitInfo[1]
        else:
            firstNum = wordsToNumbers[firstWordInfo[1]]
        
        if (lastDigitInfo[0] > lastWordInfo[0]):
            secondNum = lastDigitInfo[1]
        else:
            secondNum = wordsToNumbers[lastWordInfo[1]]
    
    return firstNum + secondNum

def findDigits(string):
    firstIndex = 0
    firstNum = ''
    secondIndex = len(string) - 1
    secondNum = ''

    for i in range(len(string)):
        if (string[i].isdigit()):
            firstIndex = i
            firstNum = string[firstIndex]
            break
    
    for i in range(len(string) - 1, -1, -1):
        if (string[i].isdigit()):
            secondIndex = i
            secondNum = string[secondIndex]
            break

    if (firstNum == '' and secondNum == ''):
        return None
    
    return (firstIndex, firstNum), (secondIndex, secondNum)

def findWords(string):
    # Let's do this by iterating through the string:
    firstIndex = 0
    firstWord = ''
    lastIndex = len(string) - 1
    lastWord = ''


    finished = False
    for i in range(len(string)):
        if (not finished):
            for j in range(i + 1, len(string) + 1):
                if string[i:j] in wordsToNumbers:
                    firstIndex = i
                    firstWord = string[i:j]
                    finished = True
                    break
        else:
            break

    finished = False
    
    for i in range(len(string), 0, -1):
        if (not finished):
            for j in range(i - 1, -1, -1):
                if string[j:i] in wordsToNumbers:
                    lastIndex = j
                    lastWord = string[j:i]
                    finished = True
                    break
        else:
            break
    
    if (firstWord == '' and lastWord == ''):
        return None

    return (firstIndex, firstWord), (lastIndex, lastWord)

def main():
    print(sumCalibrations('day1_input.txt'))
if __name__ == '__main__':
    main()