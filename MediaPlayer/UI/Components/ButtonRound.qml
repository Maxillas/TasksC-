import QtQuick 2.15
import QtQuick.Controls

Button {
  id: root
  width: root.height
  property color btnColor: enabled ? "#56b4d0" :  Qt.alpha("#56b4d0", 0.3)
  property color transparentColor: Qt.alpha(backgroundColor, 0)

  property url imageSource: ""

  IconImage {
    id: btnImage
    source: imageSource
    anchors.centerIn: parent
    width: root.width / 1.5
    height: width
    fillMode: Image.PreserveAspectFit
    color: btnColor

  }


  background: Rectangle {
    id: background
    border.color: btnColor
    border.width: 2
    color: transparentColor
    radius: root.width / 2
  }


}
