Communication
==
TCP / IP, that is, transmission control protocol / internet protocol, is a general term for various protocol families related to the Internet, such as: TCP, UDP, IP, FTP, HTTP, ICMP, SMTP, etc. all belong to the protocols in the TCP / IP family.<br>

TCP and Socket
--
TCP relationship structure:<br>
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Image/TCP%20relationship%20structure.png)<br>
The TCP / IP protocol family includes the application layer, the transport layer, the network layer, and the link layer.<br>

The **data link layer** is responsible for receiving IP data packets and sending them through the network, or receiving physical frames from the network, extracting IP data packets, and handing them to the IP layer.<br>

The **network layer** is responsible for the communication between adjacent computers. Its functions include:<br>
1) Process the packet sending request from the transport layer. After receiving the request, load the packet into an IP datagram, fill the header, select the path to the sink, and then send the datagram to the appropriate network interface.<br>
2) To process the remaining datagrams, first check their legitimacy, and then perform path finding-if the datagram has arrived at the sink, remove the header and leave the rest to the appropriate transmission protocol. If the datagram has not arrived at the destination, the datagram is forwarded.<br>
3) Handle issues such as routing, flow control, and congestion.<br>

The **transport layer** provides communication between applications. Functions include:<br>
1) Format the information stream.<br>
2) Provide reliable transmission.<br>

**Application layer** provides users with commonly used applications.<br>

**Socket** is used to describe the IP address and port, the application can send requests to the network or respond to network requests through Socket. Socket is the basic operation unit of network communication supporting TCP / IP protocol. It is an abstract representation of the endpoint in the network communication process. It contains five kinds of information necessary for network communication: the protocol used for connection; the IP address of the local machine; Local remote protocol port; remote host's IP address and remote protocol port.<br>

Socket is an intermediate software abstraction layer for communication between the application layer and the TCP / IP protocol family. It is a set of interfaces. In the design mode, it hides the complex TCP / IP protocol family behind the Socket interface. For users, a simple set of interfaces is all. Let the Socket organize the data to conform to the specified protocol.<br>

Communication process
--
The communication flow chart:<br>
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Image/Communication%20Flow%20Chart.jpg)<br>
The server first initializes the Socket, then binds to the port (bind), listens to the port (listen), calls accept to block, and waits for the client to connect. At this time, if a client initializes a Socket and then connects to the server (connect), if the connection is successful, then the connection between the client and the server is established. The client sends a data request, the server receives the request and processes the request, then sends the response data to the client, the client reads the data, and finally closes the connection, one interaction ends.<br>




