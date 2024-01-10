#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>

std::string generateRandomData(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255); // Диапазон значений байта (0-255)

    std::string data;
    data.reserve(size);
    for (int i = 0; i < size; ++i) {
        data.push_back(static_cast<char>(dis(gen)));
    }

    return data;
}
void generateRandomMP4(const std::string& directoryPath) {
    for (int i = 0; i < 10; ++i) {
        std::string filePath = directoryPath + "/video" + std::to_string(i) + ".mp4";
        
        // Generate random size for the MP4 file (between 1MB and 10MB for example)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1048576, 10485760); // Random size between 1MB and 10MB
        int fileSize = dis(gen);

        // Generate random data for the MP4 file
        std::string fileData = generateRandomData(fileSize);

        // Write the random data to the MP4 file
        std::ofstream file(filePath, std::ios::binary);
        file.write(fileData.data(), fileData.size());
        file.close();
    }
}


void generateRandomImage(const std::string& filename, int width, int height)
{
    std::ofstream imageFile(filename, std::ios::binary);

    // Создаем случайный генератор
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);

    // Создаем вектор для хранения пикселей
    std::vector<unsigned char> pixels(width * height * 3, 0);

    // Заполняем вектор случайными значениями для каждого пикселя
    for (int i = 0; i < width * height * 3; i++)
    {
        pixels[i] = dis(gen);
    }
 
    // Записываем заголовок файла изображения
    imageFile << "P6\n";
    imageFile << width << " " << height << "\n";
    imageFile << "255\n";

    // Записываем пиксели в файл
    imageFile.write(reinterpret_cast<char*>(&pixels[0]), pixels.size());
 
    std::cout << "Изображение успешно сгенерировано и сохранено в файле: " << filename << std::endl;
}



int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Путь до директории не указан." << std::endl;
        return 0;
    }

std::string _target_name = " ";
if (std::string(argv[2]).compare("-b") == 0) {
    _target_name = argv[3];
}

   std::cout << "ARGV = " <<argv[2] << std::endl;
   std::cout<<" -b " <<_target_name<<std::endl;
   std::string directoryPath = "test";

    for (int i = 0; i < 10; ++i) {
        std::string filePath = directoryPath + "/file" + std::to_string(i) + ".bin";
        std::string ImagePath = directoryPath + "/rndm_img" + std::to_string(i) + ".ppm";
        generateRandomImage(ImagePath, 5,5);
        generateRandomMP4(directoryPath);
        // Генерация случайного размера файла от 128 байт до 1 килобайта
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(128, 1024);
        int fileSize = dis(gen);

        // Генерация случайных данных для файла
        std::string fileData = generateRandomData(fileSize);

        // Запись данных в файл
        std::ofstream file(filePath, std::ios::binary);
        file.write(fileData.data(), fileData.size());
        file.close();
    }
   

    _target_name = "-- ./" + _target_name + " -b @@" ;
    std::cout<<"sadsda "<<_target_name<<std::endl;
    for (int i = 0; i < 10; ++i) {

        std::string filePath = directoryPath + "/file" + std::to_string(i) + ".bin";
            // Выполнение команды в shell
        std::string command = "afl-analyze -t 50000 -i " + filePath + " " + _target_name;
        int result = std::system(command.c_str());

        if (result != 0) {
            std::cout << "Ошибка при выполнении команды для файла: " << filePath << std::endl;
        }
    }
    for (int i = 0 ; i < 10; ++i){
        std::string ImagePath = directoryPath + "/rndm_img" + std::to_string(i) + ".ppm";
           // Выполнение команды в shell
        std::string command = "afl-analyze -t 50000 -i " + ImagePath + " " + _target_name;
        int result = std::system(command.c_str());

        if (result != 0) {
            std::cout << "Ошибка при выполнении команды для файла: " << ImagePath << std::endl;
        }   
    
    }   
    return 0;
}
