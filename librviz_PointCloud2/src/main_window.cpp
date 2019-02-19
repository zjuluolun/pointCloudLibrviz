/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/ros_gui/main_window.hpp"

using namespace Qt;

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    RvizPlugin rvi(this->ui.verticalLayout);
    
}

MainWindow::~MainWindow() {}

