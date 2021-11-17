//
// Created by nhann on 11/15/2021.
//

#include <iostream>
#include "graphics.h"
#include <iostream>
using namespace std;

#include "Triang.h"

dimensions1::dimensions1() : width(0), height(0) {}
dimensions1::dimensions1(double w, double h) : width(w), height(h) {}

Triang::Triang() : Shape(), size({0,0}){};


Triang::Triang(color fill) : Shape(fill), size({0, 0}) {
}

Triang::Triang(point2D center) : Shape(center), size({0, 0}) {
}

Triang::Triang(color fill, point2D center) : Shape(fill, center), size({0, 0}) {
}

Triang::Triang(double red, double green, double blue, double alpha) : Shape(red, green, blue, alpha), size({0, 0}) {
}

Triang::Triang(double x, double y) : Shape(x, y), size({0, 0}) {
}

Triang::Triang(double red, double green, double blue, double alpha, double x, double y) : Shape(red, green, blue, alpha, x, y), size({0, 0}) {
}

Triang::Triang(color fill, double x, double y) : Shape(fill, x, y), size({0, 0}) {
}

Triang::Triang(double red, double green, double blue, double alpha, point2D center) : Shape(red, green, blue, alpha, center), size({0, 0}) {
}

Triang::Triang(color fill, dimensions1 size) : Shape(fill) {
    setSize(size);
}

Triang::Triang(point2D center, dimensions1 size) : Shape(center) {
    setSize(size);
}

Triang::Triang(color fill, point2D center, dimensions1 size) : Shape(fill, center) {
    setSize(size);
}

Triang::Triang(double red, double green, double blue, double alpha, dimensions1 size) : Shape(red, green, blue, alpha) {
    setSize(size);
}

Triang::Triang(double x, double y, dimensions1 size) : Shape(x, y) {
    setSize(size);
}

Triang::Triang(double red, double green, double blue, double alpha, double x, double y, dimensions1 size) : Shape(red, green, blue, alpha, x, y) {
    setSize(size);
}

Triang::Triang(color fill, double x, double y, dimensions1 size) : Shape(fill, x, y) {
    setSize(size);
}

Triang::Triang(double red, double green, double blue, double alpha, point2D center, dimensions1 size) : Shape(red, green, blue, alpha, center) {
    setSize(size);
}

dimensions1 Triang::getSize() const {
    return size;
}

double Triang::getWidth() const {
    return size.width;
}

double Triang::getHeight() const {
    return size.height;
}

double Triang::getLeftX() const {
    return center.x - (size.width / 2.0);
}

double Triang::getRightX() const {
    return center.x + (size.width / 2.0);
}

double Triang::getTopY() const {
    return center.y - (size.height / 2.0);
    return center.y - (size.height / 2.0);
}

double Triang::getBottomY() const {
    return center.y + (size.height / 2.0);
}

void Triang::setSize(dimensions1 size) {
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}

void Triang::setSize(double width, double height) {
    setSize({width, height});
}

void Triang::setWidth(double width) {
    setSize({width, size.height});
}

void Triang::setHeight(double height) {
    setSize({size.width, height});
}

void Triang::changeSize(double deltaWidth, double deltaHeight) {
    setSize({size.width + deltaWidth, size.height + deltaHeight});
}

void Triang::changeWidth(double delta) {
    setSize({size.width + delta, size.height});
}

void Triang::changeHeight(double delta) {
    setSize({size.width, size.height + delta});
}

void Triang::draw() const {
    glColor3f(fill.red, fill.green, fill.blue);

    glBegin(GL_TRIANGLES);
        //length of top

//    glVertex2i(450, 350);
//    glVertex2i(250, 550);
//    glVertex2i(650, 550);

    glVertex2i(center.x,center.y - size.height/2);
    glVertex2i(center.x -  size.width/2, center.y + size.height/2);
    glVertex2i(center.x + size.width/2, center.y + size.height/2);
//    glVertex2i(center.x - size.width/2, center.y + size.height/2);

    glEnd();

}