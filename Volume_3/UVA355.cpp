/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

#include <cstdio>
#include <cctype>
#include <cstring>

const int MAX_LEN = 100;

int getDigitValue(char digit) {
    int digitValue = digit - '0';
    if (!isdigit(digit)) {
        digitValue = digit - 'A' + 10;
    }
    return digitValue;
}

char getDigitChar(int digitVal) {
    if (digitVal < 10) {
        return (char) ('0' + digitVal);
    }
    return (char) ('A' + digitVal - 10);
}

bool isValid(const char * inputNum, int fromBase) {
    for (int i = 0; inputNum[i] != '\0'; i++) {
        char digit = inputNum[i];

        if (!((digit >= '0' && digit <= '9') || (digit >= 'A' || digit <= 'F'))) {
            return false;
        }
        int digitValue = getDigitValue(digit);
        if (digitValue >= fromBase) {
            return false;
        }
    }
    return true;
}

long long getDecimalVal(const char * inputNum, int fromBase) {
    long long decimalVal = 0;
    for (int i = 0; inputNum[i] != '\0'; ++i) {
        decimalVal = decimalVal * fromBase + getDigitValue(inputNum[i]);
    }
    return decimalVal;
}

void convertFromDecimal(long long decimalVal, char * outputNum, int toBase) {
    if (decimalVal == 0) {
        outputNum[0] = '0';
        outputNum[1] = '\0';
        return;
    }

    int len = 0;
    while (decimalVal) {
        int remainder = decimalVal % toBase;
        decimalVal /= toBase;
        outputNum[len++] = getDigitChar(remainder);
    }
    outputNum[len] = '\0';

    // Reverse the output string
    int left = 0;
    int right = len - 1;
    while (left <= right) {
        char temp = outputNum[left];
        outputNum[left] = outputNum[right];
        outputNum[right] = temp;
        left++;
        right--;
    }
}

void convertBase(const char * inputNum, int fromBase, char * outputNum, int toBase) {
    if (fromBase == toBase) {
        strcpy(outputNum, inputNum);
        return;
    }

    long long decimalVal = getDecimalVal(inputNum, fromBase);

    if (toBase == 10) {
        sprintf(outputNum, "%lld", decimalVal);
        return;
    }

    convertFromDecimal(decimalVal, outputNum, toBase);
}

int main(void) {
    int fromBase, toBase;
    char inputNum[MAX_LEN + 1], outputNum[MAX_LEN + 1];

    while (scanf("%d %d %s", &fromBase, &toBase, inputNum) > 0) {
        if (!isValid(inputNum, fromBase)) {
            printf("%s is an illegal base %d number\n", inputNum, fromBase);
            continue;
        }

        convertBase(inputNum, fromBase, outputNum, toBase);
        printf("%s base %d = %s base %d\n", inputNum, fromBase, outputNum, toBase);
    }

    return 0;
}
