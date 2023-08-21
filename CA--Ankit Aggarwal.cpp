#include "Header.h"
#include <bitset>
#include <conio.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

// Flags
long long U = 0;
long long Z = 0;
long long R = 0;
long long W = 0;
long long F = 0;
long long N = 0;
long long CLK = 1;
// registers
long long A = 11;
long long B = 01;
long long C = 101;
long long D = 10;
long long PC = 0;
long long MAR = 0;
long long IR = 0;
long long CAR = 0;
vector<long long> ROM(1084, 0);
vector<long long> RAM(32768, 0);

// internal registers
long long a, b, c, d, e, f, addr1, addr2, addr3, su = 0, z = 1,q=B;

// RAM instruction segment 0-100 (0x000-0x064)
// RAM data segment 101-32768 (0x065-0x7FF)

void print()
{

    string box = green_bg + border + border + border + border + border + border + border + border + border + reset;

    cout << cyan << "REGISTERS:                              " << reset << endl;

    cout << yellow << "CAR = " << CAR << red << " PC = " << PC << cyan << " MAR = " << MAR << green << " IR = " << IR << blue << "  " << reset << endl;

    cout << magenta << "A = " << A << bright_red << " B = " << B << bright_green << " C = " << C << magenta << " D = " << D << "      " << reset << endl;

    cout << bright_yellow << "FLAGS:  U = " << U << bright_blue << "  Z = " << Z << "  R = " << R << bright_magenta << "  W = " << W << bright_cyan << "  N = " << N << "  " << reset << endl;

    cout << red << "clock=" << z <<reset<< endl;
    z++;
    cout << box << endl;
    cout << endl;
}

void ankit()
{


    cout << " ________                                                                              _____________        " << endl;
    cout << " |<-11->|                                                                              |            |       " << endl;
    cout << " | " << green << " PC " << reset << " |                                                                              |            |       " << endl;
    cout << " |______|                                                                        ______|    " << yellow << " ALU" << reset << "    |       " << endl;
    cout << "    |               _________  ________   _________     ________                | _____|            |       " << endl;
    cout << "    |______________|<--16-->| |<--16-->| |<--16-->|    |<--16-->|_______________| |    |____________|       " << endl;
    cout << " ___|___           |   " << cyan << "  B " << reset << " | |  " << cyan << "  C " << reset << "  | |   " << cyan << "  D " << reset << " |    |  " << cyan << "  A " << reset << "  |_________________|         |               " << endl;
    cout << " |<-11->|          |________| |________| |________|    |________|                           |               " << endl;
    cout << " | " << green << " MAR" << reset << " |               |         |           |            |                         _______|__________     " << endl;
    cout << " |______|               |         |           |            |                        |     " << red << "BARREL" << reset << "       |    " << endl;
    cout << "     |                  |         |           |            |                        |     " << red << "SHIFTER" << reset << "      |    " << endl;
    cout << "  ___|___               |         |           |            |                        |__________________|    " << endl;
    cout << " |" << yellow_bg << "  RAM  " << reset << "|              |         |           |            |                                |   |           " << endl;
    cout << " |" << yellow_bg << " DATA  " << reset << "|              |         |           |            |                                |   |           " << endl;
    cout << " |" << yellow_bg << "_______" << reset << "|______________|_________|___________|____________|________________________________|   |           " << endl;
    cout << " |" << blue_bg << "  RAM  " << reset << "|                   |                                                                  |           " << endl;
    cout << " |" << blue_bg << "  CODE " << reset << "|                   |                    ______________________________________________|           " << endl;
    cout << " |" << blue_bg << "_______" << reset << "|                   |                   |                                 ________________________ " << endl;
    cout << "  <--16-->                   |                   |        " << yellow << "CACHE" << reset << "                    |<--24-->     <--14--> | " << endl;
    cout << "             ________________|________________   |  __________________             |                      | " << endl;
    cout << "             |        <-----16----->          |  | |<-5->|D|V| <-38-> |            |______________________| " << endl;
    cout << "             |             " << magenta << " IR " << reset << "               |__| |     | | |        |            |                      | " << endl;
    cout << "             |                                |    |     | | |        |            |        " << blue << " ROM " << reset << "         | " << endl;
    cout << "             |________________________________|    |     | | |        |____________|______________________| " << endl;
    cout << "                             |                     |     | | |        |            |                      | " << endl;
    cout << "                             |                     |     | | |        |            |                      | " << endl;
    cout << "                             |                     |_____|_|_|________|            |______________________| " << endl;
    cout << "                             |                               |                     |                      | " << endl;
    cout << "                    _________|____                           |                     |                      | " << endl;
    cout << "                    |   <--8-->  |                           |                     |______________________| " << endl;
    cout << "                    |    " << magenta << " CAR" << reset << "    |___________________________|                     |                      | " << endl;
    cout << "                    |____________|                                                 |                      | " << endl;
    cout << "                                                                                   |______________________| " << endl;
    cout << "                                                                                                            " << endl;
    cout << "                                                                                                            " << endl;
    cout << "                                                                                                            " << endl;
    cout << "                                                                                                            " << endl;
    cout << "                                                                                                            " << endl;


    string box = green_bg + border + border + border + border + border + border + border + border + border + reset;

    cout << cyan << "REGISTERS:                              " << reset << endl;

    cout << yellow << "CAR = " << CAR << red << " PC = " << PC << cyan << " MAR = " << MAR << green << " IR = " << IR << blue << "  " << reset << endl;

    cout << magenta << "A = " << A << bright_red << " B = " << B << bright_green << " C = " << C << magenta << " D = " << D << "      " << reset << endl;

    cout << bright_yellow << "FLAGS:  U = " << U << bright_blue << "  Z = " << Z << "  R = " << R << bright_magenta << "  W = " << W << bright_cyan << "  N = " << N << "  " << reset << endl;

    cout << box << endl;
    cout << endl;
}

void Barrelshifter(long long a)
{

    long long n = bd(a % 10000);
    int a2 = (a % 1000000) / 10000;

    if (a2 == 0)
    {
        int b1 = bd(B);
        for (int i = 0; i < n; i++)
            b1 = b1 * 2;
        B = db(b1);
    }
    else if (a2 == 1)
    {
        int b1 = bd(B);
        for (int i = 0; i < n; i++)
            b1 = b1 / 2;
        B = db(b1);
    }
    else if (a2 == 10)
    {
        B = rotate(B, n);
    }
    else if (a2 == 11)
    {
        // remove rotate
    }
}

void run()
{
    // lda
    if (CAR == 10000000)
    {
        cout << "NOP" << endl;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 10000001)
    {
        cout << "B(E),MAR(E,L)" << endl;
        print();
        a = extractLast11Digits(B);
        MAR = a;
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10000010)
    {
        cout << "RAM(E),A(L),R" << endl;

        A = RAM[bd(a)];
        print();
    }

    // FETCH
    else if (CAR == 11111000)
    {
        cout << " Cache(L),ROM(E){CACHE miss }(V=0)" << endl;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 11111001)
    {
        cout << "PC(E),MAR(L){CACHE hit }" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 11111010)
    {
        cout << "[MAR]->IR,PC(I){CACHE hit}" << endl;
        int a4 = bd(PC);
        a4++;
        PC = db(a4);
        IR = RAM[MAR];
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 11111011)
    {
        cout << "IR(E),B(L){CACHE hit}" << endl;
        B = IR;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 11111100)
    {
        cout << "CACHE(L),ROM(E)(CACHE MISS V=0)" << endl;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    // sta

    else if (CAR == 10001000)
    {
        cout << "NOP" << endl;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10001001)
    {
        cout << "B(E),MAR(E,L)" << endl;
        a = extractLast11Digits(B);
        MAR = bd(a);
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10001010)
    {
        cout << "RAM(L),A(E),R" << endl;
        a = extractLast11Digits(B);
        MAR = bd(a);
        RAM[MAR] = A;
        print();
    }

    // INC

    else if (CAR == 100000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 100001)
    {
        cout << "A(E,L),ALU(011),R" << endl;
        a = extractLast11Digits(B);
        MAR = bd(a);
        long long j = bd(A);
        j++;
        A = db(j);
        print();
    }

    // DEC
    else if (CAR == 101000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 101001 || CAR == 00101001)
    {
        cout << "A(E,L),ALU(100),R" << endl;
        long long j = bd(A);
        j--;
        if (j < 0)
            N = 1;
        if (j == 0)
            Z = 1;
        A = db(j);
        print();
    }

    // CLA-------dout
    else if (CAR == 1001000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 1001001)
    {
        cout << "A=0" << endl;
        A = 0;
        print();
    }

    // AND
    else if (CAR == 110000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 110001)
    {
        cout << "A(E,L), ALU(110),R" << endl;
        A = A & B;
        print();
    }

    // OR
    else if (CAR == 111000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 111001)
    {
        cout << "T2:A(E,L), ALU(110),R" << endl;
        A = A | B;
        print();
    }

    // HLT
    else if (CAR == 10111000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10111001)
    {
        cout << "Clock disabled " << endl;
        CLK = 0;
        print();
    }

    // MUL
    else if (CAR == 10000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 10001)
    {
        cout << "B(L),C(E)" << endl;
        B = C;
        // XXXXXXXXX
        int u = bd(D);
        u--;
        D = db(u);
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10010)
    {
        cout << "C(E),A(L)" << endl;
        A = C;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10011)
    {
        cout << "B(E),BS(0000)" << endl;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 10100)
    {
        cout << "A(E,L),ALU(001)" << endl;
        int b1 = bd(B);
        int q1 = bd(A);
        q1 = q1 + b1;
        A = db(q1);
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10101)
    {
        cout << " A(E),C(L)" << endl;
        C = A;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 10110)
    {
        cout << " A(L),D(E)" << endl;
        A = D;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {

            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 10111)
    {
        cout << "A(E),D(L),R" << endl;
        D = A;
        print();
        if (N == 1)
            C = 0;
        else if (Z == 1)
        {
        }
        else
        {
            CAR = 10010;
            run();
        }
    }

    // BUN
    else if (CAR == 10010000)
    {
        cout << bright_white << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
       
    }

    else if (CAR == 10010001)
    {
        cout << "MAR(E),PC(L),R" << endl;
        B = RAM[MAR];
        a = extractLast11Digits(B);
        MAR = bd(a);
        PC = MAR;
        print();
    }

    // BZ
    else if (CAR == 10100000)
    {
        cout << "NOP" << endl;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10100001)
    {
        cout << "NOP" << endl;
        print();
        if (Z == 1)
        {
            CAR = 10100010;
            run();
        }
    }
    else if (CAR == 10100010)
    {
        cout << "MAR(E), PC(L)" << endl;
        PC = MAR;
    }

    // BSA
    else if (CAR == 10011000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 10011001)
    {
        cout << "B(L),MAR(E,L),PC(E)" << endl;
        B = PC;
        MAR = B;
        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 10011010)
    {
        cout << "PC(L),MAR(E)" << endl;
        PC = MAR;
        print();
        run(); // xxxx

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 10011011)
    {
        cout << "B(E),MAR(E,L),PC(E)" << endl;
        MAR = B;
        PC = MAR;

        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    // ADD
    else if (CAR == 1010000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        B = 1;
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
        
    }

    else if (CAR == 1010001)
    {
        cout << "B(E),BS(B0-B5 DECODE)" << endl;
        Barrelshifter(IR);

        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 1010010)
    {
        cout << "A(E,L),ALU(001)" << endl;
        int b1 = bd(B);
        int q1 = bd(A);
        q1 = q1 + b1;
        A = db(q1);

        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    // SUB
    else if (CAR == 1011000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        B = 1;
        j++;
        CAR = db(j);
        run();
     
    }

    else if (CAR == 1011001)
    {
        cout << "B(E),BS(B0-B5 DECODE)" << endl;
        Barrelshifter(IR);

        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    else if (CAR == 1011010)
    {
        cout << "A(E,L),ALU(010)" << endl;
        int b1 = bd(B);
        int q1 = bd(A);
        q1 = q1 - b1;
        A = db(q1);

        print();
        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }
    // IN
    else if (CAR == 10101000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
     
    }

    else if (CAR == 10101001)
    {
        cout << " NOP, R" << endl;

        print();

        long long p = CAR;
        if (R == 1)
        {
            CAR = 10101011;
            run();
        }
        else
        {
            long long j = bd(p);
            j++;
            CAR = db(j);
            run();
        }
    }
    else if (CAR == 10101010)
    {
        cout << " NOP " << endl;
        print();
    }
    else if (CAR == 10101011)
    {
        cout << " INR(E),A(L)" << endl;
        print();
    }

    // OUT

    else if (CAR == 10110000)
    {
        cout << " NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
     
    }

    else if (CAR == 10110001)
    {
        cout << " NOP , R" << endl;

        print();

        long long p = CAR;
        if (W == 1)
        {
            CAR = 10110011;
            run();
        }
        else
        {
            long long j = bd(p);
            j++;
            CAR = db(j);
            run();
        }
    }
    else if (CAR == 10110010)
    {
        cout << " NOP " << endl;
        print();
    }
    else if (CAR == 10110011)
    {
        cout << " OUTR(E),A(L)" << endl;
        print();
    }

    // MOV
    else if (CAR == 11001000)
    {
        cout << "NOP" << endl;
        MAR = PC;
        print();

        long long k, a1, a2, a3;
        k = ROM[bd(CAR)];
        split(k, a1, a2, a3);
        long long p = CAR;
        if (a1 == 1)
        {
            CAR = a3;
            run();
        }
        long long j = bd(p);
        j++;
        CAR = db(j);
        run();
    }

    else if (CAR == 11001001)
    {
        int k1 = IR % 10000;
        if (k1 == 1)
        {
            cout << "A(L),B(E)" << endl;
            A = B;
        }
        else if (k1 == 10)
        {
            cout << "A(L),C(E)" << endl;
            A = C;
        }
        else if (k1 == 11)
        {
            cout << "A(L),D(E)" << endl;
            A = D;
        }
        else if (k1 == 100)
        {
            cout << "B(L),A(E)" << endl;
            B = A;
        }
        else if (k1 == 110)
        {
            cout << "B(L),C(E)" << endl;
            B = C;
        }
        else if (k1 == 111)
        {
            cout << "B(L),D(E)" << endl;
            B = D;
        }
        else if (k1 == 1000)
        {
            cout << "C(L),A(E)" << endl;
            C = A;
        }
        else if (k1 == 1001)
        {
            cout << "C(L),B(E)" << endl;
            C = B;
        }
        else if (k1 == 1011)
        {
            cout << "C(L),D(E)" << endl;
            C = D;
        }
        else if (k1 == 1100)
        {
            cout << "D(L),A(E)" << endl;
            D = A;
        }
        else if (k1 == 1101)
        {
            cout << "D(L),B(E)" << endl;
            D = B;
        }
        else if (k1 == 1110)
        {
            cout << "D(L),C(E)" << endl;
            D = C;
        }
        print();
        }
}
void runcode()
{
    splitNumber(RAM[PC], a);
    a = a * 1000;
    CAR = a;
    run();
};

int main()
{
    // Microinstructions

    // FETCH
    ROM[bd(11111000)] = 11111111;
    ROM[bd(11111001)] = 11111111;
    ROM[bd(11111010)] = 11111111;
    ROM[bd(11111011)] = 11111111;
    ROM[bd(11111100)] = 11111111;

    // LDA
    ROM[bd(10000000)] = 10011111000;
    ROM[bd(10000001)] = 11111111;
    ROM[bd(10000010)] = 11111111;

    // STA
    ROM[bd(10001000)] = 10011111000;
    ROM[bd(10001001)] = 11111111; // NO JUMP
    ROM[bd(10001010)] = 11111111; // NO JUMP
    // INC
    ROM[bd(100000)] = 10011111000;
    ROM[bd(100001)] = 11111111; // NO JUMP
    // DEC
    ROM[bd(101000)] = 10011111000;
    ROM[bd(101001)] = 11111111; // NO JUMP
    // CLA
    ROM[bd(1001000)] = 10011111000;
    ROM[bd(1001001)] = 11111111; // NO JUMP
    // AND
    ROM[bd(110000)] = 10011111000;
    ROM[bd(110001)] = 11111111; // NO JUMP
    // OR
    ROM[bd(111000)] = 10011111000;
    ROM[bd(111001)] = 11111111; // NO JUMP
    // HLT
    ROM[bd(10111000)] = 10011111000;
    ROM[bd(10111001)] = 11111111; // NO JUMP

    // MUL
    ROM[bd(10000)] = 10011111000;
    ROM[bd(10001)] = 11111111; // NO JUMP
    ROM[bd(10010)] = 11111111; // NO JUMP
    ROM[bd(10011)] = 11111111; // NO JUMP
    ROM[bd(10100)] = 11111111;
    ROM[bd(10101)] = 11111111;    // NO JUMP
    ROM[bd(10110)] = 10000101001; // jump to dec
    ROM[bd(10111)] = 11111111;
    // BUN
    ROM[bd(10010000)] = 10011111000;
    ROM[bd(10010001)] = 11111111; // NO JUMP

    // BZ
    ROM[bd(10100000)] = 10011111000;
    ROM[bd(10100001)] = 11111111;
    ROM[bd(10100010)] = 11111111;

    // BSA
    ROM[bd(10011000)] = 10011111000;
    ROM[bd(10011001)] = 11111111; // NO JUMP

    // DIV
    ROM[bd(11000)] = 10011111000;
    ROM[bd(11001)] = 11111111; // NO JUMP
    ROM[bd(11010)] = 11111111; // NO JUMP
    ROM[bd(11011)] = 11111111; // NO JUMP
    ROM[bd(11100)] = 11111111;
    ROM[bd(11101)] = 11111111;    // NO JUMP
    ROM[bd(11110)] = 10000101001; // jump to dec
    ROM[bd(11111)] = 11111111;

    // ADD
    ROM[bd(1010000)] = 10011111000;
    ROM[bd(1010001)] = 11111111;
    ROM[bd(1010010)] = 11111111;

    // SUB
    ROM[bd(1011000)] = 10011111000;
    ROM[bd(1011001)] = 11111111;
    ROM[bd(1011010)] = 11111111;

    // IN
    ROM[bd(10101000)] = 10011111000;
    ROM[bd(10101001)] = 11111111;
    ROM[bd(10101010)] = 11111111;
    ROM[bd(10101011)] = 11111111;

    // out
    ROM[bd(10110000)] = 10011111000;
    ROM[bd(10110001)] = 11111111;
    ROM[bd(10110010)] = 11111111;
    ROM[bd(10110011)] = 11111111;

    // MOV
    ROM[bd(11001000)] = 10011111000;
    ROM[bd(11001001)] = 11111111;

    int loadingValue = 0; // Initial loading value is zero

    while (loadingValue <= 100)
    {
        cout << "Loading " << setw(3) << loadingValue << "% ";
        // Print the loading bar
        int numOfEquals = loadingValue / 2; // Each equals sign represents 5%
        int numOfSpaces = 20 - numOfEquals;
        for (int i = 0; i < numOfEquals; i++)
        {
            cout << yellow_bg << " " << reset;
        }
        loadingValue++;
        system("cls"); // Clear console window
    }

    system("cls");
    drawLine(10, 5, 100, 5, 11);   // draw horizontal line
    drawLine(10, 5, 10, 20, 11);   // draw vertical line
    drawLine(100, 5, 100, 20, 11); // draw vertical line
    drawLine(10, 20, 100, 20, 11); // draw horizontal line

    setTextColor(10);
    for (int i = 5; i <= 70; i += 10)
    {
        gotoxy(i, 5);
        cout << "*";
        Sleep(100);
    }

    setTextColor(12);
    for (int i = 5; i <= 20; i += 5)
    {
        gotoxy(10, i);
        cout << "*";
        Sleep(100);
    }

    setTextColor(14);
    gotoxy(12, 8);
    cout << "Welcome to Processor Simulation!";
    gotoxy(20, 12);
    cout << "Initializing components...";

    gotoxy(82, 16);
    cout << yellow << "Ankit Aggarwal";
 

    for (int i = 0; i < 5; i++)
    {
        setTextColor(i + 9);
        gotoxy(20 + i * 2, 14);
        cout << "*";
        Sleep(200);
    }
    gotoxy(20, 16);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    _getch();

    cout << yellow_bg << "Processor specification" << reset << endl;
    cout << cyan << "1. Register" << endl;
    cout << "   (i). Special register" << endl;
    cout << "       - PC(program counter) - 11bit" << endl;
    cout << "       - MAR (memory address register) - 11bit" << endl;
    cout << "       - IR (instruction register) - 16bit" << endl;
    cout << "       - CAR (control address register) - 8bit" << endl;
    cout << "       - SBR (Subroutine register) - 8bit" << endl;
    cout << "   (ii). General purpose register" << endl;
    cout << "       - B, C, D, A(accumulator) - 16 bit" << endl;
    cout << "   (iii). I/O register" << endl;
    cout << "       - INR (input register) - 16bit" << endl;
    cout << "       - OUTR (output register) - 16bit" << endl;
    cout << endl;
    cout << green << "2. Memory" << endl;
    cout << "   (i). RAM - 4KiB [2k*16 bit] (data portion code portion)" << endl;
    cout << "   (ii). ROM - 256*38 bit" << endl;
    cout << "   (iii). Cache -" << endl;
    cout << "       tag      offset" << endl;
    cout << "        5bit     3bit" << endl;
    cout << "       cache line- 2" << endl;
    cout << "       Block size- 8*38 bit (offset 3 bit)" << endl;
    cout << "       16*[5(tag)+1(Valid bit) +1(Dirty bit) + 38(cache Data width)] - total capacity" << endl;
    cout << "       38*2*8 - data cache capacity" << endl;
    cout << "       Look through model" << endl;
    cout << "       Fully associative organization" << endl;
    cout << endl;
    cout << red << "3. Flag" << endl;
    cout << "   - N(negative), Z(zero) - based on output of ALU" << endl;
    cout << "   - R, W (read write flag based on I/O operation)" << endl;
    cout << endl;
    cout << magenta << "4. ALU (arithmetic logic unit) - work with accumulator with 16 bit" << endl;
    cout << endl;
    cout << blue << "5. barrel shifter (one input of ALU bass by barrel shifter)" << reset << endl;
    cout << endl;
    _getch();
    cout << yellow_on_blue << "   General working feature" << reset << endl;
    cout << yellow << "-->" << reset << "  We divide our instruction on basis of arithmetic and non-arithmetic which is decide by b15 bit of instruction" << endl;
    cout << yellow << "-->" << reset << "  which enable the decoder of barrel shifter for arithmetic operation." << endl;
    cout << yellow << "-->" << reset << "  Arithmetic instruction (b15 = 0)" << endl;
    cout << yellow << "-->" << reset << "  ADD, SUB, INC, DEC, MUL, AND, OR, CMA, CLA" << endl;
    cout << yellow << "-->" << reset << "  Non-arithmetic instruction (b15 = 1)" << endl;
    cout << yellow << "-->" << reset << "  LDA, STA, BUN, BSA, BZ, IN, OUT, HLT" << endl;
    cout << yellow << "-->" << reset << "  Only load, store and branching instruction are access to the memory." << endl;
    cout << yellow << "-->" << reset << "  We have implicit operand destination register(A) and source register (A, B) in arithmetic instruction and register B is pass by barrel shifter." << std::endl;
    cout << yellow << "-->" << reset << "  We divide our RAM memory in code and date portion." << endl;
    cout << yellow << "-->" << reset << "  When power on then PC=0X000 and CAR=0XF8." << endl;
    cout << yellow << "-->" << reset << "  Unique concept in processor" << endl;
    cout << yellow << "-->" << reset << "  One input of ALU is pass by barrel shifter.by this we can implement divide and multiply fastly." << endl;
    cout << yellow << "-->" << reset << "  We implement cache memory before ROM.by this instruction access time is decrease." << endl;
    cout << yellow << "-->" << reset << "  We use branching in ROM using CAR. Due to this our ROM size is decrease." << endl;
    cout << yellow << "-->" << reset << "  We implement multiplication using branching in ROM." << endl;
    cout << yellow << "-->" << reset << "  We implement CLA (clear accumulator) using branching in ROM using concept A=A && (~A)." << endl;

    cout << endl;
    cout << cyan << "ADD: A = A+B" << endl;
    cout << "SUB: A = A-B" << endl;
    cout << "MUL: C = C*B" << endl;
    cout << "RAM Code 0-100 (0x000-0x064)" << endl;
    cout << "RAM data segment 101-32768 (0x065-0x7FF)" << endl;
    cout << "Give every instruction in  CAPITAL letters" << endl;

    cout << reset << endl;
    _getch();
    cout << endl;
    cout << " ________                                                                              _____________        " << endl;
    cout << " |<-11->|                                                                              |            |       " << endl;
    cout << " | " << green << " PC " << reset << " |                                                                              |            |       " << endl;
    cout << " |______|                                                                        ______|    " << yellow << " ALU" << reset << "    |       " << endl;
    cout << "    |               _________  ________   _________     ________                | _____|            |       " << endl;
    cout << "    |______________|<--16-->| |<--16-->| |<--16-->|    |<--16-->|_______________| |    |____________|       " << endl;
    cout << " ___|___           |   " << cyan << "  B " << reset << " | |  " << cyan << "  C " << reset << "  | |   " << cyan << "  D " << reset << " |    |  " << cyan << "  A " << reset << "  |_________________|         |               " << endl;
    cout << " |<-11->|          |________| |________| |________|    |________|                           |               " << endl;
    cout << " | " << green << " MAR" << reset << " |               |         |           |            |                         _______|__________     " << endl;
    cout << " |______|               |         |           |            |                        |     " << red << "BARREL" << reset << "       |    " << endl;
    cout << "     |                  |         |           |            |                        |     " << red << "SHIFTER" << reset << "      |    " << endl;
    cout << "  ___|___               |         |           |            |                        |__________________|    " << endl;
    cout << " |" << magenta_bg << "  RAM  " << reset << "|              |         |           |            |                                |   |           " << endl;
    cout << " |" << magenta_bg << " DATA  " << reset << "|              |         |           |            |                                |   |           " << endl;
    cout << " |" << magenta_bg << "_______" << reset << "|______________|_________|___________|____________|________________________________|   |           " << endl;
    cout << " |" << blue_bg << "  RAM  " << reset << "|                   |                                                                  |           " << endl;
    cout << " |" << blue_bg << "  CODE " << reset << "|                   |                    ______________________________________________|           " << endl;
    cout << " |" << blue_bg << "_______" << reset << "|                   |                   |                                 ________________________ " << endl;
    cout << "  <--16-->                   |                   |        " << yellow << "CACHE" << reset << "                    |<--24-->     <--14--> | " << endl;
    cout << "             ________________|________________   |  __________________             |                      | " << endl;
    cout << "             |        <-----16----->          |  | |<-5->|D|V| <-38-> |            |______________________| " << endl;
    cout << "             |             " << magenta << " IR " << reset << "               |__| |     | | |        |            |                      | " << endl;
    cout << "             |                                |    |     | | |        |            |        " << blue << " ROM " << reset << "         | " << endl;
    cout << "             |________________________________|    |     | | |        |____________|______________________| " << endl;
    cout << "                             |                     |     | | |        |            |                      | " << endl;
    cout << "                             |                     |     | | |        |            |                      | " << endl;
    cout << "                             |                     |_____|_|_|________|            |______________________| " << endl;
    cout << "                             |                               |                     |                      | " << endl;
    cout << "                    _________|____                           |                     |                      | " << endl;
    cout << "                    |   <--8-->  |                           |                     |______________________| " << endl;
    cout << "                    |    " << magenta << " CAR" << reset << "    |___________________________|                     |                      | " << endl;
    cout << "                    |____________|                                                 |                      | " << endl;
    cout << "                                                                                   |______________________| " << endl;
    cout << "                                                                                                            " << endl;
    cout << "                                                                                                            " << endl;
    cout << "                                                                                                            " << endl;
    cout << "                                                                                                            " << endl;
    cout << "                                                                                                            " << endl;

    _getch();
    cout << "what are the values of data from 0x065 to 0x067 : ";
    cin >> RAM[hd("065")] >> RAM[hd("066")] >> RAM[hd("067")];

    _getch();
    cout<<endl;
    while (CLK != 0)
    {

        string mnemonics;
        getline(cin, mnemonics);

        string mnemonics1, mnemonics2 = "000", mnemonics3 = "000";
        splitString(mnemonics, mnemonics1, mnemonics2, mnemonics3);

        if (mnemonics1 == "LDA")
        {
            string locationb = hb(mnemonics2);
            string op = "10000";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }
        else if (mnemonics1 == "STA")
        {
            string locationb = hb(mnemonics2);
            string op = "10001";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "BUN")
        {
            string locationb = hb(mnemonics2);
            string op = "10010";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "BSA")
        {
            string locationb = hb(mnemonics2);
            string op = "10011";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "BZ")
        {
            string locationb = hb(mnemonics2);
            string op = "10100";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "IN")
        {
            string locationb = hb(mnemonics2);
            string op = "10101";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "OUT")
        {
            string locationb = hb(mnemonics2);
            string op = "10110";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "HLT")
        {
            string locationb = hb(mnemonics2);
            string op = "10111";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "ADD")
        {
            string a;
            string b = hb(mnemonics3);
            if (mnemonics2 == "LSL")
                a = "00";
            else if (mnemonics2 == "LSR")
                a = "01";
            else if (mnemonics2 == "ROR")
                a = "10";
            else if (mnemonics2 == "NOP")
                a = "11";
            string op = "01010";
            string opcod = cons(op, a, b);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "SUB")
        {
            string a;
            string b = hb(mnemonics3);
            if (mnemonics2 == "LSL")
                a = "00";
            else if (mnemonics2 == "LSR")
                a = "01";
            else if (mnemonics2 == "ROR")
                a = "10";
            else if (mnemonics2 == "NOP")
                a = "11";
            string op = "01011";
            string opcod = cons(op, a, b);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "MUL")
        {
            string locationb = hb(mnemonics2);
            string op = "00010";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "DIV")
        {
            string locationb = hb(mnemonics2);
            string op = "00011";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "INC")
        {
            string locationb = hb(mnemonics2);
            string op = "00100";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "DEC")
        {
            string locationb = hb(mnemonics2);
            string op = "00101";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "AND")
        {
            string locationb = hb(mnemonics2);
            string op = "110";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }

        else if (mnemonics1 == "OR")
        {
            string locationb = hb(mnemonics2);
            string op = "111";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }
        else if (mnemonics1 == "CLA")
        {
            string locationb = hb(mnemonics2);
            string op = "01001";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }
        else if (mnemonics1 == "RES")
        {
            string locationb = hb(mnemonics2);
            string op = "11000";
            string opcod = concatenateStrings(op, locationb);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
        }
        else if (mnemonics1 == "MOV")
        {
            string mov1, mov2;
            string op = "11001";
            string zero = "0000000";
            if (mnemonics2 == "A")
                mov1 = "00";
            else if (mnemonics2 == "B")
                mov1 = "01";
            else if (mnemonics2 == "C")
                mov1 = "10";
            else if (mnemonics2 == "D")
                mov1 = "11";


            if (mnemonics3 == "A")
                mov2 = "00";
            else if (mnemonics3 == "B")
                mov2 = "01";
            else if (mnemonics3 == "C")
                mov2 = "10";
            else if (mnemonics3 == "D")
                mov2 = "11";

            string opcod;
            opcod.append(op);
            opcod.append(zero);
            opcod.append(mov1);
            opcod.append(mov2);
            long long opcode = si(opcod);
            RAM[PC] = opcode;
            cout << opcode << endl;
            }
        else if (mnemonics1 == "ARCH")
        {
            ankit();
        }
        else if (mnemonics1 == "CLEAR")
        {

            system("cls"); // Clear console window
            drawspace(0, 0, 50, 0, cyan_bg);
            drawspace(0, 0, 50, 0, bg);
            drawspace(0, 0, 50, 0, green_bg);
            system("cls"); // Clear console window
            z = 0;
        }

        else if (mnemonics1 == "RAM")
        {
            if (su == 1)
            {
                for (int i = 0; i < 100; i++)
                {
                    cout << green << "RAM[" << db(i) << "] = " << RAM[i] << endl;
                }
            }
            else
            {
                cout <<red<< "you are not a supper user" <<reset<< endl;
            }
        }

        else if (mnemonics1 == "SU")
        {
            char ch;
            string mode = "";
            cout << yellow << "SU";

            while ((ch = _getch()) != '\r')
            {
                if (ch == '\b')
                {
                    if (!mode.empty())
                    {
                        mode.pop_back();
                        cout << "\b \b";
                    }
                }
                else
                {
                    mode += ch;
                    cout << "";
                }
            }
            if (mode == "ankit")
            {
                cout << endl;
                cout << "you are supper user now!" << endl;
                su = 1;
            }
        }

        else
            cout << "_____________________________________________________________________________________";
        cout << endl;
        runcode();
    }
    return 0;
}