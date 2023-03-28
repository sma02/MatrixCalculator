#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

int A[3 * 3];
int B[3 * 3];
int C[3 * 3];

bool isCommandPresent(string toFind, string data);
void matrixAssignmentHandler(string line);
int *detectMatrix(char i);
void initalizeMatrix(int matrix[], int rows, int cols, string data);
void printMatrix(int matrix[], int rows, int cols);
bool isIdentityMatrix(int matrix[], int rows, int cols);
bool isDiagonalMatrix(int matrix[], int rows, int cols);
bool isSymmetricMatrix(int matrix[], int rows, int cols);
void transposeMatrix(int matrix[], int rows, int cols);
void addMatrices(int assignmentMatrix[], int matrix1[], int matrix2[], int rows, int cols);
void subtractMatrices(int assignmentMatrix[], int matrix1[], int matrix2[], int rows, int cols);
void multiplyMatrices(int assignmentMatrix[], int matrix1[], int matrix2[], int rows, int cols);
void scalerMultiplyMatrix(int assignmentMatrix[], int matrix[], int scalerFactor, int rows, int cols);
bool commandHandler(string line);
void takeLine(string &str);
void setColor(short color);
void printBooleanValue(bool val);
short getColor();
int getCursorX();
int getCursorY();
void gotoxy(int x, int y);
void handleCharacterColors(char character);
void handleCommandColors(string str);
void setConsoleCursor(bool visibility);
string parseData(string line, int fieldNumber, int startingPos, char seperator);

int main()
{
    string line;
    while (1)
    {
        setColor(0x8);
        cout << ">>";
        setColor(0x7);
        takeLine(line);
        matrixAssignmentHandler(line);
        commandHandler(line);
    }
}
void matrixAssignmentHandler(string line)
{
    if (line[1] == '=')
    {
        if (line[2] == '{')
        {
            initalizeMatrix(detectMatrix(line[0]), 3, 3, line);
        }
        else if (isdigit(line[2]))
        {
            string scalerFactor = parseData(line, 1, 2, '*');
            int targerMatrixStartingLocation = scalerFactor.length() + 3;
            scalerMultiplyMatrix(detectMatrix(line[0]), detectMatrix(line[targerMatrixStartingLocation]), stoi(scalerFactor), 3, 3);
        }
        else
        {
            if (line[3] == '+')
            {
                addMatrices(detectMatrix(line[0]), detectMatrix(line[2]), detectMatrix(line[4]), 3, 3);
            }
            else if (line[3] == '-')
            {
                subtractMatrices(detectMatrix(line[0]), detectMatrix(line[2]), detectMatrix(line[4]), 3, 3);
            }
            else if (line[3] == '*')
            {
                multiplyMatrices(detectMatrix(line[0]), detectMatrix(line[2]), detectMatrix(line[4]), 3, 3);
            }
        }
    }
}
void printBooleanValue(bool val)
{
    cout << endl;
    setColor(0x03);
    if (val)
    {
        cout << "true";
    }
    else
    {
        cout << "false";
    }
    cout << endl;
    setColor(0x7);
}
bool commandHandler(string line)
{
    if (isCommandPresent("print", line))
    {
        printMatrix(detectMatrix(line[6]), 3, 3);
    }
    else if (isCommandPresent("isIdentity", line))
    {
        printBooleanValue(isIdentityMatrix(detectMatrix(line[11]), 3, 3));
    }
    else if (isCommandPresent("isDiagonal", line))
    {
        printBooleanValue(isDiagonalMatrix(detectMatrix(line[11]), 3, 3));
    }
    else if (isCommandPresent("isSymmetric", line))
    {
        printBooleanValue(isSymmetricMatrix(detectMatrix(line[12]), 3, 3));
    }
    else if (isCommandPresent("transpose", line))
    {
        transposeMatrix(detectMatrix(line[10]), 3, 3);
    }
    else if (isCommandPresent("exit", line))
    {
        exit(0);
    }
    else
    {
        return false;
    }
    return true;
}
bool isCommandPresent(string toFind, string data)
{
    for (int i = data.length() - toFind.length(); i >= 0; i--)
    {
        for (int j = i; j < i + toFind.length(); j++)
        {
            if (data[j] != toFind[j - i])
            {
                break;
            }

            else if (data[j] == toFind[j - i] && j == i + toFind.length() - 1)
            {
                return true;
            }
        }
    }
    return false;
}

int *detectMatrix(char i)
{
    if (i == 'A')
    {
        return A;
    }
    else if (i == 'B')
    {
        return B;
    }
    else if (i == 'C')
    {
        return C;
    }
}
void initalizeMatrix(int matrix[], int rows, int cols, string data)
{
    for (int i = 0; i < rows * cols; i++)
    {
        matrix[i] = stoi(parseData(data, i + 1, 3, ','));
    }
}
void printMatrix(int matrix[], int rows, int cols)
{
    cout << endl;
    setColor(0x3);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << '\t' << matrix[j + (i)*rows];
        }
        cout << endl;
    }
    setColor(0x7);
}
bool isIdentityMatrix(int matrix[], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == j && matrix[j + (i)*rows] != 1)
            {
                return false;
            }
            else if (i != j && matrix[j + (i)*rows] != 0)
            {
                return false;
            }
        }
    }
    return true;
}
bool isDiagonalMatrix(int matrix[], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i != j && matrix[j + (i)*rows] != 0)
            {
                return false;
            }
        }
    }
    return true;
}
bool isSymmetricMatrix(int matrix[], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[j + (i)*rows] != matrix[i + (j)*rows])
            {
                return false;
            }
        }
    }
    return true;
}
void transposeMatrix(int matrix[], int rows, int cols)
{
    int tempMatrix[rows * cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            tempMatrix[j + (i)*rows] = matrix[j + (i)*rows];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[j + (i)*rows] = tempMatrix[i + (j)*rows];
        }
    }
}
void addMatrices(int assignmentMatrix[], int matrix1[], int matrix2[], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            assignmentMatrix[j + (i)*rows] = matrix1[j + (i)*rows] + matrix2[j + (i)*rows];
        }
    }
}
void subtractMatrices(int assignmentMatrix[], int matrix1[], int matrix2[], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            assignmentMatrix[j + (i)*rows] = matrix1[j + (i)*rows] - matrix2[j + (i)*rows];
        }
    }
}
void multiplyMatrices(int assignmentMatrix[], int matrix1[], int matrix2[], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            assignmentMatrix[j + (i)*rows] = matrix1[(i)*rows] * matrix2[j];
            assignmentMatrix[j + (i)*rows] += matrix1[1 + (i)*rows] * matrix2[j + (1) * rows];
            assignmentMatrix[j + (i)*rows] += matrix1[2 + (i)*rows] * matrix2[j + (2) * rows];
        }
    }
}
void scalerMultiplyMatrix(int assignmentMatrix[], int matrix[], int scalerFactor, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            assignmentMatrix[j + (i)*rows] = scalerFactor * matrix[j + (i)*rows];
        }
    }
}
string parseData(string line, int fieldNumber, int startingPos, char seperator)
{
    int initialPos = startingPos;
    int finalPos = 0;
    int fieldCount = 0;
    string result = "";
    for (int i = startingPos; i < line.length(); i++)
    {
        if (line[i] == seperator)
        {
            fieldCount++;
            if (fieldNumber != fieldCount)
            {
                initialPos = i + 1;
            }
            else
            {
                finalPos = i;
            }
        }
        else if (i == line.length() - 1)
        {
            fieldCount++;
            finalPos = i + 1;
        }
        if (fieldNumber == fieldCount)
        {
            for (int j = initialPos; j < finalPos; j++)
            {
                result += line[j];
            }
            return result;
        }
    }
}
void takeLine(string &str)
{
    str = "";
    char c = 0;
    while (1)
    {
        if (kbhit())
        {
            c = getch();
            if (c == '\b')
            {
                if (str.length())
                {
                    cout << '\b';
                    cout << ' ';
                    cout << '\b';
                    str.erase(str.size() - 1);
                    handleCommandColors(str);
                }
            }
            else if (c == -32)
            {
                while (kbhit())
                {
                    getch();
                }
            }
            else if (c == VK_RETURN)
            {
                while (kbhit())
                {
                    getch();
                }
                handleCharacterColors(c);
                cout << endl;
                break;
            }
            else
            {
                str += c;
                handleCharacterColors(c);
                cout << c;
                handleCommandColors(str);
            }
        }
    }
}
void handleCommandColors(string str)
{
    string temp = str.substr(0, str.find('('));
    if (temp == "print" || temp == "isIdentity" || temp == "isDiagonal" || temp == "isSymmetric" || temp == "transpose" || temp == "exit")
    {
        setColor(0x6);
        gotoxy(2, getCursorY());
        cout << temp;
        gotoxy(2 + str.length(), getCursorY());
        setColor(0x7);
    }
    else if (temp == "prin" || temp == "isIdentit" || temp == "isDiagona" || temp == "isSymmetri" || temp == "transpos" || temp == "exi")
    {
        setColor(0x7);
        gotoxy(2, getCursorY());
        cout << temp;
    }
}
void handleCharacterColors(char character)
{
    if (character >= 'A' && character <= 'C')
    {
        setColor(0x3);
    }
    else if (character == '=')
    {
        setColor(0xD);
    }
    else if (character == '{' || character == '}')
    {
        setColor(0x6);
    }
    else if (character == '(' || character == ')')
    {
        setColor(0xA);
    }
    else if (character == ',')
    {
        setColor(0x2);
    }
    else
    {
        setColor(0x7);
    }
}
int getCursorX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}
int getCursorY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void setConsoleCursor(bool visibility)
{
    CONSOLE_CURSOR_INFO ci;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = visibility;
    SetConsoleCursorInfo(stdHandle, &ci);
}
void setColor(short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
short getColor()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.wAttributes;
}