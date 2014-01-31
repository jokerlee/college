/* ================================================
 * Protocol 6 : Selective repeat 
 * Vim empowerd
 * Name : Joker Lee 
 * Class : 07409
 * ID : 071202
 * Email : jokerleee@gmail.com
 * Date : Nov 20 2009
 * =============================================== */

/*
 * put_frame  : to_physical_layer 
 * recv_frame : from_pysical_layer
 * get_packet : from_network_layer
 * put_packet : to_network_layer
*/

/*
Situation when MAX_SEQ = 7
     ack_expected   next_frame_to_send
               |           |
               v           v
     +===+===+===+===+===+===+===+===+
     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
     +===+===+===+===+===+===+===+===+
           ^           ^
           |           | 
    frame_expected  too_far

outbound stream buffer : 
    +===+===+===+===+
    | 4 | 5 | 2 | 3 |
    +===+===+===+===+
      0   1   2   3

inbound stream buffer : 
    +===+===+===+===+
    | 4 | 1 | 2 | 3 |
    +===+===+===+===+
      0   1   2   3


*/


#include <stdio.h>
#include <string.h>

#include "protocol.h"
#include "datalink.h"


#define MAX_SEQ 7
#define NR_BUFS ((MAX_SEQ + 1)/2)

#define DATA_TIMER  3000
#define ACK_TIMER 800


/*=================== Global Variable Definations ===================*/ 

struct FRAME { 
    unsigned char kind; /* FRAME_DATA */
    unsigned char ack;
    unsigned char seq;
    unsigned char data[PKT_LEN]; 
    unsigned int  padding; // room for the 4 bytes CRC code
};

typedef unsigned char seq_nr;
typedef int frame_kind;

static seq_nr next_frame_to_send = 0, // upper bound of sender's window + 1 
              ack_expected = 0, // lower bound of sender's window
              too_far = NR_BUFS, // upper bound of receiver's window +1
              frame_expected = 0, // lower bound of receiver's window
              nbuffered = 0;
              
static char in_buf[NR_BUFS][PKT_LEN], /* buffers for inbound stream*/
            out_buf[NR_BUFS][PKT_LEN]; /* buffers for outbound stream */
static char arrived[NR_BUFS] = {0}; /* bitmap for inbound buffer */
static int phl_ready = 0; /* physical layer ready */
static int no_nak = 1; // flag variable to make sure at most 1 NAK each frame

/*================ End of Global Variable Dfinations ================*/ 


static void inc(unsigned char * num)
{
    *num = (*num + 1)%(MAX_SEQ + 1);
}

static int between(seq_nr a, seq_nr b, seq_nr c)
{
    return (((a <= b) && (b < c)) || ((c < a) && (a <= b))
         || ((b < c) && (c < a)));
}

static void put_frame(seq_nr * frame, int len)
{
    *(unsigned int *)(frame + len) = crc32(frame, len);
    send_frame(frame, len + 4); // The last 4 bytes are the CRC code
    phl_ready = 0;
}

static void send_data_frame(seq_nr frame_nr)
{
    struct FRAME s;

    s.kind = FRAME_DATA;
    s.seq = frame_nr;
    s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
    
    memcpy(s.data, out_buf[frame_nr % NR_BUFS], PKT_LEN);

    dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short *)s.data);

    put_frame((unsigned char *)&s, 3 + PKT_LEN); // the extra 3 bytes are ack,kind,seq
    start_timer(frame_nr % NR_BUFS, DATA_TIMER);
    stop_ack_timer();
}

static void send_nak_frame(void)
{
    struct FRAME s;

    s.kind = FRAME_NAK;
    s.seq = 0;
    s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1); // s.ack = frame_expected - 1
    no_nak = 0;
    dbg_frame("Send NAK  %d\n", s.ack);

    put_frame((unsigned char *)&s, 3);
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

int main(int argc, char **argv)
{
    int event, arg;
    struct FRAME r;
    int len = 0; 
    int i;

    protocol_init(argc, argv); 
    lprintf("Designed by JackalDire\n");

    for (i = 0; i <= MAX_SEQ; ++i)
        arrived[i] = 0;

    disable_network_layer();

    for (;;) {
        event = wait_for_event(&arg);

        switch (event) {
        case NETWORK_LAYER_READY:
            get_packet(out_buf[next_frame_to_send % NR_BUFS]); // fetch new packet from physical layer
            ++nbuffered;
            send_data_frame(next_frame_to_send);
            inc(&next_frame_to_send);
            break;

        case PHYSICAL_LAYER_READY:
            phl_ready = 1;
            break;

        case FRAME_RECEIVED: 
            len = recv_frame((unsigned char *)&r, sizeof r);
            if (len < 5 || crc32((unsigned char *)&r, len) != 0) {
                dbg_event("**** receiver error, bad CRC checksum, packet discarded.\n");
                /* discard the error packet with wrong crc checksum,
                 * and send a NAK frame to request a repeat */
                if (no_nak) send_nak_frame();
                break;
            }

            if (r.kind == FRAME_ACK)
                dbg_frame("Recv ACK  %d\n", r.ack);
            
            if (r.kind == FRAME_NAK) {
                dbg_frame("Recv NAK  %d\n", r.ack);
                /* resend the frame ask by NAK if the ack's value is in the sender's window */
                if (between(ack_expected, (r.ack+1) % (MAX_SEQ+1), next_frame_to_send))
                    send_data_frame((r.ack + 1) % (MAX_SEQ + 1));
            }
            
            if (r.kind == FRAME_DATA) {
                dbg_frame("Recv DATA %d %d, ID %d\n", r.seq, r.ack, *(short *)r.data);
                if (r.seq != frame_expected && no_nak) 
                    send_nak_frame();
                else
                    start_ack_timer(ACK_TIMER);
                /* if this frame is in the receiver's window */
                if (between(frame_expected, r.seq, too_far) 
                        && arrived[r.seq % NR_BUFS] == 0) {
                    /* put this frame into the inbound stream window */
                    arrived[r.seq % NR_BUFS] = 1;
                    memcpy(in_buf[r.seq % NR_BUFS], r.data, PKT_LEN);
                    /* check from the bottom of receiver's buffer, transmit them  
                     to the network layer if the buffer is not empty */
                    while (arrived[frame_expected % NR_BUFS]) {
                        dbg_event("push DATA %d, ID %d\n", frame_expected, *(short *)(&in_buf[frame_expected % NR_BUFS]));
                        put_packet(in_buf[frame_expected % NR_BUFS], PKT_LEN);
                        no_nak = 1;
                        arrived[frame_expected % NR_BUFS] = 0;
                        inc(&frame_expected);
                        inc(&too_far);
                        start_ack_timer(ACK_TIMER);
                    }
                }
            }
            
            /* Acknowledged the former frames */
            while (between(ack_expected, r.ack, next_frame_to_send)) {
                --nbuffered;
                stop_timer(ack_expected % NR_BUFS);
                inc(&ack_expected);
            }
            break; 

        case DATA_TIMEOUT:
            dbg_event("---- DATA timeout, %d\n", arg); 
            
            send_data_frame(arg + ack_expected);
            break;
        
        case ACK_TIMEOUT:
            dbg_event("---- ACK %d timeout\n", arg);
            /* send a separate ACK frame if there is no outbound stream for a specific time */
            send_ack_frame();
        }
        
        if (nbuffered < NR_BUFS && phl_ready)
            enable_network_layer();
        else
            disable_network_layer();

        //dbg_event("frame_exp:%d, too_far:%d, ack_exp:%d, next:%d, buf:%d\n", 
        //        frame_expected, too_far, ack_expected, next_frame_to_send, nbuffered); 
   }
}



/* thank you for reading the f*cking source code*/
