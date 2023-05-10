namespace ET {
	class format_error :public std::exception {};
}

typedef std::string str;
class Core {


public:
	
	static int generate(str, str, str);
	static bool start(str genFile, int& examN, int& studL, str genName);
};