/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
#include <QtGui>
#include <QApplication>
#include "../include/ros_gui/main_window.hpp"

int main(int argc, char **argv) {

    if( !ros::isInitialized() )
    {
      ros::init( argc, argv, "ros_gui", ros::init_options::AnonymousName );
    }
    QApplication app(argc, argv);
    MainWindow w(argc,argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
