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

class GPS:
	def __init__(self,cfg):
		self.port=cfg.port
		self.baud=cfg.baud
		self.ser=serial.Serial(self.port,self.baud)

	def _parse_GPGGA(self,l):
		if(l[2]):
			timestamp = self._getTimestampUTC(l)
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
	def _getTimestampUTC(self,l):
		t_ = time.gmtime(time.time())	
		t = (t_.tm_year,t_.tm_mon,t_.tm_mday,int(l[1][:2]),int(l[1][2:4]),int(l[1][4:6]),t_.tm_wday,t_.tm_yday,t_.tm_isdst)
		return time.mktime(t)+float(l[1][6:])

	def _read_GPS(self):
		l=self.ser.readline().split(',')
		while(not (l[0]=='$GPGGA' or l[0]=='$GNGGA')):
			l=self.ser.readline().split(',')
		r=self._parse_GPGGA(l)
		if(type(r) == list):
			a=[str(i)+' ' for i in r]
			a[-1]+="\n"
			return a
		else:
			return r

	def testSerial(self,timeout=20):
		t=time.time()
		while(1):
			l = self._read_GPS()
			if(type(l) == list):
				print('Found the signal successfully!!')
				return 1
			print('\r'+l+str((time.time()-t)*5)+'%\t')
			if(time.time()-t>20):
				print("Can't find satellites,try somewhere else")
				return 0

	def dataToTxt(self,q):
		if(self.testSerial()):
			path='GPS_data.txt'
			count=0
			flag=0
			with open(path,'a') as f:
				while count<100:
					r=self._read_GPS()
					print(r)
					if(type(r) == list):
						if(not flag):
							flag=1
							q.put(1)
						f.writelines(r)
					count+=1
		
		q.put(0)	
		return 0	

class captureVideo:
	def __init__(self,videoDevice=0):
		self.mkDir()
		self.videoCapture = cv2.VideoCapture(videoDevice)
		self.flag=-1

	def mkDir(self):
		if(not os.path.exists('./pics')):
			os.mkDir('./pics')

	def saveImg(self,q):
		self.sucess,frame=self.videoCapture.read()
		while(self.sucess):
			while not q.empty():
					self.flag=q.get()
			if (self.flag==0):
				break
			if (self.flag==1):
				self.sucess,frame=self.videoCapture.read()
				img=cv2.resize(frame,(1024,768))
				path='./pics/'+str(time.time()-8*3600)+'.jpg'
				cv2.imwrite(path,img)

	def __det__(self):
		self.videoCapture.release()


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

	gps=GPS(cfg)
	

	if( cfg.act == 'testSerial' ):
		gps.testSerial()

	if( cfg.act == 'record' ):
		videoRecorder=captureVideo(cfg.videoDevice)
		q=Queue()
		t1 = threading.Thread(target = videoRecorder.saveImg, args = (q,))
		t2 = threading.Thread(target = gps.dataToTxt, args = (q,))
		
		t1.start()
		t2.start()