
struct dhcphdr
{
	uint8_t op;
	uint8_t type;
	uint8_t length;
	uint8_t hops;
	uint32_t xid;
	uint16_t seconds;
	uint16_t flags;
	uint32_t ciaddr;
	uint32_t yiaddr;
	uint32_t siaddr;
	uint32_t giaddr;
	unsigned char chaddr[16];
	char sname[64];
	char filename[128];
	unsigned char options[312];	
};

int get_msg_type(struct dhcphdr *dhcp)
{
	int index = 5;
	int end = 0;
	int found = 0;
	int msg_type = 0;
	int length = 0;

	while(!found && !end)
	{
		length = dhcp->options[index + 1];

		switch(dhcp->options[index])
		{
			case 0xff:
				end = 1;
				break;
			case 0x35:
				msg_type = dhcp->options[index + length];
				found = 1;
				break;
			default:
				index += (length + 2);
		}
	}

	return msg_type;

}
