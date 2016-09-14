#pragma once

#include "Tetrominio.h"
#include "Renderer.h"

#include <vector>
#include <map>

class Board
{
public:
    Board(Renderer& ren, size_t rows, size_t cols);
    ~Board();
    void Update(int dt);
    void Copy(Renderer& ren);
    void tryMoveLeft();
    void tryMoveRight();
    void tryRotateLeft();
    void tryRotateRight();
    void startMoveDown() { movingDown = true; };
    void stopMoveDown() { movingDown = false; };
    bool tryMoveTetrominionTo(const float x, const float y);
private:
    bool currentTetroIsColliding() const;
    void SetCuadtritoPos(CuadtritoTetris& c, size_t col, size_t row);
    void onCurrentTetrominioCollided();
    void checkForNewMadeLine();
    void onNewLineMade(size_t rowId);
    static size_t cuadtritoRow(CuadtritoTetris& c);
    void addNewRandomTetrominio();
    void updateNextTetroDisplay();
    void updateFallingPiecesYPos(int dt);
    void updateCuadtritosYPos(std::vector<CuadtritoTetris>& cuadtritos, size_t yPos, int dt);

    static const float fallSpeedIncrement;
    float fallSpeed;
    bool lost;
    Tetrominio currentTetro;
    Tetrominio nextTetro;
    std::vector<CuadtritoTetris> cuadtritosFijos;
    std::vector<std::vector<CuadtritoTetris>> cuadtritosBoardRows;
    Renderer& ren;
    const size_t cols, rows;
    bool movingDown;
    int nextRandomTetro;
    size_t howManyFramesAgoUpdatedCuadtritosYPos;
    size_t collisionTimer;
    Texture background;
    SDL_Rect backgroundRect;
};
