/**
 * \file genetika_teszt.cpp
 *
 * Genetika nevű szorgalmi feladat tesztjei gtest_lite eszközkészletével megvalósítva.
 * A szorgalmi feladat megoldásához ezt az állományt nem kell beadni (feltölteni).
 *
 * A ELKESZULT makró vezérli az egyes tesztesetek fordítását, ezzel lehetővé válik
 * hogy kisebb lépésekben teszteljünk.
 * Kezdetben ez 0, azaz nem tesztel semmit!
 *
 */

#include <iostream>

#include "gtest_lite.h"
#include "allapotgep.h"
#include "memtrace.h"

#define ELKESZULT 3

int main() {

    GTINIT(std::cin); // Csak C(J)PORTA működéséhez kell
    #if ELKESZULT > 0
    /// Azt vizsgálja, hogy dob-e hibát a fájl megnyitásakor
        TEST(Konfig, KonfigHiba) {
            Allapotgep gep;
            try {
                EXPECT_THROW_THROW(gep.konfigural("nincs_ilyen_fajl"), const char* p);
            } catch (const char *p) {
            #ifdef CPORTA
                EXPECT_ENVCASEEQ("ORG_ID", p);
            #endif
            }
        } END
    #endif // ELKESZULT > 0

    #if ELKESZULT > 1
    /// Azt vizsgálja, hogy be tudja-e olvasni a konfigurációs fájlt
        TEST(ParosTrimin, fajbolkonfig1) {
            Allapotgep gep;
            ASSERT_NO_THROW(gep.konfigural("paros.txt"));
            EXPECT_STREQ("ParosTimin", gep.aktualisallapot());
        } END
    #endif // ELKESZULT > 1

    #if ELKESZULT > 1
    /// Kipróbálja az egyik pédakonfigot
        TEST(ParosTrimin, fajbolkonfig1) {
            Allapotgep gep;
            ASSERT_NO_THROW(gep.konfigural("paros.txt"));
            EXPECT_STREQ("ParosTimin", gep.aktualisallapot());
            Bazis demo[] = {Timin, Citozin, Guanin, Adenin, Timin};
            EXPECT_EQ(true, gep.feldolgoz(demo, 5));
            gep.alaphelyzet();
            EXPECT_STREQ("ParosTimin", gep.aktualisallapot());
            EXPECT_EQ(true, gep.elfogad());
            EXPECT_EQ(false, gep.feldolgoz(demo, 4));
        } END
    #endif

    #if ELKESZULT > 2
    /// Kipróbálja az másik pédakonfigot
        TEST(Implikacio: AA->CC, fajbolkonfig2) {
            Allapotgep gep;
            ASSERT_NO_THROW(gep.konfigural("implikacio.txt"));
            EXPECT_STREQ("Alap", gep.aktualisallapot());
            Bazis demo[] = {Adenin, Adenin, Timin, Citozin, Adenin, Citozin, Citozin, Guanin};
            EXPECT_EQ(true, gep.feldolgoz(demo, 8));
            gep.alaphelyzet();
            gep.atmenet(Citozin);
            EXPECT_STREQ("C1", gep.aktualisallapot());
            gep.atmenet(Adenin);
            gep.atmenet(Timin);
            EXPECT_STREQ("A1", gep.aktualisallapot());
            Bazis test[] = {Citozin, Citozin, Timin, Adenin, Guanin, Citozin};
            gep.feldolgoz(test, 6);
            EXPECT_STREQ("C2", gep.aktualisallapot());
        } END
    #endif

    /// Itt a vége
    if (ELKESZULT < 3)
      ADD_FAILURE() << "\nNem futott minden teszteset!" << std::endl;

    GTEND(std::cerr); // Csak C(J)PORTA működéséhez kell
    return 0;
}

