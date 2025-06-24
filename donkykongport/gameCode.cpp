#include "game.h"
#include "console.h"
#include "mapper.h"

void game::reset() {
    flgI = true;
    flgD = false;
    a = 0x10;
    setLoadFlag(a);
    myMapper->writeCPU(0x2000, a);
    x = 0xFF;
    setLoadFlag(x);
    s = x;
    do {
        a = myMapper->readCPU(0x2002);
        setLoadFlag(a);
        opAND(0x80);
    } while (flgZ);
    y = 0x07;
    setLoadFlag(y);
    myMapper->writeCPU(0x0001, y);
    y = 0x00;
    setLoadFlag(y);
    myMapper->writeCPU(0x0000, y);
    a = 0x00;
    setLoadFlag(a);
    do {
        do {
            myMapper->writeCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y, a);
            opDEY(1);
        } while (!flgZ);
        opDEC(0x0001, 1);
    } while (!flgN);
    pushAddress(0x0007C2);
    SUB_0007E7();
    if (poppedEntry.value != 0x0007C2) return;
    a = 0x7F;
    setLoadFlag(a);
    myMapper->writeCPU(0x0511, a);
    a = 0x18;
    setLoadFlag(a);
    myMapper->writeCPU(0x0051, a);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x004E, a);
    myMapper->writeCPU(0x0055, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x004F, a);
    a = myMapper->readCPU(0x0010);
    setLoadFlag(a);
    opEOR(0x80);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0010, a);
}

void game::repeat() {
    pushAddress(0x0007E1);
    SUB_0034ED();
    if (poppedEntry.value != 0x0007E1) return;
}

void game::SUB_0007E7() {
    a = 0x10;
    setLoadFlag(a);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0010, a);
    a = 0x06;
    setLoadFlag(a);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x0011, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x0013, a);
    pushAddress(0x000801);
    SUB_000BAE();
    if (poppedEntry.value != 0x000801) return;
    SUB_000BB7();
    return;
}

void game::SUB_000807() {
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC4A7 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0xC4A8 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    SUB_003228();
    return;
}

void game::SUB_000815() {
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC03C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    a = myMapper->readCPU(0xC03D + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    SUB_0032D7();
    return;
}

void game::SUB_000823() {
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC03C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0xC03D + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    SUB_000D76();
    return;
}

void game::SUB_000831() {
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC03C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0004, a);
    a = myMapper->readCPU(0xC03D + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0xC044 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0006, a);
    a = myMapper->readCPU(0xC045 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0007, a);
    popAddress();
}

void game::SUB_000847() {
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC03C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    a = myMapper->readCPU(0xC03D + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    popAddress();
}

void game::SUB_000853() {
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC03C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0xC03D + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0009, a);
    popAddress();
}

void game::nmi() {
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0010);
    setLoadFlag(a);
    opAND(0x7F);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0010, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x2003, a);
    a = 0x02;
    setLoadFlag(a);
    myMapper->writeCPU(0x4014, a);
    a = 0x31;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x03;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    pushAddress(0x00087B);
    SUB_003228();
    if (poppedEntry.value != 0x00087B) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0330, a);
    myMapper->writeCPU(0x0331, a);
    pushAddress(0x000886);
    SUB_00350E();
    if (poppedEntry.value != 0x000886) return;
    a = myMapper->readCPU(0x0011);
    setLoadFlag(a);
    opEOR(0x18);
    myMapper->writeCPU(0x2001, a);
    pushAddress(0x000890);
    SUB_003A48();
    if (poppedEntry.value != 0x000890) return;
    a = myMapper->readCPU(0x004E);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x004F);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0008D4;
        }
        a = myMapper->readCPU(0x009A);
        setLoadFlag(a);
        if (flgZ) {
            pushAddress(0x00089F);
            SUB_000E7C();
            if (poppedEntry.value != 0x00089F) return;
            goto L_0008D7;
        }
        a = myMapper->readCPU(0x044F);
        setLoadFlag(a);
        if (a != 0x08) {
            goto L_0008D4;
        }
        pushAddress(0x0008AC);
        SUB_000CF4();
        if (poppedEntry.value != 0x0008AC) return;
        a = myMapper->readCPU(0x0043);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0008D7;
        }
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x044F, a);
        myMapper->writeCPU(0x004F, a);
        a = 0x79;
        setLoadFlag(a);
        myMapper->writeCPU(0x0043, a);
        goto L_0008D7;
    }
    a = myMapper->readCPU(0x0055);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x0008C5);
        SUB_000A30();
        if (poppedEntry.value != 0x0008C5) return;
    }
    else {
        pushAddress(0x0008CB);
        SUB_0008F3();
        if (poppedEntry.value != 0x0008CB) return;
        pushAddress(0x0008CE);
        SUB_0034AC();
        if (poppedEntry.value != 0x0008CE) return;
        goto L_0008D7;
    L_0008D4:
        pushAddress(0x0008D4);
        SUB_000AC9();
        if (poppedEntry.value != 0x0008D4) return;
    }
L_0008D7:
    a = myMapper->readCPU(0x0505);
    setLoadFlag(a);
    if (a != 0x01) {
        goto L_0008E8;
    }
    a = myMapper->readCPU(0x0051);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    pushAddress(0x0008E2);
    SUB_00323C();
    if (poppedEntry.value != 0x0008E2) return;
    opDEC(0x0505, 1);
L_0008E8:
    a = myMapper->readCPU(0x0010);
    setLoadFlag(a);
    opEOR(0x80);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0010, a);
    opPLA();
    return;
}

void game::SUB_0008F3() {
    a = myMapper->readCPU(0x0102);
    setLoadFlag(a);
    if (flgZ) {
        myMapper->writeCPU(0x4015, a);
        myMapper->writeCPU(0x0100, a);
    }
    a = myMapper->readCPU(0x0518);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x80;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FD, a);
        a = 0x04;
        setLoadFlag(a);
        myMapper->writeCPU(0x0518, a);
        a = 0x0F;
        setLoadFlag(a);
        myMapper->writeCPU(0x4015, a);
        myMapper->writeCPU(0x0100, a);
    }
    a = myMapper->readCPU(0x0510);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x000919);
        SUB_00119A();
        if (poppedEntry.value != 0x000919) return;
        a = 0x08;
        setLoadFlag(a);
        pushAddress(0x00091E);
        SUB_000807();
        if (poppedEntry.value != 0x00091E) return;
        a = myMapper->readCPU(0x0511);
        setLoadFlag(a);
        myMapper->writeCPU(0x0200, a);
        a = 0xA2;
        setLoadFlag(a);
        myMapper->writeCPU(0x0201, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0202, a);
        myMapper->writeCPU(0x0058, a);
        a = 0x38;
        setLoadFlag(a);
        myMapper->writeCPU(0x0203, a);
        myMapper->writeCPU(0x0510, a);
        a = 0x20;
        setLoadFlag(a);
        myMapper->writeCPU(0x0044, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0015);
    setLoadFlag(a);
    opAND(0x20);
    if (flgZ) {
        a = myMapper->readCPU(0x0015);
        setLoadFlag(a);
        opAND(0x10);
        if (!flgZ) {
            SUB_00098A();
            return;
        }
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0512, a);
        a = myMapper->readCPU(0x0044);
        setLoadFlag(a);
        if (flgZ) {
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x0058, a);
            SUB_0009B1();
            return;
        }
        popAddress();
        return;
    }
    a = 0x40;
    setLoadFlag(a);
    myMapper->writeCPU(0x0044, a);
    a = myMapper->readCPU(0x0512);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x40;
        setLoadFlag(a);
        myMapper->writeCPU(0x0035, a);
        a = myMapper->readCPU(0x0200);
        setLoadFlag(a);
        flgC = false;
        opADC(0x10);
        if (a == 0xBF) {
            a = 0x7F;
            setLoadFlag(a);
        }
        myMapper->writeCPU(0x0200, a);
        myMapper->writeCPU(0x0511, a);
        opINC(0x0512, 1);
        a = 0x0A;
        setLoadFlag(a);
        myMapper->writeCPU(0x0513, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0035);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_000989;
    }
L_000989:
    popAddress();
}

void game::SUB_00098A() {
    myMapper->writeCPU(0x0514, a);
    x = 0x0A;
    setLoadFlag(x);
    a = 0x00;
    setLoadFlag(a);
    do {
        myMapper->writeCPU((0x0024 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0511);
    setLoadFlag(a);
    opLSR_A(4);
    flgC = true;
    opSBC(0x07);
    myMapper->writeCPU(0x0050, a);
    if (a < 0x02) {
        goto L_0009AD;
    }
    a = 0x1C;
    setLoadFlag(a);
    myMapper->writeCPU(0x0051, a);
    SUB_0009B1();
    return;
L_0009AD:
    a = 0x18;
    setLoadFlag(a);
    myMapper->writeCPU(0x0051, a);
    SUB_0009B1();
    return;
}

void game::SUB_0009B1() {
    a = myMapper->readCPU(0x0050);
    setLoadFlag(a);
    opAND(0x01);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0x0507 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0021, a);
    a = myMapper->readCPU(0x0508 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0022, a);
    a = 0x0F;
    setLoadFlag(a);
    myMapper->writeCPU(0x0018, a);
    a = 0x13;
    setLoadFlag(a);
    myMapper->writeCPU(0x0019, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x004E, a);
    myMapper->writeCPU(0x0406, a);
    myMapper->writeCPU(0x0407, a);
    myMapper->writeCPU(0x004F, a);
    myMapper->writeCPU(0x0510, a);
    myMapper->writeCPU(0x050B, a);
    myMapper->writeCPU(0x0512, a);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0053, a);
    myMapper->writeCPU(0x0400, a);
    myMapper->writeCPU(0x0401, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0054, a);
    myMapper->writeCPU(0x0402, a);
    myMapper->writeCPU(0x0403, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0052, a);
    myMapper->writeCPU(0x0408, a);
    myMapper->writeCPU(0x0409, a);
    myMapper->writeCPU(0x00FC, a);
    a = 0x03;
    setLoadFlag(a);
    x = myMapper->readCPU(0x0058);
    setLoadFlag(x);
    if (!flgZ) {
        a = 0x01;
        setLoadFlag(a);
    }
    myMapper->writeCPU(0x0055, a);
    myMapper->writeCPU(0x0404, a);
    myMapper->writeCPU(0x0405, a);
    myMapper->writeCPU(0x040B, a);
    a = myMapper->readCPU(0x0058);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_000A26;
    }
    a = 0x97;
    setLoadFlag(a);
    myMapper->writeCPU(0x0043, a);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FD, a);
    a = 0x0F;
    setLoadFlag(a);
    myMapper->writeCPU(0x4015, a);
    myMapper->writeCPU(0x0100, a);
    popAddress();
    return;
L_000A26:
    opDEC(0x0518, 1);
    a = 0x75;
    setLoadFlag(a);
    myMapper->writeCPU(0x0043, a);
    SUB_000BAE();
    return;
}

void game::SUB_000A30() {
    pushAddress(0x000A30);
    SUB_0034AC();
    if (poppedEntry.value != 0x000A30) return;
    a = myMapper->readCPU(0x0058);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_000A4A;
    }
    a = myMapper->readCPU(0x0043);
    setLoadFlag(a);
    if (a == 0x75) {
        SUB_000A5A();
        return;
    }
    if (a == 0x74) {
        SUB_000A5F();
        return;
    }
    if (a == 0x73) {
        SUB_000A64();
        return;
    }
    if (a == 0x5F) {
        SUB_000A79();
        return;
    }
    popAddress();
    return;
L_000A4A:
    myMapper->writeCPU(0x0055, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0058, a);
    myMapper->writeCPU(0x0510, a);
    SUB_000A53();
    return;
}

void game::SUB_000A53() {
    pushAddress(0x000A53);
    SUB_000BB7();
    if (poppedEntry.value != 0x000A53) return;
    pushAddress(0x000A56);
    SUB_000BAE();
    if (poppedEntry.value != 0x000A56) return;
    popAddress();
}

void game::SUB_000A5A() {
    opDEC(0x0043, 1);
    SUB_000BAE();
    return;
}

void game::SUB_000A5F() {
    opDEC(0x0043, 1);
    SUB_000BCA();
    return;
}

void game::SUB_000A64() {
    opDEC(0x0043, 1);
    a = myMapper->readCPU(0x0050);
    setLoadFlag(a);
    opAND(0x01);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0x0021);
    setLoadFlag(a);
    myMapper->writeCPU(0x0507 + x, a);
    a = myMapper->readCPU(0x0022);
    setLoadFlag(a);
    myMapper->writeCPU(0x0508 + x, a);
    SUB_000BF5();
    return;
}

void game::SUB_000A79() {
    x = myMapper->readCPU(0x0052);
    setLoadFlag(x);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0406 + x, a);
    myMapper->writeCPU(0x004E, a);
    a = myMapper->readCPU(0x0051);
    setLoadFlag(a);
    if (a != 0x1C) {
        goto L_000A94;
    }
    a = myMapper->readCPU(0x0052);
    setLoadFlag(a);
    opEOR(0x01);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0x0406 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x004E, a);
    if (flgZ) {
        goto L_000A99;
    }
L_000A94:
    myMapper->writeCPU(0x0055, a);
    SUB_000A53();
    return;
L_000A99:
    a = 0x85;
    setLoadFlag(a);
    myMapper->writeCPU(0x0043, a);
    myMapper->writeCPU(0x040B, a);
    y = 0x00;
    setLoadFlag(y);
    myMapper->writeCPU(0x004F, y);
    myMapper->writeCPU(0x0052, x);
    SUB_000AA9();
    return;
}

void game::SUB_000AA9() {
    y = 0x00;
    setLoadFlag(y);
    do {
        a = myMapper->readCPU(0x0400 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0053 + y, a);
        opINX(2);
        opINY(1);
    } while (y != 0x03);
    popAddress();
}

void game::SUB_000AB9() {
    y = 0x00;
    setLoadFlag(y);
    do {
        a = myMapper->readCPU(0x0053 + y);
        setLoadFlag(a);
        myMapper->writeCPU(0x0400 + x, a);
        opINX(2);
        opINY(1);
    } while (y != 0x03);
    popAddress();
}

void game::SUB_000AC9() {
    pushAddress(0x000AC9);
    SUB_0034AC();
    if (poppedEntry.value != 0x000AC9) return;
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a != 0x01) {
        a = myMapper->readCPU(0x0043);
        setLoadFlag(a);
        if (a == 0x84) {
            goto L_000B02;
        }
    }
    a = myMapper->readCPU(0x0043);
    setLoadFlag(a);
    if (a < 0x72) {
        if (a == 0x6D) {
            goto L_000AE7;
        }
        if (a == 0x62) {
            goto L_000AFA;
        }
        popAddress();
        return;
    L_000AE7:
        a = myMapper->readCPU(0x040B);
        setLoadFlag(a);
        if (!flgZ) {
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x040B, a);
            opDEC(0x0055, 1);
            pushAddress(0x000AF3);
            SUB_000BBD();
            if (poppedEntry.value != 0x000AF3) return;
        }
        pushAddress(0x000AF6);
        SUB_000C34();
        if (poppedEntry.value != 0x000AF6) return;
        popAddress();
        return;
    L_000AFA:
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x004F, a);
        pushAddress(0x000AFE);
        SUB_000C47();
        if (poppedEntry.value != 0x000AFE) return;
        popAddress();
        return;
    L_000B02:
        x = myMapper->readCPU(0x0052);
        setLoadFlag(x);
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a != myMapper->readCPU(0x0400 + x)) {
            if (a == 0x01) {
                goto L_000B15;
            }
            pushAddress(0x000B0F);
            SUB_000C24();
            if (poppedEntry.value != 0x000B0F) return;
            pushAddress(0x000B12);
            SUB_000C04();
            if (poppedEntry.value != 0x000B12) return;
        }
    L_000B15:
        opDEC(0x0043, 1);
        popAddress();
        return;
    }
    goto L_000B1B;
L_000B1B:
    if (a != 0x7A) {
        if (a == 0x75) {
            goto L_000B39;
        }
        if (a == 0x74) {
            goto L_000B36;
        }
        if (a == 0x73) {
            goto L_000B58;
        }
        if (a == 0x72) {
            goto L_000B47;
        }
        popAddress();
        return;
    }
    pushAddress(0x000B30);
    SUB_000A53();
    if (poppedEntry.value != 0x000B30) return;
    pushAddress(0x000B33);
    SUB_000BCA();
    if (poppedEntry.value != 0x000B33) return;
L_000B36:
    opDEC(0x0043, 1);
    popAddress();
    return;
L_000B39:
    pushAddress(0x000B39);
    SUB_000BB7();
    if (poppedEntry.value != 0x000B39) return;
    opDEC(0x0043, 1);
    a = myMapper->readCPU(0x0058);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x08;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FD, a);
    }
    popAddress();
    return;
L_000B47:
    opDEC(0x0043, 1);
    x = myMapper->readCPU(0x0053);
    setLoadFlag(x);
    opDEX(1);
    a = myMapper->readCPU(0xC608 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    SUB_002BA6();
    return;
L_000B58:
    pushAddress(0x000B58);
    SUB_00119A();
    if (poppedEntry.value != 0x000B58) return;
    x = myMapper->readCPU(0x0053);
    setLoadFlag(x);
    opDEX(1);
    a = x;
    setLoadFlag(a);
    opASL_A(1);
    pushAddress(0x000B60);
    SUB_000807();
    if (poppedEntry.value != 0x000B60) return;
    a = 0x0A;
    setLoadFlag(a);
    pushAddress(0x000B65);
    SUB_000807();
    if (poppedEntry.value != 0x000B65) return;
    a = myMapper->readCPU(0x0051);
    setLoadFlag(a);
    if (a != 0x1C) {
        a = 0x76;
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        a = 0x20;
        setLoadFlag(a);
        myMapper->writeCPU(0x0001, a);
        a = 0x04;
        setLoadFlag(a);
        pushAddress(0x000B78);
        SUB_000815();
        if (poppedEntry.value != 0x000B78) return;
    }
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0505, a);
    pushAddress(0x000B80);
    SUB_001032();
    if (poppedEntry.value != 0x000B80) return;
    pushAddress(0x000B83);
    SUB_000BBD();
    if (poppedEntry.value != 0x000B83) return;
    a = 0xBC;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    y = myMapper->readCPU(0x0054);
    setLoadFlag(y);
    opINY(1);
    pushAddress(0x000B8D);
    SUB_0034C2();
    if (poppedEntry.value != 0x000B8D) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x002C, a);
    a = 0x80;
    setLoadFlag(a);
    opDEY(1);
    if (y >= 0x04) {
        goto L_000B9E;
    }
    a = myMapper->readCPU(0xC207 + y);
    setLoadFlag(a);
L_000B9E:
    myMapper->writeCPU(0x002E, a);
    a = 0x0D;
    setLoadFlag(a);
    myMapper->writeCPU(0x0045, a);
    a = 0x02;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    pushAddress(0x000BA8);
    SUB_00323C();
    if (poppedEntry.value != 0x000BA8) return;
    opDEC(0x0043, 1);
    popAddress();
}

void game::SUB_000BAE() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0004, a);
    a = 0xFF;
    setLoadFlag(a);
    SUB_003092();
    return;
}

void game::SUB_000BB7() {
    pushAddress(0x000BB7);
    SUB_00119A();
    if (poppedEntry.value != 0x000BB7) return;
    SUB_0031B4();
    return;
}

void game::SUB_000BBD() {
    a = 0xB5;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    y = myMapper->readCPU(0x0055);
    setLoadFlag(y);
    SUB_0034C2();
    return;
}

void game::SUB_000BCA() {
    a = myMapper->readCPU(0x0058);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x0051);
        setLoadFlag(a);
        if (a == 0x1C) {
            x = myMapper->readCPU(0x0052);
            setLoadFlag(x);
            a = myMapper->readCPU(0x0053);
            setLoadFlag(a);
            if (a == myMapper->readCPU(0x0400 + x)) {
                y = 0x00;
                setLoadFlag(y);
                while (true) {
                    a = myMapper->readCPU(0xC6AA + y);
                    setLoadFlag(a);
                    myMapper->writeCPU(0x0331 + y, a);
                    if (flgZ) {
                        goto L_000BEB;
                    }
                    opINY(1);
                }
            L_000BEB:
                a = myMapper->readCPU(0x0052);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_000BF4;
                }
                a = 0x67;
                setLoadFlag(a);
                myMapper->writeCPU(0x0345, a);
            }
        }
    }
L_000BF4:
    popAddress();
}

void game::SUB_000BF5() {
    y = 0x00;
    setLoadFlag(y);
    while (true) {
        a = myMapper->readCPU(0xC6C2 + y);
        setLoadFlag(a);
        myMapper->writeCPU(0x0331 + y, a);
        if (flgZ) {
            goto L_000C03;
        }
        opINY(1);
    }
L_000C03:
    popAddress();
}

void game::SUB_000C04() {
    a = myMapper->readCPU(0x0058);
    setLoadFlag(a);
    if (flgZ) {
        x = myMapper->readCPU(0x0052);
        setLoadFlag(x);
        a = myMapper->readCPU(0x0408 + x);
        setLoadFlag(a);
        if (flgZ) {
            a = x;
            setLoadFlag(a);
            y = a;
            setLoadFlag(y);
            flgC = false;
            opASL_A(2);
            x = a;
            setLoadFlag(x);
            a = myMapper->readCPU((0x0025 + x) & 0x00ff);
            setLoadFlag(a);
            if (a < 0x02) {
                goto L_000C23;
            }
            myMapper->writeCPU(0x0408 + y, a);
            opINC(0x0055, 1);
            pushAddress(0x000C20);
            SUB_000BBD();
            if (poppedEntry.value != 0x000C20) return;
        }
    }
L_000C23:
    popAddress();
}

void game::SUB_000C24() {
    a = myMapper->readCPU(0x002E);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0052);
    setLoadFlag(a);
    opORA(0x08);
    myMapper->writeCPU(0x0001, a);
    pushAddress(0x000C2E);
    SUB_003342();
    if (poppedEntry.value != 0x000C2E) return;
    SUB_001032();
    return;
}

void game::SUB_000C34() {
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0505, a);
    pushAddress(0x000C39);
    SUB_001032();
    if (poppedEntry.value != 0x000C39) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x050B, a);
    pushAddress(0x000C41);
    SUB_000CC1();
    if (poppedEntry.value != 0x000C41) return;
    SUB_0017F2();
    return;
}

void game::SUB_000C47() {
    a = 0x00;
    setLoadFlag(a);
    x = a;
    setLoadFlag(x);
    do {
        myMapper->writeCPU((0x0059 + x) & 0x00ff, a);
        myMapper->writeCPU(0x040D + x, a);
        opINX(1);
    } while (x != 0x89);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0059, a);
    myMapper->writeCPU(0x0096, a);
    myMapper->writeCPU(0x043E, a);
    myMapper->writeCPU(0x0451, a);
    myMapper->writeCPU(0x0452, a);
    myMapper->writeCPU(0x009F, a);
    myMapper->writeCPU(0x0503, a);
    a = 0x04;
    setLoadFlag(a);
    myMapper->writeCPU(0x0097, a);
    a = 0x58;
    setLoadFlag(a);
    myMapper->writeCPU(0x043D, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x00A2, a);
    a = 0x80;
    setLoadFlag(a);
    myMapper->writeCPU(0x0018, a);
    a = 0x0A;
    setLoadFlag(a);
    myMapper->writeCPU(0x0034, a);
    x = myMapper->readCPU(0x0052);
    setLoadFlag(x);
    pushAddress(0x000C7F);
    SUB_000AB9();
    if (poppedEntry.value != 0x000C7F) return;
    a = 0xBB;
    setLoadFlag(a);
    myMapper->writeCPU(0x0039, a);
    a = 0x27;
    setLoadFlag(a);
    myMapper->writeCPU(0x0044, a);
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a == 0x01) {
        goto L_000C99;
    }
    if (a == 0x03) {
        goto L_000CA6;
    }
    a = 0x10;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FC, a);
    popAddress();
    return;
L_000C99:
    a = 0x38;
    setLoadFlag(a);
    myMapper->writeCPU(0x0036, a);
    a = 0x40;
    setLoadFlag(a);
    myMapper->writeCPU(0x0043, a);
    a = 0x02;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FC, a);
    popAddress();
    return;
L_000CA6:
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0036, a);
    a = 0x50;
    setLoadFlag(a);
    myMapper->writeCPU(0x043F, a);
    myMapper->writeCPU(0x0441, a);
    myMapper->writeCPU(0x0443, a);
    a = 0x03;
    setLoadFlag(a);
    myMapper->writeCPU(0x0440, a);
    myMapper->writeCPU(0x0442, a);
    myMapper->writeCPU(0x0444, a);
    popAddress();
}

void game::SUB_000CC1() {
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x01);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC5A6 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0009, a);
    a = myMapper->readCPU(0xC5A7 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    x = 0x00;
    setLoadFlag(x);
    y = 0x00;
    setLoadFlag(y);
    while (true) {
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (a == 0xFE) {
                goto L_000CF3;
            }
            myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
            opINY(1);
            opINX(1);
        } while (x != 0x05);
        myMapper->writeCPU(0x0086, y);
        a = myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        pushAddress(0x000CE8);
        SUB_003096();
        if (poppedEntry.value != 0x000CE8) return;
        y = myMapper->readCPU(0x0086);
        setLoadFlag(y);
        opINY(1);
        x = 0x00;
        setLoadFlag(x);
    }
L_000CF3:
    popAddress();
}

void game::SUB_000CF4() {
    a = myMapper->readCPU(0x0450);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0450, a);
        a = 0x0A;
        setLoadFlag(a);
        myMapper->writeCPU(0x0034, a);
        a = 0x10;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FD, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0043);
    setLoadFlag(a);
    if (a >= 0x58) {
        pushAddress(0x000D0D);
        SUB_0034AC();
        if (poppedEntry.value != 0x000D0D) return;
    }
    else {
        pushAddress(0x000D13);
        SUB_000C24();
        if (poppedEntry.value != 0x000D13) return;
        pushAddress(0x000D16);
        SUB_000C04();
        if (poppedEntry.value != 0x000D16) return;
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0043, a);
        myMapper->writeCPU(0x009A, a);
        SUB_000A53();
        return;
    }
    a = myMapper->readCPU(0x0043);
    setLoadFlag(a);
    if (a == 0x9F) {
        goto L_000D45;
    }
    if (a == 0x9E) {
        goto L_000D4A;
    }
    if (a == 0x9D) {
        goto L_000D4F;
    }
    if (a == 0x9C) {
        goto L_000D58;
    }
    if (a == 0x9B) {
        goto L_000D61;
    }
    if (a >= 0x90) {
        goto L_000D66;
    }
    if (a >= 0x86) {
        goto L_000D69;
    }
    if (a >= 0x70) {
        goto L_000D6C;
    }
    popAddress();
    return;
L_000D45:
    opDEC(0x0043, 1);
    goto L_000D6F;
L_000D4A:
    opDEC(0x0043, 1);
    SUB_000D7F();
    return;
L_000D4F:
    y = 0x1C;
    setLoadFlag(y);
    opDEC(0x0043, 1);
    a = 0x06;
    setLoadFlag(a);
    SUB_000823();
    return;
L_000D58:
    y = 0x1C;
    setLoadFlag(y);
    opDEC(0x0043, 1);
    a = 0x08;
    setLoadFlag(a);
    SUB_000823();
    return;
L_000D61:
    opDEC(0x0043, 1);
    SUB_000D89();
    return;
L_000D66:
    SUB_000D9D();
    return;
L_000D69:
    SUB_000DB1();
    return;
L_000D6C:
    SUB_000E24();
    return;
L_000D6F:
    y = 0x0C;
    setLoadFlag(y);
    a = 0x0A;
    setLoadFlag(a);
    SUB_000823();
    return;
}

void game::SUB_000D76() {
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        myMapper->writeCPU(0x0331 + y, a);
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_000D7F() {
    pushAddress(0x000D7F);
    SUB_000BAE();
    if (poppedEntry.value != 0x000D7F) return;
    y = 0x16;
    setLoadFlag(y);
    a = 0x0C;
    setLoadFlag(a);
    SUB_000823();
    return;
}

void game::SUB_000D89() {
    y = 0x0C;
    setLoadFlag(y);
    a = 0x0E;
    setLoadFlag(a);
    pushAddress(0x000D8D);
    SUB_000823();
    if (poppedEntry.value != 0x000D8D) return;
    a = 0x03;
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    a = 0x18;
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = 0x50;
    setLoadFlag(a);
    SUB_00308C();
    return;
}

void game::SUB_000D9D() {
    a = 0x8D;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x0043);
    setLoadFlag(a);
    opAND(0x01);
    if (flgZ) {
        goto L_000DAE;
    }
    SUB_002B89();
    return;
L_000DAE:
    SUB_002B92();
    return;
}

void game::SUB_000DB1() {
    if (a != 0x8F) {
        goto L_000DD7;
    }
    opDEC(0x0043, 1);
    y = 0x10;
    setLoadFlag(y);
    a = 0x10;
    setLoadFlag(a);
    pushAddress(0x000DBB);
    SUB_000823();
    if (poppedEntry.value != 0x000DBB) return;
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FE, a);
    a = 0x68;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x3E;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    while (true) {
        a = 0x40;
        setLoadFlag(a);
        myMapper->writeCPU(0x0002, a);
        a = 0x46;
        setLoadFlag(a);
        myMapper->writeCPU(0x0003, a);
        a = 0x50;
        setLoadFlag(a);
        SUB_003080();
        return;
    L_000DD7:
        a = myMapper->readCPU(0x0250);
        setLoadFlag(a);
        if (a == 0xA0) {
            goto L_000DEF;
        }
        if (a == 0xFF) {
            goto L_000DF3;
        }
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x0001, a);
        a = myMapper->readCPU(0x0253);
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
    }
L_000DEF:
    a = 0x80;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FE, a);
L_000DF3:
    a = 0x18;
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = 0x50;
    setLoadFlag(a);
    pushAddress(0x000DF9);
    SUB_00308C();
    if (poppedEntry.value != 0x000DF9) return;
    a = 0xEB;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x23;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = 0x12;
    setLoadFlag(a);
    pushAddress(0x000E06);
    SUB_000815();
    if (poppedEntry.value != 0x000E06) return;
    a = 0x01;
    setLoadFlag(a);
    SUB_000E0E();
    return;
}

void game::SUB_000E0E() {
    pushStatus();
    a = 0x8D;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x22;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    popStatus();
    if (!flgZ) {
        goto L_000E1F;
    }
    a = 0x16;
    setLoadFlag(a);
    SUB_000815();
    return;
L_000E1F:
    a = 0x14;
    setLoadFlag(a);
    SUB_000815();
    return;
}

void game::SUB_000E24() {
    if (a == 0x85) {
        goto L_000E2F;
    }
    a = myMapper->readCPU(0x0043);
    setLoadFlag(a);
    opAND(0x01);
    SUB_000E0E();
    return;
L_000E2F:
    a = 0x04;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FD, a);
    y = 0x04;
    setLoadFlag(y);
    a = 0x18;
    setLoadFlag(a);
    pushAddress(0x000E37);
    SUB_000823();
    if (poppedEntry.value != 0x000E37) return;
    a = 0x78;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = 0xC8;
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    a = 0x22;
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = 0xB0;
    setLoadFlag(a);
    pushAddress(0x000E4C);
    SUB_003080();
    if (poppedEntry.value != 0x000E4C) return;
    opDEC(0x0043, 1);
    a = 0xA0;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x30;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = 0x04;
    setLoadFlag(a);
    pushAddress(0x000E5B);
    SUB_002AD4();
    if (poppedEntry.value != 0x000E5B) return;
    a = 0x00;
    setLoadFlag(a);
    pushAddress(0x000E60);
    SUB_003086();
    if (poppedEntry.value != 0x000E60) return;
    a = 0x28;
    setLoadFlag(a);
    myMapper->writeCPU(0x02E8, a);
    myMapper->writeCPU(0x02EC, a);
    a = 0x30;
    setLoadFlag(a);
    myMapper->writeCPU(0x02F0, a);
    myMapper->writeCPU(0x02F8, a);
    a = 0x38;
    setLoadFlag(a);
    myMapper->writeCPU(0x02F4, a);
    myMapper->writeCPU(0x02FC, a);
    popAddress();
}

void game::SUB_000E7C() {
    a = myMapper->readCPU(0x0058);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x0102);
        setLoadFlag(a);
        if (flgZ) {
            myMapper->writeCPU(0x4015, a);
            myMapper->writeCPU(0x0100, a);
        }
        a = myMapper->readCPU(0x0015);
        setLoadFlag(a);
        opAND(0x20);
        if (!flgZ) {
            goto L_000F2B;
        }
    }
    a = myMapper->readCPU(0x0516);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x0517);
        setLoadFlag(a);
        if (!flgZ) {
            opDEC(0x0517, 1);
            popAddress();
            return;
        }
        pushAddress(0x000EA2);
        SUB_000C04();
        if (poppedEntry.value != 0x000EA2) return;
        pushAddress(0x000EA5);
        SUB_000FA8();
        if (poppedEntry.value != 0x000EA5) return;
        a = myMapper->readCPU(0x009A);
        setLoadFlag(a);
        if (a != 0x01) {
            goto L_000EB1;
        }
    }
    goto L_000F1C;
L_000EB1:
    a = myMapper->readCPU(0x00BF);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x0096);
        setLoadFlag(a);
        if (a == 0xFF) {
            goto L_000F19;
        }
        if (a != 0x08) {
            if (a == 0x04) {
                goto L_000ED6;
            }
            a = myMapper->readCPU(0x0058);
            setLoadFlag(a);
            if (!flgZ) {
                pushAddress(0x000ECD);
                SUB_002BDA();
                if (poppedEntry.value != 0x000ECD) return;
            }
            else {
                pushAddress(0x000ED3);
                SUB_001175();
                if (poppedEntry.value != 0x000ED3) return;
            }
        }
    L_000ED6:
        pushAddress(0x000ED6);
        SUB_002B06();
        if (poppedEntry.value != 0x000ED6) return;
        pushAddress(0x000ED9);
        SUB_002BB6();
        if (poppedEntry.value != 0x000ED9) return;
        pushAddress(0x000EDC);
        SUB_001041();
        if (poppedEntry.value != 0x000EDC) return;
        pushAddress(0x000EDF);
        SUB_0011A4();
        if (poppedEntry.value != 0x000EDF) return;
        pushAddress(0x000EE2);
        SUB_002A5F();
        if (poppedEntry.value != 0x000EE2) return;
        pushAddress(0x000EE5);
        SUB_0021E5();
        if (poppedEntry.value != 0x000EE5) return;
        pushAddress(0x000EE8);
        SUB_002E79();
        if (poppedEntry.value != 0x000EE8) return;
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a != 0x03) {
            if (a == 0x04) {
                goto L_000F0D;
            }
            pushAddress(0x000EF5);
            SUB_001A16();
            if (poppedEntry.value != 0x000EF5) return;
            pushAddress(0x000EF8);
            SUB_00219A();
            if (poppedEntry.value != 0x000EF8) return;
            pushAddress(0x000EFB);
            SUB_002C29();
            if (poppedEntry.value != 0x000EFB) return;
            goto L_000F1C;
        }
        pushAddress(0x000F01);
        SUB_002834();
        if (poppedEntry.value != 0x000F01) return;
        pushAddress(0x000F04);
        SUB_002981();
        if (poppedEntry.value != 0x000F04) return;
        pushAddress(0x000F07);
        SUB_002C29();
        if (poppedEntry.value != 0x000F07) return;
        goto L_000F1C;
    L_000F0D:
        pushAddress(0x000F0D);
        SUB_002C29();
        if (poppedEntry.value != 0x000F0D) return;
        goto L_000F1C;
    }
    pushAddress(0x000F13);
    SUB_002E0C();
    if (poppedEntry.value != 0x000F13) return;
    goto L_000F1C;
L_000F19:
    pushAddress(0x000F19);
    SUB_0010C0();
    if (poppedEntry.value != 0x000F19) return;
L_000F1C:
    pushAddress(0x000F1C);
    SUB_000F42();
    if (poppedEntry.value != 0x000F1C) return;
    a = myMapper->readCPU(0x0516);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_000F2A;
    }
    pushAddress(0x000F24);
    SUB_00104C();
    if (poppedEntry.value != 0x000F24) return;
    pushAddress(0x000F27);
    SUB_0034AC();
    if (poppedEntry.value != 0x000F27) return;
L_000F2A:
    popAddress();
    return;
L_000F2B:
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x004E, a);
    myMapper->writeCPU(0x0512, a);
    myMapper->writeCPU(0x0055, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0044, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0058, a);
    myMapper->writeCPU(0x0510, a);
    SUB_000A53();
    return;
}

void game::SUB_000F42() {
    a = myMapper->readCPU(0x0015);
    setLoadFlag(a);
    opAND(0x10);
    if (!flgZ) {
        a = myMapper->readCPU(0x0058);
        setLoadFlag(a);
        if (!flgZ) {
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x0058, a);
            a = myMapper->readCPU(0x0015);
            setLoadFlag(a);
            SUB_00098A();
            return;
        }
        a = myMapper->readCPU(0x0015);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0x0514)) {
            goto L_000F92;
        }
        myMapper->writeCPU(0x0514, a);
        a = myMapper->readCPU(0x0516);
        setLoadFlag(a);
        if (!flgZ) {
            a = myMapper->readCPU(0x0517);
            setLoadFlag(a);
            if (flgZ) {
                myMapper->writeCPU(0x0516, a);
                a = myMapper->readCPU(0x000F);
                setLoadFlag(a);
                myMapper->writeCPU(0x00FC, a);
                a = myMapper->readCPU(0x0011);
                setLoadFlag(a);
                opAND(0xEF);
                myMapper->writeCPU(0x0011, a);
                goto L_000F87;
            }
            popAddress();
            return;
        }
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0516, a);
        a = myMapper->readCPU(0x00FC);
        setLoadFlag(a);
        myMapper->writeCPU(0x000F, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FC, a);
    L_000F87:
        a = 0x40;
        setLoadFlag(a);
        myMapper->writeCPU(0x0517, a);
        myMapper->writeCPU(0x00FD, a);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0514, a);
L_000F92:
    a = myMapper->readCPU(0x0517);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x0517, 1);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0516);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_000FA1;
    }
    popAddress();
    return;
L_000FA1:
    a = myMapper->readCPU(0x0011);
    setLoadFlag(a);
    opORA(0x10);
    myMapper->writeCPU(0x0011, a);
    popAddress();
}

void game::SUB_000FA8() {
    x = 0x00;
    setLoadFlag(x);
    y = 0x00;
    setLoadFlag(y);
    do {
        a = myMapper->readCPU((0x0041 + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_000FB8;
        }
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(0x02C0 + y, a);
        myMapper->writeCPU(0x02C4 + y, a);
    L_000FB8:
        opINX(1);
        opINY(8);
    } while (x < 0x02);
    popAddress();
}

void game::SUB_000FC6() {
    y = 0x00;
    setLoadFlag(y);
    myMapper->writeCPU(0x000F, y);
    pushAddress(0x000FCA);
    SUB_001008();
    if (poppedEntry.value != 0x000FCA) return;
    do {
        a = myMapper->readCPU(0x02C0 + y);
        setLoadFlag(a);
        if (a != 0xFF) {
            goto L_000FF9;
        }
        a = myMapper->readCPU(0x0005);
        setLoadFlag(a);
        myMapper->writeCPU(0x02C3 + y, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x02C7 + y, a);
        a = myMapper->readCPU(0x0006);
        setLoadFlag(a);
        myMapper->writeCPU(0x02C0 + y, a);
        myMapper->writeCPU(0x02C4 + y, a);
        a = myMapper->readCPU(0xC604 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x02C1 + y, a);
        a = 0xD4;
        setLoadFlag(a);
        myMapper->writeCPU(0x02C5 + y, a);
        x = myMapper->readCPU(0x000F);
        setLoadFlag(x);
        a = 0x03;
        setLoadFlag(a);
        myMapper->writeCPU((0x0041 + x) & 0x00ff, a);
        popAddress();
        return;
    L_000FF9:
        opINY(8);
        opINC(0x000F, 1);
    } while (y < 0x10);
    popAddress();
}

void game::SUB_001008() {
    a = x;
    setLoadFlag(a);
    mStack.push({ false, a });
    a = y;
    setLoadFlag(a);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0058);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_00102A;
    }
    a = myMapper->readCPU(0x0052);
    setLoadFlag(a);
    opORA(0x18);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0xC600 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0005);
    setLoadFlag(a);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0006);
    setLoadFlag(a);
    mStack.push({ false, a });
    pushAddress(0x001021);
    SUB_003342();
    if (poppedEntry.value != 0x001021) return;
    opPLA();
    myMapper->writeCPU(0x0006, a);
    opPLA();
    myMapper->writeCPU(0x0005, a);
L_00102A:
    pushAddress(0x00102A);
    SUB_001032();
    if (poppedEntry.value != 0x00102A) return;
    opPLA();
    y = a;
    setLoadFlag(y);
    opPLA();
    x = a;
    setLoadFlag(x);
    popAddress();
}

void game::SUB_001032() {
    a = myMapper->readCPU(0x0505);
    setLoadFlag(a);
    opORA(0x01);
    myMapper->writeCPU(0x0505, a);
    a = 0xF9;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    SUB_003435();
    return;
}

void game::SUB_001041() {
    a = myMapper->readCPU(0x002E);
    setLoadFlag(a);
    if (a >= 0x10) {
        goto L_00104B;
    }
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FC, a);
L_00104B:
    popAddress();
}

void game::SUB_00104C() {
    a = myMapper->readCPU(0x009A);
    setLoadFlag(a);
    if (flgZ) {
        x = myMapper->readCPU(0x0053);
        setLoadFlag(x);
        if (x != 0x04) {
            a = myMapper->readCPU(0x005A);
            setLoadFlag(a);
            if (flgZ) {
                goto L_0010BF;
            }
            opDEX(1);
            a = myMapper->readCPU(0xC1FA + x);
            setLoadFlag(a);
            if (a == myMapper->readCPU(0x0059)) {
                goto L_001074;
            }
            popAddress();
            return;
        }
        x = 0x00;
        setLoadFlag(x);
        do {
            a = myMapper->readCPU((0x00C1 + x) & 0x00ff);
            setLoadFlag(a);
            if (flgZ) {
                goto L_0010BF;
            }
            opINX(1);
            myMapper->writeCPU(0x044F, x);
        } while (x != 0x08);
        goto L_001086;
    L_001074:
        pushAddress(0x001074);
        SUB_002AE1();
        if (poppedEntry.value != 0x001074) return;
        a = 0x04;
        setLoadFlag(a);
        pushAddress(0x001079);
        SUB_002AD4();
        if (poppedEntry.value != 0x001079) return;
        pushAddress(0x00107C);
        SUB_002ACD();
        if (poppedEntry.value != 0x00107C) return;
        pushAddress(0x00107F);
        SUB_003088();
        if (poppedEntry.value != 0x00107F) return;
        a = 0x02;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FD, a);
    L_001086:
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FC, a);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x009A, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x003A, a);
    }
    a = myMapper->readCPU(0x003A);
    setLoadFlag(a);
    if (flgZ) {
        opINC(0x0053, 1);
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a == 0x02) {
            goto L_0010A5;
        }
        if (a >= 0x05) {
            goto L_0010AA;
        }
        goto L_0010B5;
    L_0010A5:
        opINC(0x0053, 1);
        goto L_0010B5;
    L_0010AA:
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0053, a);
        opINC(0x0054, 1);
        a = 0xA0;
        setLoadFlag(a);
        myMapper->writeCPU(0x0043, a);
        popAddress();
        return;
    L_0010B5:
        a = 0x8D;
        setLoadFlag(a);
        myMapper->writeCPU(0x0043, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x004F, a);
        myMapper->writeCPU(0x009A, a);
    }
L_0010BF:
    popAddress();
}

void game::SUB_0010C0() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FC, a);
    a = 0x10;
    setLoadFlag(a);
    pushAddress(0x0010C6);
    SUB_0019E6();
    if (poppedEntry.value != 0x0010C6) return;
    if (!flgZ) {
        a = myMapper->readCPU(0x0098);
        setLoadFlag(a);
        if (a != 0xFF) {
            a = myMapper->readCPU(0x0098);
            setLoadFlag(a);
            if (flgZ) {
                a = myMapper->readCPU(0x0058);
                setLoadFlag(a);
                if (flgZ) {
                    a = 0x80;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x00FE, a);
                }
                a = 0x40;
                setLoadFlag(a);
                myMapper->writeCPU(0x003A, a);
                opINC(0x0098, 1);
                popAddress();
                return;
            }
            a = myMapper->readCPU(0x003A);
            setLoadFlag(a);
            if (!flgZ) {
                if (a < 0x0E) {
                    goto L_001138;
                }
                a = myMapper->readCPU(0x0058);
                setLoadFlag(a);
                if (flgZ) {
                    a = 0x01;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x00FF, a);
                }
                a = 0x00;
                setLoadFlag(a);
                myMapper->writeCPU(0x003A, a);
            }
            a = myMapper->readCPU(0x0201);
            setLoadFlag(a);
            if (a < 0x6C) {
                a = 0x6C;
                setLoadFlag(a);
            }
            flgC = false;
            opADC(0x04);
            if (a >= 0x7C) {
                opINC(0x0098, 1);
                a = myMapper->readCPU(0x0098);
                setLoadFlag(a);
                if (a != 0x05) {
                    a = 0x6C;
                    setLoadFlag(a);
                }
                else {
                    a = myMapper->readCPU(0x0058);
                    setLoadFlag(a);
                    if (!flgZ) {
                        a = 0x7D;
                        setLoadFlag(a);
                        myMapper->writeCPU(0x003A, a);
                    }
                    a = 0x7C;
                    setLoadFlag(a);
                }
            }
            myMapper->writeCPU(0x0002, a);
            pushAddress(0x001121);
            SUB_002AE1();
            if (poppedEntry.value != 0x001121) return;
            pushAddress(0x001124);
            SUB_002ACD();
            if (poppedEntry.value != 0x001124) return;
            pushAddress(0x001127);
            SUB_003082();
            if (poppedEntry.value != 0x001127) return;
            a = myMapper->readCPU(0x0098);
            setLoadFlag(a);
            if (a != 0x05) {
                goto L_001138;
            }
        }
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(0x0098, a);
        a = myMapper->readCPU(0x003A);
        setLoadFlag(a);
        if (flgZ) {
            goto L_001139;
        }
    }
L_001138:
    popAddress();
    return;
L_001139:
    x = myMapper->readCPU(0x0052);
    setLoadFlag(x);
    pushAddress(0x00113B);
    SUB_000AB9();
    if (poppedEntry.value != 0x00113B) return;
    a = myMapper->readCPU(0x0055);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x004E, a);
        a = 0x87;
        setLoadFlag(a);
        myMapper->writeCPU(0x0043, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0051);
    setLoadFlag(a);
    if (a == 0x1C) {
        a = myMapper->readCPU(0x0052);
        setLoadFlag(a);
        opEOR(0x01);
        x = a;
        setLoadFlag(x);
        myMapper->writeCPU(0x0052, x);
        a = myMapper->readCPU(0x0406 + x);
        setLoadFlag(a);
        if (flgZ) {
            goto L_001166;
        }
        a = x;
        setLoadFlag(a);
        opEOR(0x01);
        x = a;
        setLoadFlag(x);
        myMapper->writeCPU(0x0052, x);
        goto L_001169;
    L_001166:
        pushAddress(0x001166);
        SUB_000AA9();
        if (poppedEntry.value != 0x001166) return;
    }
L_001169:
    a = 0x87;
    setLoadFlag(a);
    myMapper->writeCPU(0x0043, a);
    myMapper->writeCPU(0x040B, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x004F, a);
    popAddress();
}

void game::SUB_001175() {
    a = myMapper->readCPU(0x0052);
    setLoadFlag(a);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU((0x0015 + x) & 0x00ff);
    setLoadFlag(a);
    opAND(0x0F);
    myMapper->writeCPU(0x0056, a);
    if (!flgZ) {
        opLSR_A(2);
        if (flgZ) {
            a = myMapper->readCPU(0x0056);
            setLoadFlag(a);
            myMapper->writeCPU(0x0057, a);
        }
    }
    a = myMapper->readCPU(0x0096);
    setLoadFlag(a);
    if (a == 0x01) {
        a = myMapper->readCPU((0x0015 + x) & 0x00ff);
        setLoadFlag(a);
        opAND(0x80);
        if (flgZ) {
            goto L_001199;
        }
        a = 0x04;
        setLoadFlag(a);
        myMapper->writeCPU(0x0096, a);
    }
L_001199:
    popAddress();
}

void game::SUB_00119A() {
    a = myMapper->readCPU(0x0011);
    setLoadFlag(a);
    opAND(0xE7);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x0011, a);
    popAddress();
}

void game::SUB_0011A4() {
    a = myMapper->readCPU(0x0096);
    setLoadFlag(a);
    if (a == 0x01) {
        goto L_0011BB;
    }
    while (a != 0x02) {
        if (a == 0x04) {
            goto L_0011C6;
        }
        if (a == 0x08) {
            goto L_0011C9;
        }
        if (a == 0x0A) {
            goto L_0011CC;
        }
        popAddress();
        return;
    L_0011BB:
        pushAddress(0x0011BB);
        SUB_0011CF();
        if (poppedEntry.value != 0x0011BB) return;
        a = myMapper->readCPU(0x0096);
        setLoadFlag(a);
    }
    SUB_00137E();
    return;
L_0011C6:
    SUB_001547();
    return;
L_0011C9:
    SUB_001697();
    return;
L_0011CC:
    SUB_0016C6();
    return;
}

void game::SUB_0011CF() {
    a = myMapper->readCPU(0x0056);
    setLoadFlag(a);
    if (a != 0x01) {
        if (a == 0x02) {
            goto L_0011E5;
        }
        if (a != 0x04) {
            if (a == 0x08) {
                goto L_0011E2;
            }
            popAddress();
            return;
        }
    L_0011E2:
        goto L_00128B;
    }
L_0011E5:
    a = 0xDB;
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    a = 0x36;
    setLoadFlag(a);
    pushAddress(0x0011EB);
    SUB_0019E8();
    if (poppedEntry.value != 0x0011EB) return;
    if (flgZ) {
    }
    else {
        pushAddress(0x0011F3);
        SUB_001990();
        if (poppedEntry.value != 0x0011F3) return;
        if (!flgZ) {
            popAddress();
            return;
        }
        a = myMapper->readCPU(0x0056);
        setLoadFlag(a);
        if (a != 0x02) {
            opINC(0x0203, 1);
        }
        else {
            opDEC(0x0203, 1);
        }
        pushAddress(0x001208);
        SUB_0012CB();
        if (poppedEntry.value != 0x001208) return;
        myMapper->writeCPU(0x005A, a);
        a = myMapper->readCPU(0x0200);
        setLoadFlag(a);
        pushAddress(0x001210);
        SUB_002016();
        if (poppedEntry.value != 0x001210) return;
        myMapper->writeCPU(0x0059, a);
        pushAddress(0x001215);
        SUB_0018EB();
        if (poppedEntry.value != 0x001215) return;
        if (!flgZ) {
            x = myMapper->readCPU(0x0053);
            setLoadFlag(x);
            if (x == 0x01) {
                flgC = false;
                opADC(myMapper->readCPU(0x0200));
                myMapper->writeCPU(0x0200, a);
            }
            pushAddress(0x001227);
            SUB_00136A();
            if (poppedEntry.value != 0x001227) return;
            if (a != 0x00) {
                a = 0x08;
                setLoadFlag(a);
                myMapper->writeCPU(0x0096, a);
                popAddress();
                return;
            }
        }
        a = myMapper->readCPU(0x009B);
        setLoadFlag(a);
        if (flgZ) {
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x009B, a);
        }
        else {
            a = 0x08;
            setLoadFlag(a);
            myMapper->writeCPU(0x00FF, a);
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x009B, a);
            a = myMapper->readCPU(0x0097);
            setLoadFlag(a);
            if (!flgZ) {
                if (a == 0x08) {
                    goto L_00126D;
                }
                a = 0x04;
                setLoadFlag(a);
                myMapper->writeCPU(0x0097, a);
                a = myMapper->readCPU(0x0085);
                setLoadFlag(a);
                if (!flgZ) {
                    a = 0x00;
                    setLoadFlag(a);
                }
                else {
                    a = 0x08;
                    setLoadFlag(a);
                }
                myMapper->writeCPU(0x0097, a);
            }
            else {
                a = 0x04;
                setLoadFlag(a);
                myMapper->writeCPU(0x0097, a);
                a = 0x00;
                setLoadFlag(a);
                myMapper->writeCPU(0x0085, a);
                goto L_001275;
            L_00126D:
                a = 0x04;
                setLoadFlag(a);
                myMapper->writeCPU(0x0097, a);
                a = 0x01;
                setLoadFlag(a);
                myMapper->writeCPU(0x0085, a);
            }
        }
    }
L_001275:
    pushAddress(0x001275);
    SUB_002AE1();
    if (poppedEntry.value != 0x001275) return;
    a = myMapper->readCPU(0x0097);
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    pushAddress(0x00127C);
    SUB_002ACD();
    if (poppedEntry.value != 0x00127C) return;
    a = myMapper->readCPU(0x0056);
    setLoadFlag(a);
    if (a != 0x02) {
        SUB_003082();
        return;
    }
    SUB_003088();
    return;
L_00128B:
    pushAddress(0x00128B);
    SUB_002AE1();
    if (poppedEntry.value != 0x00128B) return;
    a = 0x86;
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    a = 0xC1;
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    pushAddress(0x001296);
    SUB_002FEB();
    if (poppedEntry.value != 0x001296) return;
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x01);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC47B + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0004, a);
    a = myMapper->readCPU(0xC47C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0xC483 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0006, a);
    a = myMapper->readCPU(0xC484 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0007, a);
    pushAddress(0x0012B4);
    SUB_0018AD();
    if (poppedEntry.value != 0x0012B4) return;
    if (flgZ) {
        goto L_0012CA;
    }
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x00A1, a);
    a = 0x02;
    setLoadFlag(a);
    myMapper->writeCPU(0x0096, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x005B, a);
    myMapper->writeCPU(0x005C, a);
L_0012CA:
    popAddress();
}

void game::SUB_0012CB() {
    pushAddress(0x0012CB);
    SUB_002AE1();
    if (poppedEntry.value != 0x0012CB) return;
    a = myMapper->readCPU(0x0096);
    setLoadFlag(a);
    if (a != 0x04) {
        if (a == 0x08) {
            goto L_0012DD;
        }
        a = 0x2C;
        setLoadFlag(a);
        goto L_0012DF;
    }
L_0012DD:
    a = 0x4A;
    setLoadFlag(a);
L_0012DF:
    pushAddress(0x0012DF);
    SUB_002FE8();
    if (poppedEntry.value != 0x0012DF) return;
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a != 0x01) {
        flgC = true;
        opSBC(0x01);
        opASL_A(1);
        x = a;
        setLoadFlag(x);
    }
    else {
        a = 0x1A;
        setLoadFlag(a);
        pushAddress(0x0012F2);
        SUB_000831();
        if (poppedEntry.value != 0x0012F2) return;
        pushAddress(0x0012F5);
        SUB_00191A();
        if (poppedEntry.value != 0x0012F5) return;
        myMapper->writeCPU(0x000C, a);
        goto L_001323;
    }
    a = myMapper->readCPU(0xC46B + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0004, a);
    a = myMapper->readCPU(0xC46C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0xC473 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0006, a);
    a = myMapper->readCPU(0xC474 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0007, a);
    pushAddress(0x001311);
    SUB_0018AD();
    if (poppedEntry.value != 0x001311) return;
    myMapper->writeCPU(0x000C, a);
    if (flgZ) {
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a != 0x03) {
            goto L_001323;
        }
        pushAddress(0x00131E);
        SUB_001326();
        if (poppedEntry.value != 0x00131E) return;
        myMapper->writeCPU(0x000C, a);
    }
L_001323:
    a = myMapper->readCPU(0x000C);
    setLoadFlag(a);
    popAddress();
}

void game::SUB_001326() {
    a = 0x2A;
    setLoadFlag(a);
    pushAddress(0x001328);
    SUB_000847();
    if (poppedEntry.value != 0x001328) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00D2, a);
    while (true) {
        a = myMapper->readCPU(0x00D2);
        setLoadFlag(a);
        if (a == 0x06) {
            goto L_001365;
        }
        x = a;
        setLoadFlag(x);
        y = myMapper->readCPU(0xC2CC + x);
        setLoadFlag(y);
        a = myMapper->readCPU(0x0200 + y);
        setLoadFlag(a);
        if (a == 0xFF) {
            goto L_00134E;
        }
        myMapper->writeCPU(0x0001, a);
        a = myMapper->readCPU(0x0203 + y);
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        pushAddress(0x001347);
        SUB_002FEF();
        if (poppedEntry.value != 0x001347) return;
        if (a == 0x01) {
            goto L_001353;
        }
    L_00134E:
        opINC(0x00D2, 1);
    }
L_001353:
    a = myMapper->readCPU(0x00D2);
    setLoadFlag(a);
    if (a >= 0x03) {
        goto L_00135E;
    }
    a = 0x01;
    setLoadFlag(a);
    goto L_001360;
L_00135E:
    a = 0x02;
    setLoadFlag(a);
L_001360:
    myMapper->writeCPU(0x00DA, a);
    a = 0x01;
    setLoadFlag(a);
    popAddress();
    return;
L_001365:
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DA, a);
    popAddress();
}

void game::SUB_00136A() {
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a == 0x01) {
        goto L_001373;
    }
    goto L_00137B;
L_001373:
    a = 0x1C;
    setLoadFlag(a);
    pushAddress(0x001375);
    SUB_000831();
    if (poppedEntry.value != 0x001375) return;
    SUB_0018AD();
    return;
L_00137B:
    a = 0x01;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00137E() {
    a = myMapper->readCPU(0x0056);
    setLoadFlag(a);
    if (a != 0x08) {
        if (a == 0x04) {
            goto L_00138B;
        }
        goto L_0014CF;
    L_00138B:
        goto L_001432;
    }
    a = myMapper->readCPU(0x005A);
    setLoadFlag(a);
    if (!flgZ) {
        pushAddress(0x001392);
        SUB_002AE1();
        if (poppedEntry.value != 0x001392) return;
        opDEC(0x0001, 1);
        pushAddress(0x001397);
        SUB_00150A();
        if (poppedEntry.value != 0x001397) return;
        if (!flgZ) {
            goto L_0013CD;
        }
    }
    a = 0x24;
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    a = 0x49;
    setLoadFlag(a);
    pushAddress(0x0013A2);
    SUB_0019E8();
    if (poppedEntry.value != 0x0013A2) return;
    if (flgZ) {
        a = myMapper->readCPU(0x0200);
        setLoadFlag(a);
        myMapper->writeCPU(0x0001, a);
    }
    else {
        pushAddress(0x0013AF);
        SUB_00150A();
        if (poppedEntry.value != 0x0013AF) return;
        if (!flgZ) {
            if (a != 0x02) {
                goto L_0013BB;
            }
            goto L_0014CF;
        L_0013BB:
            a = myMapper->readCPU(0x005B);
            setLoadFlag(a);
            if (!flgZ) {
                flgC = false;
                opADC(0x01);
                opCMP(a, 0x10);
                if (flgZ) {
                    goto L_0013D2;
                }
                if (!flgC) {
                    goto L_0013D2;
                }
                a = 0x10;
                setLoadFlag(a);
                goto L_0013D2;
            L_0013CD:
                goto L_0014CF;
            }
            a = 0x01;
            setLoadFlag(a);
        L_0013D2:
            myMapper->writeCPU(0x005B, a);
            x = a;
            setLoadFlag(x);
            opDEX(1);
            a = myMapper->readCPU(0xC147 + x);
            setLoadFlag(a);
            myMapper->writeCPU(0x0002, a);
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x005A, a);
            myMapper->writeCPU(0x005C, a);
            pushAddress(0x0013E1);
            SUB_0014EE();
            if (poppedEntry.value != 0x0013E1) return;
            goto L_00140D;
        }
        a = myMapper->readCPU(0x005C);
        setLoadFlag(a);
        if (!flgZ) {
            flgC = false;
            opADC(0x01);
            opCMP(a, 0x06);
            if (flgZ) {
                goto L_0013FB;
            }
            if (!flgC) {
                goto L_0013FB;
            }
            a = 0x01;
            setLoadFlag(a);
        }
        else {
            a = 0x02;
            setLoadFlag(a);
        }
    L_0013FB:
        myMapper->writeCPU(0x005C, a);
        x = a;
        setLoadFlag(x);
        opDEX(1);
        a = myMapper->readCPU(0xC159 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0002, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x005A, a);
        myMapper->writeCPU(0x005B, a);
        pushAddress(0x00140A);
        SUB_0014EE();
        if (poppedEntry.value != 0x00140A) return;
    L_00140D:
        a = myMapper->readCPU(0x00A1);
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        myMapper->writeCPU(0x0203, a);
        pushAddress(0x001414);
        SUB_002AD1();
        if (poppedEntry.value != 0x001414) return;
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0004, a);
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        if (a != 0x54) {
            a = 0x00;
            setLoadFlag(a);
        }
        else {
            a = 0x24;
            setLoadFlag(a);
            myMapper->writeCPU(0x0002, a);
            a = 0x01;
            setLoadFlag(a);
        }
        pushAddress(0x00142C);
        SUB_003096();
        if (poppedEntry.value != 0x00142C) return;
        goto L_0014CF;
    L_001432:
        a = myMapper->readCPU(0x005A);
        setLoadFlag(a);
        if (!flgZ) {
            pushAddress(0x001436);
            SUB_002AE1();
            if (poppedEntry.value != 0x001436) return;
            opINC(0x0001, 1);
            pushAddress(0x00143B);
            SUB_00150A();
            if (poppedEntry.value != 0x00143B) return;
            if (a != 0x01) {
                goto L_0014CF;
            }
        }
        a = 0x24;
        setLoadFlag(a);
        myMapper->writeCPU(0x000A, a);
        a = 0x49;
        setLoadFlag(a);
        myMapper->writeCPU(0x000B, a);
        pushAddress(0x00144D);
        SUB_0019E6();
        if (poppedEntry.value != 0x00144D) return;
        if (flgZ) {
            a = myMapper->readCPU(0x0200);
            setLoadFlag(a);
            myMapper->writeCPU(0x0001, a);
        }
        else {
            pushAddress(0x00145A);
            SUB_00150A();
            if (poppedEntry.value != 0x00145A) return;
            if (!flgZ) {
                if (a == 0x02) {
                    goto L_00148B;
                }
                a = myMapper->readCPU(0x005B);
                setLoadFlag(a);
                if (!flgZ) {
                    flgC = true;
                    opSBC(0x01);
                    if (a < 0x01) {
                        goto L_001476;
                    }
                }
                else {
                    a = 0x0D;
                    setLoadFlag(a);
                    goto L_001478;
                L_001476:
                    a = 0x01;
                    setLoadFlag(a);
                }
            L_001478:
                myMapper->writeCPU(0x005B, a);
                x = a;
                setLoadFlag(x);
                opDEX(1);
                a = myMapper->readCPU(0xC147 + x);
                setLoadFlag(a);
                myMapper->writeCPU(0x0002, a);
                a = 0x03;
                setLoadFlag(a);
                myMapper->writeCPU(0x005C, a);
                pushAddress(0x001485);
                SUB_0014F9();
                if (poppedEntry.value != 0x001485) return;
                goto L_0014B1;
            }
        L_00148B:
            a = myMapper->readCPU(0x005C);
            setLoadFlag(a);
            if (!flgZ) {
                flgC = false;
                opADC(0x01);
                opCMP(a, 0x06);
                if (flgZ) {
                    goto L_00149F;
                }
                if (!flgC) {
                    goto L_00149F;
                }
                a = 0x01;
                setLoadFlag(a);
            }
            else {
                a = 0x01;
                setLoadFlag(a);
            }
        L_00149F:
            myMapper->writeCPU(0x005C, a);
            flgC = true;
            opSBC(0x01);
            x = a;
            setLoadFlag(x);
            a = myMapper->readCPU(0xC159 + x);
            setLoadFlag(a);
            myMapper->writeCPU(0x0002, a);
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x005B, a);
            pushAddress(0x0014AE);
            SUB_0014F9();
            if (poppedEntry.value != 0x0014AE) return;
        L_0014B1:
            a = myMapper->readCPU(0x00A1);
            setLoadFlag(a);
            myMapper->writeCPU(0x0203, a);
            myMapper->writeCPU(0x0000, a);
            pushAddress(0x0014B8);
            SUB_002ACD();
            if (poppedEntry.value != 0x0014B8) return;
            a = myMapper->readCPU(0x0002);
            setLoadFlag(a);
            if (a != 0x54) {
                a = 0x00;
                setLoadFlag(a);
            }
            else {
                a = 0x24;
                setLoadFlag(a);
                myMapper->writeCPU(0x0002, a);
                a = 0x01;
                setLoadFlag(a);
            }
            pushAddress(0x0014CC);
            SUB_003096();
            if (poppedEntry.value != 0x0014CC) return;
        }
    }
L_0014CF:
    pushAddress(0x0014CF);
    SUB_0012CB();
    if (poppedEntry.value != 0x0014CF) return;
    myMapper->writeCPU(0x005A, a);
    if (flgZ) {
        goto L_0014ED;
    }
    a = myMapper->readCPU(0x0200);
    setLoadFlag(a);
    flgC = false;
    opADC(0x08);
    pushAddress(0x0014DC);
    SUB_002016();
    if (poppedEntry.value != 0x0014DC) return;
    myMapper->writeCPU(0x0059, a);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0096, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x005C, a);
    myMapper->writeCPU(0x005B, a);
    myMapper->writeCPU(0x0085, a);
L_0014ED:
    popAddress();
}

void game::SUB_0014EE() {
    a = myMapper->readCPU(0x0200);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0001, a);
    SUB_001501();
    return;
}

void game::SUB_0014F9() {
    a = myMapper->readCPU(0x0200);
    setLoadFlag(a);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0001, a);
    SUB_001501();
    return;
}

void game::SUB_001501() {
    opAND(0x06);
    if (!flgZ) {
        goto L_001509;
    }
    a = 0x08;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FF, a);
L_001509:
    popAddress();
}

void game::SUB_00150A() {
    pushAddress(0x00150A);
    SUB_002AE1();
    if (poppedEntry.value != 0x00150A) return;
    a = 0x2C;
    setLoadFlag(a);
    pushAddress(0x00150F);
    SUB_002FE8();
    if (poppedEntry.value != 0x00150F) return;
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x01);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC48B + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0004, a);
    a = myMapper->readCPU(0xC48C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0005, a);
    a = 0x43;
    setLoadFlag(a);
    myMapper->writeCPU(0x0006, a);
    a = 0xC1;
    setLoadFlag(a);
    myMapper->writeCPU(0x0007, a);
    pushAddress(0x00152B);
    SUB_0018AD();
    if (poppedEntry.value != 0x00152B) return;
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a == 0x01) {
        a = 0x1E;
        setLoadFlag(a);
        pushAddress(0x001538);
        SUB_000831();
        if (poppedEntry.value != 0x001538) return;
        pushAddress(0x00153B);
        SUB_0018AD();
        if (poppedEntry.value != 0x00153B) return;
        if (flgZ) {
            goto L_001544;
        }
        a = 0x02;
        setLoadFlag(a);
        myMapper->writeCPU(0x0008, a);
    }
L_001544:
    a = myMapper->readCPU(0x0008);
    setLoadFlag(a);
    popAddress();
}

void game::SUB_001547() {
    a = 0xFF;
    setLoadFlag(a);
    pushAddress(0x001549);
    SUB_0019E6();
    if (poppedEntry.value != 0x001549) return;
    if (a == 0x00) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0094);
    setLoadFlag(a);
    if (a >= 0xF0) {
    }
    else {
        pushAddress(0x00155A);
        SUB_001990();
        if (poppedEntry.value != 0x00155A) return;
        if (!flgZ) {
            a = myMapper->readCPU(0x0056);
            setLoadFlag(a);
            if (a == 0x01) {
                a = 0x02;
                setLoadFlag(a);
            }
            else {
                a = 0x01;
                setLoadFlag(a);
            }
            myMapper->writeCPU(0x0056, a);
            myMapper->writeCPU(0x0057, a);
        }
        a = myMapper->readCPU(0x0200);
        setLoadFlag(a);
        myMapper->writeCPU(0x0001, a);
        a = 0x00;
        setLoadFlag(a);
        pushAddress(0x001577);
        SUB_002F72();
        if (poppedEntry.value != 0x001577) return;
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        myMapper->writeCPU(0x0200, a);
        a = myMapper->readCPU(0x0056);
        setLoadFlag(a);
        if (a != 0x01) {
            if (a == 0x02) {
                goto L_0015A1;
            }
        }
        else {
            a = myMapper->readCPU(0x009E);
            setLoadFlag(a);
            if (!flgZ) {
                opINC(0x0203, 1);
                a = 0x00;
                setLoadFlag(a);
                myMapper->writeCPU(0x009E, a);
            }
            else {
                a = 0x01;
                setLoadFlag(a);
                myMapper->writeCPU(0x009E, a);
                goto L_0015B3;
            L_0015A1:
                a = myMapper->readCPU(0x009E);
                setLoadFlag(a);
                if (!flgZ) {
                    opDEC(0x0203, 1);
                    a = 0x00;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x009E, a);
                }
                else {
                    a = 0x01;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x009E, a);
                }
            }
        }
    L_0015B3:
        a = myMapper->readCPU(0x0203);
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        pushAddress(0x0015B8);
        SUB_001800();
        if (poppedEntry.value != 0x0015B8) return;
        a = myMapper->readCPU(0x0094);
        setLoadFlag(a);
        if (!flgZ) {
            a = myMapper->readCPU(0x0001);
            setLoadFlag(a);
            flgC = true;
            opSBC(0x10);
            if (a >= myMapper->readCPU(0x0095)) {
                a = 0xFF;
                setLoadFlag(a);
                myMapper->writeCPU(0x0095, a);
            }
            pushAddress(0x0015CC);
            SUB_0012CB();
            if (poppedEntry.value != 0x0015CC) return;
            myMapper->writeCPU(0x005A, a);
            if (flgZ) {
                goto L_0015F1;
            }
            a = myMapper->readCPU(0x004B);
            setLoadFlag(a);
            flgC = true;
            opSBC(0x11);
            myMapper->writeCPU(0x0200, a);
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x005A, a);
        }
        else {
            a = 0x04;
            setLoadFlag(a);
            myMapper->writeCPU(0x00FF, a);
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x0094, a);
            a = myMapper->readCPU(0x0001);
            setLoadFlag(a);
            myMapper->writeCPU(0x0095, a);
            goto L_0015F1;
        L_0015F1:
            a = 0x28;
            setLoadFlag(a);
            SUB_003070();
            return;
        }
        pushAddress(0x0015F6);
        SUB_002AE1();
        if (poppedEntry.value != 0x0015F6) return;
        a = 0x2C;
        setLoadFlag(a);
        myMapper->writeCPU(0x0002, a);
        pushAddress(0x0015FD);
        SUB_002ACD();
        if (poppedEntry.value != 0x0015FD) return;
        a = myMapper->readCPU(0x0057);
        setLoadFlag(a);
        opAND(0x03);
        opLSR_A(1);
        pushAddress(0x001605);
        SUB_003096();
        if (poppedEntry.value != 0x001605) return;
        a = 0xF0;
        setLoadFlag(a);
        myMapper->writeCPU(0x0094, a);
        popAddress();
        return;
    }
    opINC(0x0094, 1);
    a = myMapper->readCPU(0x0094);
    setLoadFlag(a);
    if (a == 0xF4) {
        a = myMapper->readCPU(0x0095);
        setLoadFlag(a);
        if (a == 0xFF) {
            goto L_001642;
        }
        a = 0x04;
        setLoadFlag(a);
        pushAddress(0x00161D);
        SUB_003070();
        if (poppedEntry.value != 0x00161D) return;
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x042C, a);
        myMapper->writeCPU(0x0094, a);
        myMapper->writeCPU(0x0095, a);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0096, a);
        a = myMapper->readCPU(0x00A0);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00164F;
        }
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x009F, a);
        a = 0x4B;
        setLoadFlag(a);
        myMapper->writeCPU(0x003F, a);
        a = 0x0A;
        setLoadFlag(a);
        myMapper->writeCPU(0x0096, a);
        a = 0x40;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FC, a);
        popAddress();
        return;
    L_001642:
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x042C, a);
        myMapper->writeCPU(0x0094, a);
        myMapper->writeCPU(0x0095, a);
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(0x0096, a);
    }
L_00164F:
    popAddress();
}

void game::SUB_001697() {
    a = 0xFF;
    setLoadFlag(a);
    pushAddress(0x001699);
    SUB_0019E6();
    if (poppedEntry.value != 0x001699) return;
    if (!flgZ) {
        pushAddress(0x00169E);
        SUB_002AE1();
        if (poppedEntry.value != 0x00169E) return;
        opINC(0x0001, 2);
        a = myMapper->readCPU(0x0057);
        setLoadFlag(a);
        if (a != 0x02) {
            a = myMapper->readCPU(0x0201);
            setLoadFlag(a);
        }
        else {
            a = myMapper->readCPU(0x0201);
            setLoadFlag(a);
            flgC = true;
            opSBC(0x02);
        }
        myMapper->writeCPU(0x0002, a);
        pushAddress(0x0016B9);
        SUB_003075();
        if (poppedEntry.value != 0x0016B9) return;
        pushAddress(0x0016BC);
        SUB_0012CB();
        if (poppedEntry.value != 0x0016BC) return;
        if (flgZ) {
            goto L_0016C5;
        }
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(0x0096, a);
    }
L_0016C5:
    popAddress();
}

void game::SUB_0016C6() {
    a = myMapper->readCPU(0x003F);
    setLoadFlag(a);
    if (flgZ) {
    }
    else {
        a = 0xDB;
        setLoadFlag(a);
        myMapper->writeCPU(0x000A, a);
        a = 0x36;
        setLoadFlag(a);
        pushAddress(0x0016D3);
        SUB_0019E8();
        if (poppedEntry.value != 0x0016D3) return;
        if (flgZ) {
            popAddress();
            return;
        }
        pushAddress(0x0016D9);
        SUB_001990();
        if (poppedEntry.value != 0x0016D9) return;
        if (flgZ) {
            a = myMapper->readCPU(0x0056);
            setLoadFlag(a);
            if (a == 0x01) {
                goto L_00170A;
            }
            if (a == 0x02) {
                goto L_001710;
            }
        }
        a = myMapper->readCPU(0x00A2);
        setLoadFlag(a);
        opASL_A(1);
        myMapper->writeCPU(0x00A2, a);
        if (!flgZ) {
        }
        else {
            a = 0x20;
            setLoadFlag(a);
            myMapper->writeCPU(0x00A2, a);
            a = myMapper->readCPU(0x009F);
            setLoadFlag(a);
            if (!flgZ) {
                if (a < 0x04) {
                    goto L_001703;
                }
            }
            a = 0x02;
            setLoadFlag(a);
            goto L_001705;
        L_001703:
            a = 0x05;
            setLoadFlag(a);
        L_001705:
            myMapper->writeCPU(0x009F, a);
            goto L_001753;
        L_00170A:
            opINC(0x0203, 1);
            goto L_001713;
        L_001710:
            opDEC(0x0203, 1);
        L_001713:
            pushAddress(0x001713);
            SUB_0012CB();
            if (poppedEntry.value != 0x001713) return;
            myMapper->writeCPU(0x005A, a);
            a = myMapper->readCPU(0x0200);
            setLoadFlag(a);
            pushAddress(0x00171B);
            SUB_002016();
            if (poppedEntry.value != 0x00171B) return;
            myMapper->writeCPU(0x0059, a);
            pushAddress(0x001720);
            SUB_0018EB();
            if (poppedEntry.value != 0x001720) return;
            if (!flgZ) {
                x = myMapper->readCPU(0x0053);
                setLoadFlag(x);
                if (x == 0x01) {
                    flgC = false;
                    opADC(myMapper->readCPU(0x0200));
                    myMapper->writeCPU(0x0200, a);
                }
                pushAddress(0x001732);
                SUB_00136A();
                if (poppedEntry.value != 0x001732) return;
                if (!flgZ) {
                    a = 0x08;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x0096, a);
                    goto L_0017BF;
                }
            }
            a = 0x08;
            setLoadFlag(a);
            myMapper->writeCPU(0x00FF, a);
            a = myMapper->readCPU(0x009F);
            setLoadFlag(a);
            if (!flgZ) {
                if (a >= 0x06) {
                    goto L_00174F;
                }
                opINC(0x009F, 1);
                goto L_001753;
            }
        L_00174F:
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x009F, a);
        }
    L_001753:
        x = myMapper->readCPU(0x009F);
        setLoadFlag(x);
        opDEX(1);
        a = myMapper->readCPU(0xC1A2 + x);
        setLoadFlag(a);
        pushAddress(0x001759);
        SUB_003070();
        if (poppedEntry.value != 0x001759) return;
        a = myMapper->readCPU(0x009F);
        setLoadFlag(a);
        opLSR_A(2);
        if (!flgZ) {
            a = 0x00;
            setLoadFlag(a);
        }
        else {
            a = 0x01;
            setLoadFlag(a);
        }
        if (!flgZ) {
            a = 0x04;
            setLoadFlag(a);
            flgC = false;
            opADC(myMapper->readCPU(0x0203));
            myMapper->writeCPU(0x0000, a);
            a = myMapper->readCPU(0x0200);
            setLoadFlag(a);
            flgC = true;
            opSBC(0x0E);
            myMapper->writeCPU(0x0001, a);
            a = 0x21;
            setLoadFlag(a);
            myMapper->writeCPU(0x0003, a);
            a = 0xF6;
            setLoadFlag(a);
            myMapper->writeCPU(0x0002, a);
        }
        else {
            a = myMapper->readCPU(0x0057);
            setLoadFlag(a);
            if (a == 0x01) {
                a = 0x0E;
                setLoadFlag(a);
                flgC = false;
                opADC(myMapper->readCPU(0x0203));
            }
            else {
                a = myMapper->readCPU(0x0203);
                setLoadFlag(a);
                flgC = true;
                opSBC(0x0E);
            }
            myMapper->writeCPU(0x0000, a);
            a = 0x06;
            setLoadFlag(a);
            flgC = false;
            opADC(myMapper->readCPU(0x0200));
            myMapper->writeCPU(0x0001, a);
            a = 0x12;
            setLoadFlag(a);
            myMapper->writeCPU(0x0003, a);
            a = 0xFA;
            setLoadFlag(a);
            myMapper->writeCPU(0x0002, a);
        }
        a = myMapper->readCPU(0x00A0);
        setLoadFlag(a);
        if (a != 0x01) {
            a = 0xD8;
            setLoadFlag(a);
        }
        else {
            a = 0xD0;
            setLoadFlag(a);
        }
        myMapper->writeCPU(0x0004, a);
        SUB_003078();
        return;
    }
L_0017BF:
    a = 0x12;
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU(0x00A0);
    setLoadFlag(a);
    if (a == 0x01) {
        goto L_0017D3;
    }
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0452, a);
    a = 0xD8;
    setLoadFlag(a);
    goto L_0017DA;
L_0017D3:
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0451, a);
    a = 0xD0;
    setLoadFlag(a);
L_0017DA:
    myMapper->writeCPU(0x0004, a);
    pushAddress(0x0017DC);
    SUB_003094();
    if (poppedEntry.value != 0x0017DC) return;
    pushAddress(0x0017DF);
    SUB_0017F2();
    if (poppedEntry.value != 0x0017DF) return;
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0096, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00A0, a);
    myMapper->writeCPU(0x009F, a);
    a = myMapper->readCPU(0x0519);
    setLoadFlag(a);
    myMapper->writeCPU(0x00FC, a);
    popAddress();
}

void game::SUB_0017F2() {
    a = 0x19;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x3F;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = 0x4E;
    setLoadFlag(a);
    pushAddress(0x0017FC);
    SUB_000815();
    if (poppedEntry.value != 0x0017FC) return;
    popAddress();
}

void game::SUB_001800() {
    a = myMapper->readCPU(0x00A0);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    y = myMapper->readCPU(0x0053);
    setLoadFlag(y);
    if (y == 0x03) {
    }
    else {
        a = myMapper->readCPU(0x0203);
        setLoadFlag(a);
        if (y != 0x01) {
            opCMP(a, 0x88);
            if (flgZ) {
                goto L_001827;
            }
            if (!flgC) {
                goto L_001827;
            }
        }
        else {
            opCMP(a, 0x28);
            if (!flgZ) {
                if (!flgC) {
                    goto L_001827;
                }
                goto L_0018A8;
            }
        L_001827:
            a = myMapper->readCPU(0x0200);
            setLoadFlag(a);
            flgC = false;
            opADC(0x08);
            pushAddress(0x00182D);
            SUB_002016();
            if (poppedEntry.value != 0x00182D) return;
            myMapper->writeCPU(0x0059, a);
            a = myMapper->readCPU(0x0053);
            setLoadFlag(a);
            flgC = true;
            opSBC(0x01);
            opASL_A(1);
            x = a;
            setLoadFlag(x);
            a = myMapper->readCPU(0x0059);
            setLoadFlag(a);
            if (a != myMapper->readCPU(0xC1A8 + x)) {
                opINX(1);
                if (a != myMapper->readCPU(0xC1A8 + x)) {
                    goto L_0018A8;
                }
            }
            a = x;
            setLoadFlag(a);
            opAND(0x01);
            if (!flgZ) {
                a = myMapper->readCPU(0x0452);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_0018A8;
                }
                a = 0x02;
                setLoadFlag(a);
                myMapper->writeCPU(0x00A0, a);
                a = myMapper->readCPU(0x02D8);
                setLoadFlag(a);
                myMapper->writeCPU(0x0001, a);
                a = myMapper->readCPU(0x02DB);
                setLoadFlag(a);
                myMapper->writeCPU(0x0000, a);
                goto L_00187D;
            }
            a = myMapper->readCPU(0x0451);
            setLoadFlag(a);
            if (flgZ) {
                goto L_0018A8;
            }
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x00A0, a);
            a = myMapper->readCPU(0x02D0);
            setLoadFlag(a);
            myMapper->writeCPU(0x0001, a);
            a = myMapper->readCPU(0x02D3);
            setLoadFlag(a);
            myMapper->writeCPU(0x0000, a);
        L_00187D:
            a = 0x2E;
            setLoadFlag(a);
            pushAddress(0x00187F);
            SUB_002FE8();
            if (poppedEntry.value != 0x00187F) return;
            pushAddress(0x001882);
            SUB_002AE1();
            if (poppedEntry.value != 0x001882) return;
            a = 0x30;
            setLoadFlag(a);
            pushAddress(0x001887);
            SUB_000847();
            if (poppedEntry.value != 0x001887) return;
            pushAddress(0x00188A);
            SUB_002FEF();
            if (poppedEntry.value != 0x00188A) return;
            if (!flgZ) {
                a = myMapper->readCPU(0x00FC);
                setLoadFlag(a);
                myMapper->writeCPU(0x0519, a);
                a = myMapper->readCPU(0x0053);
                setLoadFlag(a);
                if (a != 0x04) {
                    goto L_0018A7;
                }
                a = 0x19;
                setLoadFlag(a);
                myMapper->writeCPU(0x0000, a);
                a = 0x3F;
                setLoadFlag(a);
                myMapper->writeCPU(0x0001, a);
                a = 0x46;
                setLoadFlag(a);
                pushAddress(0x0018A4);
                SUB_000815();
                if (poppedEntry.value != 0x0018A4) return;
            L_0018A7:
                popAddress();
                return;
            }
        }
    }
L_0018A8:
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00A0, a);
    popAddress();
}

void game::SUB_0018AD() {
    a = 0xF3;
    setLoadFlag(a);
    myMapper->writeCPU(0x000B, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0086, a);
    y = 0x00;
    setLoadFlag(y);
    a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    while (true) {
        myMapper->writeCPU(0x0000, a);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        myMapper->writeCPU(0x0001, a);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        flgC = false;
        opADC(myMapper->readCPU(0x0006));
        myMapper->writeCPU(0x0002, a);
        a = myMapper->readCPU(0x0007);
        setLoadFlag(a);
        opADC(0x00);
        myMapper->writeCPU(0x0003, a);
        myMapper->writeCPU(0x0086, y);
        pushAddress(0x0018D0);
        SUB_002FF3();
        if (poppedEntry.value != 0x0018D0) return;
        if (!flgZ) {
            goto L_0018E1;
        }
        y = myMapper->readCPU(0x0086);
        setLoadFlag(y);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (a == 0xFE) {
            goto L_0018E6;
        }
    }
L_0018E1:
    a = 0x01;
    setLoadFlag(a);
    goto L_0018E8;
L_0018E6:
    a = 0x00;
    setLoadFlag(a);
L_0018E8:
    myMapper->writeCPU(0x000C, a);
    popAddress();
}

void game::SUB_0018EB() {
    a = myMapper->readCPU(0x005A);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x0059);
        setLoadFlag(a);
        if (!flgZ) {
            opAND(0x01);
            if (flgZ) {
                a = myMapper->readCPU(0x0056);
                setLoadFlag(a);
                if (a == 0x01) {
                    goto L_001914;
                }
                if (a == 0x02) {
                    goto L_001911;
                }
            }
            else {
                a = myMapper->readCPU(0x0056);
                setLoadFlag(a);
                if (a == 0x01) {
                    goto L_001911;
                }
                if (a == 0x02) {
                    goto L_001914;
                }
                goto L_001917;
            L_001911:
                a = 0xFF;
                setLoadFlag(a);
                popAddress();
                return;
            L_001914:
                a = 0x01;
                setLoadFlag(a);
                popAddress();
                return;
            }
        }
    }
L_001917:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00191A() {
    a = myMapper->readCPU(0x0200);
    setLoadFlag(a);
    flgC = false;
    opADC(0x08);
    pushAddress(0x001920);
    SUB_002016();
    if (poppedEntry.value != 0x001920) return;
    myMapper->writeCPU(0x0059, a);
    if (a == 0x01) {
        goto L_001938;
    }
    x = 0x02;
    setLoadFlag(x);
    a = 0x0C;
    setLoadFlag(a);
    while (true) {
        if (x == myMapper->readCPU(0x0059)) {
            goto L_00193B;
        }
        flgC = false;
        opADC(0x06);
        opINX(1);
    }
L_001938:
    flgC = true;
    opSBC(0x01);
L_00193B:
    x = a;
    setLoadFlag(x);
    while (true) {
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0086, a);
        a = myMapper->readCPU(0xC08C + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        opINX(1);
        a = myMapper->readCPU(0xC08C + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0001, a);
        opINX(1);
        a = myMapper->readCPU(0xC08C + x);
        setLoadFlag(a);
        flgC = false;
        opADC(myMapper->readCPU(0x0006));
        myMapper->writeCPU(0x0002, a);
        a = myMapper->readCPU(0x0007);
        setLoadFlag(a);
        myMapper->writeCPU(0x0003, a);
        opINX(1);
        a = myMapper->readCPU(0xC08C + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0008, a);
        opINX(1);
        a = myMapper->readCPU(0xC08C + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0009, a);
        do {
            pushAddress(0x001964);
            SUB_002FEF();
            if (poppedEntry.value != 0x001964) return;
            if (!flgZ) {
                goto L_00198B;
            }
            a = myMapper->readCPU(0x0000);
            setLoadFlag(a);
            flgC = false;
            opADC(myMapper->readCPU(0x0008));
            myMapper->writeCPU(0x0000, a);
            opDEC(0x0001, 1);
            opINC(0x0086, 1);
            a = myMapper->readCPU(0x0009);
            setLoadFlag(a);
        } while (a != myMapper->readCPU(0x0086));
        opINX(1);
        a = myMapper->readCPU(0xC08C + x);
        setLoadFlag(a);
        if (a == 0xFE) {
            goto L_001986;
        }
        opINX(1);
    }
L_001986:
    a = 0x00;
    setLoadFlag(a);
    goto L_00198D;
L_00198B:
    a = 0x01;
    setLoadFlag(a);
L_00198D:
    myMapper->writeCPU(0x005A, a);
    popAddress();
}

void game::SUB_001990() {
    a = myMapper->readCPU(0x0056);
    setLoadFlag(a);
    if (a != 0x01) {
        if (a == 0x02) {
            goto L_0019AF;
        }
    }
    else {
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        opASL_A(1);
        x = a;
        setLoadFlag(x);
        opDEX(1);
        a = myMapper->readCPU(0xC1B4 + x);
        setLoadFlag(a);
        opCMP(a, myMapper->readCPU(0x0203));
        if (!flgZ) {
            if (!flgC) {
                goto L_0019E0;
            }
            goto L_0019E3;
        L_0019AF:
            a = myMapper->readCPU(0x0053);
            setLoadFlag(a);
            opASL_A(1);
            x = a;
            setLoadFlag(x);
            opDEX(2);
            a = myMapper->readCPU(0xC1B4 + x);
            setLoadFlag(a);
            if (a < myMapper->readCPU(0x0203)) {
                a = myMapper->readCPU(0x0053);
                setLoadFlag(a);
                if (a == 0x04) {
                    goto L_0019E3;
                }
                x = myMapper->readCPU(0x0059);
                setLoadFlag(x);
                if (a != 0x03) {
                    if (x != 0x06) {
                        goto L_0019E3;
                    }
                }
                else {
                    if (x != 0x05) {
                        goto L_0019E3;
                    }
                }
                a = myMapper->readCPU(0x0203);
                setLoadFlag(a);
                opCMP(a, 0x68);
                if (!flgZ) {
                    if (!flgC) {
                        goto L_0019E0;
                    }
                    goto L_0019E3;
                }
            }
        }
    L_0019E0:
        a = 0x01;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_0019E3:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0019E6() {
    myMapper->writeCPU(0x000A, a);
    SUB_0019E8();
    return;
}

void game::SUB_0019E8() {
    myMapper->writeCPU(0x000B, a);
    opINC(0x0088, 1);
    a = myMapper->readCPU(0x0088);
    setLoadFlag(a);
    if (a < 0x0F) {
    }
    else {
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0088, a);
    }
    if (a < 0x08) {
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0xC1BC + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x000A));
    }
    else {
        flgC = true;
        opSBC(0x08);
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0xC1BC + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x000B));
    }
    if (flgZ) {
        goto L_001A13;
    }
    a = 0x01;
    setLoadFlag(a);
L_001A13:
    myMapper->writeCPU(0x00BE, a);
    popAddress();
}

void game::SUB_001A16() {
    pushAddress(0x001A16);
    SUB_002166();
    if (poppedEntry.value != 0x001A16) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x005D, a);
    do {
        pushAddress(0x001A1D);
        SUB_002FD5();
        if (poppedEntry.value != 0x001A1D) return;
        a = myMapper->readCPU(0x0200 + x);
        setLoadFlag(a);
        if (a != 0xFF) {
            goto L_001A3D;
        }
        a = myMapper->readCPU(0x0036);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_001A40;
        }
        a = 0x80;
        setLoadFlag(a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        myMapper->writeCPU((0x005E + x) & 0x00ff, a);
        a = 0x10;
        setLoadFlag(a);
        myMapper->writeCPU(0x0037, a);
        pushAddress(0x001A35);
        SUB_002AF7();
        if (poppedEntry.value != 0x001A35) return;
        a = myMapper->readCPU(0xC443 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0036, a);
    L_001A3D:
        pushAddress(0x001A3D);
        SUB_001A4C();
        if (poppedEntry.value != 0x001A3D) return;
    L_001A40:
        a = myMapper->readCPU(0x005D);
        setLoadFlag(a);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x005D, a);
    } while (a != 0x09);
    popAddress();
}

void game::SUB_001A4C() {
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x005E + x) & 0x00ff);
    setLoadFlag(a);
    if (a != 0x80) {
        if (a == 0x81) {
            goto L_001A80;
        }
        if (a == 0x01) {
            goto L_001A83;
        }
        if (a == 0x02) {
            goto L_001A86;
        }
        if (a == 0xC0) {
            goto L_001A89;
        }
        if (a == 0xC1) {
            goto L_001A89;
        }
        if (a == 0xC2) {
            goto L_001A89;
        }
        if (a == 0x08) {
            goto L_001A8F;
        }
        if (a == 0x10) {
            goto L_001A92;
        }
        if (a == 0x20) {
            goto L_001A95;
        }
        if (a == 0x40) {
            goto L_001A98;
        }
        popAddress();
        return;
    }
    goto L_001A9C;
L_001A80:
    goto L_001B00;
L_001A83:
    goto L_001B2C;
L_001A86:
    SUB_001C30();
    return;
L_001A89:
    a = myMapper->readCPU(0x0421 + x);
    setLoadFlag(a);
    SUB_001D8B();
    return;
L_001A8F:
    SUB_001C69();
    return;
L_001A92:
    SUB_001CD0();
    return;
L_001A95:
    SUB_001D32();
    return;
L_001A98:
    pushAddress(0x001A98);
    SUB_001F07();
    if (poppedEntry.value != 0x001A98) return;
    popAddress();
    return;
L_001A9C:
    pushAddress(0x001A9C);
    SUB_002FD5();
    if (poppedEntry.value != 0x001A9C) return;
    a = 0x30;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    myMapper->writeCPU(0x0001, a);
    a = 0x90;
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x001AAB);
    SUB_002ADB();
    if (poppedEntry.value != 0x001AAB) return;
    a = myMapper->readCPU(0x0037);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x81;
        setLoadFlag(a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        myMapper->writeCPU((0x005E + x) & 0x00ff, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU((0x008A + x) & 0x00ff, a);
        a = myMapper->readCPU(0x00AD);
        setLoadFlag(a);
        if (!flgZ) {
        }
        else {
            a = myMapper->readCPU(0x005D);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_001AFF;
            }
            a = 0xC0;
            setLoadFlag(a);
            x = myMapper->readCPU(0x005D);
            setLoadFlag(x);
            myMapper->writeCPU((0x005E + x) & 0x00ff, a);
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x0421 + x, a);
            goto L_001AF7;
        }
        a = myMapper->readCPU(0x0043);
        setLoadFlag(a);
        if (flgZ) {
            a = myMapper->readCPU(0x005D);
            setLoadFlag(a);
            if (flgZ) {
                a = 0xC0;
                setLoadFlag(a);
                x = myMapper->readCPU(0x005D);
                setLoadFlag(x);
                myMapper->writeCPU((0x005E + x) & 0x00ff, a);
                a = myMapper->readCPU(0x0421 + x);
                setLoadFlag(a);
                if (a == 0x01) {
                    a = 0x03;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x0421 + x, a);
                }
                else {
                    a = 0x01;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x0421 + x, a);
                }
            L_001AF7:
                pushAddress(0x001AF7);
                SUB_002AF7();
                if (poppedEntry.value != 0x001AF7) return;
                a = myMapper->readCPU(0xC44D + x);
                setLoadFlag(a);
                myMapper->writeCPU(0x0043, a);
            }
        }
    }
L_001AFF:
    popAddress();
    return;
L_001B00:
    a = 0x55;
    setLoadFlag(a);
    pushAddress(0x001B02);
    SUB_001FE4();
    if (poppedEntry.value != 0x001B02) return;
    if (flgZ) {
        pushAddress(0x001B07);
        SUB_002FD5();
        if (poppedEntry.value != 0x001B07) return;
        a = 0x4D;
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        a = 0x32;
        setLoadFlag(a);
        myMapper->writeCPU(0x0001, a);
        a = 0x84;
        setLoadFlag(a);
        myMapper->writeCPU(0x0002, a);
        myMapper->writeCPU(0x0004, x);
        pushAddress(0x001B18);
        SUB_002ADB();
        if (poppedEntry.value != 0x001B18) return;
        opINC(0x0515, 1);
    }
    else {
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU((0x005E + x) & 0x00ff, a);
        a = 0x84;
        setLoadFlag(a);
        myMapper->writeCPU((0x0072 + x) & 0x00ff, a);
    }
    popAddress();
    return;
L_001B2C:
    a = 0xFF;
    setLoadFlag(a);
    pushAddress(0x001B2E);
    SUB_001FE4();
    if (poppedEntry.value != 0x001B2E) return;
    if (flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x001B34);
    SUB_002FD5();
    if (poppedEntry.value != 0x001B34) return;
    mStack.push({ false, a });
    pushAddress(0x001B38);
    SUB_002AEC();
    if (poppedEntry.value != 0x001B38) return;
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    pushAddress(0x001B3D);
    SUB_002016();
    if (poppedEntry.value != 0x001B3D) return;
    y = myMapper->readCPU(0x005D);
    setLoadFlag(y);
    myMapper->writeCPU(0x0068 + y, a);
    opAND(0x01);
    if (flgZ) {
        opINC(0x0000, 1);
    }
    else {
        opDEC(0x0000, 1);
    }
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    pushAddress(0x001B52);
    SUB_00205A();
    if (poppedEntry.value != 0x001B52) return;
    myMapper->writeCPU(0x007D, a);
    pushAddress(0x001B57);
    SUB_002048();
    if (poppedEntry.value != 0x001B57) return;
    flgC = false;
    opADC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x0001, a);
    pushAddress(0x001B5F);
    SUB_001BEE();
    if (poppedEntry.value != 0x001B5F) return;
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x0072 + x) & 0x00ff);
    setLoadFlag(a);
    pushAddress(0x001B66);
    SUB_002AD4();
    if (poppedEntry.value != 0x001B66) return;
    opPLA();
    x = a;
    setLoadFlag(x);
    pushAddress(0x001B6B);
    SUB_003080();
    if (poppedEntry.value != 0x001B6B) return;
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    pushAddress(0x001B70);
    SUB_0020AE();
    if (poppedEntry.value != 0x001B70) return;
    if (!flgZ) {
        pushAddress(0x001B75);
        SUB_002AF7();
        if (poppedEntry.value != 0x001B75) return;
        a = myMapper->readCPU(0xC448 + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x0019));
        if (flgZ) {
            x = myMapper->readCPU(0x005D);
            setLoadFlag(x);
            a = myMapper->readCPU((0x0068 + x) & 0x00ff);
            setLoadFlag(a);
            x = a;
            setLoadFlag(x);
            opDEX(1);
            a = myMapper->readCPU((0x007E + x) & 0x00ff);
            setLoadFlag(a);
            if (a < 0x04) {
                a = myMapper->readCPU(0x0096);
                setLoadFlag(a);
                if (a == 0x02) {
                    x = myMapper->readCPU(0x0004);
                    setLoadFlag(x);
                    a = myMapper->readCPU(0x0200 + x);
                    setLoadFlag(a);
                    if (a < myMapper->readCPU(0x0200)) {
                        flgC = false;
                        opADC(0x0F);
                        if (a >= myMapper->readCPU(0x0200)) {
                            goto L_001BAC;
                        }
                    }
                }
                a = 0x02;
                setLoadFlag(a);
                x = myMapper->readCPU(0x005D);
                setLoadFlag(x);
                myMapper->writeCPU((0x005E + x) & 0x00ff, a);
                opDEC((0x0068 + x) & 0x00ff, 1);
                popAddress();
                return;
            }
        }
    }
L_001BAC:
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    pushAddress(0x001BAE);
    SUB_002090();
    if (poppedEntry.value != 0x001BAE) return;
    if (!flgZ) {
    }
    else {
        pushAddress(0x001BB6);
        SUB_001F40();
        if (poppedEntry.value != 0x001BB6) return;
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = myMapper->readCPU((0x0068 + x) & 0x00ff);
        setLoadFlag(a);
        if (a != 0x01) {
            goto L_001BED;
        }
        pushAddress(0x001BC1);
        SUB_001FC3();
        if (poppedEntry.value != 0x001BC1) return;
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        opCMP(a, 0x20);
        if (!flgZ) {
            if (!flgC) {
                goto L_001BCD;
            }
            popAddress();
            return;
        }
    L_001BCD:
        a = 0x03;
        setLoadFlag(a);
        myMapper->writeCPU(0x0002, a);
        a = 0x04;
        setLoadFlag(a);
        myMapper->writeCPU(0x0003, a);
        pushAddress(0x001BD5);
        SUB_00308E();
        if (poppedEntry.value != 0x001BD5) return;
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x00AD, a);
        a = 0x00;
        setLoadFlag(a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        myMapper->writeCPU((0x0068 + x) & 0x00ff, a);
        a = 0x80;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FE, a);
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = 0x08;
    setLoadFlag(a);
    myMapper->writeCPU((0x005E + x) & 0x00ff, a);
L_001BED:
    popAddress();
}

void game::SUB_001BEE() {
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    opINC(0x040D + x, 1);
    a = myMapper->readCPU(0x040D + x);
    setLoadFlag(a);
    if (a < 0x06) {
        popAddress();
        return;
    }
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x040D + x, a);
    a = myMapper->readCPU((0x0068 + x) & 0x00ff);
    setLoadFlag(a);
    opAND(0x01);
    if (!flgZ) {
        a = myMapper->readCPU((0x0072 + x) & 0x00ff);
        setLoadFlag(a);
        flgC = false;
        opADC(0x04);
        if (a >= 0x80) {
            if (a >= 0x90) {
                goto L_001C16;
            }
            goto L_001C2D;
        }
    L_001C16:
        a = 0x80;
        setLoadFlag(a);
        goto L_001C2D;
    }
    a = myMapper->readCPU((0x0072 + x) & 0x00ff);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x04);
    if (a >= 0x80) {
        if (a >= 0x90) {
            goto L_001C2B;
        }
        goto L_001C2D;
    }
L_001C2B:
    a = 0x8C;
    setLoadFlag(a);
L_001C2D:
    myMapper->writeCPU((0x0072 + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_001C30() {
    a = 0x55;
    setLoadFlag(a);
    pushAddress(0x001C32);
    SUB_001FE4();
    if (poppedEntry.value != 0x001C32) return;
    if (!flgZ) {
        pushAddress(0x001C37);
        SUB_002FD5();
        if (poppedEntry.value != 0x001C37) return;
        myMapper->writeCPU(0x0004, x);
        pushAddress(0x001C3C);
        SUB_002AEC();
        if (poppedEntry.value != 0x001C3C) return;
        opINC(0x0001, 1);
        y = myMapper->readCPU(0x005D);
        setLoadFlag(y);
        a = myMapper->readCPU(0x0072 + y);
        setLoadFlag(a);
        if (a == 0x90) {
            a = 0x94;
            setLoadFlag(a);
        }
        else {
            a = 0x90;
            setLoadFlag(a);
        }
        myMapper->writeCPU(0x0002, a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        myMapper->writeCPU((0x0072 + x) & 0x00ff, a);
        pushAddress(0x001C57);
        SUB_002ADB();
        if (poppedEntry.value != 0x001C57) return;
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        if (a != myMapper->readCPU((0x00A3 + x) & 0x00ff)) {
            goto L_001C68;
        }
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU((0x005E + x) & 0x00ff, a);
    }
L_001C68:
    popAddress();
}

void game::SUB_001C69() {
    a = 0xFF;
    setLoadFlag(a);
    pushAddress(0x001C6B);
    SUB_001FE4();
    if (poppedEntry.value != 0x001C6B) return;
    if (flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x001C71);
    SUB_002FD5();
    if (poppedEntry.value != 0x001C71) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x001C76);
    SUB_002AEC();
    if (poppedEntry.value != 0x001C76) return;
    opINC(0x0001, 1);
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    opAND(0x01);
    if (!flgZ) {
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = myMapper->readCPU((0x0068 + x) & 0x00ff);
        setLoadFlag(a);
        opAND(0x01);
        if (!flgZ) {
            opDEC(0x0000, 1);
        }
        else {
            opINC(0x0000, 1);
        }
    }
    pushAddress(0x001C90);
    SUB_001BEE();
    if (poppedEntry.value != 0x001C90) return;
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x0072 + x) & 0x00ff);
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    pushAddress(0x001C99);
    SUB_002ADB();
    if (poppedEntry.value != 0x001C99) return;
    a = 0x32;
    setLoadFlag(a);
    pushAddress(0x001C9E);
    SUB_000853();
    if (poppedEntry.value != 0x001C9E) return;
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    pushAddress(0x001CA3);
    SUB_002112();
    if (poppedEntry.value != 0x001CA3) return;
    if (!flgZ) {
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = 0x10;
        setLoadFlag(a);
        myMapper->writeCPU((0x005E + x) & 0x00ff, a);
        pushAddress(0x001CAE);
        SUB_002130();
        if (poppedEntry.value != 0x001CAE) return;
        if (!flgZ) {
            a = myMapper->readCPU(0x0019);
            setLoadFlag(a);
            opAND(0x01);
            if (!flgZ) {
                goto L_001CC9;
            }
        }
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = myMapper->readCPU((0x0068 + x) & 0x00ff);
        setLoadFlag(a);
        x = a;
        setLoadFlag(x);
        opDEX(1);
        a = myMapper->readCPU((0x007E + x) & 0x00ff);
        setLoadFlag(a);
        if (a >= 0x04) {
            goto L_001CC9;
        }
        popAddress();
        return;
    L_001CC9:
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = 0x20;
        setLoadFlag(a);
        myMapper->writeCPU((0x005E + x) & 0x00ff, a);
    }
    popAddress();
}

void game::SUB_001CD0() {
    a = 0x77;
    setLoadFlag(a);
    pushAddress(0x001CD2);
    SUB_001FE4();
    if (poppedEntry.value != 0x001CD2) return;
    if (flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x001CD8);
    SUB_002FD5();
    if (poppedEntry.value != 0x001CD8) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x001CDD);
    SUB_002AEC();
    if (poppedEntry.value != 0x001CDD) return;
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    pushAddress(0x001CE2);
    SUB_002016();
    if (poppedEntry.value != 0x001CE2) return;
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    myMapper->writeCPU((0x0068 + x) & 0x00ff, a);
    opAND(0x01);
    if (flgZ) {
        opINC(0x0000, 1);
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        x = 0x00;
        setLoadFlag(x);
        while (true) {
            if (a == myMapper->readCPU(0xC3FC + x)) {
                goto L_001D13;
            }
            opINX(1);
            if (x == 0x0B) {
                goto L_001D25;
            }
        }
    }
    opDEC(0x0000, 1);
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    x = 0x00;
    setLoadFlag(x);
    while (a != myMapper->readCPU(0xC412 + x)) {
        opINX(1);
        if (x == 0x0B) {
            goto L_001D25;
        }
    }
L_001D13:
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    flgC = false;
    opADC(myMapper->readCPU(0xC407 + x));
    myMapper->writeCPU(0x0001, a);
    if (x != 0x0A) {
        goto L_001D25;
    }
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU((0x005E + x) & 0x00ff, a);
L_001D25:
    pushAddress(0x001D25);
    SUB_001BEE();
    if (poppedEntry.value != 0x001D25) return;
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x0072 + x) & 0x00ff);
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    pushAddress(0x001D2E);
    SUB_002ADB();
    if (poppedEntry.value != 0x001D2E) return;
    popAddress();
}

void game::SUB_001D32() {
    a = 0x55;
    setLoadFlag(a);
    pushAddress(0x001D34);
    SUB_001FE4();
    if (poppedEntry.value != 0x001D34) return;
    if (flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x001D3A);
    SUB_002FD5();
    if (poppedEntry.value != 0x001D3A) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x001D3F);
    SUB_002AEC();
    if (poppedEntry.value != 0x001D3F) return;
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    pushAddress(0x001D44);
    SUB_002016();
    if (poppedEntry.value != 0x001D44) return;
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    myMapper->writeCPU((0x0068 + x) & 0x00ff, a);
    opAND(0x01);
    if (flgZ) {
        opDEC(0x0000, 1);
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        if (a == 0x14) {
            opDEC(0x0001, 1);
        }
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_001D73;
        }
    }
    else {
        opINC(0x0000, 1);
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        if (a == 0xEC) {
            opDEC(0x0001, 1);
        }
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        if (a != 0xF4) {
            goto L_001D73;
        }
        goto L_001D7F;
    L_001D73:
        pushAddress(0x001D73);
        SUB_001BEE();
        if (poppedEntry.value != 0x001D73) return;
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = myMapper->readCPU((0x0072 + x) & 0x00ff);
        setLoadFlag(a);
        myMapper->writeCPU(0x0002, a);
        SUB_002ADB();
        return;
    }
L_001D7F:
    a = 0x22;
    setLoadFlag(a);
    pushAddress(0x001D81);
    SUB_003092();
    if (poppedEntry.value != 0x001D81) return;
    a = 0x00;
    setLoadFlag(a);
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    myMapper->writeCPU((0x0068 + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_001D8B() {
    myMapper->writeCPU(0x0007, a);
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x005E + x) & 0x00ff);
    setLoadFlag(a);
    if (a == 0xC2) {
    }
    else {
        if (a == 0xC1) {
            goto L_001DD7;
        }
        a = myMapper->readCPU(0x0007);
        setLoadFlag(a);
        if (a != 0x02) {
            if (a == 0x03) {
                goto L_001DB0;
            }
            a = 0x34;
            setLoadFlag(a);
        }
        else {
            a = 0x36;
            setLoadFlag(a);
            goto L_001DB2;
        L_001DB0:
            a = 0x38;
            setLoadFlag(a);
        }
    L_001DB2:
        pushAddress(0x001DB2);
        SUB_000853();
        if (poppedEntry.value != 0x001DB2) return;
        pushAddress(0x001DB5);
        SUB_002FD5();
        if (poppedEntry.value != 0x001DB5) return;
        myMapper->writeCPU(0x0004, x);
        a = myMapper->readCPU(0x0200 + x);
        setLoadFlag(a);
        pushAddress(0x001DBD);
        SUB_002112();
        if (poppedEntry.value != 0x001DBD) return;
        y = myMapper->readCPU(0x000A);
        setLoadFlag(y);
        if (y == 0x04) {
            goto L_001E73;
        }
        if (a != 0x00) {
            x = myMapper->readCPU(0x005D);
            setLoadFlag(x);
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU((0x008A + x) & 0x00ff, a);
            a = 0xC1;
            setLoadFlag(a);
            myMapper->writeCPU((0x005E + x) & 0x00ff, a);
        }
    L_001DD7:
        pushAddress(0x001DD7);
        SUB_002FD5();
        if (poppedEntry.value != 0x001DD7) return;
        myMapper->writeCPU(0x0004, x);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = myMapper->readCPU((0x005E + x) & 0x00ff);
        setLoadFlag(a);
        if (a == 0xC1) {
            a = 0x20;
            setLoadFlag(a);
            pushAddress(0x001DE6);
            SUB_001FE4();
            if (poppedEntry.value != 0x001DE6) return;
            if (flgZ) {
                x = myMapper->readCPU(0x0004);
                setLoadFlag(x);
                a = myMapper->readCPU(0x0200 + x);
                setLoadFlag(a);
                myMapper->writeCPU(0x0001, a);
                goto L_001E27;
            }
            x = myMapper->readCPU(0x005D);
            setLoadFlag(x);
            a = 0xC0;
            setLoadFlag(a);
            myMapper->writeCPU((0x005E + x) & 0x00ff, a);
            a = myMapper->readCPU(0x0007);
            setLoadFlag(a);
            if (a == 0x03) {
                a = myMapper->readCPU(0x0417 + x);
                setLoadFlag(a);
                if (!flgZ) {
                    a = 0x00;
                    setLoadFlag(a);
                }
                else {
                    a = 0x01;
                    setLoadFlag(a);
                }
                myMapper->writeCPU(0x0417 + x, a);
            }
            goto L_001E1A;
        }
        a = 0xFF;
        setLoadFlag(a);
        pushAddress(0x001E15);
        SUB_001FE4();
        if (poppedEntry.value != 0x001E15) return;
        if (flgZ) {
            goto L_001E85;
        }
    L_001E1A:
        x = myMapper->readCPU(0x0004);
        setLoadFlag(x);
        a = 0x01;
        setLoadFlag(a);
        flgC = false;
        opADC(myMapper->readCPU(0x0200 + x));
        myMapper->writeCPU(0x0001, a);
        pushAddress(0x001E24);
        SUB_001E86();
        if (poppedEntry.value != 0x001E24) return;
    L_001E27:
        opINX(3);
        a = myMapper->readCPU(0x0007);
        setLoadFlag(a);
        if (a == 0x02) {
            opINC(0x0200 + x, 1);
        }
        else {
            if (a != 0x03) {
                goto L_001E56;
            }
            a = myMapper->readCPU(0x0001);
            setLoadFlag(a);
            opAND(0x01);
            if (!flgZ) {
                y = myMapper->readCPU(0x005D);
                setLoadFlag(y);
                a = myMapper->readCPU(0x0417 + y);
                setLoadFlag(a);
                if (flgZ) {
                    opINC(0x0200 + x, 2);
                }
                else {
                    opDEC(0x0200 + x, 2);
                }
            }
        }
    L_001E56:
        a = myMapper->readCPU(0x0200 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = myMapper->readCPU((0x0072 + x) & 0x00ff);
        setLoadFlag(a);
        if (a != 0x90) {
            goto L_001E68;
        }
        a = 0x94;
        setLoadFlag(a);
        goto L_001E6A;
    L_001E68:
        a = 0x90;
        setLoadFlag(a);
    L_001E6A:
        myMapper->writeCPU(0x0002, a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        myMapper->writeCPU((0x0072 + x) & 0x00ff, a);
        SUB_002ADB();
        return;
    L_001E73:
        a = 0xC2;
        setLoadFlag(a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        myMapper->writeCPU((0x005E + x) & 0x00ff, a);
        x = myMapper->readCPU(0x0004);
        setLoadFlag(x);
        a = myMapper->readCPU(0x0203 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x042B, a);
        popAddress();
        return;
    }
    pushAddress(0x001E82);
    SUB_001EA5();
    if (poppedEntry.value != 0x001E82) return;
L_001E85:
    popAddress();
}

void game::SUB_001E86() {
    a = myMapper->readCPU(0x0007);
    setLoadFlag(a);
    if (a != 0x01) {
        goto L_001EA4;
    }
    y = 0x00;
    setLoadFlag(y);
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    do {
        if (a < myMapper->readCPU(0xC41D + y)) {
            goto L_001E9F;
        }
        if (a >= myMapper->readCPU(0xC420 + y)) {
            goto L_001E9F;
        }
        opINC(0x0001, 1);
        goto L_001EA4;
    L_001E9F:
        opINY(1);
    } while (y != 0x03);
L_001EA4:
    popAddress();
}

void game::SUB_001EA5() {
    pushAddress(0x001EA5);
    SUB_002FD5();
    if (poppedEntry.value != 0x001EA5) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x001EAA);
    SUB_002AEC();
    if (poppedEntry.value != 0x001EAA) return;
    opDEC(0x0000, 1);
    a = myMapper->readCPU(0x042B);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x01);
    if (a == myMapper->readCPU(0x0000)) {
        goto L_001EE8;
    }
    flgC = true;
    opSBC(0x01);
    if (a == myMapper->readCPU(0x0000)) {
        goto L_001EE8;
    }
    flgC = true;
    opSBC(0x01);
    if (a == myMapper->readCPU(0x0000)) {
        goto L_001EF2;
    }
    flgC = true;
    opSBC(0x08);
    if (a == myMapper->readCPU(0x0000)) {
        goto L_001EED;
    }
    flgC = true;
    opSBC(0x01);
    if (a == myMapper->readCPU(0x0000)) {
        goto L_001EED;
    }
    flgC = true;
    opSBC(0x01);
    if (a != myMapper->readCPU(0x0000)) {
        goto L_001EFB;
    }
    do {
        a = 0x01;
        setLoadFlag(a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        myMapper->writeCPU((0x005E + x) & 0x00ff, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0417 + x, a);
        popAddress();
        return;
    L_001EE8:
        opDEC(0x0001, 1);
        goto L_001EFB;
    L_001EED:
        opINC(0x0001, 1);
        goto L_001EFB;
    L_001EF2:
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        a = myMapper->readCPU(0x0421 + x);
        setLoadFlag(a);
    } while (a == 0x01);
L_001EFB:
    a = 0x84;
    setLoadFlag(a);
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    myMapper->writeCPU((0x0072 + x) & 0x00ff, a);
    myMapper->writeCPU(0x0002, a);
    pushAddress(0x001F03);
    SUB_002ADB();
    if (poppedEntry.value != 0x001F03) return;
    popAddress();
}

void game::SUB_001F07() {
    a = 0x55;
    setLoadFlag(a);
    pushAddress(0x001F09);
    SUB_001FE4();
    if (poppedEntry.value != 0x001F09) return;
    if (flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x001F0F);
    SUB_002FD5();
    if (poppedEntry.value != 0x001F0F) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x001F14);
    SUB_002AEC();
    if (poppedEntry.value != 0x001F14) return;
    opINC(0x0001, 1);
    a = myMapper->readCPU(0x0201 + x);
    setLoadFlag(a);
    if (a != 0x90) {
        a = 0x90;
        setLoadFlag(a);
    }
    else {
        a = 0x94;
        setLoadFlag(a);
    }
    myMapper->writeCPU(0x0002, a);
    pushAddress(0x001F29);
    SUB_002ADB();
    if (poppedEntry.value != 0x001F29) return;
    a = myMapper->readCPU(0x00C0);
    setLoadFlag(a);
    opCMP(a, myMapper->readCPU(0x0001));
    if (!flgZ) {
        if (!flgC) {
            goto L_001F35;
        }
        popAddress();
        return;
    }
L_001F35:
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU((0x005E + x) & 0x00ff, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00C0, a);
    popAddress();
}

void game::SUB_001F40() {
    a = myMapper->readCPU(0x00C0);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0096);
    setLoadFlag(a);
    if (a != 0x0A) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0059);
    setLoadFlag(a);
    if (a != 0x03) {
    }
    else {
        x = 0x03;
        setLoadFlag(x);
        a = myMapper->readCPU((0x007E + x) & 0x00ff);
        setLoadFlag(a);
        if (a < 0x05) {
            popAddress();
            return;
        }
        x = 0x00;
        setLoadFlag(x);
        do {
            a = myMapper->readCPU((0x005E + x) & 0x00ff);
            setLoadFlag(a);
            if (a != 0x01) {
                goto L_001F6C;
            }
            a = myMapper->readCPU((0x0068 + x) & 0x00ff);
            setLoadFlag(a);
            if (a == 0x03) {
                goto L_001F8F;
            }
        L_001F6C:
            opINX(1);
        } while (x != 0x0A);
        popAddress();
        return;
    }
    x = 0x05;
    setLoadFlag(x);
    a = myMapper->readCPU((0x007E + x) & 0x00ff);
    setLoadFlag(a);
    if (a >= 0x05) {
        goto L_001F7B;
    }
    popAddress();
    return;
L_001F7B:
    x = 0x00;
    setLoadFlag(x);
    do {
        a = myMapper->readCPU((0x005E + x) & 0x00ff);
        setLoadFlag(a);
        if (a != 0x01) {
            goto L_001F89;
        }
        a = myMapper->readCPU((0x0068 + x) & 0x00ff);
        setLoadFlag(a);
        if (a == 0x05) {
            goto L_001F8F;
        }
    L_001F89:
        opINX(1);
    } while (a != 0x0A);
    popAddress();
    return;
L_001F8F:
    a = 0x40;
    setLoadFlag(a);
    myMapper->writeCPU((0x005E + x) & 0x00ff, a);
    opDEC((0x0068 + x) & 0x00ff, 1);
    a = x;
    setLoadFlag(a);
    flgC = false;
    opADC(0x03);
    opASL_A(4);
    y = a;
    setLoadFlag(y);
    a = myMapper->readCPU(0x0200 + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x0203 + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0xC1EB);
    setLoadFlag(a);
    y = 0x00;
    setLoadFlag(y);
    while (a < myMapper->readCPU(0x0000)) {
        flgC = false;
        opADC(0x18);
        opINY(1);
    }
    a = y;
    setLoadFlag(a);
    opASL_A(1);
    flgC = false;
    opADC(0x15);
    flgC = false;
    opADC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x00C0, a);
    popAddress();
}

void game::SUB_001FC3() {
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x0068 + x) & 0x00ff);
    setLoadFlag(a);
    if (a == 0x01) {
        pushAddress(0x001FCB);
        SUB_002FD5();
        if (poppedEntry.value != 0x001FCB) return;
        a = myMapper->readCPU(0x0203 + x);
        setLoadFlag(a);
        if (a >= 0x30) {
            goto L_001FE3;
        }
        a = 0x23;
        setLoadFlag(a);
        myMapper->writeCPU(0x0202 + x, a);
        myMapper->writeCPU(0x0206 + x, a);
        myMapper->writeCPU(0x020A + x, a);
        myMapper->writeCPU(0x020E + x, a);
    }
L_001FE3:
    popAddress();
}

void game::SUB_001FE4() {
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x000B, a);
    SUB_001FE8();
    return;
}

void game::SUB_001FE8() {
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    opINC((0x008A + x) & 0x00ff, 1);
    a = myMapper->readCPU((0x008A + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgN) {
        if (a >= 0x10) {
            goto L_001FF7;
        }
        goto L_001FFB;
    }
L_001FF7:
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU((0x008A + x) & 0x00ff, a);
L_001FFB:
    if (a < 0x08) {
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0xC1BC + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x000A));
    }
    else {
        flgC = true;
        opSBC(0x08);
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0xC1BC + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x000B));
    }
    if (flgZ) {
        goto L_002015;
    }
    a = 0x01;
    setLoadFlag(a);
L_002015:
    popAddress();
}

void game::SUB_002016() {
    myMapper->writeCPU(0x000A, a);
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x01);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC493 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0xC494 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0009, a);
    y = 0x00;
    setLoadFlag(y);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x000B, a);
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (a == 0xFF) {
            goto L_002041;
        }
        opCMP(a, myMapper->readCPU(0x000A));
        if (flgZ) {
            goto L_002045;
        }
        if (!flgC) {
            goto L_002045;
        }
        opINC(0x000B, 1);
        opINY(1);
    }
L_002041:
    a = 0x07;
    setLoadFlag(a);
    myMapper->writeCPU(0x000B, a);
L_002045:
    a = myMapper->readCPU(0x000B);
    setLoadFlag(a);
    popAddress();
}

void game::SUB_002048() {
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x005E + x) & 0x00ff);
    setLoadFlag(a);
    if (a == 0x01) {
        a = myMapper->readCPU(0x007D);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_002057;
        }
        a = 0x01;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_002057:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00205A() {
    myMapper->writeCPU(0x000C, a);
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x0068 + x) & 0x00ff);
    setLoadFlag(a);
    if (a != 0x01) {
        if (a == 0x06) {
            goto L_002079;
        }
        x = 0x00;
        setLoadFlag(x);
        while (true) {
            a = myMapper->readCPU(0xC1C4 + x);
            setLoadFlag(a);
            if (a == myMapper->readCPU(0x000C)) {
                goto L_00208A;
            }
            opINX(1);
            if (x == 0x09) {
                goto L_00208D;
            }
        }
    }
L_002079:
    x = 0x04;
    setLoadFlag(x);
    while (true) {
        a = myMapper->readCPU(0xC1C4 + x);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0x000C)) {
            goto L_00208A;
        }
        opINX(1);
        if (x == 0x09) {
            goto L_00208D;
        }
    }
L_00208A:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
    return;
L_00208D:
    a = 0x01;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_002090() {
    myMapper->writeCPU(0x000C, a);
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x0068 + x) & 0x00ff);
    setLoadFlag(a);
    opAND(0x01);
    if (!flgZ) {
        x = 0x00;
        setLoadFlag(x);
    }
    else {
        x = 0x01;
        setLoadFlag(x);
    }
    a = myMapper->readCPU(0xC1CD + x);
    setLoadFlag(a);
    if (a == myMapper->readCPU(0x000C)) {
        goto L_0020AB;
    }
    a = 0x00;
    setLoadFlag(a);
    popAddress();
    return;
L_0020AB:
    a = 0x01;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0020AE() {
    myMapper->writeCPU(0x000C, a);
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x0068 + x) & 0x00ff);
    setLoadFlag(a);
    if (a != 0x02) {
        if (a == 0x03) {
            goto L_0020CB;
        }
        if (a == 0x04) {
            goto L_0020D1;
        }
        if (a == 0x05) {
            goto L_0020DD;
        }
        if (a == 0x06) {
            goto L_0020E9;
        }
        goto L_0020EC;
    }
L_0020CB:
    pushAddress(0x0020CB);
    SUB_0020F1();
    if (poppedEntry.value != 0x0020CB) return;
    goto L_0020EC;
L_0020D1:
    pushAddress(0x0020D1);
    SUB_0020F1();
    if (poppedEntry.value != 0x0020D1) return;
    y = 0x89;
    setLoadFlag(y);
    if (a == 0xC4) {
        SUB_002109();
        return;
    }
    goto L_0020EC;
L_0020DD:
    pushAddress(0x0020DD);
    SUB_0020F1();
    if (poppedEntry.value != 0x0020DD) return;
    y = 0x71;
    setLoadFlag(y);
    if (a == 0xB4) {
        SUB_002109();
        return;
    }
    goto L_0020EC;
L_0020E9:
    pushAddress(0x0020E9);
    SUB_0020F1();
    if (poppedEntry.value != 0x0020E9) return;
L_0020EC:
    a = 0x00;
    setLoadFlag(a);
    SUB_00210F();
    return;
}

void game::SUB_0020F1() {
    x = a;
    setLoadFlag(x);
    opDEX(2);
    a = myMapper->readCPU(0x000C);
    setLoadFlag(a);
    y = myMapper->readCPU(0xC172 + x);
    setLoadFlag(y);
    if (a != myMapper->readCPU(0xC177 + x)) {
        y = myMapper->readCPU(0xC17C + x);
        setLoadFlag(y);
        opCMP(a, myMapper->readCPU(0xC181 + x));
        if (flgZ) {
            goto L_002107;
        }
        popAddress();
        return;
    }
L_002107:
    opPLA();
    opPLA();
    SUB_002109();
    return;
}

void game::SUB_002109() {
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    myMapper->writeCPU((0x00A3 + x) & 0x00ff, y);
    a = 0x01;
    setLoadFlag(a);
    SUB_00210F();
    return;
}

void game::SUB_00210F() {
    myMapper->writeCPU(0x000C, a);
    popAddress();
}

void game::SUB_002112() {
    myMapper->writeCPU(0x000B, a);
    y = 0x00;
    setLoadFlag(y);
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (a == 0xFE) {
            goto L_002129;
        }
        if (a == myMapper->readCPU(0x000B)) {
            goto L_002124;
        }
        opINY(1);
    }
L_002124:
    a = 0x01;
    setLoadFlag(a);
    goto L_00212B;
L_002129:
    a = 0x00;
    setLoadFlag(a);
L_00212B:
    myMapper->writeCPU(0x000C, a);
    myMapper->writeCPU(0x000A, y);
    popAddress();
}

void game::SUB_002130() {
    x = myMapper->readCPU(0x005D);
    setLoadFlag(x);
    a = myMapper->readCPU((0x0068 + x) & 0x00ff);
    setLoadFlag(a);
    flgC = true;
    opSBC(myMapper->readCPU(0x0059));
    if (!flgZ) {
        if (flgN) {
            goto L_00213E;
        }
        goto L_002141;
    }
L_00213E:
    a = 0x01;
    setLoadFlag(a);
    popAddress();
    return;
L_002141:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_002166() {
    a = 0x00;
    setLoadFlag(a);
    y = 0x06;
    setLoadFlag(y);
    do {
        myMapper->writeCPU(0x007E + y, a);
        opDEY(1);
    } while (!flgN);
    y = 0x00;
    setLoadFlag(y);
    while (true) {
        a = myMapper->readCPU(0x0068 + y);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00217F;
        }
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU((0x007E + x) & 0x00ff);
        setLoadFlag(a);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU((0x007E + x) & 0x00ff, a);
    L_00217F:
        if (y == 0x09) {
            goto L_002187;
        }
        opINY(1);
    }
L_002187:
    x = myMapper->readCPU(0x0059);
    setLoadFlag(x);
    if (x != 0x07) {
        opINC((0x007E + x) & 0x00ff, 1);
        a = myMapper->readCPU(0x0096);
        setLoadFlag(a);
        if (a != 0x0A) {
            goto L_002199;
        }
        x = myMapper->readCPU(0x0059);
        setLoadFlag(x);
        opINC((0x007E + x) & 0x00ff, 1);
    }
L_002199:
    popAddress();
}

void game::SUB_00219A() {
    a = myMapper->readCPU(0x00AD);
    setLoadFlag(a);
    if (flgZ) {
        popAddress();
        return;
    }
    if (a == 0x01) {
        a = 0x20;
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        a = 0xC0;
        setLoadFlag(a);
        myMapper->writeCPU(0x0001, a);
        a = 0xFC;
        setLoadFlag(a);
        myMapper->writeCPU(0x0002, a);
        a = 0x12;
        setLoadFlag(a);
        myMapper->writeCPU(0x0003, a);
        a = 0xE0;
        setLoadFlag(a);
        pushAddress(0x0021B5);
        SUB_003080();
        if (poppedEntry.value != 0x0021B5) return;
        a = 0x02;
        setLoadFlag(a);
        myMapper->writeCPU(0x00AD, a);
    }
    else {
        a = myMapper->readCPU(0x0038);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0021E4;
        }
        a = 0x03;
        setLoadFlag(a);
        myMapper->writeCPU(0x00AD, a);
        x = 0xE1;
        setLoadFlag(x);
        a = myMapper->readCPU(0x0200 + x);
        setLoadFlag(a);
        if (a == 0xFC) {
            goto L_0021D5;
        }
        a = 0xFC;
        setLoadFlag(a);
        goto L_0021D7;
    L_0021D5:
        a = 0xFE;
        setLoadFlag(a);
    L_0021D7:
        myMapper->writeCPU(0x0200 + x, a);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0204 + x, a);
    }
    a = 0x10;
    setLoadFlag(a);
    myMapper->writeCPU(0x0038, a);
L_0021E4:
    popAddress();
}

void game::SUB_0021E5() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00AE, a);
    while (true) {
        pushAddress(0x0021E9);
        SUB_002FDD();
        if (poppedEntry.value != 0x0021E9) return;
        a = myMapper->readCPU(0x0200 + x);
        setLoadFlag(a);
        if (a == 0xFF) {
            a = myMapper->readCPU(0x0053);
            setLoadFlag(a);
            if (a == 0x01) {
                goto L_002200;
            }
            if (a == 0x04) {
                goto L_002213;
            }
            goto L_002225;
        L_002200:
            a = myMapper->readCPU(0x0040);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_002228;
            }
            a = myMapper->readCPU(0x00AD);
            setLoadFlag(a);
            if (flgZ) {
                goto L_002228;
            }
            if (a != 0x02) {
                goto L_002228;
            }
            a = 0x19;
            setLoadFlag(a);
            myMapper->writeCPU(0x0040, a);
            goto L_00221F;
        L_002213:
            a = myMapper->readCPU(0x0040);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_002228;
            }
            pushAddress(0x002217);
            SUB_002AF7();
            if (poppedEntry.value != 0x002217) return;
            a = myMapper->readCPU(0xC466 + x);
            setLoadFlag(a);
            myMapper->writeCPU(0x0040, a);
        L_00221F:
            a = 0x06;
            setLoadFlag(a);
            x = myMapper->readCPU(0x00AE);
            setLoadFlag(x);
            myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
        }
    L_002225:
        pushAddress(0x002225);
        SUB_002250();
        if (poppedEntry.value != 0x002225) return;
    L_002228:
        x = myMapper->readCPU(0x0053);
        setLoadFlag(x);
        opDEX(1);
        opINC(0x00AE, 1);
        a = myMapper->readCPU(0x00AE);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0xC1F6 + x)) {
            goto L_002237;
        }
    }
L_002237:
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a != 0x03) {
        a = myMapper->readCPU(0x003B);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_00224F;
        }
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x00D2, a);
        myMapper->writeCPU(0x00D3, a);
        myMapper->writeCPU(0x00D4, a);
        myMapper->writeCPU(0x00D5, a);
        a = 0xBC;
        setLoadFlag(a);
        myMapper->writeCPU(0x003B, a);
    }
L_00224F:
    popAddress();
}

void game::SUB_002250() {
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00AF + x) & 0x00ff);
    setLoadFlag(a);
L_002254:
    opAND(0x0F);
    if (!flgZ) {
        if (a == 0x06) {
            goto L_00228F;
        }
        if (a != 0x08) {
            if (a == 0x01) {
                goto L_002295;
            }
            if (a == 0x02) {
                goto L_00229A;
            }
            if (a == 0x03) {
                goto L_0022A1;
            }
            a = myMapper->readCPU(0x0053);
            setLoadFlag(a);
            if (a != 0x03) {
                pushAddress(0x002272);
                SUB_0022B6();
                if (poppedEntry.value != 0x002272) return;
            }
            else {
                a = myMapper->readCPU((0x0019 + x) & 0x00ff);
                setLoadFlag(a);
                opAND(0x03);
                x = myMapper->readCPU(0x00AE);
                setLoadFlag(x);
                myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
            }
            a = myMapper->readCPU((0x00AF + x) & 0x00ff);
            setLoadFlag(a);
            if (a == 0x01) {
                goto L_00228A;
            }
            if (a != 0x02) {
                goto L_00228C;
            }
        L_00228A:
            myMapper->writeCPU((0x00B3 + x) & 0x00ff, a);
        L_00228C:
            goto L_002254;
        }
    L_00228F:
        SUB_002538();
        return;
    }
    while (true) {
        SUB_0022F9();
        return;
    L_002295:
        a = 0x00;
        setLoadFlag(a);
        goto L_00229C;
    L_00229A:
        a = 0x01;
        setLoadFlag(a);
    L_00229C:
        myMapper->writeCPU(0x0099, a);
        SUB_002368();
        return;
    L_0022A1:
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a != 0x01) {
            goto L_0022B3;
        }
        pushAddress(0x0022A7);
        SUB_002626();
        if (poppedEntry.value != 0x0022A7) return;
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        a = myMapper->readCPU((0x00AF + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0022B3;
        }
    }
L_0022B3:
    SUB_00241B();
    return;
}

void game::SUB_0022B6() {
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00D2 + x) & 0x00ff);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU((0x00D2 + x) & 0x00ff, a);
        a = myMapper->readCPU(0x00AE);
        setLoadFlag(a);
        flgC = false;
        opADC(0x01);
        opASL_A(4);
        y = a;
        setLoadFlag(y);
        a = myMapper->readCPU(0x0203 + y);
        setLoadFlag(a);
        if (a < myMapper->readCPU(0x0203)) {
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU((0x00EC + x) & 0x00ff, a);
        }
        else {
            a = 0x02;
            setLoadFlag(a);
            myMapper->writeCPU((0x00EC + x) & 0x00ff, a);
        }
    }
    a = myMapper->readCPU((0x0019 + x) & 0x00ff);
    setLoadFlag(a);
    opAND(0x07);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    y = a;
    setLoadFlag(y);
    if (a < 0x04) {
    }
    else {
        y = myMapper->readCPU((0x00EC + x) & 0x00ff);
        setLoadFlag(y);
        if (a >= 0x07) {
            goto L_0022F4;
        }
        goto L_0022F6;
    L_0022F4:
        y = 0x03;
        setLoadFlag(y);
    }
L_0022F6:
    myMapper->writeCPU((0x00AF + x) & 0x00ff, y);
    popAddress();
}

void game::SUB_0022F9() {
    a = 0x55;
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x000B, a);
    pushAddress(0x0022FF);
    SUB_002806();
    if (poppedEntry.value != 0x0022FF) return;
    if (flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x002305);
    SUB_002FDD();
    if (poppedEntry.value != 0x002305) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x00230A);
    SUB_002AEC();
    if (poppedEntry.value != 0x00230A) return;
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00AF + x) & 0x00ff);
    setLoadFlag(a);
    if (a == 0x20) {
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
        popAddress();
        return;
    }
    if (a != 0x10) {
        opDEC(0x0001, 1);
    }
    else {
        opINC(0x0001, 1);
    }
    a = myMapper->readCPU(0x0004);
    setLoadFlag(a);
    y = a;
    setLoadFlag(y);
    opINY(1);
    a = myMapper->readCPU(0x0200 + y);
    setLoadFlag(a);
    x = myMapper->readCPU(0x0053);
    setLoadFlag(x);
    if (x != 0x04) {
        if (a == 0x9C) {
            goto L_00233B;
        }
        a = 0x9C;
        setLoadFlag(a);
        goto L_00234B;
    L_00233B:
        a = 0x98;
        setLoadFlag(a);
        goto L_00234B;
    }
    if (a != 0xAC) {
        a = 0xAC;
        setLoadFlag(a);
    }
    else {
        a = 0xA8;
        setLoadFlag(a);
    }
L_00234B:
    pushAddress(0x00234B);
    SUB_002AD4();
    if (poppedEntry.value != 0x00234B) return;
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00B3 + x) & 0x00ff);
    setLoadFlag(a);
    opLSR_A(1);
    pushAddress(0x002353);
    SUB_003096();
    if (poppedEntry.value != 0x002353) return;
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00AF + x) & 0x00ff);
    setLoadFlag(a);
    if (a == 0x10) {
        goto L_002363;
    }
    a = 0x10;
    setLoadFlag(a);
    goto L_002365;
L_002363:
    a = 0x20;
    setLoadFlag(a);
L_002365:
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_002368() {
    a = 0x55;
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x000B, a);
    pushAddress(0x00236E);
    SUB_002806();
    if (poppedEntry.value != 0x00236E) return;
    if (flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x002374);
    SUB_002FDD();
    if (poppedEntry.value != 0x002374) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x002379);
    SUB_002AEC();
    if (poppedEntry.value != 0x002379) return;
    a = myMapper->readCPU(0x0099);
    setLoadFlag(a);
    if (flgZ) {
        opINC(0x0000, 1);
    }
    else {
        opDEC(0x0000, 1);
    }
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    opAND(0x0F);
    if (a != 0x04) {
        if (a == 0x0C) {
            goto L_002396;
        }
        goto L_00239B;
    }
L_002396:
    opINC(0x0001, 1);
    goto L_0023AF;
L_00239B:
    x = myMapper->readCPU(0x0099);
    setLoadFlag(x);
    if (a != myMapper->readCPU(0xC3E2 + x)) {
        if (a == myMapper->readCPU(0xC3E4 + x)) {
            goto L_0023AA;
        }
        goto L_0023AF;
    }
L_0023AA:
    opDEC(0x0001, 1);
    goto L_0023C0;
L_0023AF:
    if (a != 0x04) {
        if (a == 0x0C) {
            goto L_0023BA;
        }
        goto L_0023C0;
    }
L_0023BA:
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = 0xFF;
    setLoadFlag(a);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
L_0023C0:
    y = myMapper->readCPU(0x0099);
    setLoadFlag(y);
    pushAddress(0x0023C2);
    SUB_0026A5();
    if (poppedEntry.value != 0x0023C2) return;
    if (flgZ) {
        a = 0x00;
        setLoadFlag(a);
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0099);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        opCMP(a, 0x0C);
        if (!flgZ) {
            if (!flgC) {
                goto L_0023E6;
            }
        }
        else {
            a = 0x00;
            setLoadFlag(a);
            x = myMapper->readCPU(0x00AE);
            setLoadFlag(x);
            myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
            goto L_0023ED;
        L_0023E6:
            a = 0x00;
            setLoadFlag(a);
            x = myMapper->readCPU(0x00AE);
            setLoadFlag(x);
            myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
            popAddress();
            return;
        }
    }
L_0023ED:
    a = myMapper->readCPU(0x0004);
    setLoadFlag(a);
    y = a;
    setLoadFlag(y);
    opINY(1);
    a = myMapper->readCPU(0x0200 + y);
    setLoadFlag(a);
    x = myMapper->readCPU(0x0053);
    setLoadFlag(x);
    if (x != 0x04) {
        if (a >= 0x9C) {
            goto L_002403;
        }
        a = 0x9C;
        setLoadFlag(a);
        goto L_002413;
    L_002403:
        a = 0x98;
        setLoadFlag(a);
        goto L_002413;
    }
    if (a >= 0xAC) {
        goto L_002411;
    }
    a = 0xAC;
    setLoadFlag(a);
    goto L_002413;
L_002411:
    a = 0xA8;
    setLoadFlag(a);
L_002413:
    pushAddress(0x002413);
    SUB_002AD4();
    if (poppedEntry.value != 0x002413) return;
    a = myMapper->readCPU(0x0099);
    setLoadFlag(a);
    SUB_003096();
    return;
}

void game::SUB_00241B() {
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00AF + x) & 0x00ff);
    setLoadFlag(a);
    opLSR_A(3);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a == 0x04) {
        goto L_002436;
    }
    do {
        a = myMapper->readCPU(0xC3F4 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x000A, a);
        a = myMapper->readCPU(0xC3F5 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x000B, a);
        goto L_00244B;
    L_002436:
        a = myMapper->readCPU(0x0050);
        setLoadFlag(a);
        opAND(0x01);
        flgC = false;
        opADC(myMapper->readCPU(0x0054));
    } while (a < 0x03);
    a = myMapper->readCPU(0xC3F8 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    a = myMapper->readCPU(0xC3F9 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x000B, a);
L_00244B:
    pushAddress(0x00244B);
    SUB_002806();
    if (poppedEntry.value != 0x00244B) return;
    if (flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x002451);
    SUB_002FDD();
    if (poppedEntry.value != 0x002451) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x002456);
    SUB_002AEC();
    if (poppedEntry.value != 0x002456) return;
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00E8 + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x03) {
            goto L_002466;
        }
        goto L_00246D;
    L_002466:
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU((0x00E8 + x) & 0x00ff, a);
    }
    else {
    L_00246D:
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        opAND(0x03);
        if (flgZ) {
            a = 0x01;
            setLoadFlag(a);
            opINC((0x00E8 + x) & 0x00ff, 1);
            goto L_00250C;
        }
    }
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a != 0x01) {
        pushAddress(0x002480);
        SUB_0027A3();
        if (poppedEntry.value != 0x002480) return;
        if (a != 0x03) {
            if (a == 0x13) {
                goto L_00249B;
            }
            goto L_00250C;
        }
        opDEC(0x0001, 1);
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        if (a != myMapper->readCPU((0x00DB + x) & 0x00ff)) {
            goto L_00250C;
        L_00249B:
            opINC(0x0001, 1);
            a = myMapper->readCPU(0x0001);
            setLoadFlag(a);
            x = myMapper->readCPU(0x00AE);
            setLoadFlag(x);
            if (a != myMapper->readCPU((0x00DB + x) & 0x00ff)) {
                goto L_00250C;
            }
        }
        a = 0x01;
        setLoadFlag(a);
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU((0x00DB + x) & 0x00ff, a);
        goto L_00250C;
    }
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00AF + x) & 0x00ff);
    setLoadFlag(a);
    if (a != 0x13) {
    }
    else {
        opINC(0x0001, 1);
        a = myMapper->readCPU(0x00AE);
        setLoadFlag(a);
        opASL_A(1);
        x = a;
        setLoadFlag(x);
        opINX(1);
        a = myMapper->readCPU((0x00B9 + x) & 0x00ff);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0x0001)) {
            a = 0x01;
            setLoadFlag(a);
            x = myMapper->readCPU(0x00AE);
            setLoadFlag(x);
            myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
        }
        goto L_00250C;
    }
    opDEC(0x0001, 1);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    if (x == 0x00) {
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        a = myMapper->readCPU((0x00E0 + x) & 0x00ff);
        setLoadFlag(a);
        if (a != 0x02) {
            a = myMapper->readCPU(0x00AE);
            setLoadFlag(a);
            opASL_A(1);
            x = a;
            setLoadFlag(x);
            a = myMapper->readCPU((0x00B9 + x) & 0x00ff);
            setLoadFlag(a);
            if (a != myMapper->readCPU(0x0001)) {
                goto L_00250C;
            }
            a = 0x02;
            setLoadFlag(a);
            x = myMapper->readCPU(0x00AE);
            setLoadFlag(x);
            myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
            goto L_00250C;
        }
    }
    a = myMapper->readCPU(0x00AE);
    setLoadFlag(a);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU((0x00B9 + x) & 0x00ff);
    setLoadFlag(a);
    flgC = false;
    opADC(0x0D);
    if (a == myMapper->readCPU(0x0001)) {
        a = 0x13;
        setLoadFlag(a);
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    }
L_00250C:
    a = myMapper->readCPU(0x0004);
    setLoadFlag(a);
    y = a;
    setLoadFlag(y);
    opINY(1);
    a = myMapper->readCPU(0x0200 + y);
    setLoadFlag(a);
    x = myMapper->readCPU(0x0053);
    setLoadFlag(x);
    if (x != 0x04) {
        if (a >= 0x9C) {
            goto L_002522;
        }
        a = 0x9C;
        setLoadFlag(a);
        goto L_002532;
    L_002522:
        a = 0x98;
        setLoadFlag(a);
        goto L_002532;
    }
    if (a >= 0xAC) {
        goto L_002530;
    }
    a = 0xAC;
    setLoadFlag(a);
    goto L_002532;
L_002530:
    a = 0xA8;
    setLoadFlag(a);
L_002532:
    pushAddress(0x002532);
    SUB_002AD4();
    if (poppedEntry.value != 0x002532) return;
    SUB_003088();
    return;
}

void game::SUB_002538() {
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00AF + x) & 0x00ff);
    setLoadFlag(a);
    if (a != 0x06) {
        if (a == 0x08) {
            goto L_002545;
        }
        popAddress();
        return;
    L_002545:
        goto L_00259F;
    }
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a != 0x01) {
        if (a == 0x04) {
            goto L_002564;
        }
        popAddress();
        return;
    }
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0xB8;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = 0x08;
    setLoadFlag(a);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    goto L_002592;
L_002564:
    a = myMapper->readCPU(0x0203);
    setLoadFlag(a);
    if (a >= 0x78) {
        y = 0x00;
        setLoadFlag(y);
    }
    else {
        y = 0x08;
        setLoadFlag(y);
    }
    myMapper->writeCPU(0x000C, y);
    a = myMapper->readCPU(0x0019);
    setLoadFlag(a);
    opAND(0x03);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x000C));
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC3CE + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0xC3CF + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    a = 0xA8;
    setLoadFlag(a);
    goto L_002594;
L_002592:
    a = 0x98;
    setLoadFlag(a);
L_002594:
    pushAddress(0x002594);
    SUB_002AD4();
    if (poppedEntry.value != 0x002594) return;
    pushAddress(0x002597);
    SUB_002FDD();
    if (poppedEntry.value != 0x002597) return;
    myMapper->writeCPU(0x0004, a);
    SUB_003082();
    return;
L_00259F:
    pushAddress(0x00259F);
    SUB_002FDD();
    if (poppedEntry.value != 0x00259F) return;
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x0025A4);
    SUB_002AEC();
    if (poppedEntry.value != 0x0025A4) return;
    a = myMapper->readCPU(0x0201 + x);
    setLoadFlag(a);
    pushAddress(0x0025AA);
    SUB_002AD4();
    if (poppedEntry.value != 0x0025AA) return;
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a != 0x01) {
        popAddress();
        return;
    }
    opINC(0x0000, 1);
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    opCMP(a, 0x2C);
    if (!flgZ) {
        if (!flgC) {
            goto L_0025E5;
        }
    }
    opINC(0x0001, 1);
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    if (a == 0xC5) {
        a = 0x00;
        setLoadFlag(a);
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
        opDEC(0x0000, 1);
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        if (a < 0x68) {
            opINC(0x0001, 1);
        }
        else {
            opDEC(0x0001, 1);
        }
        if (a != 0x60) {
            goto L_0025E5;
        }
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    }
L_0025E5:
    SUB_003082();
    return;
}

void game::SUB_0025E8() {
    myMapper->writeCPU(0x000C, a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00E0 + x) & 0x00ff);
    setLoadFlag(a);
    if (a != 0x01) {
        if (a == 0x06) {
            goto L_00260F;
        }
        x = 0x00;
        setLoadFlag(x);
        a = 0x18;
        setLoadFlag(a);
        while (a != myMapper->readCPU(0x000C)) {
            opINX(1);
            if (x == 0x09) {
                goto L_00260C;
            }
            a = myMapper->readCPU(0xC1C4 + x);
            setLoadFlag(a);
        }
        a = 0x00;
        setLoadFlag(a);
        popAddress();
        return;
    L_00260C:
        a = 0x01;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_00260F:
    x = 0x04;
    setLoadFlag(x);
    while (true) {
        a = myMapper->readCPU(0xC1C4 + x);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0x000C)) {
            goto L_002620;
        }
        opINX(1);
        if (x == 0x09) {
            goto L_002623;
        }
    }
L_002620:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
    return;
L_002623:
    a = 0x01;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_002626() {
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00AF + x) & 0x00ff);
    setLoadFlag(a);
    if (a == 0x13) {
        popAddress();
        return;
    }
    pushAddress(0x00262F);
    SUB_002FDD();
    if (poppedEntry.value != 0x00262F) return;
    pushAddress(0x002632);
    SUB_002AEC();
    if (poppedEntry.value != 0x002632) return;
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00E0 + x) & 0x00ff);
    setLoadFlag(a);
    if (a != 0x01) {
    }
    else {
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        if (a != 0x5C) {
            if (a == 0xC4) {
                goto L_00265D;
            }
            goto L_00269E;
        }
        a = myMapper->readCPU(0x00AE);
        setLoadFlag(a);
        opASL_A(1);
        x = a;
        setLoadFlag(x);
        a = 0xA6;
        setLoadFlag(a);
        myMapper->writeCPU((0x00B9 + x) & 0x00ff, a);
        opINX(1);
        a = 0xC7;
        setLoadFlag(a);
        myMapper->writeCPU((0x00B9 + x) & 0x00ff, a);
        goto L_002697;
    L_00265D:
        a = myMapper->readCPU(0x00AE);
        setLoadFlag(a);
        opASL_A(1);
        x = a;
        setLoadFlag(x);
        a = 0xAB;
        setLoadFlag(a);
        myMapper->writeCPU((0x00B9 + x) & 0x00ff, a);
        opINX(1);
        a = 0xC3;
        setLoadFlag(a);
        myMapper->writeCPU((0x00B9 + x) & 0x00ff, a);
        goto L_002697;
    }
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    if (a == 0x2C) {
        goto L_00267A;
    }
    if (a == 0x6C) {
        goto L_00268A;
    }
    goto L_00269E;
L_00267A:
    a = myMapper->readCPU(0x00AE);
    setLoadFlag(a);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = 0x8D;
    setLoadFlag(a);
    myMapper->writeCPU((0x00B9 + x) & 0x00ff, a);
    opINX(1);
    a = 0xA4;
    setLoadFlag(a);
    myMapper->writeCPU((0x00B9 + x) & 0x00ff, a);
    goto L_002697;
L_00268A:
    a = myMapper->readCPU(0x00AE);
    setLoadFlag(a);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = 0x8A;
    setLoadFlag(a);
    myMapper->writeCPU((0x00B9 + x) & 0x00ff, a);
    opINX(1);
    a = 0xA7;
    setLoadFlag(a);
    myMapper->writeCPU((0x00B9 + x) & 0x00ff, a);
L_002697:
    a = 0x03;
    setLoadFlag(a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    popAddress();
    return;
L_00269E:
    a = 0x00;
    setLoadFlag(a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_0026A5() {
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    flgC = false;
    opADC(0x0B);
    pushAddress(0x0026AA);
    SUB_002016();
    if (poppedEntry.value != 0x0026AA) return;
    y = myMapper->readCPU(0x0099);
    setLoadFlag(y);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    myMapper->writeCPU((0x00E0 + x) & 0x00ff, a);
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a == 0x01) {
    }
    else {
        if (a != 0x03) {
            goto L_0026C3;
        }
        goto L_002702;
    L_0026C3:
        goto L_00273C;
    }
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    pushAddress(0x0026C8);
    SUB_0025E8();
    if (poppedEntry.value != 0x0026C8) return;
    if (flgZ) {
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        a = myMapper->readCPU((0x00E0 + x) & 0x00ff);
        setLoadFlag(a);
        opAND(0x01);
        if (!flgZ) {
            a = myMapper->readCPU(0xC79A + y);
            setLoadFlag(a);
        }
        else {
            a = myMapper->readCPU(0xC79C + y);
            setLoadFlag(a);
        }
        flgC = false;
        opADC(myMapper->readCPU(0x0001));
        myMapper->writeCPU(0x0001, a);
    }
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00E0 + x) & 0x00ff);
    setLoadFlag(a);
    if (a != 0x01) {
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        opCMP(a, myMapper->readCPU(0xC3E6 + y));
        if (flgZ) {
            goto L_0026FB;
        }
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    opCMP(a, myMapper->readCPU(0xC3E8 + y));
    if (!flgZ) {
        popAddress();
        return;
    }
L_0026FB:
    a = 0x00;
    setLoadFlag(a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    popAddress();
    return;
L_002702:
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00E0 + x) & 0x00ff);
    setLoadFlag(a);
    if (a == 0x02) {
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0xC3EA + y)) {
            goto L_002735;
        }
        opCMP(a, myMapper->readCPU(0xC3EC + y));
        if (flgZ) {
            goto L_002735;
        }
    }
    else {
        if (y != 0x01) {
            goto L_002721;
        }
        if (a == 0x04) {
            goto L_00272E;
        }
    L_002721:
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0xC3EE + y)) {
            goto L_002735;
        }
        opCMP(a, myMapper->readCPU(0xC3F0 + y));
        if (flgZ) {
            goto L_002735;
        }
    }
    popAddress();
    return;
L_00272E:
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    opCMP(a, 0xDB);
    if (!flgZ) {
        popAddress();
        return;
    }
L_002735:
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    popAddress();
    return;
L_00273C:
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00E0 + x) & 0x00ff);
    setLoadFlag(a);
    y = a;
    setLoadFlag(y);
    opDEY(1);
    x = myMapper->readCPU(0x0099);
    setLoadFlag(x);
    a = myMapper->readCPU(0xC3F2 + x);
    setLoadFlag(a);
    while (y != 0x00) {
        if (x == 0x00) {
            goto L_002755;
        }
        flgC = false;
        opADC(0x08);
        goto L_002758;
    L_002755:
        flgC = true;
        opSBC(0x08);
    L_002758:
        opDEY(1);
    }
    if (a != myMapper->readCPU(0x0000)) {
        a = myMapper->readCPU(0x0099);
        setLoadFlag(a);
        opASL_A(1);
        pushAddress(0x002763);
        SUB_002770();
        if (poppedEntry.value != 0x002763) return;
        if (flgZ) {
            goto L_002769;
        }
        popAddress();
        return;
    }
L_002769:
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_002770() {
    myMapper->writeCPU(0x0009, a);
    pushAddress(0x002772);
    SUB_002FDD();
    if (poppedEntry.value != 0x002772) return;
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00E0 + x) & 0x00ff);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x02);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU((0x00C1 + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        y = myMapper->readCPU(0x0009);
        setLoadFlag(y);
        a = myMapper->readCPU(0xC3DE + y);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0x000A)) {
            goto L_00279D;
        }
    }
    a = myMapper->readCPU((0x00C2 + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        y = myMapper->readCPU(0x0009);
        setLoadFlag(y);
        a = myMapper->readCPU(0xC3DF + y);
        setLoadFlag(a);
        if (a != myMapper->readCPU(0x000A)) {
            goto L_0027A0;
        }
    L_00279D:
        a = 0x00;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_0027A0:
    a = 0x01;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0027A3() {
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    a = myMapper->readCPU((0x00DB + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        a = myMapper->readCPU((0x00AF + x) & 0x00ff);
        setLoadFlag(a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x02);
    opASL_A(1);
    y = a;
    setLoadFlag(y);
    a = myMapper->readCPU(0xC49B + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0xC49C + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0008, a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    y = myMapper->readCPU((0x00E0 + x) & 0x00ff);
    setLoadFlag(y);
    if (flgZ) {
        goto L_0027F2;
    }
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0009, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    flgC = true;
    opSBC(0x02);
    opASL_A(1);
    y = a;
    setLoadFlag(y);
    a = myMapper->readCPU(0xC4A1 + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0xC4A2 + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0008, a);
    y = myMapper->readCPU(0x0009);
    setLoadFlag(y);
    while (y != myMapper->readCPU(0x000A)) {
        a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0x0000)) {
            goto L_0027F9;
        }
        opINY(3);
    }
L_0027F2:
    a = 0x00;
    setLoadFlag(a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    popAddress();
    return;
L_0027F9:
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    myMapper->writeCPU((0x00DB + x) & 0x00ff, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_002806() {
    x = myMapper->readCPU(0x00AE);
    setLoadFlag(x);
    opINC((0x00E4 + x) & 0x00ff, 1);
    a = myMapper->readCPU((0x00E4 + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgN) {
        if (a >= 0x10) {
            goto L_002815;
        }
        goto L_002819;
    }
L_002815:
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU((0x00E4 + x) & 0x00ff, a);
L_002819:
    if (a < 0x08) {
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0xC1BC + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x000A));
    }
    else {
        flgC = true;
        opSBC(0x08);
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0xC1BC + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x000B));
    }
    if (flgZ) {
        goto L_002833;
    }
    a = 0x01;
    setLoadFlag(a);
L_002833:
    popAddress();
}

void game::SUB_002834() {
    pushAddress(0x002834);
    SUB_002AF7();
    if (poppedEntry.value != 0x002834) return;
    a = myMapper->readCPU(0xC45C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    a = myMapper->readCPU(0xC461 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x000B, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x005D, a);
    pushAddress(0x002845);
    SUB_001FE8();
    if (poppedEntry.value != 0x002845) return;
    if (flgZ) {
        popAddress();
        return;
    }
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00D2, a);
    while (true) {
        while (true) {
            while (true) {
                a = myMapper->readCPU(0x00D2);
                setLoadFlag(a);
                if (a >= 0x03) {
                    goto L_0028A9;
                }
                x = a;
                setLoadFlag(x);
                if (flgZ) {
                    a = myMapper->readCPU(0x00DA);
                    setLoadFlag(a);
                    if (a == 0x01) {
                        opDEC(0x0200, 1);
                        opDEC(0x0204, 1);
                        opDEC(0x0208, 1);
                        opDEC(0x020C, 1);
                    }
                }
                y = myMapper->readCPU(0xC2CC + x);
                setLoadFlag(y);
                a = myMapper->readCPU(0x0200 + y);
                setLoadFlag(a);
                if (a != 0xFF) {
                    a = y;
                    setLoadFlag(a);
                    x = a;
                    setLoadFlag(x);
                    opDEC(0x0200 + x, 1);
                    opDEC(0x0204 + x, 1);
                    a = myMapper->readCPU(0x0200 + x);
                    setLoadFlag(a);
                    if (a == 0x50) {
                        pushAddress(0x002883);
                        SUB_002968();
                        if (poppedEntry.value != 0x002883) return;
                    }
                    else {
                        if (a != 0xC8) {
                            goto L_002890;
                        }
                        pushAddress(0x00288D);
                        SUB_002971();
                        if (poppedEntry.value != 0x00288D) return;
                    }
                L_002890:
                    a = myMapper->readCPU(0x0200 + y);
                    setLoadFlag(a);
                    if (a != 0x70) {
                        goto L_00289B;
                    }
                    a = 0x01;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x00D8, a);
                L_00289B:
                    a = myMapper->readCPU(0x0200 + y);
                    setLoadFlag(a);
                    opCMP(a, 0x48);
                    if (flgZ) {
                        goto L_002901;
                    }
                    if (!flgC) {
                        goto L_002901;
                    }
                }
                opINC(0x00D2, 1);
            }
        L_0028A9:
            if (a == 0x06) {
                goto L_00290E;
            }
            x = a;
            setLoadFlag(x);
            if (a == 0x03) {
                a = myMapper->readCPU(0x00DA);
                setLoadFlag(a);
                if (a == 0x02) {
                    opINC(0x0200, 1);
                    opINC(0x0204, 1);
                    opINC(0x0208, 1);
                    opINC(0x020C, 1);
                }
            }
            y = myMapper->readCPU(0xC2CC + x);
            setLoadFlag(y);
            a = myMapper->readCPU(0x0200 + y);
            setLoadFlag(a);
            if (a != 0xFF) {
                a = y;
                setLoadFlag(a);
                x = a;
                setLoadFlag(x);
                opINC(0x0200 + x, 1);
                opINC(0x0204 + x, 1);
                a = myMapper->readCPU(0x0200 + x);
                setLoadFlag(a);
                if (a == 0x50) {
                    pushAddress(0x0028DD);
                    SUB_002971();
                    if (poppedEntry.value != 0x0028DD) return;
                }
                else {
                    if (a != 0xC8) {
                        goto L_0028EA;
                    }
                    pushAddress(0x0028E7);
                    SUB_002968();
                    if (poppedEntry.value != 0x0028E7) return;
                }
            L_0028EA:
                a = myMapper->readCPU(0x0200 + y);
                setLoadFlag(a);
                if (a != 0xA8) {
                    goto L_0028F8;
                }
                a = 0x01;
                setLoadFlag(a);
                myMapper->writeCPU(0x00D9, a);
                a = myMapper->readCPU(0x0200 + y);
                setLoadFlag(a);
            L_0028F8:
                if (a >= 0xD0) {
                    goto L_002901;
                }
            }
            opINC(0x00D2, 1);
        }
    L_002901:
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(0x0200 + y, a);
        myMapper->writeCPU(0x0204 + y, a);
        opINC(0x00D2, 1);
    }
L_00290E:
    a = myMapper->readCPU(0x00D8);
    setLoadFlag(a);
    if (a == 0x01) {
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x00D2, a);
        while (true) {
            a = myMapper->readCPU(0x00D2);
            setLoadFlag(a);
            if (a == 0x03) {
                goto L_002967;
            }
            x = a;
            setLoadFlag(x);
            y = myMapper->readCPU(0xC2CC + x);
            setLoadFlag(y);
            a = myMapper->readCPU(0x0200 + y);
            setLoadFlag(a);
            if (a == 0xFF) {
                goto L_00292E;
            }
            opINC(0x00D2, 1);
        }
    L_00292E:
        a = 0xD0;
        setLoadFlag(a);
        pushAddress(0x002930);
        SUB_00297A();
        if (poppedEntry.value != 0x002930) return;
        pushAddress(0x002933);
        SUB_002968();
        if (poppedEntry.value != 0x002933) return;
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x00D8, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x00D9);
    setLoadFlag(a);
    if (a != 0x01) {
        goto L_002967;
    }
    a = 0x03;
    setLoadFlag(a);
    myMapper->writeCPU(0x00D2, a);
    while (true) {
        a = myMapper->readCPU(0x00D2);
        setLoadFlag(a);
        if (a == 0x06) {
            goto L_002967;
        }
        x = a;
        setLoadFlag(x);
        y = myMapper->readCPU(0xC2CC + x);
        setLoadFlag(y);
        a = myMapper->readCPU(0x0200 + y);
        setLoadFlag(a);
        if (a == 0xFF) {
            goto L_00295B;
        }
        opINC(0x00D2, 1);
    }
L_00295B:
    a = 0x48;
    setLoadFlag(a);
    pushAddress(0x00295D);
    SUB_00297A();
    if (poppedEntry.value != 0x00295D) return;
    pushAddress(0x002960);
    SUB_002968();
    if (poppedEntry.value != 0x002960) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00D9, a);
L_002967:
    popAddress();
}

void game::SUB_002968() {
    a = 0x23;
    setLoadFlag(a);
    myMapper->writeCPU(0x0202 + y, a);
    myMapper->writeCPU(0x0206 + y, a);
    popAddress();
}

void game::SUB_002971() {
    a = 0x03;
    setLoadFlag(a);
    myMapper->writeCPU(0x0202 + y, a);
    myMapper->writeCPU(0x0206 + y, a);
    popAddress();
}

void game::SUB_00297A() {
    myMapper->writeCPU(0x0200 + y, a);
    myMapper->writeCPU(0x0204 + y, a);
    popAddress();
}

void game::SUB_002981() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0445, a);
    while (true) {
        a = myMapper->readCPU(0x0445);
        setLoadFlag(a);
        pushAddress(0x002989);
        SUB_002FD7();
        if (poppedEntry.value != 0x002989) return;
        a = x;
        setLoadFlag(a);
        flgC = false;
        opADC(0x30);
        x = a;
        setLoadFlag(x);
        myMapper->writeCPU(0x0004, x);
        pushAddress(0x002993);
        SUB_002AEC();
        if (poppedEntry.value != 0x002993) return;
        if (a != 0xFF) {
            x = myMapper->readCPU(0x0445);
            setLoadFlag(x);
            a = myMapper->readCPU(0x0446 + x);
            setLoadFlag(a);
            flgC = false;
            opADC(0xB0);
            if (a >= myMapper->readCPU(0x0000)) {
                a = myMapper->readCPU(0x0001);
                setLoadFlag(a);
                if (a >= 0x26) {
                    goto L_0029BE;
                }
                a = 0xC0;
                setLoadFlag(a);
                myMapper->writeCPU(0x0002, a);
            }
            else {
                pushAddress(0x0029B4);
                SUB_002A01();
                if (poppedEntry.value != 0x0029B4) return;
                if (a == 0xFF) {
                    goto L_0029F3;
                }
                goto L_0029EA;
            L_0029BE:
                a = 0xC4;
                setLoadFlag(a);
                myMapper->writeCPU(0x0002, a);
                a = myMapper->readCPU(0x0001);
                setLoadFlag(a);
                if (a < 0x2E) {
                    goto L_0029DA;
                }
                a = 0x02;
                setLoadFlag(a);
                myMapper->writeCPU(0x00FE, a);
                a = 0x2E;
                setLoadFlag(a);
                myMapper->writeCPU(0x0001, a);
                a = myMapper->readCPU(0x0445);
                setLoadFlag(a);
                opASL_A(1);
                x = a;
                setLoadFlag(x);
                a = 0x00;
                setLoadFlag(a);
                myMapper->writeCPU(0x042E + x, a);
            }
        L_0029DA:
            a = myMapper->readCPU(0x0000);
            setLoadFlag(a);
            flgC = false;
            opADC(0x02);
            myMapper->writeCPU(0x0000, a);
            a = myMapper->readCPU(0x0445);
            setLoadFlag(a);
            flgC = false;
            opADC(0x01);
            pushAddress(0x0029E7);
            SUB_002F72();
            if (poppedEntry.value != 0x0029E7) return;
        L_0029EA:
            pushAddress(0x0029EA);
            SUB_002ADB();
            if (poppedEntry.value != 0x0029EA) return;
        }
        else {
            pushAddress(0x0029F0);
            SUB_002A34();
            if (poppedEntry.value != 0x0029F0) return;
        }
    L_0029F3:
        opINC(0x0445, 1);
        a = myMapper->readCPU(0x0445);
        setLoadFlag(a);
        if (a == 0x03) {
            goto L_002A00;
        }
    }
L_002A00:
    popAddress();
}

void game::SUB_002A01() {
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    opINC(0x0001, 3);
    if (a == 0x26) {
        x = 0x01;
        setLoadFlag(x);
        myMapper->writeCPU(0x00FE, x);
    }
    if (a >= 0x50) {
        if (a < 0x90) {
            goto L_002A2F;
        }
        if (a < 0xC0) {
            goto L_002A2A;
        }
        if (a < 0xD8) {
            goto L_002A2F;
        }
        pushAddress(0x002A21);
        SUB_002AD1();
        if (poppedEntry.value != 0x002A21) return;
        pushAddress(0x002A24);
        SUB_003094();
        if (poppedEntry.value != 0x002A24) return;
        a = 0xFF;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_002A2A:
    a = 0xC4;
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    popAddress();
    return;
L_002A2F:
    a = 0xC0;
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    popAddress();
}

void game::SUB_002A34() {
    a = myMapper->readCPU(0x0036);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_002A5E;
    }
    a = myMapper->readCPU(0x0019);
    setLoadFlag(a);
    opAND(0x03);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC1FF + x);
    setLoadFlag(a);
    flgC = false;
    opADC(0x10);
    x = myMapper->readCPU(0x0445);
    setLoadFlag(x);
    myMapper->writeCPU(0x0446 + x, a);
    myMapper->writeCPU(0x0000, a);
    a = 0x30;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = 0xC4;
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    pushAddress(0x002A53);
    SUB_002ADB();
    if (poppedEntry.value != 0x002A53) return;
    pushAddress(0x002A56);
    SUB_002AF7();
    if (poppedEntry.value != 0x002A56) return;
    a = myMapper->readCPU(0xC457 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0036, a);
L_002A5E:
    popAddress();
}

void game::SUB_002A5F() {
    a = myMapper->readCPU(0x0039);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = 0x08;
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x000B, a);
    pushAddress(0x002A6C);
    SUB_002AA1();
    if (poppedEntry.value != 0x002A6C) return;
    if (flgZ) {
        popAddress();
        return;
    }
    a = 0x50;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x02F1);
    setLoadFlag(a);
    if (a != 0xDB) {
        opINC(0x00B7, 1);
        a = 0xDB;
        setLoadFlag(a);
    }
    else {
        a = 0xD7;
        setLoadFlag(a);
    }
    pushAddress(0x002A8A);
    SUB_002AD4();
    if (poppedEntry.value != 0x002A8A) return;
    a = 0xF0;
    setLoadFlag(a);
    pushAddress(0x002A8F);
    SUB_003080();
    if (poppedEntry.value != 0x002A8F) return;
    a = myMapper->readCPU(0x00B7);
    setLoadFlag(a);
    if (a != 0x04) {
        goto L_002AA0;
    }
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00B7, a);
    a = 0xBB;
    setLoadFlag(a);
    myMapper->writeCPU(0x0039, a);
L_002AA0:
    popAddress();
}

void game::SUB_002AA1() {
    opINC(0x00B8, 1);
    a = myMapper->readCPU(0x00B8);
    setLoadFlag(a);
    if (!flgN) {
        if (a >= 0x10) {
            goto L_002AAE;
        }
        goto L_002AB2;
    }
L_002AAE:
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00B8, a);
L_002AB2:
    if (a < 0x08) {
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0xC1BC + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x000A));
    }
    else {
        flgC = true;
        opSBC(0x08);
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0xC1BC + x);
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x000B));
    }
    if (flgZ) {
        goto L_002ACC;
    }
    a = 0x01;
    setLoadFlag(a);
L_002ACC:
    popAddress();
}

void game::SUB_002ACD() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0004, a);
    SUB_002AD1();
    return;
}

void game::SUB_002AD1() {
    SUB_002AD6();
    return;
}

void game::SUB_002AD4() {
    myMapper->writeCPU(0x0002, a);
    SUB_002AD6();
    return;
}

void game::SUB_002AD6() {
    a = 0x22;
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    popAddress();
}

void game::SUB_002ADB() {
    pushAddress(0x002ADB);
    SUB_002AD1();
    if (poppedEntry.value != 0x002ADB) return;
    SUB_003082();
    return;
}

void game::SUB_002AE1() {
    a = myMapper->readCPU(0x0203);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0200);
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    popAddress();
}

void game::SUB_002AEC() {
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0200 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    popAddress();
}

void game::SUB_002AF7() {
    a = myMapper->readCPU(0x0050);
    setLoadFlag(a);
    opAND(0x01);
    flgC = false;
    opADC(myMapper->readCPU(0x0054));
    x = a;
    setLoadFlag(x);
    if (x < 0x04) {
        goto L_002B05;
    }
    x = 0x04;
    setLoadFlag(x);
L_002B05:
    popAddress();
}

void game::SUB_002B06() {
    a = myMapper->readCPU(0x0503);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_002B0C;
    }
    popAddress();
    return;
L_002B0C:
    a = myMapper->readCPU(0x0505);
    setLoadFlag(a);
    opAND(0x0F);
    myMapper->writeCPU(0x0505, a);
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    x = a;
    setLoadFlag(x);
    y = a;
    setLoadFlag(y);
    opDEX(1);
    a = myMapper->readCPU(0xC608 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = y;
    setLoadFlag(a);
    if (a < 0x02) {
        goto L_002B54;
    }
    a = myMapper->readCPU(0x0044);
    setLoadFlag(a);
    if (flgZ) {
        goto L_002B4F;
    }
    while (true) {
        while (true) {
            if (a != 0x13) {
                goto L_002B32;
            }
            goto L_002B85;
        L_002B32:
            if (a == 0x0F) {
                SUB_002B8E();
                return;
            }
            if (a == 0x0B) {
                goto L_002B85;
            }
            if (a == 0x08) {
                SUB_002B8E();
                return;
            }
            if (a == 0x04) {
                pushAddress(0x002B4B);
                SUB_002BA6();
                if (poppedEntry.value != 0x002B4B) return;
            }
            popAddress();
            return;
        L_002B4F:
            a = 0x25;
            setLoadFlag(a);
            myMapper->writeCPU(0x0044, a);
            popAddress();
            return;
        L_002B54:
            a = myMapper->readCPU(0x0036);
            setLoadFlag(a);
            if (a == 0x18) {
                goto L_002B74;
            }
            if (a == 0x00) {
                goto L_002B7B;
            }
            a = myMapper->readCPU(0x0515);
            setLoadFlag(a);
            if (flgZ) {
                goto L_002B6F;
            }
            pushAddress(0x002B63);
            SUB_002BA1();
            if (poppedEntry.value != 0x002B63) return;
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x0515, a);
            a = 0x1A;
            setLoadFlag(a);
            myMapper->writeCPU(0x0044, a);
        L_002B6F:
            a = myMapper->readCPU(0x0044);
            setLoadFlag(a);
        }
    L_002B74:
        a = 0x30;
        setLoadFlag(a);
        myMapper->writeCPU(0x0044, a);
        SUB_002B9C();
        return;
    L_002B7B:
        a = 0x1A;
        setLoadFlag(a);
        myMapper->writeCPU(0x0044, a);
        pushAddress(0x002B7F);
        SUB_002B97();
        if (poppedEntry.value != 0x002B7F) return;
    }
L_002B85:
    a = 0x80;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FE, a);
    SUB_002B89();
    return;
}

void game::SUB_002B89() {
    a = 0x40;
    setLoadFlag(a);
    SUB_002BA8();
    return;
}

void game::SUB_002B8E() {
    a = 0x80;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FE, a);
    SUB_002B92();
    return;
}

void game::SUB_002B92() {
    a = 0x42;
    setLoadFlag(a);
    SUB_002BA8();
    return;
}

void game::SUB_002B97() {
    a = 0x44;
    setLoadFlag(a);
    SUB_002BA8();
    return;
}

void game::SUB_002B9C() {
    a = 0x3E;
    setLoadFlag(a);
    SUB_002BA8();
    return;
}

void game::SUB_002BA1() {
    a = 0x00;
    setLoadFlag(a);
    SUB_002BA8();
    return;
}

void game::SUB_002BA6() {
    a = 0x02;
    setLoadFlag(a);
    SUB_002BA8();
    return;
}

void game::SUB_002BA8() {
    pushAddress(0x002BA8);
    SUB_000815();
    if (poppedEntry.value != 0x002BA8) return;
    opDEC(0x0044, 1);
    a = myMapper->readCPU(0x0505);
    setLoadFlag(a);
    opORA(0x10);
    myMapper->writeCPU(0x0505, a);
    popAddress();
}

void game::SUB_002BB6() {
    a = myMapper->readCPU(0x0045);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x002E);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_002BC4;
    }
    a = 0xFF;
    setLoadFlag(a);
    myMapper->writeCPU(0x0096, a);
    popAddress();
    return;
L_002BC4:
    a = 0x0B;
    setLoadFlag(a);
    myMapper->writeCPU(0x0045, a);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x0A;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    pushAddress(0x002BD0);
    SUB_00333E();
    if (poppedEntry.value != 0x002BD0) return;
    a = 0x02;
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    SUB_00323C();
    return;
}

void game::SUB_002BDA() {
    a = myMapper->readCPU(0x050B);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x050B, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x050E, a);
        myMapper->writeCPU(0x050C, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x050C);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x050D);
        setLoadFlag(a);
        if (a == 0x05) {
            a = myMapper->readCPU(0x0096);
            setLoadFlag(a);
            if (a == 0x0A) {
                a = 0x00;
                setLoadFlag(a);
                if (flgZ) {
                    goto L_002C0A;
                }
            }
            a = 0x04;
            setLoadFlag(a);
            myMapper->writeCPU(0x0096, a);
            goto L_002C12;
        }
    L_002C0A:
        myMapper->writeCPU(0x0056, a);
        opAND(0x03);
        if (flgZ) {
            goto L_002C12;
        }
        myMapper->writeCPU(0x0057, a);
    L_002C12:
        opDEC(0x050C, 1);
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x050E);
    setLoadFlag(x);
    a = myMapper->readCPU(0xC028 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x050C, a);
    a = myMapper->readCPU(0xC014 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x050D, a);
    opINC(0x050E, 1);
    popAddress();
}

void game::SUB_002C29() {
    pushAddress(0x002C29);
    SUB_002AE1();
    if (poppedEntry.value != 0x002C29) return;
    a = 0x4C;
    setLoadFlag(a);
    pushAddress(0x002C2E);
    SUB_002FE8();
    if (poppedEntry.value != 0x002C2E) return;
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a == 0x03) {
        goto L_002C3B;
    }
    if (a != 0x01) {
        goto L_002C3E;
    }
L_002C3B:
    pushAddress(0x002C3B);
    SUB_002C44();
    if (poppedEntry.value != 0x002C3B) return;
L_002C3E:
    pushAddress(0x002C3E);
    SUB_002D8A();
    if (poppedEntry.value != 0x002C3E) return;
    SUB_002DC5();
    return;
}

void game::SUB_002C44() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x005D, a);
    while (true) {
        a = 0x3A;
        setLoadFlag(a);
        pushAddress(0x002C4A);
        SUB_000847();
        if (poppedEntry.value != 0x002C4A) return;
        pushAddress(0x002C4D);
        SUB_002FD5();
        if (poppedEntry.value != 0x002C4D) return;
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a != 0x01) {
            a = x;
            setLoadFlag(a);
            flgC = false;
            opADC(0x30);
            x = a;
            setLoadFlag(x);
        }
        pushAddress(0x002C5B);
        SUB_002AEC();
        if (poppedEntry.value != 0x002C5B) return;
        pushAddress(0x002C5E);
        SUB_002FEF();
        if (poppedEntry.value != 0x002C5E) return;
        if (!flgZ) {
            goto L_002CA7;
        }
        a = myMapper->readCPU(0x0096);
        setLoadFlag(a);
        if (a == 0x04) {
            a = myMapper->readCPU(0x0056);
            setLoadFlag(a);
            opAND(0x03);
            if (flgZ) {
                a = myMapper->readCPU(0x009C);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_002C80;
                }
            }
            else {
                a = myMapper->readCPU(0x009C);
                setLoadFlag(a);
                if (a < 0x03) {
                    a = myMapper->readCPU(0x009E);
                    setLoadFlag(a);
                    if (flgZ) {
                    L_002C80:
                        a = myMapper->readCPU(0x009D);
                        setLoadFlag(a);
                        if (a >= 0x18) {
                            goto L_002C97;
                        }
                        a = myMapper->readCPU(0x0000);
                        setLoadFlag(a);
                        myMapper->writeCPU(0x0005, a);
                        a = myMapper->readCPU(0x0001);
                        setLoadFlag(a);
                        myMapper->writeCPU(0x0006, a);
                        x = 0x00;
                        setLoadFlag(x);
                        pushAddress(0x002C90);
                        SUB_000FC6();
                        if (poppedEntry.value != 0x002C90) return;
                        a = 0x20;
                        setLoadFlag(a);
                        myMapper->writeCPU(0x00FD, a);
                    }
                }
            }
        }
    L_002C97:
        opINC(0x005D, 1);
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        opLSR_A(1);
        x = a;
        setLoadFlag(x);
        a = myMapper->readCPU(0x005D);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0xC1FD + x)) {
            goto L_002CAF;
        }
    }
L_002CA7:
    pushAddress(0x002CA7);
    SUB_002F51();
    if (poppedEntry.value != 0x002CA7) return;
    a = 0xFF;
    setLoadFlag(a);
    myMapper->writeCPU(0x0096, a);
    popAddress();
    return;
L_002CAF:
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a != 0x03) {
        a = myMapper->readCPU(0x0096);
        setLoadFlag(a);
        if (a != 0x0A) {
            goto L_002CBE;
        }
        SUB_002CBF();
        return;
    }
L_002CBE:
    popAddress();
}

void game::SUB_002CBF() {
    a = myMapper->readCPU(0x00A0);
    setLoadFlag(a);
    if (flgZ) {
    }
    else {
        a = myMapper->readCPU(0x009F);
        setLoadFlag(a);
        opLSR_A(2);
        if (!flgZ) {
            a = 0x00;
            setLoadFlag(a);
        }
        else {
            a = 0x01;
            setLoadFlag(a);
        }
        if (!flgZ) {
            a = 0x04;
            setLoadFlag(a);
            flgC = false;
            opADC(myMapper->readCPU(0x0203));
            myMapper->writeCPU(0x0000, a);
            a = myMapper->readCPU(0x0200);
            setLoadFlag(a);
            flgC = true;
            opSBC(0x10);
            myMapper->writeCPU(0x0001, a);
        }
        else {
            a = myMapper->readCPU(0x0057);
            setLoadFlag(a);
            if (a != 0x01) {
                a = myMapper->readCPU(0x0203);
                setLoadFlag(a);
                flgC = true;
                opSBC(0x10);
            }
            else {
                a = myMapper->readCPU(0x0203);
                setLoadFlag(a);
                flgC = false;
                opADC(0x10);
            }
            myMapper->writeCPU(0x0000, a);
            a = myMapper->readCPU(0x0200);
            setLoadFlag(a);
            flgC = false;
            opADC(0x06);
            myMapper->writeCPU(0x0001, a);
        }
        a = 0x3C;
        setLoadFlag(a);
        pushAddress(0x002D09);
        SUB_002FE8();
        if (poppedEntry.value != 0x002D09) return;
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a == 0x01) {
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x005D, a);
            while (true) {
                pushAddress(0x002D16);
                SUB_002FD5();
                if (poppedEntry.value != 0x002D16) return;
                pushAddress(0x002D19);
                SUB_002AEC();
                if (poppedEntry.value != 0x002D19) return;
                a = 0x3A;
                setLoadFlag(a);
                pushAddress(0x002D1E);
                SUB_000847();
                if (poppedEntry.value != 0x002D1E) return;
                pushAddress(0x002D21);
                SUB_002FEF();
                if (poppedEntry.value != 0x002D21) return;
                if (!flgZ) {
                    goto L_002D57;
                }
                a = myMapper->readCPU(0x005D);
                setLoadFlag(a);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x005D, a);
                if (a == 0x09) {
                    goto L_002D85;
                }
            }
        }
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x00AE, a);
        while (true) {
            pushAddress(0x002D38);
            SUB_002FDD();
            if (poppedEntry.value != 0x002D38) return;
            pushAddress(0x002D3B);
            SUB_002AEC();
            if (poppedEntry.value != 0x002D3B) return;
            a = 0x3A;
            setLoadFlag(a);
            pushAddress(0x002D40);
            SUB_000847();
            if (poppedEntry.value != 0x002D40) return;
            pushAddress(0x002D43);
            SUB_002FEF();
            if (poppedEntry.value != 0x002D43) return;
            if (!flgZ) {
                goto L_002D57;
            }
            opINC(0x00AE, 1);
            a = myMapper->readCPU(0x00AE);
            setLoadFlag(a);
            x = myMapper->readCPU(0x0053);
            setLoadFlag(x);
            opDEX(1);
            if (a == myMapper->readCPU(0xC1F6 + x)) {
                goto L_002D85;
            }
        }
    L_002D57:
        a = 0x02;
        setLoadFlag(a);
        myMapper->writeCPU(0x00FF, a);
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        myMapper->writeCPU(0x0005, a);
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        myMapper->writeCPU(0x0006, a);
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a != 0x01) {
            goto L_002D74;
        }
        a = 0x00;
        setLoadFlag(a);
        x = myMapper->readCPU(0x005D);
        setLoadFlag(x);
        myMapper->writeCPU((0x0068 + x) & 0x00ff, a);
        a = 0x01;
        setLoadFlag(a);
        goto L_002D87;
    L_002D74:
        a = 0x10;
        setLoadFlag(a);
        myMapper->writeCPU(0x0040, a);
        a = 0x00;
        setLoadFlag(a);
        x = myMapper->readCPU(0x00AE);
        setLoadFlag(x);
        myMapper->writeCPU((0x00E0 + x) & 0x00ff, a);
        myMapper->writeCPU((0x00DB + x) & 0x00ff, a);
        a = 0x01;
        setLoadFlag(a);
        goto L_002D87;
    L_002D85:
        a = 0x00;
        setLoadFlag(a);
    }
L_002D87:
    myMapper->writeCPU(0x00BF, a);
    popAddress();
}

void game::SUB_002D8A() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00AE, a);
    a = 0x3A;
    setLoadFlag(a);
    pushAddress(0x002D90);
    SUB_000847();
    if (poppedEntry.value != 0x002D90) return;
    while (true) {
        pushAddress(0x002D93);
        SUB_002FDD();
        if (poppedEntry.value != 0x002D93) return;
        pushAddress(0x002D96);
        SUB_002AEC();
        if (poppedEntry.value != 0x002D96) return;
        pushAddress(0x002D99);
        SUB_002FEF();
        if (poppedEntry.value != 0x002D99) return;
        if (!flgZ) {
            goto L_002DAD;
        }
        opINC(0x00AE, 1);
        a = myMapper->readCPU(0x00AE);
        setLoadFlag(a);
        x = myMapper->readCPU(0x0053);
        setLoadFlag(x);
        opDEX(1);
        if (a == myMapper->readCPU(0xC1F6 + x)) {
            goto L_002DB5;
        }
    }
L_002DAD:
    pushAddress(0x002DAD);
    SUB_002F51();
    if (poppedEntry.value != 0x002DAD) return;
    a = 0xFF;
    setLoadFlag(a);
    myMapper->writeCPU(0x0096, a);
    popAddress();
    return;
L_002DB5:
    a = myMapper->readCPU(0x0096);
    setLoadFlag(a);
    if (a == 0x0A) {
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a == 0x01) {
            goto L_002DC4;
        }
        pushAddress(0x002DC1);
        SUB_002CBF();
        if (poppedEntry.value != 0x002DC1) return;
    }
L_002DC4:
    popAddress();
}

void game::SUB_002DC5() {
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a == 0x03) {
        y = myMapper->readCPU(0x0096);
        setLoadFlag(y);
        if (y == 0x01) {
            goto L_002DD2;
        }
        popAddress();
        return;
    }
L_002DD2:
    flgC = true;
    opSBC(0x01);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0xC42B + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0002, a);
    a = myMapper->readCPU(0xC42C + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU(0xC423 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0xC424 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    while (true) {
        pushAddress(0x002DEB);
        SUB_002FEF();
        if (poppedEntry.value != 0x002DEB) return;
        if (!flgZ) {
            goto L_002E07;
        }
        a = myMapper->readCPU(0x0053);
        setLoadFlag(a);
        if (a != 0x03) {
            goto L_002E0B;
        }
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        if (a == 0xC9) {
            goto L_002E0B;
        }
        a = 0x70;
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        a = 0xC9;
        setLoadFlag(a);
        myMapper->writeCPU(0x0001, a);
    }
L_002E07:
    a = 0xFF;
    setLoadFlag(a);
    myMapper->writeCPU(0x0096, a);
L_002E0B:
    popAddress();
}

void game::SUB_002E0C() {
    a = 0x80;
    setLoadFlag(a);
    myMapper->writeCPU(0x000A, a);
    a = 0x80;
    setLoadFlag(a);
    myMapper->writeCPU(0x000B, a);
    pushAddress(0x002E14);
    SUB_001FE4();
    if (poppedEntry.value != 0x002E14) return;
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a == 0x01) {
        pushAddress(0x002E20);
        SUB_002FD5();
        if (poppedEntry.value != 0x002E20) return;
    }
    else {
        pushAddress(0x002E26);
        SUB_002FDD();
        if (poppedEntry.value != 0x002E26) return;
    }
    myMapper->writeCPU(0x0004, x);
    pushAddress(0x002E2B);
    SUB_002AEC();
    if (poppedEntry.value != 0x002E2B) return;
    a = myMapper->readCPU(0x00BF);
    setLoadFlag(a);
    if (a == 0x01) {
        y = 0x02;
        setLoadFlag(y);
        myMapper->writeCPU(0x00FF, y);
    }
    if (a != 0x0B) {
        x = myMapper->readCPU(0x00BF);
        setLoadFlag(x);
        opDEX(1);
        a = myMapper->readCPU(0xC1EC + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0002, a);
        pushAddress(0x002E44);
        SUB_002ADB();
        if (poppedEntry.value != 0x002E44) return;
        x = myMapper->readCPU(0x0004);
        setLoadFlag(x);
        a = 0x02;
        setLoadFlag(a);
        pushAddress(0x002E4B);
        SUB_002E6C();
        if (poppedEntry.value != 0x002E4B) return;
        opINC(0x00BF, 1);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0053);
    setLoadFlag(a);
    if (a != 0x01) {
        goto L_002E5C;
    }
    a = 0x03;
    setLoadFlag(a);
    pushAddress(0x002E59);
    SUB_002E6C();
    if (poppedEntry.value != 0x002E59) return;
L_002E5C:
    pushAddress(0x002E5C);
    SUB_002AD1();
    if (poppedEntry.value != 0x002E5C) return;
    pushAddress(0x002E5F);
    SUB_003094();
    if (poppedEntry.value != 0x002E5F) return;
    x = 0x02;
    setLoadFlag(x);
    pushAddress(0x002E64);
    SUB_000FC6();
    if (poppedEntry.value != 0x002E64) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00BF, a);
    popAddress();
}

void game::SUB_002E6C() {
    myMapper->writeCPU(0x0202 + x, a);
    myMapper->writeCPU(0x0206 + x, a);
    myMapper->writeCPU(0x020A + x, a);
    myMapper->writeCPU(0x020E + x, a);
    popAddress();
}

void game::SUB_002E79() {
    y = myMapper->readCPU(0x0053);
    setLoadFlag(y);
    if (y == 0x01) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x00BE);
    setLoadFlag(a);
    if (flgZ) {
        goto L_002ED8;
    }
    if (y != 0x04) {
        goto L_002EF0;
    }
    y = 0x00;
    setLoadFlag(y);
    x = myMapper->readCPU(0xC5FF);
    setLoadFlag(x);
    while (true) {
        a = myMapper->readCPU(0xC5C2 + x);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0x0203)) {
            a = myMapper->readCPU(0xC5AE + x);
            setLoadFlag(a);
            if (a >= myMapper->readCPU(0x0200)) {
                flgC = true;
                opSBC(0x11);
                if (a < myMapper->readCPU(0x0200)) {
                    a = myMapper->readCPU(0x00C1 + y);
                    setLoadFlag(a);
                    if (a == 0x00) {
                        a = myMapper->readCPU(0x0096);
                        setLoadFlag(a);
                        if (a != 0x08) {
                            if (a == 0xFF) {
                                goto L_002ED8;
                            }
                            a = 0x11;
                            setLoadFlag(a);
                            myMapper->writeCPU(0x00CC, a);
                            a = 0x01;
                            setLoadFlag(a);
                            myMapper->writeCPU(0x00C1 + y, a);
                            pushAddress(0x002EBF);
                            SUB_002F38();
                            if (poppedEntry.value != 0x002EBF) return;
                            a = myMapper->readCPU(0x0200);
                            setLoadFlag(a);
                            flgC = false;
                            opADC(0x10);
                            myMapper->writeCPU(0x0006, a);
                            a = myMapper->readCPU(0x0203);
                            setLoadFlag(a);
                            myMapper->writeCPU(0x0005, a);
                            x = 0x00;
                            setLoadFlag(x);
                            pushAddress(0x002ED1);
                            SUB_000FC6();
                            if (poppedEntry.value != 0x002ED1) return;
                            a = 0x20;
                            setLoadFlag(a);
                            myMapper->writeCPU(0x00FD, a);
                        }
                    L_002ED8:
                        popAddress();
                        return;
                    }
                    a = myMapper->readCPU(0x0096);
                    setLoadFlag(a);
                    if (a == 0x04) {
                        goto L_002EE6;
                    }
                    pushAddress(0x002EDF);
                    SUB_002F51();
                    if (poppedEntry.value != 0x002EDF) return;
                    a = 0x08;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x0096, a);
                L_002EE6:
                    popAddress();
                    return;
                }
            }
        }
        if (y == 0x07) {
            goto L_002EF0;
        }
        opINX(1);
        opINY(1);
    }
L_002EF0:
    y = myMapper->readCPU(0x0053);
    setLoadFlag(y);
    x = myMapper->readCPU(0xC5FA + y);
    setLoadFlag(x);
    y = 0x00;
    setLoadFlag(y);
    while (true) {
        a = myMapper->readCPU(0xC5AE + x);
        setLoadFlag(a);
        if (a == myMapper->readCPU(0x0200)) {
            a = myMapper->readCPU(0xC5C2 + x);
            setLoadFlag(a);
            if (a == myMapper->readCPU(0x0203)) {
                a = myMapper->readCPU(0x00C9 + y);
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_002F2F;
                }
                a = 0x22;
                setLoadFlag(a);
                myMapper->writeCPU(0x00CC, a);
                a = 0x01;
                setLoadFlag(a);
                myMapper->writeCPU(0x00C9 + y, a);
                pushAddress(0x002F15);
                SUB_002F38();
                if (poppedEntry.value != 0x002F15) return;
                a = myMapper->readCPU(0x0200);
                setLoadFlag(a);
                flgC = true;
                opSBC(0x08);
                myMapper->writeCPU(0x0006, a);
                a = myMapper->readCPU(0x0203);
                setLoadFlag(a);
                myMapper->writeCPU(0x0005, a);
                x = 0x03;
                setLoadFlag(x);
                pushAddress(0x002F27);
                SUB_000FC6();
                if (poppedEntry.value != 0x002F27) return;
                a = 0x20;
                setLoadFlag(a);
                myMapper->writeCPU(0x00FD, a);
            L_002F2E:
                popAddress();
                return;
            }
        }
    L_002F2F:
        if (y == 0x02) {
            goto L_002F2E;
        }
        opINX(1);
        opINY(1);
    }
    SUB_002F38();
    return;
}

void game::SUB_002F38() {
    a = 0x24;
    setLoadFlag(a);
    myMapper->writeCPU(0x00CD, a);
    myMapper->writeCPU(0x00CE, a);
    myMapper->writeCPU(0x00CF, a);
    myMapper->writeCPU(0x00D0, a);
    a = myMapper->readCPU(0xC5D6 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0xC5E9 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0000, a);
    a = 0x48;
    setLoadFlag(a);
    SUB_000815();
    return;
}

void game::SUB_002F51() {
    a = myMapper->readCPU(0x0096);
    setLoadFlag(a);
    if (a == 0x0A) {
        a = myMapper->readCPU(0x00A0);
        setLoadFlag(a);
        if (flgZ) {
            goto L_002F71;
        }
        flgC = true;
        opSBC(0x01);
        x = a;
        setLoadFlag(x);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0451 + x, a);
        a = x;
        setLoadFlag(a);
        opASL_A(3);
        x = a;
        setLoadFlag(x);
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(0x02D0 + x, a);
        myMapper->writeCPU(0x02D4 + x, a);
    }
L_002F71:
    popAddress();
}

void game::SUB_002F72() {
    myMapper->writeCPU(0x000F, x);
    opASL_A(1);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0x042C + x);
    setLoadFlag(a);
    if (flgZ) {
        myMapper->writeCPU(0x0436 + x, a);
        if (x == 0x00) {
            a = 0x08;
            setLoadFlag(a);
        }
        else {
            a = 0x80;
            setLoadFlag(a);
        }
        myMapper->writeCPU(0x0435 + x, a);
        a = 0xF0;
        setLoadFlag(a);
        myMapper->writeCPU(0x042D + x, a);
    }
    else {
        a = myMapper->readCPU(0x0435 + x);
        setLoadFlag(a);
        opCMP(x, 0x00);
        if (!flgZ) {
            goto L_002FA0;
        }
        opADC(0x10);
        goto L_002FA2;
    L_002FA0:
        opADC(0x30);
    L_002FA2:
        myMapper->writeCPU(0x0435 + x, a);
        a = myMapper->readCPU(0x0436 + x);
        setLoadFlag(a);
        opADC(0x00);
        myMapper->writeCPU(0x0436 + x, a);
    }
    a = myMapper->readCPU(0x042D + x);
    setLoadFlag(a);
    flgC = true;
    opSBC(myMapper->readCPU(0x043D + x));
    myMapper->writeCPU(0x042D + x, a);
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    opSBC(myMapper->readCPU(0x043E + x));
    myMapper->writeCPU(0x0001, a);
    flgC = false;
    a = myMapper->readCPU(0x042D + x);
    setLoadFlag(a);
    opADC(myMapper->readCPU(0x0435 + x));
    myMapper->writeCPU(0x042D + x, a);
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    opADC(myMapper->readCPU(0x0436 + x));
    myMapper->writeCPU(0x0001, a);
    opINC(0x042C + x, 1);
    x = myMapper->readCPU(0x000F);
    setLoadFlag(x);
    popAddress();
}

void game::SUB_002FD5() {
    a = myMapper->readCPU(0x005D);
    setLoadFlag(a);
    SUB_002FD7();
    return;
}

void game::SUB_002FD7() {
    flgC = false;
    opADC(0x03);
    SUB_002FE2();
    return;
}

void game::SUB_002FDD() {
    a = myMapper->readCPU(0x00AE);
    setLoadFlag(a);
    flgC = false;
    opADC(0x01);
    SUB_002FE2();
    return;
}

void game::SUB_002FE2() {
    opASL_A(4);
    x = a;
    setLoadFlag(x);
    popAddress();
}

void game::SUB_002FE8() {
    pushAddress(0x002FE8);
    SUB_000847();
    if (poppedEntry.value != 0x002FE8) return;
    SUB_002FEB();
    return;
}

void game::SUB_002FEB() {
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_002FF5();
        return;
    }
    SUB_002FEF();
    return;
}

void game::SUB_002FEF() {
    a = 0x01;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_002FF5();
        return;
    }
    SUB_002FF3();
    return;
}

void game::SUB_002FF3() {
    a = 0x02;
    setLoadFlag(a);
    SUB_002FF5();
    return;
}

void game::SUB_002FF5() {
    myMapper->writeCPU(0x000C, a);
    a = x;
    setLoadFlag(a);
    mStack.push({ false, a });
    a = y;
    setLoadFlag(a);
    mStack.push({ false, a });
    y = 0x00;
    setLoadFlag(y);
    a = myMapper->readCPU(0x000C);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x003001);
        SUB_003063();
        if (poppedEntry.value != 0x003001) return;
        myMapper->writeCPU(0x0046, a);
        pushAddress(0x003006);
        SUB_003069();
        if (poppedEntry.value != 0x003006) return;
        myMapper->writeCPU(0x0047, a);
        pushAddress(0x00300B);
        SUB_003062();
        if (poppedEntry.value != 0x00300B) return;
        myMapper->writeCPU(0x0048, a);
        pushAddress(0x003010);
        SUB_003069();
        if (poppedEntry.value != 0x003010) return;
        myMapper->writeCPU(0x0049, a);
    }
    else {
        pushAddress(0x003018);
        SUB_003063();
        if (poppedEntry.value != 0x003018) return;
        myMapper->writeCPU(0x004A, a);
        pushAddress(0x00301D);
        SUB_003069();
        if (poppedEntry.value != 0x00301D) return;
        myMapper->writeCPU(0x004B, a);
        pushAddress(0x003022);
        SUB_003062();
        if (poppedEntry.value != 0x003022) return;
        myMapper->writeCPU(0x004C, a);
        pushAddress(0x003027);
        SUB_003069();
        if (poppedEntry.value != 0x003027) return;
        myMapper->writeCPU(0x004D, a);
        a = myMapper->readCPU(0x004A);
        setLoadFlag(a);
        flgC = true;
        opSBC(myMapper->readCPU(0x0046));
        myMapper->writeCPU(0x009C, a);
        a = myMapper->readCPU(0x004B);
        setLoadFlag(a);
        flgC = true;
        opSBC(myMapper->readCPU(0x0047));
        myMapper->writeCPU(0x009D, a);
        a = myMapper->readCPU(0x0049);
        setLoadFlag(a);
        if (a >= myMapper->readCPU(0x004B)) {
            a = myMapper->readCPU(0x004D);
            setLoadFlag(a);
            if (a >= myMapper->readCPU(0x0047)) {
                a = myMapper->readCPU(0x004C);
                setLoadFlag(a);
                if (a >= myMapper->readCPU(0x0046)) {
                    a = myMapper->readCPU(0x0048);
                    setLoadFlag(a);
                    if (a < myMapper->readCPU(0x004A)) {
                        goto L_003057;
                    }
                    a = 0x01;
                    setLoadFlag(a);
                    goto L_003059;
                }
            }
        }
    L_003057:
        a = 0x00;
        setLoadFlag(a);
    }
L_003059:
    myMapper->writeCPU(0x000C, a);
    opPLA();
    y = a;
    setLoadFlag(y);
    opPLA();
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0x000C);
    setLoadFlag(a);
    popAddress();
}

void game::SUB_003062() {
    opINY(1);
    SUB_003063();
    return;
}

void game::SUB_003063() {
    a = myMapper->readCPU(myMapper->readCPU(0x0002) + (myMapper->readCPU((0x0002 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    flgC = false;
    opADC(myMapper->readCPU(0x0000));
    popAddress();
}

void game::SUB_003069() {
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0002) + (myMapper->readCPU((0x0002 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    flgC = false;
    opADC(myMapper->readCPU(0x0001));
    popAddress();
}

void game::SUB_003070() {
    myMapper->writeCPU(0x0002, a);
    pushAddress(0x003072);
    SUB_002AE1();
    if (poppedEntry.value != 0x003072) return;
    SUB_003075();
    return;
}

void game::SUB_003075() {
    pushAddress(0x003075);
    SUB_002ACD();
    if (poppedEntry.value != 0x003075) return;
    SUB_003078();
    return;
}

void game::SUB_003078() {
    a = myMapper->readCPU(0x0057);
    setLoadFlag(a);
    opAND(0x03);
    opLSR_A(1);
    SUB_003096();
    return;
}

void game::SUB_003080() {
    myMapper->writeCPU(0x0004, a);
    SUB_003082();
    return;
}

void game::SUB_003082() {
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_003096();
        return;
    }
    SUB_003086();
    return;
}

void game::SUB_003086() {
    myMapper->writeCPU(0x0004, a);
    SUB_003088();
    return;
}

void game::SUB_003088() {
    a = 0x01;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003096();
        return;
    }
    SUB_00308C();
    return;
}

void game::SUB_00308C() {
    myMapper->writeCPU(0x0004, a);
    SUB_00308E();
    return;
}

void game::SUB_00308E() {
    a = 0x04;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003096();
        return;
    }
    SUB_003092();
    return;
}

void game::SUB_003092() {
    myMapper->writeCPU(0x0003, a);
    SUB_003094();
    return;
}

void game::SUB_003094() {
    a = 0x0F;
    setLoadFlag(a);
    SUB_003096();
    return;
}

void game::SUB_003096() {
    mStack.push({ false, a });
    myMapper->writeCPU(0x000F, a);
    a = x;
    setLoadFlag(a);
    mStack.push({ false, a });
    a = y;
    setLoadFlag(a);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0005);
    setLoadFlag(a);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0006);
    setLoadFlag(a);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0007);
    setLoadFlag(a);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0008);
    setLoadFlag(a);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0009);
    setLoadFlag(a);
    mStack.push({ false, a });
    a = 0x02;
    setLoadFlag(a);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x000F);
    setLoadFlag(a);
    if (a != 0x04) {
        a = 0x0F;
        setLoadFlag(a);
        opAND(myMapper->readCPU(0x0003));
        myMapper->writeCPU(0x0007, a);
        a = myMapper->readCPU(0x0003);
        setLoadFlag(a);
        opLSR_A(4);
        myMapper->writeCPU(0x0006, a);
        x = a;
        setLoadFlag(x);
        a = 0x00;
        setLoadFlag(a);
        flgC = false;
        do {
            opADC(myMapper->readCPU(0x0007));
            opDEX(1);
        } while (!flgZ);
        myMapper->writeCPU(0x0008, a);
        a = myMapper->readCPU(0x000F);
        setLoadFlag(a);
        if (flgZ) {
            pushAddress(0x0030D6);
            SUB_00311E();
            if (poppedEntry.value != 0x0030D6) return;
        }
        else {
            if (a == 0x01) {
                goto L_0030E6;
            }
            pushAddress(0x0030E0);
            SUB_003195();
            if (poppedEntry.value != 0x0030E0) return;
            goto L_0030F2;
        L_0030E6:
            pushAddress(0x0030E6);
            SUB_003161();
            if (poppedEntry.value != 0x0030E6) return;
        }
        pushAddress(0x0030E9);
        SUB_003139();
        if (poppedEntry.value != 0x0030E9) return;
        goto L_0030F2;
    }
    pushAddress(0x0030EF);
    SUB_00310A();
    if (poppedEntry.value != 0x0030EF) return;
L_0030F2:
    opPLA();
    myMapper->writeCPU(0x0009, a);
    opPLA();
    myMapper->writeCPU(0x0008, a);
    opPLA();
    myMapper->writeCPU(0x0007, a);
    opPLA();
    myMapper->writeCPU(0x0006, a);
    opPLA();
    myMapper->writeCPU(0x0005, a);
    opPLA();
    myMapper->writeCPU(0x0000, a);
    opPLA();
    y = a;
    setLoadFlag(y);
    opPLA();
    x = a;
    setLoadFlag(x);
    opPLA();
    popAddress();
}

void game::SUB_00310A() {
    x = myMapper->readCPU(0x0003);
    setLoadFlag(x);
    y = 0x00;
    setLoadFlag(y);
    do {
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
        opINY(2);
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
        opINY(2);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00311E() {
    a = myMapper->readCPU(0x0002);
    setLoadFlag(a);
    x = myMapper->readCPU(0x0008);
    setLoadFlag(x);
    y = 0x01;
    setLoadFlag(y);
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
        flgC = false;
        opADC(0x01);
        opINY(1);
        mStack.push({ false, a });
        a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        opAND(0x3F);
        myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
        opPLA();
        opINY(3);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_003139() {
    y = 0x00;
    setLoadFlag(y);
    do {
        x = myMapper->readCPU(0x0006);
        setLoadFlag(x);
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        myMapper->writeCPU(0x0009, a);
        do {
            a = myMapper->readCPU(0x0009);
            setLoadFlag(a);
            myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x0009, a);
            opINY(3);
            a = myMapper->readCPU(0x0000);
            setLoadFlag(a);
            myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            opDEX(1);
        } while (!flgZ);
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0000, a);
        opDEC(0x0007, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_003161() {
    y = 0x01;
    setLoadFlag(y);
    myMapper->writeCPU(0x000A, y);
    a = myMapper->readCPU(0x0008);
    setLoadFlag(a);
    flgC = true;
    opSBC(myMapper->readCPU(0x0006));
    do {
        y = a;
        setLoadFlag(y);
        myMapper->writeCPU(0x000B, a);
        x = myMapper->readCPU(0x0006);
        setLoadFlag(x);
        do {
            a = y;
            setLoadFlag(a);
            mStack.push({ false, a });
            flgC = false;
            a = y;
            setLoadFlag(a);
            opADC(myMapper->readCPU(0x0002));
            y = myMapper->readCPU(0x000A);
            setLoadFlag(y);
            myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            opAND(0x3F);
            opEOR(0x40);
            myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
            opINY(3);
            myMapper->writeCPU(0x000A, y);
            opPLA();
            y = a;
            setLoadFlag(y);
            opINY(1);
            opDEX(1);
        } while (!flgZ);
        a = myMapper->readCPU(0x000B);
        setLoadFlag(a);
        flgC = true;
        opSBC(myMapper->readCPU(0x0006));
    } while (!flgN);
    popAddress();
}

void game::SUB_003195() {
    y = 0x00;
    setLoadFlag(y);
    do {
        x = myMapper->readCPU(0x0006);
        setLoadFlag(x);
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        myMapper->writeCPU(0x0009, a);
        a = 0xFF;
        setLoadFlag(a);
        do {
            myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
            opINY(4);
            opDEX(1);
        } while (!flgZ);
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0000, a);
        opDEC(0x0007, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0031B4() {
    a = myMapper->readCPU(0x2002);
    setLoadFlag(a);
    a = myMapper->readCPU(0x0010);
    setLoadFlag(a);
    opAND(0xFB);
    myMapper->writeCPU(0x2000, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x2006, a);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x2006, a);
    x = 0x04;
    setLoadFlag(x);
    y = 0x00;
    setLoadFlag(y);
    a = 0x24;
    setLoadFlag(a);
    do {
        do {
            myMapper->writeCPU(0x2007, a);
            opDEY(1);
        } while (!flgZ);
        opDEX(1);
    } while (!flgZ);
    a = 0x23;
    setLoadFlag(a);
    myMapper->writeCPU(0x2006, a);
    a = 0xC0;
    setLoadFlag(a);
    myMapper->writeCPU(0x2006, a);
    y = 0x40;
    setLoadFlag(y);
    a = 0x00;
    setLoadFlag(a);
    do {
        myMapper->writeCPU(0x2007, a);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0031EC() {
    myMapper->writeCPU(0x2006, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x2006, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    opASL_A(1);
    mStack.push({ false, a });
    a = myMapper->readCPU(0x0010);
    setLoadFlag(a);
    opORA(0x04);
    if (!flgC) {
        opAND(0xFB);
    }
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0010, a);
    opPLA();
    opASL_A(1);
    if (!flgC) {
        goto L_00320E;
    }
    opORA(0x02);
    opINY(1);
L_00320E:
    opLSR_A(2);
    x = a;
    setLoadFlag(x);
    do {
        if (flgC) {
            goto L_003214;
        }
        opINY(1);
    L_003214:
        a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    flgC = true;
    a = y;
    setLoadFlag(a);
    opADC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0000, a);
    a = 0x00;
    setLoadFlag(a);
    opADC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x0001, a);
    SUB_003228();
    return;
}

void game::SUB_003228() {
    x = myMapper->readCPU(0x2002);
    setLoadFlag(x);
    y = 0x00;
    setLoadFlag(y);
    a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_0031EC();
        return;
    }
    a = myMapper->readCPU(0x0012);
    setLoadFlag(a);
    myMapper->writeCPU(0x2005, a);
    a = myMapper->readCPU(0x0013);
    setLoadFlag(a);
    myMapper->writeCPU(0x2005, a);
    popAddress();
}

void game::SUB_00323C() {
    flgD = false;
    a = 0x04;
    setLoadFlag(a);
    do {
        opLSR_M(0x0000, 1);
        if (!flgC) {
            goto L_003248;
        }
        mStack.push({ false, a });
        pushAddress(0x003244);
        SUB_00324E();
        if (poppedEntry.value != 0x003244) return;
        opPLA();
    L_003248:
        flgC = false;
        opSBC(0x00);
    } while (!flgN);
    popAddress();
}

void game::SUB_00324E() {
    opASL_A(2);
    y = a;
    setLoadFlag(y);
    myMapper->writeCPU(0x0001, a);
    x = myMapper->readCPU(0x0330);
    setLoadFlag(x);
    a = myMapper->readCPU(0xC000 + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    pushAddress(0x00325C);
    SUB_00332D();
    if (poppedEntry.value != 0x00325C) return;
    opINY(1);
    a = myMapper->readCPU(0xC000 + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    pushAddress(0x003266);
    SUB_00332D();
    if (poppedEntry.value != 0x003266) return;
    opINY(1);
    a = myMapper->readCPU(0xC000 + y);
    setLoadFlag(a);
    opAND(0x87);
    myMapper->writeCPU(0x0331 + x, a);
    opAND(0x07);
    myMapper->writeCPU(0x0002, a);
    a = x;
    setLoadFlag(a);
    flgC = true;
    opADC(myMapper->readCPU(0x0002));
    pushAddress(0x00327A);
    SUB_00332F();
    if (poppedEntry.value != 0x00327A) return;
    x = a;
    setLoadFlag(x);
    myMapper->writeCPU(0x0330, x);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    opINY(1);
    a = myMapper->readCPU(0xC000 + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    opDEX(1);
    flgC = false;
    do {
        a = myMapper->readCPU(0x0020 + y);
        setLoadFlag(a);
        opAND(0x0F);
        if (!flgZ) {
            flgC = false;
        }
        if (flgC) {
            a = 0x24;
            setLoadFlag(a);
        }
        myMapper->writeCPU(0x0331 + x, a);
        opDEX(1);
        opDEC(0x0002, 1);
        if (flgZ) {
            goto L_0032C4;
        }
        a = myMapper->readCPU(0x0020 + y);
        setLoadFlag(a);
        opAND(0xF0);
        pushStatus();
        opLSR_A(4);
        popStatus();
        if (!flgZ) {
            flgC = false;
        }
        if (flgC) {
            a = 0x24;
            setLoadFlag(a);
        }
        myMapper->writeCPU(0x0331 + x, a);
        a = myMapper->readCPU(0x0003);
        setLoadFlag(a);
        opAND(0x01);
        if (flgZ) {
            goto L_0032BE;
        }
        flgC = true;
    L_0032BE:
        opDEY(1);
        opDEX(1);
        opDEC(0x0002, 1);
    } while (!flgZ);
L_0032C4:
    a = myMapper->readCPU(0x0003);
    setLoadFlag(a);
    opAND(0x10);
    if (flgZ) {
        goto L_0032D6;
    }
    opINX(1);
    y = myMapper->readCPU(0x0001);
    setLoadFlag(y);
    flgC = false;
    a = myMapper->readCPU(0x0020 + y);
    setLoadFlag(a);
    opADC(0x37);
    myMapper->writeCPU(0x0331 + x, a);
L_0032D6:
    popAddress();
}

void game::SUB_0032D7() {
    y = 0x00;
    setLoadFlag(y);
    a = myMapper->readCPU(myMapper->readCPU(0x0002) + (myMapper->readCPU((0x0002 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    opAND(0x0F);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(myMapper->readCPU(0x0002) + (myMapper->readCPU((0x0002 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    opLSR_A(4);
    myMapper->writeCPU(0x0004, a);
    x = myMapper->readCPU(0x0330);
    setLoadFlag(x);
    do {
        a = myMapper->readCPU(0x0001);
        setLoadFlag(a);
        myMapper->writeCPU(0x0331 + x, a);
        pushAddress(0x0032EF);
        SUB_00332D();
        if (poppedEntry.value != 0x0032EF) return;
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        myMapper->writeCPU(0x0331 + x, a);
        pushAddress(0x0032F7);
        SUB_00332D();
        if (poppedEntry.value != 0x0032F7) return;
        a = myMapper->readCPU(0x0004);
        setLoadFlag(a);
        myMapper->writeCPU(0x0006, a);
        opORA(0x80);
        myMapper->writeCPU(0x0331 + x, a);
        do {
            pushAddress(0x003303);
            SUB_00332D();
            if (poppedEntry.value != 0x003303) return;
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x0002) + (myMapper->readCPU((0x0002 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            myMapper->writeCPU(0x0331 + x, a);
            opDEC(0x0006, 1);
        } while (!flgZ);
        pushAddress(0x003310);
        SUB_00332D();
        if (poppedEntry.value != 0x003310) return;
        flgC = false;
        a = 0x01;
        setLoadFlag(a);
        opADC(myMapper->readCPU(0x0000));
        myMapper->writeCPU(0x0000, a);
        a = 0x00;
        setLoadFlag(a);
        opADC(myMapper->readCPU(0x0001));
        myMapper->writeCPU(0x0001, a);
        myMapper->writeCPU(0x0330, x);
        opDEC(0x0005, 1);
    } while (!flgZ);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    popAddress();
}

void game::SUB_00332D() {
    opINX(1);
    a = x;
    setLoadFlag(a);
    SUB_00332F();
    return;
}

void game::SUB_00332F() {
    if (a < 0x3F) {
        goto L_00333D;
    }
    x = myMapper->readCPU(0x0330);
    setLoadFlag(x);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    opPLA();
    opPLA();
L_00333D:
    popAddress();
}

void game::SUB_00333E() {
    x = 0xFF;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_003344();
        return;
    }
    SUB_003342();
    return;
}

void game::SUB_003342() {
    x = 0x00;
    setLoadFlag(x);
    SUB_003344();
    return;
}

void game::SUB_003344() {
    myMapper->writeCPU(0x0004, x);
    x = 0x00;
    setLoadFlag(x);
    myMapper->writeCPU(0x0005, x);
    myMapper->writeCPU(0x0006, x);
    myMapper->writeCPU(0x0007, x);
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    opAND(0x08);
    if (flgZ) {
        opINX(1);
    }
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    myMapper->writeCPU((0x0006 + x) & 0x00ff, a);
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    goto L_00335E;
L_00335E:
    opAND(0x07);
    opASL_A(2);
    x = a;
    setLoadFlag(x);
    a = myMapper->readCPU(0x0004);
    setLoadFlag(a);
    if (flgZ) {
        goto L_00338E;
    }
    a = myMapper->readCPU((0x0024 + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        do {
            flgC = false;
            a = myMapper->readCPU((0x0027 + x) & 0x00ff);
            setLoadFlag(a);
            myMapper->writeCPU(0x0003, a);
            a = myMapper->readCPU(0x0007);
            setLoadFlag(a);
            pushAddress(0x003372);
            SUB_0033E3();
            if (poppedEntry.value != 0x003372) return;
            myMapper->writeCPU((0x0027 + x) & 0x00ff, a);
            a = myMapper->readCPU((0x0026 + x) & 0x00ff);
            setLoadFlag(a);
            myMapper->writeCPU(0x0003, a);
            a = myMapper->readCPU(0x0006);
            setLoadFlag(a);
            pushAddress(0x00337D);
            SUB_0033E3();
            if (poppedEntry.value != 0x00337D) return;
            myMapper->writeCPU((0x0026 + x) & 0x00ff, a);
            a = myMapper->readCPU((0x0025 + x) & 0x00ff);
            setLoadFlag(a);
            myMapper->writeCPU(0x0003, a);
            a = myMapper->readCPU(0x0005);
            setLoadFlag(a);
            pushAddress(0x003388);
            SUB_0033E3();
            if (poppedEntry.value != 0x003388) return;
            myMapper->writeCPU((0x0025 + x) & 0x00ff, a);
            popAddress();
            return;
        L_00338E:
            a = myMapper->readCPU((0x0024 + x) & 0x00ff);
            setLoadFlag(a);
        } while (flgZ);
    }
    flgC = true;
    a = myMapper->readCPU((0x0027 + x) & 0x00ff);
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU(0x0007);
    setLoadFlag(a);
    pushAddress(0x003399);
    SUB_003404();
    if (poppedEntry.value != 0x003399) return;
    myMapper->writeCPU((0x0027 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0026 + x) & 0x00ff);
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU(0x0006);
    setLoadFlag(a);
    pushAddress(0x0033A4);
    SUB_003404();
    if (poppedEntry.value != 0x0033A4) return;
    myMapper->writeCPU((0x0026 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0025 + x) & 0x00ff);
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU(0x0005);
    setLoadFlag(a);
    pushAddress(0x0033AF);
    SUB_003404();
    if (poppedEntry.value != 0x0033AF) return;
    myMapper->writeCPU((0x0025 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0025 + x) & 0x00ff);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU((0x0026 + x) & 0x00ff);
        setLoadFlag(a);
        if (flgZ) {
            a = myMapper->readCPU((0x0027 + x) & 0x00ff);
            setLoadFlag(a);
            if (flgZ) {
                goto L_0033C6;
            }
        }
    }
    if (flgC) {
        goto L_0033E2;
    }
    a = myMapper->readCPU((0x0024 + x) & 0x00ff);
    setLoadFlag(a);
    opEOR(0xFF);
L_0033C6:
    myMapper->writeCPU((0x0024 + x) & 0x00ff, a);
    flgC = true;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU((0x0027 + x) & 0x00ff);
    setLoadFlag(a);
    pushAddress(0x0033CF);
    SUB_003404();
    if (poppedEntry.value != 0x0033CF) return;
    myMapper->writeCPU((0x0027 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0026 + x) & 0x00ff);
    setLoadFlag(a);
    pushAddress(0x0033D6);
    SUB_003404();
    if (poppedEntry.value != 0x0033D6) return;
    myMapper->writeCPU((0x0026 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0025 + x) & 0x00ff);
    setLoadFlag(a);
    pushAddress(0x0033DD);
    SUB_003404();
    if (poppedEntry.value != 0x0033DD) return;
    myMapper->writeCPU((0x0025 + x) & 0x00ff, a);
L_0033E2:
    popAddress();
}

void game::SUB_0033E3() {
    pushAddress(0x0033E3);
    SUB_003426();
    if (poppedEntry.value != 0x0033E3) return;
    opADC(myMapper->readCPU(0x0001));
    opCMP(a, 0x0A);
    if (!flgC) {
        goto L_0033EE;
    }
    opADC(0x05);
L_0033EE:
    flgC = false;
    opADC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0002, a);
    a = myMapper->readCPU(0x0003);
    setLoadFlag(a);
    opAND(0xF0);
    opADC(myMapper->readCPU(0x0002));
    if (!flgC) {
        goto L_0033FF;
    }
    do {
        opADC(0x5F);
        flgC = true;
        popAddress();
        return;
    L_0033FF:
        opCMP(a, 0xA0);
    } while (flgC);
    popAddress();
}

void game::SUB_003404() {
    pushAddress(0x003404);
    SUB_003426();
    if (poppedEntry.value != 0x003404) return;
    opSBC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x0001, a);
    if (!flgC) {
        opADC(0x0A);
        myMapper->writeCPU(0x0001, a);
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        opADC(0x0F);
        myMapper->writeCPU(0x0002, a);
    }
    a = myMapper->readCPU(0x0003);
    setLoadFlag(a);
    opAND(0xF0);
    flgC = true;
    opSBC(myMapper->readCPU(0x0002));
    if (flgC) {
        goto L_003423;
    }
    opADC(0xA0);
    flgC = false;
L_003423:
    opORA(myMapper->readCPU(0x0001));
    popAddress();
}

void game::SUB_003426() {
    mStack.push({ false, a });
    opAND(0x0F);
    myMapper->writeCPU(0x0001, a);
    opPLA();
    opAND(0xF0);
    myMapper->writeCPU(0x0002, a);
    a = myMapper->readCPU(0x0003);
    setLoadFlag(a);
    opAND(0x0F);
    popAddress();
}

void game::SUB_003435() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0004, a);
    flgC = false;
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    opADC(0x10);
    opAND(0xF0);
    opLSR_A(2);
    y = a;
    setLoadFlag(y);
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    opAND(0x07);
    opASL_A(2);
    x = a;
    setLoadFlag(x);
    do {
        a = myMapper->readCPU(0x0020 + y);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0034A0;
        }
        a = myMapper->readCPU((0x0024 + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgZ) {
        L_003453:
            flgC = true;
            a = myMapper->readCPU(0x0023 + y);
            setLoadFlag(a);
            myMapper->writeCPU(0x0003, a);
            a = myMapper->readCPU((0x0027 + x) & 0x00ff);
            setLoadFlag(a);
            pushAddress(0x00345B);
            SUB_003404();
            if (poppedEntry.value != 0x00345B) return;
            a = myMapper->readCPU(0x0022 + y);
            setLoadFlag(a);
            myMapper->writeCPU(0x0003, a);
            a = myMapper->readCPU((0x0026 + x) & 0x00ff);
            setLoadFlag(a);
            pushAddress(0x003465);
            SUB_003404();
            if (poppedEntry.value != 0x003465) return;
            a = myMapper->readCPU(0x0021 + y);
            setLoadFlag(a);
            myMapper->writeCPU(0x0003, a);
            a = myMapper->readCPU((0x0025 + x) & 0x00ff);
            setLoadFlag(a);
            pushAddress(0x00346F);
            SUB_003404();
            if (poppedEntry.value != 0x00346F) return;
            if (flgC) {
                goto L_0034A4;
            }
            a = myMapper->readCPU(0x0020 + y);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0034A9;
            }
        }
    L_003479:
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(0x0004, a);
        flgC = true;
    L_00347E:
        a = y;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_00349F;
        }
        if (!flgC) {
            goto L_003493;
        }
        a = myMapper->readCPU((0x0024 + x) & 0x00ff);
        setLoadFlag(a);
        myMapper->writeCPU(0x0020, a);
        a = myMapper->readCPU((0x0025 + x) & 0x00ff);
        setLoadFlag(a);
        myMapper->writeCPU(0x0021, a);
        a = myMapper->readCPU((0x0026 + x) & 0x00ff);
        setLoadFlag(a);
        myMapper->writeCPU(0x0022, a);
        a = myMapper->readCPU((0x0027 + x) & 0x00ff);
        setLoadFlag(a);
        myMapper->writeCPU(0x0023, a);
    L_003493:
        a = myMapper->readCPU(0x0000);
        setLoadFlag(a);
        opAND(0x08);
        if (flgZ) {
            goto L_00349F;
        }
        opDEX(4);
    } while (!flgN);
L_00349F:
    popAddress();
    return;
L_0034A0:
    a = myMapper->readCPU((0x0024 + x) & 0x00ff);
    setLoadFlag(a);
    if (flgZ) {
        goto L_003453;
    }
L_0034A4:
    a = myMapper->readCPU(0x0020 + y);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_003479;
    }
L_0034A9:
    flgC = false;
    if (!flgC) {
        goto L_00347E;
    }
    SUB_0034AC();
    return;
}

void game::SUB_0034AC() {
    x = 0x09;
    setLoadFlag(x);
    opDEC(0x0034, 1);
    if (!flgN) {
        goto L_0034B8;
    }
    a = 0x0A;
    setLoadFlag(a);
    myMapper->writeCPU(0x0034, a);
    x = 0x10;
    setLoadFlag(x);
    do {
    L_0034B8:
        a = myMapper->readCPU((0x0035 + x) & 0x00ff);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0034BE;
        }
        opDEC((0x0035 + x) & 0x00ff, 1);
    L_0034BE:
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0034C2() {
    x = myMapper->readCPU(0x0330);
    setLoadFlag(x);
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    pushAddress(0x0034CA);
    SUB_00332D();
    if (poppedEntry.value != 0x0034CA) return;
    a = myMapper->readCPU(0x0000);
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    pushAddress(0x0034D2);
    SUB_00332D();
    if (poppedEntry.value != 0x0034D2) return;
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    pushAddress(0x0034DA);
    SUB_00332D();
    if (poppedEntry.value != 0x0034DA) return;
    a = y;
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    pushAddress(0x0034E1);
    SUB_00332D();
    if (poppedEntry.value != 0x0034E1) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0331 + x, a);
    myMapper->writeCPU(0x0330, x);
    popAddress();
}

void game::SUB_0034ED() {
    a = myMapper->readCPU(0x0018);
    setLoadFlag(a);
    opAND(0x02);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0019);
    setLoadFlag(a);
    opAND(0x02);
    opEOR(myMapper->readCPU(0x0000));
    flgC = false;
    if (flgZ) {
        goto L_0034FD;
    }
    flgC = true;
L_0034FD:
    opROR_M(0x0018, 1);
    opROR_M(0x0019, 1);
    opROR_M(0x001A, 1);
    opROR_M(0x001B, 1);
    opROR_M(0x001C, 1);
    opROR_M(0x001D, 1);
    opROR_M(0x001E, 1);
    opROR_M(0x001F, 1);
    popAddress();
}

void game::SUB_00350E() {
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x4016, a);
    x = 0x00;
    setLoadFlag(x);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x4016, a);
    pushAddress(0x00351A);
    SUB_003522();
    if (poppedEntry.value != 0x00351A) return;
    opINX(1);
    pushAddress(0x00351E);
    SUB_003522();
    if (poppedEntry.value != 0x00351E) return;
    popAddress();
}

void game::SUB_003522() {
    y = 0x08;
    setLoadFlag(y);
    do {
        mStack.push({ false, a });
        a = myMapper->readCPU(0x4016 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0000, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0000));
        opLSR_A(1);
        opPLA();
        opROL_A(1);
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0000, x);
    opASL_M(0x0000, 1);
    x = myMapper->readCPU(0x0000);
    setLoadFlag(x);
    y = myMapper->readCPU((0x0014 + x) & 0x00ff);
    setLoadFlag(y);
    myMapper->writeCPU(0x0000, y);
    myMapper->writeCPU((0x0014 + x) & 0x00ff, a);
    opAND(0xFF);
    if (flgN) {
        opBIT(myMapper->readCPU(0x0000));
        if (flgN) {
            opAND(0x7F);
        }
    }
    y = myMapper->readCPU((0x0015 + x) & 0x00ff);
    setLoadFlag(y);
    myMapper->writeCPU((0x0015 + x) & 0x00ff, a);
    a = y;
    setLoadFlag(a);
    opAND(0x0F);
    opAND(myMapper->readCPU((0x0015 + x) & 0x00ff));
    if (flgZ) {
        goto L_00355A;
    }
    opORA(0xF0);
    opAND(myMapper->readCPU((0x0015 + x) & 0x00ff));
    myMapper->writeCPU((0x0015 + x) & 0x00ff, a);
L_00355A:
    popAddress();
}

void game::SUB_003A48() {
    a = 0xC0;
    setLoadFlag(a);
    myMapper->writeCPU(0x4017, a);
    pushAddress(0x003A4D);
    SUB_003BF2();
    if (poppedEntry.value != 0x003A4D) return;
    x = 0x00;
    setLoadFlag(x);
    myMapper->writeCPU(0x00FF, x);
    myMapper->writeCPU(0x00FE, x);
    myMapper->writeCPU(0x00FD, x);
    a = myMapper->readCPU(0x06F0);
    setLoadFlag(a);
    if (a < 0x90) {
        x = 0x00;
        setLoadFlag(x);
        myMapper->writeCPU(0x06F1, x);
    }
    if (a >= 0xD8) {
        opINC(0x06F1, 1);
    }
    y = a;
    setLoadFlag(y);
    opLSR_A(6);
    myMapper->writeCPU(0x0000, a);
    a = y;
    setLoadFlag(a);
    x = myMapper->readCPU(0x06F1);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_003A7F;
    }
    flgC = true;
    opADC(myMapper->readCPU(0x0000));
    if (!flgZ) {
        goto L_003A82;
    }
L_003A7F:
    flgC = false;
    opSBC(myMapper->readCPU(0x0000));
L_003A82:
    myMapper->writeCPU(0x06F0, a);
    popAddress();
}

void game::SUB_003A86() {
    y = 0x07;
    setLoadFlag(y);
    do {
        opASL_A(1);
        if (flgC) {
            goto L_003A8E;
        }
        opDEY(1);
    } while (!flgZ);
L_003A8E:
    popAddress();
}

void game::SUB_003A8F() {
    myMapper->writeCPU(0x00F1, a);
    myMapper->writeCPU(0x00F2, y);
    SUB_003A93();
    return;
}

void game::SUB_003A93() {
    y = 0x7F;
    setLoadFlag(y);
    SUB_003A95();
    return;
}

void game::SUB_003A95() {
    myMapper->writeCPU(0x4000, x);
    myMapper->writeCPU(0x4001, y);
    popAddress();
}

void game::SUB_003A9F() {
    x = 0x00;
    setLoadFlag(x);
    SUB_003AA1();
    return;
}

void game::SUB_003AA1() {
    y = a;
    setLoadFlag(y);
    a = myMapper->readCPU(0xFB01 + y);
    setLoadFlag(a);
    if (flgZ) {
        goto L_003AB2;
    }
    myMapper->writeCPU(0x4002 + x, a);
    a = myMapper->readCPU(0xFB00 + y);
    setLoadFlag(a);
    opORA(0x08);
    myMapper->writeCPU(0x4003 + x, a);
L_003AB2:
    popAddress();
}

void game::SUB_003AB3() {
    myMapper->writeCPU(0x4005, y);
    x = 0x04;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_003AA1();
        return;
    }
    SUB_003ABA();
    return;
}

void game::SUB_003ABA() {
    myMapper->writeCPU(0x4008, a);
    a = x;
    setLoadFlag(a);
    opAND(0x3E);
    x = 0x08;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_003AA1();
        return;
    }
    SUB_003AC4();
    return;
}

void game::SUB_003AC4() {
    x = a;
    setLoadFlag(x);
    opROR_A(1);
    a = x;
    setLoadFlag(a);
    opROL_A(3);
    SUB_003ACA();
    return;
}

void game::SUB_003ACA() {
    opAND(0x07);
    flgC = false;
    opADC(myMapper->readCPU(0x068D));
    y = a;
    setLoadFlag(y);
    a = myMapper->readCPU(0xFB4C + y);
    setLoadFlag(a);
    popAddress();
}

void game::SUB_003AD5() {
    a = y;
    setLoadFlag(a);
    opLSR_A(1);
    SUB_003AD7();
    return;
}

void game::SUB_003AD7() {
    opLSR_A(2);
    myMapper->writeCPU(0x0000, a);
    a = y;
    setLoadFlag(a);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    popAddress();
}

void game::SUB_003AE0() {
    a = 0x90;
    setLoadFlag(a);
    myMapper->writeCPU(0x4000, a);
    popAddress();
}

void game::SUB_003B75() {
    myMapper->writeCPU(0x00F0, a);
    myMapper->writeCPU(0x00FB, a);
    y = 0x08;
    setLoadFlag(y);
    SUB_003D67();
    return;
}

void game::SUB_003B7E() {
    myMapper->writeCPU(0x00F0, y);
    a = 0x71;
    setLoadFlag(a);
    y = 0x00;
    setLoadFlag(y);
    x = 0x9F;
    setLoadFlag(x);
    pushAddress(0x003B86);
    SUB_003A8F();
    if (poppedEntry.value != 0x003B86) return;
    SUB_003B89();
    return;
}

void game::SUB_003B89() {
    x = myMapper->readCPU(0x00F2);
    setLoadFlag(x);
    y = myMapper->readCPU(0xFB67 + x);
    setLoadFlag(y);
    opDEC(0x00F1, 1);
    a = myMapper->readCPU(0x00F1);
    setLoadFlag(a);
    if (flgZ) {
        SUB_003B75();
        return;
    }
    opAND(0x07);
    if (flgZ) {
        a = y;
        setLoadFlag(a);
        opLSR_A(1);
        opADC(myMapper->readCPU(0xFB67 + x));
        y = a;
        setLoadFlag(y);
        if (!flgZ) {
            goto L_003BA7;
        }
    }
    opAND(0x03);
    if (flgZ) {
        opINC(0x00F2, 1);
        flgC = false;
    L_003BA7:
        myMapper->writeCPU(0x4002, y);
        y = 0x28;
        setLoadFlag(y);
        if (!flgC) {
            goto L_003BAF;
        }
        opINY(1);
    L_003BAF:
        myMapper->writeCPU(0x4003, y);
    }
    a = 0x00;
    setLoadFlag(a);
    SUB_003E00();
    return;
}

void game::SUB_003BB7() {
    myMapper->writeCPU(0x00F0, y);
    a = 0x54;
    setLoadFlag(a);
    y = 0x6A;
    setLoadFlag(y);
    x = 0x9C;
    setLoadFlag(x);
    pushAddress(0x003BBF);
    SUB_003A8F();
    if (poppedEntry.value != 0x003BBF) return;
    SUB_003BC2();
    return;
}

void game::SUB_003BC2() {
    y = myMapper->readCPU(0x00F2);
    setLoadFlag(y);
    a = myMapper->readCPU(0x00F1);
    setLoadFlag(a);
    opAND(0x03);
    if (flgZ) {
        goto L_003BD4;
    }
    opCMP(a, 0x03);
    if (!flgZ) {
        goto L_003BD9;
    }
    pushAddress(0x003BCE);
    SUB_003AD5();
    if (poppedEntry.value != 0x003BCE) return;
    myMapper->writeCPU(0x00F2, a);
    y = a;
    setLoadFlag(y);
L_003BD4:
    a = y;
    setLoadFlag(a);
    opLSR_A(1);
    opADC(myMapper->readCPU(0x00F2));
    y = a;
    setLoadFlag(y);
L_003BD9:
    a = y;
    setLoadFlag(a);
    opROL_A(3);
    myMapper->writeCPU(0x4002, a);
    opROL_A(1);
    myMapper->writeCPU(0x4003, a);
    a = myMapper->readCPU(0x00F1);
    setLoadFlag(a);
    opCMP(a, 0x18);
    if (flgC) {
        SUB_003C44();
        return;
    }
    opLSR_A(1);
    opORA(0x90);
    myMapper->writeCPU(0x4000, a);
    if (!flgZ) {
        SUB_003C44();
        return;
    }
    SUB_003BF2();
    return;
}

void game::SUB_003BF2() {
    y = myMapper->readCPU(0x00FF);
    setLoadFlag(y);
    a = myMapper->readCPU(0x00F0);
    setLoadFlag(a);
    opLSR_A(1);
    if (flgC) {
        SUB_003B89();
        return;
    }
    opLSR_M(0x00FF, 1);
    if (flgC) {
        SUB_003B7E();
        return;
    }
    x = myMapper->readCPU(0x00FA);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_003C4B();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003BC2();
        return;
    }
    opLSR_M(0x00FF, 1);
    if (flgC) {
        SUB_003BB7();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003C28();
        return;
    }
    opLSR_M(0x00FF, 1);
    if (flgC) {
        SUB_003C19();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003C62();
        return;
    }
    opLSR_M(0x00FF, 1);
    if (flgC) {
        SUB_003C51();
        return;
    }
    SUB_003C16();
    return;
}

void game::SUB_003C16() {
    SUB_003C90();
    return;
}

void game::SUB_003C19() {
    myMapper->writeCPU(0x00F0, y);
    a = 0x22;
    setLoadFlag(a);
    myMapper->writeCPU(0x00F1, a);
    y = 0x0B;
    setLoadFlag(y);
    myMapper->writeCPU(0x00F2, y);
    a = 0x20;
    setLoadFlag(a);
    pushAddress(0x003C25);
    SUB_003A9F();
    if (poppedEntry.value != 0x003C25) return;
    SUB_003C28();
    return;
}

void game::SUB_003C28() {
    opDEC(0x00F2, 1);
    if (!flgZ) {
        goto L_003C30;
    }
    a = 0x07;
    setLoadFlag(a);
    myMapper->writeCPU(0x00F2, a);
L_003C30:
    x = myMapper->readCPU(0x00F2);
    setLoadFlag(x);
    y = myMapper->readCPU(0xFAF5 + x);
    setLoadFlag(y);
    x = 0x5A;
    setLoadFlag(x);
    a = myMapper->readCPU(0x00F1);
    setLoadFlag(a);
    opCMP(a, 0x14);
    if (flgC) {
        SUB_003C41();
        return;
    }
    opLSR_A(1);
    opORA(0x50);
    x = a;
    setLoadFlag(x);
    SUB_003C41();
    return;
}

void game::SUB_003C41() {
    pushAddress(0x003C41);
    SUB_003A95();
    if (poppedEntry.value != 0x003C41) return;
    SUB_003C44();
    return;
}

void game::SUB_003C44() {
    opDEC(0x00F1, 1);
    if (!flgZ) {
        SUB_003C16();
        return;
    }
    pushAddress(0x003C48);
    SUB_003AE0();
    if (poppedEntry.value != 0x003C48) return;
    SUB_003C4B();
    return;
}

void game::SUB_003C4B() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00F0, a);
    if (flgZ) {
        SUB_003C16();
        return;
    }
    SUB_003C51();
    return;
}

void game::SUB_003C51() {
    myMapper->writeCPU(0x00F0, y);
    a = 0x0A;
    setLoadFlag(a);
    myMapper->writeCPU(0x00F1, a);
    y = myMapper->readCPU(0x06F0);
    setLoadFlag(y);
    myMapper->writeCPU(0x4002, y);
    a = 0x88;
    setLoadFlag(a);
    myMapper->writeCPU(0x4003, a);
    SUB_003C62();
    return;
}

void game::SUB_003C62() {
    a = myMapper->readCPU(0x0018);
    setLoadFlag(a);
    opAND(0x08);
    flgC = false;
    opADC(myMapper->readCPU(0x00F1));
    opADC(0xFE);
    x = a;
    setLoadFlag(x);
    y = myMapper->readCPU(0xFAE5 + x);
    setLoadFlag(y);
    x = 0x41;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_003C41();
        return;
    }
    SUB_003C73();
    return;
}

void game::SUB_003C73() {
    a = 0x0E;
    setLoadFlag(a);
    myMapper->writeCPU(0x06A5, a);
    y = 0x85;
    setLoadFlag(y);
    a = 0x46;
    setLoadFlag(a);
    pushAddress(0x003C7C);
    SUB_003AB3();
    if (poppedEntry.value != 0x003C7C) return;
    SUB_003C7F();
    return;
}

void game::SUB_003C7F() {
    opDEC(0x06A5, 1);
    if (flgZ) {
        SUB_003C9D();
        return;
    }
    a = myMapper->readCPU(0x06A5);
    setLoadFlag(a);
    opORA(0x90);
    y = a;
    setLoadFlag(y);
    opDEY(1);
    myMapper->writeCPU(0x4004, y);
    if (!flgZ) {
        SUB_003C9D();
        return;
    }
    SUB_003C90();
    return;
}

void game::SUB_003C90() {
    a = myMapper->readCPU(0x00F3);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003C9D();
        return;
    }
    a = myMapper->readCPU(0x06A5);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003C7F();
        return;
    }
    y = myMapper->readCPU(0x00FE);
    setLoadFlag(y);
    if (flgN) {
        SUB_003C73();
        return;
    }
    SUB_003C9D();
    return;
}

void game::SUB_003C9D() {
    a = myMapper->readCPU(0x00FC);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x00F9);
        setLoadFlag(a);
        if (flgZ) {
            y = myMapper->readCPU(0x00FE);
            setLoadFlag(y);
            a = myMapper->readCPU(0x06A1);
            setLoadFlag(a);
            opLSR_M(0x00FE, 1);
            if (!flgC) {
                opLSR_A(1);
                if (flgC) {
                    goto L_003CBE;
                }
                opLSR_A(1);
                if (flgC) {
                    goto L_003CF0;
                }
                opLSR_M(0x00FE, 1);
                if (flgC) {
                    goto L_003CDB;
                }
                if (!flgC) {
                    goto L_003D0B;
                }
            }
            a = 0x28;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_003CDD;
            }
        L_003CBE:
            a = myMapper->readCPU(0x00F5);
            setLoadFlag(a);
            if (flgZ) {
                opLSR_M(0x00FE, 1);
                if (flgC) {
                    goto L_003CDB;
                }
            }
            a = myMapper->readCPU(0x00F6);
            setLoadFlag(a);
            opLSR_A(5);
            opADC(myMapper->readCPU(0x00F6));
            if (flgC) {
                do {
                    a = 0x00;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x06A1, a);
                    myMapper->writeCPU(0x4008, a);
                    if (flgZ) {
                        goto L_003D0B;
                    }
                L_003CDB:
                    a = 0xFE;
                    setLoadFlag(a);
                L_003CDD:
                    myMapper->writeCPU(0x06A1, y);
                    x = 0x0E;
                    setLoadFlag(x);
                    myMapper->writeCPU(0x00F5, x);
                    y = 0xFF;
                    setLoadFlag(y);
                    myMapper->writeCPU(0x4008, y);
                    y = 0x08;
                    setLoadFlag(y);
                    myMapper->writeCPU(0x400B, y);
                    if (!flgZ) {
                        goto L_003D00;
                    }
                L_003CF0:
                    a = 0xFE;
                    setLoadFlag(a);
                    y = myMapper->readCPU(0x00F5);
                    setLoadFlag(y);
                } while (flgZ);
                opCMP(y, 0x07);
                if (!flgZ) {
                    a = myMapper->readCPU(0x00F6);
                    setLoadFlag(a);
                    y = a;
                    setLoadFlag(y);
                    pushAddress(0x003CFD);
                    SUB_003AD7();
                    if (poppedEntry.value != 0x003CFD) return;
                }
            }
        L_003D00:
            myMapper->writeCPU(0x00F6, a);
            myMapper->writeCPU(0x400A, a);
            a = myMapper->readCPU(0x00F5);
            setLoadFlag(a);
            if (!flgZ) {
                opDEC(0x00F5, 1);
            }
        }
    }
L_003D0B:
    x = myMapper->readCPU(0x00FA);
    setLoadFlag(x);
    if (flgZ) {
        a = myMapper->readCPU(0x00FC);
        setLoadFlag(a);
        if (flgZ) {
            myMapper->writeCPU(0x06A3, a);
            if (flgZ) {
                goto L_003D58;
            }
        }
        opEOR(myMapper->readCPU(0x06A3));
        if (flgZ) {
            goto L_003D35;
        }
        do {
            a = myMapper->readCPU(0x00FC);
            setLoadFlag(a);
            myMapper->writeCPU(0x06A3, a);
            pushAddress(0x003D22);
            SUB_003A86();
            if (poppedEntry.value != 0x003D22) return;
            a = myMapper->readCPU(0xFFCD + y);
            setLoadFlag(a);
            myMapper->writeCPU(0x0680, a);
            a = 0xD4;
            setLoadFlag(a);
            myMapper->writeCPU(0x00F5, a);
            a = 0xFF;
            setLoadFlag(a);
            myMapper->writeCPU(0x00F6, a);
            if (!flgZ) {
                goto L_003D3A;
            }
        L_003D35:
            opDEC(0x0698, 1);
            if (!flgZ) {
                goto L_003D58;
            }
        L_003D3A:
            y = myMapper->readCPU(0x0680);
            setLoadFlag(y);
            opINC(0x0680, 1);
            a = myMapper->readCPU(myMapper->readCPU(0x00F5) + (myMapper->readCPU((0x00F5 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
        } while (flgZ);
        x = a;
        setLoadFlag(x);
        opROR_A(1);
        a = x;
        setLoadFlag(a);
        opROL_A(3);
        opAND(0x07);
        y = a;
        setLoadFlag(y);
        a = myMapper->readCPU(0xFB62 + y);
        setLoadFlag(a);
        myMapper->writeCPU(0x0698, a);
        a = 0x10;
        setLoadFlag(a);
        pushAddress(0x003D55);
        SUB_003ABA();
        if (poppedEntry.value != 0x003D55) return;
    }
L_003D58:
    a = myMapper->readCPU(0x00FD);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_003D62;
    }
    a = myMapper->readCPU(0x0102);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003D9B();
        return;
    }
    popAddress();
    return;
L_003D62:
    pushAddress(0x003D62);
    SUB_003A86();
    if (poppedEntry.value != 0x003D62) return;
    myMapper->writeCPU(0x00FB, y);
    SUB_003D67();
    return;
}

void game::SUB_003D67() {
    a = myMapper->readCPU(0xFE59 + y);
    setLoadFlag(a);
    y = a;
    setLoadFlag(y);
    a = myMapper->readCPU(0xFE59 + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x068D, a);
    a = myMapper->readCPU(0xFE5A + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x00F7, a);
    a = myMapper->readCPU(0xFE5B + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x00F8, a);
    a = myMapper->readCPU(0xFE5C + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x00F9, a);
    a = myMapper->readCPU(0xFE5D + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x00FA, a);
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0695, a);
    myMapper->writeCPU(0x0696, a);
    myMapper->writeCPU(0x0698, a);
    myMapper->writeCPU(0x0102, a);
    y = 0x00;
    setLoadFlag(y);
    myMapper->writeCPU(0x00F3, y);
    a = myMapper->readCPU(0x00FB);
    setLoadFlag(a);
    if (flgZ) {
        SUB_003DA4();
        return;
    }
    SUB_003D9B();
    return;
}

void game::SUB_003D9B() {
    y = myMapper->readCPU(0x00FA);
    setLoadFlag(y);
    if (flgZ) {
        SUB_003DD8();
        return;
    }
    opDEC(0x0696, 1);
    if (!flgZ) {
        SUB_003DD8();
        return;
    }
    SUB_003DA4();
    return;
}

void game::SUB_003DA4() {
    opINC(0x00FA, 1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F7) + (myMapper->readCPU((0x00F7 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (flgZ) {
        SUB_003DE9();
        return;
    }
    if (flgN) {
        pushAddress(0x003DAC);
        SUB_003ACA();
        if (poppedEntry.value != 0x003DAC) return;
        myMapper->writeCPU(0x0691, a);
        y = myMapper->readCPU(0x00FA);
        setLoadFlag(y);
        opINC(0x00FA, 1);
        a = myMapper->readCPU(myMapper->readCPU(0x00F7) + (myMapper->readCPU((0x00F7 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
    }
    pushAddress(0x003DB8);
    SUB_003A9F();
    if (poppedEntry.value != 0x003DB8) return;
    if (flgZ) {
        y = 0x10;
        setLoadFlag(y);
        if (!flgZ) {
            goto L_003DCF;
        }
    }
    x = 0x9F;
    setLoadFlag(x);
    a = myMapper->readCPU(0x00FB);
    setLoadFlag(a);
    if (!flgZ) {
        x = 0x06;
        setLoadFlag(x);
        a = myMapper->readCPU(0x00F9);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_003DCF;
        }
        x = 0x86;
        setLoadFlag(x);
    }
L_003DCF:
    pushAddress(0x003DCF);
    SUB_003A93();
    if (poppedEntry.value != 0x003DCF) return;
    a = myMapper->readCPU(0x0691);
    setLoadFlag(a);
    myMapper->writeCPU(0x0696, a);
    SUB_003DD8();
    return;
}

void game::SUB_003DD8() {
    a = myMapper->readCPU(0x00FB);
    setLoadFlag(a);
    if (flgZ) {
        SUB_003E31();
        return;
    }
    opDEC(0x0695, 1);
    if (!flgZ) {
        SUB_003E31();
        return;
    }
    y = myMapper->readCPU(0x00F3);
    setLoadFlag(y);
    opINC(0x00F3, 1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F7) + (myMapper->readCPU((0x00F7 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003E09();
        return;
    }
    SUB_003DE9();
    return;
}

void game::SUB_003DE9() {
    pushAddress(0x003DE9);
    SUB_003AE0();
    if (poppedEntry.value != 0x003DE9) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00FA, a);
    myMapper->writeCPU(0x00F3, a);
    myMapper->writeCPU(0x00F9, a);
    myMapper->writeCPU(0x0102, a);
    y = myMapper->readCPU(0x00FB);
    setLoadFlag(y);
    if (flgZ) {
        SUB_003E00();
        return;
    }
    y = myMapper->readCPU(0x06A1);
    setLoadFlag(y);
    if (!flgZ) {
        SUB_003E03();
        return;
    }
    SUB_003E00();
    return;
}

void game::SUB_003E00() {
    myMapper->writeCPU(0x4008, a);
    SUB_003E03();
    return;
}

void game::SUB_003E03() {
    a = 0x10;
    setLoadFlag(a);
    myMapper->writeCPU(0x4004, a);
    popAddress();
}

void game::SUB_003E09() {
    pushAddress(0x003E09);
    SUB_003AC4();
    if (poppedEntry.value != 0x003E09) return;
    myMapper->writeCPU(0x0695, a);
    a = x;
    setLoadFlag(a);
    opAND(0x3E);
    y = 0x7F;
    setLoadFlag(y);
    pushAddress(0x003E14);
    SUB_003AB3();
    if (poppedEntry.value != 0x003E14) return;
    if (flgZ) {
        x = 0x10;
        setLoadFlag(x);
        if (!flgZ) {
            goto L_003E2E;
        }
    }
    x = 0x89;
    setLoadFlag(x);
    a = myMapper->readCPU(0x0695);
    setLoadFlag(a);
    opCMP(a, 0x18);
    if (!flgC) {
        x = 0x86;
        setLoadFlag(x);
        opCMP(a, 0x10);
        if (flgC) {
            goto L_003E2E;
        }
        x = 0x84;
        setLoadFlag(x);
    }
L_003E2E:
    myMapper->writeCPU(0x4004, x);
    SUB_003E31();
    return;
}

void game::SUB_003E31() {
    y = myMapper->readCPU(0x00F9);
    setLoadFlag(y);
    if (!flgZ) {
        opDEC(0x0698, 1);
        if (flgZ) {
            opINC(0x00F9, 1);
            a = myMapper->readCPU(myMapper->readCPU(0x00F7) + (myMapper->readCPU((0x00F7 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            pushAddress(0x003E3E);
            SUB_003AC4();
            if (poppedEntry.value != 0x003E3E) return;
            myMapper->writeCPU(0x0698, a);
            flgC = false;
            opADC(0xFE);
            opASL_A(2);
            opCMP(a, 0x38);
            if (flgC) {
                a = 0x38;
                setLoadFlag(a);
            }
            y = myMapper->readCPU(0x00FB);
            setLoadFlag(y);
            if (!flgZ) {
                goto L_003E55;
            }
            a = 0xFF;
            setLoadFlag(a);
        L_003E55:
            pushAddress(0x003E55);
            SUB_003ABA();
            if (poppedEntry.value != 0x003E55) return;
        }
    }
    popAddress();
}

