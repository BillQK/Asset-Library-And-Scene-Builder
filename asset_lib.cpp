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
    auto it = find_if(images.begin(), images.end(), [&name](const shared_ptr<cs3520::Image> &image)
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

  // Find the album by image name
  string find_album_by_image_name(const string &image_name, const vector<cs3520::Album> &albums)
  {
    auto album_iter = find_if(albums.begin(), albums.end(), [&image_name](const cs3520::Album &album)
                              { return any_of(album.images.begin(),
                                              album.images.end(),
                                              [&image_name](const shared_ptr<cs3520::Image> &image)
                                              { return image->get_name() == image_name; }); });
    if (album_iter != albums.end())
    {
      return album_iter->name;
    }
    else
    {
      throw cs3520::InvalidUserInputException("Image '" + image_name + "' not found in any albums");
    }
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
  Image::Image(filesystem::path fs) : m_path(fs)
  {
    m_name = fs.filename().string();
  }

  vector<shared_ptr<const Image>> Library::list_images() const
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

  void Library::import_image(const string &file_path)
  {
    // Check if the file exists
    if (!filesystem::exists(file_path))
    {
      throw InvalidUserInputException("Couldn't find file " + file_path);
    }

    // Get the name of the file
    string file_name = filesystem::path(file_path).filename().string();

    // Check if the name is already in use
    if (any_of(m_images.begin(), m_images.end(), [&file_name](const auto &image)
               { return filesystem::path(image->get_path()).filename().string() == file_name; }))
    {
      throw InvalidUserInputException("Image " + file_name + " already exists");
    }

    // Import the image
    m_images.push_back(make_shared<Image>(file_path));
  }

  shared_ptr<const Image> Library::get_image(const string &name) const
  {
    auto it = find_image(m_images, name);
    return *it;
  }

  void Library::remove_image(const string &name)
  {
    // TODO: exception
    auto it = find_image(m_images, name);
    m_images.erase(it);
    string album_contains_image = find_album_by_image_name(name, m_albums);
    remove_from_album(album_contains_image, name);
  }

  void Library::rename_image(const string &current_name, const string &new_name)
  {
    auto it = find_image(m_images, current_name);
    shared_ptr<Image> image = *it;

    // Check if the specified new name is already in use
    auto it_new_name = find_image(m_images, new_name);
    if (it_new_name != m_images.end())
    {
      throw InvalidUserInputException("Image " + new_name + " already exists");
    }
    image->rename(new_name);
  }

  vector<shared_ptr<const Image>> Library::query_images(const string &query) const
  {
    vector<shared_ptr<const Image>> result;
    copy_if(m_images.begin(), m_images.end(), back_inserter(result),
            [query](const auto &img)
            { return str_contains(img->get_name(), query); });

    sort(result.begin(), result.end(), [](const auto &img1, const auto &img2)
         { return img1->get_name() < img2->get_name(); });
    return result;
  }

  vector<string> Library::get_album_names() const
  {
    vector<string> result;
    transform(
        m_albums.begin(), m_albums.end(),
        back_inserter(result), [](const Album &album)
        { return album.name; });
    return result;
  }

  void Library::delete_album(const std::string &album_name)
  {
    auto it = find_album(m_albums, album_name);
    m_albums.erase(it);
  }

  void Library::add_to_album(const std::string &album_name, const std::string &img_name)
  {
    auto it = find_album(m_albums, album_name);
    auto image_it = find_image(m_images, img_name);

    // check if image already exists in album list
    auto image_check_in_album = find_image(it->images, img_name);
    if (image_check_in_album != it->images.end())
    {
      throw InvalidUserInputException("Image " + img_name +
                                      " already part of album " + album_name);
    }

    it->images.push_back(*image_it);
  }

  void Library::remove_from_album(const string &album_name, const string &img_name)
  {
    auto it = find_album(m_albums, album_name);
    auto image_it = find_image(it->images, img_name);
    it->images.erase(image_it);
  }

  void Library::sort_album(const std::string &album_name)
  {
    auto it = find_album(m_albums, album_name);
    sort(it->images.begin(), it->images.end(),
         [](const shared_ptr<Image> &image1, const shared_ptr<Image> &image2)
         {
           return image1->get_name() < image2->get_name();
         });
  }

}
