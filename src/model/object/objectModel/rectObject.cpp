#include "rectObject.h"
#include "../../../view/object/rectObjectView.h"

namespace AGE
{

RectObject::RectObject(vec2d<float> pos1, vec2d<float> pos2, std::string fill): 
    ObjectModel { std::make_unique<RectObjectView>(*this) }, 
    _pos {pos1}, _w {pos2.X() - pos1.X()}, _h {pos2.Y() - pos1.Y()}, _fill {fill}
{}

RectObject::RectObject(vec2d<float> pos, float width, float height, std::string fill):
    ObjectModel { std::make_unique<RectObjectView>(*this) },
    _pos {pos}, _w {width}, _h {height}, _fill {fill}
{}

RectObject::~RectObject() {}

void 
RectObject::setFill(std::string fill) { _fill = fill; }

void 
RectObject::setPosition(vec2d<float> pos) { _pos = pos; }

void 
RectObject::setWidth(float width) { _w = width; }

void 
RectObject::setHeight(float height) { _h = height; }

vec2d<float> &
RectObject::getPosition() { return _pos; }

float 
RectObject::getWidth() const noexcept { return _w; }

float 
RectObject::getHeight() const noexcept { return _h; }

std::string &
RectObject::getFill() noexcept { return _fill; }

const std::string &
RectObject::getFill() const noexcept { return _fill; }

} // AGE

