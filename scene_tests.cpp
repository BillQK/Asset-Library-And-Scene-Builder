#include "unit_test_framework.h"
#include "scene.hpp"

// Add your Scene, SceneBuilder, SceneObjectTemplate, and SceneObject unit tests
// to this file.
using namespace cs3520;
using namespace std;
TEST(write_your_tests_here)
{
  ASSERT_TRUE(true);
}
TEST(test_scene_objects_templates) { 
  Image img = Image("imgs/crabster.jpg");
  SceneObjectTemplate scene_tmp = SceneObjectTemplate("crabster", img);
  SceneObject scene_obj = SceneObject(1, make_shared<SceneObjectTemplate>(scene_tmp));
}

// TEST(test_add_scene_objects)
// {
//   Scene scenes;

//   SceneObject scene_object = SceneObject(1, )
  
// }

TEST_MAIN()
