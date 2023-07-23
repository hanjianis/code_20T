QT       += core gui network sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    AtmoTask.cpp\
    AutoTestDlg.cpp\
    AutoTestDlg12A.cpp \
    AutoTestWidget.cpp\
    CPUTask.cpp\
    DeviceMgr/CK_Manager.cpp \
    DeviceMgr/CK_Manager12A.cpp \
    DeviceMgr/CK_Manager20T.cpp \
    DeviceMgr/DHXHMNQ_Manager.cpp \
    DeviceMgr/Dan2_Manager.cpp \
    DeviceMgr/Dan_Manager.cpp \
    DeviceMgr/DeviceBase.cpp \
    DeviceMgr/HT_Manager.cpp \
    DeviceMgr/HecDataManager.cpp \
    DeviceMgr/KJGXSMNQ_Manager.cpp \
    DeviceMgr/LDGDB_Manager.cpp \
    DeviceMgr/PLCManager.cpp \
    DeviceMgr/PLCManager12A.cpp \
    DeviceMgr/RYJCY_Manager.cpp \
    DeviceMgr/SPQ_Manager.cpp \
    DeviceMgr/SPQ_Manager12A.cpp \
    DeviceMgr/SXZPDY_Manager.cpp \
    DeviceMgr/ZHDY_Manager.cpp \
    DeviceMgr/ZJ_Manager.cpp \
    DiagnosticPause.cpp \
    ExcelOperate.cpp \
    ISysCheckItem12A.cpp \
    Integraedconfirmdlg.cpp \
    IntegratedLowerDisplay.cpp \
    integratedtestdialog.cpp \
    integratedtesting.cpp \
    snap7.cpp\
    DeviceOnlineManage.cpp\
    DPUTask.cpp\
    ExcelOperate.cpp\
    FeiKongTask.cpp\
    GlobalManager.cpp\
    HistoryDlg.cpp\    
    InputTemperatureDlg.cpp\
    InsConfigDlg.cpp\
    INSTestOBJ.cpp\
    ISysCheckItem.cpp\
    ITask.cpp\
    LogMgr.cpp \
    LoginDlg.cpp\
    LogMgr.cpp \
    MakeSureDlg.cpp \
    MessageBoxDlg.cpp \
    MultTestOBJ.cpp \
    MultiControlSys.cpp \
    MyMessageBox.cpp \
    MyToolTipDlg.cpp \
    PowerTask.cpp \
    SelectMissleDlg.cpp \
    TCPClient.cpp \
    Task10.cpp \
    Task13.cpp \
    Task5.cpp \    
    TestItemsDlg.cpp \
    UDPServer.cpp \
    XLManager.cpp


HEADERS += AtmoTask.h\
    DeviceMgr/CK_Manager20T.h \
    DeviceMgr/PLCManager12A.h\
           ../inc/UDPCmd.h \
           AutoTestDlg.h\
           AutoTestDlg12A.h \
           AutoTestWidget.h\
           CPUTask.h\
           DeviceMgr/CK_Manager.h \
           DeviceMgr/CK_Manager12A.h \
           DeviceMgr/DHXHMNQ_Manager.h \
           DeviceMgr/Dan2_Manager.h \
           DeviceMgr/Dan_Manager.h \
           DeviceMgr/DeviceBase.h \
           DeviceMgr/HT_Manager.h \
           DeviceMgr/HecDataManager.h \
           DeviceMgr/KJGXSMNQ_Manager.h \
           DeviceMgr/LDGDB_Manager.h \
           DeviceMgr/PLCManager.h \
           DeviceMgr/RYJCY_Manager.h \
           DeviceMgr/SPQ_Manager.h \
           DeviceMgr/SPQ_Manager12A.h \
           DeviceMgr/SXZPDY_Manager.h \
           DeviceMgr/ZHDY_Manager.h \
           DeviceMgr/ZJ_Manager.h \
           DeviceOnlineManage.h \
    DiagnosticPause.h \
           ISysCheckItem12A.h \
           Integraedconfirmdlg.h \
           iIntegratedLowerDisplay.h \
           integratedtesting.h \
           integratedtestdialog.h \
           libxl/IBookT.h \
           libxl/IFontT.h \
           libxl/IFormatT.h \
           libxl/ISheetT.h \
           libxl/enum.h \
           libxl/libxl.h \
           libxl/setup.h \
           snap7.h\
           DPUTask.h\
           ExcelOperate.h\
           FeiKongTask.h\
           GlobalManager.h\
           HistoryDlg.h\
           InputTemperatureDlg.h\
           InsConfigDlg.h\
           INSTestOBJ.h\
           ISysCheckItem.h\
           ITask.h\
           LoginDlg.h\
           LogMgr.h \
           MakeSureDlg.h \
           MessageBoxDlg.h \
           MultTestOBJ.h \
           MultiControlSys.h \
           MyMessageBox.h \
           MyToolTipDlg.h \
           Packet.h \
           PowerTask.h \
           SelectMissleDlg.h \
           TCPClient.h \
           Task10.h \
           Task13.h \
           Task5.h \
           TestItemsDlg.h \
           UDPCmd.h \
           UDPServer.h \
           XLManager.h



FORMS += AutoTestDlg.ui\
         AutoTestDlg12A.ui \
         AutoTestWidget.ui\
         DiagnosticPause.ui \
         HistoryDlg.ui\
         InputTemperatureDlg.ui\
         InsConfigDlg.ui\
         Integraedconfirmdlg.ui \
         IntegratedLowerDisplay.ui \
         integratedtestdialog.ui \
         LoginDlg.ui \
         MakeSureDlg.ui \
         MessageBoxDlg.ui \
         MultiControlSys.ui \
         MyMessageBox.ui \
         MyToolTipDlg.ui \
         SelectMissleDlg.ui \
         TestItemsDlg.ui
INCLUDEPATH += ./DeviceMgr
INCLUDEPATH += ../inc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/snap7/ -lsnap7

INCLUDEPATH += $$PWD/snap7
DEPENDPATH += /snap7






INCLUDEPATH += $$PWD/libxl
#DEPENDPATH += $$PWD/libxl

RESOURCES += \
    MultiControlSys.qrc

