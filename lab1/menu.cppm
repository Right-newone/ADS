export module menu;
import classes;
import functions;
import std;

export int menuf() {
    while (true) {
        std::cout << "[1] Демонстрация чтения-записи изображений" << std::endl;
        std::cout << "[2] Демонстрация умножения изображений" << std::endl;
        std::cout << "[3] Демонстрация сложения изображений" << std::endl;
        std::cout << "[4] Демонстрация вычитания изображений" << std::endl;
        std::cout << "[5] Демонстрация умножения на константу изображения" << std::endl;
        std::cout << "[6] Демонстрация сложения с константой изображения" << std::endl;
        std::cout << "[7] Демонстрация инвертирования значений изображений" << std::endl;
        std::cout << "[8] Вычисление коэффициента заполнения изображения" << std::endl;
        std::cout << "[9] Инвертирование значений выше заданной прямой" << std::endl;
        std::cout << "[10] Выход" << std::endl;

        int choice;
        std::cout << "\nВведите пункт меню: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            readnwrite();
            break;
        case 2:
            mult();
            break;
        case 3:
            summ();
            break;
        case 4:
            dif();
            break;
        case 5:
            multnconst();
            break;
        case 6:
            summnconst();
            break;
        case 7:
            invert();
            break;
        case 8:
            ratio();
            break;
        case 9:
            invertednlinedemo();
            break;
        case 10:
            std::cout << "Выход из программы" << std::endl;
            return 0;
        default:
            std::cout << "Неверный выбор, попробуйте снова [1-10]" << std::endl;
            break;
        }
    }
}