# coding=utf-8
#This prog is built for testting GPS & record GPS data while taking pics.
#Before using this , u should run VideoGPSRecorder.py --act testSerial --port <ur path by default /dev/ttyUSB0> --baud <ur baudrate by default 115200> to test if GPS is workable.Wait untill it stop searching...
#


import time,os
import serial
import cv2
import requests,json
import argparse
import threading
from queue import Queue


def getTimestampUTC(l):
		t_ = time.gmtime(time.time())	
		t = (t_.tm_year,t_.tm_mon,t_.tm_mday,int(l[1][:2]),int(l[1][2:4]),int(l[1][4:6]),t_.tm_wday,t_.tm_yday,t_.tm_isdst)
		return time.mktime(t)+float(l[1][6:])

def parse_GPGGA(l):
	if(l[2]):
		timestamp = getTimestampUTC(l)
		lon = float(l[4][0:3])+float(l[4][3:])/60
		lat = float(l[2][0:2])+float(l[2][2:])/60
		#url='https://restapi.amap.com/v3/geocode/regeo?location='+lon+','+lat+'&key=a317cca0f0706fadc03bc0761eaa9db3'
		#cont=requests.get(url)
		#cont=json.loads(cont.content)
		#addr=cont["regeocode"]["formatted_address"].decode('utf8')
		#info["addr"]=addr
		sat_num=l[7]
		HDOP=l[8]
		info=[timestamp,lon,lat,sat_num,HDOP]	
		return info 
	else:
		return 'searching...'

def read_GPS(gps):
	l=gps.readline().split(',')
	while(not (l[0]=='$GPGGA' or l[0]=='$GNGGA')):
		l=gps.readline().split(',')
	r=parse_GPGGA(l)
	if(type(r) == list):
		a=[str(i)+' ' for i in r]
		a[-1]+="\n"
		return a
	else:
		return r

def dataToTxt(cfg,q):
	path='GPS_data.txt'
	count=0
	flag=0
	with open(path,'a') as f:
		while count<100:
			r=read_GPS(gps)
			print(r)
			if(type(r) == list):
				if(not flag):
					flag=1
					q.put(1)
				f.writelines(r)
			count+=1
	
	q.put(0)

	return 0

def captureVideo(videoCapture,q):
	if(not os.path.exists('./pics')):
		os.mkdir('./pics')
	videoCapture = cv2.VideoCapture(cfg.videoDevice)
	sucess,frame=videoCapture.read()
	flag=-1
	while(sucess):
		while not q.empty():
				flag=q.get()
		if (flag==0):
			break
		if (flag==1):
			sucess,frame=videoCapture.read()
			img=cv2.resize(frame,(1024,768))
			path='./pics/'+str(time.time()-8*3600)+'.jpg'
			cv2.imwrite(path,img)

	videoCapture.release()
	return 0

def testSerial(cfg):
	uart = serial.Serial(cfg.port, cfg.baud)
	while(1):
		l = read_GPS(uart)
		print(l)


def parseArguments():
	parser = argparse.ArgumentParser(description='Record video & GPS information')

	parser.add_argument('--act', default='record', help='Action type (record, testSerial')

	parser.add_argument('--port', default='/dev/ttyUSB0', help='GPS port (eg: /dev/ttyUSB0)')
	parser.add_argument('--baud', default=115200, help='Serial port baud rate')

	parser.add_argument('--videoDevice', default=0, help='Video device number')

	df = time.strftime('data_%Y%m%d-%H%M%s')
	parser.add_argument('--dataPrefix', default=df, help='Stored data prefix')

	args = parser.parse_args()
	return args

if __name__=='__main__':
	
	cfg = parseArguments()

	if( cfg.act == 'testSerial' ):
		testSerial(cfg)
	if( cfg.act == 'record' ):
		gps = serial.Serial(cfg.port,cfg.baud)
		q=Queue()
		t1 = threading.Thread(target = captureVideo, args = (cfg,q))
		t2 = threading.Thread(target = dataToTxt, args = (cfg,q))

		t1.deamon = True
		
		t1.start()
		t2.start()

		t2.join()
