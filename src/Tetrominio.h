#pragma once

#include "CuadtritoTetris.h"
#include "Renderer.h"

#include <vector>

class Tetrominio
{

public:

    enum Kind {
        I,
        L,
        J,
        O,
        S,
        T,
        Z,
        KindMax
    };

    explicit Tetrominio();
	virtual ~Tetrominio();
    void Copy(Renderer& ren);
    void RotateR();
    void RotateL();
    bool collidesWith(const CuadtritoTetris& cuadtritoIn) const;
    std::vector<CuadtritoTetris>& getCuadtritos() { return cuadtritos; }

    static Tetrominio CreateTetrominio(Renderer& renderer, Kind kind, Color color);

    // KindMax tetrominions, each one having 4 rotations, each one having 4 cuadtritos
    static const std::pair<int, int> tetrominioGrids[KindMax][4][4];

	void SetX(float x);
    float GetX() { return xBase; }
	void SetY(float y);
    float GetY() { return yBase; }
    int GetWidth();

private:
    void UpdateCuadtritosPositions();
    std::vector<CuadtritoTetris> cuadtritos;
    int currentRotationIndex;
    float xBase, yBase;
    Kind kind;

};
