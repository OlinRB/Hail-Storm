//
// Created by nhann on 11/15/2021.
//

#ifndef GRAPHICS_STARTER_TRIANG_H
#define GRAPHICS_STARTER_TRIANG_H

#include "shape.h"

struct dimensions1 {
    double width;
    double height;
    dimensions1();
    dimensions1(double w, double h);
    friend std::ostream& operator << (std::ostream& outs, const dimensions1 &d);
};

class Triang : public Shape {
private:
    std::string rotation = "right";
    dimensions1 size;
public:
    Triang();
    explicit Triang(dimensions1 size);
    explicit Triang(color fill);
    explicit Triang(point2D center);

    Triang(color fill, point2D center);
    Triang(double red, double green, double blue, double alpha);
    Triang(double x, double y);
    Triang(double red, double green, double blue, double alpha, double x, double y);
    Triang(color fill, double x, double y);
    Triang(double red, double green, double blue, double alpha, point2D center);
    Triang(color fill, dimensions1 size);
    Triang(point2D center, dimensions1 size);
    Triang(color fill, point2D center, dimensions1 size);
    Triang(double red, double green, double blue, double alpha, dimensions1 size);
    Triang(double x, double y, dimensions1 size);
    Triang(double red, double green, double blue, double alpha, double x, double y, dimensions1 size);
    Triang(color fill, double x, double y, double w, double h);
    Triang(color fill, double x, double y, dimensions1 size, std::string rotation);
    Triang(double red, double green, double blue, double alpha, point2D center, dimensions1 size);


    //Get the size
    dimensions1 getSize() const;
    double getWidth() const;
    double getHeight() const;
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    virtual ~Triang() = default;

    void setSize(dimensions1 size);
    void setSize(double width, double height);
    void setWidth(double width);
    void setHeight(double height);
    void changeSize(double deltaWidth, double deltaHeight);
    void changeWidth(double delta);
    void changeHeight(double delta);

    bool isOverlapping(const Shape &s) const;


    //Draw
    void draw() const override;
};


#endif //GRAPHICS_STARTER_TRIANG_H
