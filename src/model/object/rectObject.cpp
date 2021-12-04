#include "rectObject.h"
#include "../../view/object/rectObjectView.h"

namespace AGE
{

RectObject::RectObject(Point<float> pos1, Point<float> pos2, std::string fill): 
    ObjectModel { std::make_unique<RectObjectView>(*this) }, 
    _pos1 {pos1}, _pos2 {pos2}, _fill {fill}
{}

RectObject::RectObject(Point<float> pos, float width, float height, std::string fill):
    ObjectModel { std::make_unique<RectObjectView>(*this) },
    _pos1 {pos}, _pos2 { Point<float> {pos.X() + width, pos.Y() + height} }, _fill {fill}
{}

RectObject::~RectObject() {}

void RectObject::setFill(std::string fill) { _fill = fill; }

void RectObject::setPos1(Point<float> pos) { _pos1 = pos; }

void RectObject::setPos2(Point<float> pos) { _pos2 = pos; }

std::string &
RectObject::getFill() noexcept { return _fill; }

Point<float> &
RectObject::getPos1() noexcept { return _pos1; }

Point<float> &
RectObject::getPos2() noexcept { return _pos2; }


const std::string &
RectObject::getFill() const noexcept { return _fill; }

const Point<float> &
RectObject::getPos1() const noexcept { return _pos1; }

const Point<float> &
RectObject::getPos2() const noexcept { return _pos2; }

} // AGE

