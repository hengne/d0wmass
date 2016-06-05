import sys
import os
import string

basefilename=sys.argv[1]
splitpoint=basefilename.find('Binned')
objqual='dummy'
inputfile=open(sys.argv[1],'r')
mynewfile=open('temp.file','a')

triggerstring=sys.argv[2]
for line in inputfile:
#    if line.find('Comments') != -1:
    if line.find(triggerstring) != -1:
#        print line
        mynewfile.write('\n')
        mynewfile.close()
#        print 'I am renaming to '+ basefilename[:splitpoint]+ objqual + '_Binned.spac'
        newfilename=basefilename[:splitpoint]+objqual+'_Binned.spc'
        appendfile=open(newfilename,'a')
        mynewfile=open('temp.file','r')
        for appline in mynewfile:
            appendfile.write(appline)
        mynewfile.close()
        appendfile.close()
        mynewfile=open('temp.file','w')
        mynewfile.write(line)
    elif line.find('ObjRelativeTo') != -1:
        mynewfile.write(line)
        objline=line.strip()
        objqual=objline[objline.find(': ')+2:]
        ### assume that this is the last section of the file.  If it isn't, it will get replaced next time.
        lastfilename=basefilename[:splitpoint]+objqual+'_Binned.spc'
        print objqual
    else:
        mynewfile.write(line)

inputfile.close()
#so now we have gone all the way through the input file.  now we have to add the last part "by hand"
mynewfile.close()
print 'Final filename is  '+ lastfilename
appendfile=open(lastfilename,'a')
mynewfile=open('temp.file','r')
for appline in mynewfile:
    appendfile.write(appline)
mynewfile.close()
appendfile.close()

