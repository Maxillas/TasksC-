import QtQuick
import QtQuick.Layouts
import "../Components"
import "../Resources"

Rectangle {
  id: root
  property color textColor: "#5caabe"
  property color backgroundColor: "#043544"
  property color transparentColor: Qt.alpha(backgroundColor, 0)

  // height: root.height * 1/3
  // width: root.width
  // color: transparentColor

  ProgressBar {
    id: progressBar
    width: root.width
    anchors.top: root.top
    anchors.topMargin: 15
  }

  Text {
    id: progress_time
    anchors.left: parent.left
    anchors.top: progressBar.bottom
    anchors.topMargin: 10
    anchors.leftMargin: 5
    text: "00:59"
    //font.family: "Arial"
    font.pointSize: 12
    color: textColor
  }

  Text {
    id: full_time
    anchors.right: parent.right
    anchors.top: progressBar.bottom
    anchors.topMargin: 10
    anchors.rightMargin: 5
    text: "30:00"
    font.family: "Arial"
    font.pointSize: 12
    color: textColor
  }

  Text {
    id: txt
    anchors.left: parent.left
    anchors.top: progress_time.bottom
    anchors.topMargin: 10
    anchors.leftMargin: 5
    text: qsTr("Playlist time ") + "0:29:00"
    font.family: "Arial"
    font.pointSize: 12
    color: textColor
  }

  // Rectangle {
  //   id: button_wrapper
  //   anchors.top: progressBar.bottom
  //   anchors.horizontalCenter: parent.horizontalCenter
  //   height: parent.height
  //   //width: parent.width / 2
  //   color: transparentColor

    ButtonRound {
      id: stopBtn
      height: parent.height / 3
      anchors {
        verticalCenter: playBtn.verticalCenter
        right: prevBtn.left
        rightMargin: 25
      }
      imageSource: "../Resources/stop.png"
      onClicked: {
        AudioPlayer.stop();
      }
    }
    ButtonRound {
      id: prevBtn
      height: parent.height / 3
      anchors {
        verticalCenter: playBtn.verticalCenter
        right: playBtn.left
        rightMargin: 25
      }
      imageSource: "../Resources/backward.png"

    }
    ButtonRound {
      id: playBtn
      height: parent.height
      anchors {
        horizontalCenter: parent.horizontalCenter
        top: progressBar.bottom
        topMargin: 5
      }
      imageSource: {
        if(!AudioPlayer) {
        return ""; //проверка на существование объекта с++
        }
        !AudioPlayer.isPlaying ? "../Resources/play.png" : "../Resources/pause.png"
      }

      onClicked: {
        AudioPlayer.play();
      }
    }
    ButtonRound {
      id: nextBtn
      height: parent.height / 3
      anchors {
        verticalCenter: playBtn.verticalCenter
        left: playBtn.right
        leftMargin: 25
      }
      imageSource: "../Resources/forward.png"
    }
    ButtonRound {
      id: repeatBtn
      height: parent.height / 3
      anchors {
        verticalCenter: playBtn.verticalCenter
        left: nextBtn.right
        leftMargin: 25
      }
      imageSource: "../Resources/repeat.png"
    }


}
