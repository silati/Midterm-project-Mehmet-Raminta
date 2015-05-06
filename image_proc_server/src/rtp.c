#include "rtp.h"
static unsigned timestamp;

//RTP: start by sending packets
void rtp_send_packets(int sock, struct sockaddr_in* to, char *rtp_data,
unsigned long data_length, unsigned payload_size){
rtp_hdr* rtphdr;
char* rtp_payload;
unsigned long rtp_payload_size, rtp_data_index;
u_int8 *rtp_send_packet = (u_int8 *) malloc(payload_size + sizeof(rtp_hdr));

// defining RTP packet: flags, marker, timestamp, etc.
rtphdr = (rtp_hdr*) rtp_send_packet;
timestamp += 1000/30;
rtphdr->flags = RTP_VERSION;
rtphdr->mk_pt = RTP_PAYLOADTYPE;
rtphdr->ssrc = htonl(RTP_SSRC);
rtphdr->timestamp = htonl(ntohl(timestamp));

//RTP stream packet send-out
if (sendto(sock, rtp_send_packet, sizeof(rtp_hdr) + rtp_payload_size,
0, (struct sockaddr *)to, sizeof(struct sockaddr)) >= 0) {
rtphdr->seqNum = htons(ntohs(rtphdr->seqNum) + 1);
rtp_data_index += rtp_payload_size;
} else {
fprintf(stderr, "rtp_server: not sendto==%i\n", errno);
while (rtp_data_index < data_length);
free(rtp_send_packet);
}
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
}
