#ifndef CPP_UNIT_CDISTTESTCASE_H
#define CPP_UNIT_CDISTTESTCASE_H

#include <cppunit/extensions/HelperMacros.h>

#include <cybergarage/bittorrent/cbittorrent.h>

class CDistTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( CDistTestCase );

  CPPUNIT_TEST( testBencodingString );
  CPPUNIT_TEST( testBencodingInteger );
  CPPUNIT_TEST( testBencodingList );
  CPPUNIT_TEST( testBencodingDictionary );
  CPPUNIT_TEST( testBencodingDictionaryNest );
  CPPUNIT_TEST( testMessageHasPiece );
  //CPPUNIT_TEST( testMetainfoFetch );
  CPPUNIT_TEST( testMetainfoLoad);
  CPPUNIT_TEST( testBlockDevice );
  CPPUNIT_TEST( testTrackerLoad);
  //CPPUNIT_TEST( testSHA1 );
  CPPUNIT_TEST( testPeerHandshake );
  CPPUNIT_TEST( testFileMgr );

  CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

protected:
  
	void testBencodingString();
	void testBencodingInteger();
	void testBencodingList();
	void testBencodingDictionary();
	void testBencodingDictionaryNest();
	void testMessageHasPiece();
	void testMetainfoFetch();
	void testMetainfoLoad();
	void testTrackerLoad();
	void testSHA1();
	void testPeerHandshake();
	void testBlockDevice();
	void testFileMgr();
};

#endif
