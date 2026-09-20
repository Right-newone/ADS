export module functions;
import classes;
import std;

export void readnwrite() {
    Image<short> img(3, 4, false);
    std::cout << "До записи: "
        << img(1, 2) << '\n';

    img(1, 2) = 75;

    std::cout << "После записи: "
        << img(1, 2) << '\n';
    std::cout << "\n";
}

export void mult() {
    Image<short> img2(2, 3, true);
    Image<short> img3(3, 2, true);
    Image<short> result = img2 * img3;

    int maxRows = std::max(img2.get_rows(), img3.get_rows());

    for (int i = 0; i < maxRows; ++i)
    {
        if (i < img2.get_rows())
        {
            for (int j = 0; j < img2.get_cols(); ++j)
            {
                std::cout << std::setw(4) << img2(i, j);
            }
        }
        else
        {
            std::cout << std::string(img2.get_cols() * 4, ' ');
        }

        std::cout << "   * ";

        if (i < img3.get_rows())
        {
            for (int j = 0; j < img3.get_cols(); ++j)
            {
                std::cout << std::setw(4) << img3(i, j);
            }
        }
        else
        {
            std::cout << std::string(img3.get_cols() * 4, ' ');
        }

        std::cout << "   =   ";

        if (i < result.get_rows())
        {
            for (int j = 0; j < result.get_cols(); ++j)
            {
                std::cout << std::setw(5) << result(i, j);
            }
        }

        std::cout << "\n";
    }
    std::cout << "\n";
}

export void summ()
{
    Image<short> img2(2, 3, true);
    Image<short> img3(3, 2, true);
    Image<short> result = img2 + img3;

    int maxRows = std::max(img2.get_rows(), img3.get_rows());

    for (int i = 0; i < maxRows; ++i)
    {
        if (i < img2.get_rows())
        {
            for (int j = 0; j < img2.get_cols(); ++j)
                std::cout << std::setw(5) << img2(i, j);
        }
        else
        {
            std::cout << std::string(img2.get_cols() * 5, ' ');
        }

        std::cout << "   +   ";

        if (i < img3.get_rows())
        {
            for (int j = 0; j < img3.get_cols(); ++j)
                std::cout << std::setw(5) << img3(i, j);
        }
        else
        {
            std::cout << std::string(img3.get_cols() * 5, ' ');
        }

        std::cout << "   =   ";

        for (int j = 0; j < result.get_cols(); ++j)
            std::cout << std::setw(5) << result(i, j);

        std::cout << '\n';
    }

    std::cout << '\n';
}

export void dif()
{
    Image<short> img2(2, 3, true);
    Image<short> img3(3, 2, true);
    Image<short> result = img2 - img3;

    int maxRows = std::max(img2.get_rows(), img3.get_rows());

    for (int i = 0; i < maxRows; ++i)
    {
        if (i < img2.get_rows())
        {
            for (int j = 0; j < img2.get_cols(); ++j)
                std::cout << std::setw(5) << img2(i, j);
        }
        else
        {
            std::cout << std::string(img2.get_cols() * 5, ' ');
        }
        std::cout << "   -   ";

        if (i < img3.get_rows())
        {
            for (int j = 0; j < img3.get_cols(); ++j)
                std::cout << std::setw(5) << img3(i, j);
        }
        else
        {
            std::cout << std::string(img3.get_cols() * 5, ' ');
        }
        std::cout << "   =   ";

        for (int j = 0; j < result.get_cols(); ++j)
            std::cout << std::setw(5) << result(i, j);

        std::cout << '\n';
    }

    std::cout << '\n';
}

export void multnconst()
{
    Image<short> img2(2, 2, true);
    const int num = 6;
    Image<short> result = img2 * num;
    const int rows = img2.get_rows();
    const int cols = img2.get_cols();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << img2(i, j) << ' ';
        }

        std::cout << "   * " << num << "   =   ";

        for (int j = 0; j < cols; ++j)
        {
            std::cout << result(i, j) << ' ';
        }

        std::cout << '\n';
    }
    std::cout << '\n';
}

export void summnconst()
{
    Image<short> img2(2, 2, true);
    const int num = 6;
    Image<short> result = img2 + num;
    const int rows = img2.get_rows();
    const int cols = img2.get_cols();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << img2(i, j) << ' ';
        }

        std::cout << "   + " << num << "   =   ";

        for (int j = 0; j < cols; ++j)
        {
            std::cout << result(i, j) << ' ';
        }

        std::cout << '\n';
    }
    std::cout << '\n';
}

export void invert()
{
    Image<float> img2(2, 2, true);
    Image<float> result = !img2;
    for (int i = 0; i < img2.get_rows(); ++i)
    {
        for (int j = 0; j < img2.get_cols(); ++j)
        {
            std::cout << img2(i, j) << ' ';
        }

        std::cout << "  !  " << "  =  ";

        for (int j = 0; j < img2.get_cols(); ++j)
        {
            std::cout << result(i, j) << ' ';
        }
        std::cout << "\n";
    }
    std::cout << '\n';
}
 
export void ratio()
{
    Image<short> img2(2, 2, true);
    for (int i = 0; i < img2.get_rows(); ++i)
    {
        for (int j = 0; j < img2.get_cols(); ++j)
        {
            std::cout << img2(i, j) << ' ';
        }
        std::cout << "\n";
    }

    std::cout << "Коэффициент заполнения: " << img2.ratio(img2.get_rows(), img2.get_cols()) << std::endl;
}

export void invertednline(Image<short>& result, int x1, int y1, int x2, int y2)
{
    for (int i = 0; i < result.get_rows(); ++i)
    {
        for (int j = 0; j < result.get_cols(); ++j)
        {
            int x = j;
            int y = i;

            int pos = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
            if (pos > 0)
            {
                result(i, j) = invertedValue(result(i, j));
            }
        }
    }
}

export void invertednlinedemo()
{
    Image<short> img(3, 2, true);
    int x1 = 0;
    int y1 = 1;
    int x2 = 1;
    int y2 = 1;

    std::cout << "Исходное изображение:\n";
    for (int i = 0; i < img.get_rows(); ++i)
    {
        for (int j = 0; j < img.get_cols(); ++j)
        {
            std::cout << std::setw(5) << img(i, j);
        }
        std::cout << '\n';
    }
    std::cout << "\nПрямая: " << "(" << x1 << "," << y1 << ")" << " - " << "(" << x2 << "," << y2 << ")\n";

    invertednline(img, x1, y1, x2, y2);
    std::cout << "\nПосле инвертирования выше прямой:\n";
    for (int i = 0; i < img.get_rows(); ++i)
    {
        for (int j = 0; j < img.get_cols(); ++j)
        {
            std::cout << std::setw(5) << img(i, j);
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}