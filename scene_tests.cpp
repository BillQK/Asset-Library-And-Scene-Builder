#include "unit_test_framework.h"
#include "scene.hpp"
#include "asset_lib.hpp"

// Add your Scene, SceneBuilder, SceneObjectTemplate, and SceneObject unit tests
// to this file.
using namespace std;
using namespace cs3520;
TEST(write_your_tests_here)
{
  ASSERT_TRUE(true);
}
// ----------------------------------------------------------------
// Test SceneObjectTemplate
TEST(test_scene_object_template)
{
  SceneObjectTemplate sceneObjectTemplate = SceneObjectTemplate("empty-scene");
  ASSERT_EQUAL(sceneObjectTemplate.get_name(), "empty-scene");
  ASSERT_EQUAL(sceneObjectTemplate.get_texture().getSize().x, 0.0);
  ASSERT_EQUAL(sceneObjectTemplate.get_texture().getSize().y, 0.0);
}

// ----------------------------------------------------------------
TEST(test_add_scene_obj)
{
  Scene scene;
  shared_ptr<SceneObjectTemplate> sceneObjectTemplate =
      make_shared<SceneObjectTemplate>("crab", Image("imgs/crabster.jpg"));
  unique_ptr<SceneObject> sceneObject =
      make_unique<SceneObject>(1, sceneObjectTemplate);

  scene.add_scene_obj(move(sceneObject));
  stringstream actual;
  stringstream expected;

  expected << "crab object 1 at position "
           << "0, 0" << endl;

  scene.print(actual);

  ASSERT_EQUAL(actual.str(), expected.str());
}

TEST(test_remove_scene_obj)
{
  Scene scene;
  shared_ptr<SceneObjectTemplate> sceneObjectTemplate =
      make_shared<SceneObjectTemplate>("crab", Image("imgs/crabster.jpg"));
  unique_ptr<SceneObject> sceneObject =
      make_unique<SceneObject>(1, sceneObjectTemplate);

  scene.add_scene_obj(move(sceneObject));
  scene.remove_scene_obj(1);

  stringstream actual;
  stringstream expected;

  actual << "";
  scene.print(actual);

  ASSERT_EQUAL(actual.str(), expected.str());
}

TEST_MAIN()