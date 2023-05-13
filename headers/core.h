#pragma once
typedef std::string str;

struct exam_ {
	str exam = "#";
	std::vector<uint16_t>studIDs;
};

namespace ET {
	class format_error :public std::exception {};
	class location_error :public std::exception {};
	class limit_error :public std::exception {};
}

class uncopyable {
public:
	uncopyable() = default;
	uncopyable(const uncopyable&) = delete;
	uncopyable& operator = (const uncopyable&)=delete;
};

class Core : private uncopyable {
	exam_* mtavari_exam_ptr = nullptr;
	std::map<uint16_t, str> ID_map;
	std::vector<std::vector<exam_*>> sesiebi;

	str fileLocation, folder, resultName;
	uint16_t LIMIT, totalExams;

	bool newDireExicsts = false;
	friend class User;
public:

	Core(str&& fL, str&& f, str&& rN, uint16_t l, uint16_t tE);
	void sesiebis_dalageba();
	static int generate(str, str, str);
	void hashmap();
	void invertMap(std::map<str, uint16_t>*);
	void sort_mtavari_exam();
	bool check_limit();
	void print();
	bool has_matching_IDs(const std::vector<uint16_t>& v1, const std::vector<uint16_t>& v2);
	void save_result();
	void save_IDMap();
	void newDir();
	
};