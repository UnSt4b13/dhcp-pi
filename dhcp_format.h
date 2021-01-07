
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
