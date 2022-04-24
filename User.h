class User
{
	int fdNumber;
	char* name = "<NULL>";
public:
	User(int targetFD)
	{
		fdNumber = targetFD;
	}

	void SerName(wstring wantName) { name = wantName; }
};