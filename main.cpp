#include <iostream>

using namespace std;

int main()
{
    bool gioco = true, ciotole1a0 = true, ciotole2a0 = true;
    int ciotole[14] = {3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 0};
    int mossa, player = 1, posizione;
    while (gioco == true)
    {
        for (int i = 0; i < 14; i++)
        {
            if (i == 7)
                cout << endl;
            cout << ciotole[i] << "\t";
        }
        cout << endl;
        if (player == 1)
        {
            do
            {
                cout << "Player " << player << " inserisci la tua mossa: ";
                cin >> mossa;
            } while (ciotole[mossa - 1] == 0);
            posizione = mossa - 1;
            int i = 0, idk;
            for (; i < ciotole[posizione]; i++)
            {
                idk = posizione + 1 + i;
                if (idk > 12)
                    idk -= 13;
                ciotole[idk] += 1;
            }
            ciotole[posizione] = 0;
#pragma region ciula semi
            if (ciotole[idk] - 1 == 0 && idk != 6)
            {
                if (idk + 7 > 13)
                    idk -= 7;
                if (ciotole[idk + 7] != 0)
                {
                    ciotole[6] += ciotole[idk + 7];
                    ciotole[6] += ciotole[idk];
                    ciotole[idk + 7] = 0;
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
            if (counter2 == 6)
            {
                for (int k = 0; k < 6; k++)
                {
                    ciotole[6] += ciotole[k];
                    ciotole[k] = 0;
                }
            }
#pragma endregion

            if (ciotole[13] > 18 && ciotole[13] > ciotole[6])
            {
                cout << "Player 2 ha vinto!";
                return 0;
            }
            else if (ciotole[6] > 18 && ciotole[6] > ciotole[13])
            {
                cout << "Player 1 ha vinto!";
                return 0;
            }

            player = 2;
        }
        else
        {
            do
            {
                cout << "Player " << player << " inserisci la tua mossa: ";
                cin >> mossa;
            } while (ciotole[mossa + 6] == 0);
            posizione = mossa + 6;
            int i = 0, idk;
            for (; i < ciotole[posizione]; i++)
            {
                idk = posizione + 1 + i;
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
                if (idk + 7 > 13)
                    idk -= 7;
                if (ciotole[idk + 7] != 0)
                {
                    ciotole[13] += ciotole[idk + 7];
                    ciotole[13] += ciotole[idk];
                    ciotole[idk + 7] = 0;
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
            if (counter2 == 6)
            {
                for (int k = 0; k < 6; k++)
                {
                    ciotole[6] += ciotole[k];
                    ciotole[k] = 0;
                }
            }
#pragma endregion

            if (ciotole[13] > 18 && ciotole[13] > ciotole[6])
            {
                cout << "Player 2 ha vinto!";
                return 0;
            }
            else if (ciotole[6] > 18 && ciotole[6] > ciotole[13])
            {
                cout << "Player 1 ha vinto!";
                return 0;
            }
            player = 1;
        }

        /*for (int i = 0; i < 14; i++)
        {
            if (i == 7)
                cout << endl;
            cout << ciotole[i] << "\t";
        }*/
    }
}