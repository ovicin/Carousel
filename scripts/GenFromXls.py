import xlrd
import re
import sys
import time

workbook_name = "SequenceGenerator.xls"

StartTimeRow = 1
StartTimeColumn = 2

TableStartRow = 4

SlideNoColumn = 1
TempoColumn = 2
BangColumn = 3


#open the workbook
wb = xlrd.open_workbook(workbook_name)

#open the application part_no sheet
try:
        sh = wb.sheet_by_name("Sheet1")
except XLRDError:
        raise XLRDError
		
StartTime = str(sh.cell(StartTimeRow-1,StartTimeColumn-1).value)

# Open output files
timeline1 = open('timeline_xls.xml', 'w')


timeline1.write('<keyframes>\n')


timeline1_oldtime = float(StartTime)

for rowx in xrange(TableStartRow-1, sh.nrows):
	tempo = sh.cell(rowx,TempoColumn-1).value

	timeline1.write('\t<key>\n')
	timeline1.write('\t\t<flag>'+sh.cell(rowx,BangColumn-1).value+'</flag>\n')
	timeline1.write('\t\t<time>'+time.strftime('%H:%M:%S:000', time.gmtime(timeline1_oldtime+tempo))+'</time>\n')
	timeline1.write('\t\t<value>'+str(sh.cell(rowx,SlideNoColumn-1).value)+'.000000000</value>\n')
	timeline1.write('\t</key>\n')
	timeline1_oldtime=timeline1_oldtime+tempo



timeline1.write('</keyframes>\n')

	
timeline1.close()

