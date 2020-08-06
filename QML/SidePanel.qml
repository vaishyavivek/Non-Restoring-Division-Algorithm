import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
//import Qt.labs.platform 1.0
import "CustomComponents"

Popup {
    id: sidePanel
    property bool isExpanded: false
    property bool isPined: true
    property int normalizedWidth: 35
    property int widthWhenExpanded: 200

    padding: 0
    rightPadding: 1
    width: parent.width
    height: parent.height
    closePolicy: Popup.NoAutoClose

    Rectangle{
        id: sidePanelParentRect
        width: parent.width
        height: parent.height
        color: "#312d2d"

        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "lightgray"
        }

        Column{
            anchors.fill: parent
            spacing: 2
            Rectangle{
                id: controlBar
                width: parent.width
                height: normalizedWidth //OR iconScale
                color: "transparent"

                RImageButton{
                    id: hamburgerBtn
                    width: normalizedWidth
                    height: normalizedWidth
                    icon.source: "/local/assets/icons-menu.svg"
                    icon.color: "white"
                    onClicked: (!isPined && isExpanded) ? reverseExpandMenu() : expandMenu()
                }

                RImageButton{
                    id: pinBtn
                    width: normalizedWidth*0.5
                    height: width
                    visible: isExpanded
                    anchors.right: parent.right
                    icon.source: isPined ? "/local/assets/icons-pin.png" : "/local/assets/icons-unpin.svg"
                    icon.color: "white"
                    onClicked: rFileSystem.IsPinPinned = !isPined
                }
            }
        }
    }

    PropertyAnimation{
        id: expandAnimation
        target: sidePanel
        property: "width"
        to: widthWhenExpanded
        duration: 200//nonRestoringDivisionCPP.GlobalAnimationDuration*2
    }

    PropertyAnimation{
        id: reverseExpandAnimation
        target: sidePanel
        property: "width"
        to: normalizedWidth
        duration: 200//nonRestoringDivisionCPP.GlobalAnimationDuration*2
    }

    Component.onCompleted: sidePanel.open()

    function expandMenu(){
        if(!isExpanded){
            isExpanded = true
            expandAnimation.start()
        }
        if(isPined)
            sideBar.width = widthWhenExpanded
    }

    function reverseExpandMenu(){
        if(isExpanded){
            isExpanded = false
            reverseExpandAnimation.start()
            sideBar.width = normalizedWidth
        }
    }

    onIsPinedChanged: {
        widthWhenExpanded = 200
        isPined ? expandMenu() : reverseExpandMenu()
    }
}
