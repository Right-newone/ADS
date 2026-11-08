export module menu;
import std;
import classes;

export int menu_f()
{
    while (true)
    {
        std::cout << "[1] Image read-write demonstration" << std::endl;
        std::cout << "[2] End session" << std::endl;
        int choice = 0;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Hi" << std::endl;
            break;
        case 2:
            std::cout << "End of the session";
            return 0;
        default:
            std::cout << "Wrong choice, try again from [1-1]" << std::endl;
            break;
        }
    }
}