#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cmath> // For std::round
// Add any additional #includes here
#include "scene.hpp"
#include "exceptions.hpp"

#include <SFML/Graphics.hpp>

using namespace std;
namespace
{
  template <typename Container>
  auto find_scene_objects(Container &scenes, const int id)
  {
    auto it =
        find_if(scenes.begin(), scenes.end(),
                [&id](const auto &scene)
                { return scene->get_id() == id; });

    if (it == scenes.end())
    {
      throw cs3520::InvalidUserInputException("Scene object " + to_string(id) + " not found");
    }
    return it;
  }
}

namespace cs3520
{
  // TASK: Implement the Scene member functions.
  bool Scene::SceneObjectComparator::operator()(const std::unique_ptr<SceneObject> &scene_obj, const int id) const
  {
    return scene_obj->get_id() < id;
  }

  bool Scene::SceneObjectComparator::operator()(const int id, const std::unique_ptr<SceneObject> &scene_obj) const
  {
    return id < scene_obj->get_id();
  }

  bool Scene::SceneObjectComparator::operator()(const std::unique_ptr<SceneObject> &lhs, const std::unique_ptr<SceneObject> &rhs) const
  {
    return lhs->get_id() < rhs->get_id();
  }

  void Scene::add_scene_obj(unique_ptr<SceneObject> scene_obj)
  {
    m_scene_objects.insert(move(scene_obj));
  }

  void Scene::remove_scene_obj(int id)
  {
    auto it = find_scene_objects(m_scene_objects, id);
    m_scene_objects.erase(it);
  }

  void Scene::set_scene_obj_position(int id, sf::Vector2f position)
  {
    auto it = find_scene_objects(m_scene_objects, id);
    (*it)->set_position(position);
  }

  void Scene::print(std::ostream &os) const
  {
    for_each(m_scene_objects.begin(), m_scene_objects.end(),
             [&os](const unique_ptr<SceneObject> &scene_obj)
             {
               scene_obj->print(os);
               os << endl;
             });
  }
  void Scene::render(sf::RenderWindow &window) const
  {
    for_each(m_scene_objects.begin(), m_scene_objects.end(),
             [&window](const unique_ptr<SceneObject> &scene_obj)
             {
               scene_obj->draw(window);
             });
  }

  // --------------------------------------------------------------------------------------------

  // TASK: Implement the SceneBuilder member functions.

  // --------------------------------------------------------------------------------------------
  vector<std::string> SceneBuilder::get_scene_object_template_names() const
  {
    vector<string> result;
    transform(
        m_templates.begin(), m_templates.end(),
        back_inserter(result),
        [](const auto &element)
        {
          return element.first;
        });
    return result;
  }

  void SceneBuilder::create_scene_obj_template(const std::string &name, const cs3520::Image &img)
  {
    // Check if a template with that name already exists
    auto it = m_templates.find(name);
    if (it != m_templates.end())
    {
      throw InvalidUserInputException("Scene object template " + name + " already exists");
    }
    // Add the template
    m_templates.emplace(name, SceneObjectTemplate(name, img));
  }

  void SceneBuilder::delete_scene_obj_template(const std::string &name)
  {
    // Check if template with the given name exists
    if (m_templates.find(name) == m_templates.end())
    {
      throw InvalidUserInputException("Scene object template " + name + " not found");
    }

    // Delete the template
    m_templates.erase(name);
  }
  std::unique_ptr<SceneObject> SceneBuilder::instantiate_scene_obj(
      const std::string &scene_object_template_name,
      int scene_object_id) const
  {
    // Check if the template exists
    auto iter = m_templates.find(scene_object_template_name);
    if (iter == m_templates.end())
    {
      throw InvalidUserInputException("Scene object template " + scene_object_template_name + " not found");
    }

    // Create a new SceneObject instance from the template and return it
    return std::make_unique<SceneObject>(scene_object_id, make_shared<SceneObjectTemplate>(iter->second));
  }

  // TASK: Implement the SceneObjectTemplate constructor(s) and member functions.
  // You must decide which of those can go in the .hpp file and which should
  // go here in the .cpp file.
  SceneObjectTemplate::SceneObjectTemplate(const std::string &name) : m_name(name) {}
  SceneObjectTemplate::SceneObjectTemplate(const std::string &name, const cs3520::Image image) : m_name(name)
  {
    sf::Texture m;
    m.loadFromFile(image.get_path());
    m_texture = m;
  }

  // --------------------------------------------------------------------------------------------

  // TASK: Implement the SceneObject member functions.
  // Constructs a SceneObject
  SceneObject::SceneObject(int id, shared_ptr<SceneObjectTemplate> tmpl) : m_id(id)
  {
    sf::Texture scene_texture;
    scene_texture = tmpl->get_texture();
    sf::Sprite scene_sprite(scene_texture);
    m_sprite = scene_sprite;
    m_tmpl = tmpl;
  }

  const sf::Vector2f &SceneObject::get_position() const
  {
    return m_sprite.getPosition();
  }

  void SceneObject::set_position(const sf::Vector2f &pos)
  {
    m_sprite.setPosition(pos);
  }

  void SceneObject::draw(sf::RenderWindow &window) const
  {
    window.draw(m_sprite);
    window.display();
    shared_ptr<SceneObjectTemplate> new_tmpl = m_tmpl.lock();
    if (new_tmpl)
    {
      cerr << "Template " + new_tmpl->get_name() << " was deleted" << endl;
    }
  }

  void SceneObject::print(ostream &os) const
  {
    shared_ptr<SceneObjectTemplate> new_tmpl = m_tmpl.lock();
    if (new_tmpl)
    {
      cerr << "Template " + new_tmpl->get_name() << " was deleted" << endl;
    }
    os << new_tmpl->get_name() << " object "
       << to_string(m_id) << " at position "
       << to_string(int(round(m_sprite.getPosition().x)))
       << ", " << to_string(int(round(m_sprite.getPosition().y)));
  }

}
