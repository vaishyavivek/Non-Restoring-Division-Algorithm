import QtQuick 2.7

Rectangle {
    id: animationBar
    property var shiftingBit: nonRestoringDivisionCPP.Operand2
    color: "transparent"

    Rectangle{
        id: operationText
        width: parent.width
        height: parent.height*0.3
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"
        Text {
            anchors.topMargin: 5
            width: parent.width
            height: parent.height
            text: nonRestoringDivisionCPP.OperationText
            font.family: "URW Bookman"
            color: "white"
            font.pointSize: 10
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Text {
        text: nonRestoringDivisionCPP.FOperand1
        visible: text != "-32767"
        font.pointSize: 14
        font.bold: true
        color: "blue"
        x: operand1.x + operand1.width/2
        y: operand1.y - operand1.height
    }

    ListView{
        id: operand1
        x: parent.x + parent.width*0.45 - width*2
        width: (height*0.5 + 5)*count
        height: parent.height*0.3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        model: nonRestoringDivisionCPP.Operand1
        orientation: ListView.Horizontal
        spacing: 5

        delegate: Rectangle{
            height: parent.height
            width: height*0.5
            color: "transparent"
            Image {
                width: parent.width
                height: parent.height
                source: "/local/assets/" + modelData + "-grey.png"
                sourceSize.height: height*0.75
                sourceSize.width: width*0.75
                anchors.centerIn: parent
            }
        }
    }

    Text {
        text: nonRestoringDivisionCPP.FOperand2
        visible: text != "-32767"
        font.pointSize: 14
        font.bold: true
        color: "blue"
        x: operand2.x + operand1.width/2
        y: operand2.y - operand2.height
    }

    ListView{
        id: operand2
        x: parent.x + parent.width*0.55 + width*0.5
        width: (height*0.5 + 5)*count
        height: parent.height*0.3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        model: nonRestoringDivisionCPP.Operand2
        orientation: ListView.Horizontal
        spacing: 5

        delegate: Rectangle{
            height: parent.height
            width: height*0.5
            color: "transparent"
            Image {
                width: parent.width
                height: parent.height
                source: "/local/assets/" + modelData + "-grey.png"
                sourceSize.height: height*0.75
                sourceSize.width: width*0.75
                anchors.centerIn: parent
            }
        }
    }

    Rectangle{
        id: shiftingBitAnimatingRect
        height: parent.height*0.3
        width: height*0.5
        color: "transparent"
        visible: false
        y: operand2.y

        Image {
            width: parent.width
            height: parent.height
            source: "/local/assets/" + shiftingBit[0] + "-grey.png"
            sourceSize.height: height*0.75
            sourceSize.width: width*0.75
            anchors.centerIn: parent
        }
    }

    SequentialAnimation{
        id: shiftBitAnimation
        NumberAnimation{
            target: shiftingBitAnimatingRect
            property: "x"
            from: operand2.x
            to: operand1.x + operand1.width
            duration: 2000
        }
        PropertyAnimation{
            target: shiftingBitAnimatingRect
            property: "visible"
            to: false
        }

    }

    Rectangle{
        id: invertBitAnimatingRect
        height: 25
        anchors.top: operationText.bottom
        anchors.left: operand1.left
        color: "transparent"
        visible: false
        Image {
            width: parent.width
            height: parent.height
            source: "/local/assets/invert-bit-connectorpng.png"
            sourceSize.width: parent.width
        }
    }

    SequentialAnimation{
        id: invertBitAnimation
        NumberAnimation{
            target: invertBitAnimatingRect
            property: "width"
            from: 0
            to: (operand2.x + operand2.width*1.2) - operand1.x
            duration: 1500
        }
        PropertyAnimation{
            target: invertBitAnimatingRect
            property: "visible"
            to: false
            duration: 500
        }
    }

    Connections{
        target: nonRestoringDivisionCPP
        onOperationChanged:{
            if(nonRestoringDivisionCPP.Operation === 1){
                shiftingBitAnimatingRect.visible = true
                shiftBitAnimation.start()
            }
            else if(nonRestoringDivisionCPP.Operation === 4){
                invertBitAnimatingRect.visible = true
                invertBitAnimation.start()
            }
        }
    }

    Connections{
        target: shiftBitAnimation
        onFinished: nonRestoringDivisionCPP.letFurtherUpdateHappen()
    }

    Connections{
        target: invertBitAnimation
        onFinished: nonRestoringDivisionCPP.letFurtherUpdateHappen()
    }
}
