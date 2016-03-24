#include <boost/test/unit_test.hpp>
#include <fstream>

#include <Bpp/Seq/Alphabet.all>
#include <Bpp/Seq/Sequence.h>

#include <Bpp/Phyl/Model/SubstitutionModel.h>
#include <Bpp/Phyl/Model/Nucleotide/JCnuc.h>
#include <Bpp/Phyl/Simulation/HomogeneousSequenceSimulator.h>
#include <Bpp/Phyl/Tree.h>
#include <Bpp/Phyl/Io/Newick.h>
#include <Bpp/Numeric/Prob/GammaDiscreteDistribution.h>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_CASE(test_dna_sequence)
{
  const std::string name{"test"};
  const std::string dna{"ATGC"};
  const bpp::BasicSequence sequence(
    name, dna, &bpp::AlphabetTools::DNA_ALPHABET
  );
  BOOST_CHECK(name == sequence.getName());
  BOOST_CHECK(dna == sequence.toString());
  BOOST_CHECK(dna.size() == sequence.size());
}


BOOST_AUTO_TEST_CASE(test_bpp_2)
{
  //Create substitution model
  const bpp::JCnuc model(&bpp::AlphabetTools::DNA_ALPHABET);

  //Create mutation distribution model
  //(Note: wouldn't Poisson be better?)
  const int gamma_distribution_n_categories{4};
  const double gamma_distribution_alpha{0.5}; //Mutation rate
  const bpp::GammaDiscreteDistribution rate(
    gamma_distribution_n_categories,
    gamma_distribution_alpha
  );

  //Create an ancestral sequence
  const std::string name{"test"};
  const std::string dna{"AAAAAAAAAA"};
  bpp::BasicSequence sequence(
    name, dna, &bpp::AlphabetTools::DNA_ALPHABET
  );

  //Create a tree of one branch for that sequence to evolve over
  const std::string filename{"temp_newick.txt"};
  {
    std::ofstream f(filename);
    f << "A:15;";
  }
  const bpp::Newick reader;
  const bpp::Tree * const tree = reader.read(filename);
  std::remove(filename.c_str()); //Clean up

  //Create a simulator
  bpp::HomogeneousSequenceSimulator simulator(&model, &rate, tree);
  //Q: How to put the sequence in?

  BOOST_CHECK("AAAAAAAAAA" != sequence.toString()); //Sequence should have changed
}

#pragma GCC diagnostic pop
