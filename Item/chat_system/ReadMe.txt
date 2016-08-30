项目名称: linux群聊系统
项目时间：  20160830
简介： linux环境下的基于C/S模式的多人聊天系统
开发环境:CentOS,C++,vim,make,g++,gdb, bash
主要用到的技术:多线程pthread、socket、udp编程、生产者消费者模型、shell、STL的vector、map、jsoncpp数据序列化库、POSIX semaphore信号量库以及ncurse图形界面库。
项目特点：
    网络数据传输使用UDP协议。
	客户端用ncurse实现简单的界面，用jsoncpp实现数据的序列化和反序列化处理。
	用map实现记录在线用户，用vector实现后端数据池，信号量semaphore保证服务器生产者消费者模型，多线程分别处理接收数据和广播功能
	用Shell和make实现自动化编译和运行。




