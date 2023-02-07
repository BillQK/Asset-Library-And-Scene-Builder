#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cmath>  // For std::round
// Add any additional #includes here

#include <SFML/Graphics.hpp>

#include "scene.hpp"
#include "asset_lib.hpp"
#include "exceptions.hpp"


namespace cs3520 {
  // TASK: Implement the Scene member functions.

  // --------------------------------------------------------------------------------------------

  // TASK: Implement the SceneBuilder member functions.

  // --------------------------------------------------------------------------------------------

  // TASK: Implement the SceneObjectTemplate constructor(s) and member functions.
  // You must decide which of those can go in the .hpp file and which should
  // go here in the .cpp file.

  // --------------------------------------------------------------------------------------------

  // Non-const static member variables have to be initialized in the .cpp file.
  // Note that the first SceneObject created should have an ID of 1.
  // You can use the prefix-increment operator (++i) to accomplish this
  // in a member initializer list.
  int SceneObject::object_id = 0;

  // TASK: Implement the SceneObject member functions.
}
