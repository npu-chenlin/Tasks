# coding=utf-8
#This prog is built for testting GPS & record GPS data while taking pics.
#Before using this , u should run 'VideoGPSRecorder.py --act testSerial --port <ur path by default /dev/ttyUSB0> --baud <ur baudrate by default 115200> to test if GPS is workable.'
#If u want to see more details , run 'VideoGPSRecorder.py --seeDetail 1'.


import time,os,sys
import numpy as np
import serial
import cv2
#import requests,json
import argparse
import threading
from queue import Queue


def getUTC_timestamp():
    t_l      = time.time()
    ts_utc   = t_l + time.altzone
    return ts_utc

class GPS:
    def __init__(self,cfg):
        self.cfg = cfg
        self.port=cfg.port
        self.baud=cfg.baud
        self.ser=serial.Serial(self.port,self.baud)

    def _parse_GPGGA(self,l):
        #解析传送过来的GPS信号
        if(l[2] and l[1]):
            timestamp = self._getTimestampUTC(l[1])
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
        #获取UTC时间。由于time.mktime函数只能精确到秒，故先将系统时间读取出来，再加上从GPS读取到的毫秒数。
        t_ = time.gmtime(time.time())
        l=str(l)
        t = (t_.tm_year,t_.tm_mon,t_.tm_mday,int(l[:2]),int(l[2:4]),int(l[4:6]),t_.tm_wday,t_.tm_yday,t_.tm_isdst)
        return time.mktime(t)+float(l[6:])

    def _read_GPS(self):
        #读取GPS信号，筛选出有用信号后，格式化再传入_parse_GPGGA。
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

    def testSerial(self,timeout=10):
        t=time.time()
        while(1):
            l = self._read_GPS()
            if(type(l) == list):
                print('\nFound the signal successfully!!\n')
                return 1
            sys.stdout.flush()
            d=int(round((time.time()-t)/(timeout)*100))
            sys.stdout.write(l+str(d)+'%'+'>'*d+'\r')
            if(time.time()-t>timeout):
                print("\nCan't find satellites,try somewhere else")
                return 0

    def dataToTxt(self,q):
        if(self.testSerial()):
            path= os.path.join(self.cfg.dataPrefix , 'GPS_data.txt')
            flag=0
            with open(path,'a') as f:
            	print('Writing data to txt\n')
                cv2.imshow('Press q to exit',np.zeros((20,10)))
                while(cv2.waitKey(1) & 0xFF != ord('q')):
                    r=self._read_GPS()
                    print(r)
                    if(type(r) == list):
                        if(not flag):
                            flag = 1
                            q.put(1)
                        f.writelines(r)
                    else:
                        if(flag):
                            flag = 0
                            q.put(0)
        q.put(-1)
        return 0    

class CaptureVideo:
    def __init__(self,cfg):
        self.cfg = cfg
        self.videoCapture = cv2.VideoCapture(cfg.videoDevice)
        self.videoCapture.set(3,cfg.imgW)
        self.videoCapture.set(4,cfg.imgH)
        self.videoCapture.set(5,cfg.FPS)
        self.flag=0

    def saveImg(self,q):
        p = os.path.join(self.cfg.dataPrefix, 'images')
        os.mkdir(p)

        sucess,frame=self.videoCapture.read()
        while(sucess):
            while not q.empty():
                self.flag=q.get()

            if (self.flag == 0):
                continue
            if (self.flag == 1):
                sucess,frame=self.videoCapture.read()
                ts_utc = getUTC_timestamp()
                path = os.path.join(p, "%f" % ts_utc + '.jpg')
                cv2.imwrite(path,frame)
            if (self.flag == -1):
                break

    def __det__(self):
        self.videoCapture.release()
        print('Camera closed')

def parseArguments():
    parser = argparse.ArgumentParser(description='Record video & GPS information')

    parser.add_argument('--act', default='record', help='Action type (record, testSerial')

    parser.add_argument('--port', default='/dev/ttyUSB0', help='GPS port (eg: /dev/ttyUSB0)')
    parser.add_argument('--baud', default=115200, help='Serial port baud rate')

    parser.add_argument('--videoDevice', default=0, help='Video device number')
    parser.add_argument('--imgW', default=640, help='Default image width')
    parser.add_argument('--imgH', default=480, help='Default image height')
    parser.add_argument('--FPS', default=30, help='Video frame per second')

    parser.add_argument('--seeDetail', default=0, help='Show details. By deault 0')

    df = time.strftime('data_%Y%m%d-%H%M%s')
    main_dir = os.path.dirname(os.path.realpath(__file__))
    p = os.path.join(main_dir, df)
    parser.add_argument('--dataPrefix', default=p, help='Stored data prefix')

    args = parser.parse_args()
    return args

if __name__=='__main__':
    
    # parse input arguments
    cfg = parseArguments()

    # open GPS device
    gps=GPS(cfg)
    
    if( cfg.seeDetail == '1'):
        t=time.time()
        while(time.time()-t<20):
            l=gps.ser.readline().split(',')
            while(not (l[0]=='$GPGGA' or l[0]=='$GNGGA')):
                l=gps.ser.readline().split(',')
            print(l)

    elif( cfg.act == 'testSerial' ):
        gps.testSerial()
    
    elif( cfg.act == 'record' ):
        os.mkdir(cfg.dataPrefix)
        print('Initializing camera: '+str(cfg.videoDevice))
        videoRecorder=CaptureVideo(cfg)
        print('Camera prepared')
        q=Queue()
        try:
            t1 = threading.Thread(target = videoRecorder.saveImg, args = (q,))
            t2 = threading.Thread(target = gps.dataToTxt, args = (q,))
        
            t1.start()
            t2.start()

        finally:
            del videoRecorder