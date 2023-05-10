#include"headers/Entry.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Entry entry;
    entry.show();
    return a.exec();
}