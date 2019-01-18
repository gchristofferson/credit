// This program checks to ensure that the credit card number entered is valid

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // promt user for credit card
    // validate that we have a positive integer between 13 and 16 digits
    long long ccNum;
    // if user gives a negative number, prompt again
    do
    {
        ccNum = get_long_long("Enter Credit Card Number: ");
    }
    while (ccNum < 0);
    // reset value of ccNum
    long long copyCCNum = ccNum;
    int count = 0;
    // count the number of digits in the integer provided by user
    if (ccNum > 0)
    {
        while (ccNum)
        {
            ccNum = ccNum / 10;
            count++;
        }
    }
    // if user provides a number less than thirteen or more than 16, print "INVALID"
    if (count < 13 || count > 16)
    {
        printf("INVALID\n");
        return 0;
    }
    // reset value of ccNum
    ccNum = copyCCNum;
    // access company identifier (2 digits) at the beginning of card number
    long divNum;
    switch (count)
    {
        case 13:
            divNum = 100000000000;
            break;
        case 14:
            divNum = 1000000000000;
            break;
        case 15:
            divNum = 10000000000000;
            break;
        case 16:
            divNum = 100000000000000;
            break;
    }
    int identifier = ccNum / divNum;
    // validate the identifier and assign company to the number if valid
    string company = " ";
    switch (identifier)
    {
        case 34:
        case 37:
            company = "AMEX";
            break;
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            company = "VISA";
            break;
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            company = "MASTERCARD";
            break;
    }
    // If no valid identifier is found, print "INVALID"
    int result;
    result = strncmp(company, " ", 3);
    if (result == 0)
    {
        printf("INVALID\n");
        return 0;
    }
    // check the string value of the company variable
    int amex = strncmp(company, "AMEX", 3);
    int visa = strncmp(company, "VISA", 3);
    int mastercard = strncmp(company, "MASTERCARD", 3);
    // if company is not AMEX, VISA, or MASTERCARD, print "INVALID"
    if (amex != 0 && visa != 0 && mastercard != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    // if company is AMEX, VISA or MASTERCARD, but number doesn't have required number of digits, print "INVALID"
    if (amex == 0 && count != 15)
    {
        printf("INVALID\n");
        return 0;
    }
    if (visa == 0 && count < 13)
    {
        printf("INVALID\n");
        return 0;
    }
    if (visa == 0 && count > 16)
    {
        printf("INVALID\n");
        return 0;
    }
    if (mastercard == 0 && count != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    // for valid company and number, start with second-to-last digit & multiply every other digit by 2 & then sum those digits
    int product = 0;
    int splitA = 0;
    int splitB = 0;
    int sum = 0;
    int secondLastNum = 0;
    while (ccNum)
    {
        ccNum /= 10;
        secondLastNum = ccNum % 10;
        product = secondLastNum * 2;
        splitA = product % 10;
        splitB = product / 10;
        sum += (splitA + splitB);
        ccNum /= 10;
    }
    ccNum = copyCCNum;
    // add sum to remaining digits
    int lastNum = 0;
    while (ccNum)
    {
        lastNum = ccNum % 10;
        ccNum /= 100;
        sum += lastNum;
    }
    // validate checksum
    int lastNumDigit = sum % 10;
    if (amex == 0 && lastNumDigit == 0)
    {
        printf("AMEX\n");
        return 0;
    }
    else if (visa == 0 && lastNumDigit == 0)
    {
        printf("VISA\n");
        return 0;
    }
    else if (mastercard == 0 && lastNumDigit == 0)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}