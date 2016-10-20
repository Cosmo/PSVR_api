/*
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
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

#ifndef _SIE_BRIDGE_H_
#define _SIE_BRIDGE_H_

//----------------------------------------------------------------------------
/* Compiler switch flags */
//#define ENABLE_MBRIDGE_DEBUG

//----------------------------------------------------------------------------

/* Definitions for the device descriptors. */
#define MORPHEUS_VENDOR_ID      0x054c
#define MORPHEUS_PRODUCT_ID     0x09af
#define MORPHEUS_DFU_PRODUCT_ID 0x09b0

/* Changing from 0x0106 to 0x0107, due to Bug #125981. */
#define MORPHEUS_BCDDEVICE      0x0107
#define MORPHEUS_DFU_BCDDEVICE  0x0107

// interface numbers exported to the device descriptor
enum mbridge_interface_no {
	MORPHEUS_AUDIO3D_INTERFACE = 0,
	MORPHEUS_CONTROL_INTERFACE = 1,
	MORPHEUS_MIC_INTERFACE = 2,
	MORPHEUS_CHAT_INTERFACE = 3,
	MORPHEUS_SENSOR_INTERFACE = 4,
	MORPHEUS_COMMAND_INTERFACE = 5,
	MORPHEUS_SOCIALFEED_INTERFACE = 6,
	MORPHEUS_BULKIN_INTERFACE = 7,
	MORPHEUS_AUTHENTICATION_INTERFACE = 8, // must be last
	MORPHEUS_NUM_INTERFACES,
};
// for DFU mode
enum mbridge_dfu_interface_no {
	MORPHEUS_DFU_COMMAND_INTERFACE = 0,
	MORPHEUS_DFU_INTERFACE = 1,
	MORPHEUS_NUM_DFU_INTERFACES,
};

// string descriptor
#define MORPHEUS_MANUFACTURER                  "Sony"
// (R) mark U+00AE in UTF-8 is 0xc2 0xae
#define MORPHEUS_PRODUCT                       "PlayStation\xc2\xaeVR"

// MORPHEUS_AUDIO3D_INTERFACE #0
#define MORPHEUS_AUDIO3D_INTERFACE_NAME         "PS VR 3D Audio"
#define MORPHEUS_AUDIO3D_ENDPOINT_SINK          0x01

// MORPHEUS_CONTROL_INTERFACE #1
#define MORPHEUS_CONTROL_INTERFACE_CLASS        0x01
#define MORPHEUS_CONTROL_INTERFACE_NAME         "PS VR Audio"
#define MORPHEUS_CONTROL_ENDPOINT_SOURCE        0

// MORPHEUS_MIC_INTERFACE #2
#define MORPHEUS_MIC_INTERFACE_CLASS            0x01
#define MORPHEUS_MIC_INTERFACE_NAME             "PS VR Audio Mic"
#define MORPHEUS_MIC_ENDPOINT_SOURCE            0x02

// MORPHEUS_CHAT_INTERFACE #3
#define MORPHEUS_CHAT_INTERFACE_CLASS           0x01
#define MORPHEUS_CHAT_INTERFACE_NAME            "PS VR Audio Chat"
#define MORPHEUS_CHAT_ENDPOINT_SINK             0x02

// MORPHEUS_SENSOR_INTERFACE #4
#define MORPHEUS_SENSOR_INTERFACE_CLASS         3
#define MORPHEUS_SENSOR_INTERFACE_NAME          "PS VR Sensor"
#define MORPHEUS_SENSOR_ENDPOINT_SOURCE         0x03

// MORPHEUS_COMMAND_INTERFACE #5
// MORPHEUS_DFU_COMMAND_INTERFACE #0
#define MORPHEUS_COMMAND_INTERFACE_CLASS        3
#define MORPHEUS_COMMAND_INTERFACE_NAME         "PS VR Control"
#define MORPHEUS_COMMAND_ENDPOINT_SINK          0x04
#define MORPHEUS_COMMAND_ENDPOINT_SOURCE        0x04

// MORPHEUS_SOCIALFEED_INTERFACE #6
#define MORPHEUS_SOCIALFEED_INTERFACE_NAME      "PS VR H.264"
#define MORPHEUS_SOCIALFEED_ENDPOINT_SINK       0x05
#define MORPHEUS_SOCIALFEED_USE_ISOC

// MORPHEUS_AUTHENTICATION_INTERFACE #8
#define MORPHEUS_AUTHENTICATION_INTERFACE_CLASS     0x03
#define MORPHEUS_AUTHENTICATION_INTERFACE_NAME      "PS VR Control2"
#define MORPHEUS_AUTHENTICATION_ENDPOINT_SINK       0x06
#define MORPHEUS_AUTHENTICATION_ENDPOINT_SOURCE     0x06

// MORPHEUS_DFU_INTERFACE
#define MORPHEUS_DFU_INTERFACE_NAME             "PS VR DFU"
#define MORPHEUS_DFU_ENDPOINT_SINK              0x05

// MORPHEUS_BULKIN_INTERFACE #7
#define MORPHEUS_BULKIN_INTERFACE_NAME          "PS VR BulkIn"
#define MORPHEUS_BULKIN_ENDPOINT_SOURCE         0x07

//----------------------------------------------------------------------------

/* String indexes. */
#define STRING_MANUFACTURER_IDX      0
#define STRING_PRODUCT_IDX           1
#define STRING_AUDIO3D_IDX           2
#define STRING_CONTROL_IDX           3
#define STRING_MIC_IDX               4
#define STRING_CHAT_IDX              5
#define STRING_SENSOR_IDX            6
#define STRING_COMMAND_IDX           7
#define STRING_SOCIALFEED_IDX        8
#define STRING_AUTHENTICATION_IDX    9
#define STRING_BULKIN_IDX           10

#define STRING_SERIAL_IDX           11 // unused so far
#define STRING_CONFIG_IDX           12 //     "

// DFU mode
#define STRING_DFU_COMMAND_IDX       2
#define STRING_DFU_IDX               3

//----------------------------------------------------------------------------
#endif
