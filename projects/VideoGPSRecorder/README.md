#This prog is built for testting GPS & record GPS data while taking pics.

##It shall be run in the cmd window with at least 2 parameters.
```
usage: VideoGPSRecorder.py [-h] [--act ACT] [--port PORT] [--baud BAUD]
                           [--videoDevice VIDEODEVICE] [--seeDetail SEEDETAIL]
                           [--dataPrefix DATAPREFIX]

optional arguments:
  -h, --help            show this help message and exit
  --act ACT             Action type (record, testSerial
  --port PORT           GPS port (eg: /dev/ttyUSB0)
  --baud BAUD           Serial port baud rate
  --videoDevice VIDEODEVICE
                        Video device number.By default 0
  --seeDetail SEEDETAIL
                        Show details. By default 0
```
##Before using this , u should run
`python VideoGPSRecorder.py --act testSerial --port <ur GPS path by default /dev/ttyUSB0> --baud <ur baudrate by default 115200>`  
##to make sure ur GPS is workable.

##Then run
`python VideoGPSRecorder.py --port PORT --baud BAUD`
##to record.

##If u want to see more GPS details , run  
`VideoGPSRecorder.py --seeDetail 1`
