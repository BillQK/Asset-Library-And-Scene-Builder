#ifndef SCENE_HPP
#define SCENE_HPP

// IMPORTANT: You may only modify this file in the places specified
// and in ways allowed by the assignment specification.

#include <string>
#include <memory>
// Add any additional #includes here

#include <SFML/Graphics.hpp>

#include "asset_lib.hpp"

namespace cs3520 {
  class SceneObjectTemplate;
  class SceneObject;

  // Maintains a collection of SceneObjects and provides methods
  // for updating objects in the scene and rendering the scene.
  // TASK: Implement the member functions of the Scene class in scene.cpp
  class Scene {
  public:
    // Adds the given object to the scene.
    // SceneObjects should be created with unique IDs not specified by the user.
    // This method does not check to see whether an object with the same ID
    // exists in the scene. It is up to the programmer to ensure that no duplicate
    // objects are added to the scene.
    //
    // Runtime upper bound: O(n), n=number of objects in the scene
    void add_scene_obj(std::unique_ptr<SceneObject> scene_obj);

    // Removes the object with the specified ID from the scene.
    //
    // Throws InvalidUserInputException with the message "Scene object " + id + " not found"
    // if no such object is in the scene.
    //
    // Runtime upper bounds:
    // - O(log(n)) to find the object, n=number of objects in the scene
    // - O(n) to remove object
    void remove_scene_obj(int id);

    // Sets the position of the object with the specified ID to the given value.
    //
    // Throws InvalidUserInputException with the message "Scene object " + id + " not found"
    // if no such object is in the scene.
    //
    // Runtime upper bound: O(log(n)), n=number of objects in the scene
    void set_scene_obj_position(int id, sf::Vector2f position);

    // Render the scene to the given window by drawing all objects in the scene.
    void render(sf::RenderWindow& window) const;

    // Prints a text represenation of the scene by printing all objects in the scene
    // (using SceneObject::print) to the given stream in order of ID.
    // Each printed scene object should be followed by a newline.
    //
    // Runtime upper bound: O(n), n=number of objects in the scene
    void print(std::ostream& os) const;

  private:
    // ------------ vvvvvvvvvvvv MAKE CHANGES HERE vvvvvvvvvvvvvvvv --------------------
    // Declare any private member variables, private member functions,
    // or transparent comparator functors needed by your implementation here.
    // ------------ ^^^^^^^^^^^^ MAKE CHANGES HERE ^^^^^^^^^^^^^^^^ --------------------
  };

  // Maintains a collection of SceneObjectTemplates.
  // TASK: Implement the member functions of the SceneBuilder class in scene.cpp
  class SceneBuilder {
  public:
    // Returns a vector containing the names of all the available scene object
    // templates, sorted lexicographically.
    //
    // Runtime upper bound: O(n), n=number of templates
    std::vector<std::string> get_scene_object_template_names() const;

    // Creates a scene object template with the given name and initializes it with
    // a texture from the given image.  
    //
    // Throws InvalidUserInputException with the message
    // "Scene object template " + name + " already exists"
    // if a scene object template with that name already exists in the library.
    //
    // Runtime upper bounds:
    // - O(log(n)) to check if a template with that name already exists, n=number of templates
    // - O(n) to add the template
    void create_scene_obj_template(const std::string& name, const cs3520::Image& img);

    // Deletes the scene object template with the given name.
    //
    // Throws InvalidUserInputException with the message
    // "Scene object template " + name + " not found" if no such template exists.
    //
    // Runtime upper bounds:
    // - O(log(n)) to check if a template with that name already exists, n=number of templates
    // - O(n) to delete the template
    void delete_scene_obj_template(const std::string& name);

    // Instantiates a SceneObject from this template.
    //
    // Throws InvalidUserInputException with the message
    // "Scene object template " + name + " not found" if no such template exists.
    //
    // Runtime upper bound: O(log(n)), n=number of templates
    std::unique_ptr<SceneObject> instantiate_scene_obj(
      const std::string& scene_object_template_name,
      int scene_object_id
    ) const;

  private:
    // ------------ vvvvvvvvvvvv MAKE CHANGES HERE vvvvvvvvvvvvvvvv --------------------
    // Declare any private member variables, private member functions,
    // or transparent comparator functors needed by your implementation here.
    // ------------ ^^^^^^^^^^^^ MAKE CHANGES HERE ^^^^^^^^^^^^^^^^ --------------------
  };

  // SceneObjectTemplate instances are the blueprints from which we can
  // create SceneObjects. SceneObjectTemplates have a user-specified name
  // and a texture loaded from an image from our Library.
  class SceneObjectTemplate {
  public:
    // TASK: Implement two constructors. One should take in only a name as a string, and
    // the other should take in a name as a string followed by the cs3520::Image
    // to initialize the template's texture from.
    // ------------ vvvvvvvvvvvv MAKE CHANGES HERE vvvvvvvvvvvvvvvv --------------------
    // ------------ ^^^^^^^^^^^^ MAKE CHANGES HERE ^^^^^^^^^^^^^^^^ --------------------

    // TASK: Implement get_name, get_texture, and set_texture
    // ------------ vvvvvvvvvvvv MAKE CHANGES HERE vvvvvvvvvvvvvvvv --------------------
    const std::string& get_name();
    const sf::Texture& get_texture() const;
    void set_texture(const cs3520::Image& img);
    // ------------ ^^^^^^^^^^^^ MAKE CHANGES HERE ^^^^^^^^^^^^^^^^ --------------------

  private:
    std::string m_name;
    sf::Texture m_texture;
  };

  // An drawable object in a Scene.
  // SceneObjects must have a unique ID, and those IDs start at 1 and
  // increase by one for each instantiated SceneObject. IDs are unique across
  // all SceneObjects.
  //
  // SceneObjects are not deleted when the SceneObjectTemplate from which they
  // were instatiated gets deleted.
  //
  // TASK: Implement the member functions of SceneObject.
  class SceneObject {
  public:
    // Constructs a SceneObject from the given template.
    // It is up to you to decide whether to put the implementation of
    // this constructor here in the .hpp file or in the .cpp file.
    SceneObject(int id, std::shared_ptr<SceneObjectTemplate> tmpl);

    // The implementation of get_id is provided for you.
    int get_id() const { return m_id; }

    // Gets the position of this scene object.
    const sf::Vector2f& get_position() const;
    // Sets the position of this scene object.
    void set_position(const sf::Vector2f& pos);

    // Renders a sprite to the given window.
    // The sprite's texture is specified by the scene object template
    // from which this object was created, and the position
    // of the sprite can be updated by calling set_position on this object.
    //
    // If the SceneObjectTemplate from which this object was created no longer
    // exists, print the message "Template " + m_template_name + " was deleted\n"
    // to cerr instead of drawing this object.
    void draw(sf::RenderWindow& window) const;

    // Prints a text representation of this object to the given stream.
    // The text should follow this format (text in angle brackets should be replaced
    // by the actual values):
    // "<scene object template name> object <scene object id> at position <x>, <y>
    // The coordinates printed should be rounded to the nearest integer.
    // You can use the std::round function defined in the <cmath> library for this.
    // Does not print a trailing newline.
    //
    // If the SceneObjectTemplate from which this object was created no longer
    // exists, print the above text, followed by the message:
    // " (template <scene object template name> was deleted)"
    // to the given stream. Note the single space between the two messages.
    // Does not print a trailing newline in this situation either.
    void print(std::ostream& os) const;

  private:
    int m_id;
    sf::Sprite m_sprite;
    // ------------ vvvvvvvvvvvv MAKE CHANGES HERE vvvvvvvvvvvvvvvv --------------------
    // Add any private member variables you need here.
    // ------------ ^^^^^^^^^^^^ MAKE CHANGES HERE ^^^^^^^^^^^^^^^^ --------------------
  };
}

#endif // SCENE_HPP
