#include <fstream>

int main()
{
    std::ofstream out("/tmp/demo_file_deleteme");
    out << "write to file hello\r\n";
    out << "next line.\r\n";

    printf("write to file finished.\r\n");
}
