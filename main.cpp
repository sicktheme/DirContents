#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <conio.h>
using namespace Qt;

int main(int argc, char *argv[])
{
    QTextStream out(stdout);

    if(argc != 2) {
        qWarning("Single directory usage.");
        return 1;
    }

    QString directory = argv[1];
    QDir dir(directory);

    if(!dir.exists()) {
        qWarning("The directory does not exist"); return 1;
    }

    dir.setFilter(QDir::Files | QDir::AllDirs);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();

    int max_size = 0;

    foreach(QFileInfo fileinfo, list) {
        QString name = fileinfo.fileName();
        int size = name.size();

        if(size > max_size) {
            max_size = size;
        }
    }

    int lenght = max_size + 2;
    out << QString("Filename").leftJustified(lenght).append("Bytes") << endl;

    for(int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QString str = fileInfo.fileName().leftJustified(lenght);
        str.append(QString("%1").arg(fileInfo.size()));
        out << str << endl;
    }

    return 0;
}
