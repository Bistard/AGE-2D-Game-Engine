#include "objectModel.h"
#include "../../common/box.h"
#include "../../common/point.h"
#include "../../common/velocity.h"
namespace AGE
{

/*******************************************************************************
 * @brief `ObjectModel` implementation
 ******************************************************************************/

ObjectModel::ObjectModel() {}

ObjectModel::~ObjectModel() {}

uint8_t ObjectModel::getAltitude() const noexcept { return _altitude; }

void ObjectModel::setAltitude(char val) { _altitude = val; }

/*******************************************************************************
 * @brief `ObjectDecorator` implementation
 ******************************************************************************/

ObjectDecorator::ObjectDecorator(ObjectModel &object): object {object} {}

ObjectDecorator::~ObjectDecorator() {}

} // AGE

