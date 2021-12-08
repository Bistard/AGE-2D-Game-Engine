#include "ASCIIObject.h"
#include "../../../view/object/asciiObjectView.h"

namespace AGE
{

ASCIIObject::ASCIIObject(vec2d<float> pos, char ascii): 
    ObjectModel { std::make_unique<ASCIIObjectView>(*this) }, 
    _pos {pos}, _ascii {ascii}
{}

ASCIIObject::~ASCIIObject() {}

void 
ASCIIObject::setPos(vec2d<float> pos) { _pos = pos; }

vec2d<float> &
ASCIIObject::getPos() noexcept { return _pos; }

const vec2d<float> &
ASCIIObject::getPos() const noexcept { return _pos; }

void 
ASCIIObject::setASCII(char ascii) noexcept { _ascii = ascii; }

char
ASCIIObject::getASCII() const noexcept { return _ascii; }

vec2d<float> &
ASCIIObject::getPosition() { return _pos; }

} // AGE

