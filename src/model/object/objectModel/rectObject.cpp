#include "rectObject.h"
#include "../../../view/object/rectObjectView.h"

namespace AGE
{

RectObject::RectObject(vec2d<float> pos1, vec2d<float> pos2, std::string fill): 
    ObjectModel { std::make_unique<RectObjectView>(*this) }, 
    _pos1 {pos1}, _pos2 {pos2}, _fill {fill}
{}

RectObject::RectObject(vec2d<float> pos, float width, float height, std::string fill):
    ObjectModel { std::make_unique<RectObjectView>(*this) },
    _pos1 {pos}, _pos2 { vec2d<float> {pos.X() + width, pos.Y() + height} }, _fill {fill}
{}

RectObject::~RectObject() {}

void RectObject::setFill(std::string fill) { _fill = fill; }

void RectObject::setPos1(vec2d<float> pos) { _pos1 = pos; }

void RectObject::setPos2(vec2d<float> pos) { _pos2 = pos; }

std::string &
RectObject::getFill() noexcept { return _fill; }

vec2d<float> &
RectObject::getPos1() noexcept { return _pos1; }

vec2d<float> &
RectObject::getPos2() noexcept { return _pos2; }


const std::string &
RectObject::getFill() const noexcept { return _fill; }

const vec2d<float> &
RectObject::getPos1() const noexcept { return _pos1; }

const vec2d<float> &
RectObject::getPos2() const noexcept { return _pos2; }

vec2d<float> &
RectObject::getPosition() { return _pos1; }

} // AGE

