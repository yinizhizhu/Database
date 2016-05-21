# -*- coding: utf-8 -*-   
import sys  
from PyQt4.QtGui import *  
from PyQt4.QtCore import *  
import MySQLdb

conn=MySQLdb.connect(
    host="localhost",
    port=3306,
    user="root",
    passwd="",
    db="live",
    charset='utf8'
    )
cur=conn.cursor()

QTextCodec.setCodecForTr(QTextCodec.codecForName("utf8"))  
class StockDialog(QDialog):
    def __init__(self,parent=None):
        super(StockDialog,self).__init__(parent)  
            
        self.setWindowTitle('Flyos')
        self.setWindowIcon(QIcon('pic/stupid.gif'))
  
        mainSplitter=QSplitter(Qt.Horizontal)  
        mainSplitter.setOpaqueResize(True)
   
        listWidget=QListWidget(mainSplitter)  
        listWidget.insertItem(0,self.tr("ER-Diagram"))  
        listWidget.insertItem(1,self.tr("View"))  
        listWidget.insertItem(2,self.tr("Insert"))  
        listWidget.insertItem(3,self.tr("Delete"))  
        listWidget.insertItem(4,self.tr("Query"))  
  
        frame=QFrame(mainSplitter)
        stack=QStackedWidget()
        stack.setFrameStyle(QFrame.Panel|QFrame.Raised)

        show_ER=showER()
        view = View()
        insert = Insert()
        delete = Delete()
        query = Query()
        stack.addWidget(show_ER)
        stack.addWidget(view)
        stack.addWidget(insert)
        stack.addWidget(delete)
        stack.addWidget(query)

        closePushButton=QPushButton(self.tr("Exit"))  

        buttonLayout=QHBoxLayout()  
        buttonLayout.addStretch(1)  
        buttonLayout.addWidget(closePushButton)  

        mainLayout=QVBoxLayout(frame)  
        mainLayout.setMargin(10)  
        mainLayout.setSpacing(6)  
        mainLayout.addWidget(stack)  
        mainLayout.addLayout(buttonLayout)  

        self.connect(listWidget,SIGNAL("currentRowChanged(int)"),stack,SLOT("setCurrentIndex(int)"))
        self.connect(closePushButton,SIGNAL("clicked()"),self,SLOT("close()"))
  
        layout=QHBoxLayout(self)
        layout.addWidget(mainSplitter)
        self.setLayout(layout)  

class showER(QWidget):
    def __init__(self, parent=None):
        super(showER,self).__init__(parent)  
        pixmap = QPixmap("pic/ER.png")
        self.label = QLabel(self)
        self.label.setPixmap(pixmap)
        layout=QGridLayout(self)
        layout.addWidget(self.label,0,0)
    def excute(self):
        print "Hou hava pressed the button to excute."
        
class View(QWidget):  
    def __init__(self,parent=None):  
        super(View,self).__init__(parent)  
                 
        label1=QLabel(self.tr("视图名："))  
        label2=QLabel(self.tr("要查询属性：")) 
        label3=QLabel(self.tr("限制："))   
        button=QPushButton(self.tr("Excute"))  
        label4=QLabel(self.tr("执行结果："))  
  
        self.viewEdit=QLineEdit()  
        self.attrEdit=QLineEdit()  
        self.limitEdit=QLineEdit()  
        self.resultEdit=QTextEdit()  
  
        layout=QGridLayout(self)  
        layout.addWidget(label1,0,0)  
        layout.addWidget(self.viewEdit,0,1)  
        layout.addWidget(label2,1,0)  
        layout.addWidget(self.attrEdit,1,1)  
        layout.addWidget(label3,2,0)  
        layout.addWidget(self.limitEdit,2,1) 
        layout.addWidget(button,3,0)  
        layout.addWidget(label4,4,0)  
        layout.addWidget(self.resultEdit,4,1)  
        self.connect(button,SIGNAL("clicked()"), self.excute)
    def excute(self):
        view = self.viewEdit.text()
        attr = self.attrEdit.text()
        query = "select "+attr+" from "+view
        limit = self.limitEdit.text()
        if len(str(limit)) > 0:
            query +=" where "+limit
        print query
#        query = "select * from people"
        a2=cur.execute(str(query).decode("gbk").encode("utf8"))
        info = cur.fetchmany(a2)
        result = ""
        for i in info:
            for j in i:
                result += " "
                result += j
            result += '\n'
        if len(result) > 0:
            self.resultEdit.setText(result)
        else:
            self.resultEdit.setText("Cannot excute\""+str(query)+"\"")

class Insert(QWidget):  
    def __init__(self,parent=None):  
        super(Insert,self).__init__(parent)  
        
        label1=QLabel(self.tr("表名："))  
        label2=QLabel(self.tr("值："))  
        button=QPushButton(self.tr("Excute"))  
        label3=QLabel(self.tr("执行结果："))  
  
        self.tableEdit=QLineEdit()  
        self.attrEdit=QLineEdit()  
        self.resultEdit=QTextEdit()  
  
        layout=QGridLayout(self)  
        layout.addWidget(label1,0,0)  
        layout.addWidget(self.tableEdit,0,1)  
        layout.addWidget(label2,1,0)  
        layout.addWidget(self.attrEdit,1,1)  
        layout.addWidget(button, 2, 0)
        layout.addWidget(label3,3,0)  
        layout.addWidget(self.resultEdit,3,1)  
        self.connect(button,SIGNAL("clicked()"), self.excute)
    def excute(self):
        table = self.tableEdit.text()
        value = self.attrEdit.text()
        query = "insert into "+str(table)+" values("+str(value)+")"
        print query
#        query = "select * from people"
        a2=cur.execute(query.decode("gbk").encode("utf8"))
        info = cur.fetchmany(a2)
        result = ""
        for i in info:
            for j in i:
                result += " "
                result += j
            result += '\n'
        self.resultEdit.setText("Successed to insert the values into "+table)

class Delete(QWidget):  
    def __init__(self,parent=None):  
        super(Delete,self).__init__(parent)  

        label1=QLabel(self.tr("表名："))  
        label2=QLabel(self.tr("选择删除属性值："))  
        label3=QLabel(self.tr("限制："))   
        button=QPushButton(self.tr("Excute"))  
        label4=QLabel(self.tr("执行结果："))  
  
        self.tableEdit=QLineEdit()  
        self.attrEdit=QLineEdit()  
        self.limitEdit=QLineEdit()  
        self.resultEdit=QTextEdit()  
  
        layout=QGridLayout(self)  
        layout.addWidget(label1,0,0)  
        layout.addWidget(self.tableEdit,0,1)  
        layout.addWidget(label2,1,0)  
        layout.addWidget(self.attrEdit,1,1)  
        layout.addWidget(label3,2,0)  
        layout.addWidget(self.limitEdit,2,1) 
        layout.addWidget(button, 3, 0)
        layout.addWidget(label4,4,0)  
        layout.addWidget(self.resultEdit,4,1)  
        self.connect(button,SIGNAL("clicked()"), self.excute)
    def excute(self):
        table = self.tableEdit.text()
        attr = self.attrEdit.text()
        query = "delete "+attr+" from "+table
        limit = self.limitEdit.text()
        if len(limit) > 0:
            query +=" where "+limit
        print query
#        query = "select * from people"
        a2=cur.execute(str(query).decode("gbk").encode("utf8"))
        info = cur.fetchmany(a2)
        result = ""
        for i in info:
            for j in i:
                result += " "
                result += j
            result += '\n'
        self.resultEdit.setText("Successed to delete the values on "+table)
        
class Query(QWidget):
    def __init__(self, parent=None):
        super(Query,self).__init__(parent)  

        label1=QLabel(self.tr("表名："))  
        label2=QLabel(self.tr("要查询属性值："))  
        label3=QLabel(self.tr("限制："))   
        label4=QLabel(self.tr("分组："))   
        button=QPushButton(self.tr("Excute"))  
        label5=QLabel(self.tr("执行结果："))  
  
        self.tableEdit=QLineEdit()  
        self.attrEdit=QLineEdit()  
        self.limitEdit=QLineEdit()  
        self.groupEdit=QLineEdit()  
        self.resultEdit=QTextEdit()  
  
        layout=QGridLayout(self)  
        layout.addWidget(label1,0,0)  
        layout.addWidget(self.tableEdit,0,1)  
        layout.addWidget(label2,1,0)  
        layout.addWidget(self.attrEdit,1,1)  
        layout.addWidget(label3,2,0)  
        layout.addWidget(self.limitEdit,2,1) 
        layout.addWidget(label4, 3, 0)
        layout.addWidget(self.groupEdit, 3, 1)
        layout.addWidget(button, 4, 0)
        layout.addWidget(label5,5,0)  
        layout.addWidget(self.resultEdit,5,1) 
        self.connect(button,SIGNAL("clicked()"), self.excute)
    def excute(self):
        table = self.tableEdit.text()
        attr = self.attrEdit.text()
        query = "select "+attr+" from "+table
        limit = self.limitEdit.text()
        if len(limit) > 0:
            query +=" where "+limit
        group = self.groupEdit.text()
        if len(group) > 0:
            query += " group by "+group
        print query
#        query = "select * from people"
        a2=cur.execute(str(query).decode("gbk").encode("utf8"))
        info = cur.fetchmany(a2)
        result = ""
        for i in info:
            for j in i:
                result += " "
                result += j
            result += '\n'
        if len(result) > 0:
            self.resultEdit.setText(result)
        else:
            self.resultEdit.setText("Cannot excute\""+str(query)+"\""+". Or no values return.")

app=QApplication(sys.argv)
main=StockDialog()
main.show()
app.exec_()
conn.commit()
cur.close()
conn.close()