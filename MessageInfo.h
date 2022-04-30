//���� �̶�� �ϴ� ������!
//Struct�� ����ϰ� ���� �� �ֽ��ϴ�!
//�������� �����̳�? �ϳ��� �޸𸮸� �������� �ڷ����� �����ؿ�!
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

//�׻� Ŭ���̾�Ʈ�� enum���� ��ġ�����ּ���!
enum class MessageType
{
	LogIn,
	LogOut,
	Chat,

	Length
	//���� ���� �޽��� Ÿ���� �������� �� ���� ������ ������ ����!
};

class MessageInfo
{
public:
	MessageType type;
	int length;
};

class MessageInfo_Login :public MessageInfo
{
public:
	int userIndex;
	string name;
	MessageInfo_Login(char* message, int targetUser)
	{
		type = MessageType::LogIn;
		//���� �κ��� �� �� Ȯ��!
		byteConvertor.character[0] = message[2];
		byteConvertor.character[1] = message[3];
		//ĳ���� �ΰ��� �о�ͼ� �װŸ� ���ڷ� ���!
		length = byteConvertor.shortInteger[0];
		userIndex = targetUser;
		//�޼����� 4��°���� ������ �־��ֵ��� �սô�!
		name = (message[4]);
	}
};