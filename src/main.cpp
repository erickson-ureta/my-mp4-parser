#include "logger.hpp"
#include "mp4_parser.hpp"

int
main(int argc, char **argv)
{
    if (argc <= 1)
    {
        Logger::get().error("No input files specified.");
        Logger::get().error("usage: ./%s <file1.mp4> <file2.mp4> ... <fileN.mp4>",
                            argv[0]);

        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        Logger::get().info("----");
        Logger::get().info("Analyzing file: %s", argv[i]);
        Mp4Parser parser(argv[i]);
        parser.parseMp4File();
    }

    return 0;
}
