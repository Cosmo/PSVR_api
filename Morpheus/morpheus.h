/*
* Copyright (C) 2016 Nathan LeRoux
*
* This program is free software; you can redistribute  it and/or modify it
* under  the terms of  the GNU General  Public License as published by the
* Free Software Foundation;  version 2 of the  License.
*
* THIS  SOFTWARE  IS PROVIDED   ``AS  IS AND   ANY  EXPRESS OR IMPLIED
* WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
* NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
* USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* You should have received a copy of the  GNU General Public License along
* with this program; if not, write  to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#pragma once

#include <iostream>

enum MORPHEUS_BUTTONS : uint8_t
{
	VolumePlus = 2,
	VolumeMinus = 4,
	MicrophoneMute = 8,
};

#pragma pack(1)
struct morpheus_sensor_data
{
	MORPHEUS_BUTTONS buttons;
	uint8_t unk0;
	uint8_t volume;
	uint8_t unk1[5];
	union
	{
		uint8_t asByte;
		struct
		{
			uint8_t unk0 : 2;
			uint8_t HDMIDisconnected : 1;
			uint8_t microphoneMuted : 1;
			uint8_t headphonesPresent : 1;
			uint8_t unk1 : 2;
			uint8_t timer : 1;
		};
	} headsetState;

	uint8_t flags;

	uint16_t unk2[4];

	short frame;
	struct
	{
		struct
		{
			short x, y, z;
		} accelerometer;

		struct
		{
			short x, y, z;
		} gyroscope;
	} sensorFrames[2];

	int unk4[5];
};
#pragma pack()

// All routines return negative values on failure

// Open/close the command channel over USB
int morpheus_open_command();
void morpheus_close_command();

// Open/close the sensor channel over USB
int morpheus_open_sensor();
void morpheus_close_sensor();

// Power the PSVR headset on or off
int morpheus_set_headset_power(int on);

// Power the PSVR headset off, wait 5 seconds, power it back on
int morpheus_reboot_headset();

// Enable VR mode, which splits the eyes, and presumably activates the box's magical 120Hz thing.
// I have no idea if it really does though, as I can't see framerates that high.
int morpheus_enable_vr_mode();

// This just calls morpheus_reboot_headset, because I'm lazy and don't feel like figuring out how to do this without restarting the headset
int morpheus_disable_vr_mode();

int morpheus_poll_sensors(morpheus_sensor_data * data);
