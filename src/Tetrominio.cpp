#include "Tetrominio.h"
#include "Color.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>

const std::pair<int, int> Tetrominio::tetrominioGrids[Tetrominio::Kind::KindMax][4][4] = {
    // I:
    {
        { { 0, 1 },{ 1, 1 },{ 2, 1 },{ 3, 1 } },
        { { 2, 0 },{ 2, 1 },{ 2, 2 },{ 2, 3 } },
        { { 0, 2 },{ 1, 2 },{ 2, 2 },{ 3, 2 } },
        { { 1, 0 },{ 1, 1 },{ 1, 2 },{ 1, 3 } }
    },
    // L:
    {
        { { 1, 0 },{ 1, 1 },{ 1, 2 },{ 0, 0 } },
        { { 0, 1 },{ 1, 1 },{ 2, 1 },{ 0, 2 } },
        { { 1, 0 },{ 1, 1 },{ 1, 2 },{ 2, 2 } },
        { { 0, 1 },{ 1, 1 },{ 2, 1 },{ 2, 0 } }
    },
    // J:
    {
        { { 1, 0 },{ 1, 1 },{ 1, 2 },{ 0, 2 } },
        { { 0, 1 },{ 1, 1 },{ 2, 1 },{ 2, 2 } },
        { { 1, 0 },{ 1, 1 },{ 1, 2 },{ 2, 0 } },
        { { 0, 1 },{ 1, 1 },{ 2, 1 },{ 0, 0 } }
    },
    // O:
    {
        { { 1, 0 },{ 2, 0 },{ 1, 1 },{ 2, 1 } },
        { { 1, 0 },{ 2, 0 },{ 1, 1 },{ 2, 1 } },
        { { 1, 0 },{ 2, 0 },{ 1, 1 },{ 2, 1 } },
        { { 1, 0 },{ 2, 0 },{ 1, 1 },{ 2, 1 } }
    },
    // S
    {
        { { 0, 1 },{ 1, 1 },{ 1, 0 },{ 2, 0 } },
        { { 1, 0 },{ 1, 1 },{ 2, 1 },{ 2, 2 } },
        { { 0, 2 },{ 1, 2 },{ 1, 1 },{ 2, 1 } },
        { { 0, 0 },{ 0, 1 },{ 1, 1 },{ 1, 2 } }
    },
    // T
    {
        { { 0, 1 },{ 1, 0 },{ 1, 1 },{ 1, 2 } },
        { { 0, 1 },{ 1, 1 },{ 2, 1 },{ 1, 2 } },
        { { 1, 0 },{ 1, 1 },{ 1, 2 },{ 2, 1 } },
        { { 0, 1 },{ 1, 1 },{ 2, 1 },{ 1, 0 } }
    },
    // Z
    {
        { { 1, 0 },{ 1, 1 },{ 0, 1 },{ 0, 2 } },
        { { 0, 1 },{ 1, 1 },{ 1, 2 },{ 2, 2 } },
        { { 2, 0 },{ 2, 1 },{ 1, 1 },{ 1, 2 } },
        { { 0, 0 },{ 1, 0 },{ 1, 1 },{ 2, 1 } }
    }
};

Tetrominio::Tetrominio() : cuadtritos(), currentRotationIndex(0), xBase(0), yBase(0), kind(I)
{
}

Tetrominio::~Tetrominio()
{
}

void Tetrominio::Copy(Renderer & ren)
{
    for (auto& c : cuadtritos)
    {
        c.Copy(ren);
    }
}

void Tetrominio::SetX(float x)
{
	xBase = x;
	UpdateCuadtritosPositions();
}

void Tetrominio::SetY(float y)
{
	yBase = y;
	UpdateCuadtritosPositions();
}

int Tetrominio::GetWidth()
{
    int min = INT_MAX;
    int max = INT_MIN;
    for (auto& c : cuadtritos)
    {
        min = std::min(min, c.GetX());
        max = std::max(max, c.GetX());
    }
    max += CuadtritoTetris::CuadtritoSize;
    return max - min;
}

void Tetrominio::UpdateCuadtritosPositions()
{
    int i = 0;
    for (auto& g : tetrominioGrids[kind][currentRotationIndex])
    {
        CuadtritoTetris& c = cuadtritos[i];
        c.SetX(g.first * CuadtritoTetris::CuadtritoSize + static_cast<int>(xBase));
        c.SetY(g.second * CuadtritoTetris::CuadtritoSize + static_cast<int>(yBase));
        ++i;
    }
}

void Tetrominio::RotateR()
{
    currentRotationIndex = (currentRotationIndex + 3) % 4;
    UpdateCuadtritosPositions();
}

void Tetrominio::RotateL()
{
    currentRotationIndex = (currentRotationIndex + 1) % 4;
    UpdateCuadtritosPositions();
}

bool Tetrominio::collidesWith(const CuadtritoTetris& cuadtritoIn) const
{
    for (auto& c : cuadtritos)
    {
        if (cuadtritoIn.collidesWith(c))
        {
            return true;
        }
    }
    return false;
}

Tetrominio Tetrominio::CreateTetrominio(Renderer& renderer, Kind kind, Color color)
{
    Tetrominio tNew;
    for (auto& g : tetrominioGrids[kind][0])
    {
        CuadtritoTetris c = CuadtritoTetris::CreateCuadtritoTetris(renderer, color);
        c.SetX(g.first * CuadtritoTetris::CuadtritoSize);
        c.SetY(g.second * CuadtritoTetris::CuadtritoSize);
        tNew.cuadtritos.push_back(c);
    }
    tNew.kind = kind;

    return tNew;
}
