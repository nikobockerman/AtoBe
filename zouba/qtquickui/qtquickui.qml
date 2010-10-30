import Qt 4.7
import com.meego 1.0

Window {
    id: window

    Component {
        id: journeysPageComponent

        Page {
            title: "Journeys"
            ListView {
                anchors.fill: parent
                model: Journeys { }
                delegate: BasicListItem {
                    title: journeys
                    onClicked: {
                        window.nextPage(Qt.createComponent(source));
                    }
                }

                PositionIndicator { }
            }
        }
    }

    Component.onCompleted: {
        window.nextPage(pageComponent)
    }
}
