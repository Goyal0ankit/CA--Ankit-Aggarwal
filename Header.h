
#include <bitset>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <windows.h>
using namespace std;

static const char* const red = "\033[0;31m";     // red color
static const char* const cyan = "\033[0;36m";    // cyan color
static const char* const yellow = "\033[0;33m";  // yellow color
static const char* const green = "\033[0;32m";   // green color
static const char* const black = "\033[0;30m";   // black
static const char* const blue = "\033[0;34m";    // blue
static const char* const magenta = "\033[0;35m"; // magenta
static const char* const white = "\033[0;37m";   // white

static const char* const bright_red = "\033[1;31m";     // bright red
static const char* const bright_green = "\033[1;32m";   // bright green
static const char* const bright_yellow = "\033[1;33m";  // bright yellow
static const char* const bright_blue = "\033[1;34m";    // bright blue
static const char* const bright_magenta = "\033[1;35m"; // bright magenta
static const char* const bright_cyan = "\033[1;36m";    // bright cyan
static const char* const bright_white = "\033[1;37m";   // bright white

static const char* const reset = "\033[0m";  // reset color
static const char* const border = "======="; // horizontal line character for box drawing

std::string bg = "\033[48;5;236m";              // dark gray
std::string cyan_bg = "\033[48;2;0;128;128m";   // cyan background color
std::string yellow_bg = "\033[48;2;255;255;0m"; // yellow background color
std::string green_bg = "\033[48;2;0;128;0m";    // green background color
std::string red_bg = "\033[48;2;255;0;0m";      // red background color
std::string blue_bg = "\033[44m";
std::string magenta_bg = "\033[45m";
std::string white_bg = "\033[47m";
std::string yellow_on_blue = "\033[33;44m";  // yellow text on blue background
std::string light_yellow_bg = "\033[103m";
std::string light_green_bg = "\033[102m";
std::string light_red_bg = "\033[101m";
std::string light_magenta_bg = "\033[105m";
std::string light_cyan_bg = "\033[106m";



int rotate(int num, int n)
{
    // Convert integer to string
    string str = to_string(num);

    // Rotate the string by n positions
    rotate(str.begin(), str.begin() + n, str.end());

    // Convert the rotated string back to integer
    int rotated_num = stoi(str);

    return rotated_num;
}
void splitNumber(long long a, long long& b)
{

    // Get first digit
    b = a / 100000000000;
}

long long extractLast11Digits(long long input)
{
    long long output = input % static_cast<long long>(pow(10, 11));
    return output;
}
vector<int> strint(string& str)
{
    std::vector<int> result;
    for (const auto& c : str)
    {
        result.push_back(c - '0');
    }
    return result;
}

void splitString(string inputString, string& string1, string& string2,
    string& string3)
{
    stringstream ss(inputString);
    ss >> string1;
    ss >> string2;
    ss >> string3;
}

long long si(string& str)
{
    long long num = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        num = num * 10 + (str[i] - '0');
    }
    return num;
}
long long db(long long n)
{
    long long binary = 0;
    int i = 1;
    while (n != 0)
    {
        int remainder = n % 2;
        n /= 2;
        binary += remainder * i;
        i *= 10;
    }
    return binary;
}
long long bd(long long n)
{
    int decimal = 0, i = 0, rem;
    while (n != 0)
    {
        rem = n % 10;
        n /= 10;
        decimal += rem * pow(2, i);
        ++i;
    }
    return decimal;
}

// Function to convert a hexadecimal digit to its binary equivalent
string hexDigitToBinary(char hexDigit)
{
    switch (hexDigit)
    {
    case '0':
        return "0000";
    case '1':
        return "0001";
    case '2':
        return "0010";
    case '3':
        return "0011";
    case '4':
        return "0100";
    case '5':
        return "0101";
    case '6':
        return "0110";
    case '7':
        return "0111";
    case '8':
        return "1000";
    case '9':
        return "1001";
    case 'a':
    case 'A':
        return "1010";
    case 'b':
    case 'B':
        return "1011";
    case 'c':
    case 'C':
        return "1100";
    case 'd':
    case 'D':
        return "1101";
    case 'e':
    case 'E':
        return "1110";
    case 'f':
    case 'F':
        return "1111";
    default:
        return "";
    }
}

// Function to convert a hexadecimal number to binary
string hb(string hexNumber)
{
    string binaryNumber = "";
    for (char hexDigit : hexNumber)
    {
        binaryNumber += hexDigitToBinary(hexDigit);
    }
    return binaryNumber;
}

int hd(string hex)
{
    int dec = 0;
    int power = 1;
    for (int i = hex.size() - 1; i >= 0; i--)
    {
        int digit;
        if (hex[i] >= '0' && hex[i] <= '9')
        {
            digit = hex[i] - '0';
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f')
        {
            digit = hex[i] - 'a' + 10;
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            digit = hex[i] - 'A' + 10;
        }
        else
        {
            cout << "Invalid hexadecimal string" << endl;
            return 0;
        }
        dec += digit * power;
        power *= 16;
    }
    return dec;
}

string dh(int dec)
{
    string hex = "";
    while (dec > 0)
    {
        int remainder = dec % 16;
        if (remainder < 10)
        {
            hex = char(remainder + '0') + hex;
        }
        else
        {
            hex = char(remainder - 10 + 'a') + hex;
        }
        dec /= 16;
    }
    return hex;
}

string concatenateStrings(string st1, string st2)
{
    string str = st1; // Start with the first string
    str.append(st2.substr(
        1)); // Append the second string starting from the second character
    return str;
}
string cons(string st1, string st2, string st3)
{
    string str = st1; // Start with the first string
    string s = "00000";
    str.append(s);
    str.append(st2);
    str.append(st3);
    return str;
}

long long inc(long long n)
{
    long long temp = n;
    long long i = 0;
    while (temp != 0)
    {
        if (temp % 10 == 0)
        {
            n += (1 << i);
            break;
        }
        else
        {
            n -= (1 << i);
        }
        temp /= 10;
        i++;
    }
    return n;
}

long long first5(long long number)
{
    // Divide the number by 1000 to remove the last 3 digits
    long long truncatedNumber = number / 1000;

    // Divide the truncated number by 10^2 to remove the last 2 digits
    long long firstFiveDigits = truncatedNumber / 100;

    return firstFiveDigits;
}
void split(long long a, long long& a1, long long& a2, long long& a3)
{
    // Get first digit
    a1 = a / 10000000000;

    // Get second and third digits
    a2 = (a / 1000000) % 1000;

    // Get digits from 4th to 11th position
    a3 = a % 100000000;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawLine(int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float x = x1;
    float y = y1;
    float xIncr = dx / (float)steps;
    float yIncr = dy / (float)steps;
    setTextColor(color);
    for (int i = 0; i <= steps; i++) {
        gotoxy((int)x, (int)y);
        cout << "*";
        x += xIncr;
        y += yIncr;
        Sleep(10);
    }
}

void drawspace(int x1, int y1, int x2, int y2, string s) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float x = x1;
    float y = y1;
    float xIncr = dx / (float)steps;
    float yIncr = dy / (float)steps;
    for (int i = 0; i <= steps; i++) {
        gotoxy((int)x, (int)y);
        cout << s << " " << reset;
        x += xIncr;
        y += yIncr;
        Sleep(10);
    }
}
