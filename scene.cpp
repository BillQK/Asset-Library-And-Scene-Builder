#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cmath> // For std::round
// Add any additional #includes here

#include <SFML/Graphics.hpp>

#include "scene.hpp"
#include "asset_lib.hpp"
#include "exceptions.hpp"

using namespace std;
namespace
{
  template <typename Container>
  auto find_scene_objects(Container &scenes, const int id)
  {
    auto it =
        lower_bound(scenes.begin(), scenes.end(), id,
                    [](const auto &scene, const int id)
                    { return scene->get_id() < id; });

    if (it == scenes.end() || (*it)->get_id() != id)
    {
      throw cs3520::InvalidUserInputException("Scene object " + to_string(id) + " not found");
    }
    return it;
  }
}

namespace cs3520
{
  // TASK: Implement the Scene member functions.
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
    if (m_tmpl)
    {
      cerr << "Template " + m_tmpl->get_name() << " was deleted" << endl;
    }
  }

  void SceneObject::print(ostream &os) const
  {
    os << m_tmpl->get_name() << " object "
       << to_string(m_id) << " at position "
       << to_string(int(m_sprite.getPosition().x))
       << ", " << to_string(int(m_sprite.getPosition().y))
       << endl;
  }

}
