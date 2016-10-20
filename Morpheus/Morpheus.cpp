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

#if _WIN64
#pragma comment (lib, "libusb64.lib")
#else
#pragma comment (lib, "libusb.lib")
#endif

#include "stdafx.h"
#include "morpheus.h"

#include "morpheus_bridge.h"
#include "morpheus_hostdef.h"
#include "morpheus_command.h"

#include "lusb0_usb.h"

// Some utility defines that the user doesn't need to care about
#define HID_REQ_GET_REPORT      0x01
#define HID_REQ_SET_REPORT      0x09

#define R_ID_CONFIGURE_VR_MODE 0x11
#define R_ID_SET_CONTROL_BOX_POWER 0x13
#define R_ID_SET_HEADSET_POWER 0x17

using namespace std;

static usb_dev_handle *open_dev(struct usb_device ** out_device, int iface)
{
	struct usb_bus *bus;
	struct usb_device *dev;

	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == MORPHEUS_VENDOR_ID
				&& dev->descriptor.idProduct == MORPHEUS_PRODUCT_ID)
			{
				for (int i = 0; i < (int)dev->config->bNumInterfaces; i++)
				{
					auto inter = &dev->config->interface[i];
					for (int j = 0; j < inter->num_altsetting; j++)
					{
						auto interdesc = &inter->altsetting[j];
						if (interdesc->bInterfaceNumber == iface)
						{
							*out_device = dev;
							return usb_open(dev);
						}
					}
				}
			}
		}
	}
	return NULL;
}

static usb_dev_handle * command_device, * sensor_device;

int morpheus_open_command()
{
	struct usb_device * devinfo;

	if (!(command_device = open_dev(&devinfo, MORPHEUS_COMMAND_INTERFACE)))
		return -1;

	if (usb_claim_interface(command_device, MORPHEUS_COMMAND_INTERFACE) < 0)
	{
		usb_close(command_device);
		return -1;
	}

	return 0;
}

void morpheus_close_command()
{
	usb_release_interface(command_device, MORPHEUS_COMMAND_INTERFACE);
	usb_close(command_device);

	command_device = NULL;
}

int morpheus_open_sensor()
{
	struct usb_device * devinfo;

	if (!(sensor_device = open_dev(&devinfo, MORPHEUS_SENSOR_INTERFACE)))
		return -1;

	if (usb_claim_interface(sensor_device, MORPHEUS_SENSOR_INTERFACE) < 0)
	{
		usb_close(sensor_device);
		return -1;
	}

	return 0;
}

void morpheus_close_sensor()
{
	usb_release_interface(sensor_device, MORPHEUS_SENSOR_INTERFACE);
	usb_close(sensor_device);

	command_device = NULL;
}

int morpheus_set_headset_power(int on)
{
	mbridge_ctrlcmd_in_packet pkt = { 0 };
	pkt.header.r_id = R_ID_SET_HEADSET_POWER;
	pkt.header.magic = 0xAA;
	pkt.header.length = 4;
	*(int*)pkt.payload = on;

	return usb_bulk_write(command_device, USB_ENDPOINT_OUT | MORPHEUS_COMMAND_ENDPOINT_SOURCE, (char*)&pkt, pkt.header.length + sizeof(pkt.header), 0);
}

int morpheus_reboot_headset()
{
	if (morpheus_set_headset_power(0) < 0)
		return -1;

	Sleep(5000);
	
	return morpheus_set_headset_power(1);
}

int morpheus_enable_vr_mode()
{
	mbridge_ctrlcmd_in_packet pkt = { 0 };
	pkt.header.r_id = R_ID_CONFIGURE_VR_MODE;
	pkt.header.magic = 0xAA;
	pkt.header.length = 8;
	((int*)pkt.payload)[0] = 0xFFFFFF00; // Magic numbers!  Turns on the VR mode and the blue lights on the front
	((int*)pkt.payload)[1] = 0x00000000;

	return usb_bulk_write(command_device, USB_ENDPOINT_OUT | MORPHEUS_COMMAND_ENDPOINT_SOURCE, (char*)&pkt, pkt.header.length + sizeof(pkt.header), 0);
}

int morpheus_disable_vr_mode()
{
	return morpheus_reboot_headset();
}

int morpheus_poll_sensors(morpheus_sensor_data * data)
{
	int sz = sizeof(morpheus_sensor_data);
	return usb_interrupt_read(sensor_device, USB_ENDPOINT_IN | MORPHEUS_SENSOR_ENDPOINT_SOURCE, (char*)data, sizeof(morpheus_sensor_data), 0);
}
