#include <algorithm>
#include <cmath>  // For std::round
#include <iostream>
#include <memory>
#include <string>
// Add any additional #includes here
#include <SFML/Graphics.hpp>

#include "asset_lib.hpp"
#include "exceptions.hpp"
#include "scene.hpp"

using namespace std;
namespace {
  template <typename Container>
  // find scene object of given id & if it's not found, throws exception
  auto find_scene_objects(Container &scenes, const int id) {
    auto it = find_if(scenes.begin(), scenes.end(),
                      [&id](const auto &scene) {
                        return scene->get_id() == id;
                      });

    if (it == scenes.end()) {
      throw cs3520::InvalidUserInputException("Scene object " + to_string(id) + " not found");
    }
    return it;
  }
}  // namespace

namespace cs3520 {
  // --------------------------------------------------------------------------------------------
  // TASK: Implement the Scene member functions.
  // --------------------------------------------------------------------------------------------
  bool Scene::SceneObjectComparator::operator()(const std::unique_ptr<SceneObject> &scene_obj,
                                              const int id) const {
    return scene_obj->get_id() < id;
  }

  bool Scene::SceneObjectComparator::operator()(const int id,
                                                const std::unique_ptr<SceneObject> &scene_obj) 
                                                const {
    return id < scene_obj->get_id();
  }

  bool Scene::SceneObjectComparator::operator()(const std::unique_ptr<SceneObject> &lhs,
                                                const std::unique_ptr<SceneObject> &rhs) const {
    return lhs->get_id() < rhs->get_id();
  }

  // add given object to set m_scene_objects
  void Scene::add_scene_obj(unique_ptr<SceneObject> scene_obj) {
    m_scene_objects.insert(move(scene_obj));
  }

  // remove object and throw error if not found
  void Scene::remove_scene_obj(int id) {
    // call helper to search for object, if not found helper will throw exception
    auto it = find_scene_objects(m_scene_objects, id);
    // remove object from the set
    m_scene_objects.erase(it);
  }

  // set object at given position
  void Scene::set_scene_obj_position(int id, sf::Vector2f position) {
    auto it = find_scene_objects(m_scene_objects, id);
    (*it)->set_position(position);
  }

  // render scene to given window
  void Scene::render(sf::RenderWindow &window) const {
    // use while loop for the SFML window & event handling
    auto it = m_scene_objects.begin();
    while (it != m_scene_objects.end()) {
      (*it)->draw(window);
      ++it;
    }
    // for_each(m_scene_objects.begin(), m_scene_objects.end(),
    //         [&window](const unique_ptr<SceneObject> &scene_obj) {
    //           scene_obj->draw(window);
    //         });
  }

  void Scene::print(std::ostream &os) const {
    for_each(m_scene_objects.begin(), m_scene_objects.end(),
            [&os](const unique_ptr<SceneObject> &scene_obj) {
              scene_obj->print(os);
              os << endl;
            });
  }

  // --------------------------------------------------------------------------------------------
  // TASK: Implement the SceneBuilder member functions.
  // --------------------------------------------------------------------------------------------
  vector<std::string> SceneBuilder::get_scene_object_template_names() const {
    vector<string> result;
    transform(
        m_templates.begin(), m_templates.end(),
        back_inserter(result),
        [](const auto &element) {
          return element.first;
        });
    return result;
  }

  void SceneBuilder::create_scene_obj_template(const std::string &name, const cs3520::Image &img) {
    // Check if a template with that name already exists
    auto it = m_templates.find(name);
    if (it != m_templates.end()) {
      throw InvalidUserInputException("Scene object template " + name + " already exists");
    }
    // Add the template
    m_templates.emplace(name, SceneObjectTemplate(name, img));
  }

  void SceneBuilder::delete_scene_obj_template(const std::string &name) {
    // Check if template with the given name exists
    if (m_templates.find(name) == m_templates.end()) {
      throw InvalidUserInputException("Scene object template " + name + " not found");
    }

    // Delete the template
    m_templates.erase(name);
  }

  std::unique_ptr<SceneObject> SceneBuilder::instantiate_scene_obj(
      const std::string &scene_object_template_name,
      int scene_object_id) const {
    // look for template
    auto iter = m_templates.find(scene_object_template_name);
    // if template not found
    if (iter == m_templates.end()) {
      throw InvalidUserInputException("Scene object template " +
                                      scene_object_template_name +
                                      " not found");
    }

    // Create a new SceneObject instance from the template and return it
    return std::make_unique<SceneObject>(scene_object_id,
                                         make_shared<SceneObjectTemplate>(iter->second));
  }

  // --------------------------------------------------------------------------------------------
  // TASK: Implement the SceneObjectTemplate constructor(s) and member functions.
  // You must decide which of those can go in the .hpp file and which should
  // go here in the .cpp file.
  // --------------------------------------------------------------------------------------------
  SceneObjectTemplate::SceneObjectTemplate(const std::string &name) : m_name(name) {}
  SceneObjectTemplate::SceneObjectTemplate(const std::string &name,
                                           const cs3520::Image image) : m_name(name) {
    // sf::Texture m;
    // m.loadFromFile(image.get_path());
    // m_texture = m;
    set_texture(image);
    // should it do anything if img not found ?
  }

  void SceneObjectTemplate::set_texture(const cs3520::Image &img) {
    sf::Texture m;
    m.loadFromFile(img.get_path());
    m_texture = m;
  }
  
  // --------------------------------------------------------------------------------------------
  // TASK: Implement the SceneObject member functions.
  // --------------------------------------------------------------------------------------------
  // Constructs a SceneObject from given SceneObjectTemplate
  SceneObject::SceneObject(int id, shared_ptr<SceneObjectTemplate> tmpl) : m_id(id) {
    sf::Texture scene_texture;
    scene_texture = tmpl->get_texture();
    sf::Sprite scene_sprite(scene_texture);
    m_sprite = scene_sprite;
    m_tmpl = tmpl;
  }

  // gets position of the scene obj
  const sf::Vector2f &SceneObject::get_position() const {
    return m_sprite.getPosition();
  }

  // sets the position of the scene obj
  void SceneObject::set_position(const sf::Vector2f &pos) {
    m_sprite.setPosition(pos);
  }

  // renders a sprite to the given window
  void SceneObject::draw(sf::RenderWindow &window) const {
    shared_ptr<SceneObjectTemplate> new_tmpl = m_tmpl.lock();

    // if tmpl exists, render sprite to window
    if (!new_tmpl) {
      window.draw(m_sprite);
      // should position be set to 0,0?
      window.display();
    }
    // else it no longer exists, print this instead of drawing
    else {
      cerr << "Template " + new_tmpl->get_name() << " was deleted" << endl;
      
    }
  }

  void SceneObject::print(ostream &os) const {
    shared_ptr<SceneObjectTemplate> new_tmpl = m_tmpl.lock();

    os << new_tmpl->get_name() << " object "
      << to_string(m_id) << " at position "
      << to_string(int(round(m_sprite.getPosition().x)))
      << ", " << to_string(int(round(m_sprite.getPosition().y)));

    // if template no longer exists
    if (!new_tmpl) {
      os << " (template " + new_tmpl->get_name() << " was deleted";
    }
  }

}  // namespace cs3520
