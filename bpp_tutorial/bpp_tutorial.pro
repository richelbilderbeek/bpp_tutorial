TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test_dna_sequence.cpp \
    test_newick.cpp

# C++11
QMAKE_CXX = g++-5
QMAKE_LINK = g++-5
QMAKE_CC = gcc-5
QMAKE_CXXFLAGS += -std=c++11

# Bio++
LIBS += -lbpp-core -lbpp-seq -lbpp-phyl -lbpp-popgen -lbpp-qt -lbpp-raa

# Boost.Test
LIBS += -lboost_unit_test_framework
