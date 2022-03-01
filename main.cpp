#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <winbgim.h>

using namespace std;

void readBMP(char *filename)
{
    int i;
    FILE *f = fopen(filename, "rb");
    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    // extract image height and width from header
    int width = *(int *)&info[18];
    int height = *(int *)&info[22];
    std::cout << width << " x " << height << std::endl;
    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    int off = 0;
    int of = 0;
    if ((width * 3 + of) % 4 != 0)
        of = 2;
    size += of * height;

    unsigned char *data = new unsigned char[size];

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f); // devo leggere anche gli spazi tra una riga %8 e l'altra
    fclose(f);

    std::cout << of << " offset " << std::endl;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            putpixel(x, height - y, COLOR((int)data[y * width * 3 + x * 3 + off + 2], (int)data[y * width * 3 + x * 3 + 1 + off], (int)data[y * width * 3 + x * 3 + off]));
        }
        off += of;
    }
}

void stampa_semi(int ciotole[])
{
    setbkcolor(COLOR(255, 0, 0));
    int x = 270, y = 400;
    char numero[10];
    setcolor(COLOR(255, 255, 255));
    for (int i = 0; i < 14; i++)
    {
        if (i < 7 && i != 0)
        {
            x += 143;
        }
        else if (i > 6)
        {
            setbkcolor(COLOR(0, 0, 255));
            if (i == 7)
            {
                x = 980;
                y = 577;
            }
            else
            {
                x -= 143;
            }
        }
        settextjustify(1, 1);
        if (ciotole[i] > 9)
        {
            settextstyle(3, 0, 4);
        }
        else
        {
            settextstyle(3, 0, 5);
        }
        outtextxy(x, y, "   ");
        itoa(ciotole[i], numero, 10);
        outtextxy(x, y, numero);
    }
    cout << endl;
}

int mouse2()
{
    int x, y;
    bool valida = false;
    do
    {
        while (!ismouseclick(WM_LBUTTONDOWN))
        {
            delay(500);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if (x >= 210 && x <= 328 && y >= 514 && y <= 631)
            return 6;
        else if (x >= 350 && x <= 470 && y >= 500 && y <= 620)
            return 5;
        else if (x >= 494 && x <= 616 && y >= 490 && y <= 608)
            return 4;
        else if (x >= 643 && x <= 762 && y >= 486 && y < 609)
            return 3;
        else if (x >= 789 && x <= 913 && y >= 495 && y <= 614)
            return 2;
        else if (x >= 936 && x <= 1056 && y >= 508 && y <= 627)
            return 1;

    } while (valida == false);
}

int mouse()
{
    int x, y;
    bool valida = false;
    do
    {
        while (!ismouseclick(WM_LBUTTONDOWN))
        {
            delay(500);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if (x >= 210 && x <= 328 && y >= 330 && y <= 447)
            return 1;
        else if (x >= 350 && x <= 470 && y >= 316 && y <= 436)
            return 2;
        else if (x >= 494 && x <= 616 && y >= 306 && y <= 424)
            return 3;
        else if (x >= 643 && x <= 762 && y >= 302 && y < 425)
            return 4;
        else if (x >= 789 && x <= 913 && y >= 331 && y <= 430)
            return 5;
        else if (x >= 936 && x <= 1056 && y >= 324 && y <= 443)
            return 6;

    } while (valida == false);
}

int main()
{
    bool ok = false, ai = false, okpt2 = false;
    int x0, y0;
    initwindow(1280, 960, "Bantumi");
    rectangle(590, 460, 630, 500);
    rectangle(650, 460, 690, 500);
    do
    {
        while (!ismouseclick(WM_LBUTTONDOWN))
        {
            delay(500);
        }
        getmouseclick(WM_LBUTTONDOWN, x0, y0);
        if (x0 > 580 && x0 < 620 && y0 > 460 && y0 < 500)
        {
            ai = true;
            okpt2 = true;
        }
        else if (x0 > 660 && x0 < 700 && y0 > 460 && y0 < 500)
            okpt2 = true;
    } while (okpt2 == false);
    // readBMP("Board1.bmp");
    bool gioca_ancora = false;
    do
    {
        setcolor(COLOR(255, 255, 254));
        setfillstyle(1, COLOR(255, 255, 255));
        rectangle(0, 690, 1015, 750);
        floodfill(50, 700, COLOR(255, 255, 254));
        setcolor(COLOR(0, 0, 0));
        circle(633, 227, 40);
        circle(633, 160, 27);
        setfillstyle(1, COLOR(255, 216, 224));
        floodfill(630, 155, COLOR(0, 0, 0));
        bool gioco = true, ciotole1a0 = true, ciotole2a0 = true;
        srand(time(0));
        int n = rand() % 4 + 3;
        int ciotole[14] = {1, 0, 0, 1, 0, 0, 0, 0, 5, 0, 0, 1, 0, 0}; //{n, n, n, n, n, n, 0, n, n, n, n, n, n, 0}
        int mossa, player = rand() % 2 + 1, posizione;
        while (gioco == true)
        {
            if (player == 1)
            {
                setfillstyle(1, COLOR(255, 0, 0));
                floodfill(630, 227, COLOR(0, 0, 0));
                setcolor(COLOR(255, 255, 225));
                setbkcolor(COLOR(255, 0, 0));
                settextjustify(1, 1);
                settextstyle(3, 0, 4);
                outtextxy(633, 227, "P1");
                bool rigioca = false;
                do
                {
                    stampa_semi(ciotole);
                    do
                    {
                        mossa = mouse();
                    } while (ciotole[mossa - 1] == 0);
                    posizione = mossa - 1;
                    int i = 0, idk;
                    for (; i < ciotole[posizione]; i++)
                    {
                        idk = posizione + 1 + i;
                        if (idk > 13)
                            idk -= 14;
                        ciotole[idk] += 1;
                    }
                    ciotole[posizione] = 0;
#pragma region ciula semi
                    if (ciotole[idk] - 1 == 0 && idk != 6)
                    {
                        if (ciotole[12 - idk] != 0 && idk < 7)
                        {
                            ciotole[6] += ciotole[12 - idk];
                            ciotole[6] += ciotole[idk];
                            ciotole[12 - idk] = 0;
                            ciotole[idk] = 0;
                        }
                    }
#pragma endregion

#pragma region controllo ciotole
                    int counter1 = 0, counter2 = 0;
                    for (int k = 0; k < 6; k++)
                    {
                        if (ciotole[k] == 0)
                            counter1++;
                        if (ciotole[k + 7] == 0)
                            counter2++;
                    }
                    if (counter1 == 6)
                    {
                        for (int k = 7; k < 13; k++)
                        {
                            ciotole[13] += ciotole[k];
                            ciotole[k] = 0;
                        }
                    }
                    else if (counter2 == 6)
                    {
                        for (int k = 0; k < 6; k++)
                        {
                            ciotole[6] += ciotole[k];
                            ciotole[k] = 0;
                        }
                    }
#pragma endregion

                    if (ciotole[13] > n * 6 && ciotole[13] > ciotole[6])
                    {
                        stampa_semi(ciotole);
                        setcolor(COLOR(0, 0, 0));
                        setbkcolor(COLOR(255, 255, 255));
                        outtextxy(440, 721, "   Player 2 ha vinto! Vuoi rigiocare?  Si  No");
                        int x = 0, y = 0;
                        do
                        {
                            while (!ismouseclick(WM_LBUTTONDOWN))
                            {
                                delay(500);
                            }
                            getmouseclick(WM_LBUTTONDOWN, x, y);
                            if (x > 740 && x < 790 && y > 680 && y < 745)
                            {
                                gioca_ancora = true;
                                gioco = false;
                                ok = true;
                                break;
                            }
                            else if (x > 825 && x < 875 && y > 680 && y < 745)
                            {
                                gioca_ancora = false;
                                return 0;
                            }
                        } while (ok == false);
                    }
                    else if (ciotole[6] > n * 6 && ciotole[6] > ciotole[13])
                    {
                        stampa_semi(ciotole);
                        setcolor(COLOR(0, 0, 0));
                        setbkcolor(COLOR(255, 255, 255));
                        outtextxy(440, 721, "   Player 1 ha vinto! Vuoi rigiocare?  Si  No");
                        int x = 0, y = 0;
                        do
                        {
                            while (!ismouseclick(WM_LBUTTONDOWN))
                            {
                                delay(500);
                            }
                            getmouseclick(WM_LBUTTONDOWN, x, y);
                            if (x > 740 && x < 790 && y > 680 && y < 745)
                            {
                                gioca_ancora = true;
                                gioco = false;
                                ok = true;
                                break;
                            }
                            else if (x > 825 && x < 875 && y > 680 && y < 745)
                            {
                                gioca_ancora = false;
                                return 0;
                            }
                        } while (ok == false);
                    }
                    if (ok == true)
                    {
                        ok = false;
                        break;
                    }
                    if (idk == 6)
                        rigioca = true;
                    else
                        rigioca = false;

                } while (rigioca == true);
                player = 2;
            }
            else
            {
                setfillstyle(1, COLOR(0, 0, 255));
                floodfill(630, 227, COLOR(0, 0, 0));
                setcolor(COLOR(255, 255, 225));
                settextstyle(3, 0, 4);
                setbkcolor(COLOR(0, 0, 255));
                settextjustify(1, 1);
                outtextxy(630, 227, "P2");
                bool rigioca = false;
                do
                {
                    stampa_semi(ciotole);
                    if (ai == false)
                    {
                        do
                        {
                            mossa = mouse2();
                        } while (ciotole[mossa + 6] == 0);
                        posizione = mossa + 6;
                    }
                    else
                    {
                        bool scelto = false;
                        for (int z = 7; z < 13; z++)
                        {
                            if (ciotole[z] != 0 && 13 - z - ciotole[z] == 0)
                            {
                                posizione = z;
                                scelto = true;
                                break;
                            }
                        }
                        if (scelto == false)
                        {
                            int a = -1;
                            for (int z = 0; z < 6; z++)
                            {
                                if (ciotole[ciotole[z] + z] == 0)
                                {
                                    if (ciotole[13 - z] > ciotole[a])
                                        a = 13 - z;
                                }
                            }
                            if (a != -1 && ciotole[a] != 0)
                            {
                                posizione = a;
                                scelto = true;
                            }
                        }
                        if (scelto == false)
                        {
                            for (int z = 7; z < 13; z++)
                            {
                                if (z + ciotole[z] < 13 && ciotole[(ciotole[z] + z)] == 0 && ciotole[z] != 0)
                                {
                                    posizione = z;
                                    scelto = true;
                                    break;
                                }
                            }
                        }
                        if (scelto == false)
                        {
                            do
                            {
                                posizione = (rand() % 5) + 7;
                            } while (ciotole[posizione] == 0);
                        }
                    }
                    int i = 0, idk;
                    for (; i < ciotole[posizione]; i++)
                    {
                        idk = posizione + i;
                        if (idk > 13)
                            idk -= 14;
                        if (idk == 6)
                            idk++;
                        ciotole[idk] += 1;
                    }
                    ciotole[posizione] = 0;
#pragma region ciula semi
                    if (ciotole[idk] - 1 == 0 && idk != 13)
                    {
                        if (ciotole[12 - idk] != 0 && idk > 7)
                        {
                            ciotole[13] += ciotole[12 - idk];
                            ciotole[13] += ciotole[idk];
                            ciotole[12 - idk] = 0;
                            ciotole[idk] = 0;
                        }
                    }
#pragma endregion

#pragma region controllo ciotole
                    int counter1 = 0, counter2 = 0;
                    for (int k = 0; k < 6; k++)
                    {
                        if (ciotole[k] == 0)
                            counter1++;
                        if (ciotole[k + 7] == 0)
                            counter2++;
                    }
                    if (counter1 == 6)
                    {
                        for (int k = 7; k < 13; k++)
                        {
                            ciotole[13] += ciotole[k];
                            ciotole[k] = 0;
                        }
                    }
                    else if (counter2 == 6)
                    {
                        for (int k = 0; k < 6; k++)
                        {
                            ciotole[6] += ciotole[k];
                            ciotole[k] = 0;
                        }
                    }
#pragma endregion

                    if (ciotole[13] > n * 6 && ciotole[13] > ciotole[6])
                    {
                        stampa_semi(ciotole);
                        setcolor(COLOR(0, 0, 0));
                        setbkcolor(COLOR(255, 255, 255));
                        outtextxy(440, 721, "   Player 2 ha vinto! Vuoi rigiocare?  Si  No");
                        int x = 0, y = 0;
                        do
                        {
                            while (!ismouseclick(WM_LBUTTONDOWN))
                            {
                                delay(500);
                            }
                            getmouseclick(WM_LBUTTONDOWN, x, y);
                            if (x > 740 && x < 790 && y > 680 && y < 745)
                            {
                                gioca_ancora = true;
                                gioco = false;
                                ok = true;
                                break;
                            }
                            else if (x > 825 && x < 875 && y > 680 && y < 745)
                            {
                                gioca_ancora = false;
                                return 0;
                            }
                        } while (ok == false);
                    }
                    else if (ciotole[6] > n * 6 && ciotole[6] > ciotole[13])
                    {
                        stampa_semi(ciotole);
                        setcolor(COLOR(0, 0, 0));
                        setbkcolor(COLOR(255, 255, 255));
                        outtextxy(440, 721, "   Player 1 ha vinto! Vuoi rigiocare?  Si  No");
                        int x = 0, y = 0;
                        do
                        {
                            while (!ismouseclick(WM_LBUTTONDOWN))
                            {
                                delay(500);
                            }
                            getmouseclick(WM_LBUTTONDOWN, x, y);
                            if (x > 740 && x < 790 && y > 680 && y < 745)
                            {
                                gioca_ancora = true;
                                gioco = false;
                                ok = true;
                                break;
                            }
                            else if (x > 825 && x < 875 && y > 680 && y < 745)
                            {
                                gioca_ancora = false;
                                return 0;
                            }
                        } while (ok == false);
                    }
                    if (ok == true)
                    {
                        ok = false;
                        break;
                    }
                    if (idk == 13)
                        rigioca = true;
                    else
                        rigioca = false;

                    if (ai == true)
                        delay(2000);

                } while (rigioca == true);
                player = 1;
            }
        }
    } while (gioca_ancora == true);
    getch();
}

/*
To do:
    - Finish graphics
    - Ai

*/