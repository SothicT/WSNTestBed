/************************************************************************/
/* TinyOS2.x��������֡��ʽö������                                      */
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
	    RXSTATE_NOSYNC, //����ͬ����
		RXSTATE_PROTO,  //Э������
		RXSTATE_TOKEN,
		RXSTATE_INFO,
		RXSTATE_ESC
};

