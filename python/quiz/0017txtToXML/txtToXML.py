from lxml import etree

root=etree.Element('root')
student=etree.SubElement(root,'student')

with open('students.txt','r') as f:
	student.text=r"""
<!-- 
	学生信息表
	"id" : [名字, 数学, 语文, 英文]
-->
"""
	student.text+=f.read()

tree=etree.ElementTree(root)
tree.write('studenInfo.xml',pretty_print=True, xml_declaration=True, encoding='utf-8')