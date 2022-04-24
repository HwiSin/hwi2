class User userArray[MAX_USER_NUMBER];


class User
{
	int fdNumber;
	char* name = "<NULL>";
public:
	User(int targetFD)
	{
		fdNumber = targetFD;
	}

	void SerName(string wantName) { name = wantName; };
};