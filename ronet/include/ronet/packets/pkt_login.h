/* $Id$ */
/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of The Open Ragnarok Project
    Copyright 2007 - 2009 The Open Ragnarok Team
    For the latest information visit http://www.open-ragnarok.org
    ------------------------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any later
    version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
    ------------------------------------------------------------------------------------
*/
#ifndef __RONET_PACKET_LOGIN_H
#define __RONET_PACKET_LOGIN_H

#include "ronet/packet.h"

namespace ronet {

// S 0064 <version>.l <account name>.24B <password>.24B <version2>.B
// S 01dd <version>.l <account name>.24B <md5 binary>.16B <version2>.B
// S 0277 <version>.l <account name>.24B <password>.24B <junk?>.29B <version2>.B
// S 02b0 <version>.l <account name>.24B <password>.24B <junk?>.30B <version2>.B

	class RONET_DLLAPI pktLogin : public Packet {
	protected:
		unsigned int version;
		std::string username, password;
		unsigned char version2;


		virtual bool PrepareData();
	public:
		pktLogin();
		pktLogin(const std::string& user, const std::string& pass, unsigned int version);
	};
}

#endif /* __RONET_PACKET_LOGIN_H */
