#include <iostream>
#include <fstream>
#include <vector>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <cstdlib>

int mutation(std::string name, std::string mutator , int iterator)
{   
    std::string _iter = std::to_string(iterator);
    std::string newname = _iter + "_mutt" + name;
    std::string cmd ="radamsa -o outdir/"+ newname + " " + name + mutator;
    std::cout<<cmd<<std::endl;
    const char* charPtr = cmd.c_str();
    std::system(charPtr);
    return 0;
}
// void genere_input(std::string name, std::string mutator , int iterator)
//         {
//             for(int i=0; i<iterator; i++)
//             {
//                 std::string cmd = "radamsa -o outdir/" + "-g random " + name + mutator;
//             }
//         }
int main(int argc, char* argv[], char* envp[]) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(argv[1])) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // Проверка, что это обычный файл
                std::string fileName = ent->d_name;
                std::string filePath = std::string(argv[1]) + "/" + fileName;
                int fd = open(filePath.c_str(), O_RDONLY);
                if (fd != -1) {
                    off_t length = lseek(fd, 0, SEEK_END);
                    void* addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
                    if (addr != MAP_FAILED) {
                        // Работа с содержимым файла через addr
                        // Например, вывод содержимого файла в 16-ричном виде с группировкой по 4 байта
                        std::cout << "File: " << fileName << std::endl;
                        std::cout << "Mutation...  " << fileName << std::endl;
                        std::string arg = "  "; 
                        for(int i = 1; i<=27; i++)
                        {
                            switch(i) {
                                case 1 : 
                                    arg = " -m fn=2"; 
                                case 2 : 
                                    arg = " -m fo=2"; 
                                case 3 : 
                                    arg = " -m fn";
                                case 4 : 
                                    arg = " -m num=5 ";
                                case 5 : 
                                    arg = " -m ld ";
                                case 6 : 
                                    arg = " -m lds";
                                case 7 :
                                    arg = " -m lr2";
                                case 8 :
                                    arg = " -m li";
                                case 9 : 
                                    arg = " -m ls";
                                case 10 : 
                                    arg = " -m lp";
                                case 11 : 
                                    arg = " -m lr";
                                case 12 : 
                                    arg = " -m lis"; 
                                case 13 : 
                                    arg = " -m lrs"; 
                                case 14 : 
                                    arg = " -m sr";
                                case 15 : 
                                    arg = " -m sd";
                                case 16 : 
                                    arg = " -m bd";
                                case 17 : 
                                    arg = " -m bf";
                                case 18 : 
                                    arg = " -m bi ";
                                case 19 : 
                                    arg = " -m br"; 
                                case 20 : 
                                    arg = " -m bp";
                                case 21 : 
                                    arg = " -m bei";
                                case 22 : 
                                    arg = " -m bed";
                                case 23 : 
                                    arg = " -m ber";
                                case 24 : 
                                    arg = " -m uw";
                                case 25 : 
                                    arg = " -m ui=2";
                                case 26 : 
                                    arg = " -m xp=9"; 
                                case 27 : 
                                    arg = " -m ab"; 
                                    }
                                
                        mutation(fileName, arg , i);
                        }
    
                        std::cout << std::endl;

                        munmap(addr, length);
                    } else {
                        std::cout << "Error mapping file: " << fileName << std::endl;
                    }
                    close(fd);
                } else {
                    std::cout << "Error opening file: " << fileName << std::endl;
                }
            }
        }
        closedir(dir);
    } else {
        std::cout << "Error opening directory" << std::endl;
    }

    return 0;
}