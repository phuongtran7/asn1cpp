#define BOOST_TEST_MODULE stringTests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "TestPrintableString.h"

#include "asn1cpp/Seq.hpp"
#include "asn1cpp/Getter.hpp"
#include "asn1cpp/Setter.hpp"
#include "asn1cpp/Encoding.hpp"

BOOST_AUTO_TEST_CASE( construction ) {
    auto test = asn1cpp::makeSeq(TestPrintableString);
}

BOOST_AUTO_TEST_CASE( assignment ) {
    const std::string value = "abcd";

    auto test = asn1cpp::makeSeq(TestPrintableString);

    asn1cpp::set(test->string, value);

    auto v = asn1cpp::get(test->string, std::string);

    BOOST_CHECK_EQUAL(value, v);
}

BOOST_AUTO_TEST_CASE( encoding ) {
    const std::string value = "qwerty";

    auto test = asn1cpp::makeSeq(TestPrintableString);

    asn1cpp::set(test->string, value);

    auto str = asn1cpp::ber::encode(test);
    auto recoveredTest = asn1cpp::ber::decode(str, TestPrintableString);

    BOOST_CHECK(recoveredTest);

    auto v = asn1cpp::get(recoveredTest->string, std::string);

    BOOST_CHECK_EQUAL(value, v);
}
