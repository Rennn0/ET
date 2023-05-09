#include "../headers/core.h"

int Core::generate(std::string location, std::string name)
{
	std::ifstream input(location);
	if (!input)return 0;
    
    std::map<std::string, std::vector<std::string>> exams;
    std::string line;
    while (std::getline(input, line)) {
        if (line != "") {
            std::stringstream ss(line);
            std::string first_name, last_name, exam_name;

            std::size_t last_comma = line.find_last_of(",");
            first_name = line.substr(last_comma + 1);
            line.erase(last_comma);

            std::size_t second_last_comma = line.find_last_of(",");
            last_name = line.substr(second_last_comma + 1);
            exam_name = line.substr(0, second_last_comma);

            exams[exam_name].push_back(last_name + ' ' + first_name);
        }
        else 
            return 0;
    }
    input.close();

    int total_exams = exams.size();
    int total_students = 0;
    for (const auto& exam : exams) {
        total_students += exam.second.size();
    }

    std::string folder = "OUTPUT";
    std::filesystem::create_directories(folder);

    std::ofstream output(folder + '/' + name + ".txt");
    std::ofstream outputStats(folder +'/'+ name + "Stats.txt");

    outputStats << "Total number of exams: " << total_exams << '\n' << "Total number of students: " << total_students ;
    outputStats.close();

    for (const auto& exam : exams) {
        output << exam.first << std::endl;
        for (const auto& student : exam.second) {
            output << ' ' << student << std::endl;
        }
    }
    output.close();
	return total_exams;
}
