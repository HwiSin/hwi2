enum class MessageType
{
	Chat,

	Length //제가 가진 메시지 타입의 개수보다 더 많은 내용이 들어오면 무시!
};

void SeparateMessage()
{

}

void TranslateMessage()
{

}

//                                              본인에게 보내기는 기본적으로 true에요!
//                                              그럼 뭐.. 체크안해도 되겠죠!
//                                              체크하려면 FD가 설정되어야 되니까!
//                                              sendSlef를 false로 하고 싶으면 snedFD도
//                                              꼭 정해야 할 겁니다
void BroadCastMessage(char* message, int length, int sendFD = -1, bool sendSelf = true)
{
	//저희는 유저의 인원수를 알고 있습니다! 그 말은 곧,
	//끝까지 다 돌지 않아도 유저한테 다 전달을 했다면
	//굳이 뭐.. 더 돌 필요있나!
	//보낼 때만다 send를 1씩 늘려주고, 유저수만큼 보냈다면 끝나기!
	
	//sendSlef가 false면 ->본인한테 보내주는게 아니면! 보내야 하는 유저개수를
	//수정해줘야 하겠죠! 본인한테 보내준 셈 칩시다!
	//반복문이 한 명 덜 줬는데.. 누구지? 하면서 끝까지 갈 거에요! 그거 막아주기!
	int send = sendSlef ? 0 : 1;
	//           조건   ? true : false;
	//     본인한테보냄 ? 아무한테도 아직 안보냈다 : 1명 보내놨다!

	//   0번은 리슨소켓 최대치까지 갔거나, 또는 현재 유저 수만큼 보냈다면!
	for (int i = 1; i < MAX_USER_NUMBER || send >= currentUserNumber; i++)
	{
		//본인한테 안 보낼거임! 이라거 할 떄 받아온 정보가 있다면 넘어가기!
		if (!sendSelf && i == sendFD) continue;

		//대상이 없는데 보낼순 없겠죠?
		if (pollFDArray[i].fd != -1)
		{
			//서버가 무언가 보낼 때 "적어 주는 거"에요 그래서 Write라고 부르고
			//받을 떄에는 Read하겠죠?
			//        대상의 소켓     메시지,   길이
			write(pollFDArray[i].fd, message, length);

			//보냈다!
			++send;
		}
	}
}