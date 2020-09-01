#include <iostream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

enum TokenValue
{
    NUMMBER,
    NAME,
    RP,
    LP,
    END,
    MULTI,
    DIV,
    EQU = '=',
    PLUS = '+',
    MINUS = '-',
    PRINT = ';'
};

TokenValue currentToken = PRINT;
double g_eing_z = 0;
string g_eingabe_s;
map<string, double> g_memory;
void getToken();
double parser_prim(bool get);
double parser_multDiv(bool get);
double parser_plus_minus(bool get);

int main()
{

    cout << "Quit [q]" << endl;
    while (currentToken != END)
    {
        getToken();
        if (currentToken == END)
            break;
        if (currentToken == PRINT)
            continue;
        cout << parser_plus_minus(false) << endl;
    }
    cout << "End Of calculation \n";
    return 0;
}

void getToken()
{
    char ch = 0;
    if (currentToken == PRINT && g_eing_z == 0)
        cout << "Enter a expression: ";
    cin.get(ch);
    while (isspace(ch) && ch != '\n')
    {
        cin.get(ch);
    }

    switch (ch)
    {
    case 'q':
        currentToken = END;
        break;
    case '\n':
        currentToken = PRINT;
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '7':
    case '8':
    case '9':
        cin.putback(ch);
        cin >> g_eing_z;
        currentToken = NUMMBER;
        break;
    case '+':
        currentToken = PLUS;
        break;
    case '-':
        currentToken = MINUS;
        break;
    case ';':
        currentToken = PRINT;
        break;
    case '*':
        currentToken = MULTI;
        break;
    case '/':
        currentToken = DIV;
        break;
    case '(':
        currentToken = LP;
        break;
    case ')':
        currentToken = RP;
        break;
    case '=':
        currentToken = EQU;
        break;

    default:
        if (isalpha(ch))
        {
            currentToken = NAME;
            g_eingabe_s = ch;
            while (cin.get(ch) && isalpha(ch))
                g_eingabe_s.push_back(ch);
            cin.putback(ch);
            break;
        }

        currentToken = PRINT;
        break;
    }
}

double parser_prim(bool get)
{
    if (get)
        getToken();
    double left = 0;
    switch (currentToken)
    {
    case NUMMBER:
    {
        left = g_eing_z;
        getToken();
        return left;
    }
    case NAME:
    {
        double &value = g_memory[g_eingabe_s];
        getToken();
        if (currentToken == EQU)
            value = parser_plus_minus(true);
        return value;
    }
    case LP:
    {
        left = parser_plus_minus(true);
        if (currentToken != RP)
            cout << " ) erwartet!!" << endl;
        getToken();
        return left;
    }
    }
}

double parser_multDiv(bool get)
{
    double left_md = parser_prim(get);
    switch (currentToken)
    {
    case MULTI:
        left_md *= parser_prim(true);
        break;
    case DIV:
        left_md /= parser_prim(true);
        break;
    default:
        break;
    }
    return left_md;
}
double parser_plus_minus(bool get)
{
    double left = parser_multDiv(get);
    switch (currentToken)
    {
    case PLUS:
        left += parser_multDiv(true);
        break;
    case MINUS:
        left -= parser_multDiv(true);
        break;
    }
    return left;
}
