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

#include "stdafx.h"
#include "lusb0_usb.h"
#include "morpheus.h"

void initialize_usb()
{
	usb_init(); /* initialize the library */
	usb_set_debug(3); //set verbosity level to 3, as suggested in the documentation

	usb_find_busses(); /* find all busses */
	usb_find_devices(); /* find all connected devices */
}

int main()
{
	initialize_usb();

	if (morpheus_open_command() < 0 || morpheus_open_sensor() < 0)
		return 0;

	morpheus_set_headset_power(1);

	/*
	for (;;)
	{
		morpheus_sensor_data data;
		morpheus_poll_sensors(&data);

		printf("%5i %5i %5i\n%5i %5i %5i\n\n",
			data.sensorFrames[0].accelerometer.x, data.sensorFrames[0].accelerometer.y, data.sensorFrames[0].accelerometer.z,
			data.sensorFrames[0].gyroscope.x, data.sensorFrames[0].gyroscope.y, data.sensorFrames[0].gyroscope.z);

		Sleep(100);
	}*/

	morpheus_enable_vr_mode();

	morpheus_disable_vr_mode();

	morpheus_set_headset_power(0);

	morpheus_close_command();
	morpheus_close_sensor();

	return 0;
}