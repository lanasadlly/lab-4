#include <iostream>
#include <fstream>
#include <conio.h>
#define N (1000)

using namespace std;

void printMenu ()
{
    cout << "1) Enter 1 - 50 words from a keyboard or from a file" << endl;
    cout << "   each of which contains 1 - 10 lower latin letters and digits." << endl;
    cout << "   Any number of gaps can be between each 2 words." << endl;
    cout << "   a dot must finish the sequence" << endl;
    cout << "2) Edit the text:" << endl;
    cout << "   * Delete extra gaps" << endl;
    cout << "   * Delete extra punctuation marks" << endl;
    cout << "   * Correct the register of letters" << endl;
    cout << "3) Print all words containing only letters," << endl;
    cout << "   then all words containing only digits," << endl;
    cout << "   then all words containing both letters and digits" << endl;
    cout << "4) Print all words upright" << endl;
    cout << "5) Find all entered sublines in the whole text" << endl;
    cout << "6) Finish" << endl;
}

int len (char *text)
{
    int l = 0;
    while (text [l])
        l++;
    return l;
}

void  readFile (char *text)
{
    ifstream File;
    File.open ("textfile.txt");
    if (!(File.is_open ()))
    {
        cout << "File hasn't opened!!!" << endl;
    }
    File.getline (text, 1000);
    File.close ();
    cout << text << endl;
}

bool punctIsExtra (char *text, int &i, int step)
{
    char puncSet [] = ",.!?@%#$%^&*()-_=+[]{};:\'\"<>`~/|\\";
    int lenPuncSet = len (puncSet);
    bool flagCurr = 0;
    bool flagNext = 0;

    if (text [i] == '.' && text [i + 1] == '.' && text [i + 2] == '.' && text [i + 3] != '.' && i + 3 < lenPuncSet)
    {
        i += 3;
        int key = i + 1;
        for (int j = len(text) + 1; j > i ; j --)
            text [j] = text [j - 1];
        text [key] = ' ';
    }

    for (int j = 0; j < lenPuncSet; j ++)
    {
        if (text [i] == puncSet [j])
            flagCurr = 1;
        if (text [i + step] == puncSet [j])
            flagNext = 1;
    }
    if (flagCurr == 1 && flagNext == 1)
        return 1;
    else
        return 0;
}

void deleteExtraGaps (char *text)
{
    int length = len (text);
    for (int i = 0; i < length - 1; i++)
    {
        int numberMoves = 0;
        int step = 1;
        while (text [i] == text [i + step] && text [i] == ' ')
        {
            numberMoves++;
            step++;
        }
        for (int j = i + 1; j <= length - numberMoves; j ++)
            text [j] = text [j + numberMoves];
        length -= numberMoves;
    }
}

void deleteExtraPunctuation (char *text)
{
    int length = len (text);
    for (int i = 0; i < length - 1; i++)
    {
        int numberMoves = 0;
        int step = 1;
        while (punctIsExtra (text, i, step))
        {
            numberMoves++;
            step++;
        }
        for (int j = i + 1; j <= length - numberMoves; j ++)
            text [j] = text [j + numberMoves];
        length -= numberMoves;
    }
}

void removeGapsBefore (char *text)
{
    int length = len (text);
    int countQuotes = text [0] == '\'' ? 1 : 0;
    int countDoubleQuotes = text [0] == '\"' ? 1 : 0;

    for (int i = 1; i < length; i++)
    {
        int numberMoves = 0;
        int step = 1;
        if (text [i] == '\'')
            countQuotes++;
        if (text [i] == '\"')
            countDoubleQuotes++;
        while ((text [i] == ',' || text [i] == ':' || text [i] == ';' ||
                text [i] == '!' || text [i] == ']' || text [i] == '?' ||
                text [i] == ')' || text [i] == '}' ||
               (text [i] == '\'' && countQuotes % 2 == 0) ||
               (text [i] == '\"' && countDoubleQuotes % 2 == 0))
                && text [i - step] == ' ')
        {
            numberMoves++;
            step++;
        }
        for (int j = i - step + 1; j <= length - numberMoves; j ++)
            text [j] = text [j + numberMoves];
        length -= numberMoves;
    }
}

void removeGapsAfter (char *text)
{
    int length = len (text);
    int countQuotes = 0;
    int countDoubleQuotes = 0;

    for (int i = 0; i < length - 1; i++)
    {
        int numberMoves = 0;
        int step = 1;
        if (text [i] == '\'')
            countQuotes++;
        if (text [i] == '\"')
            countDoubleQuotes++;
        while ((text [i] == '(' || text [i] == '[' || text [i] == '{' ||
               (text [i] == '\'' && countQuotes % 2 == 1) ||
               (text [i] == '\"' && countDoubleQuotes % 2 == 1))
                && text [i + step] == ' ')
        {
            numberMoves++;
            step++;
        }
        for (int j = i + 1; j <= length - numberMoves; j ++)
            text [j] = text [j + numberMoves];
        length -= numberMoves;
    }
}

void addGapsBefore (char *text)
{
    int length = len (text);
    int countQuotes = text [0] == '\'' ? 1 : 0;
    int countDoubleQuotes = text [0] == '\"' ? 1 : 0;

    for (int i = 1; i < length; i++)
    {
        if (text [i] == '\'')
            countQuotes++;
        if (text [i] == '\"')
            countDoubleQuotes++;
        if ((text [i] == '(' || text [i] == '[' || text [i] == '{' || text [i] == '-' ||
            (text [i] == '\'' && countQuotes % 2 == 1) ||
            (text [i] == '\"' && countDoubleQuotes % 2 == 1))
            && text [i - 1] != ' ')
        {
            int key = i;
            for (int j = length + 1; j > i; j--)
                text [j] = text [j - 1];
            text [key] = ' ';
            length++;
        }
    }
}

void addGapsAfter (char *text)
{
    int length = len (text);
    int countQuotes = 0;
    int countDoubleQuotes = 0;

    for (int i = 0; i < length - 1; i++)
    {
        if (text [i] == '\'')
            countQuotes++;
        if (text [i] == '\"')
            countDoubleQuotes++;
        if ((text [i] == ',' || text [i] == ':' || text [i] == ';' ||
             text [i] == '!' || text [i] == ']' || text [i] == '?' ||
             text [i] == ')' || text [i] == '}' || text [i] == '-' ||
            (text [i] == '\'' && countQuotes % 2 == 0) ||
            (text [i] == '\"' && countDoubleQuotes % 2 == 0))
            && text [i + 1] != ' ')
        {
            int key = i + 1;
            for (int j = length + 2; j > i + 1; j--)
                text [j] = text [j - 1];
            text [key] = ' ';
            length++;
        }
    }
}

void normalizeGaps (char *text)
{
    removeGapsBefore (text);
    removeGapsAfter (text);
    addGapsBefore (text);
    addGapsAfter (text);
}

bool isUpLetter (char letter)
{
    if ((int (letter)) > 64 && (int (letter)) < 91)
        return 1;
    return 0;
}

bool isLowLetter (char letter)
{
    if ((int (letter)) > 96 && (int (letter)) < 123)
        return 1;
    return 0;
}

bool isDigit (char letter)
{
    if ((int (letter)) > 47 && (int (letter)) < 58)
        return 1;
    return 0;
}

void correctRegister (char *text)
{
    bool setBefore;

    for (int i = 0; i < len (text); i++)
    {
        setBefore = 0;
        if (text [i - 2] == '.' || text [i - 2] == '!' || text [i - 2] == '?')
            setBefore = 1;

        if ((i == 0 || setBefore == 1) && (isLowLetter (text [i])))
        {
            int ch = int (text [i]);
            ch = ch - 32;
            text [i] = char (ch);
        }

        if ((i == 1 || setBefore == 0) && (isUpLetter (text [i])) && (i != 0))
        {
            int ch = int (text [i]);
            ch = ch + 32;
            text [i] = char (ch);
        }
    }
}

void printWordsLetters (char *text)
{
    for (int i = 0; i < len (text); )
        {
            int length = 0;
            bool isSuitable = 0;
            while (isUpLetter (text [i + length]) || isLowLetter (text [i + length]))
                length++;
            if (i == 0)
            {
                if (!(isDigit (text [i + length])))
                    isSuitable = 1;
            }
            else if (i + length == len (text))
            {
                if (!(isDigit (text [i - 1])))
                    isSuitable = 1;
            }
            else
            {
                if (!(isDigit (text [i - 1]) || isDigit (text [i + length])))
                    isSuitable = 1;
            }
            if (isSuitable == 1)
                for (int j = i; j < i + length; j++)
                    cout << text [j];
            if (length > 0)
            {
                i = i + length;
                if (isSuitable)
                    cout << "  ";
            }
            else
                i++;
        }
}

void printWordsDigits (char *text)
{
    for (int i = 0; i < len (text); )
        {
            int length = 0;
            bool isSuitable = 0;
            while (isDigit (text [i + length]))
                length++;
            if (i == 0)
            {
                if (!(isUpLetter (text [i + length]) || isLowLetter (text [i + length])))
                    isSuitable = 1;
            }
            else if (i + length == len (text))
            {
                if (!(isUpLetter (text [i - 1]) || isLowLetter (text [i - 1])))
                    isSuitable = 1;
            }
            else
            {
                if (!(isUpLetter (text [i - 1]) || isLowLetter (text [i + length]) ||
                      isUpLetter (text [i - 1]) || isLowLetter (text [i + length])))
                    isSuitable = 1;
            }
            if (isSuitable == 1)
                for (int j = i; j < i + length; j++)
                    cout << text [j];
            if (length > 0)
            {
                i = i + length;
                if (isSuitable)
                    cout << "  ";
            }
            else
                i++;
        }
}

void printWordsLettersDigits (char *text)
{
    for (int i = 0; i < len (text); )
        {
            bool containLetter = 0;
            bool containDigit = 0;
            int length = 0;
            while (isUpLetter (text [i + length]) || isLowLetter (text [i + length]) || isDigit (text [i + length]))
            {
                if (isUpLetter (text [i + length]) || isLowLetter (text [i + length]))
                    containLetter = 1;
                if (isDigit (text [i + length]))
                    containDigit = 1;
                length++;
            }
            if (containLetter == 1 && containDigit == 1)
            {
                for (int j = i; j < i + length; j++)
                cout << text [j];
            }
            if (length > 0)
            {
                i = i + length;
                if (containLetter == 1 && containDigit == 1)
                    cout << "  ";
            }
            else
                i++;
        }
}

void doLinearSearch (char *text, char *subline, int *indexes, int &numberOfIndexes)
{
    int lenText = len (text);
    int lenSub = len (subline);
    for (int i = 0; i < lenText; i++)
    {
        int numberOverlap = 0;
        for (int j = 0; j < lenSub; j++)
        {
            if (text [i + j] == subline [j])
                numberOverlap++;
        }
        if (numberOverlap == lenSub)
        {
            indexes [numberOfIndexes] = i;
            numberOfIndexes++;
        }
    }
}

void makeArrOfPrefixes(char *subline, int *arrOfPrefixes)
{
    int lenSub = len (subline);
    int lenCurr = 0;
    int i = 1;
    while (i < lenSub)
    {
        if (subline [i] == subline [lenCurr])
        {
            lenCurr++;
            arrOfPrefixes [i] = lenCurr;
            i++;
        }
        else
        {
            if (lenCurr == 0)
            {
                arrOfPrefixes [i] = 0;
                i++;
            }
            else
                lenCurr = arrOfPrefixes [lenCurr - 1];
        }
    }
}

void doKnuthMorrisPrattAlg (char *text, char *subline, int *indexes, int &numberOfIndexes)
{
    int arrOfPrefixes [1000];
    makeArrOfPrefixes (subline, arrOfPrefixes);
    int lenText = len (text);
    int lenSub = len (subline);
    int i = 0;
    int j = 0;

    while (i < lenText)
    {
        if (text [i] == subline [j])
        {
            i++;
            j++;
        }
        if (j == lenSub)
        {
            indexes [numberOfIndexes] = (i - j);
            numberOfIndexes++;
            j = arrOfPrefixes [j - 1];
        }
        else if (i < lenText && text [i] != subline [j])
        {
            if (j == 0)
                i++;
            else
                j = arrOfPrefixes [j - 1];
        }
    }
}

void doPoint1 (char *text)
{
    int choose;
    bool chooseDone = 0;

    while (!(choose == 1 || choose == 2))
    {
        if (chooseDone)
            cout << "Wrong input!" << endl << endl;
        cout << "How do you want to enter the words?" << endl;
        cout << "1) From a keyboard" << endl;
        cout << "2) From a file" << endl;
        choose = getch () - 48;
        chooseDone = 1;
        cout << endl;
    }

    switch (choose)
    {
        case 1:
            cin.getline (text, N);
            break;
        case 2:
            readFile (text);
            break;
    }

    cout << endl;
    cout << "Press any button to continue..." << endl << endl;
    getch ();
}

void doPoint2 (char *text)
{
    deleteExtraGaps (text);
    deleteExtraPunctuation (text);
    normalizeGaps (text);
    correctRegister (text);

    cout << "Corrected Text:" << endl << endl;
    cout << text << endl;

    cout << endl;
    cout << "Press any button to continue..." << endl << endl;
    getch ();
}

void doPoint3 (char *text)
{
    cout << "Words containing only letters:" << endl << endl;
    printWordsLetters (text);
    cout << endl << endl;

    cout << "Words containing only digits:" << endl << endl;
    printWordsDigits (text);
    cout << endl << endl;

    cout << "Words containing both letters and digits:" << endl << endl;
    printWordsLettersDigits (text);
    cout << endl;

    cout << endl;
    cout << "Press any button to continue..." << endl << endl;
    getch ();
}

void doPoint4 (char *text)
{
    for (int i = 0; i < len(text); )
    {
        int length = 0;
        while (isUpLetter (text [i + length]) || isLowLetter (text [i + length]) || isDigit (text [i + length]))
            length++;
        for (int j = i; j < i + length; j++)
            cout << text [j];
        if (length > 0)
        {
            i += length;
            cout << endl;
        }
        else
            i++;
    }

    cout << endl;
    cout << "Press any button to continue..." << endl << endl;
    getch ();
}

void doPoint5 (char *text)
{
    int choose;
    bool chooseDone = 0;

    while (!(choose == 1 || choose == 2))
    {
        if (chooseDone)
            cout << "Wrong input!" << endl << endl;
        cout << "Which way do you want to find the sublines?" << endl;
        cout << "1) Linear search" << endl;
        cout << "2) Knuth-Morris-Pratt algorithm" << endl;
        choose = getch () - 48;
        chooseDone = 1;
        cout << endl;
    }

    char subline [1000];
    cout << "Enter a subline that you want to find in the text" << endl << endl;
    cin.getline (subline, 1000);
    cout << endl;

    int listOfIndexes [1000];
    int numberOfIndexes = 0;

    switch (choose)
    {
        case 1:
            doLinearSearch (text, subline, listOfIndexes, numberOfIndexes);
            break;
        case 2:
            doKnuthMorrisPrattAlg (text, subline, listOfIndexes, numberOfIndexes);
            break;
    }

    cout << endl;
    if (numberOfIndexes == 0)
        cout << "Subline was not found in the text" << endl;
    else
        cout << "Subline found in the text with first indexes:  ";
    for (int i = 0; i < numberOfIndexes; i++)
        cout << listOfIndexes [i] << "  ";

    cout << endl;
    cout << "Press any button to continue..." << endl << endl;
    getch ();
}

int main()
{
    char text [N];
    int choose;
    bool textEntered = 0;
    bool textEdited = 0;
    while (true)
    {
        printMenu ();
        choose = getch () - 48;
        cout << endl;
        switch (choose)
        {
            case 1:
                doPoint1 (text);
                textEntered = 1;
                break;
            case 2:
                if (textEntered)
                {
                    doPoint2 (text);
                    textEdited = 1;
                }
                else
                    cout << "You need to enter a text first!!! (point 1)" << endl << endl;
                break;
            case 3:
                if (textEntered && textEdited)
                    doPoint3 (text);
                else if (textEntered)
                    cout << "You need to edit the text first!!! (point 2)" << endl << endl;
                else
                    cout << "You need to enter a text first!!! (point 1)" << endl << endl;
                break;
            case 4:
                if (textEntered && textEdited)
                    doPoint4 (text);
                else if (textEntered)
                    cout << "You need to edit the text first!!! (point 2)" << endl << endl;
                else
                    cout << "You need to enter a text first!!! (point 1)" << endl << endl;
                break;
            case 5:
                if (textEntered && textEdited)
                    doPoint5 (text);
                else if (textEntered)
                    cout << "You need to edit the text first!!! (point 2)" << endl << endl;
                else
                    cout << "You need to enter a text first!!! (point 1)" << endl << endl;
                break;
            case 6:
                exit (0);
            default:
                cout << "Wrong input!" << endl << endl;
                break;
        }
    }
    return 0;
}
