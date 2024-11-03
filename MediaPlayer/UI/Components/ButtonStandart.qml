import QtQuick 2.15
import QtQuick.Controls

Button {
  id: root
  property string mainText: ""
  property color btnColor: enabled ? "#56b4d0" :  Qt.alpha("#56b4d0", 0.3)
  property color backgroundColor: "white"
  width: 125
  height: 35
  Text {
    id: txt
    anchors.centerIn: parent
    text: mainText
    font.family: "Arial"
    font.pointSize: 14
    color: btnColor
  }
  background: Rectangle {
    border.color: btnColor
    border.width: 2
    color: backgroundColor
  }

}
