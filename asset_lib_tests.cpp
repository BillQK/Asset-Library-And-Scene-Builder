#include <iostream>

#include "asset_lib.hpp"
#include "unit_test_framework.h"
#include "exceptions.hpp"

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

  library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/crabster.jpg");
  library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster_link.jpg");
  library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster.png");
  library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/trogdor1.png");

  ASSERT_EQUAL(library.list_images().size(), 4);
}

TEST(test_import_images_failed_images_exists)
{
  Library library = Library();
  try
  {
    library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/crabster.jpg");
    library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster_link.jpg");
    library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster_link.jpg");
    library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/trogdor1.png");
    // The test should fail here, as an exception should be thrown
    // when importing the third image with the same name
    ASSERT_TRUE(false);
  }
  catch (InvalidUserInputException &e)
  {
    // Check if the exception message is correct
    ASSERT_EQUAL("Image lobster_link.jpg already exists",
                 std::string(e.what()));
  }
}

TEST(test_import_images_failed_images_path_does_not_exist)
{
  Library library = Library();
  try
  {
    library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/crabster.jpg");
    library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster_link.jpg");
    library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster_link.png");
    library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/trogdor1.png");
    // The test should fail here, as an exception should be thrown
    // when importing the third image with the same name
    ASSERT_TRUE(false);
  }
  catch (InvalidUserInputException &e)
  {
    // Check if the exception message is correct
    ASSERT_EQUAL("Couldn't find file /home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster_link.png",
                 std::string(e.what()));
  }
}

TEST(test_list_images)
{
  Library library = Library();
  library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/crabster.jpg");
  library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster.png");
  library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/lobster_link.jpg");
  library.import_image("/home/billngo/Work-Space/Asset-Library-And-Scene-Builder/imgs/trogdor1.png");

  std::vector<std::shared_ptr<const cs3520::Image>> list_images = library.list_images();

  ASSERT_EQUAL(list_images.size(), 4);
  ASSERT_EQUAL(list_images.at(0)->get_name(), "crabster.jpg");
  ASSERT_EQUAL(list_images.at(2)->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(list_images.at(1)->get_name(), "lobster.png");
  ASSERT_EQUAL(list_images.at(3)->get_name(), "trogdor1.png");
}

TEST(test_get_image)
{
}

// TEST(test_find_image) {
//   Image img = Image();
//   Image img2 = Image(")asdf");

//   std::vector<Image> images = {img, img2};

//   std::iterator img_found = find_image(images, ")asdf");

// }

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
