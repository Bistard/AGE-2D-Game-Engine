#include "ASCIIObject.h"
#include "../../../view/object/asciiObjectView.h"

namespace AGE
{

ASCIIObject::ASCIIObject(Point<float> pos, char ascii): 
    ObjectModel { std::make_unique<ASCIIObjectView>(*this) }, 
    _pos {pos}, _ascii {ascii}
{}

ASCIIObject::~ASCIIObject() {}

void 
ASCIIObject::setPos(Point<float> pos) { _pos = pos; }

Point<float> &
ASCIIObject::getPos() noexcept { return _pos; }

const Point<float> &
ASCIIObject::getPos() const noexcept { return _pos; }

void 
ASCIIObject::setASCII(char ascii) noexcept { _ascii = ascii; }

char
ASCIIObject::getASCII() const noexcept { return _ascii; }

} // AGE

