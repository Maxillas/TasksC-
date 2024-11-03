import QtQuick
import QtQuick.Shapes
import QtQuick.Layouts
import "Blocks"

Rectangle {
  id: root
  width: 1000
  height: 550
  property color backgroundColor: "#043544"
  property color transparentColor: Qt.alpha(backgroundColor, 0)

  gradient: Gradient {
    orientation: Gradient.Horizontal
    GradientStop { position: 0.0; color: "#021621" }
    GradientStop { position: 0.5; color: backgroundColor} // Центр яркий
    GradientStop { position: 1.0; color: "#021621" }
  }

  Column {
    anchors.fill: parent
    //anchors.topMargin: 25
    anchors.margins: 25
    Rectangle {
      id: upper
      height: root.height * 2/3 - 25 // 25 = TopMargin
      width: root.width - 75 // 75 left + right margin + spacing
      color: transparentColor

      Row {
        spacing: 25

        UpperLeft {
          id: upperLeftBlock
          height: upper.height
          width: upper.width / 2
          color: transparentColor
        }
        UpperRight {
          id: upperRightBlock
          height: upper.height
          width: upper.width / 2
          color: transparentColor
        }
      }
    }
    Bottom {
      id: bottomBlock
      height: root.height * 1/3 - 25
      width: root.width - 75
      color: transparentColor
    }
  }
}
