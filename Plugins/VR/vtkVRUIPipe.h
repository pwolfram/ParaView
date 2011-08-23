#ifndef vtkVRUIPipe_h
#define vtkVRUIPipe_h
#include <string>
#ifdef QTSOCK
class QTcpSocket;
#endif

class vtkVRUIServerState;

class vtkVRUIPipe
{
public:
  // Description:
  // VRUI Protocol messages
  enum MessageTag
  {
    CONNECT_REQUEST=0, // Request to connect to server
    CONNECT_REPLY, // Positive connect reply with server layout
    DISCONNECT_REQUEST, // Polite request to disconnect from server
    ACTIVATE_REQUEST, // Request to activate server (prepare for sending packets)
    DEACTIVATE_REQUEST, // Request to deactivate server (no more packet requests)
    PACKET_REQUEST, // Requests a single packet with current device state
    PACKET_REPLY, // Sends a device state packet
    STARTSTREAM_REQUEST, // Requests entering stream mode (server sends packets automatically)
    STOPSTREAM_REQUEST, // Requests leaving stream mode
    STOPSTREAM_REPLY // Server's reply after last stream packet has been sent
  };

  // Description:
  // Constructor from tcp socket.
  // \pre socket_exists: socket!=0
#ifdef QTSOCK
  vtkVRUIPipe(QTcpSocket *socket);
#else
  vtkVRUIPipe(int socket);
#endif

  // Description:
  // Destructor.
  ~vtkVRUIPipe();

  // Description:
  // Send a VRUI protocol message.
  void Send(MessageTag m);

  // Description:
  // Wait for server's reply (with a msecs milliseconds timeout).
  // Return true if there is something to read.
  // Return false in case of timeout or error.
  bool WaitForServerReply(int msecs);

  // Description:
  // Read message from server.
  MessageTag Receive();

  // Description:
  // Read server's layout (whatever that means) and initialize current state
  // \pre state_exists: state!=0
  void ReadLayout(vtkVRUIServerState *state);

  // Description:
  // Read server state.
  // \pre state_exists: state!=0
  void ReadState(vtkVRUIServerState *state);

  // Description:
  // Prints the appropriate packet type
  std::string GetString( MessageTag m )
  {
    switch( m )
      {
      case CONNECT_REQUEST: return "CONNECT_REQUEST";
      case CONNECT_REPLY: return "CONNECT_REPLY";
      case DISCONNECT_REQUEST: return "DISCONNECT_REQUEST";
      case ACTIVATE_REQUEST: return "ACTIVATE_REQUEST";
      case DEACTIVATE_REQUEST: return "DEACTIVATE_REQUEST";
      case PACKET_REQUEST: return "PACKET_REQUEST";
      case PACKET_REPLY: return "PACKET_REPLY";
      case STARTSTREAM_REQUEST: return "STARTSTREAM_REQUEST";
      case STOPSTREAM_REQUEST: return "STOPSTREAM_REQUEST";
      case STOPSTREAM_REPLY: return "STOPSTREAM_REPLY";
      default: return "UNKNOWN";
      }
  }

protected:
#ifdef QTSOCK
  QTcpSocket *Socket;
#else
  int	Socket;	/* socket file descriptor */
#endif

private:
  vtkVRUIPipe(); // Not implemented.
  vtkVRUIPipe(const vtkVRUIPipe&); // Not implemented.
  void operator=(const vtkVRUIPipe&); // Not implemented.
};

#endif // #ifndef vtkVRUIPipe_h
