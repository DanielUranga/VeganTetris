#include "Board.h"

#include <algorithm>
#include <iostream>
#include <cmath>
#include "Random.h"

const float Board::fallSpeedIncrement = 0.009f;

Board::Board(Renderer& ren, size_t cols, size_t rows)
    : cuadtritosFijos()
    , cuadtritosBoardRows(rows)
    , ren(ren)
    , lost(false)
    , cols(cols)
    , rows(rows)
    , fallSpeed(0.1f)
    , howManyFramesAgoUpdatedCuadtritosYPos(0)
    , collisionTimer(0)
{
    nextRandomTetro = getRandomBetweenZeroAndLessThan(Tetrominio::Kind::KindMax);
    addNewRandomTetrominio();
    for (size_t x = 0; x < cols; ++x)
    {
        CuadtritoTetris c = CuadtritoTetris::CreateCuadtritoTetris(ren, Color::Esperanza);
        SetCuadtritoPos(c, x, rows - 1);
        cuadtritosFijos.push_back(c);
    }
    for (size_t y = 0; y < rows; ++y)
    {
        CuadtritoTetris c1 = CuadtritoTetris::CreateCuadtritoTetris(ren, Color::Esperanza);
        CuadtritoTetris c2 = CuadtritoTetris::CreateCuadtritoTetris(ren, Color::Esperanza);
        SetCuadtritoPos(c1, 0, y);
        SetCuadtritoPos(c2, cols - 1, y);
        cuadtritosFijos.push_back(c1);
        cuadtritosFijos.push_back(c2);
    }
    background = Texture::CreateTextureFromSurface(ren, Surface::LoadBMP("background.bmp"));
    backgroundRect.x = 0;
    backgroundRect.y = rows * CuadtritoTetris::CuadtritoSize - background.getH();
    backgroundRect.w = background.getW();
    backgroundRect.h = background.getH();
    background.SetBlendMode(SDL_BLENDMODE_BLEND);
    background.SetAlpha(64);
}

Board::~Board()
{
}

void Board::Update(int dt)
{
    if (lost)
    {
        return;
    }
    float howMuchToMove = fallSpeed * dt;
    if (movingDown)
    {
        howMuchToMove = 1.5f * dt;
    }
    bool wasAbleToMove = tryMoveTetrominionTo(currentTetro.GetX(), currentTetro.GetY() + howMuchToMove);
    if (!wasAbleToMove)
    {
        collisionTimer += dt;
        if (collisionTimer > 300)
        {
            onCurrentTetrominioCollided();
            collisionTimer = 0;
        }
    }

    if (howManyFramesAgoUpdatedCuadtritosYPos > 8)
    {
        updateFallingPiecesYPos(dt);
        howManyFramesAgoUpdatedCuadtritosYPos = 0;
    }
    howManyFramesAgoUpdatedCuadtritosYPos++;

}

void Board::Copy(Renderer& ren)
{
    ren.Copy(background, nullptr, &backgroundRect);
    currentTetro.Copy(ren);
    for (auto& c : cuadtritosFijos)
    {
        c.Copy(ren);
    }
    for (auto& row : cuadtritosBoardRows)
    {
        for (auto& c : row)
        {
            c.Copy(ren);
        }
    }
    nextTetro.Copy(ren);
}

void Board::tryMoveLeft()
{
    tryMoveTetrominionTo(currentTetro.GetX() - CuadtritoTetris::CuadtritoSize, currentTetro.GetY());
}

void Board::tryMoveRight()
{
    tryMoveTetrominionTo(currentTetro.GetX() + CuadtritoTetris::CuadtritoSize, currentTetro.GetY());
}

void Board::tryRotateLeft()
{
    currentTetro.RotateL();
    if (currentTetroIsColliding())
    {
        currentTetro.RotateR();
    }
}

void Board::tryRotateRight()
{
    currentTetro.RotateR();
    if (currentTetroIsColliding())
    {
        currentTetro.RotateL();
    }
}

bool Board::tryMoveTetrominionTo(const float x, const float y)
{
    const float prevX = currentTetro.GetX();
    const float prevY = currentTetro.GetY();
    currentTetro.SetX(x);
    currentTetro.SetY(y);
    if (currentTetroIsColliding())
    {
        currentTetro.SetX(prevX);
        currentTetro.SetY(prevY);
        if (fabs(prevY - y) > 1.0)
        {
            return tryMoveTetrominionTo(x, (prevY + y) / 2);
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Board::onCurrentTetrominioCollided()
{
    for (auto& c : currentTetro.getCuadtritos())
    {
        cuadtritosBoardRows[cuadtritoRow(c)].push_back(c);
    }
    checkForNewMadeLine();
    addNewRandomTetrominio();
}

void Board::checkForNewMadeLine()
{
    for (size_t y = 0; y < rows; ++y)
    {
        if (cuadtritosBoardRows[y].size() == cols - 2)
        {
            onNewLineMade(y);
        }
    }
}

void Board::onNewLineMade(size_t rowId)
{
    std::vector<CuadtritoTetris>& row = cuadtritosBoardRows[rowId];
    row.clear();
    for (size_t y2 = rowId; y2 > 0; --y2)
    {
        std::vector<CuadtritoTetris>& a = cuadtritosBoardRows[y2];
        std::vector<CuadtritoTetris>& b = cuadtritosBoardRows[y2 - 1];
        a.insert(a.end(), b.begin(), b.end());
        b.clear();
    }
    fallSpeed += fallSpeedIncrement;
}

size_t Board::cuadtritoRow(CuadtritoTetris& c)
{
    return c.GetY() / CuadtritoTetris::CuadtritoSize;
}

void Board::addNewRandomTetrominio()
{
    currentTetro = Tetrominio::CreateTetrominio(
        ren,
        static_cast<Tetrominio::Kind>(nextRandomTetro),
        static_cast<Color>(nextRandomTetro)
    );
    size_t midX = cols / 2 - 1;
    currentTetro.SetX(static_cast<float>(midX * CuadtritoTetris::CuadtritoSize));
    if (currentTetroIsColliding())
    {
        lost = true;
    }
    nextRandomTetro = getRandomBetweenZeroAndLessThan(Tetrominio::Kind::KindMax);
    updateNextTetroDisplay();
}

void Board::updateNextTetroDisplay()
{
    nextTetro = Tetrominio::CreateTetrominio(
        ren,
        static_cast<Tetrominio::Kind>(nextRandomTetro),
        static_cast<Color>(nextRandomTetro)
    );
    nextTetro.SetX((cols + 2.0f) * CuadtritoTetris::CuadtritoSize - nextTetro.GetWidth() / 2);
    nextTetro.SetY(50.f);
}

void Board::updateFallingPiecesYPos(int dt)
{
    for (size_t y = 0; y < rows; ++y)
    {
        std::vector<CuadtritoTetris>& row = cuadtritosBoardRows[y];
        updateCuadtritosYPos(row, y, dt);
    }
}

void Board::updateCuadtritosYPos(std::vector<CuadtritoTetris>& cuadtritos, size_t yPos, int dt)
{
    int maxPos = yPos * CuadtritoTetris::CuadtritoSize;
    for (auto& c : cuadtritos)
    {
        int nextPos = c.GetY() + 1;
        nextPos = std::min(maxPos, nextPos);
        c.SetY(nextPos);
    }
}

bool Board::currentTetroIsColliding() const
{
    for (auto& c : cuadtritosFijos)
    {
        if (currentTetro.collidesWith(c))
        {
            return true;
        }
    }
    for (auto& row : cuadtritosBoardRows)
    {
        for (auto& c : row)
        {
            if (currentTetro.collidesWith(c))
            {
                return true;
            }
        }
    }
    return false;
}

void Board::SetCuadtritoPos(CuadtritoTetris & c, size_t col, size_t row)
{
    c.SetX(col * CuadtritoTetris::CuadtritoSize);
    c.SetY(row * CuadtritoTetris::CuadtritoSize);
}
