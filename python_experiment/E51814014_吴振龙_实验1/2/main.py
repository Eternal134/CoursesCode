import sys
import re
from PyQt5 import Qt, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow, QHeaderView, QTableWidgetItem, \
    QMessageBox, QWidget

from Ui_2 import Ui_MainWindow
from Ui_input_info import Ui_Form           # 输入窗口
from manager import Manager

class Interface(QMainWindow, Ui_MainWindow):

    def __init__(self, parent = None):
        super().__init__(parent)
        self.setupUi(MainWindow)
        self.selectedRow = -1                           # 保存用户点击的行号，为-1时表示没有点击表格
        self.window_input = QWidget()                   # 输入窗口
        self.ui_input = Ui_Form()                       # 输入ui对象
        self.ui_input.setupUi(self.window_input)        # 初始化输入ui对象
        # 设置输入窗口的水平表头填充
        self.ui_input.tw_input.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)     
        # 设置输入窗口的垂直表头填充
        self.ui_input.tw_input.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)                            
        # 点击输入窗口的确认按钮，向manager对象添加一个item
        self.ui_input.btn_confirm.clicked.connect(self.add_item)  
        self.manager = Manager()                        # 创建信息管理对象    
        # 点击add按钮，显示输入窗口
        self.btn_add.clicked.connect(self.display_input_window)
        # 水平表头居中
        self.tw_display.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        # 垂直表头居中
        self.tw_display.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        # 表格被点击时，获取被点击处的行和列
        self.tw_display.itemClicked.connect(self.slot_get_widget_selected_row)
        self.display_items()
        # 点击删除按钮，根据选中表格中的行删除该条记录
        self.btn_delete.clicked.connect(self.delete_item)
        # 当搜索框输入字符时，触发搜索槽函数
        self.line_search.textChanged.connect(self.slot_search)

    def slot_search(self, search_string):
        ''' 搜索功能 '''
        self.tw_display.setCurrentItem(None)
        if search_string == "":
            return
        # 将匹配到的item设为选中状态
        [item.setSelected(True) for item in self.tw_display.findItems(search_string, QtCore.Qt.MatchContains)]

    def slot_get_widget_selected_row(self, widgetItem):
        ''' 获取表格中被选中的单元格的行和列 '''
        self.selectedRow = widgetItem.row()

    def display_input_window(self):
        ''' 显示输入窗口 '''
        self.window_input.show()    

    def add_item(self):
        ''' 添加一条项目 '''
        item = []
        for col in range(self.ui_input.tw_input.columnCount()):
            try:
                item.append(self.ui_input.tw_input.item(0, col).text())
            except AttributeError:
                # 发生此错误说明输入的第col列没有值，则将该分量置为空
                item.append("")
        if item == ["","","","","","","",""]:
            # 如果输入的信息全为空
            QMessageBox.information(None, "提示", "输入信息为空")
            return ""
        self.manager.add_item(item)
        self.ui_input.tw_input.clearContents()          # 将输入窗口清空
        self.display_items()
        QMessageBox.information(None, "提示", "添加信息成功")

    def display_items(self):
        ''' 将已有项目展示在表格中 '''
        row = self.tw_display.rowCount()
        while(row >= 0):
            # 清除所有行
            self.tw_display.removeRow(row)
            row -= 1
        for i in range(len(self.manager.infos_list)):
            # 将信息逐个显示在表格中
            self.tw_display.insertRow(i)            # 先插入一行
            for j in range(len(self.manager.infos_list[i])):
                self.tw_display.setItem(i, j, QTableWidgetItem(self.manager.infos_list[i][j]))
    
    def delete_item(self):
        ''' 根据display表格中选中的行，删除一条记录 '''
        if self.selectedRow == -1:
            QMessageBox.information(MainWindow, "提示", "请在表格中选择你要删除的记录")
            return
        self.manager.del_item(self.selectedRow)
        self.display_items()
        QMessageBox.information(MainWindow, "提示", "记录已删除")

if __name__ == "__main__":

    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    ui = Interface(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())