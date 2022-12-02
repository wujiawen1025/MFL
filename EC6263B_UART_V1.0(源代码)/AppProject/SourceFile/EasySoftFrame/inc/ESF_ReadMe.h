/*

9600波特率， 1ms发送0.96个字节。
发送用中断，如果在发送中，如何重新有效投递发送事件。



ESF 系统主要RAM消耗：

ESF_Evt_t         --> 一个事件占用12字节
ESF_Tmr_t	      --> 一个定时器占用12字节
ESF_EvtMemPool_t  --> 占用8字节
ESF_Mem_t		  --> 占用8字节
ESF_EvtQuene_t    --> 最少八字节（队列空间1），每加一个空间加4字节

esf_MemUnit_t ESF_MemBlkBuf[ESF_MEM_BOLCK_NUM][ESF_MEM_BOLCK_SIZE]  
--> 根据情况，主要是给通信数据包使用。ESF_MEM_BOLCK_NUM建议至少为2。

根据事件的多少与通信包的需求占用的内存不定。
建议ESF系统应用于至少有512字节RAM的单片机上。
如果事件少于5个（包括定时），也无数据包的通信，
也可用于 128字节RAM的系统上。






*/
