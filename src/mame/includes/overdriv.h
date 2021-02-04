// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/*************************************************************************

    Over Drive

*************************************************************************/
#ifndef MAME_INCLUDES_OVERDRIV_H
#define MAME_INCLUDES_OVERDRIV_H

#pragma once

#include "machine/k053252.h"
#include "machine/timer.h"
#include "video/k051316.h"
#include "video/k053246_k053247_k055673.h"
#include "video/k053251.h"
#include "video/konami_helper.h"
#include "screen.h"

class overdriv_state : public driver_device
{
public:
	overdriv_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_subcpu(*this, "sub")
		, m_audiocpu(*this, "audiocpu")
		, m_k051316_1(*this, "k051316_1")
		, m_k051316_2(*this, "k051316_2")
		, m_k053246(*this, "k053246")
		, m_k053251(*this, "k053251")
		, m_k053252(*this, "k053252")
		, m_screen(*this, "screen")
		, m_led(*this, "led0")
	{ }

	void overdriv(machine_config &config);

private:
	void eeprom_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void cpuA_ctrl_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	uint16_t cpuB_ctrl_r();
	void cpuB_ctrl_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void overdriv_soundirq_w(uint16_t data);
	void sound_ack_w(uint8_t data);
	void slave_irq4_assert_w(uint16_t data);
	void slave_irq5_assert_w(uint16_t data);
	void objdma_w(uint8_t data);
	TIMER_CALLBACK_MEMBER(objdma_end_cb);

	uint32_t screen_update_overdriv(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	//INTERRUPT_GEN_MEMBER(cpuB_interrupt);
	TIMER_DEVICE_CALLBACK_MEMBER(overdriv_cpuA_scanline);

	K051316_CB_MEMBER(zoom_callback_1);
	K051316_CB_MEMBER(zoom_callback_2);
	K053246_CB_MEMBER(sprite_callback);
	void overdriv_master_map(address_map &map);
	void overdriv_slave_map(address_map &map);
	void overdriv_sound_map(address_map &map);


	virtual void machine_start() override;
	virtual void machine_reset() override;

	/* video-related */
	int       m_zoom_colorbase[2];
	int       m_road_colorbase[2];
	int       m_sprite_colorbase;
	emu_timer *m_objdma_end_timer;

	/* misc */
	uint16_t     m_cpuB_ctrl;

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_subcpu;
	required_device<cpu_device> m_audiocpu;
	required_device<k051316_device> m_k051316_1;
	required_device<k051316_device> m_k051316_2;
	required_device<k053247_device> m_k053246;
	required_device<k053251_device> m_k053251;
	required_device<k053252_device> m_k053252;
	required_device<screen_device> m_screen;
	output_finder<> m_led;
	int m_fake_timer;
};

#endif // MAME_INCLUDES_OVERDRIV_H
