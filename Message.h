//항상 클라이언트의 enum값과 일치시켜주세요!
enum class MessageType
{
	LogIn,
	LogOut,
	Chat,

	Length
	//제가 가진 메시지 타입의 개수보다 더 많은 내용이 들어오면 무시!
};

//통합 이라고 하는 것이죠!
//Struct랑 비슷하게 쓰실 수 있습니다!
//차이점이 무엇이냐? 하나의 메모리를 여러가지 자료형이 공유해요!
//[0][0][0][10]
//          10   int
//          \n   char[3]
union ConvertionBase
{
	unsigned int uInteger;
	int integer;

	float floating;

	char character[4];

	short shortInteger[2];
	unsigned short uShortInteger[2];
};
ConvertionBase byteConvertor;

struct MessageInfo
{
	MessageInfo type;
	int length;
};

//                                              본인에게 보내기는 기본적으로 true에요~!
//												그럼 뭐.. 체크안해도 되겠죠!
//												체크하려면 FD가 설정되어야 되니까!
//												sendSelf를 false로 하고 싶으면 sendFD도
//												꼭 정해야 할 겁니다!
void BroadCastMessage(char* message, int length, int sendFD = -1, bool sendSelf = true)
{
	//저희는 유저의 인원수를 알고 있습니다! 그 말은 곧,
	//끝까지 다 돌지 않아도 유저한테 다 전달을 했다면
	//굳이 뭐.. 더 돌 필요 있나!
	//보낼 때마다 send를 1씩 늘려주고, 유저수만큼 보냈다면 끝내기!

	//sendSelf가 false면 -> 본인한테 보내주는 게 아니면! 보내야 하는 유저 개수를
	//수정해줘야 하겠죠! 본인한테 보내준 셈 칩시다!
	//반복문이 한 명 덜 줬는데.. 누구지..? 하면서 끝까지 갈 거에요! 그거 막아주기!
	int send = sendSelf ? 0 : 1;
	//			 조건   ? true : false
	//     본인한테 보냄?  아무한테도 아직 안보냈다! : 1명 보내놨다!

	// 0번은 리슨 소켓!   최대치까지 갔거나, 또는 현재 유저 수만큼 보냈다면!
	for (int i = 1; i < MAX_USER_NUMBER; i++)
	{
		//본인한테 안 보낼거임! 이라고 할 때 받아온 정보가 있다면 넘어가기!
		if (!sendSelf && i == sendFD) continue;

		//대상이 없는데 보낼 순 없겠죠?
		if (pollFDArray[i].fd != -1)
		{
			//서버가 무언가 보낼 때 "적어 주는 거"에요 그래서 Write라고 부르고
			//받을 때에는 Read하겠죠?
			//       대상의 소켓,     메시지,   길이
			if (write(pollFDArray[i].fd, message, length))
			{
				//보냈다!   그랬더니 다 보냄! 이라고 했을 때 돌려주기!
				if (++send >= currentUserNumber) break;
			};
		};
	};

	cout << "Message Send To " << send << "User : " << message << endl;
}

//메시지를 구분하는 용도                    길이 받을 int 주세요!
MessageType ProcessMessage(char input[4])
{
	byteConvertor.character = input;
	for (int i = 0; i < 4; i++)
	{
		byteConvertor.character[i] = input[i];
	}
	//메시지타입          길이
	//[][]               [][]

	MessageInfo result;
	result.type   = (MessageType)byteConvertor.shortInteger[0]; //타입도 돌려주기
	result.length = byteConvertor.shortInteger[1] + 4;				//길이를 주고
		
	return result;
}

int TranslateMessage(int fromFD, char* message,int messageLength, MessageInfo info)
{
	//전체 길이와 하나의 메시지 길이 둘 중에 작은 값으로!
	int currentLength = min(messageLength, info.length);

	//메모리 중에서 제가 처리해야하는 메모리까지만!
	char* target = new char[currentLength];
	memcpy(target, message, currentLength);

	switch (info.type)
	{
	case MessageType::Chat:
		BroadCastMessage(target currentLength, fromFD);
		break;
	case MessageType::LogIn:
		break;
	case MessageType::LogOut:
		break;

	default:return;
	}
	//사실 메세지같은 경우는 하나씩 보내면 조금 효율이 떨어집니다 ㅎㅎ
	//보낼 수 있을 때 여러개를 같이 보내는 게 좋습니다!
	//모아두었다가 보내는 개념!
	//전체 메시지 길이 - 지금 확인한 메시지 길이!
	//아직 뒤에 메시지가 더 있어요! 라고 하는 걸 확인할 수 있죠!
	return messageLength - info.length;
}


