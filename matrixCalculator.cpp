#include <iostream>
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
string parseData(string line, int fieldNumber, int startingPos, char seperator);

int main()
{
    string line;
    while (1)
    {
        cout << ">>";
        getline(cin, line);
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

bool commandHandler(string line)
{
    char newline = '\n';
    if (isCommandPresent("print", line))
    {
        printMatrix(detectMatrix(line[6]), 3, 3);
    }
    else if (isCommandPresent("isIdentity", line))
    {
        cout << newline << isIdentityMatrix(detectMatrix(line[11]), 3, 3) << newline;
    }
    else if (isCommandPresent("isDiagonal", line))
    {
        cout << newline << isDiagonalMatrix(detectMatrix(line[11]), 3, 3) << newline;
    }
    else if (isCommandPresent("isSymmetric", line))
    {
        cout << newline << isSymmetricMatrix(detectMatrix(line[12]), 3, 3) << newline;
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
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << '\t' << matrix[j + (i)*rows];
        }
        cout << endl;
    }
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