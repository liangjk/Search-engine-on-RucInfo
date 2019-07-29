#!D:\Python35\python
#coding:utf-8

import time
import os
import codecs
import cgi, cgitb 

form = cgi.FieldStorage() 

my_query=form.getvalue('query')

File=codecs.open("engine\input.in","w","utf-8")
File.write(my_query)
File.close()
# os.system("copy engine\input.in input.in");
time.sleep(0.2)
os.system("del engine\input.in");
print("Location:../result.html\n\n")