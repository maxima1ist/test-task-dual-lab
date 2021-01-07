#include <fstream>
#include <vector>
#include <set>
#include "timetable.h"

using std::ifstream;
using std::ofstream;
using std::vector;
using std::set;

using timetable::TransportService;

void readInfo(ifstream& fin, vector<TransportService>& poshTimetable, vector<TransportService>& grottyTimetable) {
    std::string company;
    while (fin >> company) {
        try {
            TransportService ts;
            fin >> ts;
            if (ts.getDurationInMinutes() <= 60) {
                if (company == "Posh") {
                    poshTimetable.push_back(ts);
                } else if (company == "Grotty") {
                    grottyTimetable.push_back(ts);
                }
            }
        } catch (const timetable::TimeFormatException& exception) {
            std::cerr << exception.what() << '\n' << "This entry will be ignored." << '\n';
        }
    }
}

void printInfo(ofstream& fout, const set<TransportService>& posh, const set<TransportService>& grotty) {
    for (const auto& it : posh) {
        fout << "Posh " << it << '\n';
    }
    fout << '\n';
    for (const auto& it : grotty) {
        fout << "Grotty " << it << '\n';
    }
}

void modifyTimetable(ifstream& fin, ofstream& fout) {
    vector<TransportService> poshTimetable, grottyTimetable;
    readInfo(fin, poshTimetable, grottyTimetable);

    // marking ineffective services
    vector<bool> poshMask(poshTimetable.size(), true), grottyMask(grottyTimetable.size(), true);
    for (size_t i(0); i < poshTimetable.size(); ++i) {
        if (poshMask[i]) {
            for (size_t j(0); j < poshTimetable.size(); ++j) {
                if (i != j && poshMask[j]) {
                    poshMask[j] = !poshTimetable[i].isInsideOfRange(poshTimetable[j]);
                }
            }
            for (size_t j(0); j < grottyTimetable.size(); ++j) {
                if (grottyMask[j]) {
                    if (poshTimetable[i].isTheSameRange(grottyTimetable[j])) {
                        grottyMask[j] = false;
                    } else {
                        grottyMask[j] = !poshTimetable[i].isInsideOfRange(grottyTimetable[j]);
                    }
                }
            }
        }
    }
    for (size_t i(0); i < grottyTimetable.size(); ++i) {
        if (grottyMask[i]) {
            for (size_t j(0); j < poshTimetable.size(); ++j) {
                if (poshMask[j]) {
                    if (grottyTimetable[i].isTheSameRange(poshTimetable[j])) {
                        grottyMask[i] = false;
                        break;
                    } else {
                        poshMask[j] = !grottyTimetable[i].isInsideOfRange(poshTimetable[j]);
                    }
                }
            }
            if (grottyMask[i]) {
                for (size_t j(0); j < grottyTimetable.size(); ++j) {
                    if (i != j && grottyMask[j]) {
                        grottyMask[j] = !grottyTimetable[i].isInsideOfRange(grottyTimetable[j]);
                    }
                }
            }
        }
    }

    // leaving only effective services, building them into right order
    std::set<TransportService> poshRes, grottyRes;
    for (size_t i(0); i < poshTimetable.size(); ++i) {
        if (poshMask[i]) {
            poshRes.insert(poshTimetable[i]);
        }
    }
    for (size_t i(0); i < grottyTimetable.size(); ++i) {
        if (grottyMask[i]) {
            grottyRes.insert(grottyTimetable[i]);
        }
    }

    printInfo(fout, poshRes, grottyRes);
}

int main() {
    ifstream fin;
    ofstream fout;

    fin.open("./data/input.txt");
    fout.open("./data/output.txt");

    modifyTimetable(fin, fout);

    fin.close();
    fout.close();
    
    std::cout << "The timetable was successfully optimized and written to the file \"output.txt\"" << '\n';

    return 0;
}
