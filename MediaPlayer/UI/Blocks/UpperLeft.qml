import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import "../Components"

Rectangle {
  id: root

  ColumnLayout {
    Rectangle {
      id: spacer
      width: root.width
      height: 20
      color: transparentColor
    }

    FileDialog {
      id: file_dialog
      visible: false
    }

    Rectangle {
      id: upperBlock
      height: openBtn.height
      width: root.width
      color: transparentColor
      Row {
        anchors.right: parent.right
        spacing: 15
        ButtonStandart {
          id: openBtn
          mainText: "open playlist"
          backgroundColor: transparentColor
          onClicked: {
            file_dialog.visible = true
          }
        }
        ButtonStandart {
          id: newBtn
          mainText: "new playlist"
          backgroundColor: transparentColor
        }
      }
    }
    ListView {
      id: playList
      Layout.preferredHeight: root.height - upperBlock.height - bottom.height - spacer.height - 15
      Layout.preferredWidth: root.width
      model: PlayList
      delegate: Text {
        text: model.display
        width: 50
        height: 50
        color: "white"
      }

    }
    Rectangle {
      id: bottom
      height: openBtn.height
      width: root.width
      color: transparentColor
      Row {
        anchors.left: parent.left
        spacing: 15
        ButtonStandart {
          id: addBtn
          mainText: "add track"
          backgroundColor: transparentColor
          //enabled: false
          onClicked: {
            PlayListManager.addTrack();
          }
        }
        ButtonStandart {
          id: copyBtn
          mainText: "copy track"
          backgroundColor: transparentColor
          enabled: false
        }
        ButtonStandart {
          id: deleteBtn
          mainText: "delete track"
          backgroundColor: transparentColor
          enabled: false
        }
      }

    }
  }
}
