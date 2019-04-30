/************************************************************************/
/* TinyOS2.x串口数据帧格式枚举类型                                      */
/************************************************************************/
enum {
		HDLC_QUEUESIZE		=2,
		HDLC_FLAG_BYTE		=0x7e,
		HDLC_CTLESC_BYTE	=0x7d,
		PROTO_ACK			=64,
		PROTO_PACKET_ACK	=65,
		PROTO_PACKET_NOACK	=66,
		PROTO_UNKNOWN		=255
};

enum {
	    RXSTATE_NOSYNC, //不是同步字
		RXSTATE_PROTO,  //协议类型
		RXSTATE_TOKEN,
		RXSTATE_INFO,
		RXSTATE_ESC
};

