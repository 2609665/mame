// license:BSD-3-Clause
// copyright-holders:Aaron Giles

#ifndef MAME_SOUND_Y8950_H
#define MAME_SOUND_Y8950_H

#pragma once

#include "ymfm_mame.h"
#include "ymfm/src/ymfm_opl.h"
#include "dirom.h"


// ======================> y8950_device

DECLARE_DEVICE_TYPE(Y8950, y8950_device);

class y8950_device : public ymfm_device_base<ymfm::y8950>, public device_rom_interface<21>
{
public:
	// constructor
	y8950_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// configuration helpers
	auto io_read() { return io_read_handler(0); }
	auto io_write() { return io_write_handler(0); }
	auto keyboard_read() { return io_read_handler(1); }
	auto keyboard_write() { return io_write_handler(1); }

	// additional register reads
	u8 data_r() { return update_streams().read_data(); }

protected:
	// ROM device overrides
	virtual void rom_bank_updated() override;

private:
	// ADPCM read/write callbacks
	uint8_t ymfm_adpcm_b_read(offs_t address) override;
	void ymfm_adpcm_b_write(offs_t address, uint8_t data) override;
};


#endif // MAME_SOUND_Y8950_H
