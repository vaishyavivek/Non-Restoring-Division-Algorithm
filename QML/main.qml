import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import "CustomComponents"

ApplicationWindow{
    id: mainWindow
    visible: true
    minimumWidth: 900
    minimumHeight: 600
    color: "#312d2d"

    property int opType: 0

    Row{
        anchors.fill: parent
        Rectangle{
            id: sideBar
            width: 35
            height: parent.height
            color: "transparent"
            SidePanel{}
        }


        Column{
            width: parent.width - sideBar.width
            height: parent.height

            InputBar {
                id: inputBar
            }

            AnimationBar{
                id: animationComponent
                width: parent.width
                height: 100
            }

            TabView{
                id: mainTab
                width: parent.width
                height: parent.height - inputBar.height - animationComponent.height
                currentIndex: 0
                tabsVisible: false

                Tab{
                    title: "nonrestoring"
                    NonRestoringDivision{}
                }

                Tab{
                    title: "booth"
                    Rectangle{
                        id: boothsAlgorithm
                    }
                }
            }
        }
    }
}
