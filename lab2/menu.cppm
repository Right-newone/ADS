export module menu;
import std;
import classes;
import functions;

export int menu_f()
{
    while (true)
    {
        std::cout << "\n[1] Assignment demonstration" << std::endl;
        std::cout << "[2] Push_tail demonstration" << std::endl;
        std::cout << "[3] Push_tail_list demonstration" << std::endl;
        std::cout << "[4] Push_head demonstration" << std::endl;
        std::cout << "[5] Push_head_list demonstration" << std::endl;
        std::cout << "[6] Pop_head demonstration" << std::endl;
        std::cout << "[7] Pop_tail demonstration" << std::endl;
        std::cout << "[8] Delete_node demonstration" << std::endl;
        std::cout << "[9] Read_by_idx demonstration" << std::endl;
        std::cout << "[10] Write_by_idx demonstration" << std::endl;
        std::cout << "[11] Output demonstration" << std::endl;
        std::cout << "[12] Reversing list demonstration" << std::endl;
        std::cout << "[13] End session" << std::endl;
        int choice = 0;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            assign();
            break;
        case 2:
            push_tail_demo();
            break;
        case 3:
            push_tail_list_demo();
            break;
        case 4:
            push_head_demo();
            break;
        case 5:
            push_head_list_demo();
            break;
        case 6:
            pop_head_demo();
            break;
        case 7:
            pop_tail_demo();
            break;
        case 8:
            delete_node_demo();
            break;
        case 9:
            read_by_idx_demo();
            break;
        case 10:
            write_by_idx_demo();
            break;
        case 11:
            output_demo();
            break;
        case 12:
            reversed_list_demo();
            break;
        case 13:
            std::cout << "End of the session";
            return 0;
        default:
            std::cout << "Wrong choice, try again from [1-13]" << std::endl;
            break;
        }
    }
}