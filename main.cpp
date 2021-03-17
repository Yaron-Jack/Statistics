/******************************************************************************
THE Statistics GAME


 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

static constexpr int const &Success = 0;
static constexpr int const &ERROR = -1;
static constexpr int const &LOWER_BOUND = 1;
static constexpr int const &UPPER_BOUND = 11;

using namespace std;

/*** string multiplier operator***/
string operator*(string a, unsigned int b)
{
    string output = "";
    while (b--)
    {
        output += a;
    }
    return output;
}

void PrintTable(vector<vector<float> > &Board)
{
    for (int i = 0; i < Board.size(); ++i)
    {
        if (i == 0)
        {
            for (int j = 0; j < Board[i].size(); ++j)
            {
                if (j == 0)
                {
                    cout << "Min Border  " << "|";
                }
                if (j == 1)
                {
                    cout << "Max Border  " << "|";
                }
                if (j == 2)
                {
                    cout << "Group size  " << "|";
                }
                if (j == 3)
                {
                    cout << "f(x)frequen " << "|";
                }
                if (j == 4)
                {
                    cout << "middle*f(x) " << "|";
                }
                if (j == 5)
                {
                    cout << "h-density   " << "|";
                }
                if (j == 6)
                {
                    cout << "middle^2f(x)" << "|";
                }
                if (j == 7)
                {
                    cout << "F(x)normal " << "|";
                }
                if (j == 8)
                {
                    cout << "F(x)middle " << "|";
                }
            }
        }
    }
    string Divide = "-------------";
    cout << "\n" << (Divide * 9) << endl;

    for (int i = 0; i < Board.size(); ++i)
    {
        for (int j = 0; j < Board[i].size(); ++j)
        {
            cout << Board[i][j] << "         |";
        }
        cout << "Row" << i << endl;
        cout << (Divide * Board[i].size()) << endl;
    }
}


void SumFrequency(vector<vector<float> > &Board, float &Sum, float &MiddleFxSum,
                  float &FxSum, float &SquareMiddleFx, float &SumSizeFrequency)
{
    for (int j = 3; j < Board[0].size(); j++)
    {
        for (int i = 0; i < Board.size(); i++)
        {
            if (Board[i][j] == 0)
            {
                break;
            }
            else
            {
                Sum += Board[i][j];
            }
        }
        cout << "\t\nThe Sum of " << j << " column is: " << Sum << endl;
        if (j == 4)
        {
            MiddleFxSum = Sum;
        }
        if (j == 3)
        {
            FxSum = Sum;
        }
        if (j == 6)
        {
            SquareMiddleFx = Sum;
        }
        if (j == 7)
        {
            SumSizeFrequency = Sum;
        }
        Sum = 0;
    }
}

void
RepeatingInput(vector<vector<float> > &Board, float &Sum, float &MiddleFxSum,
               float &FxSum, float &SquareMiddleFx, float &SumSizeFrequency)
{
    float InputChoice = 0;

    for (int i = 0; i < Board.size(); ++i)
    {
        for (int j = 0; j < Board[i].size(); ++j)
        {
            if (j < 2 || j == 3)
            {
                cout << "\n\tPlease enter input for the following place\n\t" << i << " " << j << "\n"

                     << flush;

                if (cin >> InputChoice)
                {
                    Board[i][j] = InputChoice;

                    PrintTable(Board);

                    continue;

                }
            }
            else if (j == 2)
            {
                Board[i][j] = Board[i][1] - Board[i][0];
            }
            else if (j == 4)
            {
                Board[i][j] = ((Board[i][0] + Board[i][1]) / 2) * Board[i][3];
            }
            else if (j == 5)
            {
                Board[i][j] = Board[i][3] / Board[i][2];
            }
            else if (j == 6)
            {
                Board[i][j] = ((Board[i][0] + Board[i][1]) / 2) * ((Board[i][0] + Board[i][1]) / 2) * Board[i][3];
            }
            if (j == 7)
            {
                if (i == 0)
                {
                    Board[i][7] = Board[0][3];
                }
                if (i != 0)
                {
                    Board[i][7] += Board[i - 1][7] + Board[i][3];
                }
            }
            if (j == 8)
            {
                if (i == 0)
                {
                    Board[i][8] = Board[0][4];
                }
                if (i != 0)
                {
                    Board[i][8] += Board[i - 1][8] + Board[i][4];
                }
                cout << "\n\t*****Final Row********\n" << endl;
                PrintTable(Board);
            }

            if (i == Board.size() - 1 && j == Board[i].size() - 1)
            {
                SumFrequency(Board, Sum, MiddleFxSum,
                             FxSum, SquareMiddleFx, SumSizeFrequency);
            }
        }
    }
}

void PecentageToNumber(vector<vector<float> > &Board, float &UserPercentage, float &FxSum, float &Medium)
{
    cout << "\n\tfor what number would you like the percentage for please: \n" << flush;
    cin >> UserPercentage;

    for (int i = 0; i < Board.size(); ++i)
    {
        if (Board[i][1] >= UserPercentage && i != 0)
        {
            Medium =
                    (((((UserPercentage - Board[i][0]) / Board[i][2]) * Board[i][3]) + Board[i - 1][7])) *
                    (100 / FxSum);
            break;
        }
        if (Board[i][1] >= UserPercentage && i == 0)
        {
            Medium =
                    ((((UserPercentage - Board[i][0]) / Board[i][2]) * Board[i][7])) * (100 / FxSum);
            break;
        }
    }


    cout << "\t\n\nThe Number at the place " << UserPercentage << " is: " << Medium << "% \nHooray!! "
         << char(1)
         << endl;
}

void NumberToPrecentage(vector<vector<float> > &Board, float &UserPercentage, float &FxSum, float &Medium)
{
    cout << "\n\tTo What percentage would you like the number for please,in a decimal form: \n" << flush;
    cin >> UserPercentage;

    for (int i = 0; i < Board.size(); ++i)
    {
        if (Board[i][7] >= FxSum * UserPercentage && i != 0)
        {
            Medium = Board[i][0] +
                     (((((FxSum * UserPercentage) - Board[i - 1][7])) / Board[i][3]) * Board[i][2]);
            break;
        }
        if (Board[i][7] >= FxSum * UserPercentage && i == 0)
        {
            Medium = Board[i][0] + ((((FxSum * UserPercentage) / Board[i][3]) * Board[i][2]));
            break;
        }
    }


    cout << "\t\n\nThe Number at the place " << UserPercentage << " is: " << Medium << " \nHooray!! "
         << char(1)
         << endl;
}

void
Results(vector<vector<float> > &Board, float &MiddleFxSum, float &FxSum, float &SquareMiddleFx, int &UserInputTable,
        float &HighestFrequency)
{
    for (int i = 0; i < Board.size() - 1; i++)
    {
        if (Board[i][5] > HighestFrequency)
        {
            HighestFrequency = Board[i][5];
        }
        if (HighestFrequency == Board[i][5] && i == Board.size() - 2)
        {
            cout << "\n\tThe group with the highest Frequency,Its middle is: " << (Board[i][1] + Board[i][0]) / 2
                 << endl;
            break;
        }
    }
    cout << "\n\tThe Middle range is: " << (Board[0][0] + Board[UserInputTable - 1][1]) / 2 << endl;
    cout << "\n\tThe Average is: " << MiddleFxSum / FxSum << endl;
    cout << "\n\tThe Standard deviation is: "
         << sqrt(SquareMiddleFx / FxSum - ((MiddleFxSum / FxSum) * (MiddleFxSum / FxSum))) << " \n\n\tHooray!! "
         << char(1)
         << endl;
}


int main()
{
    cout << "\n\n\tStatistics \n\n";

    int UserInputTable = 0;
    float Sum = 0;
    float MiddleFxSum, FxSum = 0;
    float SquareMiddleFx = 0;
    float Medium = 0;
    float SumSizeFrequency = 0;
    float HighestFrequency = 0;

    cout << "\nplease enter the Board size (1 to 11): \n" << flush;


    if (cin >> UserInputTable && UserInputTable >= LOWER_BOUND && UserInputTable <= UPPER_BOUND)
    {
        cout << "\n\tHello and Welcome! Please input each number according to the request \n\t"
             << "\n\tMake sure the boarders are real - meaning Max and next Min are the same number! \n\t"
             << "\n\tGood luck!" << char(1) << "\n\t"
             << endl;

        ///create a vector of vectors for the board with input each time
        vector<vector<float>> Board(UserInputTable, vector<float>(9, 0));

        PrintTable(Board);

        RepeatingInput(Board, Sum, MiddleFxSum, FxSum, SquareMiddleFx, SumSizeFrequency);

        Results(Board, MiddleFxSum, FxSum, SquareMiddleFx, UserInputTable, HighestFrequency);

        char UserContinue = '0';
        do
        {
            float UserPercentage = 0;
            int UserChosenPercentage = 0;
            cout << "\nWould you like to give in \n1.a percentage \n\tor \n2.a number?\n" << flush;
            cin >> UserChosenPercentage;


            switch (UserChosenPercentage)
            {
                case 1:

                    NumberToPrecentage(Board, UserPercentage, FxSum, Medium);

                    break;

                case 2:

                    PecentageToNumber(Board, UserPercentage, FxSum, Medium);

                    break;
            }

            cout << "\n\tIf you would like to continue please press \'y\',otherwise press anything else\n"
                 << flush;

        } while (cin >> UserContinue && UserContinue == 'y');

        cout << "\n\tGOODBYE" << endl;

        return Success;

    }
    else
    {
        cout << "Bad Input" << endl;
        exit(ERROR);
    }
}

/**************
TODO add undo and linear transgression
 */