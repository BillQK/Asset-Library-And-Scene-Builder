#include <iostream>

#include "asset_lib.hpp"
#include "unit_test_framework.h"
#include "exceptions.hpp"

using namespace cs3520; 

// Add your Library unit tests to this file
TEST(write_your_tests_here) {
  ASSERT_TRUE(true);
}

TEST(test_image_constructor) {
  // Empty image constructor
  Image img = Image(); 
  ASSERT_EQUAL(img.get_name(), ""); 
  ASSERT_EQUAL(img.get_path(), ""); 

  std::ostringstream actual;
  std::ostringstream expected;

  img.print(actual); 

  expected << " ()" << std::endl;

  ASSERT_EQUAL(expected.str(), actual.str());

}

TEST(test_image_constructor_with_path) {
  // Create a test image 
  Image img = Image("/acd.pdf"); 
  ASSERT_EQUAL(img.get_name(), "acd.pdf");
  ASSERT_EQUAL(img.get_path(), "/acd.pdf");

  std::ostringstream expected;
  std::ostringstream actual;

  img.print(actual);

  expected << "acd.pdf" << " (/acd.pdf)" << std::endl;

  ASSERT_EQUAL(expected.str(), actual.str());
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
