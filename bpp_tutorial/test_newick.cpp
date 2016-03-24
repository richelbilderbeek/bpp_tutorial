#include <boost/test/unit_test.hpp>
#include <Bpp/Phyl/Io/Newick.h>
#include <Bpp/Phyl/Tree.h>
#include <Bpp/Phyl/TreeTools.h>
#include <Bpp/Phyl/Graphics/TreeDrawing.h>
#include <iostream>
#include <fstream>

BOOST_AUTO_TEST_CASE(test_newick_1)
{
  const std::string filename{"temp_newick.txt"};
  {
    std::ofstream f(filename);
    f << "((A:0.1, B:0.15):0.2, C:0.27);";
  }
  const bpp::Newick reader;
  const bpp::Tree * const tree = reader.read(filename);
  std::remove(filename.c_str());
  BOOST_CHECK(tree->getNumberOfLeaves() == 3);
}

BOOST_AUTO_TEST_CASE(test_newick_2)
{
  const std::string filename{"temp_newick.txt"};
  {
    std::ofstream f(filename);
    f << "(A:0.1, B:0.15)90:0.2;";
  }
  const bpp::Newick reader;
  const bpp::Tree * const tree = reader.read(filename);
  std::remove(filename.c_str());
  BOOST_CHECK(tree->getNumberOfLeaves() == 2);
}

BOOST_AUTO_TEST_CASE(test_newick_3)
{
  const std::string filename{"temp_newick.txt"};
  {
    std::ofstream f(filename);
    f << "A:15;";
  }
  const bpp::Newick reader;
  const bpp::Tree * const tree = reader.read(filename);
  std::remove(filename.c_str());
  BOOST_CHECK(tree->getNumberOfLeaves() == 1);
}



