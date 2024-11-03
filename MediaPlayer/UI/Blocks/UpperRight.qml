import QtQuick
import QtQuick.Layouts
import "../Components"

Rectangle {
  id: root
  property color textColor: "#56b4d0"

  Column {
    anchors.fill: parent

    Rectangle {
      id: upperBlock
      height: root.height / 2 / 2.5
      width: root.width
      color: transparentColor

      Rectangle {
        id: ch1_bass_wrapper
        height: ch1_bass_value.height + ch1_bass_title.height
        width: parent.width / 4
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color: parent.color

        Text {
          id: ch1_bass_value
          anchors.left: parent.left
          text: "0,0"
          font.family: "Arial"
          font.pointSize: 14
          font.bold: true
          color: textColor
        }

        Text {
          id: ch1_bass_title
          anchors.left: parent.left
          anchors.top: ch1_bass_value.bottom
          text: "C1-bass"
          font.family: "Arial"
          font.pointSize: 10
          color: Qt.alpha(textColor, 0.5)
        }
      }
      Rectangle {
        id: ch2_treble_wrapper
        height: ch2_treble_value.height + ch2_treble_title.height
        width: parent.width / 4
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        color: parent.color

        Text {
          id: ch2_treble_value
          anchors.right: parent.right
          text: "0,0"
          font.family: "Arial"
          font.pointSize: 14
          font.bold: true
          color: textColor
        }

        Text {
          id: ch2_treble_title
          anchors.right: parent.right
          anchors.top: ch2_treble_value.bottom
          text: "C2-treble"
          font.family: "Arial"
          font.pointSize: 10
          color: Qt.alpha(textColor, 0.5)
        }
      }
    }
    Rectangle {
      id: filterBlock
      height: root.height / 2 / 2.5
      width: root.width
      color: transparentColor

      Canvas {
        anchors.fill: parent
        onPaint: {
          var ctx = getContext("2d");
          ctx.clearRect(0, 0, width, height);

          // Настройки для линии
          ctx.strokeStyle = textColor;
          ctx.lineWidth = 2;

          // Начинаем рисование линии
          ctx.beginPath();
          ctx.moveTo(0, 0);
          ctx.lineTo((width / 2 - width / 15) , 0);
          ctx.lineTo((width / 2 + width / 15) , height);
          ctx.lineTo(width , height);

          ctx.moveTo(0, height);
          ctx.lineTo((width / 2 - width / 15) , height);
          ctx.lineTo((width / 2 + width / 15) , 0);
          ctx.lineTo(width , 0);

          ctx.stroke();
        }
      }

      Rectangle {
        id: gradient_wrapper
        height: gradient_value.height + gradient_title.height
        width: parent.width / 4
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color: parent.color

        Text {
          id: gradient_value
          anchors.left: parent.left
          text: "6" + " " + "db/Oct"
          font.family: "Arial"
          font.pointSize: 14
          font.bold: true
          color: textColor
        }

        Text {
          id: gradient_title
          anchors.left: parent.left
          anchors.top: gradient_value.bottom
          text: "Gradient"
          font.family: "Arial"
          font.pointSize: 10
          color: Qt.alpha(textColor, 0.5)
        }
      }
      Rectangle {
        id: freq_wrapper
        height: freq_value.height + freq_title.height
        width: parent.width / 4
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        color: parent.color

        Text {
          id: freq_value
          anchors.right: parent.right
          text: "1000" + " " + "Hz"
          font.family: "Arial"
          font.pointSize: 14
          font.bold: true
          color: textColor
        }

        Text {
          id: freq_title
          anchors.right: parent.right
          anchors.top: freq_value.bottom
          text: "frequency"
          font.family: "Arial"
          font.pointSize: 10
          color: Qt.alpha(textColor, 0.5)
        }
      }


    }
    Rectangle {
      id: bottomBlock
      height: root.height / 2 / 2.5
      width: root.width
      color: transparentColor
      Rectangle {
        id: ch2_bass_wrapper
        height: ch2_bass_value.height + ch2_bass_title.height
        width: parent.width / 4
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color: parent.color

        Text {
          id: ch2_bass_value
          anchors.left: parent.left
          text: "0,0"
          font.family: "Arial"
          font.pointSize: 14
          font.bold: true
          color: textColor
        }

        Text {
          id: ch2_bass_title
          anchors.left: parent.left
          anchors.top: ch2_bass_value.bottom
          text: "C2-bass"
          font.family: "Arial"
          font.pointSize: 10
          color: Qt.alpha(textColor, 0.5)
        }
      }
      Rectangle {
        id: ch1_treble_wrapper
        height: ch1_treble_value.height + ch1_treble_title.height
        width: parent.width / 4
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        color: parent.color

        Text {
          id: ch1_treble_value
          anchors.right: parent.right
          text: "0,0"
          font.family: "Arial"
          font.pointSize: 14
          font.bold: true
          color: textColor
        }

        Text {
          id: ch1_treble_title
          anchors.right: parent.right
          anchors.top: ch1_treble_value.bottom
          text: "C1-treble"
          font.family: "Arial"
          font.pointSize: 10
          color: Qt.alpha(textColor, 0.5)
        }
      }
    }

    Rectangle {
      id: paramBlock
      height: root.height / 3
      width: root.width
      //color: transparentColor
      ParametersView {

      }

    }
  }
}
