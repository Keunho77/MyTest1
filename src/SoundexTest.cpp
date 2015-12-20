
#include <iostream>
#include "gmock/gmock.h"
#include "Soundex.h"

using namespace testing;

class SoundexEncoding: public testing::Test {
public :
	Soundex soundex;
};


TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord) {
	ASSERT_THAT(soundex.encode("Ab"), Eq("A100"));
}

TEST_F(SoundexEncoding, PadsWithZeroToEnsureThreeDigits) {
	ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits) {
	ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
	ASSERT_THAT(soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings) {
	ASSERT_THAT(soundex.encodedDigit('b'), Eq(soundex.encodedDigit('f')));
	ASSERT_THAT(soundex.encodedDigit('c'), Eq(soundex.encodedDigit('g')));
	ASSERT_THAT(soundex.encodedDigit('d'), Eq(soundex.encodedDigit('t')));

	ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

