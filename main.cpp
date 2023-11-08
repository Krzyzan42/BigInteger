#include <iostream>
#include <assert.h>
#include "BigInteger.h"

void createNumberTests()
{
    assert(BigInteger(0).toString() == "0");
    assert(BigInteger(1).toString() == "1");
    assert(BigInteger(1000).toString() == "1000");
    assert(BigInteger(32527).toString() == "32527");
    assert(BigInteger(-89).toString() == "-89");
}

void addTests()
{
    assert((BigInteger(5) + BigInteger(7)).toString() == "12");
    assert((BigInteger(0) + BigInteger(0)).toString() == "0");
    assert((BigInteger(15) + BigInteger(95)).toString() == "110");
    assert((BigInteger(16) + BigInteger(43)).toString() == "59");
    assert((BigInteger(5) + BigInteger(-7)).toString() == "-2");
    assert((BigInteger(7) + BigInteger(-5)).toString() == "2");
    assert((BigInteger(-7) + BigInteger(5)).toString() == "-2");
    assert((BigInteger(-7) + BigInteger(-5)).toString() == "-12");
}

void subTests()
{
    assert((BigInteger(7) - BigInteger(5)).toString() == "2");
    assert((BigInteger(0) - BigInteger(0)).toString() == "0");
    assert((BigInteger(95) - BigInteger(15)).toString() == "80");
    assert((BigInteger(28) - BigInteger(27)).toString() == "1");
    assert((BigInteger(-50) - BigInteger(27)).toString() == "-77");
    assert((BigInteger(-20) - BigInteger(-27)).toString() == "7");
}

void mulTests()
{
    assert((BigInteger(0) * BigInteger(0)).toString() == "0");
    assert((BigInteger(1) * BigInteger(67)).toString() == "67");
    assert((BigInteger(25) * BigInteger(8)).toString() == "200");
    assert((BigInteger(2147000) * BigInteger(2147000)).toString() == "4609609000000");
    assert((BigInteger(-582) * BigInteger(324)).toString() == "-188568");
    assert((BigInteger(-16) * BigInteger(-729)).toString() == "11664");
}

void divTests()
{
    assert((BigInteger(5) / BigInteger(7)).toString() == "0");
    assert((BigInteger(25) / BigInteger(5)).toString() == "5");
    assert((BigInteger(31) / BigInteger(4)).toString() == "7");
    assert((BigInteger(325426) / BigInteger(28)).toString() == "11622");
    assert((BigInteger(5) / BigInteger(0)).toString() == "0");
    assert((BigInteger(-87) / BigInteger(2)).toString() == "-43");
}

void compareTests() {
    assert((BigInteger(0) < BigInteger(0)) == false);
    assert((BigInteger(41) < BigInteger(25)) == false);
    assert((BigInteger(34) < BigInteger(85)) == true);
    assert((BigInteger(56) < BigInteger(-12)) == false);
    assert((BigInteger(56) < BigInteger(-124)) == false);
    assert((BigInteger(-15) < BigInteger(25)) == true);
    assert((BigInteger(-15) < BigInteger(7)) == true);
    assert((BigInteger(-234) < BigInteger(-56)) == true);
    assert((BigInteger(-89) < BigInteger(-114)) == false);
    assert((BigInteger(275) < BigInteger(275)) == false);
    assert((BigInteger(-325) < BigInteger(325)) == true);

    assert((BigInteger(0) <= BigInteger(0)) == true);
    assert((BigInteger(41) <= BigInteger(25)) == false);
    assert((BigInteger(34) <= BigInteger(85)) == true);
    assert((BigInteger(56) <= BigInteger(-12)) == false);
    assert((BigInteger(56) <= BigInteger(-124)) == false);
    assert((BigInteger(-15) <= BigInteger(25)) == true);
    assert((BigInteger(-15) <= BigInteger(7)) == true);
    assert((BigInteger(-234) <= BigInteger(-56)) == true);
    assert((BigInteger(-89) <= BigInteger(-114)) == false);
    assert((BigInteger(275) <= BigInteger(275)) == true);
    assert((BigInteger(-325) <= BigInteger(325)) == true);

    assert((BigInteger(0) == BigInteger(0)) == true);
    assert((BigInteger(41) == BigInteger(25)) == false);
    assert((BigInteger(34) == BigInteger(85)) == false);
    assert((BigInteger(56) == BigInteger(-12)) == false);
    assert((BigInteger(56) == BigInteger(-124)) == false);
    assert((BigInteger(-15) == BigInteger(25)) == false);
    assert((BigInteger(-15) == BigInteger(7)) == false);
    assert((BigInteger(-234) == BigInteger(-56)) == false);
    assert((BigInteger(-89) == BigInteger(-114)) == false);
    assert((BigInteger(275) == BigInteger(275)) == true);
    assert((BigInteger(-325) == BigInteger(325)) == false);

    assert((BigInteger(0) > BigInteger(0)) == false);
    assert((BigInteger(41) > BigInteger(25)) == true);
    assert((BigInteger(34) > BigInteger(85)) == false);
    assert((BigInteger(56) > BigInteger(-12)) == true);
    assert((BigInteger(56) > BigInteger(-124)) == true);
    assert((BigInteger(-15) > BigInteger(25)) == false);
    assert((BigInteger(-15) > BigInteger(7)) == false);
    assert((BigInteger(-234) > BigInteger(-56)) == false);
    assert((BigInteger(-89) > BigInteger(-114)) == true);
    assert((BigInteger(275) > BigInteger(275)) == false);
    assert((BigInteger(-325) > BigInteger(325)) == false);

    assert((BigInteger(0) >= BigInteger(0)) == true);
    assert((BigInteger(41) >= BigInteger(25)) == true);
    assert((BigInteger(34) >= BigInteger(85)) == false);
    assert((BigInteger(56) >= BigInteger(-12)) == true);
    assert((BigInteger(56) >= BigInteger(-124)) == true);
    assert((BigInteger(-15) >= BigInteger(25)) == false);
    assert((BigInteger(-15) >= BigInteger(7)) == false);
    assert((BigInteger(-234) >= BigInteger(-56)) == false);
    assert((BigInteger(-89) >= BigInteger(-114)) == true);
    assert((BigInteger(275) >= BigInteger(275)) == true);
    assert((BigInteger(-325) >= BigInteger(325)) == false);

    assert((BigInteger(0) != BigInteger(0)) == false);
    assert((BigInteger(41) != BigInteger(25)) == true);
    assert((BigInteger(34) != BigInteger(85)) == true);
    assert((BigInteger(56) != BigInteger(-12)) == true);
    assert((BigInteger(56) != BigInteger(-124)) == true);
    assert((BigInteger(-15) != BigInteger(25)) == true);
    assert((BigInteger(-15) != BigInteger(7)) == true);
    assert((BigInteger(-234) != BigInteger(-56)) == true);
    assert((BigInteger(-89) != BigInteger(-114)) == true);
    assert((BigInteger(275) != BigInteger(275)) == false);
    assert((BigInteger(-325) != BigInteger(325)) == true);
}


int main()
{
    createNumberTests();
    addTests();
    subTests();
    mulTests();
    divTests();
    compareTests();
    std::cout << "All tests passed!" << std::endl;

    return 0;
}