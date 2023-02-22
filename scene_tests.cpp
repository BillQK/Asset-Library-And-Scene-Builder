#include "unit_test_framework.h"
#include "scene.hpp"
#include "asset_lib.hpp"
#include "exceptions.hpp"

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
TEST(test_scene_object_template_constructors)
{
  // Test constructor that takes in only a name
  SceneObjectTemplate template1("crab");
  ASSERT_EQUAL(template1.get_name(), "crab");
  ASSERT_EQUAL(int(template1.get_texture().getSize().x), 0);
  ASSERT_EQUAL(int(template1.get_texture().getSize().y), 0);

  // Test constructor that takes in a name and an image
  Image image("imgs/crabster.jpg");
  SceneObjectTemplate template2("crabster", image);
  ASSERT_EQUAL(template2.get_name(), "crabster");
  ASSERT_EQUAL(int(template2.get_texture().getSize().x), 399);
  ASSERT_EQUAL(int(template2.get_texture().getSize().y), 276);
}

TEST(test_scene_object_template_get_set_texture)
{
  Image image("imgs/crabster.jpg");
  SceneObjectTemplate tmpl = SceneObjectTemplate("crabster");
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().x), 0);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().y), 0);

  // Set texture using an image
  tmpl.set_texture(image);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().x), 399);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().y), 276);

  // Set texture to an image with different dimensions
  Image image2("imgs/lobster_link.jpg");
  tmpl.set_texture(image2);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().x), 960);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().y), 338);

  // Set texture to an image with invalid path
  Image invalid_image("invalid/path.jpg");
  tmpl.set_texture(invalid_image);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().x), 0);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().y), 0);
}

TEST(test_scene_object_template_get_name)
{
  SceneObjectTemplate tmpl = SceneObjectTemplate("crab");
  ASSERT_EQUAL(tmpl.get_name(), "crab");

  SceneObjectTemplate tmpl2 = SceneObjectTemplate("starfish");
  ASSERT_EQUAL(tmpl2.get_name(), "starfish");
}
// ----------------------------------------------------------------
// Test SceneObject
TEST(test_SceneObjectConstructor)
{
  shared_ptr<SceneObjectTemplate> sceneObjectTemplate =
      make_shared<SceneObjectTemplate>("crab", Image("imgs/crabster.jpg"));

  // create SceneObject with ID 1 using the template
  SceneObject sceneObject(1, sceneObjectTemplate);

  // check that the ID was set correctly
  ASSERT_EQUAL(sceneObject.get_id(), 1);

  // check that the position is the default position (0, 0)
  ASSERT_EQUAL(sceneObject.get_position(), sf::Vector2f(0, 0));
}

TEST(test_set_position)
{
  shared_ptr<SceneObjectTemplate> sceneObjectTemplate =
      make_shared<SceneObjectTemplate>("crab", Image("imgs/crabster.jpg"));
  SceneObject sceneObject(1, sceneObjectTemplate);

  // set the position to (10, 20)
  sceneObject.set_position(sf::Vector2f(10, 20));

  // check that the position was set correctly
  ASSERT_EQUAL(sceneObject.get_position(), sf::Vector2f(10, 20));
}

TEST(test_draw)
{
  // create a window for testing
  sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

  shared_ptr<SceneObjectTemplate> sceneObjectTemplate =
      make_shared<SceneObjectTemplate>("crab", Image("imgs/crabster.jpg"));

  // create a SceneObject with ID 1 using the template
  SceneObject sceneObject(1, sceneObjectTemplate);

  // set the position to (400, 300)
  sceneObject.set_position(sf::Vector2f(400, 300));

  // draw the object to the window
  sceneObject.draw(window);

  // TODO: add assertions to check that the object was drawn correctly
  ASSERT_TRUE(true);
}

TEST(test_print)
{
  shared_ptr<SceneObjectTemplate> sceneObjectTemplate =
      make_shared<SceneObjectTemplate>("crab", Image("imgs/crabster.jpg"));

  // create a SceneObject with ID 1 using the template
  SceneObject sceneObject(1, sceneObjectTemplate);

  // set the position to (10.5, 20.8)
  sceneObject.set_position(sf::Vector2f(10.5, 20.8));

  // create a stringstream for capturing output
  stringstream ss;

  // print the object to the stringstream
  sceneObject.print(ss);

  // check that the output matches the expected string
  ASSERT_EQUAL(ss.str(), "crab object 1 at position 11, 21\n");
}

// ----------------------------------------------------------------
// Test Scene
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

  try
  {
    scene.remove_scene_obj(2);
  }
  catch (InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Scene object 2 not found"s, e.what());
  }
}

TEST(test_set_scene_obj_position)
{
  Scene scene;
  shared_ptr<SceneObjectTemplate> sceneObjectTemplate =
      make_shared<SceneObjectTemplate>("crab", Image("imgs/crabster.jpg"));
  unique_ptr<SceneObject> sceneObject =
      make_unique<SceneObject>(1, sceneObjectTemplate);

  scene.add_scene_obj(move(sceneObject));

  scene.set_scene_obj_position(1, sf::Vector2f(10.0f, 10.0f));

  stringstream actual;
  stringstream expected;

  expected << "crab object 1 at position "
           << "10, 10" << endl;

  scene.print(actual);

  ASSERT_EQUAL(actual.str(), expected.str());
}

TEST(test_render)
{
  Scene scene;
  shared_ptr<SceneObjectTemplate> sceneObjectTemplate =
      make_shared<SceneObjectTemplate>("crab", Image("imgs/crabster.jpg"));
  unique_ptr<SceneObject> sceneObject =
      make_unique<SceneObject>(1, sceneObjectTemplate);

  scene.add_scene_obj(move(sceneObject));

  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  scene.render(window);
  ASSERT_TRUE(true);
}

// ----------------------------------------------------------------
// Test SceneBuilder
TEST(test_SceneObjectBuilder_create)
{
}

TEST_MAIN()