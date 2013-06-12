import sys
import time

keyframes = 120
tempo = 3
starttime = 2

# Open output files
timeline1 = open('timeline1_colador.xml', 'w')


timeline1.write('<keyframes>\n')


timeline1_oldtime = starttime

timeline1.write('\t<key>\n')
timeline1.write('\t\t<flag>Projector2Off</flag>\n')
timeline1.write('\t\t<time>00:00:02:000</time>\n')
timeline1.write('\t\t<value>1.000000000</value>\n')
timeline1.write('\t</key>\n')

timeline1.write('\t<key>\n')
timeline1.write('\t\t<flag>AudioColadorOn</flag>\n')
timeline1.write('\t\t<time>00:00:20:000</time>\n')
timeline1.write('\t\t<value>1.000000000</value>\n')
timeline1.write('\t</key>\n')

for current_keyframe in range(1,keyframes):
	timeline1.write('\t<key>\n')
	if current_keyframe < 55:
		timeline1.write('\t\t<flag>fwd1</flag>\n')
	else:
		timeline1.write('\t\t<flag>bck1</flag>\n')
	timeline1.write('\t\t<time>'+time.strftime('%H:%M:%S:000', time.gmtime(timeline1_oldtime))+'</time>\n')
	timeline1.write('\t\t<value>'+str(current_keyframe)+'.000000000</value>\n')
	timeline1.write('\t</key>\n')
	
	if current_keyframe>26:
		tempo = 2
	if current_keyframe>55:
		tempo = 1	
	if current_keyframe == 118:
		tempo = 2
	if current_keyframe == 119:
		tempo = 3		
	timeline1_oldtime = timeline1_oldtime+tempo

timeline1.write('\t<key>\n')
timeline1.write('\t\t<flag>AudioColadorOff</flag>\n')
timeline1.write('\t\t<time>00:02:61:000</time>\n')
timeline1.write('\t\t<value>1.000000000</value>\n')
timeline1.write('\t</key>\n')

timeline1.write('</keyframes>\n')

	
timeline1.close()
