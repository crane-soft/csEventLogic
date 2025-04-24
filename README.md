# csEventLogic
## Event driven logic simulator

This is a proof of concept for an event-driven logic simulator suitable for accurate timing simulation of asynchronous logic designs such as ripple counters or RS flip-flops. 
In a first step, three logic cells were implemented
- Clock Source, 
- AND Gate, 
- Toggle flip-flop).

connected to a ripple counter with counter reset.

![LogicSim](https://github.com/user-attachments/assets/42229567-250b-4954-b9c9-cdb37baa0195)

For every event the simulator generates a log line with:  
EV: time[ns] , Outputs which has changed and the status of all outputs Q3,Q2,Q1,Q0 AND.y

```
EV:  50  CLK.Y=1 0000 0
EV: 100  CLK.Y=0 0000 0
EV: 109 TFF1.Q=1 0001 0
EV: 150  CLK.Y=1 0001 0
EV: 200  CLK.Y=0 0001 0
EV: 209 TFF1.Q=0 0000 0
EV: 218 TFF2.Q=1 0010 0
EV: 250  CLK.Y=1 0010 0
EV: 300  CLK.Y=0 0010 0
EV: 309 TFF1.Q=1 0011 0
EV: 350  CLK.Y=1 0011 0
EV: 400  CLK.Y=0 0011 0
EV: 409 TFF1.Q=0 0010 0
EV: 418 TFF2.Q=0 0000 0
EV: 427 TFF3.Q=1 0100 0
EV: 432  AND.Y=0 0100 0
EV: 450  CLK.Y=1 0100 0
EV: 500  CLK.Y=0 0100 0
EV: 509 TFF1.Q=1 0101 0
EV: 550  CLK.Y=1 0101 0
EV: 600  CLK.Y=0 0101 0
EV: 609 TFF1.Q=0 0100 0
EV: 618 TFF2.Q=1 0110 0
EV: 650  CLK.Y=1 0110 0
EV: 700  CLK.Y=0 0110 0
EV: 709 TFF1.Q=1 0111 0
EV: 750  CLK.Y=1 0111 0
EV: 800  CLK.Y=0 0111 0
EV: 809 TFF1.Q=0 0110 0
EV: 818 TFF2.Q=0 0100 0
EV: 827 TFF3.Q=0 0000 0
EV: 836 TFF4.Q=1 1000 0
EV: 850  CLK.Y=1 1000 0
EV: 900  CLK.Y=0 1000 0
EV: 909 TFF1.Q=1 1001 0
EV: 950  CLK.Y=1 1001 0
EV:1000  CLK.Y=0 1001 0
EV:1009 TFF1.Q=0 1000 0
EV:1018 TFF2.Q=1 1010 0
EV:1050  CLK.Y=1 1010 0
EV:1100  CLK.Y=0 1010 0
EV:1109 TFF1.Q=1 1011 0
EV:1150  CLK.Y=1 1011 0
EV:1200  CLK.Y=0 1011 0
EV:1209 TFF1.Q=0 1010 0
EV:1218 TFF2.Q=0 1000 0
EV:1227 TFF3.Q=1 1100 0
EV:1232  AND.Y=1 1100 1
EV:1237 TFF3.Q=0 1000 1
EV:1237 TFF4.Q=0 0000 1
EV:1242  AND.Y=0 0000 0
EV:1250  CLK.Y=1 0000 0
EV:1300  CLK.Y=0 0000 0
```
