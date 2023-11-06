//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <string>
//#include "Cheese.h"
//
//void printdivider(size_t cnt, const std::string heading = "") {
//    if (heading != "")
//        std::cout << heading << "\n";
//    for (auto i = 0u; i < cnt; ++i)
//        std::cout << "-";
//    std::cout << std::endl;
//}
//
//int main(int argc, char** argv)
//{
//    sdds::Cheese** cheeses{};
//    size_t cnt = 0;
//
//    //process the file
//    if (argc > 1)
//    {
//        //opens the file using the argument as a string
//        std::ifstream file(argv[1]);
//
//        //check if file opened
//        if (!file)
//        {
//            std::cout << "ERROR opening " << argv[1] << std::endl;
//        }
//
//        //determine # of lines in the file
//        std::string cheeseline{};
//        do
//        {
//            std::getline(file, cheeseline);
//            if (cheeseline[0] != '#')
//            {
//                cnt++;
//            }
//
//        } while (file);
//
//        //reset filestream to beginning
//        file.clear();
//        file.seekg(std::ios::beg);
//        cnt = 0;
//
//        //read file again, but this time store it into object
//        do
//        {
//            std::getline(file, cheeseline);
//            if (cheeseline[0] != '#')
//            {
//                cheeses[cnt] = new sdds::Cheese(cheeseline);
//                cnt++;
//            }
//        } while (file);
//        file.close();
//
//    }
//    else
//    {
//        std::cout << "ERROR: cheeses.txt file not provided.\n";
//        return 2;
//    }
//	return 0;
//}