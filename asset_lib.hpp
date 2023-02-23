#ifndef ASSET_LIB_HPP
#define ASSET_LIB_HPP

// IMPORTANT: You may only modify this file in the places specified
// and in ways allowed by the assignment specification.

#include <filesystem>
#include <iosfwd>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
// Add any additional #includes here
namespace cs3520
{
  // This is a "forward declaration" of the Image class. It lets us put the
  // class definition farther down in the file, as long as we only need to
  // use the Image type with pointers or references.
  //
  // TASK: You will implement one constructor for Image, see definition for details.
  // The rest of the class definition is provided for you.
  class Image;

  // Stream insertion operator overload for shared pointer to Image.
  //
  // Prints a text representation of the Image pointed to by img_ptr in the
  // following format:
  // <image_name> (<image_file_path>)
  // with <image name> replaced by the name of the image in the library and
  // <image_file_path> replaced by the path to the image file.
  // Does not print a newline or flush the stream.
  //
  // TASK: Examine the available member functions in the Image class, then
  // implement this overload in asset_lib.cpp.
  // Consider why we want this overload and where it simplifies our code.
  std::ostream &operator<<(std::ostream &os, const std::shared_ptr<const Image> &img_ptr);

  // Forward declaration of the Album struct.
  // See the struct definition below for additional details.
  struct Album;

  // Abstraction for our asset library. Supports importing, organizing,
  // and querying Image metadata.
  //
  // TASK: Implement all of the public methods of this class in asset_lib.cpp.
  // Unless specified otherwise, those methods should only use constant space.
  class Library
  {
  public:
    // Returns a vector of pointers to all images in the library,
    // sorted lexicographically by image name.
    //
    // Runtime upper bound: O(n), n=number of images in the library
    // Space upper bound: O(n), n=number of images in the library
    std::vector<std::shared_ptr<const Image>> list_images() const;

    // Imports an image located at file_path into the library, setting the name
    // of the image in the library to the name of the file being imported.
    // For example, importing an image at path/to/my_image.png would set the
    // imported image name to my_image.png.
    //
    // Note: After an image is imported into the library, it can be renamed, making
    // the name of the image in the library different from the name of the
    // image file in the file system.
    //
    // This function does not modify the file system.
    //
    // See https://en.cppreference.coImagem/w/cpp/filesystem for information on
    // how to check if a file exists in the filesystem.
    //
    // Throws InvalidUserInputException with the message "Couldn't find file " + file_path
    // if the specified file path does not exist.
    //
    // Throws InvalidUserInputException with the message
    // "Image " + name + " already exists" if an image
    // in the library already has the same name as the file being imported.
    //
    // Runtime upper bounds:
    // - O(log(n)) to check whether the image name is already in use
    // - O(n) to import the image,
    //   where n=number of images in the library
    void import_image(const std::string &file_path);

    // Returns a pointer to the image with the specified name.
    //
    // Throws InvalidUserInputException with the message "Image " + name + " not found"
    // if that image does not exist in the library.
    //
    // Runtime upper bound: O(log(n)), n=number of images in the library
    std::shared_ptr<const Image> get_image(const std::string &name) const;

    // You may use *one* range-based for-loop in this memeber function (in
    // addition to calls to STL algorithms).
    //
    // Removes the image with the specified name from the library and any albums
    // it is part of.
    // Does not modify the file system.
    //
    // Throws InvalidUserInputException with the message "Image " + name + " not found"
    // if the requested image does not exist.
    //
    // Runtime upper bounds:
    // - O(log(n)) to find the requested image
    // - O(n + a * s) to remove it,
    // where n=number of images in the library,
    //       a=number of albums in the library,
    //       s=number of images in the largest album the image is a part of.
    void remove_image(const std::string &name);

    // Renames the specified image in the library.
    // Does not modify the file system.
    //
    // First, finds the requested image in the library and throws
    // InvalidUserInputException with the message "Image " + name + " not found"
    // if that image could not be found.
    //
    // Then, checks if the specified new name is already in use, and if so throws
    // InvalidUserInputException with the message "Image " + name + " already exists".
    //
    // Runtime upper bound: O(log(n)), n=number of images in the library
    void rename_image(const std::string &current_name, const std::string &new_name);

    // Returns a vector of pointers to images whose names contain the given query string,
    // sorted lexicographically by image name.
    //
    // Runtime upper bound: O(n), n=number of images in the library
    // Space upper bound: O(n), n=number of images in the library
    std::vector<std::shared_ptr<const Image>> query_images(const std::string &query) const;

    // Returns a vector containing the names of every album in the library,
    // sorted lexicographically by album name.
    //
    // Runtime upper bound: O(a), a=number of albums in the library.
    // Space upper bound: O(a), a=number of albums in the library.
    std::vector<std::string> get_album_names() const;

    // Returns a reference to the album with the given name.
    //
    // Throws InvalidUserInputException with the message "Album " + name + " not found"
    // if an album with that name does not exist in the library.
    //
    // Runtime upper bound: O(log(a)), a=number of albums in the library.
    const Album &get_album(const std::string &album_name) const;

    // Creates a new album in the library with the given name.
    //
    // Throws InvalidUserInputException with the message
    // "Album " + album_name + " already exists" if an album with that name
    // already exists.
    //
    // Runtime upper bounds:
    // - O(log(a)) to check whether an album with that name exists
    // - O(a) to add the new album to the library,
    //   where a=number of albums in the library.
    void create_album(const std::string &album_name);

    // Removes the album with the given name from the library.
    //
    // Throws InvalidUserInputException with the message "Album " + name + " not found"
    // if an album with that name does not exist.1
    //
    // Runtime upper bounds:
    // - O(log(a)) to check whether an album with that name exists
    // - O(a) to remove the album from the library,
    //   where a=number of albums in the library.
    void delete_album(const std::string &album_name);

    // Adds the specified image to the end of the specified album.
    // Note: The images in an album are stored in the order they are
    // added and only sorted if sort_album is called.
    //
    // First, looks up the requested album and throws
    // InvalidUserInputException with the message "Album " + name + " not found"
    // if the requested album does not exist.
    //
    // Then, looks up the requested image and throws InvalidUserInputException
    // with the message "Image " + name + " not found" if the requested image
    // does not exist.
    //
    // Then, throws InvalidUserInputException with the message
    // "Image " + img_name + " already part of album " + album_name
    // if the requested image is already part of the requested album.
    //
    // Runtime upper bounds:
    // - O(log(a)) to check whether the album exists, a=number of albums in the library
    // - O(log(n)) to check whether the image exists, n=number of images in the library
    // - O(s) to check whether the image is already part of the album,
    //   s=number of images in the requested album
    // - O(1) (amortized) to add the image to the album.
    void add_to_album(const std::string &album_name, const std::string &img_name);

    // Removes the specified image from the specified album.
    //
    // Throws InvalidUserInputException with the message "Album " + name + " not found"
    // if the requested album does not exist
    //
    // Throws InvalidUserInputException with the message
    // "Image " + img_name + " already part of album " + album_name
    // if the requested image is not a part of that album.
    //
    // Runtime upper bounds:
    // - O(log(a)) to check whether the album exists, a=number of albums in the library
    // - O(s) to check whether the image is already part of the album,
    //   s=number of images in the requested album
    // - O(s) to remove the image from the album, s=number of images in the requested album
    void remove_from_album(const std::string &album_name, const std::string &img_name);

    // Sorts the images in the album with the specified name.
    //
    // Throws InvalidUserInputException with the message "Album " + name + " not found"
    // if the requested album does not exist.
    //
    // Runtime upper bounds:
    // - O(log(a)) to find the album, a=number of albums in the library
    // - O(slog(s)) to sort the images in the album, s=number of images in the requested album.
    void sort_album(const std::string &album_name);

  private:
    // ------------ vvvvvvvvvvvv MAKE CHANGES HERE vvvvvvvvvvvvvvvv --------------------
    // Declare any private member variables, private member functions,
    // or transparent comparator functors needed by your implementation here.
    // ------------ ^^^^^^^^^^^^ MAKE CHANGES HERE ^^^^^^^^^^^^^^^^ --------------------
    std::vector<Album> m_albums;
    struct ImageCompare
    {
      using is_transparent = void;
      bool operator()(const std::shared_ptr<Image> &img, const std::string &name) const;
      // {
      //   return img->get_name() < name;
      // }
      bool operator()(const std::string &name, const std::shared_ptr<Image> &img) const;
      // {
      //   return name < img->get_name();
      // }
      bool operator()(const std::shared_ptr<Image> &left, const std::shared_ptr<Image> &right) const;
      // {
      //   return left->get_name() < right->get_name();
      // }
    };
    std::set<std::shared_ptr<Image>, ImageCompare> m_images;
  };

  // Stores metadata (e.g., file path, in-library name) for an image imported
  // into the library.
  // You should implement the one constructor for this class inline (i.e., in this file).
  class Image
  {
  public:
    // ------------ vvvvvvvvvvvv MAKE CHANGES HERE vvvvvvvvvvvvvvvv --------------------
    // Implement a constructor that takes in a std::filesystem::path and initializes
    // the Image's member variables. You must decide whether to take in the
    // path variable by value, pointer, or reference.
    // ------------ ^^^^^^^^^^^^ MAKE CHANGES HERE ^^^^^^^^^^^^^^^^ --------------------
    Image(std::filesystem::path path) : m_path(path)
    {
      m_name = path.filename().string();
    }

    const std::string &get_name() const
    {
      return m_name;
    }

    const std::filesystem::path &get_path() const
    {
      return m_path;
    }

    void rename(const std::string &new_name)
    {
      m_name = new_name;
    }

    std::ostream &print(std::ostream &os) const
    {
      os << std::make_shared<const Image>(*this);
      return os;
    }

  private:
    std::filesystem::path m_path;
    std::string m_name;
  };

  // Albums are used to let the user group Images into categories.
  // The implementation of this struct is provided for you.
  struct Album
  {
    std::string name;
    std::vector<std::shared_ptr<Image>> images;

    Album(const std::string &name) : name(name) {}

    // This operator overload lets us sort albums by name.
    bool operator<(const Album &rhs) const
    {
      return name < rhs.name;
    }
  };
}

#endif // ASSET_LIB_HPP
