#ifndef MESSAGES
#define MESSAGES

namespace MessageID // Message id
{
  //Message type
	enum MessageType
	{
		None,
		Quit,
		Collide,
		ToggleDebugInfo,
		CharacterKey,
		MouseButton,
		MouseMove,
		FileDrop,
    Spawn
	};
}

class Message
{
public:
  //Constructor, initializes the message ID
  Message(){};
	Message(MessageID::MessageType id) : msgID(id){};

  //Message ID
	MessageID::MessageType msgID;

  //Destructor
	virtual ~Message(){};

  void * info;
};

#endif