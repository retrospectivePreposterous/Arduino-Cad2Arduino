;;;; Selected object entity is shown in 8x8 arduino led matrix.

(prompt "\nType ETM to run EntityToMatrix...\n")

(defun c:ETM (/ OBJ OBJENT OBJLAX PATH FILE NAME PTHFLE DES ICON)
(prompt "\n***EntityToMatrix is an application developed by ALEJANDRO BURGUENO DIAZ***\n")

(defun SLEEP (secs / endt)
(setq endt (+ (getvar "DATE") (/ secs 86400.0)))
(while (< (getvar "DATE") endt) T))

(vl-load-com)

;-------------------------------------------------------------------------------------------------------

;PATH WHERE .PS1 WILL BE STORED AND TITLE NAME:

(setq PATH "C:\\Windows\\Temp\\")
(setq FILE (strcat "matrix.ps1"))
(setq PTHFLE (strcat PATH FILE))
(setq FILE2 (strcat "matrix.bat"))
(setq PTHFLE2 (strcat PATH FILE2))

;-------------------------------------------------------------------------------------------------------

;OBJECT SELECTION AND TRANSFORMATION TO VLA AND TO ENT:

(setq OBJ (car(entsel "\n Select an object .. " )))

(setq OBJLAX (vlax-ename->vla-object OBJ))
(setq OBJENT (entget OBJ))

;-------------------------------------------------------------------------------------------------------

;GET DATA STRINGS:

(setq PROP01 (strcat "Entity: " (cdr (assoc 0 OBJENT)) ) )

(if  (eq (cdr (assoc 0 OBJENT)) "LINE") (setq ICON "line") )
(if  (or (eq (cdr (assoc 0 OBJENT)) "LWPOLYLINE") (eq (cdr (assoc 0 OBJENT)) "POLYLINE") ) (setq ICON "pline") )
(if  (eq (cdr (assoc 0 OBJENT)) "CIRCLE") (setq ICON "circle") )
(if  (eq (cdr (assoc 0 OBJENT)) "ELLIPSE") (setq ICON "ellipse") )
(if  (eq (cdr (assoc 0 OBJENT)) "POINT") (setq ICON "point") )
(if  (eq (cdr (assoc 0 OBJENT)) "INSERT") (setq ICON "block") )
(if  (or (eq (cdr (assoc 0 OBJENT)) "TEXT") (eq (cdr (assoc 0 OBJENT)) "MTEXT") ) (setq ICON "text") )
(if  (eq (cdr (assoc 0 OBJENT)) "3DSOLID") (setq ICON "solid") )
(if  (or (eq (cdr (assoc 0 OBJENT)) "LOFTEDSURFACE") (eq (cdr (assoc 0 OBJENT)) "EXTRUDEDSURFACE") ) (setq ICON "surface") )
(if  (eq (cdr (assoc 0 OBJENT)) "MESH") (setq ICON "mesh") )

;-------------------------------------------------------------------------------------------------------

;POWERSHELL:

(setq L01 (strcat "$port = New-Object System.IO.Ports.SerialPort" )  )
(setq L02 (strcat "$port.PortName = " (chr 34) "COM7" (chr 34) )  )
(setq L03 (strcat "$port.BaudRate = " (chr 34) "9600" (chr 34) )  ) 
(setq L04 (strcat "$port.open()" )  ) 

(setq L05 (strcat "Start-Sleep -Milliseconds 1000" )  ) 
(setq L06 (strcat "$port.Write(" (chr 34) "matrix`n" (chr 34) ")" )  ) 
(setq L07 (strcat "Start-Sleep -Milliseconds 2000" )  ) 
(setq L08 (strcat "$port.Write(" (chr 34) ICON "`n" (chr 34) ")" )  ) 

(setq L10 (strcat "$port.Close()" )  ) 

(setq DES (open PTHFLE "w")) (write-line L01 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L02 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L03 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L04 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L05 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L06 DES) (close DES)
(setq DES (open PTHFLE "a")) (write-line L07 DES) (close DES) 
(setq DES (open PTHFLE "a")) (write-line L08 DES) (close DES)

(setq DES (open PTHFLE "a")) (write-line L10 DES) (close DES) 

;-------------------------------------------------------------------------------------------------------

;BAT:

(setq LBAT (strcat "Powershell.exe -executionpolicy remotesigned -File " PTHFLE )  ) 
(setq DES (open PTHFLE2 "w")) (write-line LBAT DES) (close DES)

(startapp PTHFLE2)

(SLEEP 5)

(vl-file-delete PTHFLE)
(vl-file-delete PTHFLE2)
)