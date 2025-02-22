#ifndef STATIC_LINK_VW
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include "test_common.h"
#include "parse_args.h"
#include "parse_example.h"

BOOST_AUTO_TEST_CASE(spoof_hex_encoded_namespace_test)
{
  BOOST_CHECK_EQUAL(spoof_hex_encoded_namespaces("test"), "test");
  BOOST_CHECK_EQUAL(spoof_hex_encoded_namespaces("10"), "10");
  BOOST_CHECK_EQUAL(spoof_hex_encoded_namespaces("\\x01"), "\x01");
  BOOST_CHECK_EQUAL(spoof_hex_encoded_namespaces("\\xab"), "\xab");
  BOOST_CHECK_EQUAL(spoof_hex_encoded_namespaces("\\x01 unrelated \\x56"), "\x01 unrelated \x56");
}

BOOST_AUTO_TEST_CASE(parse_text_with_extents)
{
  auto* vw = VW::initialize("--no_stdin --quiet", nullptr, false, nullptr, nullptr);
  auto* ex = VW::read_example(*vw, "|features a b |new_features a b |features2 c d |empty |features c d");

  BOOST_CHECK_EQUAL(ex->feature_space['f'].size(), 6);
  BOOST_CHECK_EQUAL(ex->feature_space['n'].size(), 2);
  BOOST_CHECK_EQUAL(ex->feature_space['3'].size(), 0);

  BOOST_CHECK_EQUAL(ex->feature_space['f'].namespace_extents.size(), 3);
  BOOST_CHECK_EQUAL(ex->feature_space['n'].namespace_extents.size(), 1);

  BOOST_CHECK_EQUAL(
      ex->feature_space['f'].namespace_extents[0], (VW::namespace_extent{0, 2, VW::hash_space(*vw, "features")}));
  BOOST_CHECK_EQUAL(
      ex->feature_space['f'].namespace_extents[1], (VW::namespace_extent{2, 4, VW::hash_space(*vw, "features2")}));
  BOOST_CHECK_EQUAL(
      ex->feature_space['f'].namespace_extents[2], (VW::namespace_extent{4, 6, VW::hash_space(*vw, "features")}));

  VW::finish_example(*vw, *ex);
  VW::finish(*vw);
}
