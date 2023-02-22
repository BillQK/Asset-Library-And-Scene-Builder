#include <iostream>
#include <string>
#include "unit_test_framework.h"
#include "scene.hpp"
#include "exceptions.hpp"

// Add your Scene, SceneBuilder, SceneObjectTemplate, and SceneObject unit tests
// to this file.
using namespace std;

TEST(write_your_tests_here)
{
  ASSERT_TRUE(true);
}
// ----------------------------------------------------------------
// Test SceneObjectTemplate
TEST(test_scene_object_template_constructors)
{
  // Test constructor that takes in only a name
  cs3520::SceneObjectTemplate template1("crab");
  ASSERT_EQUAL(template1.get_name(), "crab");
  ASSERT_EQUAL(int(template1.get_texture().getSize().x), 0);
  ASSERT_EQUAL(int(template1.get_texture().getSize().y), 0);

  // Test constructor that takes in a name and an image
  cs3520::Image image("imgs/crabster.jpg");
  cs3520::SceneObjectTemplate template2("crabster", image);
  ASSERT_EQUAL(template2.get_name(), "crabster");
  ASSERT_EQUAL(int(template2.get_texture().getSize().x), 399);
  ASSERT_EQUAL(int(template2.get_texture().getSize().y), 276);
}

TEST(test_scene_object_template_get_set_texture)
{
  cs3520::Image image("imgs/crabster.jpg");
  cs3520::SceneObjectTemplate tmpl = cs3520::SceneObjectTemplate("crabster");
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().x), 0);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().y), 0);

  // Set texture using an image
  tmpl.set_texture(image);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().x), 399);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().y), 276);

  // Set texture to an image with different dimensions
  cs3520::Image image2("imgs/lobster_link.jpg");
  tmpl.set_texture(image2);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().x), 960);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().y), 338);

  // Set texture to an image with invalid path
  cs3520::Image invalid_image("invalid/path.jpg");
  tmpl.set_texture(invalid_image);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().x), 0);
  ASSERT_EQUAL(int(tmpl.get_texture().getSize().y), 0);
}

TEST(test_scene_object_template_get_name)
{
  cs3520::SceneObjectTemplate tmpl = cs3520::SceneObjectTemplate("crab");
  ASSERT_EQUAL(tmpl.get_name(), "crab");

  cs3520::SceneObjectTemplate tmpl2 = cs3520::SceneObjectTemplate("starfish");
  ASSERT_EQUAL(tmpl2.get_name(), "starfish");
}
// ----------------------------------------------------------------
// Test SceneObject
TEST(test_SceneObjectConstructor)
{
  shared_ptr<cs3520::SceneObjectTemplate> sceneObjectTemplate =
      make_shared<cs3520::SceneObjectTemplate>("crab", cs3520::Image("imgs/crabster.jpg"));

  // create SceneObject with ID 1 using the template
  cs3520::SceneObject sceneObject(1, sceneObjectTemplate);

  // check that the ID was set correctly
  ASSERT_EQUAL(sceneObject.get_id(), 1);

  // check that the position is the default position (0, 0)
  ASSERT_EQUAL(sceneObject.get_position(), sf::Vector2f(0, 0));
}

TEST(test_set_position)
{
  shared_ptr<cs3520::SceneObjectTemplate> sceneObjectTemplate =
      make_shared<cs3520::SceneObjectTemplate>("crab", cs3520::Image("imgs/crabster.jpg"));
  cs3520::SceneObject sceneObject(1, sceneObjectTemplate);

  // set the position to (10, 20)
  sceneObject.set_position(sf::Vector2f(10, 20));

  // check that the position was set correctly
  ASSERT_EQUAL(sceneObject.get_position(), sf::Vector2f(10, 20));
}

TEST(test_print)
{
  shared_ptr<cs3520::SceneObjectTemplate> sceneObjectTemplate =
      make_shared<cs3520::SceneObjectTemplate>("crab", cs3520::Image("imgs/crabster.jpg"));

  // create a SceneObject with ID 1 using the template
  cs3520::SceneObject sceneObject(1, sceneObjectTemplate);

  // set the position to (10.5, 20.8)
  sceneObject.set_position(sf::Vector2f(10.5, 20.8));

  // create a stringstream for capturing output
  stringstream ss;

  // print the object to the stringstream
  sceneObject.print(ss);

  // check that the output matches the expected string
  ASSERT_EQUAL(ss.str(), "crab object 1 at position 11, 21");
}

// ----------------------------------------------------------------
// Test Scene
TEST(test_add_scene_obj)
{
  cs3520::Scene scene;
  shared_ptr<cs3520::SceneObjectTemplate> sceneObjectTemplate =
      make_shared<cs3520::SceneObjectTemplate>("crab", cs3520::Image("imgs/crabster.jpg"));
  unique_ptr<cs3520::SceneObject> sceneObject =
      make_unique<cs3520::SceneObject>(1, sceneObjectTemplate);

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
  cs3520::Scene scene;
  shared_ptr<cs3520::SceneObjectTemplate> sceneObjectTemplate =
      make_shared<cs3520::SceneObjectTemplate>("crab", cs3520::Image("imgs/crabster.jpg"));
  unique_ptr<cs3520::SceneObject> sceneObject =
      make_unique<cs3520::SceneObject>(1, sceneObjectTemplate);

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
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Scene object 2 not found"s, e.what());
  }
}

TEST(test_set_scene_obj_position)
{
  cs3520::Scene scene;
  shared_ptr<cs3520::SceneObjectTemplate> sceneObjectTemplate =
      make_shared<cs3520::SceneObjectTemplate>("crab", cs3520::Image("imgs/crabster.jpg"));
  unique_ptr<cs3520::SceneObject> sceneObject =
      make_unique<cs3520::SceneObject>(1, sceneObjectTemplate);

  scene.add_scene_obj(move(sceneObject));

  scene.set_scene_obj_position(1, sf::Vector2f(10.0f, 10.0f));

  stringstream actual;
  stringstream expected;

  expected << "crab object 1 at position "
           << "10, 10" << endl;

  scene.print(actual);

  ASSERT_EQUAL(actual.str(), expected.str());
}

// ----------------------------------------------------------------
// Test SceneBuilder
TEST(test_get_scene_object_template_names)
{
  cs3520::SceneBuilder sceneBuilder;

  sceneBuilder.create_scene_obj_template("crab", cs3520::Image("imgs/crabster.jpg"));
  sceneBuilder.create_scene_obj_template("fish", cs3520::Image("imgs/fishy.jpg"));

  std::vector<std::string> expected = {"crab", "fish"};
  std::vector<std::string> actual = sceneBuilder.get_scene_object_template_names();

  ASSERT_EQUAL(actual, expected);
}

TEST(test_get_scene_object_template_names_sorted)
{
  cs3520::SceneBuilder sceneBuilder;

  // Add scene object templates in unsorted order
  sceneBuilder.create_scene_obj_template("template_c", cs3520::Image("imgs/crabster.jpg"));
  sceneBuilder.create_scene_obj_template("template_a", cs3520::Image("imgs/fishy.jpg"));
  sceneBuilder.create_scene_obj_template("template_b", cs3520::Image("imgs/fishy.jpg"));

  // Get the template names and check if they are sorted in lexicographic order
  std::vector<std::string> templateNames = sceneBuilder.get_scene_object_template_names();
  std::vector<std::string> expectedNames = {"template_a", "template_b", "template_c"};

  ASSERT_EQUAL(templateNames, expectedNames);
}

TEST(test_get_scene_object_template_names_empty)
{
  cs3520::SceneBuilder sceneBuilder;

  // Get the template names and check if they are sorted in lexicographic order
  std::vector<std::string> templateNames = sceneBuilder.get_scene_object_template_names();
  std::vector<std::string> expectedNames = {};

  ASSERT_EQUAL(templateNames, expectedNames);
}

TEST(test_create_scene_obj_template)
{
  cs3520::SceneBuilder builder;
  builder.create_scene_obj_template("crab", cs3520::Image("imgs/crabster.jpg"));

  // Attempt to create a template with the same name
  try
  {
    builder.create_scene_obj_template("crab", cs3520::Image("imgs/crabster.jpg"));
    ASSERT_TRUE(false)
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Scene object template crab already exists"s, e.what());
  }

  // Ensure template was created
  auto names = builder.get_scene_object_template_names();
  ASSERT_EQUAL(names.size(), 1);
  ASSERT_EQUAL("crab", names.at(0));
}
TEST(test_delete_scene_obj_template)
{
  cs3520::SceneBuilder sceneBuilder;
  sceneBuilder.create_scene_obj_template("crab", cs3520::Image("imgs/crabster.jpg"));

  // Verify that template was added successfully
  vector<string> expected_template_names = {"crab"};
  vector<string> actual_template_names = sceneBuilder.get_scene_object_template_names();
  ASSERT_EQUAL(expected_template_names, actual_template_names);

  // Try to delete the template and verify that it was deleted successfully
  sceneBuilder.delete_scene_obj_template("crab");

  expected_template_names = {};
  actual_template_names = sceneBuilder.get_scene_object_template_names();
  ASSERT_EQUAL(expected_template_names, actual_template_names);

  // Try to delete a non-existent template and verify that an exception is thrown
  try
  {
    sceneBuilder.delete_scene_obj_template("non_existent_template");
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Scene object template non_existent_template not found"s, e.what());
  }
}

TEST(test_instantiate_scene_obj)
{
  cs3520::SceneBuilder builder;
  builder.create_scene_obj_template("crab", cs3520::Image("imgs/crabster.jpg"));

  auto obj = builder.instantiate_scene_obj("crab", 1);

  ASSERT_EQUAL(obj->get_id(), 1);
}

TEST_MAIN()