//
// Created by angel on 10/11/19.
//

#include "Piece.h"

Piece::Piece(const Point &pointStart) : pointStart(pointStart) {
    this->orientation = VERTICAL;
    this->position = LEFT;
}

void Piece::generatePoints() {
    for (int r = 1; r <= 4; ++r) {
        if (r==1 || r==3){
            for (float n = 0; n <= SIZE_FIG_HEIGHT; n+=1.0) {
                if (r == 1){
                    this->points.push_back(Point(this->pointStart.getPunto()[0],
                            this->pointStart.getPunto()[1] + n));
                    this->pointsTexture.push_back(Point(this->pointStart.getPunto()[0]/WIDTH_FIG,
                            (this->pointStart.getPunto()[1] + n)/HEIGHT_FIG));
                }else{
                    this->points.push_back(Point(this->pointStart.getPunto()[0] + SIZE_FIG_WIDTH,
                            this->pointStart.getPunto()[1] + n));
                    this->pointsTexture.push_back(Point((this->pointStart.getPunto()[0] + SIZE_FIG_WIDTH)/WIDTH_FIG,
                            (this->pointStart.getPunto()[1]+n)/HEIGHT_FIG));
                }
            }
        }else{
            for (int n = 0; n <= SIZE_FIG_WIDTH ; n+=1.0) {
                if (r == 2){
                    this->points.push_back(Point(this->pointStart.getPunto()[0]+ n,
                            this->pointStart.getPunto()[1] + SIZE_FIG_HEIGHT));
                    this->pointsTexture.push_back(Point((this->pointStart.getPunto()[0]+n)/WIDTH_FIG,
                            (this->pointStart.getPunto()[1]+SIZE_FIG_HEIGHT)/HEIGHT_FIG));
                }else{
                    this->points.push_back(Point(this->pointStart.getPunto()[0] + n,
                            this->pointStart.getPunto()[1]));
                    this->pointsTexture.push_back(Point((this->pointStart.getPunto()[0] + n)/WIDTH_FIG,
                            this->pointStart.getPunto()[1]/HEIGHT_FIG));
                }
            }
        }
    }
}

void Piece::translate(float x, float y) {
    for(Point point: this->points){
        point.getPunto()[0]+=x;
        point.getPunto()[1]+=y;
    }
}

const std::vector<Point> &Piece::getPointsTexture() const {
    return pointsTexture;
}

void Piece::setPointsTexture(const std::vector<Point> &pointsTexture) {
    Piece::pointsTexture = pointsTexture;
}

const Point &Piece::getPointStart() const {
    return pointStart;
}

void Piece::setPointStart(const Point &pointStart) {
    Piece::pointStart = pointStart;
}

const std::vector<Point> &Piece::getPoints() const {
    return points;
}

void Piece::setPoints(const std::vector<Point> &points) {
    Piece::points = points;
}
