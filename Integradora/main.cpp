#include "main.hpp"

static std::string read_file(const char *name)
{
    std::ifstream file(name);
    std::string str, tmp;

    while (file >> tmp)
    {
        //If character is endline add it to string, to not lose it
        if (file.peek() == '\n')
            str = str + tmp + '\n';
        else
            str = str + tmp;
    }

    file.close();
    return str;
}

static void part1(std::vector <std::string> t, std::vector <std::string> m)
{
    int find_pos;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            find_pos = z_function(t[i].c_str(), m[j].c_str());
            if (find_pos == -1)
                printf("false\n");
            else
                printf("true %d\n", find_pos);
        }
    }
}

static void part2(std::vector <std::string> t)
{
    int find_pos;

    for (int i = 0; i < 2; i++)
    {
        int size = 0;
        find_pos = manacher(t[i].c_str(), &size);
        printf("%d %d\n", find_pos, size + find_pos);
    }
}

int main()
{
    std::vector <std::string> t;
    std::vector <std::string> m;

    t.push_back(read_file("transmission1.txt"));
    t.push_back(read_file("transmission2.txt"));
    m.push_back(read_file("mcode1.txt"));
    m.push_back(read_file("mcode2.txt"));
    m.push_back(read_file("mcode3.txt"));

    part1(t, m);
    part2(t);

    return 1;
}