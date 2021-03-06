import QtQuick 2.5

import Governikus.Global 1.0


Rectangle {
	id: content
	height: parent.height
	width: parent.width
	color: Constants.background_color

	ListModel {
		id: navModel

		ListElement {
			imageOn: "qrc:///images/iOS/tabBar/Ausweisen-on.png"
			imageOff: "qrc:///images/iOS/tabBar/Ausweisen-off.png"
			desc: QT_TR_NOOP("Identify")
			condition: "identify"
		}

		ListElement {
			imageOn: "qrc:///images/iOS/tabBar/Anbieter-on.png"
			imageOff: "qrc:///images/iOS/tabBar/Anbieter-off.png"
			desc: QT_TR_NOOP("Provider")
			condition: "provider"
		}

		ListElement {
			imageOn: "qrc:///images/iOS/tabBar/Verlauf-on.png"
			imageOff: "qrc:///images/iOS/tabBar/Verlauf-off.png"
			desc: QT_TR_NOOP("History")
			condition: "history"
		}

		ListElement {
			imageOn: "qrc:///images/iOS/tabBar/Pin-on.png"
			imageOff: "qrc:///images/iOS/tabBar/Pin-off.png"
			desc: QT_TR_NOOP("PIN Management")
			condition: "pin"
		}

		ListElement {
			imageOn: "qrc:///images/iOS/tabBar/More-on.svg"
			imageOff: "qrc:///images/iOS/tabBar/More-off.svg"
			desc: QT_TR_NOOP("More")
			condition: "more"
		}
	}

	Rectangle {
		id: topBorderLine
		width: parent.width
		height: Utils.dp(0.5)
		color: Constants.grey
	}

	Row {
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.top: topBorderLine.bottom

		Repeater {
			id: repeater
			model: navModel

			delegate: NavigationItem {
				height: parent.height
				width: parent.width / navModel.count
				source: baseItem.state === condition ? imageOn : imageOff
				textColor: baseItem.state === condition ? Constants.blue : Constants.grey
				text: qsTr(desc) + settingsModel.translationTrigger
				onClicked: baseItem.state = condition
			}
		}
	}
}
