// license:BSD-3-Clause
// copyright-holders:AJR
/****************************************************************************

    Skeleton driver for Roland R-8 drum machine.

****************************************************************************/

#include "emu.h"
#include "cpu/upd78k/upd78k2.h"

class roland_r8_state : public driver_device
{
public:
	roland_r8_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
	{
	}

	void r8(machine_config &config);
	void r8mk2(machine_config &config);

private:
	void mem_map(address_map &map);

	required_device<upd78k2_device> m_maincpu;
};


void roland_r8_state::mem_map(address_map &map)
{
	map(0x00000, 0x1ffff).rom().region("maincpu", 0);
}


static INPUT_PORTS_START(r8)
INPUT_PORTS_END


void roland_r8_state::r8(machine_config &config)
{
	UPD78210(config, m_maincpu, 12_MHz_XTAL);
	m_maincpu->set_addrmap(AS_PROGRAM, &roland_r8_state::mem_map);
}

void roland_r8_state::r8mk2(machine_config &config)
{
	UPD78213(config, m_maincpu, 12_MHz_XTAL);
	m_maincpu->set_addrmap(AS_PROGRAM, &roland_r8_state::mem_map);
}


ROM_START(r8)
	ROM_REGION(0x20000, "maincpu", 0)
	ROM_LOAD("roland r-8_2.02_27c010.bin", 0x00000, 0x20000, CRC(45d0f64f) SHA1(55f0831db74cbdeae20cd7f1ff28af27dafba9b9))
ROM_END

ROM_START(r8m)
	ROM_REGION(0x20000, "maincpu", 0)
	ROM_LOAD("rolandr8mv104.bin", 0x00000, 0x20000, CRC(5e95e2f6) SHA1(b4e1a8f15f72a9db9aa8fd41ee3c3ebd10460587))
ROM_END

ROM_START(r8mk2)
	ROM_REGION(0x20000, "maincpu", 0)
	ROM_LOAD("roland r8 mkii eprom v1.0.3.bin", 0x00000, 0x20000, CRC(128a9a0c) SHA1(94bd8c76efe270754219f2899f31b62fc4f9060d))
ROM_END


SYST(1989, r8,    0,  0, r8,    r8, roland_r8_state, empty_init, "Roland", "R-8 Human Rhythm Composer (v2.02)", MACHINE_IS_SKELETON)
SYST(1990, r8m,   r8, 0, r8,    r8, roland_r8_state, empty_init, "Roland", "R-8M Total Percussion Sound Module (v1.04)", MACHINE_IS_SKELETON)
SYST(1992, r8mk2, 0,  0, r8mk2, r8, roland_r8_state, empty_init, "Roland", "R-8 Mk II Human Rhythm Composer (v1.0.3)", MACHINE_IS_SKELETON)
