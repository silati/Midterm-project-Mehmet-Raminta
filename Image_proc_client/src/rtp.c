#include "rtp.h"
static unsigned timestamp;

// RTP: sending packets
void rtp_send_packets(int sock, struct sockaddr_in* to, char *rtp_data,
unsigned long data_length, unsigned payload_size){
rtp_hdr* rtphdr;
char* rtp_payload;
unsigned long rtp_payload_size, rtp_data_index;
u_int8 *rtp_send_packet = (u_int8 *) malloc(payload_size + sizeof(rtp_hdr));

// RTP: version, payload-type
rtphdr->flags = RTP_VERSION;
rtphdr->mk_pt = RTP_PAYLOADTYPE;
rtphdr->ssrc = htonl(RTP_SSRC);
rtphdr = (rtp_hdr*) rtp_send_packet;

timestamp += 1000/30;
rtphdr->timestamp = htonl(ntohl(timestamp));

rtp_data_index = 0;do {  //RTP: sending
rtp_payload = rtp_send_packet + sizeof(rtp_hdr);
memset(rtp_payload, 0, payload_size);
rtp_payload_size = MIN(payload_size , (data_length - rtp_data_index));
memcpy(rtp_payload, rtp_data + rtp_data_index, rtp_payload_size);
rtphdr->mk_pt = RTP_PAYLOADTYPE | (((rtp_data_index + rtp_payload_size)
>= data_length) ? RTP_MARKER_MASK : 0);

unsigned long rtp_recv_packets(int socket, unsigned char *data){
rtp_hdr* rtphdr;

struct sockaddr_in from;
int fromlen;
u_int64 received_num_bytes;
u_int32 recvrtppackets = 0;
u_int32 lostrtppackets = 0;
u_int16 lastrtpseq = 0;
u_int8 rtp_recv_packet[RTP_PACKET_SIZE];
long total_received_payload_bytes = 0;
	do {
fromlen = sizeof(from);
received_num_bytes = recvfrom(socket, rtp_recv_packet, sizeof(rtp_recv_packet), 0,
(struct sockaddr *)&from, (socklen_t *)&fromlen);
if (received_num_bytes >= sizeof(rtp_hdr)) {
rtphdr = (rtp_hdr *)rtp_recv_packet;
recvrtppackets++;
if ((lastrtpseq == 0) || ((lastrtpseq + 1) == ntohs(rtphdr->seqNum))) {
memcpy(data + total_received_payload_bytes, rtp_recv_packet + sizeof(rtp_hdr),
received_num_bytes);
total_received_payload_bytes += received_num_bytes - sizeof(rtp_hdr);
} else {
lostrtppackets++;
}
lastrtpseq = ntohs(rtphdr->seqNum);
if ((recvrtppackets % RTP_RECV_STATS) == 0) {
fprintf(stderr, "rtp_recv_thread: recv %6i packet(s) / lost %4i packet(s) (%.4f%%)...\n",
recvrtppackets, lostrtppackets, (lostrtppackets*100.0)/recvrtppackets);
}
} else {
fprintf(stderr, "rtp_recv_thread: recv timeout...\n");
return total_received_payload_bytes;
}
}while(!(rtphdr->mk_pt & RTP_MARKER_MASK)); //repeat until end marker is received
printf("[received]total_received_payload_bytes = %d\n",total_received_payload_bytes);
return total_received_payload_bytes;
return 0;
}
