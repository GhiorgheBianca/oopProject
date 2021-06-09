#include "Produse.h"
#include "InterfataGUI.h"
#include "Repository.h"
#include "Service.h"
#include "Tests.h"
#include "InterfataStatisticiGUI.h"
#include <QtWidgets/QApplication>
#include <unordered_map>
#include "ViewListGUI.h"
#include "WidgetListGUI.h"
#include "WidgetTableGUI.h"

int main(int argc, char *argv[])
{
    Tests tests{};
    tests.runTests();
    QApplication a(argc, argv);
    Produse w;

    Repository repo{ "produse.txt" };
    Validator validator{};
    Service service{ repo, validator };
    //InterfataGUI interfata{ service };
    //ViewListGUI interfata{ service };
    //WidgetListGUI interfata{ service };
    WidgetTableGUI interfata{ service };

    unordered_map<string, int> map = service.statistici();
    for (auto& key : map) {
        InterfataStatisticiGUI* i = new InterfataStatisticiGUI{ service, key.first };
        i->show();
    }
    
    interfata.show();
    return a.exec();
}
