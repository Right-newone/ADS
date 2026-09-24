export module functions;
import classes;
import std;

export void readnwrite() {
    image<short> img(3, 4, false);
    std::cout << "Before: " << img(1, 2) << "\n";
    img(1, 2) = 75;
    std::cout << "After: " << img(1, 2) << "\n";
    std::cout << "\n";
}
export void mult() {
    image<bool> img2(2, 3, true);
    image<bool> img3(2, 3, true);
    image<bool> result = img2 * img3;
    std::cout << img2;
    std::cout << "   *    \n";
    std::cout << img3;
    std::cout << "   =    \n";
    std::cout << result;    
    std::cout << "\n";
}
export void summ()
{
    image<short> img2(2, 1, true);
    image<short> img3(3, 4, true);
    image<short> result = img2 + img3;
    std::cout << img2;
    std::cout << "   +    \n";
    std::cout << img3;
    std::cout << "   =    \n";
    std::cout << result;
    std::cout << "\n";
}
export void dif()
{
    image<short> img2(2, 3, true);
    image<short> img3(3, 2, true);
    image<short> result = img2 - img3;
    std::cout << img2;
    std::cout << "   -    \n";
    std::cout << img3;
    std::cout << "   =    \n";
    std::cout << result;
    std::cout << "\n";
}
export void multnconst()
{
    image<short> img2(2, 2, true);
    const int num = 6;
    image<short> result = img2 * num;
    std::cout << img2;
    std::cout << "   *    \n";
    std::cout << "   " << num << "\n";
    std::cout << "   =    \n";
    std::cout << result;
    std::cout << "\n";
}
export void summnconst()
{
    image<short> img2(2, 2, true);
    const int num = 6;
    image<short> result = img2 + num;
    std::cout << img2;
    std::cout << "   +    \n";
    std::cout << "   " << num << "\n";
    std::cout << "   =    \n";
    std::cout << result;
    std::cout << "\n";
}
export void invert()
{
    image<bool> img2(2, 2, true);
    image<bool> result = !img2;
    std::cout << img2;
    std::cout << "   !    \n";
    std::cout << "   =    \n";
    std::cout << result;
    std::cout << "\n";
}
export void ratio()
{
    image<short> img2(2, 2, true);
    std::cout << "Image: \n" << img2 << "\n" << "Ratio: \n" << img2.ratio() << std::endl;
}
export void invertednline(image<short>& result, int x1, int y1, int x2, int y2)
{
    for (int i = 0; i < result.getrows(); ++i)
    {
        for (int j = 0; j < result.getcols(); ++j)
        {
            int x = j;
            int y = i;
            int pos = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
            if (pos > 0)
            {
                result(i, j) = invertedvalue(result(i, j));
            }
        }
    }
}
export void invertednlinedemo()
{
    image<short> img(3, 2, true);
    int x1 = 0;
    int y1 = 1;
    int x2 = 1;
    int y2 = 1;
    std::cout << "Original image:\n";
    std::cout << img;
    std::cout << "\nПрямая: " << "(" << x1 << "," << y1 << ")" << " - " << "(" << x2 << "," << y2 << ")\n";
    invertednline(img, x1, y1, x2, y2);
    std::cout << "\nAfter inverting the image:\n";
    std::cout << img;
    std::cout << '\n';
}