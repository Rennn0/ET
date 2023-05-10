#include"../pch.h"
#include "../headers/core.h"

int Core::generate(str location, str folder , str name)
{
	std::ifstream input(location);
    
    std::map<std::string, std::vector<std::string>> exams;
    std::string line;
    while (std::getline(input, line)) {
        if (line != "") {
            std::stringstream ss(line);
            std::string first_name, last_name, exam_name;

            std::size_t last_comma = line.find_last_of(",");
            if (last_comma == std::string::npos)throw ET::format_error();
            first_name = line.substr(last_comma + 1);
            line.erase(last_comma);

            std::size_t second_last_comma = line.find_last_of(",");
            if (second_last_comma == std::string::npos)throw ET::format_error();
            last_name = line.substr(second_last_comma + 1);
            exam_name = line.substr(0, second_last_comma);

            exams[exam_name].push_back(last_name + ' ' + first_name);
        }
        else 
            throw ET::format_error();
    }
    input.close();

    int total_exams = exams.size();
    int total_students = 0;
    for (const auto& exam : exams) {
        total_students += exam.second.size();
    }

    str folderOut =folder+ "/OUTPUT";
    std::filesystem::create_directories(folderOut);

    std::ofstream output(folderOut + '/' + name + ".txt");
    std::ofstream outputStats(folderOut +'/'+ name + "Stats.txt");

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



bool Core::start(str genFile, int& examN, int& studL, str genName)
{

    return true;
}

