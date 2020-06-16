;;;; Gets selected block orientation and rotates Arduino Servo in same angle.

(prompt "\nType ATS to run BlockAngleToServo...\n")

(defun c:ATS (/ OBJ OBJENT OBJLAX PATH FILE NAME PTHFLE DES)
(prompt "\n***BlockAngleToServo is an application developed by ALEJANDRO BURGUENO DIAZ***\n")

(defun SLEEP (secs / endt)
(setq endt (+ (getvar "DATE") (/ secs 86400.0)))
(while (< (getvar "DATE") endt) T))

(vl-load-com)

;-------------------------------------------------------------------------------------------------------

;PATH WHERE .PS1 WILL BE STORED AND TITLE NAME:

(setq PATH "C:\\Windows\\Temp\\")
(setq FILE (strcat "rotate.ps1"))
(setq PTHFLE (strcat PATH FILE))
(setq FILE2 (strcat "rotate.bat"))
(setq PTHFLE2 (strcat PATH FILE2))

;-------------------------------------------------------------------------------------------------------

;OBJECT SELECTION AND TRANSFORMATION TO VLA AND TO ENT:

(setq OBJ (car(entsel "\n Select an object with rotation .. " )))

(setq OBJLAX (vlax-ename->vla-object OBJ))
(setq OBJENT (entget OBJ))

;-------------------------------------------------------------------------------------------------------

;GET DATA:

(if (eq (cdr (assoc 0 OBJENT)) "INSERT")
(progn
(setq BANG (cdr (assoc 50 OBJENT)) )
(setq BANG (rtos (/ BANG 0.017453289)) )
)
(princ "Object without rotation")
)

;-------------------------------------------------------------------------------------------------------

;POWERSHELL:

(setq L01 (strcat "$port = New-Object System.IO.Ports.SerialPort" )  )
(setq L02 (strcat "$port.PortName = " (chr 34) "COM7" (chr 34) )  )
(setq L03 (strcat "$port.BaudRate = " (chr 34) "9600" (chr 34) )  ) 
(setq L04 (strcat "$port.open()" )  ) 

(setq L05 (strcat "Start-Sleep -Milliseconds 1000" )  ) 
(setq L06 (strcat "$port.Write(" (chr 34) "servo`n" (chr 34) ")" )  ) 
(setq L07 (strcat "Start-Sleep -Milliseconds 2000" )  ) 
(setq L08 (strcat "$port.Write(" (chr 34) BANG "`n" (chr 34) ")" )  )

(setq L09 (strcat "$port.Close()" )  ) 

(setq DES (open PTHFLE "w")) (write-line L01 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L02 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L03 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L04 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L05 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L06 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L07 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L08 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L09 DES) (close DES)

;-------------------------------------------------------------------------------------------------------

;BAT:

(setq LBAT (strcat "Powershell.exe -executionpolicy remotesigned -File " PTHFLE )  ) 
(setq DES (open PTHFLE2 "w")) (write-line LBAT DES) (close DES)

(startapp PTHFLE2)

(SLEEP 5)

(vl-file-delete PTHFLE)
(vl-file-delete PTHFLE2)
)