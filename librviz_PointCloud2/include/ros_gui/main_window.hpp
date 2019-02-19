/**
 * @file /include/ros_gui/main_window.hpp
 *
 * @brief Qt based gui for ros_gui.
 *
 * @date November 2010
 **/
#ifndef ros_gui_MAIN_WINDOW_H
#define ros_gui_MAIN_WINDOW_H

//#include <QtGui/QMainWindow> //qt4/qt5
#include "QMainWindow"
#include "ui_main_window.h"
#include "qnode.hpp"

#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qlistview.h>
#include <qstringlistmodel.h>
#include <QThread>

//rviz
//#ifndef Q_MOC_RUN //避免Qt的Moc工具对Boost的代码进行Moc
//#include <ros/ros.h>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/default_plugin/view_controllers/orbit_view_controller.h>
#include <rviz/view_manager.h>
//#endif

//namespace rviz {
//class Display;
//class RenderPanel;
//class VisualizationManager;
//}



//class WorkerThread : public QObject
//{
//    Q_OBJECT
//
//public:
//    WorkerThread(QObject *parent = 0);
//    //~WorkerThread();
//
//public Q_SLOTS:
//    void computeSth();
//};

class RvizPlugin: public QObject{
    Q_OBJECT
public:
    RvizPlugin(QVBoxLayout* ui){
        rviz_panel = new rviz::RenderPanel;
        rvizManager =  new rviz::VisualizationManager(rviz_panel);
        //viewManager = new rviz::ViewManager();


        rviz_panel->initialize(rvizManager->getSceneManager(), rvizManager);
        rviz_panel->setBackgroundColor( Ogre::ColourValue(0, 0,0,0.3)); //no use
        ui->addWidget(rviz_panel);

        rvizManager->initialize();
        rvizManager->startUpdate();
        rvizManager->setFixedFrame("camera_init");
        rviz::Display *grid = rvizManager->createDisplay("rviz/Grid","Grid",true);

        viewManager = rvizManager->getViewManager();
        viewManager->setRenderPanel(rviz_panel);
        viewManager->setCurrentViewControllerType("rviz/Orbit");
        viewManager->getCurrent()->subProp("Target Frame")->setValue("/aft_mapped");

        //rviz::OrbitViewController* orbitView = viewManager->create("rviz/Orbit");
        //rviz::ViewController* orbitView = viewManager->create("rviz/Orbit");
        //rviz::OrbitViewController* orbitView = new  rviz::OrbitViewController;
        //orbitView->subProp("Target Frame")->setValue("/aft_mapped");
        //viewManager->setCurrentFrom(orbitView);
        //orbitView->subProp("topic")->setValue("/aft_mapped");
        //orbitView->initialize(rvizManager);
        //orbitView->activate();
        //orbitView->update(0.01,0.01);
        //orbitView->subProp("Distance")->setValue(10);
        //orbitView->subProp("Value")->setValue("Orbit (rviz)");
        //rviz_panel->setViewController(orbitView);

        enablePointCloud2("/surfStack", "FlatColor", "1");
        rviz::Display* frameRgister=enablePointCloud2("/velodyne_cloud_registered", "Intensity", "2");
        enableOdometry("/integrated_to_init", "10000", "Axes");

        //rviz::OrbitViewController* vie = new rviz::OrbitViewController();
        //vie->subProp("Target Frame")->setValue("camera");
        //enablePointCloud2("/apollo/sensor/velodyne64/PointCloud2");
        //enablePointCloud2("/apollo/sensor/velodyne64/PointCloud2");

    }
    void enableOdometry(QString topic, QString keep, QString shape){
        rviz::Display *odometry = rvizManager->createDisplay("rviz/Odometry","Odometry", true);
        odometry->subProp("Topic")->setValue(topic);//"/apollo/sensor/velodyne64/PointCloud2");
        odometry->subProp("Keep")->setValue(keep);
        odometry->subProp("Shape")->setValue(shape);
    }
    rviz::Display* enablePointCloud2(QString topic, QString corlorTransform, QString size){
        rviz::Display *pointCloud = rvizManager->createDisplay("rviz/PointCloud2","PointCloud2", true);
        pointCloud->subProp("Topic")->setValue(topic);//"/apollo/sensor/velodyne64/PointCloud2");
        pointCloud->subProp("Style")->setValue("Points");
        pointCloud->subProp("Size (Pixels)")->setValue(size);
        pointCloud->subProp("Color Transformer")->setValue(corlorTransform);
        pointCloud->subProp("Invert Rainbow")->setValue("true");
        return pointCloud;
    }


    public slots:
    void on_pushButton_clicked(){std::cout<<3<<std::endl;}
    void hhh(){std::cout<<2<<std::endl;}
private:
    rviz::RenderPanel* rviz_panel;// = new rviz::RenderPanel;
    rviz::VisualizationManager *rvizManager;// =  new rviz::VisualizationManager(pointCloud_panel);
    rviz::ViewManager* viewManager;
};

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindowDesign ui;
    QNode qnode;

};

#endif // ros_gui_MAIN_WINDOW_H
