#include "doctest.h"
#include "Spy.hpp"
#include "Governor.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"
#include "Judge.hpp"
#include "General.hpp"

TEST_CASE("Spy: name, role, and specialAction") {
    Spy spy("SpyGuy");
    CHECK(spy.getName() == "SpyGuy");
    CHECK(spy.role() == "Spy");

    Governor target("Target");
    target.tax(); // +3 coins
    std::string result = spy.specialAction(&target);
    CHECK(result.find("blocked") != std::string::npos);
}

TEST_CASE("Governor: tax increases coins") {
    Governor gov("GovGuy");
    CHECK(gov.getCoins() == 0);
    std::string result = gov.tax();
    CHECK(result.find("3 coins") != std::string::npos);
    CHECK(gov.getCoins() == 3);
}

TEST_CASE("Baron: basic attributes") {
    Baron baron("Baroness");
    CHECK(baron.getName() == "Baroness");
    CHECK(baron.role() == "Baron");
    CHECK(baron.getCoins() == 0);
}

TEST_CASE("Merchant: gather and coin count") {
    Merchant m("TradeMaster");
    CHECK(m.getCoins() == 0);
    m.gather();  // +1
    m.gather();  // +1
    m.gather();  // +1
    CHECK(m.getCoins() == 3);
}

TEST_CASE("Judge: name and role check") {
    Judge judge("Justice");
    CHECK(judge.getName() == "Justice");
    CHECK(judge.role() == "Judge");
    CHECK(judge.getCoins() == 0);
}

TEST_CASE("General: name, role, gather") {
    General gen("Commander");
    CHECK(gen.getName() == "Commander");
    CHECK(gen.role() == "General");
    CHECK(gen.getCoins() == 0);
    gen.gather();
    CHECK(gen.getCoins() == 1);
}
