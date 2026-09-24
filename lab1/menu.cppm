export module menu;
import functions;
import std;

export int menuf() 
{
    while (true)
    {
        std::cout << "[1] Image read-write demonstration" << std::endl;
        std::cout << "[2] Image multiplication demonstration" << std::endl;
        std::cout << "[3] Image addition demonstration" << std::endl;
        std::cout << "[4] Image subtraction demonstration" << std::endl;
        std::cout << "[5] Image multiplication by a constant demonstration" << std::endl;
        std::cout << "[6] Image addition with a constant demonstration" << std::endl;
        std::cout << "[7] Image value inversion demonstration" << std::endl;
        std::cout << "[8] Image fill factor calculation" << std::endl;
        std::cout << "[9] Inversion of values above a given line" << std::endl;
        std::cout << "[10] End session" << std::endl;
        int choice = 0;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        switch (choice) 
        {
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
            std::cout << "End of session" << std::endl;
            return 0;
        default:
            std::cout << "Wrong choice, try again from [1-10]" << std::endl;
            break;
        }
    }
}