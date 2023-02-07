#include <utility>
#include <filesystem>
#include <iosfwd>
#include <string>
#include <memory>
#include <vector>
// Add any additional #includes here

#include "exceptions.hpp"
#include "asset_lib.hpp"

using namespace std;

namespace {
  // Add any helper function declarations here.
  // Define your helper functions at the bottom of the file.
  // If your helper function is templated, you can declare and define it here.


  // Provided and suggested helper functions

  bool str_contains(const string& str, const string& search_for) {
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
  template<typename Container>
  auto find_image(Container& images, const string& name) {
  }

  // Suggested helper function for looking up Images.
  //
  // Returns an iterator pointing to the element in the given container
  // identified by the given Album name.
  // Throws InvalidUserInputException if that element
  // doesn't exist in the container.
  template<typename Container>
  auto find_album(Container& albums, const string& name) {
  }
}

namespace cs3520 {
  ostream& operator<<(ostream& os, const shared_ptr<const Image>& img_ptr) {
    // TASK: Implement this stream insertion operator overload.
  }

  // TASK: Implement the Library member functions.
}
