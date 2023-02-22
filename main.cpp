// This file contains the top-level command loop for processing user input from cin.
// Each command the user enters must be one one line. For example:
//    import_img path/to/image.png
//
// Each line of input read from cin must consist of the name of a command followed
// by the required arguments for that command, delimited by non-newline whitespace.
// Extra arguments at the end of the line are discarded.
//
// Command names must match exactly. If an unrecognized command is entered,
// print the message "Unrecognized command" followed by a newline and discard the
// rest of the line.
//
// Arguments to command may not contain spaces. Assume that arguments to commands
// do not contain spaces when processing the input.
//
// If any extra newlines are entered, skip over them without printing anything.
//
// Refer to the the public test case provided for an example of the correct
// output for these commands.
// The commands that you must implement and their descriptions are as follows:
//
// list_imgs
//     Prints the phrase "Images in library:" followed by a newline,
//     then prints each image in the library in the format
//     "<image name> ("<image path>")", each followed by a newline.
//
// import_img <file path>
//     Import the image at the given path into the library
//
// remove_img <image name>
//     Remove the named image from the library
//
// rename_img <current name> <new name>
//     Rename the specified image
//
// query_imgs <query str>
//     Searches for images whose names match the query string. If no images are found,
//     prints the message "No images matching that query" to cout, followed by a newline.
//     Otherwise, prints the message "Query results:" followed by a newline,
//     then prints the each image matching the query in the same format as
//     list_imgs, each followed by a newline.
//
// list_albums
//     Prints the phrase "Albums:" followed by a newline,
//     then prints the names of every album in the library, each followed by a newline.
//
// print_album <album name>
//     Prints the phrase "<album name> contents:" followed by a newline,
//     then prints the names of every image in that album, each followed by a newline.
//
// create_album <album name>
//     Creates an album with the given name
//
// delete_album <album name>
//     Deletes the album with the given name
//
// add_to_album <album name> <image name>
//     Adds the specified image to the end of the specified album
//
// remove_from_album <album name> <image name>
//     Removes the specified image from the specified album
//
// sort_album <album name>
//     Sorts the images contained in the specified album
//
// list_scene_obj_tmpls
//     Prints the phrase "Scene Object Templates:" followed by a newline,
//     then prints the names of every scene object template in the scene builder,
//     each followed by a newline.
//
// create_scene_obj_tmpl <template name> <image name>
//     Creates a scene template object with the specified image as its texture.
//
// remove_scene_obj_tmpl <template name>
//     Removes the specified scene object template. Does not delete any scene objects.
//
// spawn_scene_obj <template name>
//     Creates a scene object from the specified template and adds it to the scene.
//
// set_scene_obj_pos <scene object id> <x> <y>
//     Sets the position of the specified scene object to be the given x & y coordinates.
//     The coordinates can be integers or floating point numbers.
//     You do not need to do any error checking of the given coordinates.
//
// despawn_scene_obj <scene object id>
//     Removes the specified scene object from the scene and deallocates it
//
// show_scene <width> <height>
//     Renders the scene in an SFML RenderWindow with the given width and height.
//     You do not need to do any error checking of the given width and height.
//
// print_scene
//     Prints a textual representation of the scene, as described in Scene::print.
//
// Note that error handling other than not enough arguments being provided is
// implemented in the asset_lib and scene modules. Your command functions should
// not duplicate that functionality. Instead, catch thrown exceptions in your
// command loop and print out their messages.

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <map>
// Add any additional #includes here.

#include "asset_lib.hpp"
#include "scene.hpp"
#include "exceptions.hpp"

using cs3520::Library;
using cs3520::Scene;
using cs3520::SceneBuilder;
using cs3520::Image;
using std::cin;
using std::cout;
using std::endl;
using std::istringstream;
using std::map;
using std::string;
// Add other "using" statements here
using namespace std;

namespace
{
  // Declare any helper functions you need here, if any.
  // NOTE: The command function declarations should go in the next
  // unnamed namespace.
  // Define them at the bottom of the file.

}

namespace
{
  // Declare your command functions here. Define them in the unnamed namespace
  // below main().
  // If a command function doesn't modify the Library, SceneBuilder, and/or Scene,
  // those parameters should be marked as const.
  // If any of the parameters are unused, remove the parameter names to suppress compiler
  // warnings.
  // The first two stubs are provided for you to illustrate this.

  // Library is const, SceneBuilder and Scene are unused.
  void list_imgs(istringstream &iss, const Library &lib, const SceneBuilder &, const Scene &);
  // Library is non-const, SceneBuilder and Scene are unused.
  void import_img(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&);
  void remove_img(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&);
  void rename_img(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&);
  void query_imgs(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&);
  void list_albums(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&);
}

// This is a map of strings to functions. By declaring the type of the functions
// as wrapped in std::function, this allows us to have some of our command
// functions take in const Libraries, SceneBuilders, and Scenes, and others
// can take in non-const versions of those parameters.
// Ask James in office hours if you're curious about how this works.
//
// Fill this map with an entry for each supported command.
// Below main(), define a function implementing each command, then add
// those functions to this map under the appropriate key.
// The commands are described below.
//
// Note: Do NOT write a function to implement the "quit" command.
// Instead, check for "quit" in the command loop in main.
const map<string, std::function<void (istringstream&, Library&, SceneBuilder&, Scene&)>> command_funcs = {
  // Add your command functions to this map.
  // Wrap the name of each function in std::function, as this will allow us to
  // use the proper const modifiers on the function parameters.

  {"list_imgs", list_imgs},
  {"import_img", import_img},
  {"remove_img", remove_img},
  {"rename_img", rename_img},
  {"query_imgs", query_imgs},
  {"list_albums", list_albums},
  // {"print_album", },
  // {"create_album", },
  // {"delete_album", },
  // {"add_to_album", },
  // {"remove_from_album", },
  // {"sort_album", },
  // {"list_scene_obj_tmpls", },
  // {"create_scene_obj_tmpl", },
  // {"remove_scene_obj_tmpl", },
  // {"spawn_scene_obj", },
  // {"set_scene_obj_pos", },
  // {"despawn_scene_obj", },
  // {"show_scene", },
  // {"print_scene", },
};

int main()
{
  // Implement your command loop according to the instructions in the comments
  // below.

  // Declare Library, SceneBuilder, and Scene variables.
  Library lib;
  SceneBuilder scene_builder;
  Scene scene;

  string input;
  // Read lines from cin as long as the state of the stream is good.
  // This while loop condition is provided for you.
  while (std::getline(cin, input))
  {
    // Skip over blank lines (provided for you). You do not need to handle
    // leading whitespace, and we will not test your code on that.
    if (input.empty())
    {
      continue;
    }

    // Create an istringstream from the line that we read in.
    // Read the first word as the command to run.
    // If the command is "quit", exit the program with zero status.
    string input_cmd;
    istringstream iss(input);
    iss >> input_cmd;
    if(input_cmd == "quit") {
      return 0;
    }
    // cout << "ISS INPUT: " << cmd << endl; // it only reads the first word entered

    // Look up the command function in the map of commands.
    // If that command doesn't exist, print "Unrecognized command"
    // to cout followed by a newline.

    // // using iterator
    // auto it = find_if(command_funcs.being, command_funcs.end,
    //                   [&input_cmd](const auto& func) {
    //                     return func.first == input_cmd;
    //                   });
    // // if cmd not found
    // if(it == command_funcs.end()) {
    //   cout << "Unrecognized command" << endl;
    // }

    if(command_funcs.find(input_cmd) == command_funcs.end()) {
      cout << "Unrecognized command" << endl;
    }

    // If it does exist, call the command function, passing in
    // the library, scene builder, and scene objects you created.
    // If InvalidUserInputException is thrown, print out the message
    // returned by the "what()" member function on the exception.
    else {
      // gets & calls the function
      try {
        command_funcs.at(input_cmd)(iss, lib, scene_builder, scene);
      }
      catch(cs3520::InvalidUserInputException &e) {
        cerr << e.what() << endl;
      }
    }
  }
}

namespace
{
  // Add your command function definitions here. The first two stubs
  // are provided as an illustration.

  // Library is const, istringstream, SceneBuilder and Scene are unused
  void list_imgs(istringstream&, const Library& lib, const SceneBuilder&, const Scene&) {
    vector<shared_ptr<const Image>> images = lib.list_images();
    cout << "Images in library: " << endl;
    copy(cbegin(images), cend(images), ostream_iterator<shared_ptr<const Image>>(cout, "\n"));
    cout << "";
  }

  // Library is non-const, SceneBuilder and Scene are unused
  void import_img(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&) {
    string file_path;
    iss >> file_path;
    lib.import_image(file_path);
  }

  // Library is non-const, SceneBuilder and Scene are unused
  void remove_img(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&) {
    // QUESTION: does this have to be const string?
    string name;
    iss >> name;
    lib.remove_image(name);
  }

  // Library is non-const, SceneBuilder and Scene are unused
  void rename_img(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&) {
    string current_name;
    string new_name;
    iss >> current_name >> new_name;
    lib.rename_image(current_name, new_name);
  }

  // finish the error msg & others
  void query_imgs(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&) {
    string query;
    iss >> query;
    lib.query_images(query);
  }

  // finish
  void list_albums(istringstream& iss, Library& lib, const SceneBuilder&, const Scene&) {
    cout << "Albums:" << endl;
  }
}

namespace
{
  // Define your other helper functions here, if any
}
