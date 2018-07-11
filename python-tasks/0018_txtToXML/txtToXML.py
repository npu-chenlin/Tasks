from lxml import etree

root=etree.Element('root')
city=etree.SubElement(root,'cities')

with open('city.txt','r') as f:
	city.text="""
<!-- 
	城市信息
-->
"""
	city.text+=f.read()

tree=etree.ElementTree(root)
tree.write('cityInfo.xml',pretty_print=True, xml_declaration=True, encoding='utf-8')