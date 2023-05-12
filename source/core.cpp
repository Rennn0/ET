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

void Core::invertMap(std::map<str, uint16_t>* tempMap) {
    for (const auto& pair : *tempMap) {
        ID_map.insert(std::make_pair(pair.second, pair.first));
    }
}

void Core::sort_mtavari_exam()
{
    std::sort(mtavari_exam_ptr, mtavari_exam_ptr + totalExams, [](auto & a, auto & b) {
        return a.studIDs.size() > b.studIDs.size();
    });
    for (auto& element : std::span<exam_>(mtavari_exam_ptr, totalExams))
        std::sort(element.studIDs.begin(), element.studIDs.end());
}

bool Core::check_limit()
{
    for (uint16_t i = 0; i < totalExams; i++)
        if (mtavari_exam_ptr[i].studIDs.size() > LIMIT) {
            throw ET::limit_error();
            return false;
        }
    return true;
}

void Core::print()
{
    std::ofstream of("TESTED.txt");
    for (const auto& exam : std::span<exam_>(mtavari_exam_ptr, totalExams)) {
        of << exam.exam<<'\n';
        for (const auto& ids : exam.studIDs)
            of << ids << ' ';
        of << '\n';
    }
}

bool Core::has_matching_IDs(const std::vector<uint16_t>& v1, const std::vector<uint16_t>& v2)
{
    return std::find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end()) != v1.end();
}

void Core::save_result()
{
    std::ofstream out(folder + "/OUTPUT/RESULT/" + resultName + ".txt");
    uint16_t N = 1;
    for (const auto& sesia : sesiebi) {
        int total_std = 0;
        for (const auto& vect : sesia) 
            total_std += vect->studIDs.size();

        out << "Session #" << N++ << " ;  Students " << total_std << '\n';
        for (const auto& vect : sesia) {
                out<< vect->exam << " _ { ";
            for (const auto& ids : vect->studIDs) {
                out << ids << ',';
            }
            out << " }\n";
        }
            out << "\n\n";
    }
}

void Core::save_IDMap()
{
    std::ofstream out(folder + "/OUTPUT/RESULT/" + resultName + "IDMap.txt");
    for (const auto& [key, value] : ID_map)
        out << key << ' ' << value << '\n';
    
}

void Core::newDir()
{
    if (!newDireExicsts) {
        std::filesystem::create_directories(folder + "/OUTPUT/RESULT/");
        newDireExicsts = true;
    }
}

void Core::hashmap()
{
    uint16_t indexCounter = -1, ID=1;
    std::ifstream in(fileLocation);

    std::map<str, uint16_t> tempMap;
    str musha;
    while (std::getline(in, musha)) {
        if (musha[0] == ' ') {
            if (tempMap.count(musha) == 0) {
                tempMap[musha] = ID++;
                mtavari_exam_ptr[indexCounter].studIDs.push_back(tempMap[musha]);
            }else
                mtavari_exam_ptr[indexCounter].studIDs.push_back(tempMap[musha]);
        }
        else
            mtavari_exam_ptr[++indexCounter].exam = musha;
    }
    in.close();

    invertMap(&tempMap);
}

Core::Core(str&& fL, str&& f, str&& rN, uint16_t l, uint16_t tE)
    :fileLocation(fL), folder(f), resultName(rN),LIMIT(l),totalExams(tE),mtavari_exam_ptr(new exam_[tE])
{
    std::ofstream fd(folder+"/Logs.txt" , std::ios::app);
    fd << fileLocation <<' ' << folder << ' ' << resultName << ' ' << LIMIT << ' ' << totalExams << '\n';
}

void Core::sesiebis_dalageba()
{
    std::map<uint16_t, bool> picked;
    while (picked.size() < totalExams) {
        std::vector<exam_*> args;
        int accumulated = 0;
        for (size_t i = 0; i < totalExams; i++) {
            if (picked.find(i) == picked.end() && accumulated + mtavari_exam_ptr[i].studIDs.size() <= LIMIT) {
                bool match = 0;
                for (const auto& arg : args) {
                    if (has_matching_IDs(mtavari_exam_ptr[i].studIDs, arg->studIDs)) {
                        match = 1;
                        break;
                    }
                }
                if (!match) {
                    args.push_back(&mtavari_exam_ptr[i]);
                    picked[i] = true;
                    accumulated += mtavari_exam_ptr[i].studIDs.size();
                }
            }
            if (accumulated >= LIMIT)
                break;
        }
        sesiebi.push_back(args);
    }
}

