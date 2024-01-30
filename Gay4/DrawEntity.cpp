#include "DrawEntity.h"


void DrawEntity::initVariable()
{
    this->width = 300;
    this->height = 10;
    this->tileSize = 32;
}

void DrawEntity::initTilemap()
{
    //On the ground 32 * 32 --> 10,200 - 10,799
    //On the ground 64 * 64 -->  2,400 - 2,699
    //On the ground 16 * 16 --> 42,000 - 43,200

    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[0][i] = 3;
    }

    for (size_t i = 10800; i <= 11399; i++)
    {
        if (!((i >= 11000) && (i <= 11075)))
        {
            this->Level[0][i] = 1;
        }
        else if (i == 11000)
        {
            this->Level[0][i] = 2;
        }
        else if (i == 11075)
        {
            this->Level[0][i] = 0;
        }
    }
    int Small_g[20] = { 11005, 3852 + this->width * 2 * 2 , 11005 - this->width * 2 * 3 + 3 , 11005 - this->width * 2 * 9 + 34 , 11005 - this->width * 2 * 12 + 42 , 10700 - this->width * 2 * 4 , 10723 - this->width * 2 * 4 };
    for (size_t i = 0; i < 7; i++)
    {
        this->Level[0][Small_g[i] - this->width * 2] = 28;
        this->Level[0][Small_g[i] - this->width * 2 + 1] = 29;
        this->Level[0][Small_g[i] - this->width * 4] = 12;
        this->Level[0][Small_g[i] - this->width * 4 + 1] = 13;
    }
    int sky_G[30] = { 98 + this->width * 2 * 5  , 245 + this->width * 2 * 15 , this->width * 2 * 14 + 90, 10728 - this->width * 2 * 7 };
    int lenght[30] = { 10  , 20 , 15 , 10 };
    for (size_t j = 0; j < 4; j++)
    {
        this->Level[0][sky_G[j]] = 0;
        this->Level[0][sky_G[j] + this->width * 2] = 16;
        this->Level[0][sky_G[j] + this->width * 2 * 2] = 32;
        this->Level[0][sky_G[j] + lenght[j]] = 2;
        this->Level[0][sky_G[j] + this->width * 2 + lenght[j]] = 18;
        this->Level[0][sky_G[j] + this->width * 2 * 2 + lenght[j]] = 34;
        for (size_t i = 1; i < lenght[j]; i++)
        {
            this->Level[0][sky_G[j] + i] = 1;
            this->Level[0][sky_G[j] + this->width * 2 + i] = 17;
            this->Level[0][sky_G[j] + this->width * 2 * 2 + i] = 33;
        }
    }

    int sma[20] = { 257 + this->width * 2 * 9 };
    int lenght_0[20] = { 3 };
    for (size_t j = 0; j < 1; j++)
    {
        this->Level[0][sma[j]] = 255 - 48 - 15;
        this->Level[0][sma[j] + lenght_0[j]] = 255 - 48 - 15 + 2;
        for (size_t i = 1; i < lenght_0[j]; i++)
        {
            this->Level[0][sma[j] + i] = 255 - 48 - 15 + 1;

        }
    }


    int Lean[10] = { 11005 - this->width * 2 * 10 + 9 };
    this->Level[0][Lean[0] + this->width * 2 * 3] = 84;
    this->Level[0][Lean[0] + this->width * 2 * 3 + 4] = 86;
    this->Level[0][Lean[0] + this->width * 2 * 3 + 5] = 87;
    this->Level[0][Lean[0] + this->width * 2 * 4] = 100;
    this->Level[0][Lean[0] + this->width * 2 * 5] = 116;
    this->Level[0][Lean[0] + this->width * 2 * 4 + 4] = 102;
    this->Level[0][Lean[0] + this->width * 2 * 4 + 5] = 103;
    this->Level[0][Lean[0] + this->width * 2 * 5 + 1] = 117;
    this->Level[0][Lean[0] + this->width * 2 * 5 + 2] = 117;
    this->Level[0][Lean[0] + this->width * 2 * 5 + 3] = 117;
    this->Level[0][Lean[0] + this->width * 2 * 5 + 4] = 118;
    this->Level[0][Lean[0] + this->width * 2 * 5 + 5] = 119;
    this->Level[0][Lean[0] + this->width * 2 * 3 + 6] = 122;
    this->Level[0][Lean[0] + this->width * 2 * 2 + 6] = 102;
    this->Level[0][Lean[0] + this->width * 2 * 1 + 6] = 86;
    this->Level[0][Lean[0] + this->width * 2 * 4 + 6] = 141;
    this->Level[0][Lean[0] + this->width * 2 * 5 + 6] = 255;
    for (size_t i = 1; i < 12; i++)
    {
        this->Level[0][Lean[0] + this->width * 2 * 3 + 6 + i] = 119;
        this->Level[0][Lean[0] + this->width * 2 * 2 + 6 + i] = 103;
        this->Level[0][Lean[0] + this->width * 2 * 1 + 6 + i] = 87;
    }
    this->Level[0][Lean[0] + this->width * 2 * 1 + 6 + 12] = 255 - 32;
    this->Level[0][Lean[0] + this->width * 2 * 2 + 6 + 12] = 255 - 16;
    this->Level[0][Lean[0] + this->width * 2 * 3 + 6 + 12] = 255;


    for (size_t i = 11400; i <= 11999; i++)
    {
        if (!((i >= 11600) && (i <= 11675)))
        {
            this->Level[0][i] = 17;
        }
        else if ((i == 11600))
        {
            this->Level[0][i] = 18;
        }
        else if (i == 11675)
        {
            this->Level[0][i] = 16;
        }
    }


    int Ancient = 10260;
    this->Level[0][Ancient + this->width * 2] = 122;
    this->Level[0][Ancient] = 122 - 16;
    this->Level[0][Ancient - this->width * 2] = 122 - 16;
    this->Level[0][Ancient - this->width * 2 * 2] = 118 - 32;
    for (size_t i = 1; i <= 5; i++)
    {
        this->Level[0][Ancient - this->width * 2 * 2 + i] = 118 - 32 + 1;
        this->Level[0][Ancient - this->width * 2 + i] = 118 - 16 + 1;
        this->Level[0][Ancient + i] = 118 - 16 + 1;
        this->Level[0][Ancient + this->width * 2 + i] = 118 - 16 + 1;
    }
    this->Level[0][Ancient - this->width * 2 * 2 + 6] = 122;
    this->Level[0][Ancient - this->width * 2 * 3 + 6] = 122 - 16;
    this->Level[0][Ancient - this->width * 2 * 4 + 6] = 122 - 16;
    this->Level[0][Ancient - this->width * 2 * 5 + 6] = 122 - 16;
    this->Level[0][Ancient - this->width * 2 * 6 + 6] = 122 - 16;
    this->Level[0][Ancient - this->width * 2 * 7 + 6] = 118 - 32;
    for (size_t i = 1; i <= 16; i++)
    {
        this->Level[0][Ancient - this->width * 2 * 4 + 6 + i] = 118 - 16 + 1;
        this->Level[0][Ancient - this->width * 2 * 5 + 6 + i] = 118 - 16 + 1;
        this->Level[0][Ancient - this->width * 2 * 6 + 6 + i] = 118 - 16 + 1;
        this->Level[0][Ancient - this->width * 2 * 7 + 6 + i] = 118 - 32 + 1;
        this->Level[0][Ancient + this->width * 2 * 2 + 6 + i] = 3;
        this->Level[0][Ancient + this->width * 2 + 6 + i] = 3;
        if (i == 16)
        {
            this->Level[0][Ancient - this->width * 2 * 7 + 6 + i + 1] = 255 - 32; this->Level[0][Ancient - this->width * 2 * 6 + 6 + i + 1] = 255 - 16; this->Level[0][Ancient - this->width * 2 * 5 + 6 + i + 1] = 255 - 16; this->Level[0][Ancient - this->width * 2 * 4 + 6 + i + 1] = 255 - 16; this->Level[0][Ancient - this->width * 2 * 3 + 6 + i + 1] = 255;
        }
    }
    for (size_t i = 16; i < 46; i++)
    {
        this->Level[0][Ancient + this->width * 2 * 2 + 6 + i] = 3;
        this->Level[0][Ancient + this->width * 2 + 6 + i] = 3;
    }
    this->Level[0][Ancient + this->width * 2 + 6 + 46] = 0;
    this->Level[0][Ancient + this->width * 2 * 2 + 6 + 46] = 16;
    this->Level[0][Ancient - this->width * 2 + 6] = 125;
    this->Level[0][Ancient - this->width * 2 + 7] = 126;
    this->Level[0][Ancient - this->width * 2 + 8] = 255;
    this->Level[0][Ancient - this->width * 2 * 2 + 8] = 141;
    this->Level[0][Ancient - this->width * 2 * 3 + 8] = 125;
    this->Level[0][Ancient - this->width * 2 * 3 + 7] = 17; this->Level[0][Ancient - this->width * 2 * 2 + 7] = 17;

    for (size_t i = 1; i <= 14; i++)
    {
        this->Level[0][Ancient - this->width * 2 * 3 + 8 + i] = 254;
    }

    this->Level[0][Ancient + 6] = 141;
    this->Level[0][Ancient + this->width * 2 + 6] = 141;
    this->Level[0][Ancient + this->width * 2 * 2 + 6] = 141;
    this->Level[0][Ancient + this->width * 2 * 3 + 6] = 141;

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 11; j++)
        {
            this->Level[0][i * 600 + 3098 + j] = 3;
        }
    }

    if (!tilemaps[0].loadFromResource("./Entity/MIXED.png", sf::Vector2u(tileSize, tileSize), this->Level[0], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }


    //_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[1][i] = 0;
    }

    for (size_t i = 0; i < 10800; i = i + 4)
    {
        if (this->Level[0][i + this->width * 2] >= 0 && this->Level[0][i + this->width * 2] <= 2)
        {
            int random_numb = std::rand() % 6;
            if (random_numb == 0 && this->Level[0][i + 1 + this->width * 2] != 3)
            {
                this->Level[1][i] = 10;
                this->Level[1][i + 1] = 11;
            }
            else if (random_numb == 1 && this->Level[0][i + 1 + this->width * 2] != 3 && this->Level[0][i + 2 + this->width * 2] != 3)
            {
                this->Level[1][i - this->width * 2] = 3;
                this->Level[1][i] = 13;
                this->Level[1][i + 1] = 14;
                this->Level[1][i + 2] = 15;
            }
            else if (random_numb == 2 && this->Level[0][i + 1 + this->width * 2] != 3 && this->Level[0][i + 2 + this->width * 2] != 3 && this->Level[0][i + 3 + this->width * 2] != 3)
            {
                this->Level[1][i] = 16;
                this->Level[1][i - this->width * 2 + 2] = 8;
                this->Level[1][i + 1] = 17;
                this->Level[1][i + 2] = 18;
                this->Level[1][i + 3] = 19;
            }
            else
            {
                this->Level[1][i] = 1;
            }
        }

    }
    if (!tilemaps[1].loadFromResource("./Entity/GRASS.png", sf::Vector2u(32, 32), this->Level[1], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }


    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________


    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[2][i] = 0;
    }
    //Last array - width = Last position
    int Well[20] = { 10250 , 10796 , 162 + this->width * 2 * 17 ,  13 + this->width * 2 * 17 ,  253 + this->width * 2 * 14 };

    for (size_t i = 0; i < 5; i++)
    {
        this->Level[2][Well[i] - this->width * 4] = 1;
        this->Level[2][Well[i] - this->width * 4 + 1] = 2;
        this->Level[2][Well[i] - this->width * 4 + 2] = 3;
        this->Level[2][Well[i] - this->width * 4 + 3] = 4;
        this->Level[2][Well[i] - this->width * 2] = 6;
        this->Level[2][Well[i] - this->width * 2 + 1] = 7;
        this->Level[2][Well[i] - this->width * 2 + 2] = 8;
        this->Level[2][Well[i] - this->width * 2 + 3] = 9;
        this->Level[2][Well[i]] = 11;
        this->Level[2][Well[i] + 1] = 12;
        this->Level[2][Well[i] + 2] = 13;
        this->Level[2][Well[i] + 3] = 14;
    }


    if (!tilemaps[2].loadFromResource("./Entity/NIGGA.png", sf::Vector2u(32, 32), this->Level[2], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }


    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________


    int level_U[3000];
    int Houset_1[20] = { 2415 };

    for (size_t i = 0; i < 3000; i++)
    {
        level_U[i] = 0;
    }

    for (size_t i = 0; i < 1; i++)
    {
        level_U[Houset_1[0] - this->width * 6] = 10;
        level_U[Houset_1[0] - this->width * 6 + 1] = 11;
        level_U[Houset_1[0] - this->width * 6 + 2] = 12;
        level_U[Houset_1[0] - this->width * 6 + 3] = 13;
        level_U[Houset_1[0] - this->width * 6 + 4] = 14;
        level_U[Houset_1[0] - this->width * 6 + 5] = 15;
        level_U[Houset_1[0] - this->width * 5] = 18;
        level_U[Houset_1[0] - this->width * 5 + 1] = 19;
        level_U[Houset_1[0] - this->width * 5 + 2] = 20;
        level_U[Houset_1[0] - this->width * 5 + 3] = 21;
        level_U[Houset_1[0] - this->width * 5 + 4] = 22;
        level_U[Houset_1[0] - this->width * 5 + 5] = 23;
        level_U[Houset_1[0] - this->width * 4] = 26;
        level_U[Houset_1[0] - this->width * 4 + 1] = 27;
        level_U[Houset_1[0] - this->width * 4 + 2] = 28;
        level_U[Houset_1[0] - this->width * 4 + 3] = 29;
        level_U[Houset_1[0] - this->width * 4 + 4] = 30;
        level_U[Houset_1[0] - this->width * 4 + 5] = 31;
        level_U[Houset_1[0] - this->width * 3] = 34;
        level_U[Houset_1[0] - this->width * 3 + 1] = 35;
        level_U[Houset_1[0] - this->width * 3 + 2] = 36;
        level_U[Houset_1[0] - this->width * 3 + 3] = 37;
        level_U[Houset_1[0] - this->width * 3 + 4] = 38;
        level_U[Houset_1[0] - this->width * 3 + 5] = 39;
        level_U[Houset_1[0] - this->width * 2] = 42;
        level_U[Houset_1[0] - this->width * 2 + 1] = 43;
        level_U[Houset_1[0] - this->width * 2 + 2] = 44;
        level_U[Houset_1[0] - this->width * 2 + 3] = 45;
        level_U[Houset_1[0] - this->width * 2 + 4] = 46;
        level_U[Houset_1[0] - this->width * 2 + 5] = 47;
        level_U[Houset_1[0] - this->width] = 50;
        level_U[Houset_1[0] - this->width + 1] = 51;
        level_U[Houset_1[0] - this->width + 2] = 52;
        level_U[Houset_1[0] - this->width + 3] = 53;
        level_U[Houset_1[0] - this->width + 4] = 54;
        level_U[Houset_1[0] - this->width + 5] = 55;
        level_U[Houset_1[0]] = 58;
        level_U[Houset_1[0] + 1] = 59;
        level_U[Houset_1[0] + 2] = 60;
        level_U[Houset_1[0] + 3] = 61;
        level_U[Houset_1[0] + 4] = 62;
        level_U[Houset_1[0] + 5] = 63;
    }

    if (!tilemaps[3].loadFromResource("./Entity/BUIDING_L.png", sf::Vector2u(64, 64), level_U, this->width, this->height))
    {
        std::cout << "Error" << "\n";
    }

    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________
    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[3][i] = 3;
    }

    int TREE1[10] = { this->width * 2 * 17 + 27 , this->width * 2 * 9 + 75,  this->width * 2 * 4 + 100, this->width * 2 * 17 + 115 , this->width * 2 * 17 + 160 , this->width * 2 * 17 + 190 };
    int TREE2[10] = { this->width * 2 * 17 + 20 , this->width * 2 * 14 + 60 , this->width * 2 * 17 + 120  , this->width * 2 * 17 + 155 ,this->width * 2 * 9 + 68 };
    for (size_t i = 0; i < 6; i++)
    {
        this->Level[3][TREE1[i]] = 46; this->Level[3][TREE1[i] - this->width * 2] = 46 - 11; this->Level[3][TREE1[i] - this->width * 2 * 2] = 46 - 22; this->Level[3][TREE1[i] - this->width * 2 * 3] = 46 - 33;
        this->Level[3][TREE1[i] - this->width * 2 + 1] = 46 - 11 + 1; this->Level[3][TREE1[i] - this->width * 2 * 2 + 1] = 46 - 22 + 1; this->Level[3][TREE1[i] - this->width * 2 * 3 + 1] = 46 - 33 + 1;
        this->Level[3][TREE1[i] - this->width * 2 - 1] = 46 - 11 - 1; this->Level[3][TREE1[i] - this->width * 2 * 2 - 1] = 46 - 22 - 1; this->Level[3][TREE1[i] - this->width * 2 * 3 - 1] = 46 - 33 - 1;
        this->Level[3][TREE1[i] - this->width * 2 + 2] = 46 - 11 + 2; this->Level[3][TREE1[i] - this->width * 2 * 2 + 2] = 46 - 22 + 2; this->Level[3][TREE1[i] - this->width * 2 * 3 + 2] = 46 - 33 + 2;
        this->Level[3][TREE1[i] - this->width * 2 - 2] = 46 - 11 - 2; this->Level[3][TREE1[i] - this->width * 2 * 2 - 2] = 46 - 22 - 2; this->Level[3][TREE1[i] - this->width * 2 * 3 - 2] = 46 - 33 - 2;
    }
    for (size_t i = 0; i < 5; i++)
    {
        this->Level[3][TREE2[i]] = 51; this->Level[3][TREE2[i] - this->width * 2] = 51 - 11; this->Level[3][TREE2[i] - this->width * 2 * 2] = 51 - 22; this->Level[3][TREE2[i] - this->width * 2 * 3] = 51 - 33; this->Level[3][TREE2[i] - this->width * 2 * 4] = 51 - 44;
        this->Level[3][TREE2[i] - this->width * 2 + 1] = 51 - 11 + 1; this->Level[3][TREE2[i] - this->width * 2 * 2 + 1] = 51 - 22 + 1; this->Level[3][TREE2[i] - this->width * 2 * 3 + 1] = 51 - 33 + 1; this->Level[3][TREE2[i] - this->width * 2 * 4 + 1] = 51 - 44 + 1;
        this->Level[3][TREE2[i] - this->width * 2 + 2] = 51 - 11 + 2; this->Level[3][TREE2[i] - this->width * 2 * 2 + 2] = 51 - 22 + 2; this->Level[3][TREE2[i] - this->width * 2 * 3 + 2] = 51 - 33 + 2;
        this->Level[3][TREE2[i] - this->width * 2 - 1] = 51 - 11 - 1; this->Level[3][TREE2[i] - this->width * 2 * 2 - 1] = 51 - 22 - 1; this->Level[3][TREE2[i] - this->width * 2 * 3 - 1] = 51 - 33 - 1; this->Level[3][TREE2[i] - this->width * 2 * 4 - 1] = 51 - 44 - 1;
        this->Level[3][TREE2[i] - this->width * 2 - 2] = 51 - 11 - 2; this->Level[3][TREE2[i] - this->width * 2 * 2 - 2] = 51 - 22 - 2; this->Level[3][TREE2[i] - this->width * 2 * 3 - 2] = 51 - 33 - 2; this->Level[3][TREE2[i] - this->width * 2 * 4 - 2] = 51 - 44 - 2;
    }
    for (size_t i = 0; i < 5; i++)
    {
        for(size_t j = 0; j < 6; j++)
        {
            this->Level[3][600 * i + 98 + j] = 3;
        }
    }

    if (!tilemaps[4].loadFromResource("./Entity/TREE.png", sf::Vector2u(32, 32), this->Level[3], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }


    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________

    int type_1[10] = { this->width * 2 * 13 + 64 , this->width * 2 * 12 + 96, this->width * 2 * 10 + 96 };
    int type_2[10] = { this->width * 2 * 14 + 62 ,  this->width * 2 * 13 + 91 ,  this->width * 2 * 13 + 95 ,this->width * 2 * 12 + 92,this->width * 2 * 11 + 94 ,this->width * 2 * 8 + 229 , 10750 , 10715 };

    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[4][i] = 2;
    }

    //type_1
    for (size_t i = 0; i < 3; i++)
    {
        this->Level[4][type_1[i]] = 0;
        this->Level[4][type_1[i] + 1] = 1;
    }

    //type_2
    for (size_t i = 0; i < 8; i++)
    {
        this->Level[4][type_2[i]] = 3;
        this->Level[4][type_2[i] + 1] = 4;
        this->Level[4][type_2[i] + 2] = 5;
        this->Level[4][type_2[i] + 3] = 6;
    }


    if (!tilemaps[5].loadFromResource("./Entity/WOOD_GROUND.png", sf::Vector2u(32, 32), this->Level[4], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }


    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[5][i] = 0;
    }



    for (size_t i = 350 + this->width * 2 * 17; i <= 491 + this->width * 2 * 17; i = i + 2)
    {
        if (this->Level[0][i + this->width * 2] >= 0 && this->Level[0][i + this->width * 2] <= 2)
        {
            int random_num = std::rand() % 8;
            if (random_num == 0)
            {
                this->Level[5][i] = 8;
                this->Level[5][i + 1] = 9;
            }
            else if (random_num == 1)
            {
                this->Level[5][i - this->width * 2] = 2;
                this->Level[5][i + 1 - this->width * 2] = 3;
                this->Level[5][i] = 10;
                this->Level[5][i + 1] = 11;
            }
            else if (random_num == 2)
            {
                this->Level[5][i - this->width * 2] = 4;
                this->Level[5][i + 1 - this->width * 2] = 5;
                this->Level[5][i] = 12;
                this->Level[5][i + 1] = 13;
            }
            else if (random_num == 3)
            {
                this->Level[5][i - this->width * 2] = 6;
                this->Level[5][i + 1 - this->width * 2] = 7;
                this->Level[5][i] = 14;
                this->Level[5][i + 1] = 15;
            }
            else
            {
                this->Level[5][i] = 0;
            }
        }
        else
        {
            this->Level[5][i] = 0;
        }

    }


    if (!tilemaps[6].loadFromResource("./Entity/GRAVE.png", sf::Vector2u(32, 32), this->Level[5], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }


    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________

    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[6][i] = 0;
    }

    int R_1[10] = { this->width * 2 * 17 + 130 , this->width * 2 * 17 + 140 , this->width * 2 * 17 + 136 , this->width * 2 * 17 + 130 + 15 , this->width * 2 * 17 + 140 + 15 , this->width * 2 * 17 + 136 + 15 , this->width * 2 * 17 + 130 + 40 , this->width * 2 * 17 + 140 + 40 , this->width * 2 * 17 + 136 + 40 };
    int R_2[10] = { this->width * 2 * 17 + 131 , this->width * 2 * 17 + 139 , this->width * 2 * 17 + 135 , this->width * 2 * 17 + 131 + 15 , this->width * 2 * 17 + 139 + 15 , this->width * 2 * 17 + 135 + 15 , this->width * 2 * 17 + 131 + 40 , this->width * 2 * 17 + 139 + 40 , this->width * 2 * 17 + 135 + 40 };
    int R_3[10] = { this->width * 2 * 17 + 132 , this->width * 2 * 17 + 141 , this->width * 2 * 17 + 137 , this->width * 2 * 17 + 132 + 15 , this->width * 2 * 17 + 141 + 15 , this->width * 2 * 17 + 137 + 15 , this->width * 2 * 17 + 132 + 40 , this->width * 2 * 17 + 141 + 40 , this->width * 2 * 17 + 137 + 40 };
    int R_4[10] = { this->width * 2 * 17 + 133 , this->width * 2 * 17 + 143 , this->width * 2 * 17 + 138 , this->width * 2 * 17 + 133 + 15 , this->width * 2 * 17 + 143 + 15 , this->width * 2 * 17 + 138 + 15 , this->width * 2 * 17 + 133 + 40 , this->width * 2 * 17 + 143 + 40 , this->width * 2 * 17 + 138 + 40 };
    int R_5[10] = { this->width * 2 * 17 + 134 , this->width * 2 * 17 + 145 , this->width * 2 * 17 + 147 , this->width * 2 * 17 + 134 + 15 , this->width * 2 * 17 + 145 + 15 , this->width * 2 * 17 + 147 + 15 , this->width * 2 * 17 + 134 + 40 , this->width * 2 * 17 + 145 + 40 , this->width * 2 * 17 + 147 + 40 };

    for (size_t i = 0; i < 9; i++)
    {
        //R-1
        this->Level[6][R_1[i] - this->width * 2] = 1;
        this->Level[6][R_1[i]] = 7;

        //R-2
        this->Level[6][R_2[i] - this->width * 2] = 2;
        this->Level[6][R_2[i]] = 8;

        //R-3
        this->Level[6][R_3[i] - this->width * 2] = 3;
        this->Level[6][R_3[i]] = 9;

        //R-4
        this->Level[6][R_4[i] - this->width * 2] = 4;
        this->Level[6][R_4[i]] = 10;

        //R-5
        this->Level[6][R_5[i] - this->width * 2] = 5;
        this->Level[6][R_5[i]] = 11;
    }


    if (!tilemaps[7].loadFromResource("./Entity/RICE.png", sf::Vector2u(32, 32), this->Level[6], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }

    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________


    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[7][i] = 29;
    }

    int Olantern[10] = { 43 + this->width * 2 * 17 , 150 + this->width * 2 * 17 , 127 + this->width * 2 * 17 };
    int Puppet[10] = { 46 + this->width * 2 * 17 };
    for (size_t i = 0; i < 3; i++)
    {
        this->Level[7][Olantern[i]] = 20;
        this->Level[7][Olantern[i] + 1] = 21;
        this->Level[7][Olantern[i] - this->width * 2] = 10;
        this->Level[7][Olantern[i] - this->width * 2 + 1] = 11;
        this->Level[7][Olantern[i] - this->width * 2 * 2] = 0;
        this->Level[7][Olantern[i] - this->width * 2 * 2 + 1] = 1;
    }

    for (size_t i = 0; i < 1; i++)
    {
        this->Level[7][Puppet[i]] = 22;
        this->Level[7][Puppet[i] + 1] = 23;
        this->Level[7][Puppet[i] - this->width * 2] = 12;
        this->Level[7][Puppet[i] - this->width * 2 + 1] = 13;
        this->Level[7][Puppet[i] - this->width * 2 * 2] = 2;
        this->Level[7][Puppet[i] - this->width * 2 * 2 + 1] = 3;
    }



    if (!tilemaps[8].loadFromResource("./Entity/PROP_S.png", sf::Vector2u(32, 32), this->Level[7], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }
    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________

    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[8][i] = 0;
    }

    int MARRY[10] = { 50 + this->width * 2 * 14 , 596 + this->width * 2 * 14 };

    for (size_t i = 0; i < 2; i++)
    {
        this->Level[8][MARRY[i]] = 6;
        this->Level[8][MARRY[i] + 1] = 7;
        this->Level[8][MARRY[i] + 1 - this->width * 2] = 4;
        this->Level[8][MARRY[i] + 1 - this->width * 2 * 2] = 1;
    }



    if (!tilemaps[9].loadFromResource("./Entity/MARRY.png", sf::Vector2u(32, 32), this->Level[8], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }
    //______________________________________________________________________________________________________________________________________________________________________________________________________________________________________


    for (size_t i = 0; i < 12000; i++)
    {
        this->Level[9][i] = 3;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (size_t i = 0; i < 12000; i++)
    {
        if (this->Level[0][i + this->width * 2] >= 0 && this->Level[0][i + this->width * 2] <= 2 || this->Level[0][i + this->width * 2] == 118 - 32 + 1)
        {
            int random_number = std::rand() % 12;
            this->Level[9][i] = random_number;
        }
        else
        {
            this->Level[9][i] = 3;
        }
    }



    if (!tilemaps[10].loadFromResource("./Entity/GRASS_XD.png", sf::Vector2u(32, 32), this->Level[9], this->width * 2, this->height * 2))
    {
        std::cout << "Error" << "\n";
    }
}

DrawEntity::DrawEntity(sf::RenderWindow& window) : window(window) {
    initVariable();
    initTilemap();
}

DrawEntity::~DrawEntity()
{

}

void DrawEntity::render()
{
    for (size_t i = 0; i < 11; i++) {
        window.draw(tilemaps[i], sf::RenderStates::Default);
    }
}
