import QtQuick 2.0
import QtQuick.Controls 2.2
import "CustomComponents"

Rectangle {
    id: inputBar
    width: parent.width
    height: 135
    color: "transparent"

    Column{
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        Text {
            id: name
            width: parent.width
            height: parent.height*0.3
            text: qsTr("Non-Restoring Division Algorithm")
            color: "white"
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 16
        }

        Row{
            width: parent.width*0.6
            height: parent.height*0.15
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 24

            Text {
                width: parent.width*0.33 - 16
                height: parent.height
                color: "white"
                text: qsTr("Input A")
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                width: parent.width*0.33 - 16
                height: parent.height
                color: "white"
                text: qsTr("Input B")
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                width: parent.width*0.33 - 16
                height: parent.height
                color: "white"
                text: qsTr("Number System")
                verticalAlignment: Text.AlignVCenter
            }
        }

        Row{
            width: parent.width*0.6
            height: parent.height*0.25 - 5
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 24

            TextField{
                id: inputA
                width: parent.width*0.33 - 16
                height: parent.height
                validator: RegExpValidator{
                    regExp: switch(numberSystem.currentIndex){
                        case 0:
                            return /[0-1]+/
                        case 1:
                            return /[0-9]+/
                        case 2:
                            return /[0-9A-Fa-f]+/
                    }
                }
            }

            TextField{
                id: inputB
                width: parent.width*0.33 - 16
                height: parent.height
                validator: RegExpValidator{
                    regExp: switch(numberSystem.currentIndex){
                        case 0:
                            return /[0-1]+/
                        case 1:
                            return /[0-9]+/
                        case 2:
                            return /[0-9A-Fa-f]+/
                    }
                }
            }

            RComboBox{
                id: numberSystem
                width: parent.width*0.33 - 16
                height: parent.height
                model: ["Binary", "Decimal", "Hexadecimal"]
            }
        }

        RTextButton{
            id: calculateBtn
            width: parent.width*0.2
            height: parent.height*0.3 - 10
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Calculate"
            onClicked: {
                if(inputA.acceptableInput && inputB.acceptableInput){
                    nonRestoringDivisionCPP.InputA = inputA.text
                    nonRestoringDivisionCPP.InputB = inputB.text
                    nonRestoringDivisionCPP.NumberSystem = numberSystem.currentIndex
                    nonRestoringDivisionCPP.calculate()
                }
                else console.log("no")
            }
        }
    }
}
