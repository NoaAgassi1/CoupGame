
#include "doctest.h"
#include "PlayersList.hpp"
#include "Spy.hpp"
#include "Governor.hpp"

TEST_CASE("PlayersList turn logic") {
    PlayersList& list = PlayersList::getInstance();
    list.clear();

    list.addPlayer(new Spy("Alice"));
    list.addPlayer(new Governor("Bob"));

    Player* current = list.current();
    CHECK(current->getName() == "Alice");

    Player* next = list.getNext();
    CHECK(next->getName() == "Bob");

    Player* again = list.getNext();
    CHECK(again->getName() == "Alice");

    list.clear();
}
