/* ================================================
 * Protocol 5 : Go Back N
 * Vim empowerd
 * Name : Joker Lee 
 * Class : 07409
 * ID : 071202
 * Email : jokerleee@gmail.com
 * Date : Nov 20 2009
 * =============================================== */

/*
 * put_frame : to_physical_layer 
 * recv_frame : from_pysical_layer
 * get_packet : from_network_layer
 * put_packet : to_network_layer
*/


#include <stdio.h>
#include <string.h>

#include "protocol.h"
#include "datalink.h"


#define MAX_SEQ 15

#define DATA_TIMER  1200
#define ACK_TIMER   600



/*=================== Global Variable Definations ===================*/ 

typedef unsigned char seq_nr;

struct FRAME { 
    unsigned char kind; /* FRAME_DATA */
    seq_nr ack;
    seq_nr seq;
    unsigned char data[PKT_LEN]; 
    unsigned int  padding; /* make room for 4 bytes CRC code */
};


static seq_nr next_frame_to_send = 0, 
              nbuffered = 0, // count of outstream buffer
              frame_expected = 0, 
              ack_expected = 0, // oldest frame as yet unacknowledged
              buffer[MAX_SEQ+1][PKT_LEN]; // buffer for outstream
static int phl_ready = 0; /* physical layer ready */


/*================ End of Global Variable Dfinations ================*/ 


static void inc(unsigned char * num)
{
    *num = (*num + 1) % MAX_SEQ;
}

/* return 1 if a <= b < c cicularly, 0 otherwise */
static int between(seq_nr a, seq_nr b, seq_nr c)
{
    if (((a <= b) && (b < c)) || ((c < a) && (a <= b))
         || ((b < c) && (c < a)))
        return 1;
    else return 0;
}

static void put_frame(seq_nr * frame, int len)
{
    *(unsigned int *)(frame + len) = crc32(frame, len);
    send_frame(frame, len + 4); // The last 4 bytes are the CRC code
    phl_ready = 0;
}

static void send_data_frame(void)
{
    struct FRAME s;

    s.kind = FRAME_DATA;
    s.seq = next_frame_to_send;
    s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
    memcpy(s.data, buffer[next_frame_to_send], PKT_LEN);

    dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short *)s.data);

    put_frame((unsigned char *)&s, 3 + PKT_LEN); // the extra 3 bytes are ack,kind,seq
    start_timer(next_frame_to_send, DATA_TIMER);
    stop_ack_timer();
}


static void send_ack_frame(void)
{
    struct FRAME s;

    s.kind = FRAME_ACK;
    s.ack = (frame_expected + MAX_SEQ)%(MAX_SEQ + 1);

    dbg_frame("Send ACK  %d\n", s.ack);

    put_frame((unsigned char *)&s, 3);
    stop_ack_timer();
}


int main(int argc, char ** argv)
{
    int event, arg;
    struct FRAME r;
    int len = 0; 
    int i;

    protocol_init(argc, argv); 
    lprintf("Designed by JackalDire\n");

    disable_network_layer();

    for (;;) {
        event = wait_for_event(&arg);

        switch (event) {
        case NETWORK_LAYER_READY:
            get_packet(buffer[next_frame_to_send]); // fetch new packet from physical layer
            nbuffered++;
            send_data_frame();
            inc(&next_frame_to_send);
            break;

        case PHYSICAL_LAYER_READY:
            phl_ready = 1;
            break;

        case FRAME_RECEIVED: 
            len = recv_frame((unsigned char *)&r, sizeof r);
            if (len < 5 || crc32((unsigned char *)&r, len) != 0) {
                /* discard the error packet with wrong crc checksum  */
                /* TODO : add NAK to  accelerate resending */
                dbg_event("**** receiver error, bad CRC checksum, packet discarded.\n");
                break;
            }

            if (r.kind == FRAME_DATA) {
                dbg_frame("Recv DATA %d %d, ID %d\n", r.seq, r.ack, *(short *)r.data);
                if (r.seq == frame_expected) {
                    /* transmit the receive packet to network layer */
                    put_packet(r.data, PKT_LEN); // 7 = 3B other fields + 4B crc code
                    inc(&frame_expected);
                    start_ack_timer(ACK_TIMER);
                }
            }
            /* ACK n means packets earlier than n were received correctly,
             * so make packet ack_expeced ~ r.ack acknowledged */ 
            while (between(ack_expected, r.ack, next_frame_to_send)) {
                --nbuffered;
                stop_timer(ack_expected);
                inc(&ack_expected);
            }
            break; 

        case DATA_TIMEOUT:
            dbg_event("---- DATA %d timeout\n", arg); 
            next_frame_to_send = ack_expected;
            /* retransmit all packets in the buffer when timeout */ 
            for (i = 1; i <= nbuffered; ++i) {
                send_data_frame();
                inc(&next_frame_to_send);
            }
            break;
        
        
        case ACK_TIMEOUT:
            /* send a separate ACK frame if there is no outstream for a specific time */
            dbg_event("---- ACK %d timeout\n", arg);
            send_ack_frame();
        }
        
        /* disable networklayer when outstrem buffer if full */
        if (nbuffered < MAX_SEQ && phl_ready)
            enable_network_layer();
        else
            disable_network_layer(); 
   }
}

/* this is the end, no more, thank godness !*/
