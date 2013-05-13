import sys
import time
import random

keyframes = 29
tempo = 2
starttime = 430

# Open output files
timeline1 = open('timeline2_blanco.xml', 'w')


timeline1.write('<keyframes>\n')


timeline1_oldtime = starttime


for current_keyframe in range(1,keyframes):
	timeline1.write('\t<key>\n')
	timeline1.write('\t\t<flag>fwd2</flag>\n')
	timeline1.write('\t\t<time>'+time.strftime('%H:%M:%S:000', time.gmtime(timeline1_oldtime))+'</time>\n')
	timeline1.write('\t\t<value>'+str(current_keyframe)+'.000000000</value>\n')
	timeline1.write('\t</key>\n')
	
	if (current_keyframe > 7) and (current_keyframe < 14):
		tempo = 3
	if current_keyframe > 14:
		tempo = random.randrange(1,4)
	
	timeline1_oldtime = timeline1_oldtime+tempo


timeline1.write('</keyframes>\n')

	
timeline1.close()
