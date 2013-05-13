import sys
import time

keyframes = 37
tempo = 2
starttime = 230

# Open output files
timeline1 = open('timeline1_contratiempo.xml', 'w')
timeline2 = open('timeline2_contratiempo.xml', 'w')

timeline1.write('<keyframes>\n')
timeline2.write('<keyframes>\n')

timeline1_oldtime = starttime
timeline2_oldtime = starttime+1

for current_keyframe in range(1,keyframes):
	timeline1.write('\t<key>\n')
	timeline1.write('\t\t<flag>fwd1</flag>\n')
	timeline1.write('\t\t<time>'+time.strftime('%H:%M:%S:000', time.gmtime(timeline1_oldtime))+'</time>\n')
	timeline1.write('\t\t<value>'+str(current_keyframe)+'.000000000</value>\n')
	timeline1.write('\t</key>\n')
	
	timeline2.write('\t<key>\n')
	timeline2.write('\t\t<flag>fwd2</flag>\n')
	timeline2.write('\t\t<time>'+time.strftime('%H:%M:%S:000', time.gmtime(timeline2_oldtime))+'</time>\n')
	timeline2.write('\t\t<value>'+str(current_keyframe)+'.00000000</value>\n')
	timeline2.write('\t</key>\n')
	
	timeline1_oldtime = timeline1_oldtime+tempo
	timeline2_oldtime = timeline2_oldtime+tempo

timeline1.write('</keyframes>\n')
timeline2.write('</keyframes>\n')
	
timeline1.close()
timeline2.close()