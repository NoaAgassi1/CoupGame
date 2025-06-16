#include "doctest.h"
#include "Spy.hpp"
#include "Governor.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"
#include "Judge.hpp"
#include "General.hpp"

TEST_CASE("Player base checks via derived roles") {
    Spy spy("Alice");
    CHECK(spy.getName() == "Alice");
    CHECK(spy.role() == "Spy");
    CHECK(spy.getCoins() == 0);

    Governor gov("Bob");
    CHECK(gov.getName() == "Bob");
    CHECK(gov.role() == "Governor");

    Baron baron("Charlie");
    CHECK(baron.role() == "Baron");

    Merchant merch("Dana");
    CHECK(merch.role() == "Merchant");

    Judge judge("Eve");
    CHECK(judge.role() == "Judge");

    General gen("Frank");
    CHECK(gen.role() == "General");
}
