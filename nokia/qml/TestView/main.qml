import QtQuick 1.0
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    initialPage: mainPage

    MainPage {
        id: mainPage
    }

    ToolBarLayout
    {
            id: commonTools
            visible: false
    }
}
