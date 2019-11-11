//
// Created by angel on 10/11/19.
//

#ifndef PRACTICAS_PIECE_H
#define PRACTICAS_PIECE_H

#include "vector"
#include "Utils.h"

class Piece {
private:
    Orientation orientation;
    Position position;
    std::vector<Point> points;
    std::vector<Point> pointsTexture;
    Point pointStart;
public:
    Piece(const Point &pointStart);
    void generatePoints();
    void translate(float x, float y);

    const std::vector<Point> &getPoints() const;

    void setPoints(const std::vector<Point> &points);

    const std::vector<Point> &getPointsTexture() const;

    void setPointsTexture(const std::vector<Point> &pointsTexture);

    const Point &getPointStart() const;

    void setPointStart(const Point &pointStart);
};


#endif //PRACTICAS_PIECE_H
