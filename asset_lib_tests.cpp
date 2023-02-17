#include <iostream>
#include <string>

#include "asset_lib.hpp"
#include "unit_test_framework.h"
#include "exceptions.hpp"

using std::operator""s;
using namespace cs3520;

// Add your Library unit tests to this file
TEST(write_your_tests_here)
{
  ASSERT_TRUE(true);
}
//----------------------------------------------------------------
// Image tests
TEST(test_image_constructor_with_path)
{
  // Create a test image
  Image img = Image("/acd.pdf");
  ASSERT_EQUAL(img.get_name(), "acd.pdf");
  ASSERT_EQUAL(img.get_path(), "/acd.pdf");

  std::ostringstream expected;
  std::ostringstream actual;

  img.print(actual);

  expected << "acd.pdf"
           << " (\"/acd.pdf\")";

  ASSERT_EQUAL(expected.str(), actual.str());
}

// ----------------------------------------------------------------
// Library Test Cases
TEST(test_import_images_correct)
{
  Library library = Library();

  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster_link.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");

  ASSERT_EQUAL(library.list_images().size(), 4);
}

TEST(test_import_images_failed_images_exists)
{
  Library library = Library();
  try
  {
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/lobster_link.jpg");
    library.import_image("imgs/lobster_link.jpg");
    library.import_image("imgs/trogdor1.png");
    // The test should fail here, as an exception should be thrown
    // when importing the third image with the same name
    ASSERT_TRUE(false);
  }
  catch (InvalidUserInputException &e)
  {
    // Check if the exception message is correct
    ASSERT_EQUAL("Image lobster_link.jpg already exists"s,
                 e.what());
  }
}

TEST(test_import_images_failed_images_path_does_not_exist)
{
  Library library = Library();
  try
  {
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/lobster_link.jpg");
    library.import_image("imgs/lobster_link.png");
    library.import_image("imgs/trogdor1.png");
    // The test should fail here, as an exception should be thrown
    // when importing the third image with the same name
    ASSERT_TRUE(false);
  }
  catch (InvalidUserInputException &e)
  {
    // Check if the exception message is correct
    ASSERT_EQUAL("Couldn't find file imgs/lobster_link.png"s,
                 e.what());
  }
}

TEST(test_list_images)
{
  Library library = Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  std::vector<std::shared_ptr<const cs3520::Image>> list_images = library.list_images();

  ASSERT_EQUAL(list_images.size(), 4);
  ASSERT_EQUAL(list_images.at(0)->get_name(), "crabster.jpg");
  ASSERT_EQUAL(list_images.at(2)->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(list_images.at(1)->get_name(), "lobster.png");
  ASSERT_EQUAL(list_images.at(3)->get_name(), "trogdor1.png");
}

TEST(test_get_image)
{
  Library library = Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  std::shared_ptr<const Image> crab = library.get_image("crabster.jpg");
  std::shared_ptr<const Image> lobster = library.get_image("lobster.png");
  std::shared_ptr<const Image> trogdor1 = library.get_image("trogdor1.png");
  std::shared_ptr<const Image> lobster_link = library.get_image("lobster_link.jpg");

  ASSERT_EQUAL(crab->get_name(), "crabster.jpg");
  ASSERT_EQUAL(lobster->get_name(), "lobster.png");
  ASSERT_EQUAL(trogdor1->get_name(), "trogdor1.png");
  ASSERT_EQUAL(lobster_link->get_name(), "lobster_link.jpg");
}

TEST(test_get_name_not_found)
{
  try
  {
    Library library = Library();
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/lobster.png");
    library.import_image("imgs/trogdor1.png");
    library.import_image("imgs/lobster_link.jpg");

    std::shared_ptr<const Image> crab = library.get_image("crabster.jpg");
    std::shared_ptr<const Image> lobster = library.get_image("lobster.png");
    std::shared_ptr<const Image> trogdor1 = library.get_image("trogdor1.png");
    std::shared_ptr<const Image> lobster_link = library.get_image("lobster_link.png");
  }
  catch (InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Image lobster_link.png not found"s, e.what());
  }
}


TEST(test_remove_image)
{
  Library library = Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.remove_image("crabster.jpg");

  ASSERT_EQUAL(library.list_images().size(), 3);
}

// To write a test that checks whether an exception is thrown, use the following
// pattern:
// TEST(test_exception_thrown) {
//   try {
//     // Add code that should throw an exception here.
//
//     // If the above code doesn't throw an exception, print a message and fail
//     // the test case.
//     std::cerr << "Exception not thrown\n";
//     ASSERT_TRUE(false);
//   }
//   catch(cs3520::InvalidUserInputException& e) {
//     // Check the message stored in e.what()
//     // .what() returns a C-style string.
//     // Make sure to compare it against a C++ string!
//     ASSERT_EQUAL("Expected message"s, e.what());
//   }
// }

TEST_MAIN()
