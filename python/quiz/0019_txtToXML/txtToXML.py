from lxml import etree

root=etree.Element('root')
numbers=etree.SubElement(root,'numbers')

with open('numbers.txt','r') as f:
	numbers.text="""
<!-- 
	数字信息
-->
"""
	numbers.text+=f.read()

tree=etree.ElementTree(root)
tree.write('numbersInfo.xml',pretty_print=True, xml_declaration=True, encoding='utf-8')