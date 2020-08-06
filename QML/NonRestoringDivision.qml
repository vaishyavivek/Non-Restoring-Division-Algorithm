import QtQuick 2.7

Rectangle{
    id: nonRestoringDivision
    anchors.fill: parent
    ListView{
        id: nonRestoringDivisionListView
        anchors.fill: parent
        model: nonRestoringDivisionCPP.OperationSteps
        clip: true
        spacing: 5
        headerPositioning: ListView.OverlayHeader

        header: Rectangle{
            width: parent.width
            height: 35
            z: 2
            Row{
                anchors.fill: parent
                Text{
                    width: parent.width*0.25
                    height: parent.height
                    text: "Comment"
                    font.pointSize: 12
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Text{
                    width: parent.width*0.25
                    height: parent.height
                    text: "Accumulator (A)"
                    font.pointSize: 12
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Text{
                    width: parent.width*0.25
                    height: parent.height
                    text: "Quotient (Q)"
                    font.pointSize: 12
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Text{
                    width: parent.width*0.25
                    height: parent.height
                    text: "Dividend (M)"
                    font.pointSize: 12
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }


        delegate: Rectangle{
            id: nonRestoringDivisionListViewDelegate

            width: parent.width
            height: model.modelData.IsStepDivision ? 50 : 35
            color: "transparent"

            Rectangle{
                id: spacing
                width: parent.width
                height: model.modelData.IsStepDivision ? 15 : 0
                color: "transparent"
                anchors.top: parent.top
            }

            Rectangle{
                width: parent.width
                height: 35
                anchors.bottom: parent.bottom
                z: 2

                Row{
                    anchors.fill: parent
                    Text{
                        width: parent.width*0.25
                        height: parent.height
                        text: model.modelData.Comment
                        font.family: "Nimbus Sans"
                        font.pointSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text{
                        width: parent.width*0.25
                        height: parent.height
                        text: model.modelData.InputA
                        font.family: "Nimbus Sans"
                        font.pointSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text{
                        width: parent.width*0.25
                        height: parent.height
                        text: model.modelData.InputB
                        font.family: "Nimbus Sans"
                        font.pointSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text{
                        width: parent.width*0.25
                        height: parent.height
                        text: model.modelData.OutputC
                        font.family: "Nimbus Sans"
                        font.pointSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                }
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.color = "#0a80a8"
                    onExited: parent.color = "white"
                }
            }
        }

        onModelChanged: currentIndex = count - 1
    }
}
