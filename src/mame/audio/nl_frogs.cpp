// license:CC0
// copyright-holders:Aaron Giles

//
// Netlist for Frogs
//
// Derived from the schematics in the Frogs manual.
//
// Known problems/issues:
//
//    * Croak sound should have a little bit more tonality.
//
//    * Performance work needed
//

#include "netlist/devices/net_lib.h"
#include "nl_frogs.h"


//
// Optimizations
//

#define ENABLE_FRONTIERS (1)
#define UNDERCLOCK_NOISE_GEN (1)



//
// Hacks
//



//
// Main netlist
//

#define D_1N914(name) DIODE(name, "1N914")

#define Q_2N4401(name) QBJT_EB(name, "2N4401")
#define Q_2N4403(name) QBJT_EB(name, "2N4403")

// JFET transistors not supported, but this should do the trick
#define Q_2N4093(name) MOSFET(name, "NMOS(VTO=-1 CAPMOD=0)")

#define LM741_DIP UA741_DIP8

NETLIST_START(frogs)

	SOLVER(Solver, 1000)
	PARAM(Solver.DYNAMIC_TS, 1)
	PARAM(Solver.DYNAMIC_MIN_TIMESTEP, 4e-6)

	TTL_INPUT(I_SOUND_0, 0)
	TTL_INPUT(I_SOUND_1, 0)
	TTL_INPUT(I_SOUND_2, 0)
	TTL_INPUT(I_SOUND_3, 0)
	TTL_INPUT(I_SOUND_4, 0)
	TTL_INPUT(I_SOUND_5, 0)
	TTL_INPUT(I_SOUND_6, 0)
	TTL_INPUT(I_SOUND_7, 0)

	NET_C(GND, I_SOUND_0.GND, I_SOUND_1.GND, I_SOUND_2.GND, I_SOUND_3.GND, I_SOUND_4.GND, I_SOUND_5.GND, I_SOUND_6.GND, I_SOUND_7.GND)
	NET_C(I_V5, I_SOUND_0.VCC, I_SOUND_1.VCC, I_SOUND_2.VCC, I_SOUND_3.VCC, I_SOUND_4.VCC, I_SOUND_5.VCC, I_SOUND_6.VCC, I_SOUND_7.VCC)

	ALIAS(I_HOP, I_SOUND_0)
	ALIAS(I_JUMP, I_SOUND_1)
	ALIAS(I_TONGUE, I_SOUND_2)
	ALIAS(I_CAPTURE, I_SOUND_3)
	ALIAS(I_FLY, I_SOUND_4)
	ALIAS(I_SPLASH, I_SOUND_7)

	ANALOG_INPUT(I_V5, 5)
	ANALOG_INPUT(I_V12, 12)
	ANALOG_INPUT(I_VM12, -12)

	RES(R1, RES_K(3.3))     // SPLASH
	RES(R2, RES_K(3.3))     // SPLASH
	RES(R3, RES_K(3.3))     // CAPTURE
	RES(R4, RES_K(3.3))     // CAPTURE
	RES(R5, RES_K(3.3))     // TONGUE
	RES(R6, RES_K(3.3))     // TONGUE
	RES(R7, RES_K(3.3))     // HOP
	RES(R8, RES_K(3.3))     // HOP
	RES(R9, RES_K(3.3))     // JUMP
	RES(R10, RES_K(3.3))    // JUMP
	RES(R11, RES_K(3.3))    // FLY
	RES(R12, RES_K(10))     // FLY
	RES(R13, RES_K(10))     // SPLASH
	RES(R14, RES_K(4.7))    // SPLASH
	RES(R15, RES_K(100))    // SPLASH
	RES(R16, RES_K(4.7))    // CAPTURE
	RES(R17, RES_K(330))    // CAPTURE
	RES(R18, RES_K(4.7))    // TONGUE
	RES(R19, RES_K(100))    // TONGUE
	RES(R20, RES_K(4.7))    // HOP
	RES(R21, RES_K(3.3))    // HOP
	RES(R22, RES_K(4.7))    // JUMP
	RES(R23, RES_K(150))    // JUMP
	RES(R24, RES_K(4.7))    // FLY
	RES(R25, RES_K(22))     // SPLASH
	RES(R26, 51)            // HOP
	RES(R27, RES_K(10))     // FLY
	RES(R28, RES_K(22))     // TONGUE
	RES(R29, RES_K(100))    // TONGUE
	RES(R30, RES_K(470))    // HOP
	RES(R31, 220)           // HOP
	RES(R32, RES_K(33))     // HOP (mislabelled R22)
	RES(R33, 330)           // JUMP
	RES(R34, 820)           // JUMP
	RES(R35, RES_K(100))    // FLY
	RES(R36, RES_K(2.2))    // FLY
	RES(R37, RES_K(2.2))    // SPLASH
	RES(R38, RES_K(10))     // SPLASH
	RES(R39, RES_K(10))     // SPLASH
	RES(R40, RES_K(68))     // CAPTURE
	RES(R41, RES_K(4.7))    // CAPTURE
	RES(R42, RES_K(1))      // TONGUE
	RES(R43, RES_K(82))     // HOP
	RES(R44, RES_K(3.3))    // FLY
	RES(R45, RES_K(100))    // FLY
	RES(R46, RES_K(3.3))    // FLY
	POT(R47, RES_K(50))     // SPLASH
	RES(R48, RES_K(47))     // CAPTURE
	RES(R49, RES_K(3.3))    // CAPTURE
	RES(R50, RES_K(100))    // CAPTURE
	RES(R51, RES_K(39))     // TONGUE
	RES(R52, 51)            // HOP
	RES(R53, RES_K(62))
	RES(R54, 470)           // JUMP
	RES(R55, RES_K(22))     // JUMP
	RES(R56, RES_M(2.2))    // JUMP
	RES(R57, RES_K(22))
	RES(R58, RES_K(22))
	RES(R59, RES_K(3.3))    // FLY
//  RES(R60, RES_K(10))     -- final amp
	RES(R61, RES_K(100))    // SPLASH
	RES(R62, RES_K(47))     // SPLASH
	RES(R63, RES_K(33))     // SPLASH
	RES(R64, RES_K(820))    // CAPTURE
	RES(R65, RES_K(150))    // CAPTURE
	RES(R66, 51)            // CAPTURE
	RES(R67, 51)            // CAPTURE
	RES(R68, RES_K(1))      // JUMP
	RES(R69, RES_K(82))     // JUMP
	RES(R70, 51)            // JUMP
	RES(R71, RES_K(4.7))    // JUMP
	RES(R72, RES_K(27))     // FLY
	RES(R73, RES_K(10))     // FLY
	RES(R74, RES_K(1))      // FLY
	RES(R75, RES_K(10))     // JUMP
	RES(R76, RES_K(10))     // JUMP
	RES(R77, 560)           // JUMP
	RES(R78, RES_K(10))     // JUMP
	RES(R79, RES_K(10))     // JUMP
	RES(R80, RES_K(39))     // FLY
	RES(R81, RES_K(100))    // FLY
	RES(R82, RES_K(10))     // FLY
	RES(R83, RES_K(100))    // JUMP
	RES(R84, RES_K(1))      // JUMP
	RES(R85, RES_K(10))     // JUMP
	RES(R86, RES_K(1))      // FLY
	RES(R87, RES_K(100))    // FLY
	RES(R88, RES_K(82))     // FLY
	RES(R90, RES_K(56))     // MIXER
	POT(R91, RES_K(100))
	POT(R92, RES_M(1))
	POT(R93, RES_M(1))
	POT(R94, RES_M(1))
	POT(R95, RES_M(1))
	POT(R96, RES_K(50))

//  CAP(C1, CAP_U(10))
//  CAP(C2, CAP_U(10))
	CAP(C3, CAP_U(0.047))
	CAP(C4, CAP_U(1))
	CAP(C5, CAP_U(1))
	CAP(C6, CAP_U(0.1))
	CAP(C7, CAP_U(0.1))
	CAP(C8, CAP_U(1))
	CAP(C9, CAP_U(0.1))
	CAP(C10, CAP_U(0.1))
	CAP(C11, CAP_U(0.05))
	CAP(C12, CAP_U(0.05))
	CAP(C13, CAP_U(0.05))
	CAP(C14, CAP_U(0.05))
	CAP(C15, CAP_U(0.05))
	CAP(C16, CAP_U(0.05))
	CAP(C17, CAP_U(0.05))
	CAP(C18, CAP_U(0.05))
	CAP(C19, CAP_U(0.05))
	CAP(C20, CAP_U(0.05))
	CAP(C21, CAP_U(0.05))
	CAP(C22, CAP_U(2.2))
	CAP(C23, CAP_U(10))
	CAP(C24, CAP_U(0.1))
	CAP(C25, CAP_U(4.7))
	CAP(C26, CAP_U(0.05))
	CAP(C27, CAP_U(1))
	CAP(C28, CAP_U(0.05))
	CAP(C29, CAP_U(0.047))
	CAP(C30, CAP_U(10))
	CAP(C31, CAP_U(0.47))
	CAP(C32, CAP_U(0.47))
	CAP(C33, CAP_U(0.05))
//  CAP(C34, CAP_U(0.05))   -- final amp
//  CAP(C35, CAP_U(0.05))   -- final amp
	CAP(C36, CAP_U(0.05))
	CAP(C37, CAP_U(0.05))
	CAP(C38, CAP_U(0.05))
	CAP(C39, CAP_U(0.1))
	CAP(C40, CAP_U(0.1))
	CAP(C41, CAP_U(0.05))
	CAP(C42, CAP_U(0.05))
	CAP(C43, CAP_U(0.05))
	CAP(C44, CAP_U(10))
	CAP(C45, CAP_U(0.01))
	CAP(C46, CAP_U(0.01))
	CAP(C47, CAP_U(1))
	CAP(C48, CAP_U(0.05))
	CAP(C49, CAP_U(0.1))
	CAP(C50, CAP_U(0.01))
	CAP(C51, CAP_U(0.01))
	CAP(C52, CAP_U(0.1))
	CAP(C53, CAP_U(0.05))
	CAP(C54, CAP_U(0.01))
	CAP(C55, CAP_U(0.05))
	CAP(C56, CAP_U(0.05))
	CAP(C57, CAP_U(2.2))
//  CAP(C58, CAP_U(0.1))    -- final amp
	CAP(C59, CAP_U(0.05))
	CAP(C60, CAP_U(0.05))
	CAP(C61, CAP_U(0.05))
	CAP(C62, CAP_U(0.1))
	CAP(C63, CAP_U(0.05))
	CAP(C64, CAP_U(0.05))
	CAP(C65, CAP_U(0.1))
	CAP(C66, CAP_U(2.2))
	CAP(C67, CAP_U(0.05))
	CAP(C68, CAP_U(0.05))
	CAP(C69, CAP_U(0.05))
	CAP(C70, CAP_U(0.05))
	CAP(C71, CAP_U(0.05))
	CAP(C72, CAP_U(1))
	CAP(C73, CAP_U(0.047))
	CAP(C74, CAP_U(0.05))

	D_1N914(D1)
	D_1N914(D2)
	D_1N914(D3)
	D_1N914(D4)
	D_1N914(D5)
	D_1N914(D6)
	D_1N914(D7)
	D_1N914(D8)
	D_1N914(D9)

	Q_2N4401(Q1)
	Q_2N4401(Q2)
	Q_2N4401(Q3)
	Q_2N4401(Q4)
	Q_2N4401(Q5)
	Q_2N4401(Q6)
	Q_2N4401(Q7)
	Q_2N4403(Q8)
	Q_2N4403(Q9)
	Q_2N4093(Q10)
	Q_2N4401(Q11)
	Q_2N4401(Q12)
	Q_2N4403(Q13)
	Q_2N4401(Q14)
	Q_2N4403(Q15)
	Q_2N4401(Q16)
	Q_2N4403(Q17)
	Q_2N4093(Q18)
	Q_2N4401(Q19)
	Q_2N4401(Q20)
	Q_2N4401(Q21)

	MM5837_DIP(U1)          // Noise Generator
#if (UNDERCLOCK_NOISE_GEN)
	PARAM(U1.FREQ, 24000)
#endif
	NE555_DIP(U2)           // Timer
	NE555_DIP(U3)           // Timer
	NE555_DIP(U4)           // Timer
	NE555_DIP(U5)           // Timer
	NE555_DIP(U6)           // Timer
	NE555_DIP(U7)           // Timer
	LM741_DIP(U8)           // Op. Amp.
	NE555_DIP(U9)           // Timer
	LM741_DIP(U10)          // Op. Amp.
	LM741_DIP(U11)          // Op. Amp.
	NE555_DIP(U12)          // Timer
//  LM741_DIP(U13)          // Op. Amp. -- final amp
	LM741_DIP(U14)          // Op. Amp.
	NE555_DIP(U15)          // Timer
	LM741_DIP(U16)          // Op. Amp.
	LM741_DIP(U17)          // Op. Amp.
	LM741_DIP(U18)          // Op. Amp.
	NE555_DIP(U19)          // Timer
	LM741_DIP(U20)          // Op. Amp.

	//
	// JUMP
	//

	NET_C(I_V12, R22.2, U6.4, U6.8, C68.2, R23.2)
	NET_C(GND, R10.1, Q2.E, C15.1, U6.1, C7.1, R34.1, U11.3, C71.1, C70.1, R54.1, Q19.B, D7.A, R84.1, R75.1, C64.1, R77.1, U19.1, C53.1, C52.1, U16.3)
	NET_C(I_JUMP, R9.1)
	NET_C(R9.2, R10.2, Q2.B)
	NET_C(Q2.C, R22.1, U6.2)
	NET_C(C15.2, U6.5)
	NET_C(C68.1, GND)
	NET_C(R23.1, U6.7, U6.6, C7.2)
	NET_C(U6.3, C22.1, R33.1)
	NET_C(R33.2, Q8.E)
	NET_C(Q8.B, GND)
	NET_C(Q8.C, C44.1, R57.1)
	NET_C(C44.2, R70.1)
	NET_C(R57.2, R58.2, Q16.B)
	NET_C(Q16.E, R71.2)
	NET_C(R71.1, R58.1, R70.2, I_VM12)
	NET_C(R34.2, C22.2, C32.1, C31.1)
	NET_C(C32.2, R56.1, U11.2)
	NET_C(R56.2, C31.2, U11.6, R55.1)
	NET_C(I_V12, C70.2, U11.7)
	NET_C(I_VM12, U11.4, C71.2)
	NET_C(R55.2, R54.2, Q21.B)
	NET_C(Q21.E, D7.K, Q16.C)
	NET_C(Q19.E, Q21.C, Q20.E)
	NET_C(Q19.C, R76.1, R85.1, U20.2)
	NET_C(I_V12, R76.2, R78.2)
	NET_C(R78.1, Q20.C, U20.3, R75.2)
	NET_C(Q20.B, R84.2, R83.1)
	NET_C(R85.2, U20.6, R79.1)
	NET_C(I_V12, U20.7, C63.2)
	NET_C(C63.1, GND)
	NET_C(I_VM12, U20.4, C64.2)
	NET_C(R83.2, C62.1)
	NET_C(R79.2, R77.2, C54.1, C51.1)
	NET_C(C62.2, U19.3)
	NET_C(I_V12, U19.4, C61.2, U19.8, R68.2)
	NET_C(C61.1, GND)
	NET_C(C53.2, U19.5)
	NET_C(U19.2, U19.6, R69.1, C52.2)
	NET_C(U19.7, R69.2, R68.1)
	NET_C(C54.2, U16.2, R53.1)
	NET_C(R53.2, U16.6, C51.2)
	NET_C(I_V12, U16.7, C42.2)
	NET_C(C42.1, GND)
	NET_C(I_VM12, U16.4, C43.2)
	NET_C(C43.1, GND)
	ALIAS(BOING, U16.6)

	//
	// TONGUE
	//

	NET_C(I_V12, C20.2, R18.2, U4.4, U4.8, R19.2, Q11.C, R28.2, R42.2, U15.4, U15.8, C48.2)
	NET_C(GND, R6.1, Q4.E, C13.1, U4.1, C5.2, R51.1, C49.1, U15.1, C41.1, C48.1)
	NET_C(I_TONGUE, R5.1)
	NET_C(R5.2, R6.2, Q4.B)
	NET_C(C20.1, GND)
	NET_C(Q4.C, R18.1, U4.2)
	NET_C(C13.2, U4.5)
	NET_C(C5.1, U4.7, U4.6, R19.1, R29.1)
	RES(RU4, RES_K(100))    // netlist doesn't like unconnected
	NET_C(RU4.1, U4.3)      // 555 outputs, so run it through
	NET_C(RU4.2, GND)       // a 100k resistor to ground
	NET_C(R29.2, Q11.B)
	NET_C(Q11.E, Q12.B)
	NET_C(Q12.E, R51.2)
	NET_C(Q12.C, R28.1, Q13.B)
	NET_C(Q13.E, R42.1)
	NET_C(Q13.C, C49.2, U15.2, U15.6, U15.7, C50.1)
	NET_C(U15.5, C41.2)
	RES(RU15, RES_K(100))   // netlist doesn't like unconnected
	NET_C(RU15.1, U15.3)    // 555 outputs, so run it through
	NET_C(RU15.2, GND)      // a 100k resistor to ground
	ALIAS(ZIP, C50.2)

	//
	// HOP
	//

	NET_C(I_V12, C69.2, R20.2, U5.4, U5.8, R21.2)
	NET_C(GND, R8.1, Q3.E, C14.1, U5.1, C6.1, C30.2, Q9.B, R52.1, U10.3)
	NET_C(I_HOP, R7.1)
	NET_C(R7.2, R8.2, Q3.B)
	NET_C(C69.1, GND)
	NET_C(Q3.C, R20.1, U5.2)
	NET_C(U5.5, C14.2)
	NET_C(R21.1, U5.6, U5.7, C6.2)
	NET_C(U5.3, D2.A, R31.1)
	NET_C(D2.K, R32.2, C30.1)
	NET_C(R32.1, Q9.E)
	NET_C(Q9.C, C72.1, R43.2, Q10.G)
	NET_C(C72.2, R26.2)
	NET_C(I_VM12, R26.1, R43.1)
	NET_C(R31.2, Q10.D, C29.1, C73.1)
	NET_C(Q10.S, R52.2)
	NET_C(C29.2, U10.2, R30.1)
	NET_C(C73.2, R30.2, U10.6)
	NET_C(I_V12, U10.7, C28.2)
	NET_C(I_VM12, U10.4, C21.2)
	NET_C(C21.1, GND)
	NET_C(C28.1, GND)
	ALIAS(HOP, U10.6)

	//
	// CAPTURE
	//

	NET_C(I_V12, R16.2, C18.2, U3.4, U3.8, R17.2, C74.2, U9.8, R41.2)
	NET_C(GND, R4.1, Q5.E, C12.1, U3.1, C4.2, C19.1, U9.1, C27.2, R65.1, Q17.B, R66.1, U8.3, C18.1)
	NET_C(I_CAPTURE, R3.1)
	NET_C(R3.2, R4.2, Q5.B)
	NET_C(Q5.C, R16.1, U3.2)
	NET_C(U3.5, C12.2)
	NET_C(R17.1, U3.6, U3.7, C4.1)
	NET_C(U3.3, U9.4)
	NET_C(C74.1, GND)
	NET_C(C19.2, U9.5)
	NET_C(R41.1, R48.2, D4.A, U9.7)
	NET_C(U9.2, U9.6, R48.1, D4.K, C27.1)
	NET_C(U9.3, R50.2, R49.1)
	NET_C(R65.2, R64.2, C47.1, Q17.C, Q18.G)
	NET_C(I_VM12, R64.1, R67.1)
	NET_C(R67.2, C47.2)
	NET_C(R50.1, Q17.E)
	NET_C(R49.2, Q18.D, C39.1, C40.1)
	NET_C(Q18.S, R66.2)
	NET_C(C39.2, R40.1, U8.2)
	NET_C(C40.2, R40.2, U8.6)
	NET_C(I_V12, U8.7, C38.2)
	NET_C(C38.1, GND)
	NET_C(I_VM12, U8.4, C26.2)
	NET_C(C26.1, GND)
	ALIAS(CROAK, U8.6)

	//
	// SPLASH
	//

	NET_C(I_V12, R14.2, C17.2, U2.4, U2.8, R15.2, C25.1, R47.3, Q15.E, U1.4)
	NET_C(GND, R2.1, Q6.E, C11.1, U2.1, C3.1, R38.1, Q14.E, U1.1, R62.1, R63.1, C37.1)
	NET_C(I_SPLASH, R1.1)
	NET_C(R1.2, R2.2, Q6.B)
	NET_C(Q6.C, R14.1, U2.2)
	NET_C(U2.5, C11.2)
	NET_C(C17.1, GND)
	NET_C(U2.6, U2.7, R15.1, C3.2)
	NET_C(U2.3, R39.1)
	NET_C(R39.2, R38.2, Q14.B)
	NET_C(Q14.C, R37.1)
	NET_C(R37.2, C25.2, R47.1, R25.1)
	NET_C(R25.2, C10.1, R13.2, C9.1)
	NET_C(Q15.C, C10.2)
	NET_C(R13.1, D1.K)
	NET_C(D1.A, D5.K)
	NET_C(D5.A, U1.3)
	NET_C(U1.2, I_VM12)
	NET_C(C9.2, R63.2, U14.3)
	NET_C(R62.2, U14.2, R61.1)
	NET_C(R61.2, U14.6)
	NET_C(I_V12, U14.7, C36.2)
	NET_C(C36.1, GND)
	NET_C(I_VM12, C37.2, U14.4)
	ALIAS(SPLASH, U14.6)

	//
	// FLY
	//

	NET_C(I_V12, R12.2, R24.2, C67.2, U7.8, R35.2, C33.2, U12.8, R44.2, U17.7, C55.2, R87.2)
	NET_C(GND, R11.1, C16.1, U7.1, C8.2, Q7.E, C23.2, U12.1, C24.1, R72.1, C56.1, R74.1, R88.1, C66.2, R86.1, U18.3, C60.1)
	NET_C(I_FLY, Q1.E)
	NET_C(R11.2, R12.1, Q1.B)
	NET_C(Q1.C, R24.1, U7.2, U7.4, U12.4)
	NET_C(C16.2, U7.5)
	NET_C(C67.1, GND)
	NET_C(R35.1, U7.6, U7.7, C8.1)
	NET_C(U7.3, R27.1, D3.A)
	NET_C(R27.2, Q7.B)
	NET_C(Q7.C, R36.1)
	NET_C(R36.2, C23.1, U12.5)
	NET_C(C33.1, GND)
	NET_C(U12.2, U12.6, D6.K, R45.1, C24.2)
	NET_C(U12.7, D6.A, R45.2, R44.1)
	NET_C(U12.3, C46.1)
	NET_C(C46.2, C45.1, R59.1)
	NET_C(C45.2, R72.2, U17.3)
	NET_C(R59.2, U17.2, U17.6, C57.1)
	NET_C(I_VM12, U17.4, C56.2)
	NET_C(C55.1, GND)
	NET_C(C57.2, R73.1)
	NET_C(D3.K, R46.1)
	NET_C(R46.2, R87.1, R80.2, R88.2, C66.1)
	NET_C(R73.2, R74.2, D8.K)
	NET_C(D8.A, R80.1, D9.A)
	NET_C(D9.K, R86.2, C65.1)
	NET_C(C65.2, R82.1)
	NET_C(R82.2, U18.2, R81.1)
	NET_C(R81.2, U18.6)
	NET_C(I_V12, U18.7, C59.2)
	NET_C(I_VM12, U18.4, C60.2)
	NET_C(C59.1, GND)
	ALIAS(BUZZZ, U18.6)

	//
	// Mixer
	//

#if (ENABLE_FRONTIERS)
	AFUNC(BOING_F, 1, "A0")
	NET_C(BOING, BOING_F.A0)
	NET_C(BOING_F.Q, R95.1)

	AFUNC(ZIP_F, 1, "A0")
	NET_C(ZIP, ZIP_F.A0)
	NET_C(ZIP_F.Q, R93.1)

	AFUNC(HOP_F, 1, "A0")
	NET_C(HOP, HOP_F.A0)
	NET_C(HOP_F.Q, R94.1)

	AFUNC(CROAK_F, 1, "A0")
	NET_C(CROAK, CROAK_F.A0)
	NET_C(CROAK_F.Q, R92.1)

	AFUNC(SPLASH_F, 1, "A0")
	NET_C(SPLASH, SPLASH_F.A0)
	NET_C(SPLASH_F.Q, R91.1)

	AFUNC(BUZZZ_F, 1, "A0")
	NET_C(BUZZZ, BUZZZ_F.A0)
	NET_C(BUZZZ_F.Q, R96.1)
#else
	NET_C(BOING, R95.1)
	NET_C(ZIP, R93.1)
	NET_C(HOP, R94.1)
	NET_C(CROAK, R92.1)
	NET_C(SPLASH, R91.1)
	NET_C(BUZZZ, R96.1)
#endif

	NET_C(R95.3, R93.3, R94.3, R92.3, R91.3, R96.3, R90.1)
	ALIAS(OUTPUT, R90.1)
	NET_C(R90.2, GND)

	//
	// Unconnected inputs
	//


	//
	// Unconnected outputs
	//

#if (ENABLE_FRONTIERS)
#define RXX 192
	OPTIMIZE_FRONTIER(BOING, RES_M(1), RXX)
#endif

NETLIST_END()
