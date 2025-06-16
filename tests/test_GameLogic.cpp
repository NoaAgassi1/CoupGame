#include "doctest.h"
#include "PlayersList.hpp"
#include "Spy.hpp"
#include "Governor.hpp"
#include "Merchant.hpp"
#include "General.hpp"
#include "Judge.hpp"


TEST_CASE("Sanction blocks gather and tax") {
    PlayersList& list = PlayersList::getInstance();
    list.clear();  

    Governor* g1 = new Governor("Gov1");
    General* g2 = new General("Gov2");

    list.addPlayer(g1);
    list.addPlayer(g2);

    *g1 += 4;  

    std::string result = g1->sanction(g2);  
    CHECK(result.find("[SUCCESS]") != std::string::npos);
    CHECK(g2->getIsSanctioned());          

    std::string gatherFail = g2->gather();
    std::string taxFail = g2->tax();

    CHECK(gatherFail.find("sanctioned") != std::string::npos);
    CHECK(taxFail.find("sanctioned") != std::string::npos);

    list.clear();  
}



TEST_CASE("Bribe gives extra turn once") {
    PlayersList& list = PlayersList::getInstance();
    list.clear();

    Governor* p1 = new Governor("Alice");
    General* p2 = new General("Bob");

    *p1 += 4; 

    list.addPlayer(p1);
    list.addPlayer(p2);

    CHECK(list.current()->getName() == "Alice");

    std::string bribeResult = p1->bribe();
    CHECK(bribeResult.find("[PENDING]") != std::string::npos);
    CHECK(p1->getCoins() == 0);


    p1->setBribe(true);

    Player* next = list.getNext();
    CHECK(next->getName() == "Alice"); 

    Player* then = list.getNext();
    CHECK(then->getName() == "Bob");

    list.clear();
}

TEST_CASE("Arrest reduces coins indirectly") {
    Merchant* m = new Merchant("Target");
    General* g = new General("Attacker");

    m->gather(); 
    m->gather(); 
    CHECK(m->getCoins() == 2);

    g->arrest(m); 

    CHECK(m->getCoins() == 0); 
    delete m;
    delete g;
}

TEST_CASE("Spy blocks arrest on target") {
    Spy* spy = new Spy("S");
    General* target = new General("T");

    spy->specialAction(target); 

    target->gather();
    target->gather();

    General* g = new General("Attacker");
    g->arrest(target); 

    CHECK(target->getCoins() >= 2);

    delete spy;
    delete target;
    delete g;
}


TEST_CASE("Turn rotation resets sanction") {
    PlayersList& list = PlayersList::getInstance();
    list.clear();

    General* a = new General("A");
    General* b = new General("B");

    *b += 3; 
    list.addPlayer(a);
    list.addPlayer(b);

    CHECK(list.current()->getName() == "A");

    list.getNext(); 
    CHECK(list.current()->getName() == "B");

    std::string result = b->sanction(a); 
    CHECK(result.find("[SUCCESS]") != std::string::npos);

    list.getNext();
    std::string failGather = a->gather();
    CHECK(failGather.find("sanctioned") != std::string::npos);

    list.getNext();

    list.getNext();
    std::string successGather = a->gather();
    CHECK(successGather.find("[SUCCESS]") != std::string::npos);

    list.clear();
}

