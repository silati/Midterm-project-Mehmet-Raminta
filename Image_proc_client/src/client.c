#include "rtp.h"
#include "pbm.h"


#define DATA_SIZE 1000000 //Initialize the max Data(bytes) to be received

void getSum (int start, int end, unsigned char *data, int* des);
	unsigned char* readData(unsigned char *data, unsigned long length,
	struct image_header *ih);
		int main (int argc, const char * argv[]){
		int sock;

	struct sockaddr_in local;
		int timeout;
		unsigned long number_of_recv_bytes;
		unsigned char *data, *yuv444, *ycbcr;

	struct image_header ih;
		char con_rgbImg[] = "./received_img.pbm";
			

		if (argc != 2){
		printf("The usage is: %s <port>", argv[0]);
		exit(1);
		}

		data = (unsigned char *)malloc(DATA_SIZE);


	//It's time to create new socket!
	sock = socket(AF_INET, SOCK_DGRAM, 0); 
	if (sock >= 0){

	//Get local IP address
	if((sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == -1)
    	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[1]));
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	return 0;


	//Receive timeout
	timeout = RTP_RECV_TIMEOUT;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

	//Prepare local address
		memset(&local, 0, sizeof(local));
		local.sin_family      = AF_INET;
		local.sin_port        = htons(INADDR_ANY);
		local.sin_addr.s_addr = htonl(INADDR_ANY);

	//Bind to local address
		if (bind( sock, (struct sockaddr *)&local, sizeof(local))==0) {


	//Start receiving packets;
		number_of_recv_bytes = rtp_recv_packets(sock, data);
		}closesocket(sock) 			//Close the socket
	}

	//Receive the packet in the YUV444 format
	yuv444 = readData(data, number_of_recv_bytes, &ih);

	ycbcr = YUV442YCbCr(yuv444, ih); 		//YUV444 to YCbCr

	//YCbCr to RGB
	YCbCr2RGB(con_rgbImg, ycbcr, ih);
	free(data);
	free(yuv444);
	free(ycbcr);
	return 0;
	}

	
	// Image header *ih
	unsigned char* readData(unsigned char *data, unsigned long length, 
		struct image_header *ih){
			int i=3,k;
			unsigned char* yuv444;
			ih->format[0] = data[0];
			ih->format[1] = data[1];
			ih->format[2] = '\0';

		while(data[i] != 0x20) i++;
		getSum(3,i,data,&ih->rows);
		k = ++i;
		
		while(data[i] != 0x20) i++;
		getSum(k,i,data,&ih->cols);
		k = ++i;

		while(data[i]!= 0x20) i++;
		getSum(k,i++,data,&ih->levels);
		printf("[client]received_img header: %d\n %d\n %d\n, size: %d\n"
		{ih->cols, 
		ih->rows, 
		ih->levels, 
		length-i});

		unsigned char send_image(sock, &img_info, );
		yuv444 = (unsigned char*) malloc(DATA_SIZE);
		return 0;


}
