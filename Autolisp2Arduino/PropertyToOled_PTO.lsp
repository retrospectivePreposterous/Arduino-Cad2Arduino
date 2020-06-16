;;;; Property data of selected object is shown in the Oled Display.

(prompt "\nType PTO to run PropertyToOled...\n")

(defun c:PTO (/ OBJ OBJENT OBJLAX PATH FILE NAME PTHFLE DES)
(prompt "\n***PropertyToOled is an application developed by ALEJANDRO BURGUENO DIAZ***\n")

(defun SLEEP (secs / endt)
(setq endt (+ (getvar "DATE") (/ secs 86400.0)))
(while (< (getvar "DATE") endt) T))

(vl-load-com)

;-------------------------------------------------------------------------------------------------------

;PATH WHERE .PS1 WILL BE STORED AND TITLE NAME:

(setq PATH "C:\\Windows\\Temp\\")
(setq FILE (strcat "properties.ps1"))
(setq PTHFLE (strcat PATH FILE))
(setq FILE2 (strcat "properties.bat"))
(setq PTHFLE2 (strcat PATH FILE2))

;-------------------------------------------------------------------------------------------------------

;OBJECT SELECTION AND TRANSFORMATION TO VLA AND TO ENT:

(setq OBJ (car(entsel "\n Select an object .. " )))

(setq OBJLAX (vlax-ename->vla-object OBJ))
(setq OBJENT (entget OBJ))

;-------------------------------------------------------------------------------------------------------

;GET DATA STRINGS:

(setq PROP01 (strcat "Entity: " (cdr (assoc 0 OBJENT)) ) )
(setq PROP02 (strcat "Layer:  " (cdr (assoc 8 OBJENT)) ) )
(setq PROP03 (strcat "Handle: " (vla-get-handle OBJLAX) ) )

(if  (= (vlax-property-available-p OBJLAX 'Length) nil)
(setq PROP04 "Lenght: ---" )
(setq PROP04 (strcat "Lenght: " (rtos(vla-get-length OBJLAX)) ) )
)

(if  (= (vlax-property-available-p OBJLAX 'Area) nil)
(setq PROP05 "Area:   ---" )
(setq PROP05 (strcat "Area:   " (rtos(vla-get-area OBJLAX)) ) )
)

(if  (= (vlax-property-available-p OBJLAX 'Volume) nil)
(setq PROP06 "Volume: ---" )
(setq PROP06 (strcat "Volume: " (rtos(vla-get-volume OBJLAX)) ) )
)

(if  (= (vlax-property-available-p OBJLAX 'Effectivename) nil)
(setq PROP07 "Name:   ---" )
(setq PROP07 (strcat "Name:   " (vla-get-effectivename OBJLAX) ) )
)

;-------------------------------------------------------------------------------------------------------

;POWERSHELL:

(setq L01 (strcat "$port = New-Object System.IO.Ports.SerialPort" )  )
(setq L02 (strcat "$port.PortName = " (chr 34) "COM7" (chr 34) )  )
(setq L03 (strcat "$port.BaudRate = " (chr 34) "9600" (chr 34) )  ) 
(setq L04 (strcat "$port.open()" )  ) 

(setq L05 (strcat "Start-Sleep -Milliseconds 1000" )  ) 
(setq L06 (strcat "$port.Write(" (chr 34) "`n" (chr 34) ")" )  ) 
(setq L07 (strcat "Start-Sleep -Milliseconds 2000" )  ) 
(setq L08 (strcat "$port.Write(" (chr 34) "clear`n" (chr 34) ")" )  ) 
(setq L09 (strcat "Start-Sleep -Milliseconds 2000" )  ) 
(setq L10 (strcat "$port.Write(" (chr 34) "text`n" (chr 34) ")" )  ) 
(setq L11 (strcat "Start-Sleep -Milliseconds 2000" )  ) 

(setq L12 (strcat "$port.Write(" (chr 34) PROP01 "`n" (chr 34) ")" )  ) 
(setq L13 (strcat "$port.Write(" (chr 34) PROP02 "`n" (chr 34) ")" )  ) 
(setq L14 (strcat "$port.Write(" (chr 34) PROP03 "`n" (chr 34) ")" )  ) 
(setq L15 (strcat "$port.Write(" (chr 34) PROP04 "`n" (chr 34) ")" )  ) 
(setq L16 (strcat "$port.Write(" (chr 34) PROP05 "`n" (chr 34) ")" )  ) 
(setq L17 (strcat "$port.Write(" (chr 34) PROP06 "`n" (chr 34) ")" )  ) 
(setq L18 (strcat "$port.Write(" (chr 34) PROP07 "`n" (chr 34) ")" )  ) 

(setq L19 (strcat "$port.Close()" )  ) 

(setq DES (open PTHFLE "w")) (write-line L01 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L02 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L03 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L04 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L05 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L06 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L07 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L08 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L09 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L10 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L11 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L12 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L13 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L14 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L15 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L16 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L17 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L18 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L19 DES) (close DES)

;-------------------------------------------------------------------------------------------------------

;BAT:

(setq LBAT (strcat "Powershell.exe -executionpolicy remotesigned -File " PTHFLE )  ) 
(setq DES (open PTHFLE2 "w")) (write-line LBAT DES) (close DES)

(startapp PTHFLE2)

(SLEEP 5)

(vl-file-delete PTHFLE)
(vl-file-delete PTHFLE2)
)