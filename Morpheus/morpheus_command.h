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

#pragma once

/* mbridge PS4 Command */

#define MBRIDGE_CTRLCMD_OUT_MAX_LEN (64)
#define MBRIDGE_CTRLCMD_MAX_PAYLOAD_LEN (60)

#pragma pack(1)
struct mbridge_cmd_status
{
	uint8_t r_id;
	uint8_t command_status;
	uint8_t magic;
	uint8_t length;
};

struct mbridge_ctrlcmd_out_packet
{
	struct mbridge_cmd_status header;
	uint8_t payload[MBRIDGE_CTRLCMD_MAX_PAYLOAD_LEN];
};

struct mbridge_cmd_command
{
	uint8_t r_id;
	uint8_t command_status;
	uint8_t magic;
	uint8_t length;
};

struct mbridge_ctrlcmd_in_packet
{
	struct mbridge_cmd_command header;
	uint8_t payload[MBRIDGE_CTRLCMD_MAX_PAYLOAD_LEN];
};

struct mbridge_ctrlcmd_report
{
	struct mbridge_ctrlcmd_out_packet packet;
	uint8_t packet_length;
};

#pragma pack()
