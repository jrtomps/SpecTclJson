
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>

#include <TH1.h>
#include <json/json.h>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include "GateInfo.h"

#include "config.h"

#define private public
#define protected public
#include "GateCmdParser.h"
#undef protected
#undef private

using namespace std;

class GateCmdParserTest : public CppUnit::TestFixture {
  public:
  CPPUNIT_TEST_SUITE(GateCmdParserTest);
  CPPUNIT_TEST( parseList_0 );
  CPPUNIT_TEST( parseList_1 );
  CPPUNIT_TEST( parseList_2 );
  CPPUNIT_TEST( parseList_3 );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {
  }
  void tearDown() {
  }
protected:

  void parseList_0();
  void parseList_1();
  void parseList_2();
  void parseList_3();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GateCmdParserTest);

void GateCmdParserTest::parseList_0()
{
    using SpJs::Slice;

    std::stringstream ss;
    ss << JSON_TEST_DIR << "/gate1d.json";
    std::ifstream file(ss.str().c_str());

    Json::Value value;
    file >> value;
    file.close();

    auto res = SpJs::GateCmdParser().parseList(value);
    CPPUNIT_ASSERT_EQUAL(size_t(1),res.size());

    Slice act;
    CPPUNIT_ASSERT_NO_THROW( act = dynamic_cast<Slice&>(*(res.at(0).get())) );

    Slice exp("test", "event.raw.00", 0.0, 10.0);

    CPPUNIT_ASSERT(exp == act);

}

void GateCmdParserTest::parseList_1()
{
    using SpJs::Contour;

    std::stringstream ss;
    ss << JSON_TEST_DIR << "/gate2dc.json";
    std::ifstream file(ss.str().c_str());

    Json::Value value;
    file >> value;
    file.close();

    auto res = SpJs::GateCmdParser().parseList(value);
    CPPUNIT_ASSERT_EQUAL(size_t(1),res.size());

    Contour act;
    CPPUNIT_ASSERT_NO_THROW( act = dynamic_cast<Contour&>(*(res.at(0).get())) );

    Contour exp("contour_002",
                "event.raw.00", "event.raw.01",
                {{324.0, 577.0},
                 {635.0, 619.0},
                 {659.0, 387.0},
                 {419.0, 323.0}});


    CPPUNIT_ASSERT(exp == act);

}

void GateCmdParserTest::parseList_2()
{
    using SpJs::Band;

    std::stringstream ss;
    ss << JSON_TEST_DIR << "/gate2db.json";
    std::ifstream file(ss.str().c_str());

    Json::Value value;
    file >> value;
    file.close();

    auto res = SpJs::GateCmdParser().parseList(value);
    CPPUNIT_ASSERT_EQUAL(size_t(1),res.size());

    Band act;
    CPPUNIT_ASSERT_NO_THROW( act = dynamic_cast<Band&>(*(res.at(0).get())) );

    Band exp("band_000",
             "event.raw.00", "event.raw.01",
             {{165.0, 464.0}, {611.0, 509.0}, {778.0, 334.0}});


    CPPUNIT_ASSERT(exp == act);

}

void GateCmdParserTest::parseList_3()
{
  // assume we have a F gate (produced when deleted)
  // we should just ignore it.

    std::stringstream ss;
    ss << JSON_TEST_DIR << "/gatef.json";
    std::ifstream file(ss.str().c_str());

    Json::Value value;
    file >> value;
    file.close();

    vector<unique_ptr<SpJs::GateInfo>> res;

    CPPUNIT_ASSERT_NO_THROW(res = SpJs::GateCmdParser().parseList(value));
    CPPUNIT_ASSERT_EQUAL(size_t(1), res.size());

    SpJs::False act;
    CPPUNIT_ASSERT_NO_THROW( act = dynamic_cast<SpJs::False&>(*(res.at(0).get())) );

    SpJs::False exp("test");
    CPPUNIT_ASSERT(exp == act);

}
