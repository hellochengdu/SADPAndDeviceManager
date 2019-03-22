import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.0 as Control20
import QtMultimedia 5.5
import Qt.Ipserver 1.0

ApplicationWindow {
	objectName:"window"
    visible: true
    width: Screen.desktopAvailableWidth/2;
    height: Screen.desktopAvailableHeight/2;
    title: qsTr("SADPAndDeviceManager");
	style:ApplicationWindowStyle{
        background: BorderImage {
            source: "JF-NAS.ico"
            border.left: 5; border.top: 5
            border.right: 5; border.bottom: 5
        }
    }
	IPServer{
		id:ioslinux;
	}
    toolBar:ToolBar{
        //anchors.fill:parent;
        id:maintool;
        Row{
            ToolButton{
                text:"主界面";
                onClicked: {
                    mainInterface.visible=true;
                    deviceInterface.visible=false;
                    deviceConfiguration.visible=false;
                    videoProgramface.visible=false;
                    logManagementInterface.visible=false;
                }
            }
            ToolButton{
                id: devicetool
                text:"设备管理";
                onClicked: {
                   mainInterface.visible=false;
                   deviceInterface.visible=true;
                   deviceConfiguration.visible=false;
                   videoProgramface.visible=false;
                   logManagementInterface.visible=false;
                }
            }
            ToolButton{
                id:devicetoolofp;
                text:"设备配置";
                onClicked: {
                    mainInterface.visible=false;
                    deviceInterface.visible=false;
                    deviceConfiguration.visible=true;
                    videoProgramface.visible=false;
                    logManagementInterface.visible=false;
                }
            }
            ToolButton{
                id:videotool;
                text:"录像计划";
                onClicked: {
                    mainInterface.visible=false;
                    deviceInterface.visible=false;
                    deviceConfiguration.visible=false;
                    videoProgramface.visible=true;
                    logManagementInterface.visible=false;
                }
            }
            ToolButton{
                id:logtool;
                text:"日志管理";
                onClicked: {
                    mainInterface.visible=false;
                    deviceInterface.visible=false;
                    deviceConfiguration.visible=false;
                    videoProgramface.visible=false;
                    logManagementInterface.visible=true;
                }
            }
        }
    }
    function settool(){
        devicetool.visible=false;
        devicetoolofp.visible=false;
        videotool.visible=false;
        logtool.visible=false;
    }
    Rectangle{
        anchors.fill: parent;
        id: mainInterface;
        visible: true;
        Grid{
            columns: 2;
            spacing: 2;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: parent.horizontalCenter;
            columnSpacing: 50;
            rowSpacing: 50;
            Button{
            id: deviceManager;
            text:"设备管理";
            width: 60;
            height: 40;
            onClicked: {
                mainInterface.visible=false;
                deviceInterface.visible=true;
                deviceConfiguration.visible=false;
                videoProgramface.visible=false;
                logManagementInterface.visible=false;
				devicetool.visible=true;
                }
            }
            Button{
            id: deviceLayout;
            text:"设备配置";
            width: 60;
            height: 40;
            onClicked: {
                mainInterface.visible=false;
                deviceInterface.visible=false;
                deviceConfiguration.visible=true;
                videoProgramface.visible=false;
                logManagementInterface.visible=false;
				devicetoolofp.visible=true;
            }
        }
            Button{
            id: videoProgram;
            text:"录像计划";
            width: 60;
            height: 40;
            onClicked: {
                mainInterface.visible=false;
                deviceInterface.visible=false;
                deviceConfiguration.visible=false;
                videoProgramface.visible=true;
                logManagementInterface.visible=false;
				videotool.visible=true;
            }
        }
            Button{
            id: logManagement;
            text:"日志管理";
            width: 60;
            height: 40;
            onClicked: {
                mainInterface.visible=false;
                deviceInterface.visible=false;
                deviceConfiguration.visible=false;
                videoProgramface.visible=false;
                logManagementInterface.visible=true;
				logtool.visible=true;
            }
          }
        }

    }
    Rectangle{
        visible: false;
        anchors.fill: parent;
        id: deviceInterface;
        CheckBox{
            id:checkAll;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 8;
            text:"全选框";
        }
        Button{
            id:refresh;
            anchors.left: checkAll.right;
            anchors.top: parent.top;
            text:"刷新";
        }
        Button{
            id:searchSetting;
            anchors.left: refresh.right;
            anchors.top: parent.top;
            text:"搜索设置";
        }
        Button{
            id:deviceFrom;
            anchors.left: searchSetting.right;
            anchors.top: parent.top;
            text:"导出表格";
        }
        Button{
            id:importFrom;
            anchors.left: deviceFrom.right;
            anchors.top: parent.top;
            text:"导入表格";
        }
        Button{
            id:manuallyFrom;
            anchors.left: importFrom.right;
            anchors.top: parent.top;
            text:"手动添加";
        }
        Button{
            id:upgrade;
            anchors.left: manuallyFrom.right;
            anchors.top: parent.top;
            text:"升级";
        }
        /*ListView{
            id:deviceSheet;
            interactive: false;
            clip:true;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            anchors.top: upgrade.bottom;
            header: Rectangle{

            }
        }*/
        TableView{
            id:deviceSheet_t;
            visible: true;
            anchors.left: deviceInterface.left;
            anchors.right: deviceInterface.right;
            anchors.bottom: deviceInterface.bottom;
            anchors.top: upgrade.bottom;
            //property var holdMenuModelDataArray: null;
            //backgroundVisible: false;
            //frameVisible: false;
            TableViewColumn{
                role:"checkBox";
                title: "";
                //width: 20;
                visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"type";
                title:"系列";
                visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role: "model";
                title:"型号";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"IP";
                title: "IP";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"port";
                title: "端口";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"admin";
                title:"用户名";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"password";
                title:"密码";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }

            TableViewColumn{
                role:"MAC";
                title: "MAC";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"gateway";
                title:"网关";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"subnetMask";
                title: "子网掩码";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"deviceSerialNumber";
                title:"设备序列号";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"versionNumber";
                title:"版本号";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"serialNumber";
                title:"序列号";
				visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            itemDelegate: Rectangle{
                id: tableCell
                anchors.fill: parent;
                anchors.margins: 3;
                border.color: "blue";
                radius:3;
                color: styleData.selected ? "transparent" : "#1A4275";
                Text{
                    id: textID;
                    text:styleData.value ;
                    font.family: "微软雅黑";
                    font.pixelSize: 12;
                    anchors.fill: parent;
                    color: "white";
                    elide: Text.ElideRight;
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            headerDelegate :Rectangle{//设置表头的样式
                implicitWidth: 10
                implicitHeight: 24
                gradient: Gradient {
                          GradientStop { position: 0.0; color: "white" }
                          GradientStop { position: 0.5; color: "black"}
                          GradientStop { position:1.0;  color: "white"}
                      }
                border.width: 1
                border.color: "gray"
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 4
                    anchors.right: parent.right
                    anchors.rightMargin: 4
                    text: styleData.value
                    color: "red"
                    font.bold: true
                }
            }
           // headerDelegate: headerDele;
            //rowDelegate: rowDele;
           // model:ListModel{}
            //Custom header delegate
            /*Component{
                id:headerDele;
                Rectangle{
                    id:headerRect;
                    height: deviceSheet_t.height;
                    border.color: frameBorderColor;
                    color: "transparent";
                    radius: 3;
                    Text{
                        text:styleDele.value;
                        anchors.centerIn: parent;
                        font.family: "微软雅黑";
                        font.pixelSize: 12;
                        color: "white";
                    }
                }
            }*/
            //Custom row delegate
            /*Component{
                id:rowDele;
                Rectangle{
                    id:rect;
                    height: 42;
                    color:"transparent";
                }
            }*/
            //Update the table title column height and role
            function updateColumnTable(arrayData){
            }

        }
    }
    Rectangle{
        visible: false;
        anchors.fill: parent;
        id: videoProgramface;
        ListView{
            id:deviceList;
            width: 100;
            anchors.top:parent.top;
            anchors.topMargin: 20;
            anchors.left: parent.left;

        }
        Rectangle{
            id:deviceVideo;
            anchors.top:parent.top;
            anchors.left:deviceList.right;
            anchors.leftMargin: 100;
            anchors.right: parent.right;
            Label{
                id: videoLabel;
                anchors.top:parent.top;
                anchors.topMargin: 50;
                anchors.left:parent.left;
                text:"录像模板";
                color: "blue"
                font.pixelSize: 22;

            }
            ComboBox{
               anchors.top:videoLabel.bottom;
               anchors.topMargin: 20;
               width:100;
               id:templateall
               model:ListModel{
                id:templateType;
                ListElement{text:"全天模板";}
                ListElement{text:"事件模板";}
                ListElement{text:"工作日模板";}
               }
            }
            Button{
                id:template1;
                anchors.top:templateall.bottom;
                anchors.topMargin: 20;
                text:"模板1";
                onClicked: {

                }
            }
            Button{
                id:template2;
                anchors.top:template1.bottom;
                anchors.topMargin: 20;
                text:"模板2";
                onClicked: {

                }
            }
            Button{
                id:template3;
                anchors.top:template2.bottom;
                anchors.topMargin: 20;
                text:"模板3";
                onClicked: {

                }
            }
            Button{
                id:template4;
                anchors.top:template3.bottom;
                anchors.topMargin: 20;
                text:"模板4";
                onClicked: {

                }
            }
            Button{
                id:programVideo;
                anchors.top:videoLabel.top;
                anchors.left: videoLabel.right;
                anchors.leftMargin: 30;
                text:"计划录像";
            }
            Button{
                id:eventVideo;
                anchors.top:programVideo.top;
                anchors.left: programVideo.right;
                text:"事件录像";
            }
            ComboBox{
                id:aisleNumberall;
                anchors.top:eventVideo.top;
                anchors.left:eventVideo.right;
                width:80;
                model:ListModel{
                 id:aisleNumber;
                 ListElement{text:"通道1";}
                 ListElement{text:"通道2";}
                 ListElement{text:"通道3";}
                }
            }
            Button{
                id:copyTo;
                anchors.top:aisleNumberall.top;
                anchors.left: aisleNumberall.right;
                text:"复制到";
            }
            Button{
                id:saveButton;
                anchors.top:copyTo.top;
                anchors.left: copyTo.right;
                text:"保存";
            }
            Label{
                anchors.top:saveButton.bottom;
                anchors.topMargin: 32;
                anchors.left: templateall.right;
                anchors.leftMargin: 10;
                text:"周一";
                font.pixelSize: 22;
                color: "red"
            }
            Rectangle{
                id:timeQuanMon;
                anchors.top:saveButton.bottom;
                anchors.topMargin: 20;
                anchors.left: templateall.right;
                anchors.leftMargin: 50;
                Image {
                    id: videoimagemon
                    anchors.left:parent.left;
                    anchors.leftMargin: 20;
                    anchors.top:parent.top;
                    width:364;
                    source: "videogramm.png"
                }
                Rectangle{
                    anchors.top:videoimagemon.bottom;
                    anchors.left: parent.left;
                    anchors.leftMargin: 20;
                    width: 360;
                    height: 20;
                    border.width: 1;
                    border.color: "black";
                    id:areaofmousemon;
                    //color: "blue";
                    property int openx: 0;
                    property bool ox: false;
                    property int endx: 0;
                    property bool ex: false;
                    function createopen(){
                        if(goodvideomon.visible==true){
                            goodvideomon.visible=false;
                        }
                        if(openx>endx){
                            goodvideomon.x=endx;
                            goodvideomon.width=openx-endx;
                        }else{
                            goodvideomon.x=openx;
                            goodvideomon.width=endx-openx;
                        }
                        goodvideomon.color="blue";
                        goodvideomon.visible=true;
                    }
                    Rectangle{
                        visible: false;
                        id: goodvideomon;
                        anchors.top:parent.top;
                        anchors.bottom: parent.bottom;
                    }
                    MouseArea{
                        id:videomousemon;
                        anchors.fill: parent;
                        enabled: true;
                        onPressAndHold: {
                            areaofmousemon.ox=true;
                            areaofmousemon.openx=mouseX;
                        }
                        onReleased: {
                            areaofmousemon.ex=true;
                            areaofmousemon.endx=mouseX;
                            if(areaofmousemon.ox==true){
                                areaofmousemon.createopen();
                                areaofmousemon.ox=false;
                            }
                        }

                    }

                }
            }
            Label{
                anchors.top:saveButton.bottom;
                anchors.topMargin: 72;
                anchors.left: templateall.right;
                anchors.leftMargin: 10;
                text:"周二";
                font.pixelSize: 22;
                color: "red"
            }
            Rectangle{
                id:timeQuanTue;
                anchors.top:saveButton.bottom;
                anchors.topMargin: 62;
                anchors.left: templateall.right;
                anchors.leftMargin: 50;
                Image {
                    id: videoimageTue
                    anchors.left:parent.left;
                    anchors.leftMargin: 20;
                    anchors.top:parent.top;
                    width:364;
                    source: "videogramm.png"
                }
                Rectangle{
                    anchors.top:videoimageTue.bottom;
                    anchors.left: parent.left;
                    anchors.leftMargin: 20;
                    width: 360;
                    height: 20;
                    border.width: 1;
                    border.color: "black";
                    id:areaofmouseTue;
                    //color: "blue";
                    property int openx: 0;
                    property bool ox: false;
                    property int endx: 0;
                    property bool ex: false;
                    function createopen(){
                        if(goodvideoTue.visible==true){
                            goodvideoTue.visible=false;
                        }
                        if(openx>endx){
                            goodvideoTue.x=endx;
                            goodvideoTue.width=openx-endx;
                        }else{
                            goodvideoTue.x=openx;
                            goodvideoTue.width=endx-openx;
                        }
                        goodvideoTue.color="blue";
                        goodvideoTue.visible=true;
                    }
                    Rectangle{
                        visible: false;
                        id: goodvideoTue;
                        anchors.top:parent.top;
                        anchors.bottom: parent.bottom;
                    }
                    MouseArea{
                        id:videomouseTue;
                        anchors.fill: parent;
                        enabled: true;
                        onPressAndHold: {
                            areaofmouseTue.ox=true;
                            areaofmouseTue.openx=mouseX;
                        }
                        onReleased: {
                            areaofmouseTue.ex=true;
                            areaofmouseTue.endx=mouseX;
                            if(areaofmouseTue.ox==true){
                                areaofmouseTue.createopen();
                                areaofmouseTue.ox=false;
                            }
                        }

                    }

                }
            }
            Label{
                anchors.top:saveButton.bottom;
                anchors.topMargin: 112;
                anchors.left: templateall.right;
                anchors.leftMargin: 10;
                text:"周三";
                font.pixelSize: 22;
                color: "red"
            }
            Rectangle{
                id:timeQuanWed;
                anchors.top:saveButton.bottom;
                anchors.topMargin: 102;
                anchors.left: templateall.right;
                anchors.leftMargin: 50;
                Image {
                    id: videoimageWed;
                    anchors.left:parent.left;
                    anchors.leftMargin: 20;
                    anchors.top:parent.top;
                    width:364;
                    source: "videogramm.png"
                }
                Rectangle{
                    anchors.top:videoimageWed.bottom;
                    anchors.left: parent.left;
                    anchors.leftMargin: 20;
                    width: 360;
                    height: 20;
                    border.width: 1;
                    border.color: "black";
                    id:areaofmouseWed;
                    //color: "blue";
                    property int openx: 0;
                    property bool ox: false;
                    property int endx: 0;
                    property bool ex: false;
                    function createopen(){
                        if(goodvideoWed.visible==true){
                            goodvideoWed.visible=false;
                        }
                        if(openx>endx){
                            goodvideoWed.x=endx;
                            goodvideoWed.width=openx-endx;
                        }else{
                            goodvideoWed.x=openx;
                            goodvideoWed.width=endx-openx;
                        }
                        goodvideoWed.color="blue";
                        goodvideoWed.visible=true;
                    }
                    Rectangle{
                        visible: false;
                        id: goodvideoWed;
                        anchors.top:parent.top;
                        anchors.bottom: parent.bottom;
                    }
                    MouseArea{
                        id:videomouseWed;
                        anchors.fill: parent;
                        enabled: true;
                        onPressAndHold: {
                            areaofmouseWed.ox=true;
                            areaofmouseWed.openx=mouseX;
                        }
                        onReleased: {
                            areaofmouseWed.ex=true;
                            areaofmouseWed.endx=mouseX;
                            if(areaofmouseWed.ox==true){
                                areaofmouseWed.createopen();
                                areaofmouseWed.ox=false;
                            }
                        }

                    }

                }
            }
            Label{
                anchors.top:saveButton.bottom;
                anchors.topMargin: 152;
                anchors.left: templateall.right;
                anchors.leftMargin: 10;
                text:"周四";
                font.pixelSize: 22;
                color: "red"
            }
            Rectangle{
                id:timeQuanThu;
                anchors.top:saveButton.bottom;
                anchors.topMargin: 142;
                anchors.left: templateall.right;
                anchors.leftMargin: 50;
                Image {
                    id: videoimageThu;
                    anchors.left:parent.left;
                    anchors.leftMargin: 20;
                    anchors.top:parent.top;
                    width:364;
                    source: "videogramm.png"
                }
                Rectangle{
                    anchors.top:videoimageThu.bottom;
                    anchors.left: parent.left;
                    anchors.leftMargin: 20;
                    width: 360;
                    height: 20;
                    border.width: 1;
                    border.color: "black";
                    id:areaofmouseThu;
                    //color: "blue";
                    property int openx: 0;
                    property bool ox: false;
                    property int endx: 0;
                    property bool ex: false;
                    function createopen(){
                        if(goodvideoThu.visible==true){
                            goodvideoThu.visible=false;
                        }
                        if(openx>endx){
                            goodvideoThu.x=endx;
                            goodvideoThu.width=openx-endx;
                        }else{
                            goodvideoThu.x=openx;
                            goodvideoThu.width=endx-openx;
                        }
                        goodvideoThu.color="blue";
                        goodvideoThu.visible=true;
                    }
                    Rectangle{
                        visible: false;
                        id: goodvideoThu;
                        anchors.top:parent.top;
                        anchors.bottom: parent.bottom;
                    }
                    MouseArea{
                        id:videomouseThu;
                        anchors.fill: parent;
                        enabled: true;
                        onPressAndHold: {
                            areaofmouseThu.ox=true;
                            areaofmouseThu.openx=mouseX;
                        }
                        onReleased: {
                            areaofmouseThu.ex=true;
                            areaofmouseThu.endx=mouseX;
                            if(areaofmouseThu.ox==true){
                                areaofmouseThu.createopen();
                                areaofmouseThu.ox=false;
                            }
                        }
                    }
                }
            }
            Label{
                anchors.top:saveButton.bottom;
                anchors.topMargin: 192;
                anchors.left: templateall.right;
                anchors.leftMargin: 10;
                text:"周五";
                font.pixelSize: 22;
                color: "red"
            }
            Rectangle{
                id:timeQuanFri;
                anchors.top:saveButton.bottom;
                anchors.topMargin: 182;
                anchors.left: templateall.right;
                anchors.leftMargin: 50;
                Image {
                    id: videoimageFri;
                    anchors.left:parent.left;
                    anchors.leftMargin: 20;
                    anchors.top:parent.top;
                    width:364;
                    source: "videogramm.png"
                }
                Rectangle{
                    anchors.top:videoimageFri.bottom;
                    anchors.left: parent.left;
                    anchors.leftMargin: 20;
                    width: 360;
                    height: 20;
                    border.width: 1;
                    border.color: "black";
                    id:areaofmouseFri;
                    //color: "blue";
                    property int openx: 0;
                    property bool ox: false;
                    property int endx: 0;
                    property bool ex: false;
                    function createopen(){
                        if(goodvideoFri.visible==true){
                            goodvideoFri.visible=false;
                        }
                        if(openx>endx){
                            goodvideoFri.x=endx;
                            goodvideoFri.width=openx-endx;
                        }else{
                            goodvideoFri.x=openx;
                            goodvideoFri.width=endx-openx;
                        }
                        goodvideoFri.color="blue";
                        goodvideoFri.visible=true;
                    }
                    Rectangle{
                        visible: false;
                        id: goodvideoFri;
                        anchors.top:parent.top;
                        anchors.bottom: parent.bottom;
                    }
                    MouseArea{
                        id:videomouseFri;
                        anchors.fill: parent;
                        enabled: true;
                        onPressAndHold: {
                            areaofmouseFri.ox=true;
                            areaofmouseFri.openx=mouseX;
                        }
                        onReleased: {
                            areaofmouseFri.ex=true;
                            areaofmouseFri.endx=mouseX;
                            if(areaofmouseFri.ox==true){
                                areaofmouseFri.createopen();
                                areaofmouseFri.ox=false;
                            }
                        }
                    }
                }
            }
            Label{
                anchors.top:saveButton.bottom;
                anchors.topMargin: 232;
                anchors.left: templateall.right;
                anchors.leftMargin: 10;
                text:"周六";
                font.pixelSize: 22;
                color: "red"
            }
            Rectangle{
                id:timeQuanSat;
                anchors.top:saveButton.bottom;
                anchors.topMargin: 222;
                anchors.left: templateall.right;
                anchors.leftMargin: 50;
                Image {
                    id: videoimageSat;
                    anchors.left:parent.left;
                    anchors.leftMargin: 20;
                    anchors.top:parent.top;
                    width:364;
                    source: "videogramm.png"
                }
                Rectangle{
                    anchors.top:videoimageSat.bottom;
                    anchors.left: parent.left;
                    anchors.leftMargin: 20;
                    width: 360;
                    height: 20;
                    border.width: 1;
                    border.color: "black";
                    id:areaofmouseSat;
                    //color: "blue";
                    property int openx: 0;
                    property bool ox: false;
                    property int endx: 0;
                    property bool ex: false;
                    function createopen(){
                        if(goodvideoSat.visible==true){
                            goodvideoSat.visible=false;
                        }
                        if(openx>endx){
                            goodvideoSat.x=endx;
                            goodvideoSat.width=openx-endx;
                        }else{
                            goodvideoSat.x=openx;
                            goodvideoSat.width=endx-openx;
                        }
                        goodvideoSat.color="blue";
                        goodvideoSat.visible=true;
                    }
                    Rectangle{
                        visible: false;
                        id: goodvideoSat;
                        anchors.top:parent.top;
                        anchors.bottom: parent.bottom;
                    }
                    MouseArea{
                        id:videomouseSat;
                        anchors.fill: parent;
                        enabled: true;
                        onPressAndHold: {
                            areaofmouseSat.ox=true;
                            areaofmouseSat.openx=mouseX;
                        }
                        onReleased: {
                            areaofmouseSat.ex=true;
                            areaofmouseSat.endx=mouseX;
                            if(areaofmouseSat.ox==true){
                                areaofmouseSat.createopen();
                                areaofmouseSat.ox=false;
                            }
                        }
                    }
                }
            }
            Label{
                anchors.top:saveButton.bottom;
                anchors.topMargin: 272;
                anchors.left: templateall.right;
                anchors.leftMargin: 10;
                text:"周日";
                font.pixelSize: 22;
                color: "red"
            }
            Rectangle{
                id:timeQuanSun;
                anchors.top:saveButton.bottom;
                anchors.topMargin: 262;
                anchors.left: templateall.right;
                anchors.leftMargin: 50;
                Image {
                    id: videoimageSun;
                    anchors.left:parent.left;
                    anchors.leftMargin: 20;
                    anchors.top:parent.top;
                    width:364;
                    source: "videogramm.png"
                }
                Rectangle{
                    anchors.top:videoimageSun.bottom;
                    anchors.left: parent.left;
                    anchors.leftMargin: 20;
                    width: 360;
                    height: 20;
                    border.width: 1;
                    border.color: "black";
                    id:areaofmouseSun;
                    //color: "blue";
                    property int openx: 0;
                    property bool ox: false;
                    property int endx: 0;
                    property bool ex: false;
                    function createopen(){
                        if(goodvideoSun.visible==true){
                            goodvideoSun.visible=false;
                        }
                        if(openx>endx){
                            goodvideoSun.x=endx;
                            goodvideoSun.width=openx-endx;
                        }else{
                            goodvideoSun.x=openx;
                            goodvideoSun.width=endx-openx;
                        }
                        goodvideoSun.color="blue";
                        goodvideoSun.visible=true;
                    }
                    Rectangle{
                        visible: false;
                        id: goodvideoSun;
                        anchors.top:parent.top;
                        anchors.bottom: parent.bottom;
                    }
                    MouseArea{
                        id:videomouseSun;
                        anchors.fill: parent;
                        enabled: true;
                        onPressAndHold: {
                            areaofmouseSun.ox=true;
                            areaofmouseSun.openx=mouseX;
                        }
                        onReleased: {
                            areaofmouseSun.ex=true;
                            areaofmouseSun.endx=mouseX;
                            if(areaofmouseSun.ox==true){
                                areaofmouseSun.createopen();
                                areaofmouseSun.ox=false;
                            }
                        }
                    }
                }
            }
        }

    }
    Rectangle{
        id:deviceConfiguration;
        visible: false;
        anchors.fill: parent;
        ListView{
            id:deviceListofConfig;
            width: 100;
            anchors.top:parent.top;
            anchors.topMargin: 20;
            anchors.left: parent.left;
        }
        Button{
            id:encodingConfiguration;
            text:"编码配置";
            anchors.left: parent.left;
            anchors.leftMargin: 100;
            anchors.top:parent.top;
            anchors.topMargin:20;
            //width:50;
            //height:20;
            style: ButtonStyle{
                background: Rectangle{
                    anchors.fill:parent;
                    color: encodingConfiguration.pressed? "grey":"white"
                }
            }
            onClicked: {
                deviceConfig.visible=true;
                videoConfig.visible=false;
            }
        }
        Button{
            id:videoConfiguration;
            text:"视频配置";
            anchors.left: encodingConfiguration.right;
            anchors.leftMargin: 10;
            anchors.top:parent.top;
            anchors.topMargin:20;
            //width:50;
            //height:20;
            style: ButtonStyle{
                background: Rectangle{
                    anchors.fill:parent;
                    color: videoConfiguration.pressed? "grey":"white"
                }
            }
            onClicked: {
                deviceConfig.visible=false;
                videoConfig.visible=true;
            }
        }
        Rectangle{
            id:deviceConfig;
            visible: true;
            anchors.left: deviceListofConfig.right;
            anchors.top:videoConfiguration.bottom;
            anchors.bottom: parent.bottom;
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 20;
                text:"通道号";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 70;
                anchors.top:parent.top;
                anchors.topMargin: 14;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 50;
                text:"主码流";
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 80;
                text:"码流类型";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 70;
                anchors.top:parent.top;
                anchors.topMargin: 70;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 110;
                text:"码流控制";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 70;
                anchors.top:parent.top;
                anchors.topMargin: 110;
                text:"固定码流";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 150;
                anchors.top:parent.top;
                anchors.topMargin: 110;
                text:"可变码流";
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 140;
                text:"帧率";
            }
            Control20.Slider{
                anchors.left: parent.left;
                anchors.leftMargin: 60;
                anchors.top:parent.top;
                anchors.topMargin: 130;
                //first.value: 20;
                //second.value: 50;
                from:20;
                to:50;
                //orientation: Qt.Horizontal;
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 180;
                text:"分辨率";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 70;
                anchors.top:parent.top;
                anchors.topMargin: 170;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 210;
                text:"图像质量";
            }
            Control20.Slider{
                anchors.left: parent.left;
                anchors.leftMargin: 60;
                anchors.top:parent.top;
                anchors.topMargin: 200;
                //first.value: 20;
                //second.value: 50;
                from:20;
                to:50;
                //orientation: Qt.Horizontal;
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 250;
                text:"码流";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 70;
                anchors.top:parent.top;
                anchors.topMargin: 240;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 290;
                text:"编码模式";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 70;
                anchors.top:parent.top;
                anchors.topMargin: 290;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 330;
                text:"音频使能";
            }
            CheckBox{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 70;
                anchors.top:parent.top;
                anchors.topMargin: 330;
                onClicked: {

                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                //anchors.leftMargin: 22;
                anchors.top:parent.top;
                anchors.topMargin: 370;
                text:"音频编码";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 70;
                anchors.top:parent.top;
                anchors.topMargin: 360;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 50;
                text:"副码流";
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 80;
                text:"码流类型";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 370;
                anchors.top:parent.top;
                anchors.topMargin: 70;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 110;
                text:"码流控制";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 370;
                anchors.top:parent.top;
                anchors.topMargin: 110;
                text:"固定码流";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 450;
                anchors.top:parent.top;
                anchors.topMargin: 110;
                text:"可变码流";
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 140;
                text:"帧率";
            }
            Control20.Slider{
                anchors.left: parent.left;
                anchors.leftMargin: 360;
                anchors.top:parent.top;
                anchors.topMargin: 130;
                //first.value: 20;
                //second.value: 50;
                from:20;
                to:50;
                //orientation: Qt.Horizontal;
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 180;
                text:"分辨率";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 370;
                anchors.top:parent.top;
                anchors.topMargin: 170;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 210;
                text:"图像质量";
            }
            Control20.Slider{
                anchors.left: parent.left;
                anchors.leftMargin: 360;
                anchors.top:parent.top;
                anchors.topMargin: 200;
                //first.value: 20;
                //second.value: 50;
                from:20;
                to:50;
                //orientation: Qt.Horizontal;
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 250;
                text:"码流";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 370;
                anchors.top:parent.top;
                anchors.topMargin: 240;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 290;
                text:"编码模式";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 370;
                anchors.top:parent.top;
                anchors.topMargin: 290;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 330;
                text:"音频使能";
            }
            CheckBox{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 370;
                anchors.top:parent.top;
                anchors.topMargin: 330;
                onClicked: {

                }
            }
            Label{
                visible: true;
                anchors.left: parent.left;
                anchors.leftMargin: 300;
                anchors.top:parent.top;
                anchors.topMargin: 370;
                text:"音频编码";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 370;
                anchors.top:parent.top;
                anchors.topMargin: 360;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
        }
        Rectangle{
            id:videoConfig;
            visible: false;
            anchors.left: deviceListofConfig.right;
            anchors.top:videoConfiguration.bottom;
            anchors.bottom: parent.bottom;
            VideoOutput{
                id:previewWindow;
                anchors.left: parent.left;
                anchors.leftMargin: 10;
                anchors.top:parent.top;
                anchors.topMargin: 10;
                width: 300;
                height: 200;
                source: previewSoures;
            }
            Camera {
                id:previewSoures;
            }
            Label{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin: 10;
                text:"通道号";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 380;
                anchors.top:parent.top;
                anchors.topMargin: 5;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Label{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin:50;
                text:"颜色模式";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 380;
                anchors.top:parent.top;
                anchors.topMargin: 50;
                text:"标准";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 440;
                anchors.top:parent.top;
                anchors.topMargin: 50;
                text:"明亮";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 500;
                anchors.top:parent.top;
                anchors.topMargin: 50;
                text:"柔和";
            }
            Label{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin: 90;
                text:"亮度";
            }
            Control20.Slider{
                anchors.left: parent.left;
                anchors.leftMargin: 380;
                anchors.top:parent.top;
                anchors.topMargin: 70;
                //first.value: 20;
                //second.value: 50;
                from:20;
                to:50;
                //orientation: Qt.Horizontal;
            }
            Label{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin: 130;
                text:"对比度";
            }
            Control20.Slider{
                anchors.left: parent.left;
                anchors.leftMargin: 380;
                anchors.top:parent.top;
                anchors.topMargin: 110;
                //first.value: 20;
                //second.value: 50;
                from:20;
                to:50;
                //orientation: Qt.Horizontal;
            }
            Label{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin: 170;
                text:"色调";
            }
            Control20.Slider{
                anchors.left: parent.left;
                anchors.leftMargin: 380;
                anchors.top:parent.top;
                anchors.topMargin: 150;
                //first.value: 20;
                //second.value: 50;
                from:20;
                to:50;
                //orientation: Qt.Horizontal;
            }
            Label{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin: 210;
                text:"饱和度";
            }
            Control20.Slider{
                anchors.left: parent.left;
                anchors.leftMargin: 380;
                anchors.top:parent.top;
                anchors.topMargin: 190;
                //first.value: 20;
                //second.value: 50;
                from:20;
                to:50;
                //orientation: Qt.Horizontal;
            }
            Label{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin: 250;
                text:"日夜转换";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin: 290;
                text:"彩色";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 370;
                anchors.top:parent.top;
                anchors.topMargin: 290;
                text:"自动";
            }
            RadioButton{
                anchors.left: parent.left;
                anchors.leftMargin: 420;
                anchors.top:parent.top;
                anchors.topMargin: 290;
                text:"黑白";
            }
            Label{
                anchors.left: parent.left;
                anchors.leftMargin: 320;
                anchors.top:parent.top;
                anchors.topMargin: 330;
                text:"背光补偿";
            }
            ComboBox{
                anchors.left: parent.left;
                anchors.leftMargin: 390;
                anchors.top:parent.top;
                anchors.topMargin: 320;
                model:ListModel{
                    ListElement{text:"1"}
                    ListElement{text:"2"}
                }
            }
            Button{
                anchors.left: parent.left;
                //anchors.leftMargin: 10;
                anchors.top:parent.top;
                anchors.topMargin: 320;
                text:"恢复默认";
            }
            Button{
                anchors.left: parent.left;
                anchors.leftMargin: 150;
                anchors.top:parent.top;
                anchors.topMargin: 320;
                text:"辅助聚焦";
            }
            Label{
                anchors.left: parent.left;
                anchors.top:parent.top;
                anchors.topMargin: 380;
                text:"通道名";
            }
            TextField{
                anchors.left: parent.left;
                anchors.leftMargin: 60;
                anchors.top:parent.top;
                anchors.topMargin: 370;
                width: 200;
            }
            Button{
                anchors.left: parent.left;
                anchors.leftMargin: 636;
                anchors.top:parent.top;
                anchors.topMargin: 415;
                text:"应用到...";
            }
        }
    }
    Rectangle{
        id:logManagementInterface;
        visible: false;
        Label{
            anchors.left: parent.left;
            anchors.leftMargin: 50;
            anchors.top:parent.top;
            anchors.topMargin: 100;
            text:"开始时间";
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 50;
            anchors.top:parent.top;
            anchors.topMargin: 150;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 90;
            anchors.top:parent.top;
            anchors.topMargin: 150;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 130;
            anchors.top:parent.top;
            anchors.topMargin: 150;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 170;
            anchors.top:parent.top;
            anchors.topMargin: 150;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 210;
            anchors.top:parent.top;
            anchors.topMargin: 150;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 250;
            anchors.top:parent.top;
            anchors.topMargin: 150;
        }
        Label{
            anchors.left: parent.left;
            anchors.leftMargin: 50;
            anchors.top:parent.top;
            anchors.topMargin: 200;
            text:"结束时间";
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 50;
            anchors.top:parent.top;
            anchors.topMargin: 250;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 90;
            anchors.top:parent.top;
            anchors.topMargin: 250;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 130;
            anchors.top:parent.top;
            anchors.topMargin: 250;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 170;
            anchors.top:parent.top;
            anchors.topMargin: 250;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 210;
            anchors.top:parent.top;
            anchors.topMargin: 250;
        }
        SpinBox{
            anchors.left: parent.left;
            anchors.leftMargin: 250;
            anchors.top:parent.top;
            anchors.topMargin: 250;
        }
        Button{
            anchors.left: parent.left;
            anchors.leftMargin: 100;
            anchors.top:parent.top;
            anchors.topMargin: 300;
            width: 100;
            text:"搜索";
        }
        TableView{
            id:logSheet;
            visible: true;
            anchors.left: parent.left;
            anchors.leftMargin: 300;
            //anchors.right: parent.right;
            anchors.top: parent.top;
            //anchors.topMargin: 10;
            //anchors.bottom:parent.bottom;
            width:500;
            height: 480;
            TableViewColumn{
                role:"time";
                title:"操作时间";
                visible: true;
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role: "logsize";
                title:"日志类型";
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"deviceName";
                title: "设备名称";
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"deviceSize";
                title:"设备类型";
                resizable: true;
                elideMode: Text.ElideRight;
            }
            TableViewColumn{
                role:"descriptor";
                title:"描述信息";
                resizable: true;
                elideMode: Text.ElideRight;
            }
            itemDelegate: Rectangle{
                id: logtext
                anchors.fill: parent;
                anchors.margins: 3;
                border.color: "blue";
                radius:3;
                color: styleData.selected ? "transparent" : "#1A4275";
                Text{
                    id: logtextID;
                    text:styleData.value ;
                    font.family: "微软雅黑";
                    font.pixelSize: 12
                    anchors.fill: parent;
                    color: "white";
                    elide: Text.ElideRight;
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            headerDelegate :Rectangle{//设置表头的样式
                implicitWidth: 10
                implicitHeight: 24
                gradient: Gradient {
                          GradientStop { position: 0.0; color: "white" }
                          GradientStop { position: 0.5; color: "black"}
                          GradientStop { position:1.0;  color: "white"}
                      }
                border.width: 1
                border.color: "gray"
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 4
                    anchors.right: parent.right
                    anchors.rightMargin: 4
                    text: styleData.value
                    color: "red"
                    font.bold: true
                }
            }
        }
    }
}

