// license:BSD-3-Clause
// copyright-holders:Aaron Giles

#ifndef MAME_SOUND_YM2608_H
#define MAME_SOUND_YM2608_H

#pragma once

#include "ymfm_mame.h"
#include "ymfm_opn.h"
#include "dirom.h"


// ======================> ym2608_device

DECLARE_DEVICE_TYPE(YM2608, ym2608_device);

class ym2608_device : public ymfm_ssg_device_base<ymfm::ym2608>, public device_rom_interface<21>
{
public:
	// constructor
	ym2608_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// configuration helpers, handled by the interface
	auto port_a_read_callback() { return io_read_handler(0); }
	auto port_b_read_callback() { return io_read_handler(1); }
	auto port_a_write_callback() { return io_write_handler(0); }
	auto port_b_write_callback() { return io_write_handler(1); }

	// additional register reads
	u8 data_r() { return update_streams().read_data(); }
	u8 status_hi_r() { return update_streams().read_status_hi(); }
	u8 data_hi_r() { return update_streams().read_data_hi(); }

	// additional register writes
	void address_hi_w(u8 data) { update_streams().write_address_hi(data); }
	void data_hi_w(u8 data) { update_streams().write_data_hi(data); }

protected:
	// device-level overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

	// ROM device overrides
	virtual void rom_bank_updated() override;

private:
	// ADPCM read/write callbacks
	virtual uint8_t ymfm_adpcm_a_read(uint32_t address) override;
	virtual uint8_t ymfm_adpcm_b_read(uint32_t address) override;
	virtual void ymfm_adpcm_b_write(uint32_t address, u8 data) override;

	// internal state
	required_memory_region m_internal; // internal memory region
};

#endif // MAME_SOUND_YM2608_H
