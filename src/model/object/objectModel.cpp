#include "objectModel.h"
#include "../../common/box.h"
#include "../../common/point.h"
#include "../../common/velocity.h"
#include "../../view/object/objectView.h"

namespace AGE
{

/*******************************************************************************
 * @brief `ObjectModel` implementation
 ******************************************************************************/

ObjectModel::ObjectModel(std::unique_ptr<ObjectView> &&view): _view {std::move(view)} {}

ObjectModel::~ObjectModel() {}

SIZE ObjectModel::getAltitude() const noexcept { return _altitude; }

void ObjectModel::setAltitude(char val) { _altitude = val; }

ObjectView &ObjectModel::getView() const noexcept { return *_view; }

} // AGE

