enum class MessageType
{
	Chat,

	Length //���� ���� �޽��� Ÿ���� �������� �� ���� ������ ������ ����!
};

void SeparateMessage()
{

}

void TranslateMessage()
{

}

//                                              ���ο��� ������� �⺻������ true����!
//                                              �׷� ��.. üũ���ص� �ǰ���!
//                                              üũ�Ϸ��� FD�� �����Ǿ�� �Ǵϱ�!
//                                              sendSlef�� false�� �ϰ� ������ snedFD��
//                                              �� ���ؾ� �� �̴ϴ�
void BroadCastMessage(char* message, int length, int sendFD = -1, bool sendSelf = true)
{
	//����� ������ �ο����� �˰� �ֽ��ϴ�! �� ���� ��,
	//������ �� ���� �ʾƵ� �������� �� ������ �ߴٸ�
	//���� ��.. �� �� �ʿ��ֳ�!
	//���� ������ send�� 1�� �÷��ְ�, ��������ŭ ���´ٸ� ������!
	int send = 0;

	//   0���� �������� �ִ�ġ���� ���ų�, �Ǵ� ���� ���� ����ŭ ���´ٸ�!
	for (int i = 1; i < MAX_USER_NUMBER || send >= currentUserNumber; i++)
	{
		//�������� �� ��������! �̶�� �� �� �޾ƿ� ������ �ִٸ� �Ѿ��!
		if (!sendSelf && i == sendFD) continue;
		//������ ���� ���� �� "���� �ִ� ��"���� �׷��� Write��� �θ���
		//���� ������ Read�ϰ���?
		//        ����� ����     �޽���,   ����
		write(pollFDArray[i].fd, message, lendgth);
	}
}