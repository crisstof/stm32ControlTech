Atollic:
File/New/C/C++Project
C/C++>Embedded>Standard
choisir la référence du microcontrôleur.
avoir le fichier stm32cubeL afin d'avoir les bibliothèques
https://htmlpreview.github.io/?https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Release_Notes.html
https://github.com/STMicroelectronics/STM32CubeL4
modules CMSIS: (coeur et périphérique) corresondant au coeur ARM(tm) 
               implémenté dans ce produit
HAL-LL: couche d'abstraction offrant un ensemble d'API garatissant une 
        portabilité maximisée sur l'ensemble du portefeuille STM2
BSP: pilotes BSP de chaque carte d'évaluation, de démonstration ou 
     nucléo fournie pour cette série STM32.
Middlewares: bibliothèques telles que RTOS, USB, FatFS, graphiques, détection tactile.


-------------------
bootloader origine
-------------------
Drivers/CMSIS/ST/STM32L4xx/include>fichiers stm32l476xx.h  ...
       /Include/ arm.h, core.h, cmsis.h ...
STM32L4xx_HAL_Driver/Inc/Readme.txt
                    /Src/Readme.txt
src/main.c, startup_stm32l476xx.s, system_stm32l4xx.c, tiny_printf.c
Debug/src/ ...
     /bootLoader.elf ...



----------
bootloader
----------
Drivers
       /BSP/Components/Common/fic.h
                      /stmpe811/fic{c;h}
                      /stmpe1600/fic{c;h}
           /STM32476G_EVAL/fic{c;h}
      /CMSIS/include/fic.h                   #sauf core_cmFunc.h, core_cmInstr.h, core_cmSimd.h, stm32l475xx.h, stm32l4xx.h, sysetm_stm32l4xx.h
            /source/system_stm32l4xx.h       #à l'origine il est dans src et le fichier a été créé

STM32L4xx_HAL_Driver/Inc/Readme.txt          #ajouter Legacy et les fichiers HAL.h 
                    /Src/Readme.txt          #ajouter Legacy et les fichiers HAL.c

Inc/fic.h   #flash_if.h, IAP.h, main.h, stm32l4xx_hal_conf.h, stm32l4xx_it.h, usbd_conf.h, usbd_desc.h, usbd_storage.h
		#dans STM32CubeL4-master/Projects/NUCLEO-L476RG:
                #stm32l4xx_hal_conf.h, stm32l4xx_it.h, main.h, 
                #dans STM32CubeL4-master/Projects/STM32476G-EVAL/Applications:
                #flash_if, IAP.h est construit, dans USB_Device/MSC_Standalone: usbd_conf.h, usbd_desc.h, usbd_storage.h

Middlewares/FatFS/src/fic.c  #diskio.c, ff_gen_drv.c, ff.c, ffsystem.c, ffunicode.c, sd_diskio.c, syscall.c
                /fic.h       #diskio.h, ff_gen_drv.h, ff.h, integer.h, sd_diskio.h
           /STM32_USB_Device_Library             #STM32Cubel4>Middlewares>ST>STM32_USB_Device_Library
                                    /Class/MSC/Inc         
                                              /Src
               			    /Core/Inc
 					 /Src
			            Release_Notes.html
scripts/GetRevision.class et getrevision.java #fait automatique par java

Src/flash_if.c, IAP.c, main.c, proc.c, proc.h; stm32l4xx_it.c, usbd_conf.c, usbd_desc.c, usbd_storage.c, version.h

ensuite seul on a le fichier startup_stm32l476xx.s et Debug Bootloader.launch et Download Bootloader.launch  et STM32L476_FLASH.Id




------------
application
------------
Drivers/
       
      /CMSIS/Device/ST/STM32L4xx/Include/   stm32l476xx.h, stm32l4xx.h, system_stm32l4xx.h
            /Include/arm.h ..., core_cm4.h ....
      /Modules/GPS
		/LED
		/PSU
		/SD
     /Sensors/External/fic{cpp, hpp}
	     /Internal/fic{cpp, hpp}
	     /rtd
	     /factory, adc,i2c,sdi,uart,sensor {cpp,hpp} 
	     /STM32L4xx_HAL_Driver/Inc/hal.h .... + /legacy
				  /Src/hal.c
Inc/config, it, stm32l4xx_hal_conf, stm32l4xx_it,version, version-rev .h 
Middlewares/battery
		/datalog
		/Environment
		/FatFS
		/JSON
		/Network
		/Periodic
		/Peripherals
		/SDI-12
		/timer
		Uti
Src/it.c, main.cpp, stm32l4xx_it.c
boards/
codec/connecsens-rf/datatypes ...
common/datetime{c;h}, defs, logger, units, utils
startup/startup_stm32l476xx.s
debug/
config_tp/tp_config_xxx.json ...
configTemplate/config_capteur.json
scripts/GetRevision.java

ce programme crée dans debug application.binary c'est le programme que l'on doit installer dans la carte SD






STM32L4xx_HAL_Driver/Inc/Readme.txt          #ajouter Legacy et les fichiers HAL.h 
                    /Src/Readme.txt          #ajouter Legacy et les fichiers HAL.c

Inc/fic.h   #flash_if.h, IAP.h, main.h, stm32l4xx_hal_conf.h, stm32l4xx_it.h, usbd_conf.h, usbd_desc.h, usbd_storage.h
		#dans STM32CubeL4-master/Projects/NUCLEO-L476RG:
                #stm32l4xx_hal_conf.h, stm32l4xx_it.h, main.h, 
                #dans STM32CubeL4-master/Projects/STM32476G-EVAL/Applications:
                #flash_if, IAP.h est construit, dans USB_Device/MSC_Standalone: usbd_conf.h, usbd_desc.h, usbd_storage.h

Middlewares/FatFS/src/fic.c  #diskio.c, ff_gen_drv.c, ff.c, ffsystem.c, ffunicode.c, sd_diskio.c, syscall.c
                /fic.h       #diskio.h, ff_gen_drv.h, ff.h, integer.h, sd_diskio.h
           /STM32_USB_Device_Library             #STM32Cubel4>Middlewares>ST>STM32_USB_Device_Library
                                    /Class/MSC/Inc         
                                              /Src
               			    /Core/Inc
 					 /Src
			            Release_Notes.html
scripts/GetRevision.class et getrevision.java #fait automatique par java

Src/flash_if.c, IAP.c, main.c, proc.c, proc.h; stm32l4xx_it.c, usbd_conf.c, usbd_desc.c, usbd_storage.c, version.h

ensuite seul on a le fichier startup_stm32l476xx.s et Debug Bootloader.launch et Download Bootloader.launch  et STM32L476_FLASH.Id





-------------------------------------------------------------------------------------------------------------------------------------
Utilisation de l'application bootloader
------------------------------------------------------------------------
bootloader restructuration de l'architecture de fichier avec stm32CubeL4
------------------------------------------------------------------------
Drivers
       /BSP/Components/Common/...
                      /stmpe811/...
                      /stmpe1600/...
           /STM32476G_EVAL/...

      /CMSIS/include/origine +  (stm32l475xx.h, stm32l4xx.h, sysetm_stm32l4xx.h) dans Device/ST/STM32L4xx/Includes
            /source/system_stm32l4xx.h       #dans à l'origine il est dans src et le fichier a été créé
					     #ou dans Device/ST/STM32L4xx/Source/Templates

STM32L4xx_HAL_Driver/Inc/Readme.txt          #ajouter Legacy et les fichiers HAL.h 
                    /Src/Readme.txt          #ajouter Legacy et les fichiers HAL.c


Inc/fic.h   #flash_if.h, IAP.h, main.h, stm32l4xx_hal_conf.h, stm32l4xx_it.h, usbd_conf.h, usbd_desc.h, usbd_storage.h
		#dans STM32CubeL4-master/Projects/STM32476G-EVAL/Templates/Inc:stm32l4xx_hal_conf.h, stm32l4xx_it.h, main.h
		#l'application l'a pris dans USB_Device/MSC_Standalone/Inc/:stm32l4xx_hal_conf.h, stm32l4xx_it.h, main.h
		#IAP.h le construire ce sera plus simple
								#include "main.h"
								#include "ff.h"
								#include "flash_if.h"

								void IAP(FIL *file);

                #dans STM32CubeL4-master/Projects/STM32476G-EVAL/Applications:
                #           , dans              USB_Device/MSC_Standalone: usbd_conf.h, usbd_desc.h, usbd_storage.h
		#il manque plus que flash_if:   IAP/IAP_Main/Inc: flash_if

Middlewares/FatFS/src/fic.c   #diskio.c, ff_gen_drv.c, ff.c, (ffsystem.c (non trouvé), ffunicode.c(non trouvé), sd_diskio.c[src/driver], syscall.c[src/option]) 
                 /fic.h       #diskio.h, ff_gen_drv.h, ff.h, integer.h, (sd_diskio.h) dans src/driver
            /dans Middlewares/Third_Party/FatFs/src/
           
	   /ST/STM32_USB_Device_Library             #STM32Cubel4>Middlewares>ST>STM32_USB_Device_Library/Class et l'autre Core
                                    /Class/MSC/Inc   (ok attention template)      
                                              /Src   (ok attention template) 
               			    /Core/Inc
 					 /Src
			            Release_Notes.html

scripts/GetRevision.class et getrevision.java #fait automatique par java

src/flash_if.c, IAP.c, main.c, proc.c, proc.h; stm32l4xx_it.c, usbd_conf.c, usbd_desc.c, usbd_storage.c, version.h
USB_Device/MSC_Standalone/Src/...usbd_conf.c, usbd_desc.c, usbd_storage.c, stm32l4xx_it.c
C:\WorkConnecSens\BootloaderOne\stm32cubeL\STM32CubeL4-master\STM32CubeL4-master\Projects\STM32L476G-EVAL\Applications\USB_Device\MSC_Standalone\Src
C:\WorkConnecSens\BootloaderOne\stm32cubeL\STM32CubeL4-master\STM32CubeL4-master\Projects\STM32L476G-EVAL\Applications\IAP\IAP_Main\Src
pour proc{c,h} construire


----------------------------------------------------------------------------------------------------------------------------------------
Flash Boot:
https://www.st.com/content/st_com/en.html
dfuse usb 
Compréhension du programme:






































