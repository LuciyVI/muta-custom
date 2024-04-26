#include <iostream>
#include <string>
#include <random>

// std::string mutateString(const std::string& inputString) {
//     // Перевод строки в hex
//     std::string hexString;
//     for (char c : inputString) {
//         hexString += std::to_string(static_cast<int>(c));
//     }
    
//     return hexString;
// }

std::string multiplyHexStrings(const std::string& inputString, const std::string& w) {
   
    // Вычисление веса смещения w0
   
    std::string w0 ;
    for (char c : w) {
        w0 += c;
    }

    size_t length = std::min(inputString.length(), inputString.length());
    // Выполнение операции XOR
    std::string result;
    for (size_t i = 0; i < sizeof(inputString); ++i) {
        result += inputString[i] & w[i];
    } 
    
    std::cout<<"Промежуточный результат сложения"<<result<<std::endl;

    for (size_t i = 0; i < length; ++i) {
        result += result[i] ^ w0[i];
    }

    // Преобразование результата обратно в строку в 16-ричном формате
    

    return result;
}

std::string distribute_wight(std::string inputString){
  
    // Генерация случайных данных для w
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    std::string w ;
    for (char c : inputString) {
        w += static_cast<char>(dis(gen));
    }
    std::cout<<" wight :  "<<w<<std::endl;
    return w;
}
int main() {

    std::string inputString;
    std::cout << "Введите строку: ";
    std::getline(std::cin, inputString);
    std::cout << "Исходная строка: " << inputString << std::endl;
    std::string w = distribute_wight(inputString);
    std::cout<<multiplyHexStrings(inputString,w)<<std::endl;

    return 0;
}
