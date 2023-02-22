#include <iostream>
#include <string>

#include "asset_lib.hpp"
#include "unit_test_framework.h"
#include "exceptions.hpp"

using std::operator""s;

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
  cs3520::Image img = cs3520::Image("/acd.pdf");
  ASSERT_EQUAL(img.get_name(), "acd.pdf");
  ASSERT_EQUAL(img.get_path(), "/acd.pdf");

  std::ostringstream expected;
  std::ostringstream actual;

  img.print(actual);

  expected << "acd.pdf"
           << " (\"/acd.pdf\")";

  ASSERT_EQUAL(expected.str(), actual.str());
}
TEST(test_print)
{
  std::shared_ptr<cs3520::Image> image = std::make_shared<cs3520::Image>("/path/to/image.jpg");
  std::stringstream ss;
  image->print(ss);
  ASSERT_EQUAL(ss.str(), "image.jpg (\"/path/to/image.jpg\")");
}

// ----------------------------------------------------------------
// Library Test Cases
TEST(test_import_images_correct)
{
  cs3520::Library library = cs3520::Library();

  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster_link.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");

  ASSERT_EQUAL(library.list_images().size(), 4);
}

TEST(test_import_images_failed_images_exists)
{
  cs3520::Library library = cs3520::Library();
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
  catch (cs3520::InvalidUserInputException &e)
  {
    // Check if the exception message is correct
    ASSERT_EQUAL("Image lobster_link.jpg already exists"s,
                 e.what());
  }
}

TEST(test_import_images_failed_images_path_does_not_exist)
{
  cs3520::Library library = cs3520::Library();
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
  catch (cs3520::InvalidUserInputException &e)
  {
    // Check if the exception message is correct
    ASSERT_EQUAL("Couldn't find file imgs/lobster_link.png"s,
                 e.what());
  }
}

TEST(test_list_images)
{
  cs3520::Library library = cs3520::Library();
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
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/lobster_link.jpg");
  library.import_image("imgs/trogdor1.png");

  std::shared_ptr<const cs3520::Image> crab = library.get_image("crabster.jpg");
  std::shared_ptr<const cs3520::Image> lobster = library.get_image("lobster.png");
  std::shared_ptr<const cs3520::Image> trogdor1 = library.get_image("trogdor1.png");
  std::shared_ptr<const cs3520::Image> lobster_link = library.get_image("lobster_link.jpg");

  ASSERT_EQUAL(crab->get_name(), "crabster.jpg");
  ASSERT_EQUAL(lobster->get_name(), "lobster.png");
  ASSERT_EQUAL(trogdor1->get_name(), "trogdor1.png");
  ASSERT_EQUAL(lobster_link->get_name(), "lobster_link.jpg");
}

TEST(test_get_name_not_found)
{
  try
  {
    cs3520::Library library = cs3520::Library();
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/trogdor1.png");
    library.import_image("imgs/lobster_link.jpg");
    library.import_image("imgs/lobster.png");

    std::shared_ptr<const cs3520::Image> crab = library.get_image("crabster.jpg");
    std::shared_ptr<const cs3520::Image> lobster = library.get_image("lobster.png");
    std::shared_ptr<const cs3520::Image> trogdor1 = library.get_image("trogdor1.png");
    std::shared_ptr<const cs3520::Image> lobster_link = library.get_image("lobster_link.png");
    ASSERT_TRUE(false)
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Image lobster_link.png not found"s, e.what());
  }
}

TEST(test_remove_image)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.remove_image("crabster.jpg");

  std::vector<std::shared_ptr<const cs3520::Image>> list_images = library.list_images();

  ASSERT_EQUAL(library.list_images().size(), 3);
  ASSERT_EQUAL(list_images.at(0)->get_name(), "lobster.png");
  ASSERT_EQUAL(list_images.at(1)->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(list_images.at(2)->get_name(), "trogdor1.png");
}

TEST(test_remove_image_failed)
{
  try
  {
    cs3520::Library library = cs3520::Library();
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/lobster.png");
    library.import_image("imgs/trogdor1.png");
    library.import_image("imgs/lobster_link.jpg");

    library.remove_image("crabster.png");
    ASSERT_TRUE(false)
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Image crabster.png not found"s, e.what());
  }
}

TEST(test_rename_image)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.rename_image("crabster.jpg", "bestcrabster.jpg");

  std::vector<std::shared_ptr<const cs3520::Image>> list_images = library.list_images();

  ASSERT_EQUAL(list_images.at(0)->get_name(), "bestcrabster.jpg");
  ASSERT_EQUAL(list_images.at(1)->get_name(), "lobster.png");
  ASSERT_EQUAL(list_images.at(2)->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(list_images.at(3)->get_name(), "trogdor1.png");
}

TEST(test_rename_image_library_state_after_rename_image)
{
  // Create a new library and import some images
  cs3520::Library library;
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  // Rename an image in the library
  library.rename_image("crabster.jpg", "bestcrabster.jpg");

  // Ensure that the library now contains the renamed image
  std::vector<std::shared_ptr<const cs3520::Image>> images = library.list_images();
  ASSERT_EQUAL(images.size(), 4);
  ASSERT_EQUAL(images[0]->get_name(), "bestcrabster.jpg");
  ASSERT_EQUAL(images[1]->get_name(), "lobster.png");
  ASSERT_EQUAL(images[2]->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(images[3]->get_name(), "trogdor1.png");

  // Import a new image with the original name of the renamed image
  library.import_image("imgs/crabster.jpg");

  // Ensure that the library now contains both the renamed and new images,
  // and that they are sorted alphabetically by name
  images = library.list_images();
  ASSERT_EQUAL(images.size(), 5);
  ASSERT_EQUAL(images[0]->get_name(), "bestcrabster.jpg");
  ASSERT_EQUAL(images[1]->get_name(), "crabster.jpg");
  ASSERT_EQUAL(images[2]->get_name(), "lobster.png");
  ASSERT_EQUAL(images[3]->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(images[4]->get_name(), "trogdor1.png");

  // Change trogdor1.png to abester.png
  library.rename_image("trogdor1.png", "abester.png");

  images = library.list_images();
  // Ensure that the library now contains both the renamed and new images,
  // and that they are sorted alphabetically by name
  ASSERT_EQUAL(images.size(), 5);
  ASSERT_EQUAL(images[0]->get_name(), "abester.png");
  ASSERT_EQUAL(images[1]->get_name(), "bestcrabster.jpg");
  ASSERT_EQUAL(images[2]->get_name(), "crabster.jpg");
  ASSERT_EQUAL(images[3]->get_name(), "lobster.png");
  ASSERT_EQUAL(images[4]->get_name(), "lobster_link.jpg");

  // Ensure that the rename operation doesn't change the path of the images
  ASSERT_EQUAL(images[0]->get_path(), "imgs/trogdor1.png");

  // Testing rename operation with albums
  library.create_album("crabster");
  library.add_to_album("crabster", "bestcrabster.jpg");

  cs3520::Album album = library.get_album("crabster");

  ASSERT_EQUAL(album.images.at(0)->get_name(), "bestcrabster.jpg");

  // Testing rename operation with albums
  library.rename_image("bestcrabster.jpg", "worstcrabster.jpg");

  library.get_album("crabster");
  ASSERT_EQUAL(album.images.at(0)->get_name(), "worstcrabster.jpg");
}

TEST(test_rename_image_failed_name_exists)
{
  try
  {
    cs3520::Library library = cs3520::Library();
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/lobster.png");
    library.import_image("imgs/trogdor1.png");
    library.import_image("imgs/lobster_link.jpg");

    library.rename_image("crabster.jpg", "lobster.png");
    ASSERT_TRUE(false)
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Image lobster.png already exists"s, e.what())
  }
}

TEST(test_query_images)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  auto images = library.query_images("lobster");

  ASSERT_EQUAL(images.at(0)->get_name(), "lobster.png");
  ASSERT_EQUAL(images.at(1)->get_name(), "lobster_link.jpg");
}

TEST(test_query_images_jpg_test)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  auto images = library.query_images("jpg");

  ASSERT_EQUAL(images.at(0)->get_name(), "crabster.jpg");
  ASSERT_EQUAL(images.at(1)->get_name(), "lobster_link.jpg");
}

TEST(test_query_images_png_test)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  auto images = library.query_images("png");

  ASSERT_EQUAL(images.at(0)->get_name(), "lobster.png");
  ASSERT_EQUAL(images.at(1)->get_name(), "trogdor1.png");
}

TEST(test_query_images_t_test)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  auto images = library.query_images("t");

  ASSERT_EQUAL(images.at(0)->get_name(), "crabster.jpg");
  ASSERT_EQUAL(images.at(1)->get_name(), "lobster.png");
  ASSERT_EQUAL(images.at(2)->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(images.at(3)->get_name(), "trogdor1.png");
}

TEST(test_query_images_empty_string)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  // Query all images
  auto images = library.query_images("");

  ASSERT_EQUAL(images.size(), 4);
}

TEST(test_create_and_get_album)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.create_album("lobster_album");
  library.create_album("start_with_t");
  library.create_album("crab");

  ASSERT_EQUAL(library.get_album("lobster_album").name, "lobster_album");
  ASSERT_EQUAL(library.get_album("start_with_t").name, "start_with_t");
  ASSERT_EQUAL(library.get_album("crab").name, "crab");
}

TEST(test_create_album_sorted)
{
  cs3520::Library library = cs3520::Library();

  // Add albums to library
  library.create_album("Zoo");
  library.create_album("Botanical Garden");
  library.create_album("Amusement Park");

  std::vector<std::string> names = std::vector<std::string>{"Amusement Park", "Botanical Garden", "Zoo"};

  // Check that albums are sorted alphabetically
  ASSERT_EQUAL(library.get_album_names(), names);
}

TEST(test_create_album_album_exists)
{
  try
  {
    cs3520::Library library = cs3520::Library();
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/lobster.png");
    library.import_image("imgs/trogdor1.png");
    library.import_image("imgs/lobster_link.jpg");

    library.create_album("lobster_album");
    library.create_album("crab");
    library.create_album("lobster_album");
    ASSERT_TRUE(false)
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Album lobster_album already exists"s, e.what());
  }
}

TEST(test_get_album_failed_album_does_not_exists)
{
  try
  {
    cs3520::Library library = cs3520::Library();
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/lobster.png");
    library.import_image("imgs/trogdor1.png");
    library.import_image("imgs/lobster_link.jpg");

    library.create_album("lobster_album");
    library.create_album("crab");
    library.create_album("start_with_t");

    library.get_album("crabster");
    ASSERT_TRUE(false)
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Album crabster not found"s, e.what());
  }
}

TEST(test_delete_album_album_not_found)
{
  try
  {
    cs3520::Library library = cs3520::Library();
    library.import_image("imgs/crabster.jpg");
    library.create_album("lobster_album");

    library.delete_album("crab_album");
    ASSERT_TRUE(false); // If exception is not thrown test fails
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Album crab_album not found"s, e.what());
  }
}

TEST(test_delete_album_does_not_exist)
{
  try
  {
    cs3520::Library library = cs3520::Library();
    library.import_image("imgs/crabster.jpg");
    library.import_image("imgs/lobster.png");
    library.import_image("imgs/trogdor1.png");
    library.import_image("imgs/lobster_link.jpg");

    library.create_album("lobster_album");
    library.create_album("start_with_t");
    library.create_album("crab");

    library.delete_album("fish");
    ASSERT_TRUE(false);
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Album fish not found"s, e.what());
  }
}

TEST(test_delete_album)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.create_album("lobster_album");
  library.create_album("start_with_t");
  library.create_album("crab");

  library.add_to_album("lobster_album", "lobster.png");
  library.add_to_album("lobster_album", "lobster_link.jpg");
  library.add_to_album("start_with_t", "trogdor1.png");
  library.add_to_album("crab", "crabster.jpg");

  library.delete_album("start_with_t");

  // Verify that album was removed
  try
  {
    library.get_album("start_with_t");
    ASSERT_TRUE(false);
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Album start_with_t not found"s, e.what());
  }

  // Verify that image was not deleted
  ASSERT_EQUAL(library.get_image("lobster.png")->get_name(), "lobster.png");
  ASSERT_EQUAL(library.get_image("lobster_link.jpg")->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(library.get_image("crabster.jpg")->get_name(), "crabster.jpg");

  // Verify that images were removed from album
  try
  {
    cs3520::Album lobster_album = library.get_album("lobster_album");
    ASSERT_EQUAL(lobster_album.images.size(), 2);
    ASSERT_EQUAL(lobster_album.images[0]->get_name(), "lobster.png");
    ASSERT_EQUAL(lobster_album.images[1]->get_name(), "lobster_link.jpg");
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_TRUE(false);
  }

  try
  {
    cs3520::Album crab_album = library.get_album("crab");
    ASSERT_EQUAL(crab_album.images.size(), 1);
    ASSERT_EQUAL(crab_album.images.at(0)->get_name(), "crabster.jpg");
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_TRUE(false);
  }

  // Verify that images were not deleted
  ASSERT_EQUAL(library.get_image("lobster.png")->get_name(), "lobster.png");
  ASSERT_EQUAL(library.get_image("lobster_link.jpg")->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(library.get_image("trogdor1.png")->get_name(), "trogdor1.png");
  ASSERT_EQUAL(library.get_image("crabster.jpg")->get_name(), "crabster.jpg");
}

TEST(test_add_to_album)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.create_album("lobster_album");
  library.create_album("start_with_t");
  library.create_album("crab");

  // Add image to album
  library.add_to_album("lobster_album", "lobster.png");

  // Verify image was added to album
  ASSERT_EQUAL(library.get_album("lobster_album").images.size(), 1);
  ASSERT_EQUAL(library.get_album("lobster_album").images[0]->get_name(), "lobster.png");

  // Try to add same image to album again (should throw exception)
  try
  {
    library.add_to_album("lobster_album", "lobster.png");
    ASSERT_TRUE(false);
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Image lobster.png already part of album lobster_album"s, e.what());
  }

  // Add another image to album
  library.add_to_album("lobster_album", "lobster_link.jpg");

  // Verify second image was added to album
  ASSERT_EQUAL(library.get_album("lobster_album").images.size(), 2);
  ASSERT_EQUAL(library.get_album("lobster_album").images[1]->get_name(), "lobster_link.jpg");

  // Try to add image to non-existent album (should throw exception)
  try
  {
    library.add_to_album("nonexistent_album", "trogdor1.png");
    ASSERT_TRUE(false);
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Album nonexistent_album not found"s, e.what());
  }
}

TEST(test_album_image_order)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.create_album("lobster_album");

  // Add images to album
  library.add_to_album("lobster_album", "lobster.png");
  library.add_to_album("lobster_album", "trogdor1.png");
  library.add_to_album("lobster_album", "lobster_link.jpg");
  library.add_to_album("lobster_album", "crabster.jpg");

  // Verify images in album are in order they were added
  auto album_images = library.get_album("lobster_album").images;
  ASSERT_EQUAL(album_images.size(), 4);
  ASSERT_EQUAL(album_images[0]->get_name(), "lobster.png");
  ASSERT_EQUAL(album_images[1]->get_name(), "trogdor1.png");
  ASSERT_EQUAL(album_images[2]->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(album_images[3]->get_name(), "crabster.jpg");

  // Sort album and verify images are sorted
  library.sort_album("lobster_album");
  album_images = library.get_album("lobster_album").images;
  ASSERT_EQUAL(album_images.size(), 4);
  ASSERT_EQUAL(album_images[0]->get_name(), "crabster.jpg");
  ASSERT_EQUAL(album_images[1]->get_name(), "lobster.png");
  ASSERT_EQUAL(album_images[2]->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(album_images[3]->get_name(), "trogdor1.png");
}

TEST(test_add_to_album_many_albums_to_one_image)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.create_album("lobster_album");
  library.create_album("start_with_t");

  library.add_to_album("lobster_album", "lobster.png");
  library.add_to_album("start_with_t", "lobster.png");

  auto album1 = library.get_album("lobster_album");
  auto album2 = library.get_album("start_with_t");

  ASSERT_EQUAL(album1.images.size(), 1);
  ASSERT_EQUAL(album1.images.at(0)->get_name(), "lobster.png");
  ASSERT_EQUAL(album2.images.size(), 1);
  ASSERT_EQUAL(album2.images.at(0)->get_name(), "lobster.png");
}

// test
TEST(test_add_to_album_lower_bound_does_not_work)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.create_album("lobster_album");
  library.create_album("start_with_t");

  library.add_to_album("lobster_album", "crabster.jpg");
  library.add_to_album("lobster_album", "lobster_link.jpg");
  library.add_to_album("lobster_album", "lobster.png");
  library.add_to_album("start_with_t", "lobster.png");

  auto album1 = library.get_album("lobster_album");

  ASSERT_EQUAL(album1.images.at(2)->get_name(), "lobster.png");
  ASSERT_EQUAL(album1.images.at(1)->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(album1.images.at(0)->get_name(), "crabster.jpg");

  try
  {
    library.add_to_album("lobster_album", "lobster.png");
    ASSERT_TRUE(false);
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Image lobster.png already part of album lobster_album"s, e.what());
  }
}

TEST(test_remove_from_album_lower_bound_does_not_work)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.create_album("lobster_album");
  library.create_album("start_with_t");

  library.add_to_album("lobster_album", "lobster_link.jpg");
  library.add_to_album("lobster_album", "lobster.png");
  library.add_to_album("lobster_album", "crabster.jpg");
  library.add_to_album("start_with_t", "lobster.png");

  auto album1 = library.get_album("lobster_album");

  ASSERT_EQUAL(album1.images.at(1)->get_name(), "lobster.png");
  ASSERT_EQUAL(album1.images.at(0)->get_name(), "lobster_link.jpg");
  ASSERT_EQUAL(album1.images.at(2)->get_name(), "crabster.jpg");

  try
  {
    library.remove_from_album("lobster_album", "lobster.png");
    ASSERT_TRUE(true);
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_TRUE(false);
  }
}

TEST(test_remove_from_album)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");

  library.create_album("lobster_album");
  library.add_to_album("lobster_album", "lobster.png");
  library.add_to_album("lobster_album", "trogdor1.png");
  ASSERT_EQUAL(library.get_album("lobster_album").images.size(), 2);

  library.remove_from_album("lobster_album", "lobster.png");
  ASSERT_EQUAL(library.get_album("lobster_album").images.size(), 1);

  try
  {
    library.remove_from_album("non_existent_album", "trogdor1.png");
    ASSERT_TRUE(false);
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Album non_existent_album not found"s, e.what());
  }

  try
  {
    library.remove_from_album("lobster_album", "non_existent_image");
    ASSERT_TRUE(false);
  }
  catch (cs3520::InvalidUserInputException &e)
  {
    ASSERT_EQUAL("Image non_existent_image not part of album lobster_album"s, e.what());
  }
}

TEST(TestDeleteAlbum)
{
  cs3520::Library library = cs3520::Library();
  library.create_album("Album C");
  library.create_album("Album A");
  library.create_album("Album D");
  library.create_album("Album B");

  ASSERT_EQUAL(library.get_album_names().size(), 4);

  library.delete_album("Album B");
  auto albums = library.get_album_names();

  ASSERT_EQUAL(albums.size(), 3);
  ASSERT_EQUAL(albums.at(0), "Album A");
  ASSERT_EQUAL(albums.at(1), "Album C");
  ASSERT_EQUAL(albums.at(2), "Album D");
}

TEST(test_sort_album)
{
  // create library instance and import some images
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  // create an album and add images to it
  library.create_album("my_album");
  library.add_to_album("my_album", "lobster.png");
  library.add_to_album("my_album", "crabster.jpg");
  library.add_to_album("my_album", "trogdor1.png");
  library.add_to_album("my_album", "lobster_link.jpg");

  // sort the album
  library.sort_album("my_album");

  // verify that the images in the album are sorted
  std::vector<std::string> expected_order = {"crabster.jpg", "lobster.png", "lobster_link.jpg", "trogdor1.png"};
  std::vector<std::string> actual_order;

  std::transform(library.get_album("my_album").images.begin(),
                 library.get_album("my_album").images.end(), back_inserter(actual_order),
                 [](const std::shared_ptr<cs3520::Image> &image)
                 { return image->get_name(); });
  ASSERT_EQUAL(expected_order, actual_order);
}

TEST(test_album_sort)
{
  cs3520::Library lib;

  // Add some albums to the library
  lib.create_album("Album C");
  lib.create_album("Album A");
  lib.create_album("Album B");

  // Get the album names
  std::vector<std::string> albums_names = lib.get_album_names();

  // Ensure that albums are sorted correctly
  ASSERT_EQUAL(albums_names.at(0), "Album A");
  ASSERT_EQUAL(albums_names.at(1), "Album B");
  ASSERT_EQUAL(albums_names.at(2), "Album C");

  // Add a new album
  lib.create_album("Album D");

  std::vector<std::string> albums_names_new = lib.get_album_names();

  // Ensure that the new album is inserted in the correct position
  ASSERT_EQUAL(albums_names_new.at(0), "Album A");
  ASSERT_EQUAL(albums_names_new.at(1), "Album B");
  ASSERT_EQUAL(albums_names_new.at(2), "Album C");
  ASSERT_EQUAL(albums_names_new.at(3), "Album D");

  lib.delete_album("Album A");

  std::vector<std::string> deleted_album = lib.get_album_names();

  // Ensure that the new album is inserted in the correct position
  ASSERT_EQUAL(deleted_album.at(0), "Album B");
  ASSERT_EQUAL(deleted_album.at(1), "Album C");
  ASSERT_EQUAL(deleted_album.at(2), "Album D");
}

TEST(delete_image_and_remove_from_album)
{
  cs3520::Library library = cs3520::Library();
  library.import_image("imgs/crabster.jpg");
  library.import_image("imgs/lobster.png");
  library.import_image("imgs/trogdor1.png");
  library.import_image("imgs/lobster_link.jpg");

  library.create_album("lobster_album");
  library.create_album("start_with_t");
  library.create_album("crab");

  library.add_to_album("lobster_album", "lobster.png");
  library.add_to_album("lobster_album", "lobster_link.jpg");
  library.add_to_album("start_with_t", "trogdor1.png");
  library.add_to_album("start_with_t", "lobster.png");
  library.add_to_album("crab", "crabster.jpg");

  library.remove_image("lobster.png");
  library.remove_image("lobster_link.jpg");

  ASSERT_EQUAL(library.get_album("lobster_album").images.size(), 0);
  ASSERT_EQUAL(library.get_album("start_with_t").images.size(), 1)
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
