#include <utility>
#include <filesystem>
#include <iosfwd>
#include <string>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <exception>
// Add any additional #includes here

#include "exceptions.hpp"
#include "asset_lib.hpp"

using namespace std;

namespace
{
  // Add any helper function declarations here.
  // Define your helper functions at the bottom of the file.
  // If your helper function is templated, you can declare and define it here.

  // Provided and suggested helper functions

  bool str_contains(const string &str, const string &search_for)
  {
    // string::npos plays a similar role to the "end" iterator
    // for containers, but its value is *not* one-past-the-end.
    // string::find returns string::npos if the requested string
    // could not be found.
    return str.find(search_for) != string::npos;
  }

  // Suggested helper function for looking up Images.
  //
  // Returns an iterator pointing to the element in the given container
  // identified by the given Image name.
  // Throws InvalidUserInputException if that element
  // doesn't exist in the container.
  //
  // While we recommend implementing this method and using it to
  // reduce code duplication, you may write different helper functions
  // for that purpose if you choose.
  //
  // The deduced "Container" type will include any const-qualifiers
  // on the container, and the "auto" return type will then deduce whether
  // the iterator being returned is a const_iterator or regular non-const iterator.
  template <typename Container>
  auto find_image(Container &images, const string &name)
  {
    auto it = find_if(images.begin(), images.end(), [&name](const std::shared_ptr<cs3520::Image> &image)
                      { return image->get_name() == name; });

    if (it == images.end())
    {
      throw cs3520::InvalidUserInputException("Image '" + name + "' not found in the container");
    }
    return it;
  }

  // Suggested helper function for looking up Images.
  //
  // Returns an iterator pointing to the element in the given container
  // identified by the given Album name.
  // Throws InvalidUserInputException if that element
  // doesn't exist in the container.
  template <typename Container>
  auto find_album(Container &albums, const string &name)
  {
    auto it = find_if(albums.begin(), albums.end(), [&name](const cs3520::Album &album)
                      { return album.name == name; });

    if (it == albums.end())
    {
      throw cs3520::InvalidUserInputException("Album '" + name + "' not found in the container");
    }
    return it;
  }
}

namespace cs3520
{
  ostream &operator<<(ostream &os, const shared_ptr<const Image> &img_ptr)
  {
    // TASK: Implement this stream insertion operator overload.
    os << "Image(" << img_ptr->get_name() << ", " << img_ptr->get_path() << ")";
    return os;
  }

  // TASK: Implement the Library member functions.

  Image::Image() : m_path(""), m_name("") {}
  Image::Image(std::filesystem::path fs) : m_path(fs)
  {
    m_name = fs.filename().string();
  }

  std::vector<std::shared_ptr<const Image>> Library::list_images() const
  {
    vector<shared_ptr<const Image>> images;

    // Copy all images into the vector.
    copy(m_images.begin(), m_images.end(), back_inserter(images));

    // Sort the vector of images by name.
    sort(images.begin(), images.end(),
         [](const shared_ptr<const Image> &a, const shared_ptr<const Image> &b)
         {
           return a->get_name() < b->get_name();
         });

    return images;
  }

  void Library::import_image(const std::string &file_path)
  {
    // Check if the file exists
    if (!std::filesystem::exists(file_path))
    {
      throw InvalidUserInputException("Couldn't find file " + file_path);
    }

    // Get the name of the file
    std::string file_name = std::filesystem::path(file_path).filename().string();

    // Check if the name is already in use
    if (std::any_of(m_images.begin(), m_images.end(), [&file_name](const auto &image)
                    { return std::filesystem::path(image->get_path()).filename().string() == file_name; }))
    {
      throw InvalidUserInputException("Image " + file_name + " already exists");
    }

    // Import the image
    m_images.push_back(std::make_shared<Image>(file_path));
  }

  std::shared_ptr<const Image> Library::get_image(const std::string &name) const
  {
    auto it = find_image(m_images, name);
    return *it;
  }

}
